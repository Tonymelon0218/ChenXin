//////////////////////////////////////
//Project:   LT2101
//Filename:  Lt8711uxe2.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _LT86121GXE_H
#define _LT86121GXE_H

#include "LtType.h"

#if CHIP_SEL == LT86121GXE


#define        DEMO_FW_EN




#ifdef DEMO_FW_EN
//-----------------------------------------UART-----------------------------------------------
#define UART_TX_PIN     GPIO21_UART_TX
#define UART_RX_PIN     GPIO16_MCLKA
//----------------------------------------PORT-------------------------------------------------
#define RX_PORT_SIGN    HDMI_PORT   
#define TX_PORT_SIGN    HDMI_PORT   


//=====================================HDMI RX=================================================
#define HDMIRX_FORCE_2BLOCKEDID         DISABLED        //ENABLED/DISABLED
#define HDMIRX_MAX_FRL_RATE             FRL_10G4LANE     //FRL_NOT_SPT/FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMIRX_HDCP_DEC_MODE            (HDCP1X+HDCP2X) //NO_HDCP/HDCP1X/HDCP2X/(HDCP1X+HDCP2X)
#define HDMIRX_HDCP_REPEATER            DISABLED        //ENABLED/DISABLED
#define HDMIRX_VRR_SUPPORT              DISABLED        //ENABLED/DISABLED
#define HDMIRX_EQ_STAGE                 EQ_16_STAGE     //EQ_16_STAGE/EQ_8_STAGE
#define HDMIRX_EQ_MODE                  HW_MODE         //HW_MODE/SW_MODE/FIX_MODE
#define HDMIRX_EQ_SCAN_MAX              2

#define DEBUG_HDMIRX_EDID_PRINT_EN      DISABLED        //ENABLED/DISABLED
//=====================================HDMI RX=================================================


//=====================================HDMI TX=================================================
#define HDMITX_EDID_READ_EN             ENABLED         //ENABLED/DISABLED
#define HDMITX_MAX_FRL_RATE             FRL_10G4LANE     //FRL_NOT_SPT/FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMITX_MAX_FFE_LEVEL            LEVEL_0         //LEVEL_0/LEVEL_1/LEVEL_2/LEVEL_3
#define HDMITX_HDCP_ENC_MODE            NO_HDCP         //NO_HDCP/HW_MODE/FIXED_HDCP1X/FIXED_HDCP2X
#define HDMITX_AUDIO_DATA_BYPASS        DISABLED        //ENABLED/DISABLED for 121
#define HDMITX_AUDIO_NCTS_BYPASS        DISABLED        //ENABLED/DISABLED for 121
#define HDMITX_VRR_SUPPORT              DISABLED     //ENABLED/
#define HDMITX_CTS_SUPPORT              DISABLED        //ENABLED/DISABLED

#define DEBUG_HDMITX_EDID_PRINT_EN      ENABLED         //ENABLED/DISABLED
//=====================================HDMI TX=================================================


//=====================================Dsc======================================================

#define HDMIRX_DSC_DEC_SUPPORT          DISABLED//ENABLED/DISABLED
#define HDMIRX_DSC_MAX_FRL_RATE         FRL_10G4LANE     //FRL_NOT_SPT/FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMIRX_DSC_BYPASS_SUPPORT       DISABLED//ENABLED/DISABLED

#define DSC_USER_DEFINE_PKT_EN          DISABLED        //ENABLED/DISABLED//for compatibility to audio and pkt
#define HDMITX_DSC_ENC_SUPPORT          DISABLED        //ENABLED/DISABLED
#define HDMITX_DSC_MAX_FRL_RATE         FRL_10G4LANE     //FRL_NOT_SPT/FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMITX_DSC_BYPASS_SUPPORT       DISABLED        //ENABLED/DISABLED
#define HDMITX_DSC_MAX_SLICE_NUM        EIGHT_SLICE      //ONE_SLICE/TWO_SLICE/FOUR_SLICE/EIGHT_SLICE
#define HDMITX_DSC_OUT_BPP              BPP8            //BPP8/BPP10
//=====================================Dsc=================================================



#define          REMOVE_UART					DISABLED            //ENABLED/DISABLED

#if HDMITX_CTS_SUPPORT == ENABLED
#define MAXEDID_LENGTH                    1024
#else
#define MAXEDID_LENGTH                    512
#endif
//=====================================TOP=================================================
//audio 
#define TX_AUDIO_SEL                   RX_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define I2S_AUDIO_SEL                  NO_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define SPDIF_AUDIO_SEL                NO_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define EARC_TX_AUDIO_SEL              NO_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA

//csc
#define CSC_SUPPORT                    DISABLED        //ENABLED/DISABLED
#define CSC_RANGE_EN                   DISABLED        //ENABLED/DISABLED
#define CSC_TX_MODE                    YCbCr420_3      //RGB_0/YCbCr444_2/YCbCr422_1/YCbCr420_3

//other
#define HDR_SUPPORT                    ENABLED         //ENABLED/DISABLED
#define DOBLY_VISION_SUPPORT           DISABLED        //ENABLED/DISABLED
#define SPD_SUPPORT            	       DISABLED         //ENABLED/DISABLED
//=====================================TOP=================================================

//=====================================Type C=================================================
#define TYPECRX_EN                     DISABLED            //ENABLED/DISABLED
#define TYPECTX_EN                     DISABLED            //ENABLED/DISABLED


//=====================================BillBoard=================================================
#define BB_EN                        DISABLED           //ENABLED/DISABLED
//=====================================BillBoard=================================================

#endif

extern void LT86121GXE_HdmiRxVarInit(void);
extern void LT86121GXE_HdmiTxVarInit(void);
extern void LT86121GXE_PowerOnInit(void);
extern void LT86121GXE_Main_Scan(void);

extern void LT86121GXE_HdmiRxCscOrEncSel(void);
extern void LT86121GXE_HdmiRxMsgNotify(u8 ucEvent);
extern void LT86121GXE_HdmiTxMsgNotify(u8 ucEvent);


#endif
#endif


