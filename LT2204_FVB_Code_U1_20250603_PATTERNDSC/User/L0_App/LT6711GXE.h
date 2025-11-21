//////////////////////////////////////
//Project:   LT2204
//Filename:  Lt6711gxe.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _LT6711GXE_H
#define _LT6711GXE_H

#include "LtType.h"

#if CHIP_SEL == LT6711GXE

//#define        NVIDIA_FW_EN
#define        DEMO_FW_EN


#ifdef NVIDIA_FW_EN
#include "nvidia.h"
#endif




#ifdef DEMO_FW_EN
//-----------------------------------------UART-----------------------------------------------
#define UART_TX_PIN     GPIO21_UART_TX
#define UART_RX_PIN     GPIO16_MCLKA

//----------------------------------------PORT-------------------------------------------------
#define RX_PORT_SIGN    HDMI_PORT
#define TX_PORT_SIGN    DP_PORT

//=====================================HDMI RX=================================================
#define HDMIRX_FORCE_2BLOCKEDID         DISABLED        //ENABLED/DISABLED
#define HDMIRX_MAX_FRL_RATE             FRL_10G4LANE     //FRL_NOT_SPT/FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMIRX_HDCP_DEC_MODE            (HDCP1X+HDCP2X) //NO_HDCP/HDCP1X/HDCP2X/(HDCP1X+HDCP2X)
#define HDMIRX_HDCP_REPEATER            DISABLED        //ENABLED/DISABLED
#define HDMIRX_VRR_SUPPORT              ENABLED         //ENABLED/DISABLED
#define HDMIRX_EQ_STAGE                 EQ_16_STAGE     //EQ_16_STAGE/EQ_8_STAGE
#define HDMIRX_EQ_MODE                  HW_MODE         //HW_MODE/SW_MODE/FIX_MODE
#define HDMIRX_EQ_SCAN_MAX              3

#define DEBUG_HDMIRX_EDID_PRINT_EN      ENABLED        //ENABLED/DISABLED
//=====================================HDMI RX=================================================


//=====================================DP TX=================================================
#define DPTX_EDID_READ_EN               ENABLED         //ENABLED/DISABLED
#define DPTX_TRAINING_MAX_CNT           6//the max cnt for dp tx training
#define DPTX_MAX_LINK_RATE              HBR3            //HBR3/HBR2/HBR/RBR
#define DPTX_MAX_LANE_CNT               FOUR_LANE      //FOUR_LANE/TWO_LANE/ONE_LANE
#define DPTX_TPS3_SUPPORT               ENABLED        //ENABLED/DISABLED
#define DPTX_TPS4_SUPPORT               ENABLED        //ENABLED/DISABLED
#define DPTX_SCRAMBLE_SUPPORT           ENABLED         //ENABLED/DISABLED
#define DPTX_SSC_SUPPORT                DISABLED        //ENABLED/DISABLED
#define DPTX_FEC_ENC                    DISABLED        //ENABLED/DISABLED
#define DPTX_HDCP_ENC_MODE              HW_MODE         //NO_HDCP/HW_MODE/FIXED_HDCP1X/FIXED_HDCP2X
#define DPTX_HDCP_STATE_CHECK           DISABLED         //ENABLED/DISABLED
#define DPTX_ADAPTIVE_SYNC_SUPPORT      ENABLED         //ENABLED/DISABLED
#define DPTX_CTS_SUPPORT                DISABLED        //ENABLED/DISABLED
#define DPTX_AUDIO_DATA_BYPASS          DISABLED         //ENABLED/DISABLED
#define DPTX_LINKTRAIN_REDUCTION        DISABLED         //ENABLED/DISABLED
#define DPTX_AUTOMATED_CTS_SUPPORT      DISABLED         //ENABLED/DISABLED

#define DEBUG_DPTX_EDID_PRINT_EN        DISABLED        //ENABLED/DISABLED
//=====================================DP TX=================================================


//=====================================Dsc=================================================
#define HDMIRX_DSC_DEC_SUPPORT          ENABLED         //ENABLED/DISABLED
#define HDMIRX_DSC_MAX_FRL_RATE         FRL_10G4LANE     //FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMIRX_DSC_BYPASS_SUPPORT       ENABLED          //ENABLED/DISABLED
#define HDMIRX_DSC_BYPASS_HALFPIX_EN    ENABLED          //ENABLED/DISABLED

