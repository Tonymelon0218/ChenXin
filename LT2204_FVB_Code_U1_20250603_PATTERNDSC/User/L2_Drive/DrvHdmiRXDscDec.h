/******************************************************************************
  * @project: LT2204
  * @file: DrvDscDec.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.31
/******************************************************************************/
#ifndef _DRV_HDMIRX_DSCDEC_H
#define _DRV_HDMIRX_DSCDEC_H

#include "LtType.h"

#if RX_PORT_SIGN == HDMI_PORT

#if HDMIRX_DSC_DEC_SUPPORT == ENABLED

extern void Drv_HdmiRxDscDec_Init(void);
extern void Drv_HdmiRxDscDec_ParaInit(void);
extern void Drv_HdmiRxDscDec_RxInit(void);
extern void Drv_HdmiRxDscDec_DscPcrPllCal(void);
extern void Drv_HdmiRxDscDec_ModuleEnable(void);
extern void Drv_HdmiRxDscDec_ColorInfoGet(ColorInfo_S *pstInfo);

extern u8 Drv_HdmiRxDscDec_TimingGet(void);
extern u8 Drv_HdmiRxDscDec_DscInfoGet(void);
extern u8 Drv_HdmiRxDscDec_SwitchGet(void);

#endif

#endif

#endif