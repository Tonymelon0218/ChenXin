//////////////////////////////////////
//Project:   LT2101
//Filename:  I2CMast.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CHIPRXTYPEC_H
#define _CHIPRXTYPEC_H
#include "LtType.h"

#if ((CHIP_SEL == LT8711GXE)||(CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP)||(CHIP_SEL == LT6711GXE))

#define   DP_ALT_MODE_LBYTE         0x01
#define   DP_ALT_MODE_HBYTE         0xFF
#define   Samsung_LByte		        0xe8
#define   Samsung_HByte       		0x04
#define   Switch_LByte		        0x7e
#define   Switch_HByte       		0x05
#define   APPLE_ADAPTER_LBYTE       0xAC
#define   APPLE_ADAPTER_HBYTE       0x05


#define   Vconn_Sent                0x01
#define   Vconn_No_Sent             0xf0
#define   DR_No_Sent                0x0f
#define   DR_Sent_Accept            0x10
#define   DR_Sent_Reject            0x20
#define   DR_Sent                   0x30

#define   Sleep_None                0x00
#define   Sleep_Type0               0x01
#define   Sleep_Type1               0x02
#define   Sleep_Type0_Ing           0x03
#define   Sleep_Type1_Ing           0x04

#define   HardRst_None              0x00
#define   HardRst_Rec               0x01
#define   HardRst_Initate           0x02
#define   HardRst_Switch            0x03
#define   HardRst_Source            0x04

#define   VconnSource_None          0x00
#define   VconnSource_Going         0x01
#define   VconnSource_Ready         0x02

#define   SOP1END                   0x00
#define   SOP1SENDING               0x01
#define   SOP1CRCRECVING            0x02

#define   HUBRESETLOW               0x00
#define   HUBRESETHIGH_DONE         0x01
#define   HUBRESETHIGH_PRE          0x02
#define   HUBRESETHIGH_GOING        0x03

#define   TIMER_OVER                0x00
#define   TIMER_READY               0x01
#define   TIMER_START               0x02
#define   TIMER_CONTIUNE            0x03

#define     Watt_0          0
#define     Watt_5          1
#define     Watt_8          2
#define     Watt_10         3
#define     Watt_12         4
#define     Watt_15         5

#define     NOT_SWITCH              0x00
#define     SWITCH_ADAPTER          0x01
#define     SWITCH_ADAPTER_15V    	0x02
#define     SWITCH_ADAPTER_ALL    	0x03

#define     PIN_NONE                0x00
#define     PIN_A                   0x01
#define     PIN_B                   0x02
#define     PIN_C                   0x04
#define     PIN_D                   0x08
#define     PIN_E                   0x10
#define     PIN_F                   0x20

#define   	TRYTIMES             0x02//Try Times

#define     NO_TRY					0x00
#define     TRY_SRC					0x01
#define     TRY_SNK					0x02
typedef struct AmsStatus
{
    u8 ucPower_Ams;
    u8 ucGotoMin_Ams;
    u8 ucSoftReset_Ams;
    u8 ucHardReset_Ams;
    u8 ucCableReset_Ams;
    u8 ucGetSrcCap_Ams;
    u8 ucGetSnkCap_Ams;
    u8 ucPrSwap_Ams;
    u8 ucFrSwap_Ams;
    u8 ucDrSwap_Ams;
    u8 ucVconnSwap_Ams;
    u8 ucSrcAlert_Ams;
    u8 ucGetSrcExtCap_Ams;
    u8 ucGetStatus_Ams;
    u8 ucGetBattCap_Ams;
    u8 ucGetBattStatus_Ams;
    u8 ucGetManuInfo_Ams;
    u8 ucSecurity_Ams;
    u8 ucFwUpdate_Ams;
    u8 ucDiscoverID_Ams;
    u8 ucSrcStartup_Ams;
    u8 ucDiscoverSvids_Ams;
    u8 ucDiscoverModes_Ams;
    u8 ucDToUEnterMode_Ams;
    u8 ucDToUExitMode_Ams;
    u8 ucDToCEnterMode_Ams;
    u8 ucDToCExitMode_Ams;
    u8 ucAttention_Ams;
    u8 ucBist_Ams;
} StructAms;



