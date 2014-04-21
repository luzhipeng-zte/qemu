DEF_HELPER_3(raise_exception_err, void, env, i32, i32)
DEF_HELPER_2(raise_exception, void, env, i32)
DEF_HELPER_4(tw, void, env, tl, tl, i32)
#if defined(TARGET_PPC64)
DEF_HELPER_4(td, void, env, tl, tl, i32)
#endif
#if !defined(CONFIG_USER_ONLY)
DEF_HELPER_2(store_msr, void, env, tl)
DEF_HELPER_1(rfi, void, env)
DEF_HELPER_1(rfsvc, void, env)
DEF_HELPER_1(40x_rfci, void, env)
DEF_HELPER_1(rfci, void, env)
DEF_HELPER_1(rfdi, void, env)
DEF_HELPER_1(rfmci, void, env)
#if defined(TARGET_PPC64)
DEF_HELPER_1(rfid, void, env)
DEF_HELPER_1(hrfid, void, env)
#endif
#endif

DEF_HELPER_3(lmw, void, env, tl, i32)
DEF_HELPER_3(stmw, void, env, tl, i32)
DEF_HELPER_4(lsw, void, env, tl, i32, i32)
DEF_HELPER_5(lswx, void, env, tl, i32, i32, i32)
DEF_HELPER_4(stsw, void, env, tl, i32, i32)
DEF_HELPER_3(dcbz, void, env, tl, i32)
DEF_HELPER_2(icbi, void, env, tl)
DEF_HELPER_5(lscbx, tl, env, tl, i32, i32, i32)

#if defined(TARGET_PPC64)
DEF_HELPER_3(mulldo, i64, env, i64, i64)
DEF_HELPER_4(divdeu, i64, env, i64, i64, i32)
DEF_HELPER_4(divde, i64, env, i64, i64, i32)
#endif
DEF_HELPER_4(divweu, tl, env, tl, tl, i32)
DEF_HELPER_4(divwe, tl, env, tl, tl, i32)

DEF_HELPER_FLAGS_1(cntlzw, TCG_CALL_NO_RWG_SE, tl, tl)
DEF_HELPER_FLAGS_1(popcntb, TCG_CALL_NO_RWG_SE, tl, tl)
DEF_HELPER_FLAGS_1(popcntw, TCG_CALL_NO_RWG_SE, tl, tl)
DEF_HELPER_FLAGS_2(cmpb, TCG_CALL_NO_RWG_SE, tl, tl, tl)
DEF_HELPER_3(sraw, tl, env, tl, tl)
#if defined(TARGET_PPC64)
DEF_HELPER_FLAGS_1(cntlzd, TCG_CALL_NO_RWG_SE, tl, tl)
DEF_HELPER_FLAGS_1(popcntd, TCG_CALL_NO_RWG_SE, tl, tl)
DEF_HELPER_FLAGS_2(bpermd, TCG_CALL_NO_RWG_SE, i64, i64, i64)
DEF_HELPER_3(srad, tl, env, tl, tl)
#endif

DEF_HELPER_FLAGS_1(cntlsw32, TCG_CALL_NO_RWG_SE, i32, i32)
DEF_HELPER_FLAGS_1(cntlzw32, TCG_CALL_NO_RWG_SE, i32, i32)
DEF_HELPER_FLAGS_2(brinc, TCG_CALL_NO_RWG_SE, tl, tl, tl)

DEF_HELPER_1(float_check_status, void, env)
DEF_HELPER_1(reset_fpstatus, void, env)
DEF_HELPER_3(compute_fprf, i32, env, i64, i32)
DEF_HELPER_3(store_fpscr, void, env, i64, i32)
DEF_HELPER_2(fpscr_clrbit, void, env, i32)
DEF_HELPER_2(fpscr_setbit, void, env, i32)
DEF_HELPER_2(float64_to_float32, i32, env, i64)
DEF_HELPER_2(float32_to_float64, i64, env, i32)

DEF_HELPER_4(fcmpo, void, env, i64, i64, i32)
DEF_HELPER_4(fcmpu, void, env, i64, i64, i32)

DEF_HELPER_2(fctiw, i64, env, i64)
DEF_HELPER_2(fctiwu, i64, env, i64)
DEF_HELPER_2(fctiwz, i64, env, i64)
DEF_HELPER_2(fctiwuz, i64, env, i64)
#if defined(TARGET_PPC64)
DEF_HELPER_2(fcfid, i64, env, i64)
DEF_HELPER_2(fcfidu, i64, env, i64)
DEF_HELPER_2(fcfids, i64, env, i64)
DEF_HELPER_2(fcfidus, i64, env, i64)
DEF_HELPER_2(fctid, i64, env, i64)
DEF_HELPER_2(fctidu, i64, env, i64)
DEF_HELPER_2(fctidz, i64, env, i64)
DEF_HELPER_2(fctiduz, i64, env, i64)
#endif
DEF_HELPER_2(frsp, i64, env, i64)
DEF_HELPER_2(frin, i64, env, i64)
DEF_HELPER_2(friz, i64, env, i64)
DEF_HELPER_2(frip, i64, env, i64)
DEF_HELPER_2(frim, i64, env, i64)

