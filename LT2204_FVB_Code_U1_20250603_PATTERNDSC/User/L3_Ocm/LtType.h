//////////////////////////////////////
//Project:   LT2101
//Filename:  LtType.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _LTTYPE_H
#define _LTTYPE_H

#define IN
#define OUT
#define INOUT

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
#define DATA              data
#define BDATA             bdata
#define IDATA             idata
#define PDATA             pdata
#define XDATA             xdata
#define RDATA             code

#define CBYTE             ((unsigned char volatile code  *) 0)
#define DBYTE             ((unsigned char volatile data  *) 0)
#define PBYTE             ((unsigned char volatile pdata *) 0)
#define XBYTE             ((unsigned char volatile xdata *) 0)
#define IBYTE             ((unsigned char volatile idata *) 0)
typedef enum bool_tag
{
    FALSE = 0,
    TRUE = !FALSE,
}bool;//default sizeof 1

//set register bit M is 1, M->0~7
#define SET_BIT(__REGISTER__,__M__)  \
    do{  __REGISTER__ |= (1 << __M__);  }while(0)

//set REGISTER bit M is 0, M->0~7
#define CLEAR_BIT(__REGISTER__, __M__)  \
    do{  __REGISTER__ &= (~(1 << __M__));  }while(0)

//set register bit 1 [M,N], M,N->0~7, M > N
#define SET_BITS(__REGISTER__,__M__,__N__)  \
    do{  __REGISTER__|=((0xffU>>(7-__M__+__N__))<<__N__); }while(0)

//clear register bit [M,N], M,N->0~7, M > N
#define CLEAR_BITS(__REGISTER__,__M__,__N__)  \
    do{ __REGISTER__ &= (~((0xffU >> (7 - __M__ + __N__)) << __N__)); }while(0)

//set value REGISTER from bit M to bit N is NEW, M,N -> 0 ~ 7, M > N, NEW < bit(M - N + 1)
#define LET_BITS(__REGISTER__, __M__, __N__, __NEW__)\
    do{\
        CLEAR_BITS(__REGISTER__, __M__, __N__);\
        __REGISTER__ |= (__NEW__ << __N__);\
    }while(0)

//get value REGISTER from bit M, M-> 0 ~ 7
#define GET_BIT(__REGISTER__, __M__)  (((__REGISTER__) & (1 << (__M__))) >> (__M__))

//get value REGISTER from bit M to bit N, M,N -> 0 ~ 7, M > N
#define GET_BITS(__REGISTER__, __M__, __N__)  \
        (((__REGISTER__) & (~(~(0U)<<((__M__)-(__N__)+1))<<(__N__)))>> (__N__)) 

#define CHK_SET_BIT(__CONDITION__,__REGISTER__,__BIT__) \
    do{\
        if (__CONDITION__){\
            SET_BIT(__REGISTER__,__BIT__);\
        }else{\
            CLEAR_BIT(__REGISTER__, __BIT__);\
        }\
    }while(0)
    

#define PACK_16_BIT(__M__, __N__) \
                (((unsigned short)(__M__) << 8) + (__N__))
#define PACK_24_BIT(__M__, __N__, __O__) \
                (((unsigned long)(__M__) << 16) + ((unsigned long)(__N__) << 8) + (__O__))
#define PACK_32_BIT(__M__, __N__, __O__, __P__)  \
                (((unsigned long)(__M__) << 24) + ((unsigned long)(__N__) << 16) + ((unsigned long)(__O__) << 8) + (__P__))

#define    GET_16BIT_LOW(__M__)  (((__M__) >>  0) & 0xff)  
#define    GET_16BIT_HIGH(__M__) (((__M__) >>  8) & 0xff)

#define BIT0  0
#define BIT1  1
#define BIT2  2
#define BIT3  3
#define BIT4  4
#define BIT5  5
#define BIT6  6
#define BIT7  7

#ifndef min
#define min(a,b) (((a)<(b))? (a):(b))
#endif
    
#ifndef max
#define max(a,b) (((a)>(b))? (a):(b))
#endif

#define BIT0_1  0x01
#define BIT1_1  0x02
#define BIT2_1  0x04
#define BIT3_1  0x08
#define BIT4_1  0x10
#define BIT5_1  0x20
#define BIT6_1  0x40
#define BIT7_1  0x80

#define BIT0_0  0xfe
#define BIT1_0  0xfd
#define BIT2_0  0xfb
#define BIT3_0  0xf7
#define BIT4_0  0xef
#define BIT5_0  0xdf
#define BIT6_0  0xbf
#define BIT7_0  0x7f

#define DATA    data
#define BDATA   bdata
#define IDATA   idata
#define PDATA   pdata
#define XDATA   xdata
#define RDATA   code

