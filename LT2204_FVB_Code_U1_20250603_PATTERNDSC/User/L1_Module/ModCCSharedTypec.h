//////////////////////////////////////
//Project:   LT2101
//Filename:  I2CMast.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CHIPTXTYPEC_H
#define _CHIPTXTYPEC_H
#include "LtType.h"
#include "ModCC1Typec.h"
#include "ModCC2Typec.h"
#if ((TYPECRX_EN == ENABLED)||(TYPECTX_EN == ENABLED))
//extern void Mod_CCPortRequestMsg_Cal(u8 IN *pucMessage,u8 IN ucMismatch_Chunked_EN,u8 OUT *pucRequestMsg,u8 IN ucCC_Ver);
extern void Mod_CCPortRequestMsg_Cal(StructCcMsg *pCCPortMSG ,u8 ucMismatch_EN,u8 CCportPDO);
extern void Mod_CCPortToPointedPdo(StructCcMsg *pCCPortMSG,u8 ucDataLength, StructCcStatus *pCCPortState); //SOURCE CAP FOR THE SOURCE

extern void Mod_CCPortSaveDataToTmp(StructCcMsg *pCCPortMSG,ucDataLength);
#endif
#endif
