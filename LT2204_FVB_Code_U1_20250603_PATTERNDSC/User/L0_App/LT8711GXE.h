//////////////////////////////////////
//Project:   LT2204
//Filename:  Lt8711gxe.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _LT8711GXE_H
#define _LT8711GXE_H

#include "LtType.h"

#if CHIP_SEL == LT8711GXE


#define        DEMO_FW_EN


#ifdef DEMO_FW_EN
//-----------------------------------------UART-----------------------------------------------
#define UART_TX_PIN     GPIO21_UART_TX
#define UART_RX_PIN     GPIO16_MCLKA
//----------------------------------------PORT-------------------------------------------------
#define RX_PORT_SIGN    DP_PORT   
#define TX_PORT_SIGN    HDMI_PORT 


//=====================================DP RX=================================================

#define DPRX_LINK_RATE                  HBR3      //HBR3/HBR2/HBR/RBR
#define DPRX_LANE_COUNT                 FOUR_LANE//FOUR_LANE/TWO_LANE/ONE_LANE
#define DPRX_TPS3_SUPPORT_EN            ENABLED//ENABLED/DISABLED
#define DPRX_TPS4_SUPPORT_EN            ENABLED//ENABLED/DISABLED
#define DPRX_SSC_SUPPORT_EN             ENABLED//ENABLED/DISABLED
#define DPRX_FEC_SUPPORT                ENABLED//ENABLED/DISABLED
#define DPRX_SWING_MIN_LEVEL            LEVEL_1//LEVEL_0/LEVEL_1/LEVEL_2/LEVEL_3
#define DPRX_EQ_SCAN_MODE               SW_SCANVALIDEQ_EXT//HW_MODE/FIX_MODE/SW_SCANALLEQ/SW_SCANMIDEQ/SW_SCANVALIDEQ/SW_SCANVALIDEQ_EXT
#define DPRX_HDCP_DEC_MODE              (HDCP1X+HDCP2X)//NO_HDCP/HDCP1X/HDCP2X/(HDCP1X+HDCP2X)
#define DPRX_HDCP_REPEATER              DISABLED//ENABLED/DISABLED
#define DPRX_TIMING_HBE                 DISABLED//ENABLED/DISABLED timing for Horizontal Blanking Expansion
#define DPRX_LINK_CTS                   DISABLED//ENABLED/DISABLED 
#define DPRX_DFP_TYPE                   BRANCH_DP//BRANCH_HDMI/BRANCH_DP 
#define DPRX_VERSION                    DP1_4//DP1_0/DP1_1/DP1_2/DP1_3/DP1_4
#define DPRX_ADAPTIVE_SYNC              DISABLED//ENABLED/DISABLED
#define DPRX_ADAPTIVE_SYNC_WITHOUT_SDP  DISABLED//ENABLED/DISABLED
#define DPRX_MST_MODE_EN                DISABLED//ENABLED/DISABLED
#define DPRX_MST_SINK_CNT               1
#define DPRX_MST_DSC_NUM                1
#define DPRX_CDR_MODE                   ANACDR//ANACDR/FULL_SPEED_DIGCDR/HALF_SPEED_DIGCDR                   
 
#define	DPRX_AUX_MODE					SOFTMODE//HARDWARE/SOFTMODE/MIXEDMODE

#define DPRX_PCRPLL_HRST                ENABLED//ENABLED/DISABLED

#define DEBUG_DPRX_EDID_PRINT_EN        ENABLED//ENABLED/DISABLED
//=====================================DP RX===================================================


