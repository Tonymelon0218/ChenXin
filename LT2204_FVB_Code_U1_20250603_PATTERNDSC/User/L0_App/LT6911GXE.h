//////////////////////////////////////
//Project:   LT2204
//Filename:  LT6911gxe.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _LT6911GXE_H
#define _LT6911GXE_H

#include "LtType.h"

#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD))

#define        DEMO_FW_EN




#ifdef DEMO_FW_EN
//-----------------------------------------register-------------------------------------------
#define USER_VIDEOEN_REG     BKE0_B0_REG
//-----------------------------------------UART-----------------------------------------------
#define UART_TX_PIN     		 GPIO21_UART_TX
#define UART_RX_PIN    			 GPIO16_MCLKA
//----------------------------------------PORT-------------------------------------------------
#define RX_PORT_SIGN    		 HDMI_PORT//HDMI_PORT/DP_PORT
#define TX_PORT_SIGN   			 MIPI_PORT//LVDS_PORT/MIPI_PORT




//Load EDID from Flash , Flash Address 0x70000
#define EDID_FLASH                      DISABLED
//PWM
#define PWM_OUT                				  DISABLED//DISABLED or ENABLED
#define PWM_GPIO                				GPIO20_PWM0//GPIO20_PWM0,GPIO22_PWM1,GPIO24_PWM2,GPIO25_PWM3,
#define PWM_FREQ                				1//KHZ
#define PWM_DUTY                				50//0~100%
#define PWM_DUTY_REG           				  BKE0_B1_REG
//=====================================HDMI RX=================================================
#define HDMIRX_FORCE_2BLOCKEDID         DISABLED        //ENABLED/DISABLED
#define HDMIRX_MAX_FRL_RATE             FRL_8G4LANE     //FRL_NOT_SPT/FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMIRX_HDCP_DEC_MODE            (NO_HDCP) //NO_HDCP/HDCP1X/HDCP2X/(HDCP1X+HDCP2X)
#define HDMIRX_HDCP_REPEATER            DISABLED        //ENABLED/DISABLED
#define HDMIRX_VRR_SUPPORT              DISABLED        //ENABLED/DISABLED
#define HDMIRX_EQ_STAGE                 EQ_16_STAGE     //EQ_16_STAGE/EQ_8_STAGE
#define HDMIRX_EQ_MODE                  HW_MODE         //HW_MODE/SW_MODE/FIX_MODE
#define HDMIRX_EQ_SCAN_MAX              2
#define HDR10PLUS                      DISABLED         //ENABLED/DISABLED
#define DEBUG_HDMIRX_EDID_PRINT_EN      DISABLED        //ENABLED/DISABLED
//=====================================HDMI RX=================================================

//=====================================Dsc=================================================
#define HDMIRX_DSC_DEC_SUPPORT          DISABLED//ENABLED/DISABLED
#define HDMIRX_DSC_MAX_FRL_RATE         FRL_8G4LANE     //FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMIRX_DSC_BYPASS_SUPPORT       ENABLED//ENABLED/DISABLED
#define HDMIRX_DSC_BYPASS_HALFPIX_EN    DISABLED          //ENABLED/DISABLED

#define MIPITX_DSC_ENC_EN               DISABLED        //ENABLED/DISABLED
#define MIPITX_DSC_RATIO                THREE_RATIO     //TWO_RATIO/THREE_RATIO/FOUR_RATIO
#define MIPITX_DSC_SLICE_NUM            FOUR_SLICE      //ONE_SLICE/TWO_SLICE/FOUR_SLICE
#define MIPITX_DSC_OUT_BPP              BPP8            //BPP8/BPP10
//=====================================Dsc=================================================




//=====================================TOP=================================================
//audio
#define TX_AUDIO_SEL                    RX_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define I2S_AUDIO_SEL                   RX_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define SPDIF_AUDIO_SEL                 NO_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define EARC_TX_AUDIO_SEL               NO_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA

#define TDM_SUPPORT                     DISABLED         //ENABLED/DISABLED
//csc
#define CSC_SUPPORT                     ENABLED        //ENABLED/DISABLED
#define CSC_RANGE_EN                    DISABLED        //ENABLED/DISABLED
#define CSC_TX_MODE                     YCbCr420_3      //RGB_0/YCbCr444_2/YCbCr422_1/YCbCr420_3

//other
#define HDR_SUPPORT                    	ENABLED         //ENABLED/DISABLED
#define DOBLY_VISION_SUPPORT            DISABLED        //ENABLED/DISABLED

//=====================================TOP=================================================

//=====================================Type C=================================================
#define TYPECRX_EN                      DISABLED            //ENABLED/DISABLED
#define TYPECTX_EN                      DISABLED            //ENABLED/DISABLED
#define ET_2                            DISABLED
#define TYPEC_FRSWAP_EN                 DISABLED
//=====================================Type C=================================================


//=====================================BillBoard=================================================
#define BB_EN                           DISABLED           //ENABLED/DISABLED
//=====================================BillBoard=================================================

#endif

extern u8 g_HdmirxVedioChangeFlag;

extern void LT6911GXE_HdmiRxVarInit(void);
extern void LT6911GXE_PowerOnInit(void);
extern void LT6911GXE_Main_Scan(void);

extern void LT6911GXE_HdmiRxCscCvt(void);
extern void LT6911GXE_HdmiRxCscOrEncSel(void);
extern void LT6911GXE_HdmiRxMsgNotify(u8 ucEvent);
extern void LT6911GXE_GPIO_Init(void);

#endif
#endif


