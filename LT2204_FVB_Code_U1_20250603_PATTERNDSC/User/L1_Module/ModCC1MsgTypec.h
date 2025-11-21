//////////////////////////////////////
//Project:   LT2101
//Filename:  Lt8711uxc.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"
#ifndef _CHIPRXMSGTYPEC_H
#define _CHIPRXMSGTYPEC_H

#if ((CHIP_SEL == LT8711GXE)||(CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP)||(CHIP_SEL == LT6711GXE))
#if TYPECRX_EN == ENABLED
extern void Mod_CC1Pd_Interrupt(void);
extern void Mod_CC2Pd_Interrupt(void);
extern void Mod_CC1PsRdy_Send(void);   
extern void Mod_CC1MsgSend_Retry(void);
extern void Mod_CC2MsgSend_Retry(void);
#endif
#endif
#endif
