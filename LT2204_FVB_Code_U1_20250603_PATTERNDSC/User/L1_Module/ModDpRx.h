//////////////////////////////////////
//Project:   LT2101
//Filename:  ChipDpRx.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CHIPDPRX_H
#define _CHIPDPRX_H

#include "LtType.h"

#if RX_PORT_SIGN == DP_PORT

typedef enum
{
    STATE_DPRX_POWER_ON_1 = 1,
    STATE_DPRX_INPUT_TYPE_DET_2,
    STATE_DPRX_WAIT_SOURCE_3,
    STATE_DPRX_DOWNSTREAM_READY_4,
    STATE_DPRX_SET_HPD_5,
    STATE_DPRX_WAIT_LINK_TRAIN_6,
    STATE_DPRX_WAIT_MST_DONE_7,
    STATE_DPRX_EQ_FINE_TUNE_8,
    STATE_DPRX_DESKEW_CHECK_9,
    STATE_DPRX_DEPACKET_CHECK_10,
    STATE_DPRX_MSA_CHECK_11,
    STATE_DPRX_PPS_CHECK_12,
    STATE_DPRX_PCR_CONFIG_13,
    STATE_DPRX_HDCP_VER_CHK_14,
    STATE_DPRX_AUDIO_INFO_CHK_15,
    STATE_DPRX_PLAY_BACK_16
}EnumDpRxState;


typedef struct DpRx
{
    u8 ucRxState;
    u8 ucMstStreamNum;
    u8 b1Input_Type_Sel ;
    u8 b1Ssc_Support;
    u8 b1Tps3_Support;
    u8 b1Tps4_Support;

    u8 b1SourceDet;
    u8 b1RxStateChanged;
    u8 b1DownstreamDeviceReady; //the device that receive video stream of dp rx ip.
    #if (DPRX_TIMING_HBE == ENABLED)
    u8 b2IsTimingHBE;
    #endif
    u8 ucRxMaxLinkRate;
    u8 ucRxMaxLaneCount;
    //dsc
    u8 ucDscChunkSizeErr;
    u8 ucDscRcBufOverFlow;
    u8 ucDscRcBufUnderRun;
    //hdcp
    u8 ucHdcpVersion;
    //adaptive sync
	#if DPRX_ADAPTIVE_SYNC == ENABLED
    u8 b1AdaptiveSyncEn;
	#endif
    //hdr
    u8 b1HdrEn;
    //===audio info===
    u8 ucLayout;
    u8 ucChannel;
    u8 ucFsValue;
    //===color info===
    u8 b1VscPkg;
    u8 ucPixelEncoding;
    u8 ucColorimetryFormat;
    u8 ucBitDepth;
    u8 b1DynamicRange;
    //csc
    u8 b1CscRxEnable;
    u8 b1CscRxOutRange;
    u8 b1CscRxOutFormat;
    //msa
    u16 usHotal;
    u16 usHactive;
    u32 ulRxPixelClk;
    u32 ulRxPeakClk;
    #if DPRX_ADAPTIVE_SYNC == ENABLED
    u8 ucAdaptiveSync_En;
    #endif
	u8 b1CompressedStream;
    u8 b1DscAbnormal;
    u8 ucDscFifoEmpty;
    u8 ucDscFifoFull;
//    u8 ucDscSel;
} StructDpRx;

extern StructDpRx g_stDpRx;

extern void Mod_DpRx_PowerOnInit(void);
extern void Mod_DpRx_Handler(void);
extern void Mod_DpRx_HpdIrq(void);
extern void Mod_DpRx_InfoDisplay(void);
extern u8 Mod_DpRx_UpStreamVidReadyGet();

extern void Mod_DpRx_HpdLowAction(void);
extern void Mod_DpRx_SetState(u8 ucState);
extern void Mod_DpRx_PeakClkCal(void);
extern u8 Mod_DpRx_ColorDepth(void);
extern u8 Mod_DpRx_ColorSpace(void);
extern void Mod_DpRx_MsgNotify(u8 ucEvent);
extern void Mod_DpRx_FrameRate_Get(LtTiming_S *pstRxTimingInfo);
extern u8 Chip_Timing_Check(LtTiming_S stRxTimingInfo);
extern u8 Chip_DpRx_JudgeTimingHBE(void);
extern void Chip_DpRx_TimingHBE(void);
#endif
#endif

