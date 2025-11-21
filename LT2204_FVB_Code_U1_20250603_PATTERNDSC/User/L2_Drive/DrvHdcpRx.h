//////////////////////////////////////
//Project:   LT2101
//Filename:  HdcpRx.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _HDCPRX_H
#define _HDCPRX_H
#include "LtType.h"

extern void Drv_HdcpRx_Enable(IN u8 ucOpt);

extern u8 Drv_HdcpRx_VerGet(void);

extern void Drv_HdcpRx_StateClear(void);
extern void Drv_HdcpRx_SoftAvmuteEn(u8 ucOpt);
extern void Drv_HdcpRx_ReauthHdcpStateClr(void);
extern u8 Drv_Hdcp13_IntGet(void);
extern u8 Drv_Hdcp2X_IntGet(void);
#endif