DEF_HELPER_3(fadd, i64, env, i64, i64)
DEF_HELPER_3(fsub, i64, env, i64, i64)
DEF_HELPER_3(fmul, i64, env, i64, i64)
DEF_HELPER_3(fdiv, i64, env, i64, i64)
DEF_HELPER_4(fmadd, i64, env, i64, i64, i64)
DEF_HELPER_4(fmsub, i64, env, i64, i64, i64)
DEF_HELPER_4(fnmadd, i64, env, i64, i64, i64)
DEF_HELPER_4(fnmsub, i64, env, i64, i64, i64)
DEF_HELPER_2(fsqrt, i64, env, i64)
DEF_HELPER_2(fre, i64, env, i64)
DEF_HELPER_2(fres, i64, env, i64)
DEF_HELPER_2(frsqrte, i64, env, i64)
DEF_HELPER_4(fsel, i64, env, i64, i64, i64)

DEF_HELPER_FLAGS_2(ftdiv, TCG_CALL_NO_RWG_SE, i32, i64, i64)
DEF_HELPER_FLAGS_1(ftsqrt, TCG_CALL_NO_RWG_SE, i32, i64)

#define dh_alias_avr ptr
#define dh_ctype_avr ppc_avr_t *
#define dh_is_signed_avr dh_is_signed_ptr

