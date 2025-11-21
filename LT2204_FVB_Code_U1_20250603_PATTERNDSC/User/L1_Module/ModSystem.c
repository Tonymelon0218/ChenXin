/******************************************************************************
  * @project: LT2101
  * @file: chipsystem.c
  * @author: qihan
  * @company: LONTIUM
  * @date: 2021.10.12
/******************************************************************************/
#include "include.h"

//----------------------------------------------------------------dp tx-------------------------------------------------------------------------------
#if TX_PORT_SIGN == DP_PORT

void Mod_Audio_DpTxInfoCvt(IN AudioChlInfo_S *pstRxInfo, OUT DpTx_S *pstDpTx)
{
    pstDpTx->ucLayout = pstRxInfo->ucLayout;
    pstDpTx->ucChannel = pstRxInfo->ucChannel;
    pstDpTx->ucFsValue = pstRxInfo->ucFsValue;
    pstDpTx->ucCodingType = pstRxInfo->ucCodingType;

    if ((pstDpTx->ucChannel > 0) || (pstDpTx->ucCodingType == 1))
    {

        pstDpTx->szAudioInfo[0] = 0x84;                      // hb1
        pstDpTx->szAudioInfo[1] = 0x1b;                      // hb2
        pstDpTx->szAudioInfo[2] = 0x44;                      // hb3 is sdp1.2
        pstDpTx->szAudioInfo[3] = 0x00;                      // db1
        pstDpTx->szAudioInfo[4] = pstRxInfo->szAudioInfo[1]; // db2
        pstDpTx->szAudioInfo[5] = pstRxInfo->szAudioInfo[2]; // db3
        pstDpTx->szAudioInfo[6] = pstRxInfo->szAudioInfo[3]; // db4
        pstDpTx->szAudioInfo[7] = pstRxInfo->szAudioInfo[4]; // db5
    }
    else
    {
        pstDpTx->szAudioInfo[3] = 0x00; // db1
        pstDpTx->szAudioInfo[4] = 0x00; // db2
        pstDpTx->szAudioInfo[5] = 0x00; // db3
        pstDpTx->szAudioInfo[6] = 0x00; // db4
        pstDpTx->szAudioInfo[7] = 0x00; // db5
    }
}

void Mod_DpTx_ColorDepthCal(IN ColorInfo_S *pstRxInfo, OUT DpTx_S *pstDpTx)
{
    pstDpTx->ucMsaValue = 0x10; //[6:4]color depth: 0-6bit,1-8bit, [3:2]color space: 0-RGB/YCbCr444/YCbCr420;
    pstDpTx->ucMisc0 = 0x20;    //[7:5]color depth
    pstDpTx->ucMisc1 = 0x00;
    pstDpTx->ucVscDb16 = 0x00;
    pstDpTx->ucVscDb17 = 0x00; //[2:0]color depth
    pstDpTx->ucVscDb18 = 0x03;
    switch (pstRxInfo->ucBitDepth)
    {
#if RX_PORT_SIGN == DP_PORT
    case DPRX_6BIT_0: // 6bit
        pstDpTx->ucMsaValue = 0x00;
        pstDpTx->ucMisc0 = 0x00;
        pstDpTx->ucVscDb17 = 0x00;
        break;
    case DPRX_10BIT_2: // 10bit
        pstDpTx->ucMsaValue = 0x20;
        pstDpTx->ucMisc0 = 0x40;
        pstDpTx->ucVscDb17 = 0x02;
        break;
    case DPRX_12BIT_3: // 12bit
        pstDpTx->ucMsaValue = 0x30;
        pstDpTx->ucMisc0 = 0x60;
        pstDpTx->ucVscDb17 = 0x03;
        break;
    case DPRX_8BIT_1: // 8bit
#endif

#if RX_PORT_SIGN == HDMI_PORT
    case HDMIRX_10BIT_5: // 10bit
        pstDpTx->ucMsaValue = 0x20;
        pstDpTx->ucMisc0 = 0x40;
        pstDpTx->ucVscDb17 = 0x02;
        break;
    case HDMIRX_12BIT_6:            // 12bit
        pstDpTx->ucMsaValue = 0x30; // 422 defualt 12bit
        pstDpTx->ucMisc0 = 0x60;
        pstDpTx->ucVscDb17 = 0x03;
        break;
    case HDMIRX_8BIT_4: // 8bit
#endif
    default:
        pstDpTx->ucMsaValue = 0x10;
        pstDpTx->ucMisc0 = 0x20;
        pstDpTx->ucVscDb17 = 0x01;
        break;
    }
}

void Mod_DpTx_ColorSpaceCal(IN ColorInfo_S *pstRxInfo, OUT DpTx_S *pstDpTx)
{
    switch (pstRxInfo->ucPixelEncoding) // color fromat cal
    {
    case RGB_0:
    case RGB_WIDE_4:
        pstDpTx->ucMsaValue &= 0xf3; //[3:2]color space: 0-Rgb/YCbCr444/YCbCr420;
        pstDpTx->ucMisc0 &= 0xf9;    //[2:1]color space: 0-Rgb, 1-Ycbcr422, 2-Ycbcr444
        pstDpTx->ucVscDb16 = 0x00;   //[7:4]color space: 0-Rgb, 1-Ycbcr444, 2-Ycbcr422, 3-Ycbcr420
        break;
    case YCbCr444_2:
        pstDpTx->ucMsaValue &= 0xf3;
        pstDpTx->ucMisc0 |= 0x04;
        pstDpTx->ucVscDb16 = 0x10;
        break;
    case YCbCr422_1:
        pstDpTx->ucMsaValue |= 0x04;
        pstDpTx->ucMisc0 |= 0x02;
        pstDpTx->ucVscDb16 = 0x20;
        break;
    case YCbCr420_3:
        pstDpTx->ucMsaValue &= 0xf3;
        pstDpTx->ucMisc0 &= 0xf9;
        pstDpTx->ucVscDb16 = 0x30;
        break;
    default:
        break;
    }
    pstDpTx->ucMisc1 = (pstDpTx->b1VscEnable) ? (0x40) : (0x00); // misc 1
}

void Mod_DpTx_ColorRangeCal(IN ColorInfo_S *pstRxInfo, OUT DpTx_S *pstDpTx)
{
    switch (pstRxInfo->ucPixelEncoding) // range cal
    {
    case RGB_0:
    case RGB_WIDE_4:
#if RX_PORT_SIGN == DP_PORT
        if (pstRxInfo->b1DynamicRange == 1) // limit
        {
            pstDpTx->ucMisc0 |= BIT3_1;   //[3]1-CTA Range Limit, 0-VESA Range Full
            pstDpTx->ucVscDb17 |= BIT7_1; //[7]1-CTA Range Limit, 0-VESA Range Full
        }
#endif
#if RX_PORT_SIGN == HDMI_PORT
        if (pstRxInfo->ucRgbRange == 1) // 1-limit, 2-full
        {
            pstDpTx->ucMisc0 |= BIT3_1;
            pstDpTx->ucVscDb17 |= BIT7_1; //[7]1-CTA Range Limit, 0-VESA Range Full
        }
#endif
        break;
    default: // Ycbcr422 ycbcr420 ycbcr444
#if RX_PORT_SIGN == DP_PORT
        if (pstRxInfo->b1DynamicRange == 1) // limit
        {
            pstDpTx->ucVscDb17 |= BIT7_1; //[7]1-CTA Range Limit, 0-VESA Range Full
        }
#endif
#if RX_PORT_SIGN == HDMI_PORT
        if (pstRxInfo->ucYccRange == 0) // 0-limit, 1-full
        {
            pstDpTx->ucVscDb17 |= BIT7_1; //[7]1-CTA Range Limit, 0-VESA Range Full
        }
#endif
        break;
    }
}

