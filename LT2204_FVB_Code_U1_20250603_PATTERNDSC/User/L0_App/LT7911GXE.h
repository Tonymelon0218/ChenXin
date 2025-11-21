//////////////////////////////////////
//Project:   LT2204
//Filename:  LT7911GXE.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _LT7911GXE_H
#define _LT7911GXE_H

#include "LtType.h"

#if ((CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))

#define        DEMO_FW_EN


#ifdef DEMO_FW_EN
//-----------------------------------------custom-------------------------------------------
#define CUSTOM_EDID_SWITCH      DISABLED//ENABLED/DISABLED
//-----------------------------------------register-------------------------------------------
#define USER_VIDEOEN_REG     BKE0_B0_REG
#define EDID_SWITCH_REG      BKE0_B2_REG
#define MIPITX_HSCMD_REG     BKE0_C0_REG
//-----------------------------------------UART-----------------------------------------------
#define UART_TX_PIN     GPIO21_UART_TX
#define UART_RX_PIN     GPIO16_MCLKA
//----------------------------------------PORT-------------------------------------------------
#define RX_PORT_SIGN    DP_PORT   
#define TX_PORT_SIGN    MIPI_PORT //LVDS_PORT/MIPI_PORT

#define BRIGHTNESS_UP_GPIO      GPIO25_PWM3 //(BKE5_A8_REG & 0x01)
#define BRIGHTNESS_DOWN_GPIO    GPIO24_PWM2//(BKE5_A8_REG & 0x02)

//Load EDID from Flash , Flash Address 0x70000
#define EDID_FLASH                       DISABLED
//PWM
#define PWM_OUT                 ENABLED//DISABLED or ENABLED
#define PWM_GPIO                GPIO24_PWM2//GPIO20_PWM0,GPIO22_PWM1,GPIO24_PWM2,GPIO25_PWM3,
#define PWM_FREQ                1//KHZ
#define PWM_DUTY                50//0~100%
#define PWM_DUTY_REG            BKE0_B1_REG

//=====================================DP RX=================================================

#define DPRX_LINK_RATE                   HBR2//HBR3/HBR2/HBR/RBR
#define DPRX_LANE_COUNT                  FOUR_LANE//FOUR_LANE/TWO_LANE/ONE_LANE
#define DPRX_TPS3_SUPPORT_EN             ENABLED//ENABLED/DISABLED
#define DPRX_TPS4_SUPPORT_EN             ENABLED//ENABLED/DISABLED
#define DPRX_SSC_SUPPORT_EN              ENABLED//ENABLED/DISABLED
#define DPRX_FEC_SUPPORT                 DISABLED
#define DPRX_SWING_MIN_LEVEL             LEVEL_1//LEVEL_0/LEVEL_1/LEVEL_2/LEVEL_3
#define DPRX_EQ_SCAN_MODE                SW_SCANVALIDEQ_EXT//HW_MODE/FIX_MODE/SW_SCANALLEQ/SW_SCANMIDEQ/SW_SCANVALIDEQ/SW_SCANVALIDEQ_EXT
#define DPRX_HDCP_DEC_MODE               NO_HDCP//NO_HDCP/HDCP1X/HDCP2X/(HDCP1X+HDCP2X)
#define DPRX_HDCP_REPEATER               DISABLED//ENABLED/DISABLED
#define DPRX_TIMING_HBE                  DISABLED//ENABLED/DISABLED timing for Horizontal Blanking Expansion
#define DPRX_LINK_CTS                    DISABLED//ENABLED/DISABLED 
#define DPRX_DFP_TYPE                    BRANCH_DP//BRANCH_HDMI/BRANCH_DP 
#define DPRX_VERSION                     DP1_4//DP1_0/DP1_1/DP1_2/DP1_3/DP1_4

#define DPRX_MST_MODE_EN                 DISABLED//ENABLED/DISABLED
#define DPRX_MST_SINK_CNT                1
#define DPRX_MST_DSC_NUM                 1
#define DPRX_CDR_MODE                    ANACDR  //ANACDR/FULL_SPEED_DIGCDR/HALF_SPEED_DIGCDR

#define DPRX_AUX_MODE                    SOFTMODE//HARDWARE/SOFTMODE/MIXEDMODE

#define DPRX_PCRPLL_HRST                ENABLED//ENABLED/DISABLED

#define DEBUG_DPRX_EDID_PRINT_EN         DISABLED//ENABLED/DISABLED
//=====================================DP RX=================================================

//=====================================Dsc=================================================
#define DPRX_DSC_DEC_SUPPORT            DISABLED        //ENABLED/DISABLED
#define DPRX_DSC_BYPASS_SUPPORT         DISABLED        //ENABLED/DISABLED

#define MIPITX_DSC_ENC_EN               DISABLED        //ENABLED/DISABLED
#define MIPITX_DSC_RATIO                THREE_RATIO     //TWO_RATIO/THREE_RATIO/FOUR_RATIO
#define MIPITX_DSC_SLICE_NUM            FOUR_SLICE      //ONE_SLICE/TWO_SLICE/FOUR_SLICE
#define MIPITX_DSC_OUT_BPP              BPP8            //BPP8/BPP10
//=========================================================================================


