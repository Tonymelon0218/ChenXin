//////////////////////////////////////
//Project:   LT2204
//Filename:  ChipMipi.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CHIPMIPITX_H
#define _CHIPMIPITX_H

#include "LtType.h"

#if TX_PORT_SIGN == MIPI_PORT

#define     MIPITX_DSI          0
#define     MIPITX_CSI          1

#define     MIPITX_DPHY         0
#define     MIPITX_CPHY         1

#define     MIPITX_PLL_LOW      400000
#define     MIPITX_PLL_HIGH     2700000     // Default: 2700000

#define     CTS_DATARATE        1900000

#define     MIPI_DSI_VIDEO_MODE         NON_BURST_MODE_WITH_SYNC_PULSE  // BURST_MODE/NON_BURST_MODE_WITH_SYNC_PULSE/NON_BURST_MODE_WITH_SYNC_EVENT
#define     MIPI_CLOCK_BURST    		OFF             // ON/OFF
#define     MIPI_PORT_NUM       		MIPI_1PORT      // MIPI_1PORT/MIPI_2PORT/MIPI_4PORT
#define     MIPITX_3D_MODE_SEL  		MIPI_NO_3D_MODE // MIPI_NO_3D_MODE/MIPI_LEFT_RIGHT_MODE/MIPI_ODD_EVEN_MODE
#define     MIPI_LANE_NUM       		MIPI_PORT_4LANE // MIPI_PORT_4LANE & MIPI_PORT_3LANE & MIPI_PORT_2LANE & MIPI_PORT_1LANE , no MIPI_PORT_8LANE
#define     MIPITX_PHY_SEL      		MIPITX_CPHY     // MIPITX_DPHY/MIPITX_CPHY
#define     MIPITX_PRO_SEL      		MIPITX_DSI      // MIPITX_DSI/MIPITX_CSI
#define     MIPITX_VIDEO_FORMAT 		DSI_RGB_888     // DSI_RGB_888/CSI_YUV422_8Bit/CSI_RGB_888

#define     MIPITX_DSC          		ENABLED

/*********High-speed commands available only in DPHY*********/
#define     MIPITX_HSCMD_EN             DISABLED        /* Only work at BURST_MODE */
#define     MIPITX_HSCMD_HSSLEN         0x2A            /* HSS time must be enough for the longest HS packet */
#define     MIPITX_HSS_BURST_EN         DISABLED        /* HS Cmd must enable bit2 of 0xF989:RGD_BURST_MODE */

#define     MIPI_OUT_CTRL               DISABLED        // ENABLED/DISABLED


#if ((CHIP_SEL == LT6911GXD_HD)||(CHIP_SEL == LT6911GXD_DP))

#define     MP0_EN             	    ENABLED 
#define     MP1_EN                  DISABLED 
#define     MP2_EN              	ENABLED 
#define     MP3_EN             	    DISABLED

#else

#define     MP0_EN                ENABLED 
#define     MP1_EN                ENABLED 
#define     MP2_EN                ENABLED 
#define     MP3_EN                ENABLED

#endif

#define     CSI_SOFTWARE_SEND_FE  0                     // CSI 模式下 软件发送FE 0 禁能 1：使能

#define     MIPI_CHPY_HSLP_FALL_CFG_EN                  // Slove CPHY LP HS LDO FALL

typedef enum
{
    MIPI_PORT_1LANE = 0x01,
    MIPI_PORT_2LANE = 0x02,
    MIPI_PORT_3LANE = 0x03,
    MIPI_PORT_4LANE = 0x04,
    MIPI_PORT_8LANE = 0x08
} Enum_PORTLANE_NUM;

typedef enum
{
    MIPI_1PORT = 1,
    MIPI_2PORT = 2,
    MIPI_4PORT = 4
} Enum_PORT_NUM;

typedef enum
{
    MIPI_NO_3D_MODE = 0,
    MIPI_LEFT_RIGHT_MODE = 1,
    MIPI_UP_DOWN_MODE = 2, // Not Support
    MIPI_ODD_EVEN_MODE = 4,
} MIPITX_3D_MODE;

typedef enum
{
    DSI_RGB_565 = 0,
    DSI_RGB_666,
    DSI_RGB_888,
    DSI_RGB_30,
    DSI_YUV422_16Bit,
    DSI_YUV422_20Bit,
    DSI_YUV422_24Bit,
    DSI_YUV420_12Bit,

    CSI_RGB_565,
    CSI_RGB_666,
    CSI_RGB_888,
    CSI_YUV422_8Bit,
    CSI_YUV422_10Bit,
    CSI_YUV420_8Bit
} Enum_MIPI_OUT_FORMAT;

typedef enum
{
    NON_BURST_MODE_WITH_SYNC_EVENT = 1,
    NON_BURST_MODE_WITH_SYNC_PULSE = 2,
    BURST_MODE = 3
} MIPITX_DSI_VIDEO_MODE;

typedef enum
{
    STATE_MIPITX_POWER_ON_1 = 1,          // 0x01
    STATE_MIPITX_UPSTREAM_DEVICE_READY_2, // 0x02
    //    STATE_MIPITX_WAIT_HPD_3,             //0x03
    STATE_MIPITX_UPSTREAM_VIDEO_READY_3, // 0x04
    STATE_MIPITX_CONFIG_VIDEO_AUDIO_4,   // 0x05
    STATE_MIPITX_VIDEO_OUT_5,            // 0x06
    STATE_MIPITX_AUDIO_OUT_6,            // 0x07
    STATE_MIPITX_PLAY_BACK_7             // 0x08
} EnumMipiTxState;

typedef struct MipiTx
{
    u8 b1UpstreamDeviceReady;
    u8 b1UpstreamVideoReady;
    u8 b1MipiClockburst;
    u8 b1DphyCsi8Lane;
    u8 ucTxState;
    u8 ucTxStateChangeFlag;
    u8 ucTxPhySel;

    u8 ucTxFormat;
    u8 ucTxPixelEncoding;
    u8 ucBpp;
    u8 ucTxPortNum;
    u8 ucTxLaneNum;
    u8 uc3DMode;
    u32 ulMipiDataRate;
    u32 ulMipiInClk;
    u8 b1DSIVideoMode;
    u8 b1MIPITXStreamOn;

    u8 b1MIPITXProSel;
    u8 ucLMTXPortSel;

    /******hdr******/
    u8 b1SrcStaticHdrEn;
    u8 b1SrcStaticHdrChg;
    u8 b1SrcDoblyHdrEn;
    u8 b1SrcDoblyHdrChg;
    u8 b1SrcDynamicHdrEn;
    u8 b1SrcDynamicHdrChg;

} StructMipiTx;

typedef struct MipiVideoFmtCfg
{
    u8 ucVideoFmt; // Enum_MIPI_OUT_FORMAT
    u8 ucBpp;
    u8 ucBppAndFmtsel; // Ref reg 0xF988
    u8 ucDatatype;
    u8 ucPro; // DSI or CSI
} StructMipiVideoFmtCfg;

extern StructMipiTx g_stMipiTx;
extern u8 szEdidData[512];
extern u8 code szMipiEdid[512];

extern void Mod_MipiTx_PowerOnInit(void);
extern void Mod_MipiTx_Handler(void);
extern void Mod_LMTx_EventMonitor(u8 ucMsgType);
extern void Mod_MIPITx_Pattern(void);
#endif
#endif