DEF_HELPER_3(vaddubm, void, avr, avr, avr)
DEF_HELPER_3(vadduhm, void, avr, avr, avr)
DEF_HELPER_3(vadduwm, void, avr, avr, avr)
DEF_HELPER_3(vaddudm, void, avr, avr, avr)
DEF_HELPER_3(vsububm, void, avr, avr, avr)
DEF_HELPER_3(vsubuhm, void, avr, avr, avr)
DEF_HELPER_3(vsubuwm, void, avr, avr, avr)
DEF_HELPER_3(vsubudm, void, avr, avr, avr)
DEF_HELPER_3(vavgub, void, avr, avr, avr)
DEF_HELPER_3(vavguh, void, avr, avr, avr)
DEF_HELPER_3(vavguw, void, avr, avr, avr)
DEF_HELPER_3(vavgsb, void, avr, avr, avr)
DEF_HELPER_3(vavgsh, void, avr, avr, avr)
DEF_HELPER_3(vavgsw, void, avr, avr, avr)
DEF_HELPER_3(vminsb, void, avr, avr, avr)
DEF_HELPER_3(vminsh, void, avr, avr, avr)
DEF_HELPER_3(vminsw, void, avr, avr, avr)
DEF_HELPER_3(vminsd, void, avr, avr, avr)
DEF_HELPER_3(vmaxsb, void, avr, avr, avr)
DEF_HELPER_3(vmaxsh, void, avr, avr, avr)
DEF_HELPER_3(vmaxsw, void, avr, avr, avr)
DEF_HELPER_3(vmaxsd, void, avr, avr, avr)
DEF_HELPER_3(vminub, void, avr, avr, avr)
DEF_HELPER_3(vminuh, void, avr, avr, avr)
DEF_HELPER_3(vminuw, void, avr, avr, avr)
DEF_HELPER_3(vminud, void, avr, avr, avr)
DEF_HELPER_3(vmaxub, void, avr, avr, avr)
DEF_HELPER_3(vmaxuh, void, avr, avr, avr)
DEF_HELPER_3(vmaxuw, void, avr, avr, avr)
DEF_HELPER_3(vmaxud, void, avr, avr, avr)
DEF_HELPER_4(vcmpequb, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpequh, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpequw, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpequd, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtub, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtuh, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtuw, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtud, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtsb, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtsh, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtsw, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtsd, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpeqfp, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgefp, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtfp, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpbfp, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpequb_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpequh_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpequw_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpequd_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtub_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtuh_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtuw_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtud_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtsb_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtsh_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtsw_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtsd_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpeqfp_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgefp_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpgtfp_dot, void, env, avr, avr, avr)
DEF_HELPER_4(vcmpbfp_dot, void, env, avr, avr, avr)
DEF_HELPER_3(vmrglb, void, avr, avr, avr)
DEF_HELPER_3(vmrglh, void, avr, avr, avr)
DEF_HELPER_3(vmrglw, void, avr, avr, avr)
DEF_HELPER_3(vmrghb, void, avr, avr, avr)
DEF_HELPER_3(vmrghh, void, avr, avr, avr)
DEF_HELPER_3(vmrghw, void, avr, avr, avr)
DEF_HELPER_3(vmulesb, void, avr, avr, avr)
DEF_HELPER_3(vmulesh, void, avr, avr, avr)
DEF_HELPER_3(vmulesw, void, avr, avr, avr)
DEF_HELPER_3(vmuleub, void, avr, avr, avr)
DEF_HELPER_3(vmuleuh, void, avr, avr, avr)
DEF_HELPER_3(vmuleuw, void, avr, avr, avr)
DEF_HELPER_3(vmulosb, void, avr, avr, avr)
DEF_HELPER_3(vmulosh, void, avr, avr, avr)
DEF_HELPER_3(vmulosw, void, avr, avr, avr)
DEF_HELPER_3(vmuloub, void, avr, avr, avr)
DEF_HELPER_3(vmulouh, void, avr, avr, avr)
DEF_HELPER_3(vmulouw, void, avr, avr, avr)
DEF_HELPER_3(vmuluwm, void, avr, avr, avr)
DEF_HELPER_3(vsrab, void, avr, avr, avr)
DEF_HELPER_3(vsrah, void, avr, avr, avr)
DEF_HELPER_3(vsraw, void, avr, avr, avr)
DEF_HELPER_3(vsrad, void, avr, avr, avr)
DEF_HELPER_3(vsrb, void, avr, avr, avr)
DEF_HELPER_3(vsrh, void, avr, avr, avr)
DEF_HELPER_3(vsrw, void, avr, avr, avr)
DEF_HELPER_3(vsrd, void, avr, avr, avr)
DEF_HELPER_3(vslb, void, avr, avr, avr)
DEF_HELPER_3(vslh, void, avr, avr, avr)
DEF_HELPER_3(vslw, void, avr, avr, avr)
DEF_HELPER_3(vsld, void, avr, avr, avr)
DEF_HELPER_3(vslo, void, avr, avr, avr)
DEF_HELPER_3(vsro, void, avr, avr, avr)
DEF_HELPER_3(vaddcuw, void, avr, avr, avr)
DEF_HELPER_3(vsubcuw, void, avr, avr, avr)
DEF_HELPER_2(lvsl, void, avr, tl)
DEF_HELPER_2(lvsr, void, avr, tl)
DEF_HELPER_4(vaddsbs, void, env, avr, avr, avr)
DEF_HELPER_4(vaddshs, void, env, avr, avr, avr)
DEF_HELPER_4(vaddsws, void, env, avr, avr, avr)
DEF_HELPER_4(vsubsbs, void, env, avr, avr, avr)
DEF_HELPER_4(vsubshs, void, env, avr, avr, avr)
DEF_HELPER_4(vsubsws, void, env, avr, avr, avr)
DEF_HELPER_4(vaddubs, void, env, avr, avr, avr)
DEF_HELPER_4(vadduhs, void, env, avr, avr, avr)
DEF_HELPER_4(vadduws, void, env, avr, avr, avr)
DEF_HELPER_4(vsububs, void, env, avr, avr, avr)
DEF_HELPER_4(vsubuhs, void, env, avr, avr, avr)
DEF_HELPER_4(vsubuws, void, env, avr, avr, avr)
DEF_HELPER_3(vadduqm, void, avr, avr, avr)
DEF_HELPER_4(vaddecuq, void, avr, avr, avr, avr)
DEF_HELPER_4(vaddeuqm, void, avr, avr, avr, avr)
DEF_HELPER_3(vaddcuq, void, avr, avr, avr)
DEF_HELPER_3(vsubuqm, void, avr, avr, avr)
DEF_HELPER_4(vsubecuq, void, avr, avr, avr, avr)
DEF_HELPER_4(vsubeuqm, void, avr, avr, avr, avr)
DEF_HELPER_3(vsubcuq, void, avr, avr, avr)
DEF_HELPER_3(vrlb, void, avr, avr, avr)
DEF_HELPER_3(vrlh, void, avr, avr, avr)
DEF_HELPER_3(vrlw, void, avr, avr, avr)
DEF_HELPER_3(vrld, void, avr, avr, avr)
DEF_HELPER_3(vsl, void, avr, avr, avr)
DEF_HELPER_3(vsr, void, avr, avr, avr)
DEF_HELPER_4(vsldoi, void, avr, avr, avr, i32)
DEF_HELPER_2(vspltisb, void, avr, i32)
DEF_HELPER_2(vspltish, void, avr, i32)
DEF_HELPER_2(vspltisw, void, avr, i32)
DEF_HELPER_3(vspltb, void, avr, avr, i32)
DEF_HELPER_3(vsplth, void, avr, avr, i32)
DEF_HELPER_3(vspltw, void, avr, avr, i32)
DEF_HELPER_2(vupkhpx, void, avr, avr)
DEF_HELPER_2(vupklpx, void, avr, avr)
DEF_HELPER_2(vupkhsb, void, avr, avr)
DEF_HELPER_2(vupkhsh, void, avr, avr)
DEF_HELPER_2(vupkhsw, void, avr, avr)
DEF_HELPER_2(vupklsb, void, avr, avr)
DEF_HELPER_2(vupklsh, void, avr, avr)
DEF_HELPER_2(vupklsw, void, avr, avr)
DEF_HELPER_5(vmsumubm, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vmsummbm, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vsel, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vperm, void, env, avr, avr, avr, avr)
DEF_HELPER_4(vpkshss, void, env, avr, avr, avr)
DEF_HELPER_4(vpkshus, void, env, avr, avr, avr)
DEF_HELPER_4(vpkswss, void, env, avr, avr, avr)
DEF_HELPER_4(vpkswus, void, env, avr, avr, avr)
DEF_HELPER_4(vpksdss, void, env, avr, avr, avr)
DEF_HELPER_4(vpksdus, void, env, avr, avr, avr)
DEF_HELPER_4(vpkuhus, void, env, avr, avr, avr)
DEF_HELPER_4(vpkuwus, void, env, avr, avr, avr)
DEF_HELPER_4(vpkudus, void, env, avr, avr, avr)
DEF_HELPER_4(vpkuhum, void, env, avr, avr, avr)
DEF_HELPER_4(vpkuwum, void, env, avr, avr, avr)
DEF_HELPER_4(vpkudum, void, env, avr, avr, avr)
DEF_HELPER_3(vpkpx, void, avr, avr, avr)
DEF_HELPER_5(vmhaddshs, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vmhraddshs, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vmsumuhm, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vmsumuhs, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vmsumshm, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vmsumshs, void, env, avr, avr, avr, avr)
DEF_HELPER_4(vmladduhm, void, avr, avr, avr, avr)
DEF_HELPER_2(mtvscr, void, env, avr)
DEF_HELPER_3(lvebx, void, env, avr, tl)
DEF_HELPER_3(lvehx, void, env, avr, tl)
DEF_HELPER_3(lvewx, void, env, avr, tl)
DEF_HELPER_3(stvebx, void, env, avr, tl)
DEF_HELPER_3(stvehx, void, env, avr, tl)
DEF_HELPER_3(stvewx, void, env, avr, tl)
DEF_HELPER_4(vsumsws, void, env, avr, avr, avr)
DEF_HELPER_4(vsum2sws, void, env, avr, avr, avr)
DEF_HELPER_4(vsum4sbs, void, env, avr, avr, avr)
DEF_HELPER_4(vsum4shs, void, env, avr, avr, avr)
DEF_HELPER_4(vsum4ubs, void, env, avr, avr, avr)
DEF_HELPER_4(vaddfp, void, env, avr, avr, avr)
DEF_HELPER_4(vsubfp, void, env, avr, avr, avr)
DEF_HELPER_4(vmaxfp, void, env, avr, avr, avr)
DEF_HELPER_4(vminfp, void, env, avr, avr, avr)
DEF_HELPER_3(vrefp, void, env, avr, avr)
DEF_HELPER_3(vrsqrtefp, void, env, avr, avr)
DEF_HELPER_5(vmaddfp, void, env, avr, avr, avr, avr)
DEF_HELPER_5(vnmsubfp, void, env, avr, avr, avr, avr)
DEF_HELPER_3(vexptefp, void, env, avr, avr)
DEF_HELPER_3(vlogefp, void, env, avr, avr)
DEF_HELPER_3(vrfim, void, env, avr, avr)
DEF_HELPER_3(vrfin, void, env, avr, avr)
DEF_HELPER_3(vrfip, void, env, avr, avr)
DEF_HELPER_3(vrfiz, void, env, avr, avr)
DEF_HELPER_4(vcfux, void, env, avr, avr, i32)
DEF_HELPER_4(vcfsx, void, env, avr, avr, i32)
DEF_HELPER_4(vctuxs, void, env, avr, avr, i32)
DEF_HELPER_4(vctsxs, void, env, avr, avr, i32)

