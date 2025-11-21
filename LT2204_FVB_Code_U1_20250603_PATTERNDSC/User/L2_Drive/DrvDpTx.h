/******************************************************************************
  * @project: LT2204
  * @file: DrvDpTx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.30
/******************************************************************************/

#ifndef _DRVDPTX_H
#define _DRVDPTX_H

#include "LtType.h"

#if TX_PORT_SIGN == DP_PORT

extern void Drv_DpTx_PowerDown(void);
extern void Drv_DpTx_PowerOnInit(void);
extern void Drv_DpTx_SettingInit(void);
extern void Drv_DpTx_AuxInit(void);
extern void Drv_DpTx_RtermCali(void);
extern void Drv_DpTx_PhyInit(void);
extern void Drv_DpTx_MainLinkInit(u8 ucOutputSel);
extern void Drv_DpTx_DigitalInit(void);
extern void Drv_DpTx_IrqDet(bool b1IrqEn);
extern void Drv_DpTx_TxPllInit(void);
extern void Drv_DpTx_TxPllCali(u8 ucLinkRate);
extern void Drv_DpTx_SscSet(u8 ucLinkRate);
extern void Drv_DpTx_LaneSwingSet(bool b1IsDpOrTypec, u8 ucStd, u8 ucLane);
extern void Drv_DpTx_SwingAdjust(u8 ucStd, u8 ucLane);
extern void Drv_DpTx_TrainFirstSet(void);
extern void Drv_DpTx_TrainSecSetForTps4(void);
extern void Drv_DpTx_TrainSecSetForTps3(void);
extern void Drv_DpTx_TrainSecSetForTps2(void);
extern void Drv_DpTx_TrainPtnSet(void);
extern void Drv_DpTx_TrainFailSet(void);
extern void Drv_DpTx_DoblyHdrEnable(u8 TypecAppleFlag );
extern void Drv_DpTx_StaticHdrEnable(void);
extern void Drv_DpTx_StaticHdrDisable(void);
extern void Drv_DpTx_DynamicHdrEnable(void);
extern void Drv_DpTx_ScrambleEn(u8 ucOpt);
extern void Drv_DpTx_FecPllCal(void);
extern void Drv_DpTx_FecEn(u8 ucOpt);
extern void Drv_DpTx_VbidNoVideoStreamFlag(u8 ucOpt);
extern void Drv_DpTx_VidOutEn(u8 b1VidOut);
extern u8 Drv_DpTx_VdChkStableJudge(void);
extern void Drv_DpTx_HpdClear(void);
extern void Drv_DpTx_Reset(void);
extern void Drv_DpTx_DivLinkClkSet(void);
extern void Drv_DpTx_EdpScrambleSet(u8 IsEdpScramble);
extern void Drv_DpTx_FecPllInit(void);
extern u8 Drv_DpTx_PllStableCheck(void);
extern u8 Drv_DpTx_FecPllStableCheck(void);
//extern void Drv_DpTx_MvidCal(void);
extern void Drv_DpTx_IrqTrig(void);
extern void Drv_DpTx_TypeCOutSet(void);
extern void Drv_DpTx_PhyDis(u8 ucOpt);
#endif
#endif
