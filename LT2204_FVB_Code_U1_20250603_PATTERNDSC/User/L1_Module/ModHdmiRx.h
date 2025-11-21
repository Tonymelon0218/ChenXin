/******************************************************************************
  * @project: LT2204
  * @file: ChipHdmiRx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.06.07
/******************************************************************************/
#ifndef _CHIPHDMIRX_H
#define _CHIPHDMIRX_H

#include "LtType.h"

typedef enum
{
    STATE_HDMIRX_POWER_ON_1 = 1,
    STATE_HDMIRX_WAITE_SOURCE_2,
    STATE_HDMIRX_DOWNSTREAM_READY_3,
    STATE_HDMIRX_SET_HPD_4,
    STATE_HDMIRX_TMDSCLK_STB_CHK_5,
    STATE_HDMIRX_TMDSCLK_RXPLL_CONFIG_6,
    STATE_HDMIRX_WAIT_FRL_TRAIN_7,
    STATE_HDMIRX_DESKEW_CHECK_8,
    STATE_HDMIRX_LINK_VIDTIMING_CHK_9,
    STATE_HDMIRX_PCR_CONFIG_10,
    STATE_HDMIRX_DEPACKET_CHECK_11,
    STATE_HDMIRX_PPS_CHECK_12,
    STATE_HDMIRX_SECPCR_CONFIG_13,
    STATE_HDMIRX_DSC_CONFIG_14,
    STATE_HDMIRX_VIDEO_CHECK_15,
    STATE_HDMIRX_HDCP_VER_CHK_16,
    STATE_HDMIRX_AUDIO_INFO_CHK_17,
    STATE_HDMIRX_PLAY_BACK_18
}EnumHdmiRxState;

typedef struct HdmiRx
{
    u8 ucRxState;
    u8 ucHdmiVer;
    u8 b1SourceDet;
    u8 b1PpsInfoDet;
    u8 b1RxStateChanged;
    u8 b1DownstreamDeviceReady;//the device that receive video stream of dp rx ip.
    u8 b1EqScanEn;
    u8 ucEqScanCnt;
    u8 ucPixelEncoding;
    u8 ucColorimetryFormat;
    u8 ucBitDepth;
    u8 b1ExtendColorimetryFlag;
    u8 ucHdcpVersion;
    u8 b1VrrEn;
    u8 b1HdrEn;
    u8 b1EqSucc;
    //===audio info===
    u8 ucLayout;
    u8 ucChannel;
    u8 ucFsValue;
    //===audio info===
    //csc
    u8 b1CscRxEnable;
    u8 b1CscRxOutRange;
    u8 b1CscRxOutFormat;
    u32 ulRxPixelClk;
    u32 ulRxTmdsClk;
    u32 usFramerate;
    //csc
}StructHdmiRx;

extern StructHdmiRx g_stHdmiRx;

extern void Mod_HdmiRx_PowerOnInit(void);
extern void Mod_HdmiRx_Handler(void);
extern void Mod_HdmiRx_HpdLowAction(void);
extern u8 Mod_HdmiRx_InterlaceGet(void);
extern u8 Mod_HdmiRx_VrrSwitchGet(void);
extern u8 Mod_HdmiRx_HdrStateGet(void);
extern void Mod_HdmiRx_TmdsClkCal(void);
extern void Mod_HdmiRx_InfoDisplay(void);
extern void Mod_HdmiRxEq_Frl_ValSet(u8 ucLane,u8 ucEqValue);
#endif