DEF_HELPER_2(vclzb, void, avr, avr)
DEF_HELPER_2(vclzh, void, avr, avr)
DEF_HELPER_2(vclzw, void, avr, avr)
DEF_HELPER_2(vclzd, void, avr, avr)
DEF_HELPER_2(vpopcntb, void, avr, avr)
DEF_HELPER_2(vpopcnth, void, avr, avr)
DEF_HELPER_2(vpopcntw, void, avr, avr)
DEF_HELPER_2(vpopcntd, void, avr, avr)
DEF_HELPER_3(vbpermq, void, avr, avr, avr)
DEF_HELPER_2(vgbbd, void, avr, avr)
DEF_HELPER_3(vpmsumb, void, avr, avr, avr)
DEF_HELPER_3(vpmsumh, void, avr, avr, avr)
DEF_HELPER_3(vpmsumw, void, avr, avr, avr)
DEF_HELPER_3(vpmsumd, void, avr, avr, avr)

DEF_HELPER_2(vsbox, void, avr, avr)
DEF_HELPER_3(vcipher, void, avr, avr, avr)
DEF_HELPER_3(vcipherlast, void, avr, avr, avr)
DEF_HELPER_3(vncipher, void, avr, avr, avr)
DEF_HELPER_3(vncipherlast, void, avr, avr, avr)
DEF_HELPER_3(vshasigmaw, void, avr, avr, i32)
DEF_HELPER_3(vshasigmad, void, avr, avr, i32)
DEF_HELPER_4(vpermxor, void, avr, avr, avr, avr)

