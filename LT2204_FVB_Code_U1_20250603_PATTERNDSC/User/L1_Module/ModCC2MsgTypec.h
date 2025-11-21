//////////////////////////////////////
//Project:   LT2101
//Filename:  Lt8711uxc.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"
#ifndef _CHIPTXMSGTYPEC_H
#define _CHIPTXMSGTYPEC_H

#if ((CHIP_SEL == LT8711GXE)||(CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP)||(CHIP_SEL == LT6711GXE))
//#if TYPECTX_EN == ENABLED
extern void Mod_CC2VbusOff_Det(void);
extern void Mod_CC2PowerLost_VarIni(void);
//#endif

#endif

#endif
