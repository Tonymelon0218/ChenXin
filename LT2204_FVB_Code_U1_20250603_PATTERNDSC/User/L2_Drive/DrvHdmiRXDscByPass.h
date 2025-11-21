/******************************************************************************
  * @project: LT2204
  * @file: DrvHdmiRxDscBypass.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.31
/******************************************************************************/
#ifndef _DRV_HDMIRX_DSCBY_H
#define _DRV_HDMIRX_DSCBY_H
#if (RX_PORT_SIGN == HDMI_PORT)
#if ((HDMIRX_DSC_BYPASS_SUPPORT == ENABLED)||(HDMIRX_DSC_DEC_SUPPORT == ENABLED))

#include "LtType.h"
extern DscDecInfo_S g_stHdmiRxDscByInfo;
extern LtTiming_S g_stHdmiRxDscByTiming;
extern void Drv_HdmiRxDscBy_ParaInit(void);
extern void Drv_HdmiRxDscBy_RxInit(void);

extern void Drv_HdmiRxDscBy_TimingGet(void);
extern void Drv_HdmiRxDscBy_DscInfoGet(void);

extern void Drv_HdmiRxDscBy_Init(void);
extern void Drv_HdmiRxDscBy_ModuleEnable(void);
extern void Drv_HdmiRxDscBy_ColorInfoGet(ColorInfo_S *pstInfo);

extern u8 Drv_HdmiRxDscBy_SwitchGet(void);
extern u16 Drv_HdmiRxDscBy_BppGet(void);

extern void Drv_HdmiRxDscBy_InfoDisplay(void);
#endif
#endif
#endif