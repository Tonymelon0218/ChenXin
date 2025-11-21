/******************************************************************************
  * @project: LT2204
  * @file: DrvDscEnc.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.31
/******************************************************************************/
#ifndef _DRV_DPTX_DSCENC_H
#define _DRV_DPTX_DSCENC_H

#include "LtType.h"

#if TX_PORT_SIGN == DP_PORT
#if DPTX_DSC_ENC_SUPPORT == ENABLED

extern void Drv_DpTxDscEnc_ParaInit(void);
extern void Drv_DpTxDscEnc_InfoGet(void);

extern void Drv_DpTxDscEnc_ModuleEnable(void);
extern void Drv_DpTxDscEnc_DoduleDisable(void);
extern void Drv_DpTxDscEnc_Init(void);

extern void Drv_DpTxDscEnc_TxPktSet(void);
extern u8 Drv_DpTxDscEnc_SwitchGet(void);
extern u16 Drv_DpTxDscEnc_BppGet(void);
#endif

#endif
#endif