//=====================================TOP=================================================
//audio
#define TX_AUDIO_SEL                   RX_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define I2S_AUDIO_SEL                  RX_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define SPDIF_AUDIO_SEL                NO_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define EARC_TX_AUDIO_SEL              NO_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA

#define TDM_SUPPORT                    DISABLED         //ENABLED/DISABLED
//1.8V I2S_GPIO
#define GPIO_1P8V                      DISABLED					//ENABLED/DISABLED

//csc
#define CSC_SUPPORT                    DISABLED        //ENABLED/DISABLED
#define CSC_RANGE_EN                   DISABLED        //ENABLED/DISABLED
#define CSC_TX_MODE                    YCbCr420_3      //RGB_0/YCbCr444_2/YCbCr422_1/YCbCr420_3

//other
#define HDR_SUPPORT                    DISABLED         //ENABLED/DISABLED
#define DOBLY_VISION_SUPPORT           DISABLED         //ENABLED/DISABLED
#define SPD_SUPPORT                    DISABLED         //ENABLED/DISABLED
#define DPRX_ADAPTIVE_SYNC             DISABLED         //ENABLED/DISABLED

//=====================================TOP=================================================


//=====================================BillBoard=================================================
#define BB_EN                           DISABLED           //ENABLED/DISABLED
//=====================================BillBoard=================================================

#define TYPECTX_EN                      DISABLED           //ENABLED/DISABLED

//=====================================Type C=================================================
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
#define HUB_RESET_CTRL                 DISABLED            //ENABLED/DISABLED
#define TYPECRX_EN                     DISABLED            //ENABLED/DISABLED
#define TYPEC_PRSWAP_EN                DISABLED            //ENABLED/DISABLED
#define TYPEC_DRSWAP_EN                DISABLED            //ENABLED/DISABLED
#define TYPEC_FRSWAP_EN                DISABLED            //ENABLED/DISABLED
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

/**************LT7911UXE BGA169 EVB PD Control IO******************/
#if CHIP_SEL == LT7911UXE_DP
#define SOURCE_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIO24_PWM2, output_value)//GPIO24
#define ADAPTER_GPIO_CTRL(output_value)         Drv_IOSoftLevel_Set(GPIO25_PWM3, output_value)//GPIO25
#define DISCSOURCE_GPIO_CTRL(output_value)      Drv_IOSoftLevel_Set(GPIO4_SPDIFA, output_value)//GPIO4
#define DISCADAPTER_GPIO_CTRL(output_value)     Drv_IOSoftLevel_Set(GPIO16_MCLKA, output_value)//GPIO16
#define VCONN1_GPIO_CTRL(output_value)      	  Drv_IOSoftLevel_Set(GPIO17_SCLKA, output_value)//GPIO17
#define VCONN2_GPIO_CTRL(output_value)     		  Drv_IOSoftLevel_Set(GPIO18_WSA, output_value)//GPIO18

#define HubReset_GPIO_Ctrl(output_value)		    Drv_IOSoftLevel_Set(GPIO0_EARCN, output_value)//GPIO0//TBD
#endif

/**************LT6911GXD EVB PD Control IO******************/
#if CHIP_SEL == LT6911GXD_DP
#define SOURCE_GPIO_CTRL(output_value)          Drv_IOSoftLevel_Set(GPIO26_SD3B, output_value)//GPIO26
#define ADAPTER_GPIO_CTRL(output_value)         Drv_IOSoftLevel_Set(GPIO27_SD2B, output_value)//GPIO27
#define DISCSOURCE_GPIO_CTRL(output_value)      Drv_IOSoftLevel_Set(GPIO19_SD0A_VSYNC, output_value)//GPIO19
#define DISCADAPTER_GPIO_CTRL(output_value)     Drv_IOSoftLevel_Set(GPIO28_SD1B, output_value)//GPIO28
#define VCONN1_GPIO_CTRL(output_value)      	  Drv_IOSoftLevel_Set(GPIO0_EARCN, output_value)//GPIO0
#define VCONN2_GPIO_CTRL(output_value)     		  Drv_IOSoftLevel_Set(GPIO1_EARCP, output_value)//GPIO1

#define HubReset_GPIO_Ctrl(output_value)		    Drv_IOSoftLevel_Set(GPIOX, output_value)//GPIO0//TBD
#endif

#endif


extern void LT7911GXE_DpRxVarInit(void);
extern void LT7911GXE_CCGpioInit(void);
extern void LT7911GXE_DpRxDpOrTypecDet(void);
extern void LT7911GXE_PowerOnInit(void);
extern void LT7911GXE_Main_Scan(void);

extern void LT7911GXE_DpRxCscOrEncSel(void);
extern void LT7911GXE_DpRxCscCvt(void);
extern void LT7911GXE_DpRxMsgNotify(u8 ucEvent);
extern void LT7911GXE_I2SGPIO_Init(void);
#if TX_PORT_SIGN == MIPI_PORT		
extern void App_Brightness_Init(void);
#endif
#endif
#endif

