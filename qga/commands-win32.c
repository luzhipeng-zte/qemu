/*
 * QEMU Guest Agent win32-specific command implementations
 *
 * Copyright IBM Corp. 2012
 *
 * Authors:
 *  Michael Roth      <mdroth@linux.vnet.ibm.com>
 *  Gal Hammer        <ghammer@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 */

#include <glib.h>
#include <wtypes.h>
#include <powrprof.h>
#include "qga/guest-agent-core.h"
#include "qga/guest-file-command-state.h"
#include "qga-qmp-commands.h"
#include "qapi/qmp/qerror.h"

#ifndef SHTDN_REASON_FLAG_PLANNED
#define SHTDN_REASON_FLAG_PLANNED 0x80000000
#endif

static void acquire_privilege(const char *name, Error **err)
{
    HANDLE token;
    TOKEN_PRIVILEGES priv;
    Error *local_err = NULL;

    if (error_is_set(err)) {
        return;
    }

    if (OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &token))
    {
        if (!LookupPrivilegeValue(NULL, name, &priv.Privileges[0].Luid)) {
            error_set(&local_err, QERR_QGA_COMMAND_FAILED,
                      "no luid for requested privilege");
            goto out;
        }

        priv.PrivilegeCount = 1;
        priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if (!AdjustTokenPrivileges(token, FALSE, &priv, 0, NULL, 0)) {
            error_set(&local_err, QERR_QGA_COMMAND_FAILED,
                      "unable to acquire requested privilege");
            goto out;
        }

        CloseHandle(token);
    } else {
        error_set(&local_err, QERR_QGA_COMMAND_FAILED,
                  "failed to open privilege token");
    }

out:
    if (local_err) {
        error_propagate(err, local_err);
    }
}

static void execute_async(DWORD WINAPI (*func)(LPVOID), LPVOID opaque, Error **err)
{
    Error *local_err = NULL;

    if (error_is_set(err)) {
        return;
    }
    HANDLE thread = CreateThread(NULL, 0, func, opaque, 0, NULL);
    if (!thread) {
        error_set(&local_err, QERR_QGA_COMMAND_FAILED,
                  "failed to dispatch asynchronous command");
        error_propagate(err, local_err);
    }
}

void qmp_guest_shutdown(bool has_mode, const char *mode, Error **err)
{
    UINT shutdown_flag = EWX_FORCE;

    slog("guest-shutdown called, mode: %s", mode);

    if (!has_mode || strcmp(mode, "powerdown") == 0) {
        shutdown_flag |= EWX_POWEROFF;
    } else if (strcmp(mode, "halt") == 0) {
        shutdown_flag |= EWX_SHUTDOWN;
    } else if (strcmp(mode, "reboot") == 0) {
        shutdown_flag |= EWX_REBOOT;
    } else {
        error_set(err, QERR_INVALID_PARAMETER_VALUE, "mode",
                  "halt|powerdown|reboot");
        return;
    }

    /* Request a shutdown privilege, but try to shut down the system
       anyway. */
    acquire_privilege(SE_SHUTDOWN_NAME, err);
    if (error_is_set(err)) {
        return;
    }

    if (!ExitWindowsEx(shutdown_flag, SHTDN_REASON_FLAG_PLANNED)) {
        slog("guest-shutdown failed: %d", GetLastError());
        error_set(err, QERR_UNDEFINED_ERROR);
    }
}

/*
 * Return status of freeze/thaw
 */
GuestFsfreezeStatus qmp_guest_fsfreeze_status(Error **err)
{
    error_set(err, QERR_UNSUPPORTED);
    return 0;
}

/*
 * Walk list of mounted file systems in the guest, and freeze the ones which
 * are real local file systems.
 */
int64_t qmp_guest_fsfreeze_freeze(Error **err)
{
    error_set(err, QERR_UNSUPPORTED);
    return 0;
}

/*
 * Walk list of frozen file systems in the guest, and thaw them.
 */
int64_t qmp_guest_fsfreeze_thaw(Error **err)
{
    error_set(err, QERR_UNSUPPORTED);
    return 0;
}

/*
 * Walk list of mounted file systems in the guest, and discard unused
 * areas.
 */