void Mod_DpTx_ColorimetryCal(IN ColorInfo_S *pstRxInfo, OUT DpTx_S *pstDpTx)
{
    switch (pstRxInfo->ucPixelEncoding)
    {
    case RGB_0:
    case RGB_WIDE_4:
#if RX_PORT_SIGN == DP_PORT
        if (pstRxInfo->b1VscPkg == TRUE)
        {
            switch (pstRxInfo->ucColorimetryFormat)
            {
            case DP_VSC_RGB_WIDE_FIXED_1:
                pstDpTx->ucMisc0 |= 0x06;
                break;
            case DP_VSC_RGB_WIDE_FLOATING_2:
                pstDpTx->ucMisc0 |= 0x16;
                break;
            default:
                break;
            }
            pstDpTx->ucVscDb16 |= pstRxInfo->ucColorimetryFormat;
        }
        else
        {
            if (pstRxInfo->ucPixelEncoding == RGB_WIDE_4)
            {
                switch (pstRxInfo->ucColorimetryFormat)
                {
                case DP_MISC0_FIXED_WIDE_RGB_0:
                    pstDpTx->ucMisc0 |= 0x06;
                    pstDpTx->ucVscDb16 |= 0x01;
                    break;
                case DP_MISC0_FLOATING_WIDE_RGB_2:
                    pstDpTx->ucMisc0 |= 0x16;
                    pstDpTx->ucVscDb16 |= 0x02;
                    break;
                default:
                    break;
                }
            }
        }
#endif
#if RX_PORT_SIGN == HDMI_PORT
        if (pstRxInfo->ucColorimetryFormat == 0x03) // 3-use colorimetry ext format
        {
            switch (pstRxInfo->ucColorimetryExt)
            {
            case HDMI_EXT_ADOBE_RGB_4:
                pstDpTx->ucVscDb16 |= 0x03;
                break;
            case HDMI_EXT_ITUR_BT2020RGB_6: // ITUR_BT2020RGB_6
                pstDpTx->ucVscDb16 |= 0x06;
                break;
            default:
                break;
            }
        }
#endif
        break;
    default: // Ycbcr422 ycbcr420 ycbcr444
#if RX_PORT_SIGN == DP_PORT
        if (pstRxInfo->b1VscPkg == TRUE)
        {
            switch (pstRxInfo->ucColorimetryFormat)
            {
            case DP_VSC_ITUR_BT601_0: // bt601
                pstDpTx->ucMisc0 |= 0x08;
                break;
            case DP_VSC_ITUR_BT709_1: // bt709
                pstDpTx->ucMisc0 |= 0x18;
                break;
            case DP_VSC_XVYCC601_2: // xv601
                pstDpTx->ucMisc0 |= 0x00;
                break;
            case DP_VSC_XVYCC709_3: // xv709
                pstDpTx->ucMisc0 |= 0x10;
                break;
            default:
                break;
            }
            pstDpTx->ucVscDb16 |= pstRxInfo->ucColorimetryFormat;
        }
        else
        {
            pstDpTx->ucMisc0 |= (pstRxInfo->ucColorimetryFormat << 3);
            switch (pstRxInfo->ucColorimetryFormat)
            {
            case DP_MISC0_XVYCC601_0: // xv601
                pstDpTx->ucVscDb16 |= 0x02;
                break;
            case DP_MISC0_ITUR_BT601_1: // bt601
                pstDpTx->ucVscDb16 |= 0x00;
                break;
            case DP_MISC0_XVYCC709_2: // xv709
                pstDpTx->ucVscDb16 |= 0x03;
                break;
            case DP_MISC0_ITUR_BT709_3: // bt709
                pstDpTx->ucVscDb16 |= 0x01;
                break;
            default:
                break;
            }
        }
#endif
#if RX_PORT_SIGN == HDMI_PORT
        if (pstRxInfo->ucColorimetryFormat == HDMI_SMPTE_170M)
        {
            pstDpTx->ucMisc0 |= 0x08;
        }
        else if (pstRxInfo->ucColorimetryFormat == HDMI_ITUR_BT709_2)
        {
            pstDpTx->ucMisc0 |= 0x18;
            pstDpTx->ucVscDb16 |= 0x01;
        }
        else if (pstRxInfo->ucColorimetryFormat == 0x03) // 3-use colorimetry ext format
        {
            switch (pstRxInfo->ucColorimetryExt)
            {
            case HDMI_EXT_XVYCC601_0:
                pstDpTx->ucMisc0 |= 0x00; // xvYCC601
                pstDpTx->ucVscDb16 |= 0x02;
                break;
            case HDMI_EXT_XVYCC709_1:
                pstDpTx->ucMisc0 |= 0x10; // xvYCC709
                pstDpTx->ucVscDb16 |= 0x03;
                break;
            case HDMI_EXT_SYCC601_2:
                pstDpTx->ucMisc0 |= 0x08; // YCBCR601
                pstDpTx->ucVscDb16 |= 0x04;
                break;
            case HDMI_EXT_ADOBE_YCC601_3:
                pstDpTx->ucMisc0 |= 0x08; // YCBCR601
                pstDpTx->ucVscDb16 |= 0x05;
                break;
            case HDMI_EXT_ITUR_BT2020YCYBCYRC_5:
                pstDpTx->ucMisc0 |= 0x18; // YCBCR709
                pstDpTx->ucVscDb16 |= 0x06;
                break;
            case HDMI_EXT_ITUR_BT2020YCBCR_6:
                pstDpTx->ucMisc0 |= 0x18; // YCBCR709
                pstDpTx->ucVscDb16 |= 0x07;
                break;
            default:
                pstDpTx->ucMisc0 |= 0x18; // YCBCR709
                pstDpTx->ucVscDb16 |= 0x01;
                break;
            }
        }
#endif
        break;
    }
}
#endif
//-------------------------------------------------------------------------------hdmi tx-----------------------------------------------------------
#if TX_PORT_SIGN == HDMI_PORT