#define LT6711GXE        0
#define LT8711GXE        1
#define LT6911GXD_HD     2
#define LT7911UXE_DP     3
#define LT86121GXE       4
#define LT7911UXE_HD     5
#define LT6911GXD_DP     6

#define U1_VERSION      0
#define U2_VERSION      1
#define U3_VERSION      2

#define HALF_PIX_CLK    0x00
#define PIX_CLK         0x01

//dsc
#define NOT_SUPPORT     0x00
#define NO_PPS_PKT      0x01
#define PPS_ERROR       0x02
#define NOT_RUNNING     0x03
#define CAN_RUNNING     0x04

//hdmi
#define FRL_NOT_SPT     0
#define FRL_3G3LANE     1
#define FRL_6G3LANE     2
#define FRL_6G4LANE     3
#define FRL_8G4LANE     4
#define FRL_10G4LANE    5
#define FRL_12G4LANE    6

#define HDMI14      0//hdmi14
#define HDMI20      1//hdmi20
#define HDMI21      2//hdmi21

#define DVI_MODE      0
#define HDMI_MODE     1

#define FFE_FINISH      0x01
#define FFE_CHANGE      0x02
#define FFE_FAILED      0x03

#define TEST_PATTERN        0x01
#define TRAIN_PATTERN       0x02
#define CHANGE_PATTERN      0x03
#define FAILED_PATTERN      0x04
#define FINISH_PATTERN      0x05
#define NOTQUEST_PATTERN     0x06

//eq
#define EQ_8_STAGE      8
#define EQ_16_STAGE     16

#define BPC16   0x08
#define BPC12   0x06
#define BPC10   0x05
#define BPC8    0x04

#define BPP12   0xc0
#define BPP10   0xa0
#define BPP9    0x90
#define BPP8    0x80
#define BPP7    0x70
#define BPP6    0x60
#define BPP5    0x50
#define BPP4    0x40
#define BPP3    0x30
#define BPP2    0x20
#define BPP1    0x10

//port type
#define NULL_PORT   0x00
#define DP_PORT     0x01
#define HDMI_PORT   0x02
#define LVDS_PORT   0x03
#define MIPI_PORT   0x04
#define EDP_PORT    0x05

//state
#define LOW         0x00
#define HIGH        0x01
#define OFF         0x00
#define ON          0x01
#define LED_ON      0x00
#define LED_OFF     0x01
#define ENABLED     0x01
#define DISABLED    0x00
#define NO_ACTION   0xff

#define LEFT_IMAGE      0
#define RIGHT_IMAGE     1
#define FULL_IMAGE      2

//----------------------------------------------------------------------------------------------------------------------------------------------//

#define Init    0x00
#define ACK     0x40
#define NACK    0x80
#define BUSY    0xC0

#define SOP         0x01
#define SOP1        0x02
#define SOP2        0x03
#define HardRst     0x04
#define Cable_Rst   0x05
#define SOP1_Debug  0x06
#define SOP2_Debug  0x07

//uart
#define UART_0   0
#define UART_1   1

#define TYPEC_INTF    0
#define DP_INTF       1

#define MALE        0
#define FEMALE      1

#define HPD_LOW     0
#define HPD_HIGH    1

#define IRQ_LOW     0
#define IRQ_HIGH    1

#define SYS_CLK_25M     0
#define SYS_CLK_27M     1
#define SYS_CLK_36M     2
#define SYS_CLK_40M     3
#define SYS_CLK_48M     4
#define SYS_CLK_54M     5
#define SYS_CLK_60M     6

#define RX_OUT_VIDEO    0
#define CSC_OUT_VIDEO   1

#define DHTX_SRC_SEL_DPTX       0x03
#define DHTX_SRC_SEL_DHRXPHY    0x02
#define DHTX_SRC_SEL_HDMI21TX   0x01
#define DHTX_SRC_SEL_HDMI20TX   0x00

#define LMTX_SRC_SEL_LVDSTX     0x00
#define LMTX_SRC_SEL_MIPITX     0x05

#define CHIPRX_SRC_SEL_DPRX     0x00
#define CHIPRX_SRC_SEL_HDMIRX   0x10
#define CHIPRX_SRC_SEL_PTN      0x30

//input type
#define DP_IN                  0
#define TYPEC_MALE             1
#define TYPEC_FEMALE_FLIP      2
#define TYPEC_FEMALE_NOFLIP    3

//Dp Rx cdr mode
#define FULL_SPEED_DIGCDR      0
#define HALF_SPEED_DIGCDR      1
#define ANACDR                 2

// link rate
#define RBR         0x06//6
#define HBR         0x0a//10
#define HBR2        0x14//20
#define HBR3        0x1e//30