#define DPTX_DSC_ENC_SUPPORT            ENABLED         //ENABLED/DISABLED
#define DPTX_DSC_BYPASS_SUPPORT         ENABLED        //ENABLED/DISABLED

#define DPTX_DSC_MAX_SLICE_NUM          EIGHT_SLICE      //ONE_SLICE/TWO_SLICE/FOUR_SLICE/EIGHT_SLICE
#define DPTX_DSC_OUT_BPP                BPP8            //BPP8/BPP10
//=====================================Dsc=================================================
#define HDR10PLUS                      DISABLED         //ENABLED/DISABLED

//=====================================TOP=================================================
//audio
#define TX_AUDIO_SEL                   RX_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define I2S_AUDIO_SEL                  RX_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define SPDIF_AUDIO_SEL                NO_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define EARC_TX_AUDIO_SEL              NO_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA

//csc
#define CSC_SUPPORT                    ENABLED        //ENABLED/DISABLED
#define CSC_RANGE_EN                   DISABLED        //ENABLED/DISABLED

//other
#define HDR_SUPPORT                    ENABLED         //ENABLED/DISABLED
#define DOBLY_VISION_SUPPORT           DISABLED        //ENABLED/DISABLED
//=====================================TOP=================================================


//=====================================Typec tx=================================================

//#define TYPECRX_ROLE                   UFP_SINK         //UFP_SINK/DFP_SOURCE

#define TYPECTX_EN                     DISABLED         //ENABLED/DISABLED
#define TYPECTX_ROLE                   DFP_SOURCE       //UFP_SINK/DFP_SOURCE
#define TYPECTX_FRSWAP_EN              ENABLED          //ENABLED/DISABLED
#define TYPECTX_DCC_REQ_VOL            DEFAULT_5V       //DEFAULT_5V/MAX_VOLTAGE/DCC_USER_DEF_VOL
#define DCC_USER_DEF_VOL               15               //
#define TYPECTX_UCC_EN                 ENABLED          //ENABLED/DISABLED
#define TYPECTX_UCC_REQ_VOL            DEFAULT_5V       //DEFAULT_5V/MAX_VOLTAGE/UCC_USER_DEF_VOL
#define UCC_USER_DEF_VOL               15               //
//=====================================Typec tx=================================================


//=====================================BillBoard=================================================
#define BB_EN                          DISABLED           //ENABLED/DISABLED
//=====================================BillBoard=================================================


#define VBUS_DET                       DISABLED        //ENABLED/DISABLED
#define VCONNSWAP_SUPPORT              DISABLED        //ENABLED/DISABLED
#define UCCRequest_PointedVol          DISABLED             //ENABLED/DISABLED 
#define DCCRequest_PointedVol          DISABLED             //ENABLED/DISABLED 
#define PINE_SUPPORT                   DISABLED             //ENABLED/DISABLED
#define PDCTS_USE                      DISABLED             //ENABLED/DISABLED
#define PDVERSION                      PD30              //PD20/PD30/PD31
#define IICMASTER_EN                   DISABLED            //ENABLED/DISABLED 
#define UCC_EMARK_SUPPORT              DISABLED            //ENABLED/DISABLED 
#define DCC_TOGGLE_SUPPORT             DISABLED            //ENABLED/DISABLED 
#define HUB_RESET_CTRL                 DISABLED            //ENABLED/DISABLED
#define TYPECRX_EN                     DISABLED            //ENABLED/DISABLED
#define TYPEC_PRSWAP_EN                ENABLED            //ENABLED/DISABLED
#define TYPEC_DRSWAP_EN                ENABLED            //ENABLED/DISABLED
#define TYPEC_FRSWAP_EN                ENABLED            //FRTODUALPOWER/FRTOSOURCE/FRTOSINK/DISABLED
#define ET_2                           ENABLED            //ENABLED/DISABLED    
#define CCTRY_MODE                     NO_TRY            //NO_TRY/TRY_SRC/TRY_SNK
#define PD_PPS_EN                      DISABLED           //ENABLED/DISABLED
#define PD_CHUNK_EN                    DISABLED           //ENABLED/DISABLED
#define DCC_DET_WITHCC                 DISABLED            //ENABLED/DISABLED
#define NINTENDO_SWITCH                DISABLED             //ENABLED/DISABLED
#define NINTENDO_SWITCH_FORALL         DISABLED             //ENABLED/DISABLED
#define FORCE_NINTENDO_SWITCH          DISABLED             //ENABLED/DISABLED
#define NINTENDO_SWITCH_HDMIHPD        DISABLED             //ENABLED/DISABLED
#define NINTENDO_SWITCH_REPEATER       DISABLED             //ENABLED/DISABLED