DEF_HELPER_4(bcdadd, i32, avr, avr, avr, i32)
DEF_HELPER_4(bcdsub, i32, avr, avr, avr, i32)

DEF_HELPER_2(xsadddp, void, env, i32)
DEF_HELPER_2(xssubdp, void, env, i32)
DEF_HELPER_2(xsmuldp, void, env, i32)
DEF_HELPER_2(xsdivdp, void, env, i32)
DEF_HELPER_2(xsredp, void, env, i32)
DEF_HELPER_2(xssqrtdp, void, env, i32)
DEF_HELPER_2(xsrsqrtedp, void, env, i32)
DEF_HELPER_2(xstdivdp, void, env, i32)
DEF_HELPER_2(xstsqrtdp, void, env, i32)
DEF_HELPER_2(xsmaddadp, void, env, i32)
DEF_HELPER_2(xsmaddmdp, void, env, i32)
DEF_HELPER_2(xsmsubadp, void, env, i32)
DEF_HELPER_2(xsmsubmdp, void, env, i32)
DEF_HELPER_2(xsnmaddadp, void, env, i32)
DEF_HELPER_2(xsnmaddmdp, void, env, i32)
DEF_HELPER_2(xsnmsubadp, void, env, i32)
DEF_HELPER_2(xsnmsubmdp, void, env, i32)
DEF_HELPER_2(xscmpodp, void, env, i32)
DEF_HELPER_2(xscmpudp, void, env, i32)
DEF_HELPER_2(xsmaxdp, void, env, i32)
DEF_HELPER_2(xsmindp, void, env, i32)
DEF_HELPER_2(xscvdpsp, void, env, i32)
DEF_HELPER_2(xscvdpspn, i64, env, i64)
DEF_HELPER_2(xscvspdp, void, env, i32)
DEF_HELPER_2(xscvspdpn, i64, env, i64)
DEF_HELPER_2(xscvdpsxds, void, env, i32)
DEF_HELPER_2(xscvdpsxws, void, env, i32)
DEF_HELPER_2(xscvdpuxds, void, env, i32)
DEF_HELPER_2(xscvdpuxws, void, env, i32)
DEF_HELPER_2(xscvsxddp, void, env, i32)
DEF_HELPER_2(xscvuxdsp, void, env, i32)
DEF_HELPER_2(xscvsxdsp, void, env, i32)
DEF_HELPER_2(xscvuxddp, void, env, i32)
DEF_HELPER_2(xsrdpi, void, env, i32)
DEF_HELPER_2(xsrdpic, void, env, i32)
DEF_HELPER_2(xsrdpim, void, env, i32)
DEF_HELPER_2(xsrdpip, void, env, i32)
DEF_HELPER_2(xsrdpiz, void, env, i32)

DEF_HELPER_2(xsaddsp, void, env, i32)
DEF_HELPER_2(xssubsp, void, env, i32)
DEF_HELPER_2(xsmulsp, void, env, i32)
DEF_HELPER_2(xsdivsp, void, env, i32)
DEF_HELPER_2(xsresp, void, env, i32)
DEF_HELPER_2(xsrsp, i64, env, i64)
DEF_HELPER_2(xssqrtsp, void, env, i32)
DEF_HELPER_2(xsrsqrtesp, void, env, i32)
DEF_HELPER_2(xsmaddasp, void, env, i32)
DEF_HELPER_2(xsmaddmsp, void, env, i32)
DEF_HELPER_2(xsmsubasp, void, env, i32)
DEF_HELPER_2(xsmsubmsp, void, env, i32)
DEF_HELPER_2(xsnmaddasp, void, env, i32)
DEF_HELPER_2(xsnmaddmsp, void, env, i32)
DEF_HELPER_2(xsnmsubasp, void, env, i32)
DEF_HELPER_2(xsnmsubmsp, void, env, i32)

