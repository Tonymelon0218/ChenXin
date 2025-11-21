/******************************************************************************
  * @project: LT2204
  * @file: ChipDpTx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.30
/******************************************************************************/

#ifndef _CHIPDPTX_H
#define _CHIPDPTX_H

#include "LtType.h"
typedef enum
{
    STATE_DPTX_POWER_ON_1 = 1,
    STATE_DPTX_UPSTREAM_DEVICE_READY_2,
    STATE_DPTX_WAITE_HPD_3,
    STATE_DPTX_READ_SINK_INFO_4,
    STATE_DPTX_UPSTREAM_VIDEO_READY_5,
    STATE_DPTX_DSCENC_CONFIG_6,
    STATE_DPTX_LINK_TRAINING_7,
    STATE_DPTX_VIDEO_OUT_8,
    STATE_DPTX_AUDIO_OUT_9,
    STATE_DPTX_HDCP_ENABLE_10,
    STATE_DPTX_PLAY_BACK_11
}EnumDpTxState;


typedef struct DpTx
{
    u8 b1IsDpOrTypec;
    u8 ucTxLinkStartEn;
    u8 ucTxState;
    u8 ucTxLinkStep;
    u8 ucTxLinkTrainingCnt;
    u8 ucTxLinkReduceNumber;
    u8 ucTxLinkTpsState;
    u8 ucTxLinkStopDrvAdjust;
    u8 ucTxLinkStopReduction;
    u8 ucTxLinkTrainSinkState[3];
    u8 b1TxStateChanged;
    u8 b1UpstreamDeviceReady;
    u8 b1UpstreamVideoReady;
    u8 b1IsTxHpdDet;
    u8 b1SoftMsaUpdate;
    u8 b1SoftMsaEn;
    //dsc
    u8 b1SrcDscByEn;
    u8 b1TxDscByEn;
    u8 b1EncodeEn;
    u8 b1FecEnable;
    //vsc
    u8 b1VscEnable;
    u8 b1HbeEnable;
    /******hdcp******/
    u8 ucHdcpRxVersion;
    u8 ucHdcpRxVerChg;
    u8 ucHdcpTx1xAuthState;
    /******hdcp******/

    /******color info******/
    u8 ucPixelEncoding;
    u8 ucColorimetryFormat;
    u8 ucBitDepth;
    u8 ucMsaValue;
    u8 ucMisc0;
    u8 ucMisc1;
    u8 ucVscDb16;
    u8 ucVscDb17;
    u8 ucVscDb18;
    /******color info******/

    /******audio info******/
    u8 ucLayout;
    u8 ucChannel;
    u8 ucFsValue;
    u8 szAudioInfo[9];
    u8 b1AudioInfoChg;
    u8 b1AudioMuteEn;
    u8 b1AudioHbrEn;
    /******audio info******/

    /******Vrr******/
    u8 b1SrcVrrEn;
    u8 b1SrcVrrChg;
    /******Vrr******/
    
    /******I TIMING******/
    u8 b1SrcInterlaceEn;
    u8 b1SrcInterlaceChg;
    /******I TIMING******/
    
    /******hdr******/
    u8 b1SrcStaticHdrEn;
    u8 b1SrcStaticHdrChg;
    u8 b1SrcDoblyHdrEn;
    u8 b1SrcDoblyHdrChg;
    u8 b1SrcDynamicHdrEn;
    u8 b1SrcDynamicHdrChg;
    u8 b1DpTxAppleFlag;
    /******hdr******/
    u32 ulTxPixelClk;
    u32 ulTxPeakClk;
    
    u8 ucCodingType;
    
}DpTx_S;

typedef struct DpTxAux
{
    u8 ucTps3En;
    u8 ucTps4En;
    u8 ucDscCap;
    u8 ucDscSliceCap;
    u8 ucDscColorFormat;
    u8 ucFecCap;
    u8 b1SscCap;
    u8 b1ScrambleCap;
    u8 ucASyncCap;//adaptive sync cap
    u8 ucHbeCap;//hbe en
    u8 ucSwingWave;
    u8 ucVoltSwing;
    u8 ucDpVersion;
    u8 ucPreEmphase;
    u8 ucLaneCntMax;
    u8 ucLinkRateMax;
    u8 ucLaneCntCap;
    u8 ucLinkRateCap;
    u8 ucEdpLinkRateCap;
    u8 ucTrainInterval;
    u8 ucSinkCnt ;
    u8 b1SinkVscSupport;
    u8 b1TestEdidReadEn;
    u8 b1MsaIgnoreCap;
    u8 ucDscBPPCap;
    u8 ucDscSupportCap;
}DpTxAuX_S;


extern DpTx_S g_stDpTx;
extern LtTiming_S g_stDpTxTiming;

extern void Mod_DpTx_Handler(void);
extern void Mod_DpTx_PowerOnInit(void);
extern void Mod_DpTx_HpdLowAction(void);
extern void Mod_DpTx_Pattern(void);
extern void Mod_DpTx_TotalByteUpdate(u8 IsUpdate);
extern void Mod_DpTx_SetState(u8 ucState);

extern u8 Mod_DpTx_HbeEnableJudge(void);
extern u8 Mod_DpTx_DscEncEnableJudge(void);
extern u8 Mod_DpTx_SinkHpdDet(void);
#endif