u16 code szTimeTable[108][7] =
    {
        // hact,vact,htot,vto,vfro,vic,format
        // 24/25/30/48Hz
        {1280, 720, 3300, 750, 24, 60, FORMAT_PROG}, // 0
        {1280, 720, 3960, 750, 25, 61, FORMAT_PROG},
        {1280, 720, 3300, 750, 30, 62, FORMAT_PROG},
        {1280, 720, 2500, 750, 48, 108, FORMAT_PROG},

        {1920, 1080, 2750, 1125, 24, 32, FORMAT_PROG},
        {1920, 1080, 2640, 1125, 25, 33, FORMAT_PROG},
        {1920, 1080, 2200, 1125, 30, 34, FORMAT_PROG},
        {1920, 1080, 2750, 1125, 48, 111, FORMAT_PROG},

        {1680, 720, 3300, 750, 24, 79, FORMAT_PROG},
        {1680, 720, 3168, 750, 25, 80, FORMAT_PROG},
        {1680, 720, 2640, 750, 30, 81, FORMAT_PROG},
        {1680, 720, 2750, 750, 48, 110, FORMAT_PROG},

        {2560, 1080, 3750, 1100, 24, 86, FORMAT_PROG},
        {2560, 1080, 3200, 1125, 25, 87, FORMAT_PROG},
        {2560, 1080, 3520, 1125, 30, 88, FORMAT_PROG},
        {2560, 1080, 3750, 1100, 48, 113, FORMAT_PROG},

        {3840, 2160, 5500, 2250, 24, 93, FORMAT_PROG},
        {3840, 2160, 5280, 2250, 25, 94, FORMAT_PROG},
        {3840, 2160, 4400, 2250, 30, 95, FORMAT_PROG},
        {3840, 2160, 5500, 2250, 48, 114, FORMAT_PROG},

        {4096, 2160, 5500, 2250, 24, 98, FORMAT_PROG},
        {4096, 2160, 5280, 2250, 25, 99, FORMAT_PROG},
        {4096, 2160, 4400, 2250, 30, 100, FORMAT_PROG},
        {4096, 2160, 5500, 2250, 48, 115, FORMAT_PROG},

        {5120, 2160, 7500, 2200, 24, 121, FORMAT_PROG},
        {5120, 2160, 7200, 2200, 25, 122, FORMAT_PROG},
        {5120, 2160, 6000, 2200, 30, 123, FORMAT_PROG},
        {5120, 2160, 6250, 2475, 48, 124, FORMAT_PROG},

        {7680, 4320, 11000, 4500, 24, 194, FORMAT_PROG},
        {7680, 4320, 10800, 4400, 25, 195, FORMAT_PROG},
        {7680, 4320, 9000, 4400, 30, 196, FORMAT_PROG},
        {7680, 4320, 11000, 4500, 48, 197, FORMAT_PROG},

        {10240, 4320, 12500, 4950, 24, 210, FORMAT_PROG},
        {10240, 4320, 13500, 4400, 25, 211, FORMAT_PROG},
        {10240, 4320, 11000, 4500, 30, 212, FORMAT_PROG},
        {10240, 4320, 12500, 4950, 48, 213, FORMAT_PROG},

        // 50Hz
        {720, 576, 864, 625, 50, 17, FORMAT_PROG}, // 36
        {1280, 720, 1980, 750, 50, 19, FORMAT_PROG},
        {1920, 540, 2640, 562, 50, 20, FORMAT_INTL}, // Format I
        {1440, 288, 1728, 312, 50, 21, FORMAT_INTL}, // NOTE I/P
        {1440, 288, 1728, 312, 50, 23, FORMAT_PROG}, // NOTE
        {1440, 288, 1728, 313, 50, 23, FORMAT_PROG}, // NOTE
        {1440, 288, 1728, 314, 50, 23, FORMAT_PROG}, // NOTE
        {2880, 288, 3456, 312, 50, 25, FORMAT_INTL},
        {2880, 288, 3456, 312, 50, 27, FORMAT_PROG}, // NOTE
        {2880, 288, 3456, 313, 50, 27, FORMAT_PROG}, // NOTE
        {2880, 288, 3456, 314, 50, 27, FORMAT_PROG}, // NOTE
        {1440, 576, 1728, 625, 50, 29, FORMAT_PROG}, // NOTE I/P

        {1920, 1080, 2640, 1125, 50, 31, FORMAT_PROG},
        {2880, 576, 3456, 625, 50, 37, FORMAT_PROG},
        {1920, 1080, 2304, 1250, 50, 39, FORMAT_INTL},
        {1680, 720, 2200, 750, 50, 82, FORMAT_PROG},
        {2560, 1080, 3300, 1125, 50, 89, FORMAT_PROG},
        {3840, 2160, 5280, 2250, 50, 96, FORMAT_PROG},
        {4096, 2160, 5280, 2250, 50, 101, FORMAT_PROG},
        {5120, 2160, 6600, 2250, 50, 125, FORMAT_PROG},
        {7680, 4320, 10800, 4400, 50, 198, FORMAT_PROG},
        {10240, 4320, 13500, 4400, 50, 214, FORMAT_PROG},

        // 60Hz
        {640, 480, 800, 525, 60, 1, FORMAT_PROG}, // 58
        {720, 480, 858, 525, 60, 2, FORMAT_PROG},
        {1280, 720, 1650, 750, 60, 4, FORMAT_PROG},
        {1920, 540, 2200, 562, 60, 5, FORMAT_INTL},
        {1440, 240, 1716, 262, 60, 6, FORMAT_INTL}, // NOTE I/P
        {1440, 240, 1716, 262, 60, 8, FORMAT_PROG}, // NOTE
        {1440, 240, 1716, 263, 60, 8, FORMAT_PROG}, // NOTE
        {2880, 240, 3432, 262, 60, 10, FORMAT_INTL},
        {2880, 240, 3432, 262, 60, 12, FORMAT_PROG}, // NOTE
        {2880, 240, 3432, 263, 60, 12, FORMAT_PROG}, // NOTE
        {1440, 480, 1716, 525, 60, 14, FORMAT_PROG}, // NOTE I/P

        {1920, 1080, 2200, 1125, 60, 16, FORMAT_PROG},
        {2880, 480, 3432, 525, 60, 35, FORMAT_PROG},
        {1680, 720, 2200, 750, 60, 83, FORMAT_PROG},
        {2560, 1080, 3000, 1100, 60, 90, FORMAT_PROG},
        {3840, 2160, 4400, 2250, 60, 97, FORMAT_PROG},
        {4096, 2160, 4400, 2250, 60, 102, FORMAT_PROG},
        {5120, 2160, 5500, 2250, 60, 126, FORMAT_PROG},
        {7680, 4320, 9000, 4400, 60, 199, FORMAT_PROG},
        {10240, 4320, 11000, 44500, 60, 215, FORMAT_PROG},

        // 100Hz
        {1920, 540, 2640, 562, 100, 40, FORMAT_INTL}, // 78
        {1280, 720, 1980, 750, 100, 41, FORMAT_PROG},
        {720, 576, 864, 625, 100, 42, FORMAT_PROG},
        {1440, 288, 1728, 312, 100, 44, FORMAT_INTL},
        {1920, 1080, 2640, 1125, 100, 64, FORMAT_PROG},
        {1680, 720, 2000, 825, 100, 84, FORMAT_PROG},
        {2560, 1080, 2970, 1250, 100, 91, FORMAT_PROG},
        {3840, 2160, 5280, 2250, 100, 117, FORMAT_PROG},
        {5120, 2160, 6600, 2250, 100, 127, FORMAT_PROG},
        {7680, 4320, 10560, 4500, 100, 200, FORMAT_PROG},
        {10240, 4320, 13200, 4500, 100, 216, FORMAT_PROG},
        {4096, 2160, 5280, 2250, 100, 218, FORMAT_PROG},
        // 120Hz
        {1920, 540, 2200, 562, 120, 46, FORMAT_INTL},
        {1280, 720, 1650, 750, 120, 47, FORMAT_PROG},
        {720, 480, 858, 525, 120, 48, FORMAT_PROG},
        {1440, 240, 1716, 262, 120, 50, FORMAT_INTL},
        {1920, 1080, 2200, 1125, 120, 63, FORMAT_PROG},
        {1680, 720, 2000, 825, 120, 85, FORMAT_PROG},
        {2560, 1080, 3300, 1250, 120, 92, FORMAT_PROG},
        {3840, 2160, 4400, 2250, 120, 118, FORMAT_PROG},
        {5120, 2160, 5500, 2250, 120, 193, FORMAT_PROG},
        {7680, 4320, 8800, 4500, 120, 201, FORMAT_PROG},
        {10240, 4320, 11000, 4500, 120, 217, FORMAT_PROG},
        {4096, 2160, 4400, 2250, 120, 219, FORMAT_PROG},
        // 200Hz
        {720, 576, 864, 625, 200, 52, FORMAT_PROG}, // 102
        {1440, 288, 1728, 312, 200, 54, FORMAT_INTL},
        {1440, 288, 1728, 313, 200, 54, FORMAT_INTL},
        // 240Hz
        {720, 480, 858, 525, 240, 56, FORMAT_PROG},
        {1440, 240, 1716, 262, 240, 58, FORMAT_INTL},
        {1440, 240, 1716, 263, 240, 58, FORMAT_INTL}};

void Mod_Audio_HdmiTxInfoCvt(IN AudioChlInfo_S *pstRxInfo, OUT HdmiTx_S *pstHdmiTx)
{
    u8 ucCheckSum = 0;

    pstHdmiTx->ucLayout = pstRxInfo->ucLayout;
    pstHdmiTx->ucChannel = pstRxInfo->ucChannel;
    pstHdmiTx->ucFsValue = pstRxInfo->ucFsValue;
    pstHdmiTx->ucCodingType = pstRxInfo->ucCodingType;
    pstHdmiTx->szAudioInfo[0] = 0x84; // hb0
    pstHdmiTx->szAudioInfo[1] = 0x01; // hb1
    pstHdmiTx->szAudioInfo[2] = 0x0a; // hb2
    if (pstRxInfo->ucLayout > 0)
    {
        pstHdmiTx->szAudioInfo[4] = pstRxInfo->szAudioInfo[0]; // pb1
        pstHdmiTx->szAudioInfo[5] = pstRxInfo->szAudioInfo[1]; // pb2
        pstHdmiTx->szAudioInfo[6] = pstRxInfo->szAudioInfo[2]; // pb3
        pstHdmiTx->szAudioInfo[7] = pstRxInfo->szAudioInfo[3]; // pb4
        pstHdmiTx->szAudioInfo[8] = pstRxInfo->szAudioInfo[4]; // pb5
    }
    else
    {
        pstHdmiTx->szAudioInfo[4] = 0x00;
        pstHdmiTx->szAudioInfo[5] = 0x00;
        pstHdmiTx->szAudioInfo[6] = 0x00;
        pstHdmiTx->szAudioInfo[7] = 0x00;
        pstHdmiTx->szAudioInfo[8] = 0x00;
    }
    ucCheckSum += pstHdmiTx->szAudioInfo[0];
    ucCheckSum += pstHdmiTx->szAudioInfo[1];
    ucCheckSum += pstHdmiTx->szAudioInfo[2];
    ucCheckSum += pstHdmiTx->szAudioInfo[4];
    ucCheckSum += pstHdmiTx->szAudioInfo[5];
    ucCheckSum += pstHdmiTx->szAudioInfo[6];
    ucCheckSum += pstHdmiTx->szAudioInfo[7];
    ucCheckSum += pstHdmiTx->szAudioInfo[8];
    pstHdmiTx->szAudioInfo[3] = 256 - ucCheckSum; // pb0, check sum
}