DEF_HELPER_2(xvadddp, void, env, i32)
DEF_HELPER_2(xvsubdp, void, env, i32)
DEF_HELPER_2(xvmuldp, void, env, i32)
DEF_HELPER_2(xvdivdp, void, env, i32)
DEF_HELPER_2(xvredp, void, env, i32)
DEF_HELPER_2(xvsqrtdp, void, env, i32)
DEF_HELPER_2(xvrsqrtedp, void, env, i32)
DEF_HELPER_2(xvtdivdp, void, env, i32)
DEF_HELPER_2(xvtsqrtdp, void, env, i32)
DEF_HELPER_2(xvmaddadp, void, env, i32)
DEF_HELPER_2(xvmaddmdp, void, env, i32)
DEF_HELPER_2(xvmsubadp, void, env, i32)
DEF_HELPER_2(xvmsubmdp, void, env, i32)
DEF_HELPER_2(xvnmaddadp, void, env, i32)
DEF_HELPER_2(xvnmaddmdp, void, env, i32)
DEF_HELPER_2(xvnmsubadp, void, env, i32)
DEF_HELPER_2(xvnmsubmdp, void, env, i32)
DEF_HELPER_2(xvmaxdp, void, env, i32)
DEF_HELPER_2(xvmindp, void, env, i32)
DEF_HELPER_2(xvcmpeqdp, void, env, i32)
DEF_HELPER_2(xvcmpgedp, void, env, i32)
DEF_HELPER_2(xvcmpgtdp, void, env, i32)
DEF_HELPER_2(xvcvdpsp, void, env, i32)
DEF_HELPER_2(xvcvdpsxds, void, env, i32)
DEF_HELPER_2(xvcvdpsxws, void, env, i32)
DEF_HELPER_2(xvcvdpuxds, void, env, i32)
DEF_HELPER_2(xvcvdpuxws, void, env, i32)
DEF_HELPER_2(xvcvsxddp, void, env, i32)
DEF_HELPER_2(xvcvuxddp, void, env, i32)
DEF_HELPER_2(xvcvsxwdp, void, env, i32)
DEF_HELPER_2(xvcvuxwdp, void, env, i32)
DEF_HELPER_2(xvrdpi, void, env, i32)
DEF_HELPER_2(xvrdpic, void, env, i32)
DEF_HELPER_2(xvrdpim, void, env, i32)
DEF_HELPER_2(xvrdpip, void, env, i32)
DEF_HELPER_2(xvrdpiz, void, env, i32)

DEF_HELPER_2(xvaddsp, void, env, i32)
DEF_HELPER_2(xvsubsp, void, env, i32)
DEF_HELPER_2(xvmulsp, void, env, i32)
DEF_HELPER_2(xvdivsp, void, env, i32)
DEF_HELPER_2(xvresp, void, env, i32)
DEF_HELPER_2(xvsqrtsp, void, env, i32)
DEF_HELPER_2(xvrsqrtesp, void, env, i32)
DEF_HELPER_2(xvtdivsp, void, env, i32)
DEF_HELPER_2(xvtsqrtsp, void, env, i32)
DEF_HELPER_2(xvmaddasp, void, env, i32)
DEF_HELPER_2(xvmaddmsp, void, env, i32)
DEF_HELPER_2(xvmsubasp, void, env, i32)
DEF_HELPER_2(xvmsubmsp, void, env, i32)
DEF_HELPER_2(xvnmaddasp, void, env, i32)
DEF_HELPER_2(xvnmaddmsp, void, env, i32)
DEF_HELPER_2(xvnmsubasp, void, env, i32)
DEF_HELPER_2(xvnmsubmsp, void, env, i32)
DEF_HELPER_2(xvmaxsp, void, env, i32)
DEF_HELPER_2(xvminsp, void, env, i32)
DEF_HELPER_2(xvcmpeqsp, void, env, i32)
DEF_HELPER_2(xvcmpgesp, void, env, i32)
DEF_HELPER_2(xvcmpgtsp, void, env, i32)
DEF_HELPER_2(xvcvspdp, void, env, i32)
DEF_HELPER_2(xvcvspsxds, void, env, i32)
DEF_HELPER_2(xvcvspsxws, void, env, i32)
DEF_HELPER_2(xvcvspuxds, void, env, i32)
DEF_HELPER_2(xvcvspuxws, void, env, i32)
DEF_HELPER_2(xvcvsxdsp, void, env, i32)
DEF_HELPER_2(xvcvuxdsp, void, env, i32)
DEF_HELPER_2(xvcvsxwsp, void, env, i32)
DEF_HELPER_2(xvcvuxwsp, void, env, i32)
DEF_HELPER_2(xvrspi, void, env, i32)
DEF_HELPER_2(xvrspic, void, env, i32)
DEF_HELPER_2(xvrspim, void, env, i32)
DEF_HELPER_2(xvrspip, void, env, i32)
DEF_HELPER_2(xvrspiz, void, env, i32)

