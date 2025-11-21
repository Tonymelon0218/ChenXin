////////////////////////////////////////
////Project:   LT2101
////Filename:  Lt8711uxc.h
////Version:   V1.0
////Copyright: Lontium
////////////////////////////////////////
#include "Include.h"
#ifndef _MODUCC1BASICTYPEC_H
#define _MODUCC1BASICTYPEC_H

#if ((CHIP_SEL == LT8711GXE)||(CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP)||(CHIP_SEL == LT6711GXE))
//extern u8 Mod_AppleDockingFlag(void);
#if ((TYPECRX_EN == ENABLED)||(TYPECTX_EN == ENABLED))
extern void Mod_CC1Msg_Send(void);
extern void Mod_CC2Msg_Send(void);
extern void Mod_CC1PdMsg_Analysis(u8 ucMsg_Type,u8 ucLength,u8 ucExt);
extern void Mod_CC2Msg_Deal(u8 ucMsg_Type,u8 ucLength,u8 ucExt);
extern void Mod_CC1SourceCapMsg_Set(void);
#if UCC_EMARK_SUPPORT == ENABLED
extern void Mod_CC1MessageSOP1_Send(void);
#endif
extern u8 Mod_CCPortMsgId_Cal(u8 ucsum);
extern void Mod_CCPortMsg_Retry(IN u8 ucCC_Port);
extern void Mod_DiscoverID_Handle(u8 IN ucPD_Ver,u8 IN *pucData,u8 IN ucReply);
extern void Mod_Cc1DrSwap_Set(void);
#endif
#endif
#endif
