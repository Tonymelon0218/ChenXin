/******************************************************************************
  * @project: LT2204
  * @file: DrvDscEnc.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.31
/******************************************************************************/
#ifndef _DRVDSCENC_H
#define _DRVDSCENC_H

#include "LtType.h"

#if TX_PORT_SIGN == HDMI_PORT

#if HDMITX_DSC_ENC_SUPPORT == ENABLED


extern void Drv_HdmiTxDscEnc_ParaInit(void);
extern void Drv_HdmiTxDscEnc_InfoGet(void);

extern void Drv_HdmiTxDscEnc_Init(void);
extern void Drv_HdmiTxDscEnc_ModuleEnable(void);
extern void Drv_HdmiTxDscEnc_DoduleDisable(void);

extern u8 Drv_HdmiTxDscEnc_ColorDepthGet(void);
extern u8 Drv_HdmiTxDscEnc_ColorSpaceGet(void);

extern u8 Drv_HdmiTxDscEnc_SwitchGet(void);
#endif

#endif

#endif

