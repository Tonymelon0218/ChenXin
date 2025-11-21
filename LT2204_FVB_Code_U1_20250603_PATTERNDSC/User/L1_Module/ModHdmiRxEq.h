/******************************************************************************
  * @project: LT2204
  * @file: FrlRx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.06.27
/******************************************************************************/
#ifndef _HDMIRX_AUTO_EQ_H
#define _HDMIRX_AUTO_EQ_H

#include "LtType.h"

extern void Mod_HdmiRxEq_EqCheckInPreDet(void);
extern void Mod_HdmiRxEq_Init(void);
extern void Mod_HdmiRxEq_Frl_Set(void);
extern void Mod_HdmiRxEq_Tmds_Set(void);
extern u8 Mod_HdmiRxEq_Frl_StateGet(u8 ucLane);
extern u8 Mod_HdmiRxEq_Tmds_StateGet(u8 ucLane);
#endif
