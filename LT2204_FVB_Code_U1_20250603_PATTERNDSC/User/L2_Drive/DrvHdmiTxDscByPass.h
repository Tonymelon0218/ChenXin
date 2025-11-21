/******************************************************************************
  * @project: LT2204
  * @file: DrvDscEnc.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.31
/******************************************************************************/
#ifndef _DRV_HDMITX_DSCBY_H
#define _DRV_HDMITX_DSCBY_H

#include "LtType.h"

#if TX_PORT_SIGN == HDMI_PORT

#if HDMITX_DSC_BYPASS_SUPPORT == ENABLED


extern void Drv_HdmiTxDscBy_Init(void);
extern void Drv_HdmiTxDscBy_PktSet(void);


#endif


#endif


#endif

