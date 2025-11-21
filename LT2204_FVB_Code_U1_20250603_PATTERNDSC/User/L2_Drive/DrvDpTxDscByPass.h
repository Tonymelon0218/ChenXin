/******************************************************************************
  * @project: LT2204
  * @file: DrvDscEnc.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.31
/******************************************************************************/
#ifndef _DRV_DPTX_DSCBY_H
#define _DRV_DPTX_DSCBY_H

#include "LtType.h"

#if TX_PORT_SIGN == DP_PORT

#if DPTX_DSC_BYPASS_SUPPORT == ENABLED


extern void Drv_DpTxDscBy_ClkMux(void);
extern void Drv_DpTxDscBy_PktSet(void);
extern void Drv_DpTxDscBy_Init(void);

#endif

#endif

#endif