void qmp_guest_fstrim(bool has_minimum, int64_t minimum, Error **err)
{
    error_set(err, QERR_UNSUPPORTED);
}

typedef enum {
    GUEST_SUSPEND_MODE_DISK,
    GUEST_SUSPEND_MODE_RAM
} GuestSuspendMode;

static void check_suspend_mode(GuestSuspendMode mode, Error **err)
{
    SYSTEM_POWER_CAPABILITIES sys_pwr_caps;
    Error *local_err = NULL;

    if (error_is_set(err)) {
        return;
    }
    ZeroMemory(&sys_pwr_caps, sizeof(sys_pwr_caps));
    if (!GetPwrCapabilities(&sys_pwr_caps)) {
        error_set(&local_err, QERR_QGA_COMMAND_FAILED,
                  "failed to determine guest suspend capabilities");
        goto out;
    }

    switch (mode) {
    case GUEST_SUSPEND_MODE_DISK:
        if (!sys_pwr_caps.SystemS4) {
            error_set(&local_err, QERR_QGA_COMMAND_FAILED,
                      "suspend-to-disk not supported by OS");
        }
        break;
    case GUEST_SUSPEND_MODE_RAM:
        if (!sys_pwr_caps.SystemS3) {
            error_set(&local_err, QERR_QGA_COMMAND_FAILED,
                      "suspend-to-ram not supported by OS");
        }
        break;
    default:
        error_set(&local_err, QERR_INVALID_PARAMETER_VALUE, "mode",
                  "GuestSuspendMode");
    }

out:
    if (local_err) {
        error_propagate(err, local_err);
    }
}

static DWORD WINAPI do_suspend(LPVOID opaque)
{
    GuestSuspendMode *mode = opaque;
    DWORD ret = 0;

    if (!SetSuspendState(*mode == GUEST_SUSPEND_MODE_DISK, TRUE, TRUE)) {
        slog("failed to suspend guest, %s", GetLastError());
        ret = -1;
    }
    g_free(mode);
    return ret;
}

void qmp_guest_suspend_disk(Error **err)
{
    GuestSuspendMode *mode = g_malloc(sizeof(GuestSuspendMode));

    *mode = GUEST_SUSPEND_MODE_DISK;
    check_suspend_mode(*mode, err);
    acquire_privilege(SE_SHUTDOWN_NAME, err);
    execute_async(do_suspend, mode, err);

    if (error_is_set(err)) {
        g_free(mode);
    }
}

void qmp_guest_suspend_ram(Error **err)
{
    GuestSuspendMode *mode = g_malloc(sizeof(GuestSuspendMode));

    *mode = GUEST_SUSPEND_MODE_RAM;
    check_suspend_mode(*mode, err);
    acquire_privilege(SE_SHUTDOWN_NAME, err);
    execute_async(do_suspend, mode, err);

    if (error_is_set(err)) {
        g_free(mode);
    }
}

void qmp_guest_suspend_hybrid(Error **err)
{
    error_set(err, QERR_UNSUPPORTED);
}

GuestNetworkInterfaceList *qmp_guest_network_get_interfaces(Error **err)
{
    error_set(err, QERR_UNSUPPORTED);
    return NULL;
}

int64_t qmp_guest_get_time(Error **errp)
{
    error_set(errp, QERR_UNSUPPORTED);
    return -1;
}

void qmp_guest_set_time(int64_t time_ns, Error **errp)
{
    error_set(errp, QERR_UNSUPPORTED);
}

GuestLogicalProcessorList *qmp_guest_get_vcpus(Error **errp)
{
    error_set(errp, QERR_UNSUPPORTED);
    return NULL;
}

int64_t qmp_guest_set_vcpus(GuestLogicalProcessorList *vcpus, Error **errp)
{
    error_set(errp, QERR_UNSUPPORTED);
    return -1;
}

typedef struct GuestFileHandle {
    GIOChannel *chan;
    GPollFD pollfd;
    bool pollable;
} GuestFileHandle;

