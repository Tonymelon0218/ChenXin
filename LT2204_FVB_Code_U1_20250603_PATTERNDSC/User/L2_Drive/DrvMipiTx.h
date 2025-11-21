//////////////////////////////////////
//Project:   LT2204
//Filename:  DrvMipi.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DRVMIPITX_H
#define _DRVMIPITX_H

#include "LtType.h"
#include "DrvLmTxCommon.h"

#define NEGITVE         0
#define POSITIVE        1


#if TX_PORT_SIGN == MIPI_PORT
extern u8 Drv_mipiTx_GetHsRqstPre();
extern u8 Drv_MipiTx_GetHsTrail();

extern void Drv_MipiTx_VideoSet(u8 b1Opt);
extern u8 Drv_MipiTx_PllCali();

extern void Drv_MipiTx_PllSet(u32 ulPhyClk);

extern void Drv_MipiTx_PhyTimingParaSet(u32 ulMipiDataRate, u8 b1MipiClockburst, u8 ucPhySel, u8 ucDphyCsi8Lane);
extern void Drv_MipiTx_DPhySkewCali();
extern void Drv_MipiTx_DPhyClkHsTrig();

extern void Drv_MipiTx_TimingSet(IN StructTiming *pstVidTiming);
extern void Drv_MipiTx_InHSyncPol_Sel(IN u8 b1SyncPol);
extern void Drv_MipiTx_InVSyncPol_Sel(IN u8 b1SyncPol);
extern u32  Drv_MipiTx_GetMipiInClk();
extern void Drv_MipiTx_Hss_Set(IN u16 usVal);
extern u16 Drv_MipiTx_Hss_Get();
extern u16 Drv_MipiTx_FSMHact_Get();
extern void Drv_MipiTx_FifoDelay_Set(IN u16 rddly);
extern void Drv_MipiTx_PhySet(u8 ucP0En,u8 ucP1En,u8 ucP2En,u8 ucP3En);
extern void Drv_MipiTx_LaneSwap();
extern void Drv_MipiTx_PortSwap(u8 PortNum);
extern void Drv_MipiTx_PortNumSet(u8 ucPortNum);
extern void Drv_MipiTx_LaneNumSet(u8 ucLaneNum);
extern void Drv_MipiTx_CPhyEn(u8 ucEn);
extern void Drv_MipiTx_EotpSet(u8 ucEotpSet);

extern void Drv_MipiTx_DPhyClkDataSet();
extern void Drv_MipiTx_DPhyClkModeSet(u8 ub1ClkMode);
extern void Drv_MipiTx_DPhyCSI8LaneEn(IN u8 ucEn);
extern void Drv_MipiTx_PhyModeSet(u8 ucTxPhySel);
extern void Drv_MipiTx_LmtxModeSet(u8 ucTxPhySel);
extern void Drv_MipiTx_LmtxSrcSet();
extern void Drv_MipiTx_LmtxInputDataSet();
extern void Drv_MipiTx_LmtxSramInputSet();
extern void Drv_MipiTx_3DModeSet(u8 uc3DMode);
extern void Drv_MipiTx_FrameCntSet(u8 ucFrameCntSet);

extern void Drv_MipiTx_DataTypeSet(u8 ucDataType, u8 ucBppAndFmtVal);
extern void Drv_MipiTx_CSIFeSoftwareSendInit();
extern void Drv_MipiTx_CSIFeSoftwareSend();
extern void Drv_MipiTx_DSIVideoModeSet(u8 b1DSIVideoMode);
extern void Drv_MipiTx_HssLP_En(u8 ucIsEn);
extern void Drv_MipiTx_HsCmd_En(u8 ucIsEn);
extern u8 Drv_MipiTx_VideoReadyDetect();
extern void Drv_MipiTx_EnableControl(void);
extern void Drv_MipiTx_Rst(u8 IsEn);
extern void Drv_MipiTx_WordCnt_Set(u8 IsSoftMode ,u16 WordCnt,u8 PortCnt);
extern void Drv_MipiTx_Dsc_Split(u16 Hactive,u8 PortCnt);
#endif

#endif

