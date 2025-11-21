//////////////////////////////////////
//Project:   LT2101
//Filename:  Audio.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _AUDIO_H
#define _AUDIO_H

#include "LtType.h"

extern void Drv_Audio_Init(void);
extern void Drv_Audio_OutEn(IN u8 ucOpt);
extern void Drv_Audio_HdmiNctsValueSet(u8 IsHdmi21);
extern u8 Drv_Audio_FsValStbCheck(void);
#if TX_PORT_SIGN == DP_PORT
extern void Drv_Audio_MuteCheck(u8 ucAudioMuteEn);
#endif
extern void Drv_AudioSdm_SwEn(void);
extern u8 Drv_Audio_StatusCheck(void);
extern void Drv_Audio_AcrLogicRst(void);
extern void Drv_Audio_IisHbrSet(u8 IsHbr);
extern void Drv_Audio_TdmOutInit(void);
#endif