void Mod_HdmiTx_ColorSpaceCal(IN ColorInfo_S *pstRxInfo, OUT HdmiTx_S *pstHdmiTx)
{
    pstHdmiTx->ucszAviPkt[0] = 0x00; // PB1, [7:5]color space: 0-rgb, 1-ycbcr422, 2-ycbcr444, 3-ycbcr420
    pstHdmiTx->ucszAviPkt[1] = 0x00; // PB2, [7:6]colorimetry; [3:0]active portion aspect ratio R3-R0
    pstHdmiTx->ucszAviPkt[2] = 0x00; // PB3, [6:4]colorimetry-ext; [3:2]rgb-range
    pstHdmiTx->ucszAviPkt[3] = 0x00; // PB4, [7:0]hdmi vic
    pstHdmiTx->ucszAviPkt[4] = 0x00; // PB5, [7:6]ycbcr-range
    pstHdmiTx->ucHdmiVic = 0x00;
    switch (pstRxInfo->ucPixelEncoding)
    {
    case RGB_0:
    case RGB_WIDE_4:
        pstHdmiTx->ucszAviPkt[0] = 0x00;
        pstHdmiTx->ucTxPixelEncoding = RGB_0;
        break;
    case YCbCr422_1:
        pstHdmiTx->ucszAviPkt[0] = 0x20;
        pstHdmiTx->ucTxPixelEncoding = YCbCr422_1;
        break;
    case YCbCr444_2:
        pstHdmiTx->ucszAviPkt[0] = 0x40;
        pstHdmiTx->ucTxPixelEncoding = YCbCr444_2;
        break;
    case YCbCr420_3:
        pstHdmiTx->ucszAviPkt[0] = 0x60;
        pstHdmiTx->ucTxPixelEncoding = YCbCr420_3;
        break;

    default:
        break;
    }
    pstHdmiTx->ucszAviPkt[0] |= BIT4_1; // PB1, [4]1-stand for the R3-R0 is active
    printLT(PRINT_PRIO_HIG, "\nucszAviPkt[0] = 0x%02bx", pstHdmiTx->ucszAviPkt[0]);
}

void Mod_HdmiTx_ColorRangeCal(IN ColorInfo_S *pstRxInfo, OUT HdmiTx_S *pstHdmiTx)
{
    switch (pstRxInfo->ucPixelEncoding)
    {
    case RGB_0:
    case RGB_WIDE_4:
#if RX_PORT_SIGN == DP_PORT
        if (pstRxInfo->b1DynamicRange == 1) // limit
        {
            pstHdmiTx->ucszAviPkt[2] |= 0x04; // PB3, [3:2]rgb-range: 01-limit, 10-full
        }
        else
        {
            pstHdmiTx->ucszAviPkt[2] |= 0x08; // PB3, [3:2]rgb-range: 01-limit, 10-full
        }
#endif
#if RX_PORT_SIGN == HDMI_PORT
        if (pstRxInfo->ucRgbRange == 1) // limit
        {
            pstHdmiTx->ucszAviPkt[2] |= 0x04; // PB3, [3:2]rgb-range: 01-limit, 10-full
        }
        else
        {
            pstHdmiTx->ucszAviPkt[2] |= 0x08; // PB3, [3:2]rgb-range: 01-limit, 10-full
        }
#endif
        break;
    default:
#if RX_PORT_SIGN == DP_PORT
        if (pstRxInfo->b1DynamicRange == 1) // limit
        {
            ; // PB5, [7:6]ycbcr-range: 00-limit, 01-full
        }
        else
        {
            pstHdmiTx->ucszAviPkt[4] |= 0x40; // PB5, [7:6]ycbcr-range: 00-limit, 01-full
        }
#endif
#if RX_PORT_SIGN == HDMI_PORT
        if (pstRxInfo->ucYccRange == 0) // limit
        {
            ; // PB5, [7:6]ycbcr-range: 00-limit, 01-full
        }
        else
        {
            pstHdmiTx->ucszAviPkt[4] |= 0x40; // PB5, [7:6]ycbcr-range: 00-limit, 01-full
        }
#endif
        break;
    }
}

void Mod_HdmiTx_ColorimetryCal(IN ColorInfo_S *pstRxInfo, OUT HdmiTx_S *pstHdmiTx)
{
    switch (pstRxInfo->ucPixelEncoding)
    {
    case RGB_0:
    case RGB_WIDE_4:
#if RX_PORT_SIGN == DP_PORT
        if (pstRxInfo->b1VscPkg == TRUE)
        {
            switch (pstRxInfo->ucColorimetryFormat)
            {
            case DP_VSC_ADOBE_RGB_3:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0; // PB2, [7:6]colorimetry: 3-use ext colorimetry
                pstHdmiTx->ucszAviPkt[2] |= 0x40; // PB3, [6:4]colorimetry-ext: HDMI_EXT_ADOBE_RGB_4
                break;
            case DP_VSC_ITUR_BT2020RGB_6:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0; // PB2, [7:6]colorimetry: 3-use ext colorimetry
                pstHdmiTx->ucszAviPkt[2] |= 0x60; // PB3, [6:4]colorimetry-ext: HDMI_EXT_ITUR_BT2020RGB_6
                break;
            default:
                break;
            }
        }
#endif
#if RX_PORT_SIGN == HDMI_PORT
        if (pstRxInfo->ucColorimetryFormat == 0x03) // 3-use ext colorimetry
        {
            pstHdmiTx->ucszAviPkt[1] |= 0xc0;                             // bit7:6 C1_C0 = 11
            pstHdmiTx->ucszAviPkt[2] |= pstRxInfo->ucColorimetryExt << 4; // bit6:4 EC2_EC1_EC0 = 110
        }
#endif
        break;
    default:
#if RX_PORT_SIGN == DP_PORT
        if (pstRxInfo->b1VscPkg == TRUE)
        {
            switch (pstRxInfo->ucColorimetryFormat)
            {
            case DP_VSC_ITUR_BT601_0:
                pstHdmiTx->ucszAviPkt[1] |= 0x40; // PB2, [7:6]colorimetry: 01-HDMI_SMPTE_170M
                break;
            case DP_VSC_ITUR_BT709_1:
                pstHdmiTx->ucszAviPkt[1] |= 0x80; // PB2, [7:6]colorimetry: 10-HDMI_ITUR_BT709_2
                break;
            case DP_VSC_XVYCC601_2:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0; // 3-use ext colorimetry
                pstHdmiTx->ucszAviPkt[2] |= 0x00; // PB3, [6:4]colorimetry-ext: 0-HDMI_EXT_XVYCC601_0
                break;
            case DP_VSC_XVYCC709_3:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0;
                pstHdmiTx->ucszAviPkt[2] |= 0x10; // PB3, [6:4]colorimetry-ext: 1-HDMI_EXT_XVYCC709_1
                break;
            case DP_VSC_SYCC601_4:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0;
                pstHdmiTx->ucszAviPkt[2] |= 0x20; // PB3, [6:4]colorimetry-ext: 2-HDMI_EXT_SYCC601_2
                break;
            case DP_VSC_OPYCC601_5:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0;
                pstHdmiTx->ucszAviPkt[2] |= 0x30; // PB3, [6:4]colorimetry-ext: 3-HDMI_EXT_ADOBE_YCC601_3
                break;
            case DP_VSC_ITUR_BT2020YCYBCYRC_6:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0;
                pstHdmiTx->ucszAviPkt[2] |= 0x50; // PB3, [6:4]colorimetry-ext: 5-HDMI_EXT_ITUR_BT2020YCYBCYRC_5
                break;
            case DP_VSC_ITUR_BT2020YCBCR_7:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0;
                pstHdmiTx->ucszAviPkt[2] |= 0x60; // PB3, [6:4]colorimetry-ext: 6-HDMI_EXT_ITUR_BT2020YCBCR_6
                break;
            default:
                break;
            }
        }
        else
        {
            switch (pstRxInfo->ucColorimetryFormat)
            {
            case DP_MISC0_XVYCC601_0:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0; // 3-use ext colorimetry
                pstHdmiTx->ucszAviPkt[2] |= 0x00; // PB3, [6:4]colorimetry-ext: 0-HDMI_EXT_XVYCC601_0
                break;
            case DP_MISC0_ITUR_BT601_1:
                pstHdmiTx->ucszAviPkt[1] |= 0x40; // PB2, [7:6]colorimetry: 01-HDMI_SMPTE_170M
                break;
            case DP_MISC0_XVYCC709_2:
                pstHdmiTx->ucszAviPkt[1] |= 0xc0;
                pstHdmiTx->ucszAviPkt[2] |= 0x10; // PB3, [6:4]colorimetry-ext: 1-HDMI_EXT_XVYCC709_1
                break;
            case DP_MISC0_ITUR_BT709_3:
                pstHdmiTx->ucszAviPkt[1] |= 0x80; // PB2, [7:6]colorimetry: 10-HDMI_ITUR_BT709_2
                break;
            default:
                break;
            }
        }
#endif
#if RX_PORT_SIGN == HDMI_PORT
        pstHdmiTx->ucszAviPkt[1] |= (pstRxInfo->ucColorimetryFormat << 6);
        if (pstRxInfo->ucColorimetryFormat == 0x03)
        {
            pstHdmiTx->ucszAviPkt[2] |= (pstRxInfo->ucColorimetryExt << 4);
        }
#endif
        break;
    }
}

