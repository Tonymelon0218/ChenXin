//////////////////////////////////////
//Project:   LT2204
//Filename:  Drvlvds.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DRVLVDSTX_H
#define _DRVLVDSTX_H

#include "LtType.h"
#include "DrvLmTxCommon.h"

#if TX_PORT_SIGN == LVDS_PORT


//ucVideoOpt¡êo0-video disable, 1:video able
extern void Drv_LvdxTx_VideoSet(u8 ucVideoOpt);
extern void Drv_LvdsTx_PllSrcSet();
extern void Drv_LvdsTx_PllDivSet(u32 ulInputClk, u8 ucLvdsPortcnt , u8 ucLvdsDatamap);
extern u8   Drv_LvdsTx_PllCali();
extern void Drv_LvdsTx_InVSyncPol_Sel(u8 b1SyncPol);
extern void Drv_LvdsTx_InHSyncPol_Sel(u8 b1SyncPol);

extern void Drv_LvdsTx_HtotalAdjust(StructTiming *stVideoTiming, u8 ucLvdsDatamap, u8 ucPort);
extern void Drv_LvdsTx_HactiveAdjust(StructTiming *stVideoTiming, u8 ucLvdsDatamap,u8 ucPort);

extern void Drv_LvdsTx_TimingSet(StructTiming *stVideoTiming,u8 ucLvds3d  ,u8 ucLvdsDatamap);
extern void Drv_LvdsTx_PhyPortSet(u8 ucP0En, u8 ucP1En, u8 ucP2En, u8 ucP3En);
extern void Drv_LvdsTx_PortSwap(u8 PortNum);
extern void Drv_LvdsTx_LaneSwap();
extern void Drv_LvdsTx_PortSet(u8 ucPortNum);
extern void Drv_LvdsTx_LaneNumSet(u8 ucLaneNum);

extern void Drv_LvdsTx_SscSet(u8 b1LvdsTxSscEn);
extern void Drv_LvdsTx_SyncCodeVblankSet(u8 ucSCBlankSendEn);
extern void Drv_LvdsTx_SCSendMethodSel(u8 ucLvdsSCSendIndependent);
extern void Drv_LvdsTx_PIFormatSet(u8 ucLvdsTxVidFmt);
extern void Drv_LvdsTx_3DModeSet(u8 ucLvdsTx3DMode);
extern void Drv_LvdsTx_DataMapSet(u8 ucLvdsTxDataMap);
extern void Drv_LvdsTx_DEModeSet(u8 b1LVDSTXDEMode); 
extern void Drv_LvdsTx_Sony422_DataSet(u8 ucSonyYuvDataSel);

#endif

#endif