#define DP1_0       0x10
#define DP1_1       0x11
#define DP1_2       0x12
#define DP1_3       0x13
#define DP1_4       0x14

//lane count
#define ONE_LANE    1
#define TWO_LANE    2
#define FOUR_LANE   4

//lane count
#define LANE_0      0
#define LANE_1      1
#define LANE_2      2
#define LANE_3      3
#define LANE_ALL    4

//swing level
#define LEVEL_0     0
#define LEVEL_1     1
#define LEVEL_2     2
#define LEVEL_3     3

#define NO_PATTERN      0
#define PTN480P         1
#define PTN720P         2
#define PTN1080P        3
#define PTN4K30         4
#define PTN4K60         5
#define PTN4K120        6
#define PTN8K30         7

#define VID_PTN         0
#define TPS1            1
#define TPS2            2
#define TPS3            3
#define TPS4            7

//VSC DEINED
#define DP_VSC_RGB_0                            0
#define DP_VSC_YCC444_1                         1
#define DP_VSC_YCC422_2                         2
#define DP_VSC_YCC420_3                         3

//VSC DEINED
#define MISC_RGB_0                           0
#define MISC_YCC422_1                        1
#define MISC_YCC444_2                        2
#define MISC_RGB_WIDE_3                      3

//VSC AND MISC0 DEINED
#define DPRX_6BIT_0                          0
#define DPRX_8BIT_1                          1
#define DPRX_10BIT_2                         2
#define DPRX_12BIT_3                         3

//Dp Vsc Defined
#define DP_VSC_SRGB_0                       0x00
#define DP_VSC_RGB_WIDE_FIXED_1             0x01
#define DP_VSC_RGB_WIDE_FLOATING_2          0x02
#define DP_VSC_ADOBE_RGB_3                  0x03
#define DP_VSC_DCI_P3_4                     0x04
#define DP_VSC_CUSTOM_COLOR_5               0x05
#define DP_VSC_ITUR_BT2020RGB_6             0x06

//Dp Vsc Defined
#define DP_VSC_ITUR_BT601_0                 0x00
#define DP_VSC_ITUR_BT709_1                 0x01
#define DP_VSC_XVYCC601_2                   0x02
#define DP_VSC_XVYCC709_3                   0x03
#define DP_VSC_SYCC601_4                    0x04
#define DP_VSC_OPYCC601_5                   0x05
#define DP_VSC_ITUR_BT2020YCYBCYRC_6        0x06
#define DP_VSC_ITUR_BT2020YCBCR_7           0x07

//Dp Misc0 defined
#define LEGCAY_RGB                       0x00
#define CTA_RGB                          0x01
#define ADOBE_MISC_RGB                   0x03

//Dp Misc0 defined
#define DP_MISC0_FIXED_WIDE_RGB_0        0x00
#define DP_MISC0_DCI_P3                  0x01
#define DP_MISC0_FLOATING_WIDE_RGB_2     0x02
#define DP_MISC0_COLOR_PROFILE           0x03

//Dp Misc0 defined
#define DP_MISC0_XVYCC601_0              0x00
#define DP_MISC0_ITUR_BT601_1            0x01
#define DP_MISC0_XVYCC709_2              0x02
#define DP_MISC0_ITUR_BT709_3            0x03

//Hdmi Defined
#define HDMI_SMPTE_170M                  0x01
#define HDMI_ITUR_BT709_2                0x02

//Hdmi Defined
#define HDMI_EXT_XVYCC601_0              0x00
#define HDMI_EXT_XVYCC709_1              0x01
#define HDMI_EXT_SYCC601_2               0x02
#define HDMI_EXT_ADOBE_YCC601_3          0x03
#define HDMI_EXT_ADOBE_RGB_4             0x04
#define HDMI_EXT_ITUR_BT2020YCYBCYRC_5   0x05
#define HDMI_EXT_ITUR_BT2020RGB_6        0x06
#define HDMI_EXT_ITUR_BT2020YCBCR_6      0x06

//HDMI RX

#define HDMIRX_8BIT_4                     4
#define HDMIRX_10BIT_5                    5
#define HDMIRX_12BIT_6                    6

//HDMI TX DEFINED
#define DEEP_8BIT                         8
#define DEEP_10BIT                       10
#define DEEP_12BIT                       12

#define NOT_YCC422                       0
#define IS_YCC422                        1

#define NOT_YCC420                      0
#define IS_YCC420                       1

#define FULL_RANGE                      0
#define LIMIT_RANGE                     1

#define DVI_MODE                        0
#define HDMI_MODE                       1

#define FAIL                            0
#define SUCCESS                         1

#define UNSTABLE                        0
#define STABLE                          1
#define UNKNOWN                         2