void Mod_HdmiTx_AspectRatioCal(HdmiTx_S *pstHdmiTx)
{
    //    if((pstRxTimingInfo->usHact *9) == (pstRxTimingInfo->usVact *16))
    //    {
    //[5:4]01-4:3, 10-16:9; [3:0]1000-same as picture, 1001-4:3, 1010-16:9, 1011-14:9
    pstHdmiTx->ucszAviPkt[1] |= 0x28; // PB2, [5:4]picture aspect ratio, [3:0]active portion aspect ratio
    //    }
    //    else if((pstRxTimingInfo->usHact*9) == (pstRxTimingInfo->usVact*14))
    //    {
    //        pstHdmiTx->ucszAviPkt[1] |= 0x0b;//[3:0]active portion aspect ratio: 1011-14:9
    //    }
    //    else if((pstRxTimingInfo->usHact*3) == (pstRxTimingInfo->usVact*4))
    //    {
    //        pstHdmiTx->ucszAviPkt[1] |= 0x19;//[3:0]active portion aspect ratio: 1001-4:3
    //    }
    //    else
    //    {
    //        pstHdmiTx->ucszAviPkt[1] |= 0x08;//no data
    //    }
}

// void Mod_HdmiTx_VicCal(IN LtTiming_S *pstRxTimingInfo,OUT HdmiTx_S *pstHdmiTx)
//{
//     static u16 V_FrameRate = 0x00;
////    V_FrameRate = Drv_DpRx_FrameRate_Get();
//    V_FrameRate = pstRxTimingInfo->usFramerate;
//    if(abs(V_FrameRate - 120) <= 1)//119-121Hz
//    {
//        if((pstRxTimingInfo->usHtol == 4400)&&(pstRxTimingInfo->usHact == 3840))//3840*2160 120HZ  1188Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x76;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 5500)&&(pstRxTimingInfo->usHact == 5120))//5120*2160 120HZ  1485Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0xC1;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 4400)&&(pstRxTimingInfo->usHact == 4096))//4096*2160 120HZ  2376Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0xDB;//vic
//        }
//    }
//    else if(abs(V_FrameRate - 100) <= 1)//99-101Hz
//    {
//        if((pstRxTimingInfo->usHtol == 5280)&&(pstRxTimingInfo->usHact == 3840))//3840*2160 100HZ  2376Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x75;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 5280)&&(pstRxTimingInfo->usHact == 4096))//4096*2160 100HZ  1188Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0xDA;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 6600)&&(pstRxTimingInfo->usHact == 5120))//5120*2160 100HZ 1485Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x7F;//vic
//        }
//    }
//    else if(abs(V_FrameRate - 60) <= 1)//59-61Hz
//    {
//        if((pstRxTimingInfo->usHtol == 9000)&&(pstRxTimingInfo->usHact == 7680))//7680*4320 60HZ  2376Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0xC7;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 5500)&&(pstRxTimingInfo->usHact == 5120))//5120X2160 60HZ 742.5Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x7E;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 4400)&&(pstRxTimingInfo->usHact == 4096))//4096X2160 60HZ  594
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x66;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 4400)&&(pstRxTimingInfo->usHact == 3840))//3840X2160 60HZ  594
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x61;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 2200)&&(pstRxTimingInfo->usHact == 1920))//1920x1080
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x10;
//        }
//        else if((pstRxTimingInfo->usHtol == 1650)&&(pstRxTimingInfo->usHact == 1280))//1280X720
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x04;
//        }
//    }
//    else if(abs(V_FrameRate - 50) <= 1)//49-51Hz
//    {
//        if((pstRxTimingInfo->usHtol == 10800)&&(pstRxTimingInfo->usHact == 7680))//7680*4320 50HZ  2376Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0xC6;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 6600)&&(pstRxTimingInfo->usHact == 5120))//5120*2160 50HZ  742.5Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x7D;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 5280)&&(pstRxTimingInfo->usHact == 4096))//4096*2160 50HZ  594Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x65;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 5280)&&(pstRxTimingInfo->usHact == 3840))//3840*2160 50HZ  594Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x60;//vic
//        }
//    }
//    else if(abs(V_FrameRate - 30) <= 2)//28-32Hz
//    {
//        if((pstRxTimingInfo->usHtol == 9000)&&(pstRxTimingInfo->usHact == 7680))//7680*4320 30HZ  1188Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0xC4;//vic
//        }
//        else if ((pstRxTimingInfo->usHtol == 6000)&&(pstRxTimingInfo->usHact == 5120))//5120X2160 30HZ 396Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x7B;//vic
//        }
//        else if ((pstRxTimingInfo->usHtol == 4400)&&(pstRxTimingInfo->usHact == 4096))//4096X2160 30HZ 297Mhz
//        {
//            pstHdmiTx->ucHdmiVic  = 0x01;
//        }
//        else if ((pstRxTimingInfo->usHtol == 4400)&&(pstRxTimingInfo->usHact == 3840))//3840X2160 30HZ 297Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x5f;//vic
//        }
//    }
//    else if(abs(V_FrameRate - 24) <= 2)//22-26Hz
//    {
//        if((pstRxTimingInfo->usHtol == 10800)&&(pstRxTimingInfo->usHact == 7680))//7680*4320 25HZ  2376Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0xC3;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 11000)&&(pstRxTimingInfo->usHact == 7680))//7680*4320 24HZ  2376Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0xC2;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 7200)&&(pstRxTimingInfo->usHact == 5120))//5120*2160 25HZ  396Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x7A;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 7500)&&(pstRxTimingInfo->usHact == 5120))//5120*2160 24HZ  396Mhz
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x79;//vic
//        }
//        else if((pstRxTimingInfo->usHtol == 5500)&&(pstRxTimingInfo->usHact == 3840))//3840X2160 24HZ
//        {
//            pstHdmiTx->ucHdmiVic  = 0x03;
//        }
//        else if ((pstRxTimingInfo->usHtol == 5280)&&(pstRxTimingInfo->usHact == 3840))//3840X2160 25HZ
//        {
//            pstHdmiTx->ucHdmiVic  = 0x02;
//        }
//        else if((pstRxTimingInfo->usHtol == 5500)&&(pstRxTimingInfo->usHact == 4096))//4096 X2160 24HZ
//        {
//            pstHdmiTx->ucHdmiVic  = 0x04;
//        }
//        else if((pstRxTimingInfo->usHtol == 5280)&&(pstRxTimingInfo->usHact == 4096))//4096 X2160 25HZ
//        {
//            pstHdmiTx->ucszAviPkt[3] = 0x63;//vic
//        }
//    }
//    printLT(PRINT_PRIO_TEST, "\nAVIVIC = 0x%02bx,HDMIVIC = 0x%02bx",pstHdmiTx->ucszAviPkt[3],pstHdmiTx->ucHdmiVic);
//}