//=====================================HDMI TX=================================================
#define HDMITX_EDID_READ_EN             ENABLED         //ENABLED/DISABLED
#define HDMITX_MAX_FRL_RATE             FRL_10G4LANE    //FRL_NOT_SPT/FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMITX_MAX_FFE_LEVEL            LEVEL_0         //LEVEL_0/LEVEL_1/LEVEL_2/LEVEL_3
#define HDMITX_HDCP_ENC_MODE            HW_MODE     //NO_HDCP/HW_MODE/FIXED_HDCP1X/FIXED_HDCP2X
#define HDMITX_AUDIO_DATA_BYPASS        DISABLED     //ENABLED/DISABLED for 121
#define HDMITX_AUDIO_NCTS_BYPASS        DISABLED        //ENABLED/DISABLED for 121
#define HDMITX_VRR_SUPPORT              DISABLED     //ENABLED/
#define HDMITX_CTS_SUPPORT              ENABLED         //ENABLED/DISABLED

#define DEBUG_HDMITX_EDID_PRINT_EN      ENABLED         //ENABLED/DISABLED
//=====================================HDMI TX=================================================


//=====================================Dsc=================================================
#define DPRX_DSC_DEC_SUPPORT            ENABLED//ENABLED/DISABLED
#define DPRX_DSC_BYPASS_SUPPORT         DISABLED//ENABLED/DISABLED

#define HDMITX_DSC_ENC_SUPPORT          DISABLED        //ENABLED/DISABLED
#define HDMITX_DSC_BYPASS_SUPPORT       DISABLED        //ENABLED/DISABLED

#define HDMITX_DSC_MAX_FRL_RATE         FRL_10G4LANE    //FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMITX_DSC_SLICE_NUM            FOUR_SLICE      //ONE_SLICE/TWO_SLICE/FOUR_SLICE/EIGHT_SLICE
#define HDMITX_DSC_OUT_BPP              BPP8            //BPP8/BPP10
#define HDMITX_DSC_MAX_SLICE_NUM        FOUR_SLICE      //ONE_SLICE/TWO_SLICE/FOUR_SLICE/EIGHT_SLICE
//=====================================Dsc=================================================


//=====================================TOP=================================================
//audio
#define TX_AUDIO_SEL                    RX_AUDIO_DATA   //RX_AUDIO_DATA/I2SIN_AUDIO_DATA/SPDIFIN_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define I2S_AUDIO_SEL                   RX_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define SPDIF_AUDIO_SEL                 NO_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define EARC_TX_AUDIO_SEL               NO_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA

//csc
#define CSC_SUPPORT                     ENABLED        //ENABLED/DISABLED
#define CSC_RANGE_EN                    DISABLED        //ENABLED/DISABLED
#define CSC_TX_MODE                     YCbCr420_3      //RGB_0/YCbCr444_2/YCbCr422_1/YCbCr420_3

//other
#define HDR_SUPPORT                     ENABLED         //ENABLED/DISABLED
#define DOBLY_VISION_SUPPORT            ENABLED        //ENABLED/DISABLED
#define SPD_SUPPORT            			ENABLED        //ENABLED/DISABLED

//=====================================TOP=================================================


//=====================================BillBoard=================================================
#define BB_EN                            DISABLED           //ENABLED/DISABLED
//=====================================BillBoard=================================================

#define TYPECTX_EN                       ENABLED            //ENABLED/DISABLED

//=====================================Type C=================================================


//=====================================Not used =================================================
#define DEBUG_HDMIRX_EDID_PRINT_EN       DISABLED //ENABLED/DISABLED
#define HDMIRX_DSC_DEC_SUPPORT           DISABLED//ENABLED/DISABLED
#define HDMIRX_DSC_BYPASS_SUPPORT        DISABLED//ENABLED/DISABLED
#define DSC_USER_DEFINE_PKT_EN           DISABLED//ENABLED/DISABLED//for compatibility to audio and pkt


#define VBUS_DET                         DISABLED        //ENABLED/DISABLED
#define VCONNSWAP_SUPPORT                DISABLED        //ENABLED/DISABLED
#define UCCRequest_PointedVol            DISABLED             //ENABLED/DISABLED 
#define DCCRequest_PointedVol            DISABLED             //ENABLED/DISABLED 
#define PINE_SUPPORT                     DISABLED             //ENABLED/DISABLED
#define PDCTS_USE                        DISABLED             //ENABLED/DISABLED