#define SELNODSC                        0
#define SELDSCDECODE                    1
#define SELDSCBYPASS                    2

#define NO_VRR                          0
#define VRR_ON                          1
#define VRR_OFF                         2

//link training state
#define TRAINING_FAIL                   0
#define TRAINING_WAIT                   1
#define TRAINING_PROCESS                2
#define TRAINING_SUCCESS                3
#define TRAINING_FRL_ADJUST             4
#define TRAINING_FRL_RETRY              5
#define TRAINING_FFE_ADJUST             6

//mode
#define SW_MODE                         0//software
#define HW_MODE                         1//hardware
#define FIX_MODE                        3
#define SW_SCANALLEQ                    4//software
#define SW_SCANMIDEQ                    5//software
#define SW_SCANVALIDEQ                  6//software
#define SW_SCANVALIDEQ_EXT              7//software

#define LEFT            0
#define RIGHT           1

#define LEFT_2_RIGHT    0
#define RIGHT_2_LEFT    1

#define INVALID_VAL     0xff

//dsc
#define TWO_RATIO           2
#define THREE_RATIO         3
#define FOUR_RATIO          4
//DSC SLICE NUMBER
#define ONE_SLICE           1
#define TWO_SLICE           2
#define FOUR_SLICE          4
#define EIGHT_SLICE         8
//dsc pps error
#define DSC_CHUNKSIZE_ERR   0x04
#define DSC_RCBUF_OVERFLOW  0x02
#define DSC_RCBUF_UNDERRUN  0x01


//hdcp
#define NO_HDCP             0x00
#define HDCP1X              0x10
#define HDCP2X              0x20
#define FIXED_HDCP1X        0x10
#define FIXED_HDCP2X        0x20

#define NONE_EVENT                       0x00
#define HPD_IRQ_EVENT                    0x01

//frequence meter
#define FREQ_METER_1                       1
#define FREQ_METER_2                       2

//audio in
#define NO_AUDIO_DATA                      0
#define RX_AUDIO_DATA                      1
#define I2SIN_AUDIO_DATA                   2
#define SPDIFIN_AUDIO_DATA                 3
#define PATTERN_AUDIO_DATA                 4

//i2s in port define
#define I2SIN_SD_PORT                      GPIO7_D3//GPIO26_SPDIF
#define I2SIN_WS_PORT                      GPIO6_D2//GPIO3_WS
#define I2SIN_SCLK_PORT                    GPIO23  //just sel: GPIO23 or GPIO2_SCLK
//spdif in port define
#define SPDIF_IN_PORT                      GPIO4_D0_SPDIF

//i2s out port define
#define I2SOUT_SD_PORT                     GPIO4_D0_SPDIF
#define I2SOUT_WS_PORT                     GPIO3_WS
#define I2SOUT_SCK_PORT                    GPIO2_SCLK
#define I2SOUT_MCLK_PORT                   GPIO20_MCLK
//spdif out port define
#define SPDIF_OUT_PORT                     GPIO4_D0_SPDIF

//audio
#define AUD_PTN_32K                      1
#define AUD_PTN_44D1K                    2
#define AUD_PTN_48K                      3
#define AUD_PTN_88D2K                    4
#define AUD_PTN_96K                      5
#define AUD_PTN_176D4K                   6
#define AUD_PTN_192K                     7

#define HEADERERROR                      0
#define CHECKSUMERROR                    1
#define EDIDCORRECT                      2

#define EDIDWAIT                         3

#define HARDWARE                         0
#define SOFTMODE                         1
#define MIXEDMODE                        2

#define SHDR                            0x01
#define DHDR                            0x02
#define DOLBY                           0x04
//csc
#define RGB_0             0x00
#define YCbCr422_1        0x01
#define YCbCr444_2        0x02
#define YCbCr420_3        0x03
#define RGB_WIDE_4        0x04

#define SIMPLE422_5       0x05
#define NOT_CONVERT       0xff

#define DP_FREQ_IN_KHZ_MAX              600000

//Voltage Threshold
#define VOL_1_8     0x00
#define VOL_3_3     0x01

//TIMING_HBE_HTOTAL_4k60Hz_MAX = 16.2G/30/Vtotal/Frame rate
//TIMING_HBE_HTOTAL_4k60Hz_MIN = Htotal - Buffer_Size
//3840*2160 60Hz
#define TIMING_HBE_HTOTAL_4k60Hz_MAX              4000
#define TIMING_HBE_HTOTAL_4k60Hz_MIN              3888
//3840*2160 50Hz //4096*2160 50Hz
#define TIMING_HBE_HTOTAL_4k50Hz_MAX              4800
#define TIMING_HBE_HTOTAL_4k50Hz_MIN              4768