void Mod_HdmiTx_VicCal(IN LtTiming_S *pstRxTimingInfo, OUT HdmiTx_S *pstHdmiTx)
{
    u8 ucTimingCnt;
    u8 ucInterlaceFlag;
    static u16 V_FrameRate = 0x00;

#if RX_PORT_SIGN == DP_PORT
    ucInterlaceFlag = Drv_DpRx_InterlaceGet();
#endif
#if RX_PORT_SIGN == HDMI_PORT
    ucInterlaceFlag = Mod_HdmiRx_InterlaceGet();
#endif
    //    V_FrameRate = Drv_DpRx_FrameRate_Get();
    V_FrameRate = pstRxTimingInfo->usFramerate;
    for (ucTimingCnt = 0; ucTimingCnt < 108; ucTimingCnt++)
    {
        if (abs(V_FrameRate - szTimeTable[ucTimingCnt][4]) <= 1)
        {
            if (ucInterlaceFlag == szTimeTable[ucTimingCnt][6]) // P/I Format
            {
                if ((pstRxTimingInfo->usHact == szTimeTable[ucTimingCnt][0]) && (pstRxTimingInfo->usVact == szTimeTable[ucTimingCnt][1]) && (pstRxTimingInfo->usHtol == szTimeTable[ucTimingCnt][2]))
                {
                    if (pstRxTimingInfo->usVtol == szTimeTable[ucTimingCnt][3]) // NOTE:VIC=27
                    {
                        pstHdmiTx->ucszAviPkt[3] = szTimeTable[ucTimingCnt][5]; // vic
                        break;
                    }
                }
                else
                {
                    ;
                }
            }
            else
            {
                ;
            }
        }
        else
        {
            ;
        }
    }

    if (pstHdmiTx->ucszAviPkt[3] == 95)
    {
        pstHdmiTx->ucHdmiVic = 0x01;
        pstHdmiTx->ucszAviPkt[3] = 0x00;
    }
    else if (pstHdmiTx->ucszAviPkt[3] == 94)
    {
        pstHdmiTx->ucHdmiVic = 0x02;
        pstHdmiTx->ucszAviPkt[3] = 0x00;
    }
    else if (pstHdmiTx->ucszAviPkt[3] == 93)
    {
        pstHdmiTx->ucHdmiVic = 0x03;
        pstHdmiTx->ucszAviPkt[3] = 0x00;
    }
    else if (pstHdmiTx->ucszAviPkt[3] == 98)
    {
        pstHdmiTx->ucHdmiVic = 0x04;
        pstHdmiTx->ucszAviPkt[3] = 0x00;
    }
#if RX_PORT_SIGN == DP_PORT
#if DPRX_TIMING_HBE == ENABLED
    if (g_stDpRx.b2IsTimingHBE == HBE_TYPE_UHD_60Hz)
    {
        pstHdmiTx->ucszAviPkt[3] = 97;
    }
    else if (g_stDpRx.b2IsTimingHBE == HBE_TYPE_UHD_50Hz)
    {
        pstHdmiTx->ucszAviPkt[3] = 96;
    }
    else if (g_stDpRx.b2IsTimingHBE == HBE_TYPE_4K2K_50Hz)
    {
        pstHdmiTx->ucszAviPkt[3] = 101;
    }
#endif
#endif
    printLT(PRINT_PRIO_TEST, "\nAVIVIC = 0x%02bx,HDMIVIC = 0x%02bx", pstHdmiTx->ucszAviPkt[3], pstHdmiTx->ucHdmiVic);
}

void Mod_HdmiTx_ColorDepthCal(IN ColorInfo_S *pstRxInfo, OUT HdmiTx_S *pstHdmiTx)
{
    pstHdmiTx->ucColorDepth = DEEP_8BIT;
#if RX_PORT_SIGN == DP_PORT
    switch (pstRxInfo->ucBitDepth)
    {
    case DPRX_10BIT_2:
        pstHdmiTx->ucColorDepth = DEEP_10BIT;
        break;
    case DPRX_12BIT_3:
        pstHdmiTx->ucColorDepth = DEEP_12BIT;
        break;
    default:
        break;
    }
#endif

#if RX_PORT_SIGN == HDMI_PORT
    switch (pstRxInfo->ucBitDepth)
    {
    case HDMIRX_10BIT_5:
        pstHdmiTx->ucColorDepth = DEEP_10BIT;
        break;
    case HDMIRX_12BIT_6:
        pstHdmiTx->ucColorDepth = DEEP_12BIT;
        break;
    default:
        break;
    }
#endif

    if (pstRxInfo->ucPixelEncoding == YCbCr422_1) // 422 force 12bit
    {
        pstHdmiTx->ucColorDepth = DEEP_8BIT;
    }
}
#endif

//----------------------------------------------------------------mipi tx/lvds tx-------------------------------------------------------------------------------
#if ((TX_PORT_SIGN == MIPI_PORT) || (TX_PORT_SIGN == LVDS_PORT))

void PWM_Init(u8 ucPwmGPIO, u8 ucPwmKhz, u8 ucValue) // ucvalue:0~100
{
    static u8 PreDuty = 0;
    u16 CycleFreq;
    u16 Cycle;
    if (ucValue > 100)
    {
        LTLog(LOG_INFO, "\nIncorrect PWM Duty");
        return;
    }

    if (PreDuty != ucValue)
    {
        PreDuty = ucValue;
        LTLog(LOG_INFO, "\nPWM Duty:%bd", ucValue);

        CycleFreq = 48000 / ucPwmKhz;
        if (ucValue == 100)
        {
            Cycle = CycleFreq;
        }
        else
        {
            Cycle = (CycleFreq / 100) * (ucValue);
        }

        Drv_Gpio_ModeSet(PWM_GPIO, OUT_PP_2x | NO_PU_PD, VOL_3_3);
        Drv_Gpio_OutSignalSet(PWM_GPIO, Io_Function0);

        switch (ucPwmGPIO)
        {
        case GPIO20_PWM0:
            Drv_PWM0_Sel(CycleFreq, Cycle);
            break;
        case GPIO22_PWM1:
            Drv_PWM1_Sel(CycleFreq, Cycle);
            break;
        case GPIO24_PWM2:
            Drv_PWM2_Sel(CycleFreq, Cycle);
            break;
        case GPIO25_PWM3:
            Drv_PWM3_Sel(CycleFreq, Cycle);
            break;

        default:
            break;
        }
    }
}

#if RX_PORT_SIGN == DP_PORT

#if CUSTOM_EDID_SWITCH == ENABLED
volatile u8 l_ucEDIDnum;
volatile u8 l_ucPreEDIDnum;

code u8 EDID_A[512] =
    {

        ////1920X1080 60Hz
        0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x06, 0xB3, 0x11, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x06, 0x22, 0x01, 0x04, 0xA5, 0x0C, 0x07, 0x78, 0x3A, 0x85, 0x95, 0xAB, 0x52, 0x38, 0xB3, 0x26,
        0x0A, 0x50, 0x54, 0x20, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1A, 0x36, 0x80, 0xA0, 0x70, 0x38, 0x1E, 0x40, 0x30, 0x20,
        0xA5, 0x00, 0x80, 0x38, 0x74, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x3C, 0x3C, 0x43,
        0x44, 0x0F, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x4D,
        0x31, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF,
        0x00, 0x4E, 0x36, 0x4C, 0x4A, 0x43, 0x4B, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x01, 0x6C,
        0x02, 0x03, 0x0C, 0xF1, 0x23, 0x09, 0x07, 0x07, 0x83, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40

        // 3840X1080 60Hz
        // 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x06,0xB3,0x11,0x00,0x01,0x00,0x00,0x00,
        // 0x06,0x22,0x01,0x04,0xA5,0x0C,0x07,0x78,0x3A,0x85,0x95,0xAB,0x52,0x38,0xB3,0x26,
        // 0x0A,0x50,0x54,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        // 0x01,0x01,0x01,0x01,0x01,0x01,0x1A,0x68,0x00,0xA0,0xF0,0x38,0x1E,0x40,0x30,0x20,
        // 0xA2,0x01,0x80,0x38,0x74,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x3C,0x3C,0x43,
        // 0x44,0x1E,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x4D,
        // 0x31,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFF,
        // 0x00,0x4E,0x36,0x4C,0x4A,0x43,0x4B,0x30,0x30,0x30,0x30,0x30,0x30,0x20,0x01,0x4D,
        // 0x02,0x03,0x0C,0xF1,0x23,0x09,0x07,0x07,0x83,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40

};