typedef struct TypecStatus
{  
    u8 b1PowerRole;
    u8 b1DataRole;
	#if VCONNSWAP_SUPPORT == ENABLED 
    u8 b1VconnSwap_En;
	#endif
    u8 b1FrTriggle;
    u8 b1PrDone;
    u8 b1Multi_Function;
    u8 b2Charger_Scan;
    u8 b1AdapterWithPD;
    u8 b1PsRdy_Send;
    u8 b2Toggle_enable;
    u8 b1WaitMsg_Receive;
    u8 b1Msg_ID_Change;
    u8 b1IsFlip;
    u8 b1Flag_Source_Send;
    u8 b1Toggle_DFP_EN;
    u8 b2Hardreset_Hdl;
    u8 b1IsCc_done;
    u8 b1CCDataMsg_Sent;
    u8 b1UCcInput_type;
    u8 ucPRSended;
    u8 ucPRSwaping;
    u8 ucPRSwaped;    
    u8 ucDrSwap_En;    
    u8 ucFRSwaping;
    u8 ucContract_Succeed;
    u8 ucSwap_Sent;
    u8 ucRetryCounter;    
    u8 ucFlow_Step;
    u8 ucVDM_Step;  
    u8 ucnUccSourceCapCnt;
    u8 uclaneCount;
    u8 ucnRetryCount;
    u8 b2SwapSourceStart;
    u8 b1PrSwapDone;
    u8 b1IsVconnSource;
//    #if PDCTS_USE == ENABLED
    u8 b1SwapToVconnSource;
//    #endif  
    u8 ucCable5A;
    #if UCC_EMARK_SUPPORT == ENABLED
    u8 ucSop1MsgStep;
    #endif
    #if DCC_TOGGLE_SUPPORT == ENABLED
    u8 b1DccUfpMode;
    u8 b1DccDfpMode;
    #endif
	#if HUB_RESET_CTRL == ENABLED
    u8 b2HubResetHigh;
	#endif
    u8 b1IsUccMux;
    u8 ucRequestPdo;
	#if PINE_SUPPORT == ENABLED
	u8 ucPin_Assignment;
	#endif
	#if CCTRY_MODE != NO_TRY
	u8 b2TRYTIMES;
	#endif
	u8 b1Pd31Test;
    u8 b2AttentionType;
    
    u8 b1CcDataRoleSet;
    u8 b2VdmBusy;
    u8 b2DisIdSend_En;
    u8 ucUccIrq;
} StructCcStatus;

typedef struct TypecMSG
{
    u8 b1RcvGoodCRC;
    u8 b1SendEN ;
    u8 b1Vdm_Msg;
    u8 *pDataOrder;
    u8 szRcvDate[34];
    u8 szHeader[4];
    u8 szRequest_Buffer[6];
    u8 szRequestTmp[6];
    u8 szAdapterTmp[34];
    #if FORCE_NINTENDO_SWITCH == ENABLED
    u8 szSwitchTmp[34];
    #endif
    u8 szAdapterTmpFor3A[34];
    u8 szPDP_Value[2];
    u8 szCC_ModeMsg_Buffer[10];
    u8 szAdapterCap_Ori[34];
    #if PD_PPS_EN == ENABLED
    u8 szPPS_Object[3];
    u8 szAdapterCap_For_PD30[34];
    #endif
    u8 ucCcVersion;
    u8 ucMessageID_New;
    u8 ucMessageID_Tmp;
    u8 ucMsgType_Tmp;
    u8 ucLastMsgType;
    u8 ucMessageID;
    u8 *pBuffer_Order;
    u8 *pLast_DataOrder;
} StructCcMsg;

typedef struct NINTENDOSWITCH
{
    u8 b1Switch_Online;
    u8 b1IsSwitch;
    u8 b2Switch_Ada_Online;
    u8 b2SwitchIntoSleep;
    u8 b2SwitchIntoWakeUp;
    u8 b1NintendoRecordTxHpd;
    u8 b1HPDLongTime;
}StructNintendoState;
extern StructCcStatus DCCStatus;
extern StructCcStatus UCCStatus;
extern StructCcMsg DCCMSG;
extern StructCcMsg UCCMSG;

extern StructAms UCCAmsType;
extern StructAms DCCAmsType;

extern u8 code szCC_DataMsg[][10];
extern u8 szCC_DiscoverIDMsg[22];
extern u8 code szCC_CtrlMsg[][2];
extern u8 szCC_SourceCapExt[30];
extern u8 code szSink_CapExtended_Msg[30];
extern u8 szSource_Info_Msg[6];
extern u8 code szRevision_Msg[6];