#define PDVERSION						PD30              //PD20/PD30/PD31

#define IICMASTER_EN                   DISABLED            //ENABLED/DISABLED 
#define UCC_EMARK_SUPPORT              ENABLED            //ENABLED/DISABLED 
#define DCC_TOGGLE_SUPPORT             DISABLED            //ENABLED/DISABLED 
#define HUB_RESET_CTRL                 ENABLED            //ENABLED/DISABLED
#define TYPECRX_EN                     ENABLED            //ENABLED/DISABLED
#define TYPEC_PRSWAP_EN                ENABLED            //ENABLED/DISABLED
#define TYPEC_DRSWAP_EN                ENABLED            //ENABLED/DISABLED
#define TYPEC_FRSWAP_EN                ENABLED            //ENABLED/DISABLED
#define ET_2                           ENABLED            //ENABLED/DISABLED
#define CCTRY_MODE					   NO_TRY            //NO_TRY/TRY_SRC/TRY_SNK
#define PD_PPS_EN                      DISABLED           //ENABLED/DISABLED
#define PD_CHUNK_EN                    DISABLED           //ENABLED/DISABLED
#define DCC_DET_WITHCC                 DISABLED            //ENABLED/DISABLED
#define NINTENDO_SWITCH                DISABLED             //ENABLED/DISABLED
#define NINTENDO_SWITCH_FORALL         DISABLED             //ENABLED/DISABLED
#define FORCE_NINTENDO_SWITCH          DISABLED             //ENABLED/DISABLED
#define NINTENDO_SWITCH_HDMIHPD        DISABLED             //ENABLED/DISABLED
#define NINTENDO_SWITCH_REPEATER       DISABLED             //ENABLED/DISABLED

#define          POWER_REDUCE                   Watt_8             //Watt_0/Watt_5//Watt_8/Watt_10/Watt_12/Watt_15
#define          IIC_WITH_SOC                   0x00              //TIMING/0x00
#define          REMOVE_UART					DISABLED            //ENABLED/DISABLED

#if HDMITX_CTS_SUPPORT == ENABLED
#define MAXEDID_LENGTH                    1024
#else
#define MAXEDID_LENGTH                    512
#endif

#define SOURCE_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIO26_SD3B, output_value)
#define ADAPTER_GPIO_CTRL(output_value)         Drv_IOSoftLevel_Set(GPIO27_SD2B, output_value)
#define DISCSOURCE_GPIO_CTRL(output_value)      Drv_IOSoftLevel_Set(GPIO19_SD0A_VSYNC, output_value)
#define DISCADAPTER_GPIO_CTRL(output_value)     Drv_IOSoftLevel_Set(GPIO28_SD1B, output_value)
#define VCONN1_GPIO_CTRL(output_value)      	Drv_IOSoftLevel_Set(GPIO17_SCLKA, output_value)
#define VCONN2_GPIO_CTRL(output_value)     		Drv_IOSoftLevel_Set(GPIO18_WSA, output_value)


#define HubReset_GPIO_Ctrl(output_value)		(output_value == HIGH)?(BKF1_BB_REG|=BIT1_1):(BKF1_BB_REG&=BIT1_0)
#endif
extern void LT8711GXE_DpRxVarInit(void);
extern void LT8711GXE_HdmiTxVarInit(void);
extern void LT8711GXE_CCGpioInit(void);
extern void LT8711GXE_DpRxDpOrTypecDet(void);
extern void LT8711GXE_PowerOnInit(void);
extern void LT8711GXE_Main_Scan(void);

extern void LT8711GXE_DpRxCscOrEncSel(void);
extern void LT8711GXE_DpRxMsgNotify(u8 ucEvent);
extern void LT8711GXE_HdmiTxMsgNotify(u8 ucEvent);
#endif
#endif