//3840x2160 "QFHD" 4096¡Á2160 "4K2K"
#define HBE_NONE                             0
#define HBE_TYPE_UHD_60Hz                   1
#define HBE_TYPE_UHD_50Hz                   2
#define HBE_TYPE_4K2K_50Hz                   3

#define HBE_4K60                      0x01
#define HBE_4K50                      0x02

#define BRANCH_HDMI                       0x01
#define BRANCH_DP                         0x00

#define HDR_SDPNone                       0x00
#define HDR_SDPVer12                      0x01
#define HDR_SDPVer13                      0x02

#define DPRX_ERR_CNT                      0x8010

#define MIN(A,B) ((A) < (B) ? (A):(B))

#define FORMAT_PROG                            0
#define FORMAT_INTL                            1

#define ATTENTION_NULL                    0x00
#define ATTENTION_HIGH                    0x01
#define ATTENTION_LOW                     0x02
#define ATTENTION_IRQ                     0x03

#define EDID_HDMITYPE                         0x00
#define EDID_DPTYPE                           0x01
#define EDID_VGATYPE                          0x02

typedef enum
{
    SOFT_RUNNING =   0,  //flow is running
    SOFT_RST_STATE = 1,//flow state reset
}EnumFlowState;

typedef enum
{
    STEP_CONTINUE = 0,//proceed to the next step
    STEP_DEAL_END,    //step end
    STEP_RESET_RX,    //restart rx soft flow
    STEP_RESET_TX,    //restart tx soft flow
    STEP_PORT_LINK = 0xff,//rx and tx link
}EnumFlowStep;

typedef enum
{
    OUT_DISABLE = 0x00,//None pullup or pulldown
    NO_PU_PD =  0x00,//None pullup or pulldown
    OUT_OPD  =  0x04,//Open drain
    OUT_PP_1x = 0x08,//Driver capability X1
    OUT_PP_2x = 0x0C,//Driver capability X2
    PD_100K  =  0x01,//100k pulldown
    PU_100K  =  0x02,//100k pullup
    FORBIDDEN = 0x03,//Forbidden
}EnumIOMode;

typedef enum
{
    CEC = 0,
    INT,
    GPIO32_SCLKB,
    GPIO31_MCLKB,
    GPIO30_WSB,
    GPIO29_SD0B,
    GPIO28_SD1B,
    GPIO27_SD2B,
    GPIO26_SD3B,
    GPIO25_PWM3,
    GPIO24_PWM2,
    GPIO23_SBU1,
    GPIO22_PWM1,
    GPIO21_UART_TX,
    GPIO20_PWM0,
    GPIO19_SD0A_VSYNC,
    GPIO18_WSA,
    GPIO17_SCLKA,
    GPIO16_MCLKA,
    GPIO11_KPA3,
    GPIO10_KPA2,
    GPIO9_KPA1,
    GPIO8_KPA0,
    GPIO7_SD3A,
    GPIO6_SD2A,
    GPIO5_SD1A,
    GPIO4_SPDIFA,
    GPI_HS_TSTP,
    GPI_HS_TSTN,
    GPIO3_DHRX_DCAUXP,
    GPIO2_DHRX_DCAUXN_5VDET,
    GPIO1_EARCP,
    GPIO0_EARCN,
    GPIO15_D2_VDET,
    GPIO12_D1_VDET,
    GPIO14_BB_DM,
    GPIO13_BB_DP,
    GPIOX
}EnumGPION;

typedef enum
{
    Io_Function0 = 0,
    Io_Function1,
    Io_Function2,
    Io_Function3,
    Io_Function4,
    Io_Function5,
    Io_Function6,
    Io_Function7,
    Blk_test_out_b0,
    Blk_test_out_b1,
    Blk_test_out_b2,
    Blk_test_out_b3,
    Blk_test_out_b4,
    Blk_test_out_b5,
    Blk_test_out_b6,
    Blk_test_out_b7,
}EnumGPIO_Src;

typedef enum
{
    I2C_SLAVE = 0x00,
    I2C_MASTER = 0x10,
    GPIO_MODE = 0x20,
}IO_MODE_E;


typedef enum
{
    PRINT_PRIO_HIG = 0,//High priority
    PRINT_PRIO_MID,    //middle priority
    PRINT_PRIO_LOW,    //low priority
    PRINT_PRIO_TEST,   //test priority
    PRINT_PRIO_MAX,    //max
}EnumPrintLvl;

