//////////////////////////////////////
//Project:   LT2101
//Filename:  DrvDpRx.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DRVDPRX_H
#define _DRVDPRX_H

#include "LtType.h"

#if RX_PORT_SIGN == DP_PORT

//SDP info
#define MSA_MISC0     BKF2_EB_REG
#define MSA_MISC1     BKF2_EC_REG


//#define VSC_HB0     BKF2_A8_REG
#define VSC_HB1       BKF2_A9_REG
#define VSC_HB2       BKF2_AA_REG
#define VSC_HB3       BKF2_AB_REG
//#define VSC_DB0     BKF2_AC_REG
//#define VSC_DB1     BKF2_AD_REG
//#define VSC_DB2     BKF2_AE_REG
//#define VSC_DB3     BKF2_AF_REG
//...
#define VSC_DB16      BKF2_BC_REG
#define VSC_DB17      BKF2_BD_REG
//#define VSC_DB18    BKF2_BE_REG
//#define VSC_DB19    BKF2_BF_REG
///////////////////////////////////////////////////////////////////

extern void Drv_DpRx_Dpcd_HighAddrWrite(IN u8 ucAddr15_8);
extern void Drv_DpRx_Dpcd_ValueWrite(IN u8 ucAddr7_0,IN u8 ucValue);
extern void Drv_DpRx_AuxInit(void);
extern void Drv_DpRx_AuxSwap(u8 b1SwapEn);
extern u8 Drv_DpRx_AuxDcDet(void);
#if DPRX_CDR_MODE == ANACDR
extern void Drv_DpRx_CdrSet(u8 ucLinkRate);
#else
extern void Drv_DpRx_CdrSet(u8 b1SscEnable,u8 ucLinkRate);
#endif
extern void Drv_DpRx_Cp2520KeyCodeSet(u8 b1IsCp2520ptn);
extern void Drv_DpRx_CrLockThresholdSet(u8 b1IsLock);
extern void Drv_DpRx_CdrLoopDivSet(u8 ucLinkRate);
extern void Drv_DpRx_DpcdInit(IN StructDpRx pstDpRx);
extern void Drv_DpRx_EqModeSet(u8 IsHardEq);
extern void Drv_DpRx_HpdHWIrq(void);
extern void Drv_DpRx_HpdSet(u8 b1IsHigh,u8 b1IsIrqHigh);
extern void Drv_DpRx_DigitalInit(void);
extern void Drv_DpRx_MainLink(void);
extern void Drv_DpRx_MsaPktDetEn(void);
extern void Drv_DpRx_PcrInit(void);
extern void Drv_DpRx_PhyShut(void);
extern void Drv_DpRx_RtermCal(void);
extern void Drv_DpRx_PhyInit(void);
extern u8 Drv_DpRx_DscFifoEmptyGet(void);
extern u8 Drv_DpRx_DscFifoFullGet(void);
extern void Drv_DpRx_CtleSet(u8 ucLinkRate);
extern void Drv_DpRx_PiEnable(u8 b1Enable);
extern void Drv_DpRx_PiSet(u8 ucLinkRate);
extern void Drv_DpRx_DigCdrRst(u8 b1SscEnable);
extern void Drv_DpRx_RxPllBand(u8 ucLinkRate);
extern void Drv_DpRx_RxPllCali(void);
extern void Drv_DpRx_PcrModeSet(void);
extern void Drv_DpRx_TimingFifoReset(void);
extern void Drv_DpRx_TimingHBE(void);

extern void Drv_DpRx_SdpPacketType_Set(void);
extern void Drv_DpRx_VidColorInfoGet(ColorInfo_S *pstInfo);
extern void Drv_DpRx_AudioInfoGet(AudioChlInfo_S *pstInfo);
extern void Drv_DpRx_AudioFormatSet(void);
extern void Drv_DpRx_RxTimingGet(LtTiming_S *pstTiming);
extern u8 Drv_DpRx_DscDecState(void);
extern u8 Drv_DpRx_EccErrorCheck(void);
extern u8 Drv_DpRx_DeSkewCheck(void);
extern u8 Drv_DpRx_PpsInfoCheck(void);
extern u8 Drv_DpRx_PixelStableCheck(void);
extern u8 Drv_DpRx_SscJudgeByRxFm(u8 ucLinkRate);
extern void Drv_DpRx_SyncPolSet(u8 ucOpt);
extern void Drv_DpRx_PowerOnInit(void);
extern void Drv_DpRx_SettingInit(void);
extern void Drv_DpRx_LinkClkSel(u8 uclinkClk);
extern void Drv_DpRx_DpRxChlSwap(void);
#if TYPECRX_EN == ENABLED
extern void Drv_DpRx_TypecRxChlSwap(u8 ucInputSel,StructCcStatus pUCCStatus);
#endif
extern u8 DRV_DpRx_VideoStreamFlag(void);
extern u8 Drv_DpRx_FecDecDet(void);
extern void Drv_DpRx_FecDataPathSet(u8 b1IsFecEn);
extern void Drv_DpRx_FecCtsSet(u8 ucFecErrSel);
extern void Drv_DpRx_Reset(EnumDpRxRstType ucOpt);
extern void Drv_DpRx_AnaCdrRst(u8 ucLinkRate);
extern u8 Drv_DpRxSpdVer_Get(void);
extern void Drv_DpRx_DscPpsDataChg_IntSet(IN u8 b1IsIntEn);
extern u8 Drv_DpRx_PpsDataChg(void);
extern void Drv_DpcdError_Clear(IN u8 ucI);
//extern void DRV_DpRxCdr_FreqMonitor(u8 ucLaneCnt);
extern void Drv_Dpcd270_PhyLaneSel(u8 ucPhyLane);
//extern void DRV_Timer2Cnt_Start();
extern void Drv_DpRx_FecDisclr(void);
extern u16 Drv_DpRx_FrameRate_Get(void);
extern void Drv_DpRx_SkewLock(u8 IsLock);
extern u8 Drv_DpRx_NoErrCheck(u8 ucLaneCount);
extern void Drv_DpRx_FecSoftModeSet(u8 b1IsFecEn);
extern u8 Drv_DpRx_InterlaceGet(void);
extern void Drv_DpRx_420DetectMode(u8 b1Softmode);
extern u8 Drv_DpRxPll_LockGet(void);
extern void Drv_DpRx_AcAuxTermCtrl(u8 b1IsEn);
extern void Drv_DpRx_DcAuxResCtrl(u8 b1IsEn);
extern void Drv_DpRx_PcrPllCaliCtrl(u8 b1En);
extern void Drv_DpRx_PcrPllRst(u8 b1IsRst);
extern u32 Drv_DpRx_PixFreqGet(void);
extern void Drv_DpRx_FecAbnormalDet(void);
extern u8 Drv_DpRx_PcrStableCheck(void);
extern u8 Drv_DpRx_EqModeGet(void);
extern void Drv_DpRx_HsyncPcrErrSet(StructDpRx g_stDpMsa);
extern void Drv_DpRx_VidFreqSetCheck(u8 ucOpt);
#if DPRX_ADAPTIVE_SYNC == ENABLED
extern void Drv_DpRx_AdaptiveSyncInit(void);
#endif
#endif
#endif