DEF_HELPER_2(efscfsi, i32, env, i32)
DEF_HELPER_2(efscfui, i32, env, i32)
DEF_HELPER_2(efscfuf, i32, env, i32)
DEF_HELPER_2(efscfsf, i32, env, i32)
DEF_HELPER_2(efsctsi, i32, env, i32)
DEF_HELPER_2(efsctui, i32, env, i32)
DEF_HELPER_2(efsctsiz, i32, env, i32)
DEF_HELPER_2(efsctuiz, i32, env, i32)
DEF_HELPER_2(efsctsf, i32, env, i32)
DEF_HELPER_2(efsctuf, i32, env, i32)
DEF_HELPER_2(evfscfsi, i64, env, i64)
DEF_HELPER_2(evfscfui, i64, env, i64)
DEF_HELPER_2(evfscfuf, i64, env, i64)
DEF_HELPER_2(evfscfsf, i64, env, i64)
DEF_HELPER_2(evfsctsi, i64, env, i64)
DEF_HELPER_2(evfsctui, i64, env, i64)
DEF_HELPER_2(evfsctsiz, i64, env, i64)
DEF_HELPER_2(evfsctuiz, i64, env, i64)
DEF_HELPER_2(evfsctsf, i64, env, i64)
DEF_HELPER_2(evfsctuf, i64, env, i64)
DEF_HELPER_3(efsadd, i32, env, i32, i32)
DEF_HELPER_3(efssub, i32, env, i32, i32)
DEF_HELPER_3(efsmul, i32, env, i32, i32)
DEF_HELPER_3(efsdiv, i32, env, i32, i32)
DEF_HELPER_3(evfsadd, i64, env, i64, i64)
DEF_HELPER_3(evfssub, i64, env, i64, i64)
DEF_HELPER_3(evfsmul, i64, env, i64, i64)
DEF_HELPER_3(evfsdiv, i64, env, i64, i64)
DEF_HELPER_3(efststlt, i32, env, i32, i32)
DEF_HELPER_3(efststgt, i32, env, i32, i32)
DEF_HELPER_3(efststeq, i32, env, i32, i32)
DEF_HELPER_3(efscmplt, i32, env, i32, i32)
DEF_HELPER_3(efscmpgt, i32, env, i32, i32)
DEF_HELPER_3(efscmpeq, i32, env, i32, i32)
DEF_HELPER_3(evfststlt, i32, env, i64, i64)
DEF_HELPER_3(evfststgt, i32, env, i64, i64)
DEF_HELPER_3(evfststeq, i32, env, i64, i64)
DEF_HELPER_3(evfscmplt, i32, env, i64, i64)
DEF_HELPER_3(evfscmpgt, i32, env, i64, i64)
DEF_HELPER_3(evfscmpeq, i32, env, i64, i64)
DEF_HELPER_2(efdcfsi, i64, env, i32)
DEF_HELPER_2(efdcfsid, i64, env, i64)
DEF_HELPER_2(efdcfui, i64, env, i32)
DEF_HELPER_2(efdcfuid, i64, env, i64)
DEF_HELPER_2(efdctsi, i32, env, i64)
DEF_HELPER_2(efdctui, i32, env, i64)
DEF_HELPER_2(efdctsiz, i32, env, i64)
DEF_HELPER_2(efdctsidz, i64, env, i64)
DEF_HELPER_2(efdctuiz, i32, env, i64)
DEF_HELPER_2(efdctuidz, i64, env, i64)
DEF_HELPER_2(efdcfsf, i64, env, i32)
DEF_HELPER_2(efdcfuf, i64, env, i32)
DEF_HELPER_2(efdctsf, i32, env, i64)
DEF_HELPER_2(efdctuf, i32, env, i64)
DEF_HELPER_2(efscfd, i32, env, i64)
DEF_HELPER_2(efdcfs, i64, env, i32)
DEF_HELPER_3(efdadd, i64, env, i64, i64)
DEF_HELPER_3(efdsub, i64, env, i64, i64)
DEF_HELPER_3(efdmul, i64, env, i64, i64)
DEF_HELPER_3(efddiv, i64, env, i64, i64)
DEF_HELPER_3(efdtstlt, i32, env, i64, i64)
DEF_HELPER_3(efdtstgt, i32, env, i64, i64)
DEF_HELPER_3(efdtsteq, i32, env, i64, i64)
DEF_HELPER_3(efdcmplt, i32, env, i64, i64)
DEF_HELPER_3(efdcmpgt, i32, env, i64, i64)
DEF_HELPER_3(efdcmpeq, i32, env, i64, i64)

#if !defined(CONFIG_USER_ONLY)
DEF_HELPER_2(4xx_tlbre_hi, tl, env, tl)
DEF_HELPER_2(4xx_tlbre_lo, tl, env, tl)
DEF_HELPER_3(4xx_tlbwe_hi, void, env, tl, tl)
DEF_HELPER_3(4xx_tlbwe_lo, void, env, tl, tl)
DEF_HELPER_2(4xx_tlbsx, tl, env, tl)
DEF_HELPER_3(440_tlbre, tl, env, i32, tl)
DEF_HELPER_4(440_tlbwe, void, env, i32, tl, tl)
DEF_HELPER_2(440_tlbsx, tl, env, tl)
DEF_HELPER_1(booke206_tlbre, void, env)
DEF_HELPER_1(booke206_tlbwe, void, env)
DEF_HELPER_2(booke206_tlbsx, void, env, tl)
DEF_HELPER_2(booke206_tlbivax, void, env, tl)
DEF_HELPER_2(booke206_tlbilx0, void, env, tl)
DEF_HELPER_2(booke206_tlbilx1, void, env, tl)
DEF_HELPER_2(booke206_tlbilx3, void, env, tl)
DEF_HELPER_2(booke206_tlbflush, void, env, i32)
DEF_HELPER_3(booke_setpid, void, env, i32, tl)
DEF_HELPER_2(6xx_tlbd, void, env, tl)
DEF_HELPER_2(6xx_tlbi, void, env, tl)
DEF_HELPER_2(74xx_tlbd, void, env, tl)
DEF_HELPER_2(74xx_tlbi, void, env, tl)
DEF_HELPER_FLAGS_1(tlbia, TCG_CALL_NO_RWG, void, env)
DEF_HELPER_FLAGS_2(tlbie, TCG_CALL_NO_RWG, void, env, tl)
#if defined(TARGET_PPC64)
DEF_HELPER_FLAGS_3(store_slb, TCG_CALL_NO_RWG, void, env, tl, tl)
DEF_HELPER_2(load_slb_esid, tl, env, tl)
DEF_HELPER_2(load_slb_vsid, tl, env, tl)
DEF_HELPER_FLAGS_1(slbia, TCG_CALL_NO_RWG, void, env)
DEF_HELPER_FLAGS_2(slbie, TCG_CALL_NO_RWG, void, env, tl)
#endif
DEF_HELPER_FLAGS_2(load_sr, TCG_CALL_NO_RWG, tl, env, tl)
DEF_HELPER_FLAGS_3(store_sr, TCG_CALL_NO_RWG, void, env, tl, tl)