typedef enum
{
    IRQ_DPRX_AUX_INT = 0,// ex0
    IRQ_DPRX_HDR_INT,
    IRQ_DPRX_ADAPTIVE_SYNC_INT,
    IRQ_DPRX_STATICHDR_INT,
    IRQ_DPRX_VSI_INT,
    IRQ_DPRX_DYNAMICHDR_INT,
    IRQ_DPRX_UCC_INT,
    IRQ_DPRX_DCC_INT,
    IRQ_DPRX_PPS_DATA_CHG_INT,
    IRQ_DPRX_PPS_PKT_INT,
    IRQ_DPRX_MSA_INT,
    IRQ_RXHDCP1X_INT,
    IRQ_RXHDCP2X_INT,

    IRQ_HDMIRX_FRL_INT,
    IRQ_HDMIRX_VRRSTART_INT,
    IRQ_HDMIRX_VRRSTOP_INT,
    IRQ_HDMIRX_STATICHDR_INT,
    IRQ_HDMIRX_VSI_INT,
    IRQ_HDMIRX_DYNAMICHDR_INT,
    IRQ_HDMIRX_PPS_LOAD_SUCC_INT,
    IRQ_HDMIRX_PPS_DATA_CHG_INT,
    IRQ_TMDS_UNSTB_INT,
    IRQ_TMDS_STB_INT,

    IRQ_TMDS_PKDET_INT,
    
    IRQ_RXPLL_STB_INT,
    IRQ_RXPLL_UNSTB_INT,
    IRQ_RXPLL_UNLOCK_INT,
    IRQ_HDMIRX_VIDCHK_INT,
    IRQ_BB_INT,//ex1
    
    IRQ_CC1_INT,//ex1
    IRQ_CC2_INT,//ex1
    IRQ_CC2VBUSFALL_INT,
}EnumInterrupt;

typedef enum
{
    RX_FM,
    RXLINK_FM,
    TX_FM,
    TOP_FM,
}EnumFreqMeter;

typedef enum
{
    RXFM_LINK_CLK = 0x0b,
    TOPFM_AD_PCRPLL_DIV_PCR_CLK = 0x17,
    TOPFM_PCRPLL_PCR_CLK        = 0x18,
    TOPFM_AD_DSCRX_DSC_RD_CLK   = 0x0e,
    TOPFM_AD_DSCRX_DSC_CLK      = 0x0d,
    TOPFM_AD_DSCTX_DSC_RD_CLK   = 0x12,
    TOPFM_AD_DSCTX_DSC_CLK      = 0x13,
    TOPFM_AD_DSCTX_DSC_OUT_CLK  = 0x14,
    TOPFM_AD_DHTX_READ_CLK      = 0x26,
    
}EnumClk;

typedef enum
{
    DPRX_SOURECE_PLUG_EVENT = 1,
    DPRX_SOURECE_UNPLUG_EVENT,
    DPRX_VIDEO_ON_EVENT,
    DPRX_VIDEO_OFF_EVENT,
    DPRX_HDCP_VER_CHG_EVENT,
    DPRX_COLORINFO_CHG_EVENT,
    DPRX_TIMING_CHG_EVENT,
    DPRX_PACKET_CHG_EVENT,
    DPRX_VRR_NOTIFY_EVENT,
    DPRX_HDR_NOTIFY_EVENT,
    DPRX_STATIC_HDR_NOTIFY_EVENT,
    DPRX_DYNAMIC_HDR_NOTIFY_EVENT,
    DPRX_DOBLY_HDR_NOTIFY_EVENT,
    DPRX_AUDIO_CHG_EVENT,
    DPRX_FEC_NOTIFY_EVENT,
    DPRX_COLORRIMETRY_CHG_EVENT,
}EnumDpRxEvent;

typedef enum
{
    HDMIRX_SOURECE_PLUG_EVENT = 1,
    HDMIRX_SOURECE_UNPLUG_EVENT,
    HDMIRX_VIDEO_ON_EVENT,
    HDMIRX_VIDEO_OFF_EVENT,
    HDMIRX_VID_CHK_CHG_EVENT,
    HDMIRX_HDCP_VER_CHG_EVENT,
    HDMIRX_TIMING_CHG_EVENT,
    HDMIRX_PACKET_CHG_EVENT,
    HDMIRX_VRR_NOTIFY_EVENT,
    HDMIRX_DYNAMIC_HDR_NOTIFY_EVENT,
    HDMIRX_STATIC_HDR_NOTIFY_EVENT,
    HDMIRX_DOBLY_HDR_NOTIFY_EVENT,
    HDMIRX_AUDIO_CHG_EVENT,
    HDMIRX_INTERLACE_EVENT,
    HDMIRX_VIDEO_MUTE_EN,
    HDMIRX_VIDEO_MUTE_DIS,
    HDMIRX_AUDIO_MUTE_DIS,
    HDMIRX_AUDIO_MUTE_EN,
}EnumHdmiRxEvent;