code u8 EDID_B[512] =
    {

        ////3840X1080 60Hz
        0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x06, 0xB3, 0x11, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x06, 0x22, 0x01, 0x04, 0xA5, 0x0C, 0x07, 0x78, 0x3A, 0x85, 0x95, 0xAB, 0x52, 0x38, 0xB3, 0x26,
        0x0A, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1A, 0x68, 0x00, 0xA0, 0xF0, 0x38, 0x1E, 0x40, 0x30, 0x20,
        0xA2, 0x01, 0x80, 0x38, 0x74, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x3C, 0x3C, 0x43,
        0x44, 0x1E, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x4D,
        0x31, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF,
        0x00, 0x4E, 0x36, 0x4C, 0x4A, 0x43, 0x4B, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x01, 0x4D,
        0x02, 0x03, 0x0C, 0xF1, 0x23, 0x09, 0x07, 0x07, 0x83, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40

        ////1920X1080 60Hz
        // 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x06,0xB3,0x11,0x00,0x01,0x00,0x00,0x00,
        // 0x06,0x22,0x01,0x04,0xA5,0x0C,0x07,0x78,0x3A,0x85,0x95,0xAB,0x52,0x38,0xB3,0x26,
        // 0x0A,0x50,0x54,0x20,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        // 0x01,0x01,0x01,0x01,0x01,0x01,0x1A,0x36,0x80,0xA0,0x70,0x38,0x1E,0x40,0x30,0x20,
        // 0xA5,0x00,0x80,0x38,0x74,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x3C,0x3C,0x43,
        // 0x44,0x0F,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x4D,
        // 0x31,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFF,
        // 0x00,0x4E,0x36,0x4C,0x4A,0x43,0x4B,0x30,0x30,0x30,0x30,0x30,0x30,0x20,0x01,0x6C,
        // 0x02,0x03,0x0C,0xF1,0x23,0x09,0x07,0x07,0x83,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40

};

void Custom_EDID_Select(void)
{
    l_ucEDIDnum = EDID_SWITCH_REG;
}

void Custom_EDID_Config(u8 *szEdidData)
{
#if 0
    switch ( l_ucEDIDnum )
    {
        case 0 :
    		l_CustomTimingStr.PixClk = 300000;
    		l_CustomTimingStr.Htot = 2000;
    		l_CustomTimingStr.Hact = 1920;
    		l_CustomTimingStr.Hfp = 32;
    		l_CustomTimingStr.Hsw = 16;
    		l_CustomTimingStr.Hbp = 32;
    		l_CustomTimingStr.Vtot = 1250;
    		l_CustomTimingStr.Vact = 1200;
    		l_CustomTimingStr.Vfp = 9;
    		l_CustomTimingStr.Vsw = 5;
    		l_CustomTimingStr.Vbp = 36;
    		l_CustomTimingStr.Hspol = 1;
    		l_CustomTimingStr.Vspol = 1;		        
            break;
        case 1 :
    		l_CustomTimingStr.PixClk = 600000;
    		l_CustomTimingStr.Htot = 4000;
    		l_CustomTimingStr.Hact = 3840;
    		l_CustomTimingStr.Hfp = 64;
    		l_CustomTimingStr.Hsw = 32;
    		l_CustomTimingStr.Hbp = 64;
    		l_CustomTimingStr.Vtot = 1220;
    		l_CustomTimingStr.Vact = 1200;
    		l_CustomTimingStr.Vfp = 9;
    		l_CustomTimingStr.Vsw = 5;
    		l_CustomTimingStr.Vbp = 6;
    		l_CustomTimingStr.Hspol = 1;
    		l_CustomTimingStr.Vspol = 1;	       
            break;
        default:
            break;
    }
    EDID_Dtb_18Bytes_Calc(ucEDID+0x36);
    EDID_Dtb_18Bytes_Calc(ucEDID+0x48);
#else
    switch (l_ucEDIDnum)
    {
    case 0:
        memcpy(szEdidData, EDID_A, 512);
        break;
    case 1:
        memcpy(szEdidData, EDID_B, 512);
        break;
    default:
        break;
    }
#endif
}

void Custom_Init(void)
{
    Custom_EDID_Select();
    Custom_EDID_Config(szEdidData);

    l_ucEDIDnum = EDID_SWITCH_REG;
    l_ucPreEDIDnum = l_ucEDIDnum;

    switch (l_ucEDIDnum)
    {
    case 0:
        g_stDpRx.ucRxMaxLinkRate = HBR;
        g_stDpRx.ucRxMaxLaneCount = TWO_LANE;

        // MIPI
        g_stMipiTx.uc3DMode = 1;
        g_stMipiTx.ucTxPortNum = 2;
        g_stMipiTx.ucLMTXPortSel = 0xDD;

        //						g_stLvdsTx.ucLvdsTx3DMode = 0;
        //						g_stLvdsTx.ucLvdsTxPortNum = 2;
        //						g_stLvdsTx.ucLMTXPortSel = 0xDD;

        break;
    case 1:
        g_stDpRx.ucRxMaxLinkRate = HBR;
        g_stDpRx.ucRxMaxLaneCount = FOUR_LANE;

        g_stMipiTx.uc3DMode = 1;
        g_stMipiTx.ucTxPortNum = 4;
        g_stMipiTx.ucLMTXPortSel = 0xE4;

        //						g_stLvdsTx.ucLvdsTx3DMode = 1;
        //						g_stLvdsTx.ucLvdsTxPortNum = 4;
        //						g_stLvdsTx.ucLMTXPortSel = 0x8D;
        break;
    default:
        break;
    }
}

void Custom_EDID_Switch(void)
{
    if (g_stDpRx.ucRxState >= STATE_DPRX_WAIT_LINK_TRAIN_6)
    {
        if (l_ucPreEDIDnum != l_ucEDIDnum)
        {
            LTLog(LOG_INFO, "\n Resolution Switch");
            l_ucPreEDIDnum = l_ucEDIDnum;
            Custom_EDID_Config(szEdidData);
#if TX_PORT_SIGN == MIPI_PORT
            Mod_MipiTx_PowerOnInit();
            g_stMipiTx.b1UpstreamDeviceReady = TRUE;
#else
            Mod_LvdsTx_PowerOnInit();
#endif
            switch (l_ucEDIDnum)
            {
            case 0:
                g_stDpRx.ucRxMaxLinkRate = HBR;
                g_stDpRx.ucRxMaxLaneCount = TWO_LANE;

                // MIPI
                g_stMipiTx.uc3DMode = 1;
                g_stMipiTx.ucTxPortNum = 2;
                g_stMipiTx.ucLMTXPortSel = 0xDD;

                //										g_stLvdsTx.ucLvdsTx3DMode = 0;
                //										g_stLvdsTx.ucLvdsTxPortNum = 2;
                //										g_stLvdsTx.ucLMTXPortSel = 0xDD;
                break;
            case 1:
                g_stDpRx.ucRxMaxLinkRate = HBR;
                g_stDpRx.ucRxMaxLaneCount = FOUR_LANE;

                g_stMipiTx.uc3DMode = 1;
                g_stMipiTx.ucTxPortNum = 4;
                g_stMipiTx.ucLMTXPortSel = 0xE4;

                //										g_stLvdsTx.ucLvdsTx3DMode = 1;
                //										g_stLvdsTx.ucLvdsTxPortNum = 4;
                //										g_stLvdsTx.ucLMTXPortSel = 0x8D;
                break;
            default:
                break;
            }

            // IO setting

#if TYPECRX_EN == ENABLED
            {
                UCCStatus.uclaneCount = g_stDpRx.ucRxMaxLaneCount;
                UCCStatus.b1Multi_Function = (g_stDpRx.ucRxMaxLaneCount == 4) ? (0) : (1);
                UCCMSG.pDataOrder = szCC_DataMsg[10];
                Mod_CC1Msg_Send();
                UCCMSG.ucLastMsgType = 0xff;
                Ocm_Delay1ms(1000);
                LTLog(LOG_INFO, "\nAtten Low");
            }
#else
            {
                Drv_DpRx_HpdSet(HPD_LOW, IRQ_LOW);
                Ocm_Delay1ms(300);
                LTLog(LOG_INFO, "\nHPD Low");
            }
#endif
            Mod_DpRx_SetState(STATE_DPRX_DOWNSTREAM_READY_4);
        }
    }
}

