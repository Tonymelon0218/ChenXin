/******************************************************************************
  * @project: LT2204
  * @file: FrlRx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.06.27
/******************************************************************************/
#ifndef _FRLRX_H
#define _FRLRX_H

#include "LtType.h"

#if RX_PORT_SIGN == HDMI_PORT

typedef struct HdmiRx_FrlInfo
{
    u8 ucPtnType;
    u8 b1SrcReadPtnDone;
    u8 b1IsTrainDone;
    u8 b1IsTrainFail;

    u8 ucFrlRate;
    u8 ucLaneCnt;
    u8 ucMaxffeLvl;
    u8 ucffeRequestNum;

    u8 b1EqChkInPreDeal;
    u8 ucEqScanCnt;
}HdmiRxFrlInfo_S;


extern void Mod_FrlRx_FrlTask(void);
extern void Mod_FrlRx_VarInit(void);
extern void Mod_FrlRx_FrlStartCheck(void);

extern u8 Mod_FrlRx_TrainDoneChk(void);
extern u8 Mod_FrlRx_TrainFailChk(void);

extern u8 Mod_FrlRx_RateChangChk(void);
 
extern HdmiRxFrlInfo_S g_stFrlRxInfo;
#endif

#endif
