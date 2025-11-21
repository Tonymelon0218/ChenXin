//////////////////////////////////////
//Project:   LT2101
//Filename:  main.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////

#include "LtType.h"
#if CHIP_SEL == LT6711GXE

#ifdef NVIDIA_FW_EN

#define CUSTOMER_DEFINED               ENABLED         //ENABLED/DISABLED
#define EDID_DDC_DIS                   ENABLED        //ENABLED/DISABLED

#define SLEEP_MODE                     ENABLED         //ENABLED/DISABLED
#define SOFT_POWER_DOWN                ENABLED         //ENABLED/DISABLED

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

#define DEBUG_HDMIRX_EDID_PRINT_EN      DISABLED        //ENABLED/DISABLED
//=====================================HDMI RX=================================================


//=====================================DP TX=================================================
#define DPTX_EDID_READ_EN               DISABLED         //ENABLED/DISABLED
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
#define DPTX_CTS_SUPPORT                ENABLED        //ENABLED/DISABLED
#define DPTX_AUDIO_DATA_BYPASS          DISABLED         //ENABLED/DISABLED
#define DPTX_LINKTRAIN_REDUCTION        DISABLED         //ENABLED/DISABLED
#define DPTX_AUTOMATED_CTS_SUPPORT      DISABLED         //ENABLED/DISABLED

#define DEBUG_DPTX_EDID_PRINT_EN        DISABLED         //ENABLED/DISABLED
//=====================================DP TX=================================================


//=====================================Dsc=================================================
#define HDMIRX_DSC_DEC_SUPPORT          DISABLED//ENABLED/DISABLED
#define HDMIRX_DSC_MAX_FRL_RATE         FRL_10G4LANE     //FRL_3G3LANE/FRL_6G3LANE/FRL_6G4LANE/FRL_8G4LANE/FRL_10G4LANE//FRL_12G4LANE
#define HDMIRX_DSC_BYPASS_SUPPORT       DISABLED          //ENABLED/DISABLED
#define HDMIRX_DSC_BYPASS_HALFPIX_EN    DISABLED          //ENABLED/DISABLED

#define DPTX_DSC_ENC_SUPPORT            ENABLED         //ENABLED/DISABLED
#define DPTX_DSC_BYPASS_SUPPORT         DISABLED        //ENABLED/DISABLED
#define DPTX_DSC_MAX_SLICE_NUM          FOUR_SLICE      //ONE_SLICE/TWO_SLICE/FOUR_SLICE/EIGHT_SLICE
#define DPTX_DSC_OUT_BPP                BPP8            //BPP8/BPP10
//=====================================Dsc=================================================


//=====================================TOP=================================================
//audio
#define TX_AUDIO_SEL                   RX_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define I2S_AUDIO_SEL                  NO_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define SPDIF_AUDIO_SEL                NO_AUDIO_DATA   //RX_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA
#define EARC_TX_AUDIO_SEL              NO_AUDIO_DATA   //RX_AUDIO_DATA/I2S_AUDIO_DATA/SPDIF_AUDIO_DATA/PATTERN_AUDIO_DATA/NO_AUDIO_DATA

//csc
#define CSC_SUPPORT                    ENABLED        //ENABLED/DISABLED
#define CSC_RANGE_EN                   DISABLED        //ENABLED/DISABLED
#define CSC_TX_MODE                    YCbCr420_3      //RGB_0/YCbCr444_2/YCbCr422_1/YCbCr420_3

//other
#define HDR_SUPPORT                    ENABLED         //ENABLED/DISABLED
#define DOBLY_VISION_SUPPORT           DISABLED        //ENABLED/DISABLED
//=====================================TOP=================================================


//=====================================Typec tx=================================================
#define TYPECRX_EN                     DISABLED         //ENABLED/DISABLED
#define TYPECRX_ROLE                   UFP_SINK         //UFP_SINK/DFP_SOURCE

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

#endif


#endif