void Custom_Handler(void)
{
    Custom_EDID_Select();
    Custom_EDID_Switch();
}
#endif
#endif

struct TIMING l_CustomTimingStr =
//{ 74250//PixelClock/1000
//, 1650//Htotal
//, 1280//Hactive
//, 110//Hfp
//, 40//Hsw
//, 220//Hbp
//, 750//Vtotal
//, 720//Vactive
//, 5//Vfp
//, 5//Vsw
//, 20//Vbp
//, 1//Hspol
//, 1//Vspol
//};

//{ 162000//PixelClock/1000
//, 2160//Htotal
//, 1600//Hactive
//, 64//Hfp
//, 192//Hsw
//, 304//Hbp
//, 1250//Vtotal
//, 1200//Vactive
//, 1//Vfp
//, 3//Vsw
//, 46//Vbp
//, 1//Hspol
//, 1//Vspol
//};

// { 148500//PixelClock/1000
// , 2200//Htotal
// , 1920//Hactive
// , 88//Hfp
// , 44//Hsw
// , 148//Hbp
// , 1125//Vtotal
// , 1080//Vactive
// , 4//Vfp
// , 5//Vsw
// , 36//Vbp
// , 1//Hspol
// , 1//Vspol
// };

// 2160x2160@90Hz
// {
//     475800  // PixelClock/1000
// ,   2376    // Htotal
// ,   2160    // Hactive
// ,   108     // Hfp
// ,   42      // Hsw
// ,   66     // Hbp
// ,   2225    // Vtotal
// ,   2160    // Vactive
// ,   57      // Vfp
// ,   4       // Vsw
// ,   4       // Vbp
// ,   1       // Hspol
// ,   1       // Vspol
// };

// 4320x2160@90Hz
{
    908000  // PixelClock/1000
,   4536    // Htotal
,   4320    // Hactive
,   108     // Hfp
,   42      // Hsw
,   66      // Hbp
,   2225    // Vtotal
,   2160    // Vactive
,   57      // Vfp
,   4       // Vsw
,   4       // Vbp
,   1       // Hspol
,   1       // Vspol
};

#if ((LVDXTX_VID_PATTERN_MODE != NO_PATTERN) || (MIPITX_VID_PATTERN_MODE != NO_PATTERN))
void ModPattern_Init(void)
{
    u8 Value_0xA32A, Value_0xA32B; //,Value_0xF337;
    /*
HalfPixclk/A32B/0X80 /A32B/0X90 /A32B/0XA0  /A32B/0XB0  /A32B/0XC0  /A32B/0XD0  /A32B/0XE0
0xA32A[6:0]  1        2           4          8           16          32          64
    48      600     300         150         75          37.5        18.75       9.375
    49      612.5   306.25      153.125     76.5625     38.28125    19.140625   9.5703125
    50      625     312.5       156.25      78.125      39.0625     19.53125    9.765625
    51      637.5   318.75      159.375     79.6875     39.84375    19.921875   9.9609375
    52      650     325         162.5       81.25       40.625      20.3125     10.15625
    53      662.5   331.25      165.625     82.8125     41.40625    20.703125   10.3515625
    54      675     337.5       168.75      84.375      42.1875     21.09375    10.546875
    55      687.5   343.75      171.875     85.9375     42.96875    21.484375   10.7421875
    56      700     350         175         87.5        43.75       21.875      10.9375
    57      712.5   356.25      178.125     89.0625     44.53125    22.265625   11.1328125
    58      725     362.5       181.25      90.625      45.3125     22.65625    11.328125
    59      737.5   368.75      184.375     92.1875     46.09375    23.046875   11.5234375
    60      750     375         187.5       93.75       46.875      23.4375     11.71875
    61      762.5   381.25      190.625     95.3125     47.65625    23.828125   11.9140625
    62      775     387.5       193.75      96.875      48.4375     24.21875    12.109375
    63      787.5   393.75      196.875     98.4375     49.21875    24.609375   12.3046875
    64      800     400         200         100         50          25          12.5
    65      812.5   406.25      203.125     101.5625    50.78125    25.390625   12.6953125
    66      825     412.5       206.25      103.125     51.5625     25.78125    12.890625
    67      837.5   418.75      209.375     104.6875    52.34375    26.171875   13.0859375
    68      850     425         212.5       106.25      53.125      26.5625     13.28125
    69      862.5   431.25      215.625     107.8125    53.90625    26.953125   13.4765625
    70      875     437.5       218.75      109.375     54.6875     27.34375    13.671875
    71      887.5   443.75      221.875     110.9375    55.46875    27.734375   13.8671875
    72      900     450         225         112.5       56.25       28.125      14.0625
    73      912.5   456.25      228.125     114.0625    57.03125    28.515625   14.2578125
    74      925     462.5       231.25      115.625     57.8125     28.90625    14.453125
    75      937.5   468.75      234.375     117.1875    58.59375    29.296875   14.6484375
    76      950     475         237.5       118.75      59.375      29.6875     14.84375
    77      962.5   481.25      240.625     120.3125    60.15625    30.078125   15.0390625
    78      975     487.5       243.75      121.875     60.9375     30.46875    15.234375
    79      987.5   493.75      246.875     123.4375    61.71875    30.859375   15.4296875
    80      1000    500         250         125         62.5        31.25       15.625
    81      1012.5  506.25      253.125     126.5625    63.28125    31.640625   15.8203125
    82      1025    512.5       256.25      128.125     64.0625     32.03125    16.015625
    83      1037.5  518.75      259.375     129.6875    64.84375    32.421875   16.2109375
    84      1050    525         262.5       131.25      65.625      32.8125     16.40625
    85      1062.5  531.25      265.625     132.8125    66.40625    33.203125   16.6015625
    86      1075    537.5       268.75      134.375     67.1875     33.59375    16.796875
    87      1087.5  543.75      271.875     135.9375    67.96875    33.984375   16.9921875
    88      1100    550         275         137.5       68.75       34.375      17.1875
    89      1112.5  556.25      278.125     139.0625    69.53125    34.765625   17.3828125
    90      1125    562.5       281.25      140.625     70.3125     35.15625    17.578125
    91      1137.5  568.75      284.375     142.1875    71.09375    35.546875   17.7734375
    92      1150    575         287.5       143.75      71.875      35.9375     17.96875
    93      1162.5  581.25      290.625     145.3125    72.65625    36.328125   18.1640625
    94      1175    587.5       293.75      146.875     73.4375     36.71875    18.359375
    95      1187.5  593.75      296.875     148.4375    74.21875    37.109375   18.5546875
    96      1200    600         300         150         75          37.5        18.75

    example:
    halfPixelClock = 74.25M : Value_0xA32A = 95(0x5F) , Value_0xA32B = 0xC0
    halfPixelClock = 148.5M : Value_0xA32A = 95(0x5F) , Value_0xA32B = 0xB0
    halfPixelClock = 297M   : Value_0xA32A = 95(0x5F) , Value_0xA32B = 0xA0
    halfPixelClock = 594M   : Value_0xA32A = 95(0x5F) , Value_0xA32B = 0x90
    */
    Value_0xA32A = 73;      // 72
    Value_0xA32B = 0x90;    // A0

    Drv_PtnTiming_Set(&l_CustomTimingStr);
    Drv_PtnClk_Set(Value_0xA32A, Value_0xA32B); // Set the Half pixel clock
    Drv_PtnPCR_Init();
    Drv_PtnType_Sel();
    Drv_PtnDataClk_Mux();
}
#endif

#endif