int64_t guest_file_handle_add_fd(int fd, const char *mode, Error **errp)
{
    GError *gerr = NULL;
    GuestFileHandle *gfh;

    gfh = g_new0(GuestFileHandle, 1);
    gfh->chan = g_io_channel_win32_new_fd(fd);
    if (strcmp(mode, "a")) {
        g_io_channel_win32_make_pollfd(gfh->chan,
                                       G_IO_IN | G_IO_OUT | G_IO_HUP | G_IO_ERR,
                                       &gfh->pollfd);
        gfh->pollable = true;
    }

    g_io_channel_set_encoding(gfh->chan, NULL, &gerr);
    if (gerr) {
        g_error_free(gerr);
        error_setg(errp, "error setting encoding for channel");
    }
    g_io_channel_set_buffered(gfh->chan, false);

    return guest_file_handle_add(gfh, errp);
}

int64_t qmp_guest_file_open(const char *path, bool has_mode, const char *mode, Error **err)
{
    GError *gerr = NULL;
    GuestFileHandle *gfh;
    int64_t handle;

    if (!has_mode) {
        mode = "r";
    }
    slog("guest-file-open called, filepath: %s, mode: %s", path, mode);
    gfh = g_new0(GuestFileHandle, 1);
    gfh->chan = g_io_channel_new_file(path, mode, &gerr);
    if (gerr) {
        error_setg_errno(err, errno, "failed to open file '%s' (mode: '%s')",
                         path, mode);
        g_free(gfh);
        return -1;
    }

    handle = guest_file_handle_add(gfh, err);
    if (error_is_set(err)) {
        g_io_channel_shutdown(gfh->chan, true, NULL);
        g_free(gfh);
        return -1;
    }

    slog("guest-file-open, handle: %d", handle);
    return handle;
}

void qmp_guest_file_close(int64_t handle, Error **err)
{
    GuestFileHandle *gfh = guest_file_handle_find(handle, err);
    //int ret;

    slog("guest-file-close called, handle: %ld", handle);
    if (!gfh) {
        return;
    }

#if 0
    ret = fclose(gfh->fh);
    if (ret == EOF) {
        error_setg_errno(err, errno, "failed to close handle");
        return;
    }
#endif

    g_io_channel_shutdown(gfh->chan, true, NULL);

    guest_file_handle_remove(handle);
}

struct GuestFileRead *qmp_guest_file_read(int64_t handle, bool has_count,
                                          int64_t count, Error **err)
{
    GuestFileRead *read_data = NULL;
    gchar *buf = NULL;
    GError *gerr = NULL;
    GIOStatus status;
    gsize read_count = 0;
    GIOCondition condition = 0;
    GuestFileHandle *gfh;

    gfh = guest_file_handle_find(handle, err);
    if (error_is_set(err)) {
        return NULL;
    }

    if (!has_count) {
        count = QGA_READ_COUNT_DEFAULT;
    } else if (count < 0) {
        error_setg(err, "value '%" PRId64 "' is invalid for argument count",
                   count);
        return NULL;
    }

    buf = g_malloc0(count+1);
    if (gfh->pollable) {
        if (g_io_channel_win32_poll(&gfh->pollfd, 1, 0)) {
            condition = gfh->pollfd.revents;
        }
    }

    if (!gfh->pollable || (condition & G_IO_IN)) {
        status = g_io_channel_read_chars(gfh->chan, buf, count, &read_count,
                                         &gerr);
        if (gerr) {
            error_setg(err, "failed to read file: %s", gerr->message);
            g_error_free(gerr);
            return NULL;
        }
    } else {
        status = G_IO_STATUS_NORMAL;
    }

    if (status == G_IO_STATUS_ERROR) {
        error_setg(err, "failed to read file");
        return NULL;
    } else {
        read_data = g_malloc0(sizeof(GuestFileRead));
        if (status == G_IO_STATUS_EOF) {
            read_data->eof = true;
        } else if (status == G_IO_STATUS_NORMAL) {
            buf[read_count] = 0;
            read_data->count = read_count;
            if (read_count) {
                read_data->buf_b64 = g_base64_encode((guchar *)buf, read_count);
            }
        }
    }

    /* TODO: need this check ? */
    if (buf) {
        g_free(buf);
    }

    return read_data;
}

