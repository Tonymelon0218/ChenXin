//////////////////////////////////////
//Project:   LT2101
//Filename:  AuxMsg.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _AUXMSG_H
#define _AUXMSG_H

#include "LtType.h"

#if RX_PORT_SIGN == DP_PORT

//Native Aux
#define    CMD_DPCDW            0x80
#define    CMD_DPCDR            0x90

//IIC-Over-Aux
#define    CMD_I2CLW           0x00
#define    CMD_I2CS            0x10
#define    CMD_I2CLD           0x20
#define    CMD_I2CW            0x40
#define    CMD_I2CR            0x50
#define    CMD_I2CD            0x60

#define    AUXACK              0x00
#define    AUXNACK             0x10
#define    AUXDEFER            0x20
#define    I2CNACK             0x40
#define    I2CDEFER            0x80

#define    DPCD300_IEEE_OUI_LEN     0x03
#define    DPCD300_DEV_ID_LEN       0x06
#define    DPCD300_ALL_LEN          0x0F

typedef struct Aux
{
    u8 b1Cr_Lock;
    u8 b1Train_Done;
    u8 b1AuxDone;
    #if DPRX_CDR_MODE != ANACDR
    u8 b1Ssc_Dpcd107;
    u8 b1Dpcd107_WrFlag;
    #endif
    u8 ucEdid_Block_Offset;
    u8 b1IsSwingLvl;
    u8 b1MstFlag;
    u8 ucLink_Rate;
    u8 ucLink_Count;
    u8 ucTps_Pattern;
    u8 ucTps_Save_Pattern;
    u8 ucDpcd202;
    u8 ucDpcd203;
    u8 ucDpcd204;
    u8 ucDpcd270;
    u8 FecFlag;
    u8 DscFlag;
    u8 szRxAddress[3];
    u8 szRxData[16];
    u8 szRxSendData[16];
    u8 b1IsLossSymbol;
    u16 usEdid_Offset;
	u8 szDpcd30XH[DPCD300_ALL_LEN];
//	u16 usDelayCnt;
	#if DPRX_ADAPTIVE_SYNC == ENABLED
	u8 ucMsaIgnoreEn;
    #endif
} AuxStatus_S;

extern IDATA AuxStatus_S g_stAuxStatus;

extern void Mod_Aux_DealLossLock(void);
extern void Mod_DpRx_AuxTask(void);
extern u8 Mod_Aux_GetTrainDoneStatus(void);
extern u8 Mod_Aux_GetRetrainStatus(void);

extern u8 Mod_Aux_LinkCntGet(void);
extern u8 Mod_Aux_AdaptiveSyncStateGet(void);

#endif

#endif
