//////////////////////////////////////
//Project:   LT2101
//Filename:  Edid.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CHIPHDMITX_H
#define _CHIPHDMITX_H

#include "LtType.h"

#if TX_PORT_SIGN == HDMI_PORT

typedef enum
{
    STATE_HDMITX_POWER_ON_1 = 1,          //0x01
    STATE_HDMITX_UPSTREAM_DEVICE_READY_2, //0x02
    STATE_HDMITX_WAIT_HPD_3,             //0x03
    STATE_HDMITX_UPSTREAM_VIDEO_READY_4,  //0x04
    STATE_HDMITX_DSCENC_CONFIG_5,
    STATE_HDMITX_FRL_TRAINING_6,
    STATE_HDMITX_VIDEO_OUT_7,             //0x06
    STATE_HDMITX_AUDIO_OUT_8,             //0x07
    STATE_HDMITX_HDCP_ENABLE_9,           //0x08
    STATE_HDMITX_PLAY_BACK_10              //0x09
}EnumHdmiTxState;

typedef struct HdmiTx
{
    u8 b1UpstreamDeviceReady;
    u8 b1UpstreamVideoReady;
    u8 b1IsTxHpdDet;
    u8 b1EncodeEn;
    u8 b1SrcDscByEn;
    u8 b1TxDscByEn;
    u8 ucHdmiVersion;
    //hdcp
    u8 ucHdcpRxVerChg;
    u8 b1HdmiMode;
    u8 ucszAviPkt[5];
    u8 ucColorDepth;
    u8 ucHdmiVic;
    u8 ucTxState;
    u8 b1TxStateChanged;
    u8 ucTxPixelEncoding;
    /******audio info******/
    u8 ucLayout;
    u8 ucChannel;
    u8 ucFsValue;
    u8 ucCodingType;
    u8 szAudioInfo[9];
    u8 b1AudioInfoChg;
    /******audio info******/
    #if HDMITX_VRR_SUPPORT == ENABLED
    u8 b1SrcVrrEn;
    u8 b1SrcVrrChg;
    #endif
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
    /******hdr******/
    u32 ulTxPixelClk;
    u32 ulTxTmdsClk;
    u8 ucHdcpRxVerRecord;
//	u8 szEdidSave[4];
	u8 szErrChk[7];
	u8 b1ScdcCheck_En;
    u8 b1TxHdcpScanEn;
//    u16 ulFrameRate;
} HdmiTx_S;

extern HdmiTx_S g_stHdmiTx;

extern void Mod_HdmiTx_PowerOnInit(void);
extern void Mod_HdmiTx_HpdLowAction(void);
extern void Mod_HdmiTx_Handler(void);
extern void Mod_HdmiTx_Pattern(void);

extern u8 Mod_HdmiTx_DscEncEnableJudge(void);
extern u8 Mod_HmdiTx_EdidRead(u8 *pucEDID_Data,u8 ucCntClr);
extern u32 Mod_HdmiTx_LinkBandWidthGet(void);
extern void Drv_HdmiTx_VrrSet(u8 b1VrrEn,LtTiming_S *pRxTimingInfo);
#if HDMITX_CTS_SUPPORT == ENABLED
extern void Mod_HdmiTx_ReadSinkErrorCnt(void);
#endif
extern void Drv_HdmiScdc_Scan(u8 b1IsHdmi20,u8 b1ScdcCheckEn,u8 b1ScdcPresent);
#endif
#endif
