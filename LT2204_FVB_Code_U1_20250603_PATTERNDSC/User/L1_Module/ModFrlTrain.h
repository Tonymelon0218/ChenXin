/******************************************************************************
  * @project: LT2204
  * @file: FrlTx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.07.20
/******************************************************************************/
#ifndef _FRLTX_H
#define _FRLTX_H

#include "LtType.h"

#if TX_PORT_SIGN == HDMI_PORT

typedef enum
{
    FRL_TRAIN_INIT_1 = 1,
    FRL_TRAIN_VER_PROC_2,
    FRL_TRAIN_FLTREADY_PROC_3,
    FRL_TRAIN_TXPLL_PROC_4,
    FRL_TRAIN_TXSET_PROC_5,
    FRL_TRAIN_FECPLL_PROC_6,
    FRL_TRAIN_PTN_PROC_7,
    FRL_TRAIN_START_PROC_8,
    FRL_TRAIN_ERROR_PROC_9,
    FRL_TRAIN_END_PROC_10,
}EnumFrlTrainingState;

typedef struct HdmiTx_FrlInfo
{
    u8 ucFrlState;
    u8 ucLaneRate;
    u8 ucLaneCnt;
    u8 ucFfeLevel;
    u8 b1Hdmi21En;
    u8 ucTrainStepNum;
    u16 usTrainTtolNum;
    u8 b1NoTimeOutEn;
    u8 szffe_level_lane[4];
}HdmiTxFrlInfo_S;

extern HdmiTxFrlInfo_S g_stFrlTxInfo;
extern void Mod_FrlTx_ParamInit(void);
extern u8 Mod_FrlTx_TrainingHdl(void);
extern u8 Mod_FrlTx_Hdmi21EnGet(void);
extern void Mod_FrlTx_SetState(u8 ucState);
extern void Mod_FrlTx_TrainFail(void);
#endif

#endif
