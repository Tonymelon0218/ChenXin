//////////////////////////////////////
//Project:   LT2101
//Filename:  Edid.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _EDIDHDMI_H
#define _EDIDHDMI_H

#include "LtType.h"

#if TX_PORT_SIGN == HDMI_PORT

extern u8 code szEdidDefault[512];
extern u8 szEdidData[MAXEDID_LENGTH];
extern u8 szEdidData_Tmp[MAXEDID_LENGTH];
extern EDID_S g_stHdmiEdidInfo;
extern void Mod_Edid_Update(u8 *pEdidData);
extern u8 Mod_Edid_ModeDet(void);
extern u8 Mod_EdidHdmi20_Get(void);
#if HDMITX_CTS_SUPPORT == ENABLED
extern u16 Mod_Edid_MaxTmdsRate(void);
#endif
extern u8 Mod_Check_Sum(u8 *pucEDID_Data);
#endif
extern void Mod_HdmiEdid_Analysis(u8 *pucEDID_Data);
#endif
