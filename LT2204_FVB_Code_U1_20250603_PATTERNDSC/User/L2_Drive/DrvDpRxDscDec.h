/******************************************************************************
  * @project: LT2204
  * @file: DrvDscDec.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.31
/******************************************************************************/
#ifndef _DRV_DPRX_DSCDEC_H
#define _DRV_DPRX_DSCDEC_H

#include "LtType.h"

#if RX_PORT_SIGN == DP_PORT

#if DPRX_DSC_DEC_SUPPORT == ENABLED

extern void Drv_DpRxDscDec_ParaInit(void);
extern void Drv_DpRxDscDec_RxInit(void);
extern void Drv_DpRxDscDec_Rst(void);
extern void Drv_DpRxDscDec_ModuleEnable(void);
extern void Drv_DpRxDscDec_Set(u8 ucState);
extern void Drv_DpRxDscDec_Init(void);

extern u8 Drv_DpRxDscDec_TimingGet(void);
extern u8 Drv_DpRxDscDec_DscInfoGet(void);
extern u8 Drv_DpRxDsc_SliceNum(void);

extern u8 Drv_DpRxDscDec_ColorDepthGet(void);
extern u8 Drv_DpRxDscDec_DscParaCheck(void);
extern u8 Drv_DpRxDscDec_SwitchGet(void);
extern u8 Drv_DpRxDscDec_ColorSpaceGet(void);
extern void Drv_DpRxDscDec_WordDelaySet(void);
extern void Drv_DpRxDscDec_ColorInfoGet(ColorInfo_S *pstInfo);
#endif

#endif

#endif