typedef enum
{
    HDMI_PCR_RST  =1 ,
    HDMI_ERR_DET_RST,
    HDMI_FRL_DEC_RST,
    HDMI_FEC_DEC_RST,
    HDMI_FRL_DEPKT_RST,
    HDMI_FRL_TRAIN_RST,
    HDMI_RX_FIFO_RST,
    HDMI_RX_DEPKT_RST,
}EnumHdmiRstType;

typedef enum
{
    HDMI_TX_AFIFO_RST  =1 ,
    HDMI_TX_21PKT_RST,
    HDMI_TX_20DC_RST,
    HDMI_TX_20VID_RST,
}EnumHdmiTxRstType;

typedef enum
{
    DP_RX_PCR_RST  =1 ,
    DP_ERR_DET_RST,
    DP_MLC_DAT_RST,
    DP_MLC_DPCD_RST,
    DP_FEC_DEC_RST,
    DP_RX_SDP_RST,
    DP_RX_FIFO_RST,
}EnumDpRxRstType;

typedef enum
{
    HDMIRX_EMP_CLR  =1 ,
    
}EnumHdmiPktClrType;

typedef enum
{
    DPTX_SINK_PLUG_EVENT = 1,
    DPTX_SINK_UNPLUG_EVENT,
    DPTX_EDID_VALID_EVENT,
    DPTX_EDID_INVALID_EVENT,
}EnumDpTxEvent;

typedef enum
{
    HDMITX_SINK_PLUG_EVENT = 1,
    HDMITX_SINK_UNPLUG_EVENT,
    HDMITX_EDID_VALID_EVENT,
    HDMITX_EDID_INVALID_EVENT,
    HDMITX_VIDEOOFF_EVENT,
}EnumHdmiTxEvent;

typedef enum
{
    RESERVED = 0,// 
    AUDIO_DATA_BLOCK_1 = 1,
    VIDEO_DATA_BLOCK_2 = 2,
    VENDOR_SPEC_DATA_BLOCK_3 = 3,
    SPEAKER_DATA_BLOCK_4 = 4,
    VESA_DATA_BLOCK_5 =  5,
    USE_EXTENDED_TAG_7 = 7,
}DataBlock_E;

typedef enum
{
    VIDEO_CAP_DATA_BLOCK_0 = 0,// 
    VENDOR_SPEC_VIDEO_DATA_BLOCK_1 = 1,
    VESA_DISP_DEVICE_DATA_BLOCK_2 = 2,
    VESA_VID_TIMING_BLOCK_EXTENSION_3 = 3,
    HDMI_VID_DATA_BLOCK_4 = 4,
    COLORIMETRY_DATA_BLOCK_5 = 5 ,
    HDR_STATIC_META_DATA_BLOCK_6 = 6 ,
    HDR_DYNAMIC_META_DATA_BLOCK_7 = 7 ,

    VID_FORMAT_PREREF_DATA_BLOCK_13 = 13,
    YCC420_VID_DATA_BLOCK_14 = 14 ,
    YCC420_CAP_MAP_DATA_BLOCK_15 = 15 ,
    CTA_MISC_AUDIO_FIELDS_16 = 16 ,
    VENDOR_SPEC_AUDIO_DATA_BLOCK_17 = 17 ,
    HDMI_AUDIO_DATA_BLOCK_18 = 18,
    ROOM_CONFIG_DATA_BLOCK_19 = 19,
    SPEAKER_LOCATION_DATA_BLOCK_20 = 20,
}ExtendedBlock_E;

typedef enum
{
    USER_DEFINE_PKT_0X77 = 0x77,
    VSI_INFO_FRAME_0X81 = 0x81,
    AVI_INFO_FRAME_0X82 = 0x82,
    HDR_INFO_FRAME_0X87 = 0x87,
}EnumPacktType;

typedef enum
{
    LOG_DEBUG =0x00,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_CRITICAL,
    LOG_NOTRACE,
}LogLevel;

typedef enum
{
    SLEEP_INIT_0 = 0,
    SLEEP_ENTER_1 ,
    SLEEP_TOGGLE_RTERM_ON_2 ,
    SLEEP_TOGGLE_RTERM_OFF_3 ,
    SLEEP_EXIT_4,
    SLEEP_END_5,
}EnumSleepEvent;

