//////////////////////////////////////
//Project:   LT2204
//Filename:  ChipLvds.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CHIPLVDSTX_H
#define _CHIPLVDSTX_H

#include "LtType.h"

#if TX_PORT_SIGN == LVDS_PORT

typedef enum
{
    P_VIDEO_FMT = 0,
    I_VIDEO_FMT,
}LVDS_VIDEO_FMT;

typedef enum
{
    YoCb_FIRST = 0x1b,
    YoCr_FIRST = 0x93,
    CbYo_FIRST = 0x4b,
    CrYo_FIRST = 0x63,
    
}SONY_YUV422BPC_DATA_FMT;


#define LVDS_SSC                DISABLED // ENABLED & DISABLED
#define LVDS_SSC_SEL            SSC_1920x1080_30k5
#define LVDS_DEMODE             DISABLED // ENABLED & DISABLED   如果选择disabled 那就意味着选择Sync mode
#define LVDS_PORTNUM            LVDS_4PORT //LVDS_1PORT/LVDS_2PORT/LVDS_4PORT
#define LVDS_3D                 NO_3D_MODE //NO_3D_MODE/SIDE_BY_SIDE
#define LVDS_SUB_MODE_LANE      LVDSTX_8LANE //SUB LVDS LANE Sel
#define LVDS_SONY422_DATA_MAP_SEL YoCb_FIRST

#define LVDS_DATAMAP            VESA_RGB_8Bit //SONY_YUV422_8Bit/VESA_RGB_8Bit/JEIDA_RGB_8Bit/VESA_RGB_10Bit/JEIDA_RGB_10Bit
#define LVDS_VIDEO_FMT          P_VIDEO_FMT  //REF LVDS_VIDEO_FMT 只有在sublvds 或者是内同步模式才可设置


#define LVDS_VBLANK_SYNC_CODE_EN    ENABLED     //DISABLED in Vblank periodand in vactive period  ENABLED:Vblank not Send Sync code
#define LVDS_SYNC_CODE_SEND_INDEPENDENT  ENABLED     //DISABLED:每个 port 同步码非独立传输, ENABLED:每个 port 同步码独立传输 


#define LP0_EN                  ENABLED //PORT0 ENABLED &  DISABLED
#define LP1_EN                  ENABLED //PORT1 ENABLED &  DISABLED
#define LP2_EN                  ENABLED //PORT2 ENABLED &  DISABLED
#define LP3_EN                  ENABLED //PORT3 ENABLED &  DISABLED



//
//typedef enum
//{
//    BPC6_FMT,
//    BPC8_FMT,
//    BPC10_FMT,
//}LVDS_BPC_FMT;

//
//typedef enum
//{
//    RGB_FMT ,
//    Y422_FMT,
//    Y444_FMT,
//    Y420_FMT,
//
//}LVDS_COLOR_SPACE;

#define     NO_SSC                        0
#define     SSC_1920x1080_30k5         1
#define     SSC_3840x2160_30k5         2

typedef enum
{
    LVDS_1PORT = 1,
    LVDS_2PORT = 2,
    LVDS_4PORT = 4,

}LVDS_PORT_NUM;

typedef enum
{
    LVDSTX_1LANE = 1,
    LVDSTX_2LANE = 2,
    LVDSTX_4LANE = 4,
    LVDSTX_8LANE = 8,

}LVDS_LANE_NUM;



typedef enum
{
    NO_3D_MODE = 0,
	SIDE_BY_SIDE,//left&right
	LINE_ALTER,
	FRAME_PACKING,//up&down
}LMTX_3D;


typedef enum
{
    VESA_RGB_6Bit = 0,  //RGB Data mode 
    VESA_RGB_8Bit,  //RGB Data mode 
    JEIDA_RGB_8Bit, //RGB Data mode 
    VESA_RGB_10Bit, //RGB Data mode 
    JEIDA_RGB_10Bit, //RGB Data mode 
    SONY_YUV422_8Bit, //Sony YUV4228bpc mode;
    
    INTERNAL_SYNC_MODE,
    SUB_LVDS_MODE,
}LVDSTX_DATA_MAP;


typedef enum
{
    STATE_LVDSTX_POWER_ON_1 = 1,
    STATE_LVDSTX_UPSTREAM_VIDEO_READY_2,
    STATE_LVDSTX_PLL_CALI_3,
    STATE_LVDSTX_CONFIG_4,    
    STATE_LVDSTX_VIDEO_OUT_5,
    STATE_LVDSTX_AUDIO_OUT_6,	
    STATE_LVDSTX_PLAY_BACK_7
}EnumLvdsTxState;

typedef enum
{
    LVDSTX_SINK_PLUG_EVENT = 1,
    LVDSTX_SINK_UNPLUG_EVENT,
}EnumLvdsTxEvent;

typedef struct LvdsTx
{
    u8 ucTxState;
    u8 ucTxStateChangeFlag;
    u8 b1UpstreamVideoReady;
    
    u8 b1LvdsTxSscEn;
    u8 b1LvdsTxDeModeEn;
    u8 ucLvdsTx3DMode;
    u8 ucLvdsTxDataMap;
    u8 ucLvdsTxPortNum;
    u8 ucLvdsTxLaneNum;
    u8 ucLvdsTxVidFmt;
    u32 ulLvdsTxInputClk;
    u8 ucSonyYuvDataSel;
    u8 ucLvdsVblankSCEn;
    u8 ucLvdsSCSendIndependent;

//    u8 ucLVDSTXColor;
//    u8 ucLVDSTXDataBpc;
		u8 b1LvdsTxSscSel;	
		u8 ucLMTXPortSel;
	
    
}StructLvdsTx;
extern StructLvdsTx g_stLvdsTx;

extern u8 szEdidData[512];
extern u8 code szLvdsEdid[512];

extern void Mod_LvdsTx_NotifyRegister(void (*pFunction)());
extern void Mod_LvdsTx_PowerOnInit(void);
extern void Mod_LvdsTx_Handler(void);
extern void Mod_LMTx_EventMonitor(u8 ucMsgType);
extern void Mod_LvdsTx_Pattern(void);
#endif
#endif