GuestFileWrite *qmp_guest_file_write(int64_t handle, const char *buf_b64,
                                     bool has_count, int64_t count, Error **err)
{
    GuestFileWrite *write_data = NULL;
    gchar *buf;
    gsize buf_len;
    gsize write_count = 0;
    //FILE *fh;
    GError *gerr = NULL;
    GIOStatus status;
    GuestFileHandle *gfh;

    gfh = guest_file_handle_find(handle, err);
    if (error_is_set(err)) {
        return NULL;
    }

    buf = (gchar *)g_base64_decode(buf_b64, &buf_len);

    if (!has_count) {
        count = buf_len;
    } else if (count < 0 || count > buf_len) {
        error_setg(err, "value '%" PRId64 "' is invalid for argument count",
                   count);
        g_free(buf);
        return NULL;
    }

    status = g_io_channel_write_chars(gfh->chan, buf, count, &write_count,
                                      &gerr);
    if (gerr) {
        error_setg(err, "failed to write to file: %s", gerr->message); 
        slog("guest-file-write failed, handle: %ld", handle);
        return NULL;
    }

    if (status == G_IO_STATUS_ERROR) {
    } else {
        write_data = g_malloc0(sizeof(GuestFileWrite));
        if (status == G_IO_STATUS_EOF) {
            write_data->eof = true;
        } else if (status == G_IO_STATUS_NORMAL) {
            write_data->count = write_count;
        }
    }

#if 0
    write_count = fwrite(buf, 1, count, fh);
    if (ferror(fh)) {
        error_setg_errno(err, errno, "failed to write to file");
        slog("guest-file-write failed, handle: %ld", handle);
    } else {
        write_data = g_malloc0(sizeof(GuestFileWrite));
        write_data->count = write_count;
        write_data->eof = feof(fh);
    }
#endif
    g_free(buf);
    //clearerr(fh);

    return write_data;
}

struct GuestFileSeek *qmp_guest_file_seek(int64_t handle, int64_t offset,
                                          int64_t whence, Error **err)
{
    GuestFileSeek *seek_data = NULL;
    //FILE *fh;
    GIOStatus status;
    GError *gerr = NULL;
    //int ret;
    GuestFileHandle *gfh;

    gfh = guest_file_handle_find(handle, err);
    if (error_is_set(err)) {
        return NULL;
    }

    status = g_io_channel_seek_position(gfh->chan, offset, whence, &gerr);
    if (gerr) {
        error_setg(err, "failed to seek file: %s", gerr->message);
        return NULL;
    } else if (status == G_IO_STATUS_ERROR) {
        error_setg(err, "failed to seek file");
        return NULL;
    }

    seek_data = g_malloc0(sizeof(GuestFileRead));
    /* TODO: where is ftell() for glib? fix this!!!! */
    //seek_data->position = ftell(fh);
    seek_data->position = 0;
    /* TODO: how the hell do we get eof??? set false for now,
     * they'll pick it up on a subsequent read at least */
    seek_data->eof = 0;
    //seek_data->eof = feof(fh);


#if 0
    fh = gfh->fh;
    ret = fseek(fh, offset, whence);
    if (ret == -1) {
        error_setg_errno(err, errno, "failed to seek file");
    } else {
    }
    clearerr(fh);
#endif

    return seek_data;
}

void qmp_guest_file_flush(int64_t handle, Error **err)
{
    //FILE *fh;
    GIOStatus status;
    GError *gerr = NULL;
    //int ret;
    GuestFileHandle *gfh;

    gfh = guest_file_handle_find(handle, err);
    if (error_is_set(err)) {
        return;
    }

    status = g_io_channel_flush(gfh->chan, &gerr);
    if (gerr) {
        error_setg(err, "failed to flush file: %s", gerr->message);
        g_error_free(gerr);
    } else if (status == G_IO_STATUS_ERROR) {
        error_setg(err, "failed to flush file");
    }

#if 0
    fh = gfh->fh;
    ret = fflush(fh);
    if (ret == EOF) {
        error_setg_errno(err, errno, "failed to flush file");
    }
#endif
}

/* register init/cleanup routines for stateful command groups */
void ga_command_state_init(GAState *s, GACommandState *cs)
{
    ga_command_state_add(cs, guest_file_init, NULL);
}