DEF_HELPER_FLAGS_1(602_mfrom, TCG_CALL_NO_RWG_SE, tl, tl)
DEF_HELPER_1(msgsnd, void, tl)
DEF_HELPER_2(msgclr, void, env, tl)
#endif

DEF_HELPER_4(dlmzb, tl, env, tl, tl, i32)
DEF_HELPER_FLAGS_2(clcs, TCG_CALL_NO_RWG_SE, tl, env, i32)
#if !defined(CONFIG_USER_ONLY)
DEF_HELPER_2(rac, tl, env, tl)
#endif
DEF_HELPER_3(div, tl, env, tl, tl)
DEF_HELPER_3(divo, tl, env, tl, tl)
DEF_HELPER_3(divs, tl, env, tl, tl)
DEF_HELPER_3(divso, tl, env, tl, tl)

DEF_HELPER_2(load_dcr, tl, env, tl)
DEF_HELPER_3(store_dcr, void, env, tl, tl)

DEF_HELPER_2(load_dump_spr, void, env, i32)
DEF_HELPER_2(store_dump_spr, void, env, i32)
DEF_HELPER_1(load_tbl, tl, env)
DEF_HELPER_1(load_tbu, tl, env)
DEF_HELPER_1(load_atbl, tl, env)
DEF_HELPER_1(load_atbu, tl, env)
DEF_HELPER_1(load_601_rtcl, tl, env)
DEF_HELPER_1(load_601_rtcu, tl, env)
#if !defined(CONFIG_USER_ONLY)
#if defined(TARGET_PPC64)
DEF_HELPER_1(load_purr, tl, env)
#endif
DEF_HELPER_2(store_sdr1, void, env, tl)
DEF_HELPER_2(store_tbl, void, env, tl)
DEF_HELPER_2(store_tbu, void, env, tl)
DEF_HELPER_2(store_atbl, void, env, tl)
DEF_HELPER_2(store_atbu, void, env, tl)
DEF_HELPER_2(store_601_rtcl, void, env, tl)
DEF_HELPER_2(store_601_rtcu, void, env, tl)
DEF_HELPER_1(load_decr, tl, env)
DEF_HELPER_2(store_decr, void, env, tl)
DEF_HELPER_2(store_hid0_601, void, env, tl)
DEF_HELPER_3(store_403_pbr, void, env, i32, tl)
DEF_HELPER_1(load_40x_pit, tl, env)
DEF_HELPER_2(store_40x_pit, void, env, tl)
DEF_HELPER_2(store_40x_dbcr0, void, env, tl)
DEF_HELPER_2(store_40x_sler, void, env, tl)
DEF_HELPER_2(store_booke_tcr, void, env, tl)
DEF_HELPER_2(store_booke_tsr, void, env, tl)
DEF_HELPER_3(store_ibatl, void, env, i32, tl)
DEF_HELPER_3(store_ibatu, void, env, i32, tl)
DEF_HELPER_3(store_dbatl, void, env, i32, tl)
DEF_HELPER_3(store_dbatu, void, env, i32, tl)
DEF_HELPER_3(store_601_batl, void, env, i32, tl)
DEF_HELPER_3(store_601_batu, void, env, i32, tl)
#endif

#define dh_alias_fprp ptr
#define dh_ctype_fprp uint64_t *
#define dh_is_signed_fprp dh_is_signed_ptr

DEF_HELPER_4(dadd, void, env, fprp, fprp, fprp)
DEF_HELPER_4(daddq, void, env, fprp, fprp, fprp)
DEF_HELPER_4(dsub, void, env, fprp, fprp, fprp)
DEF_HELPER_4(dsubq, void, env, fprp, fprp, fprp)