#define POWER_REDUCE                   Watt_8             //Watt_0/Watt_5//Watt_8/Watt_10/Watt_12/Watt_15
#define IIC_WITH_SOC                   0x00              //TIMING/0x00
#define REMOVE_UART                    DISABLED            //ENABLED/DISABLED

#define DPRX_CDR_MODE                           ANACDR            //ANACDR/FULL_SPEED_DIGCDR/HALF_SPEED_DIGCDR


//#define SOURCE_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIOX, output_value)//TBD
//#define ADAPTER_GPIO_CTRL(output_value)         Drv_IOSoftLevel_Set(GPIOX, output_value)
//#define DISCSOURCE_GPIO_CTRL(output_value)      Drv_IOSoftLevel_Set(GPIOX, output_value)
//#define DISCADAPTER_GPIO_CTRL(output_value)     Drv_IOSoftLevel_Set(GPIOX, output_value)
//#define VCONN1_GPIO_CTRL(output_value)      	Drv_IOSoftLevel_Set(GPIOX, output_value)
//#define VCONN2_GPIO_CTRL(output_value)     		Drv_IOSoftLevel_Set(GPIOX, output_value)
// 不支持PD功能的话需要打开此部分的设置 
//#define SOURCE_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIO26_SD3B, output_value)
////#define SOURCE_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIO16_MCLKA, output_value)
//#define ADAPTER_GPIO_CTRL(output_value)         Drv_IOSoftLevel_Set(GPIOX, output_value)
//#define DISCSOURCE_GPIO_CTRL(output_value)      Drv_IOSoftLevel_Set(GPIOX, output_value)
//#define DISCADAPTER_GPIO_CTRL(output_value)     Drv_IOSoftLevel_Set(GPIOX, output_value)
//#define VCONN1_GPIO_CTRL(output_value)      	Drv_IOSoftLevel_Set(GPIO17_SCLKA, output_value)
//#define VCONN2_GPIO_CTRL(output_value)     		Drv_IOSoftLevel_Set(GPIO18_WSA, output_value)
//// 不支持PD功能的话需要打开此部分的设置 

 //支持PD功能的话需要打开此部分的设置 
#define SOURCE_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIO26_SD3B, output_value)
#define ADAPTER_GPIO_CTRL(output_value)         Drv_IOSoftLevel_Set(GPIO27_SD2B, output_value)
#define DISCSOURCE_GPIO_CTRL(output_value)      Drv_IOSoftLevel_Set(GPIO19_SD0A_VSYNC, output_value)
#define DISCADAPTER_GPIO_CTRL(output_value)     Drv_IOSoftLevel_Set(GPIO28_SD1B, output_value)
#define VCONN1_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIO17_SCLKA, output_value)
#define VCONN2_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIO18_WSA, output_value)
 //支持PD功能的话需要打开此部分的设置 


#define HubReset_GPIO_Ctrl(output_value)		(output_value == HIGH)?(BKF1_BB_REG|=BIT1_1):(BKF1_BB_REG&=BIT1_0)//TBD

#endif


extern void LT6711GXE_HdmiRxVarInit(void);
extern void LT6711GXE_DpTxVarInit(void);
extern void LT6711GXE_DpTxDpOrTypecDet(void);
extern void LT6711GXE_CCGpioInit(void);
extern void LT6711GXE_PowerOnInit(void);
extern void LT6711GXE_Main_Scan(void);

extern u8 LT6711GXE_NvidiaValue(void);
extern void LT6711GXE_HdmiRxCscOrEncSel(void);
extern void LT6711GXE_HdmiRxMsgNotify(u8 ucEvent);
extern void LT6711GXE_DpTxMsgNotify(u8 ucEvent);

#endif
#endif
