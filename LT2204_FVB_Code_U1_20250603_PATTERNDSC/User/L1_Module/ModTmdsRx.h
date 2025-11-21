/******************************************************************************
  * @project: LT2204
  * @file: FrlRx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.06.27
/******************************************************************************/
#ifndef _TMDS_RX_H
#define _TMDS_RX_H

#include "LtType.h"

#if RX_PORT_SIGN == HDMI_PORT

extern StructSleepInfo g_stSleep;

extern void Mode_Sleep_HdmiRxPowerdown(u8 b1PowerDownEn);
extern void Mode_Sleep_DpTxPowerdown(u8 b1PowerDownEn);
extern void Mod_Sleep_TmdsNoVideoDet(void);
extern void Mod_Sleep_TmdsPowerOn(void);
extern void Mod_Sleep_FrlPowerOn(void);

extern void Mod_Sleep_PowerDownSet(u8 b1IsPowerDown);
#endif

#endif