typedef enum
{
    DPRX_INIT_SET_PATH = 0,
    DPRX_DSCDEC_PPS_PATH,
    DPRX_DSCBYPASS_PPS_PATH,

    HDMIRX_INIT_SET_PATH,
    HDMIRX_DSCDEC_PPS_PATH,
    HDMIRX_DSCBYPASS_PPS_PATH,

    DPTX_INIT_SET_PATH,
    DPTX_DSCENC_PPS_PATH,
    DPTX_DSCBYPASS_PPS_PATH,
    DPTX_HDR_PKT_PATH,

    HDMITX_INIT_SET_PATH,
    HDMITX_DSCENC_PPS_PATH,
    HDMITX_DSCBYPASS_PPS_PATH,
    HDMITX_HDR_PKT_PATH,

    MIPITX_DSCENC_PPS_PATH,
    
}EnumSramPath;
 
typedef struct tag_SleepInfo
{
    u8 ucRxPowerdownState;
    u8 ucRxPowerdownChgFlag;
    u8 ucTxPowerdownState;
    u8 ucTxPowerdownChgFlag;
    
    u8 ucSleepState;
    u8 ucSleepChgFlag;

}StructSleepInfo;

typedef struct Timing_tag
{
    u8 ucHspol;
    u8 ucVspol;

    u16 usHbp;
    u16 usHsync;//hstart = hsync + hbp
    u16 usHfp;
    u16 usHact;
    u16 usHtol;

    u16 usVbp;
    u16 usVsync;
    u16 usVfp;
    u16 usVact;
    u16 usVtol;

    u16 usFramerate;
    u32 ulPixFreq;
}LtTiming_S;

typedef struct ColorInfo_tag
{
    //dp rx
    u8 b1VscPkg;
    u8 b1DynamicRange;
    //hdmi rx
    u8 ucRgbRange;
    u8 ucYccRange;
    u8 ucVic;
    u8 ucAspectRatio;
    u8 ucColorimetryExt;
    //normal
    u8 ucPixelEncoding;
    u8 ucColorimetryFormat;
    u8 ucBitDepth;

}ColorInfo_S;

typedef struct AudioChlInfo_tag
{
    u8 ucLayout;
    u8 ucChannel;
    u8 ucFsValue;
	u8 ucCodingType;
    u8 b1AudioHbrEn;
    u8 szAudioInfo[5];
}AudioChlInfo_S;

typedef struct tag_DscDecInfo
{
    u8 ucDscByEn;
    u8 ucDscDecEn;

    u8 ucColorSpace;
    u8 ucColorDepth;

    u8 ucCoreNum;
    u8 ucSliceNum;
    u8 ucCompressRatio;

    u16 usBpp;
    u8 ucExtraHact;
    u8 ucGroupUnit;

    u8 ucSliceRemainder;
    u16 usSliceHeight;
    u16 usSliceWidth;
    u16 usSliceGroup;

    u16 usChunkSize;
}DscDecInfo_S;

typedef struct tag_DscEncInfo
{
    u8 ucDscEncEn;
    u8 ucBlockPredEn;
    u8 ucSliceNum;
    u8 ucCoreNum;
    u8 b1Simple422En;
    u8 ucColorSpace;
    u8 ucColorDepth;
    u8 ucCompressRatio;

    u8 ucMainVer;
    u8 ucMinorVer;
    u8 ucExtraHact;
    u8 ucGroupUnit;

    u16 usBpp;
    u16 usExtraBits;

    u16 usSliceHeight;
    u16 usSliceWidth;
    u16 usSliceGroup;
    u16 usSliceOffset;

    u16 usInitDelay;
    u16 usInitOffset;

    u8 ucSecLineOffset;
    u16 usNotFirstLineOffset;
}StructDscEncInfo;

typedef struct Edid_tag
{
    u8 b1HdmiMode;
    u8 b1Hdmi14Edid;
    u8 b1Hdmi20Edid;
    u8 b1Support8K;
    u8 b1Hdmi14Vsdb;
    u8 b1Hdmi20Vsdb;
    u8 b1Yuv420Edid;
    u8 b1HDREdid;
    u8 b1Timing266;
    u8 b1Timing533;
    u8 b1VicFlag;
    u8 b1EeodbFlag;
    u8 b1Scdc_Present;
    u8 b1RrEnable;
    u8 b1ReadReqCap;
    u8 ucColorDepth;        //color depth
    u8 ucBlockTag;
    u8 ucBlockLen;
    u8 ucVsdb_offset;
    u8 ucMaxFrlRate;
    u8 ucMaxFrlDscRate;
    u8 ucMaxDscSlice;
	u8 ucHdmiTmdsClk;
    u16 usMaxTmdsRate;//Max_TMDS_Character_Rate
    u32 ulDpLinkWidth;
	u8 b1EdidWithVrr;
    u8 b1Dsc_1p2;
    u8 ucDsc_TotalChunkKBytes;
    u8 b1Dsc_Native420;
	u8 ucHF_EEODBLength;
    u8 b1EdidType;
    u8 ucMinVerticalRate;
}EDID_S;
#endif
