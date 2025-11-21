/******************************************************************************
  * @project: LT2204
  * @file: DrvDscDec.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.31
/******************************************************************************/
#ifndef _DRV_DPRX_DSCBY_H
#define _DRV_DPRX_DSCBY_H

#include "LtType.h"

#if (RX_PORT_SIGN == DP_PORT)
#if (DPRX_DSC_BYPASS_SUPPORT == ENABLED)

extern void Drv_DpRxDscBy_RxInit(void);
extern void Drv_DpRxDscBy_ParaInit(void);

extern void Drv_DpRxDscBy_TimingGet(void);
extern u8 Drv_DpRxDscBy_DscInfoGet(void);
extern void Drv_DpRxDscBy_ModuleEnable(void);
extern void Drv_DpRxDscBy_Set(u8 ucState);
extern void Drv_DpRxDscBy_Init(void);
extern void Drv_DpRxDscBy_ColorInfoGet(ColorInfo_S *pstInfo);
extern u8 Drv_DpRxDscBy_SwitchGet(void);
extern LtTiming_S g_stDpRxDscByTiming;
#endif
#endif

#endif