//extern void Mod_CC1HpdIrq_Send(bool IsAttentionHigh, bool IsIrqHigh);
extern void Mod_CC1HpdIrq_Send(u8 ucAttentType);
extern u8 Mod_CC1ComDone_Get(void);
extern void Typec_Var_Init(void);
extern u8 Mod_CC1MsgType_Calc(IN u8 ucCommandType,IN u8 ucMessageType,IN u8 ucVdmType);

extern void Mod_CC1SourceCapMsg_Loop(void);
extern void Mod_CC1SwapMsg_Scan(void);
extern void Mod_CC1Vari_Init(void);
extern void TypeC_Init(void);
extern void Drv_CC2VoltageLvl_Det(void);

extern void Mod_CC1DetOff_Action(void);
extern u8 Mod_CC1DetOff_Judge(void);
extern u8 code szEprMod_Msg[6];
extern u8 code szEprRequest_Msg[10];
extern u8 code szEprKeepAlive_Msg[6];

extern void Mod_HardRstRec_Handle(void);//TDB2.2.13.1
extern void Mod_HardRstSend_Handle(void);
extern void Mod_CC1SoftRstRec_Handle(void);

extern void Mod_CC1Rx_Loop(void);
#if NINTENDO_SWITCH == ENABLED
extern StructNintendoState CC1NINTENDOState;
extern u8 szNintendo_DisC_ID[22];
extern u8 code szCC_Nintendo_DataMsg[][14];
extern void Mod_EnterIntoSwitch_Handle(void);
extern u8 code szNintendoSwitch_SourceCap_Msg[10];
#endif
extern void Mod_CC1CableVari_Init(void);
extern void Mod_CC1Vconn_Off(void);
extern void Mod_CC2Vari_Init(void);
extern u8 code szCCData_SourceCap[6];
extern u8 code szCCData_Request[6];

extern u8 code szCCData_REQDiscoverId[6];//3 Discover Identity initiator
extern u8 code szCCData_REQDiscoverSvid[6];//4 Discover SVIDs initiator
extern u8 code szCCData_REQDiscoverModes[6];//5 Discover Modes initiator
extern u8 code szCCData_REQEnterMode[6];//6 Enter Modes

extern u8 code szCCData_REQExitMode[6];

extern u8 code szCCData_REQDpStatusUpdate[10];//7 DP Status Update initiator
extern u8 code szCCData_REQDpConfig_PINCE[10];// 1 4lane DP config
extern u8 code szCCData_REQDpConfig_PIND[10];// 2 2lane DP Config

extern u8 code szCCData_SinkCapPD20[6];
extern u8 code szCCData_SinkCapPD30[6];


extern u8 code szCCCtrl_PrSwap[2];
extern u8 code szCCCtrl_PsReady[2];
extern u8 code szCCCtrl_Accept[2];
extern u8 code szCCCtrl_Reject[2];
extern u8 code szCCCtrl_VconnSwap[2];
extern u8 code szCCCtrl_DrSwap[2];
extern u8 code szCCCtrl_NotSupport[2];
extern u8 code szCCCtrl_SoftReset[2];


extern u8 code szCCCtrl_GotoMin[2];//gotomin           8
extern u8 code szCCCtrl_Ping[2];//ping              9
extern u8 code szCCCtrl_GetSourceCap[2];//get_source_cap
extern u8 code szCCCtrl_GetSinkCap[2];//get_sink_cap
extern u8 code szCCCtrl_Wait[2];//wait
extern u8 code szCCCtrl_DataReset[2];//data_reset
extern u8 code szCCCtrl_DataResetComplete[2];//data_reset_complete
extern u8 code szCCCtrl_GetSourceCapExtended[2];//get_source_cap_extended
extern u8 code sszCCCtrl_GetStatus[2];//get_status
extern u8 code sszCCCtrl_FrSwap[2];//fr_swap
extern u8 code sszCCCtrl_GetPPSStatus[2];//get_pps_status
extern u8 code sszCCCtrl_GetCountryCodes[2];//get_country_codes
extern u8 code sszCCCtrl_GetSinkCapExtended[2];//get_sink_cap_extended
extern u8 code sszCCCtrl_GetSourceInfo[2];//get_source_info
extern u8 code sszCCCtrl_GetVersion[2];//get_version
#endif
#endif
