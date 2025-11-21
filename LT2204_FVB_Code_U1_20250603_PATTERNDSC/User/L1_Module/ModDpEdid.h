//////////////////////////////////////
//Project:   LT2101
//Filename:  Edid.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DP_EDID_H
#define _DP_EDID_H

#include "LtType.h"

#if ((TX_PORT_SIGN == DP_PORT))

extern EDID_S g_stDpEdidInfo;
extern u8 code szEdidDefault[512];
#ifdef NVIDIA_FW_EN
extern u8 code szNvidiaEdid[512];
#endif
extern u8 szEdidData[512];
extern void Mod_Edid_HdmiModePrint(u8 *pucEDID_Data);
extern void Mod_Edid_Update(void);
#endif

#endif
