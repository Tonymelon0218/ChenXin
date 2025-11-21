/******************************************************************************
  * @project: LT2204
  * @file: ChipMipi.c
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.26
/******************************************************************************/
#include "include.h"

#if TX_PORT_SIGN == MIPI_PORT

StructMipiTx g_stMipiTx;
StructTiming g_stMipiTxVideoTiming;

u8 code szMipiEdid[512] = {
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x06, 0xB3, 0xA0, 0x28, 0x01, 0x01, 0x01, 0x01,
    0x04, 0x1F, 0x01, 0x03, 0x80, 0x3E, 0x22, 0x78, 0xEE, 0x69, 0x95, 0xAD, 0x52, 0x46, 0xA1, 0x27,
    0x0F, 0x50, 0x54, 0xBF, 0xCF, 0x00, 0x81, 0x40, 0x81, 0x80, 0x95, 0x00, 0x71, 0x4F, 0x81, 0xC0,
    0xB3, 0x00, 0xD1, 0xC0, 0x01, 0x01, 0x08, 0xE8, 0x00, 0x30, 0xF2, 0x70, 0x5A, 0x80, 0xB0, 0x58,
    0x8A, 0x00, 0x55, 0x50, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x18, 0x90, 0x1E,
    0xFF, 0x8A, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x56,
    0x47, 0x32, 0x38, 0x55, 0x51, 0x4C, 0x31, 0x41, 0x0A, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF,
    0x00, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x32, 0x38, 0x0A, 0x01, 0xF0,
    0x02, 0x03, 0x5A, 0xF1, 0x50, 0x04, 0x13, 0x1F, 0x10, 0x0F, 0x1E, 0x01, 0x5D, 0x5E, 0x5F, 0x60,
    0x61, 0x76, 0x03, 0x12, 0x3F, 0x23, 0x09, 0x07, 0x07, 0x83, 0x01, 0x00, 0x00, 0xE2, 0x00, 0xEA,
    0x6D, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x38, 0x3C, 0x28, 0x00, 0x60, 0x01, 0x02, 0x03, 0x6D, 0xD8,
    0x5D, 0xC4, 0x01, 0x78, 0x88, 0x53, 0x12, 0x30, 0x78, 0x83, 0x34, 0x1D, 0x6D, 0x1A, 0x00, 0x00,
    0x02, 0x01, 0x30, 0x90, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE3, 0x05, 0xC0, 0x00, 0xE4, 0x21,
    0x00, 0x1C, 0x00, 0xE6, 0x06, 0x05, 0x01, 0x60, 0x60, 0x12, 0x36, 0x6C, 0x80, 0xA0, 0x70, 0x70,
    0x3E, 0x80, 0x30, 0x20, 0x08, 0x0C, 0x6D, 0x55, 0x21, 0x00, 0x00, 0x1A, 0x6F, 0xC2, 0x00, 0xA0,
    0xA0, 0xA0, 0x55, 0x50, 0x30, 0x20, 0x35, 0x00, 0x6D, 0x55, 0x21, 0x00, 0x00, 0x1A, 0x00, 0x27};

u8 szEdidData[512];

StructMipiVideoFmtCfg g_MipiVideoFmtCfg[] =
    {
#if MIPITX_PRO_SEL == MIPITX_DSI
        {DSI_RGB_565, 16, 0x00, 0x0E, MIPITX_DSI},
        {DSI_RGB_666, 18, 0x10, 0x1E, MIPITX_DSI},
        {DSI_RGB_888, 24, 0x21, 0x3E, MIPITX_DSI}, // 默认DSI
        {DSI_RGB_30, 30, 0x41, 0x0D, MIPITX_DSI},
        {DSI_YUV422_16Bit, 16, 0x01, 0x2C, MIPITX_DSI},
        {DSI_YUV422_20Bit, 24, 0x24, 0x0C, MIPITX_DSI}, // 按照24bit发送 422 20 spec
        {DSI_YUV422_24Bit, 24, 0x23, 0x1C, MIPITX_DSI},
        {DSI_YUV420_12Bit, 24, 0x20, 0x3D, MIPITX_DSI}, // TODO:
#else
        {CSI_RGB_565, 16, 0x02, 0x22, MIPITX_CSI},
        {CSI_RGB_666, 18, 0x11, 0x23, MIPITX_CSI},
        {CSI_RGB_888, 24, 0x25, 0x24, MIPITX_CSI},
        {CSI_YUV422_8Bit, 16, 0x01, 0x1E, MIPITX_CSI}, // 默认CSI
        {CSI_YUV422_10Bit, 20, 0x31, 0x1F, MIPITX_CSI},
        {CSI_YUV420_8Bit, 24, 0x20, 0x1A, MIPITX_CSI}
#endif
};

void Mod_MipiTx_PowerOnInit(void)
{
    memset(&g_stMipiTx, 0, sizeof(StructMipiTx));
    g_stMipiTx.ucTxState = STATE_MIPITX_POWER_ON_1;

#if (MIPITX_PRO_SEL == MIPITX_CSI)
    Drv_MipiTx_CSIFeSoftwareSendInit();
#endif
}

void Mod_MipiTx_SetState(u8 ucState)
{
    if (ucState != g_stMipiTx.ucTxState)
    {
#if (MIPITX_PRO_SEL == MIPITX_CSI)
#if (1 == CSI_SOFTWARE_SEND_FE)
        if (STATE_MIPITX_PLAY_BACK_8 == g_stMipiTx.ucTxState))
            {
                Drv_MipiTx_CSIFeSoftwareSend();
                LTLog(LOG_INFO, "CSI Software Send Frame End");
            }
#endif
#endif

        if (ucState == STATE_MIPITX_VIDEO_OUT_5)
        {
            TX_Event_Set(TX_VIDEO_ON_EVENT_3);
        }
        g_stMipiTx.ucTxStateChangeFlag = TRUE;
        g_stMipiTx.ucTxState = ucState;
        LTLog(LOG_DEBUG, "TxState = 0x%02bx", ucState);
    }
}

// TODO: 外界做一个接口，对内只涉及RX （un)plug、video on/off,不用细分是dp 还是hdmi
/*
0 : Source unplug 1:source plug
2: video  OFF     3:video ON
*/
void Mod_LMTx_EventMonitor(u8 ucMsgType)
{
#define SOURECE_PLUG_EVENT 1
#define SOURECE_UNPLUG_EVENT 2
#define VIDEO_ON_EVENT 3
#define VIDEO_OFF_EVENT 4

    switch (ucMsgType)
    {
    case SOURECE_UNPLUG_EVENT: // HDMIRX_SOURECE_UNPLUG_EVENT  DPRX_SOURECE_UNPLUG_EVENT:
        g_stMipiTx.b1UpstreamDeviceReady = FALSE;
        LTLog(LOG_INFO, "RX Set Event:%02bx ", ucMsgType);
        break;
    case SOURECE_PLUG_EVENT: // HDMIRX_SOURECE_PLUG_EVENT DPRX_SOURECE_PLUG_EVENT
        g_stMipiTx.b1UpstreamDeviceReady = TRUE;
        LTLog(LOG_INFO, "RX Set Event:%02bx ", ucMsgType);
        break;
    case VIDEO_OFF_EVENT: // HDMIRX_VIDEO_OFF_EVENT DPRX_VIDEO_OFF_EVENT
        g_stMipiTx.b1UpstreamVideoReady = FALSE;
        LTLog(LOG_INFO, "RX Set Event:%02bx ", ucMsgType);
        break;
    case VIDEO_ON_EVENT: // HDMIRX_VIDEO_ON_EVENT DPRX_VIDEO_ON_EVENT
        g_stMipiTx.b1UpstreamVideoReady = TRUE;
        LTLog(LOG_INFO, "RX Set Event:%02bx ", ucMsgType);
        break;
    default:
        break;
    }
}

u8 Mod_MipiTx_VidEnCmd_Get(u8 IsCtrlEn, u8 UserReg)
{
    if (IsCtrlEn == ENABLED)
    {
        if (UserReg != 0)
        {
            return ON;
        }
        return OFF;
    }
    return ON;
}

void Mod_MipiTx_EventProc()
{
    u8 ucMinState = 0xFF;

    if (g_stMipiTx.ucTxState > STATE_MIPITX_UPSTREAM_DEVICE_READY_2)
    {
        if (g_stMipiTx.b1UpstreamDeviceReady == FALSE)
        {
            Mod_MipiTx_SetState(STATE_MIPITX_UPSTREAM_DEVICE_READY_2);
        }
    }

    if (g_stMipiTx.ucTxState > STATE_MIPITX_UPSTREAM_VIDEO_READY_3)
    {
        if (g_stMipiTx.b1UpstreamVideoReady == FALSE)
        {
            Mod_MipiTx_SetState(STATE_MIPITX_UPSTREAM_VIDEO_READY_3);
        }
    }

    if (g_stMipiTx.ucTxState >= STATE_MIPITX_VIDEO_OUT_5)
    {
#if MIPI_OUT_CTRL == ENABLED
        if (Mod_MipiTx_VidEnCmd_Get(ENABLED, USER_VIDEOEN_REG) == OFF) // default off
#else
        if (Mod_MipiTx_VidEnCmd_Get(DISABLED, USER_VIDEOEN_REG) == OFF) // default on
#endif
        {
            if (g_stMipiTx.b1MIPITXStreamOn == ON)
            {
                g_stMipiTx.b1MIPITXStreamOn = OFF;
                Drv_MipiTx_Rst(DISABLED);
                Drv_MipiTx_VideoSet(OFF);
            }
        }
        else
        {
            if (g_stMipiTx.b1MIPITXStreamOn == OFF)
            {
                ucMinState = min(ucMinState, STATE_MIPITX_VIDEO_OUT_5);
                g_stMipiTx.b1MIPITXStreamOn = ON;
            }
        }
    }

    if (ucMinState != 0xFF)
    {
        Mod_MipiTx_SetState(ucMinState);
    }
}

void Mod_MipiTx_PllSet()
{
    u32 ulByteclk, ulPhyClk;

    ulPhyClk = g_stMipiTx.ulMipiDataRate;
    ulByteclk = ulPhyClk >> 3;
    LTLog(LOG_DEBUG, "MipiInClk:%ld, calc ulByteclk:%ld, ulPhyClk:%ld, ucBpp:%bd, ucTxPortNum:0x%02bx, ucTxLaneNum:0x%02bx",
          g_stMipiTx.ulMipiInClk, ulByteclk, ulPhyClk, g_stMipiTx.ucBpp, g_stMipiTx.ucTxPortNum, g_stMipiTx.ucTxLaneNum);

    Drv_MipiTx_PllSet(ulPhyClk);
}

u8 Mod_MipiTx_PllCaliIfSucc()
{
    return Drv_MipiTx_PllCali();
}

void Mod_MipiTx_PhyTimingSet()
{
    u32 ulMipiDataRate = g_stMipiTx.ulMipiDataRate;
    u8 b1MipiClockburst = g_stMipiTx.b1MipiClockburst;
    u8 ucPhySel = g_stMipiTx.ucTxPhySel;
    u8 ucDphyCsi8Lane = g_stMipiTx.b1DphyCsi8Lane;
    Drv_MipiTx_PhyTimingParaSet(ulMipiDataRate, b1MipiClockburst, ucPhySel, ucDphyCsi8Lane);
}

u8 Mod_MipiTx_BppCalculate(u8 ucMIPIDataFmt)
{
    u8 ucBpp = 24;
    u8 ucIndex = 0;
    for (ucIndex = 0; ucIndex < sizeof(g_MipiVideoFmtCfg) / sizeof(g_MipiVideoFmtCfg[0]); ucIndex++)
    {
        if (ucMIPIDataFmt == g_MipiVideoFmtCfg[ucIndex].ucVideoFmt)
        {
            ucBpp = g_MipiVideoFmtCfg[ucIndex].ucBpp;
            break;
        }
    }

    return ucBpp;
}

void Mod_MipiTx_PortLaneAdj()
{
#if MIPITX_PRO_SEL == MIPITX_CSI
    if (MIPITX_DPHY == g_stMipiTx.ucTxPhySel)
    {
        if (g_stMipiTx.ulMipiInClk > 600000) // over 4K60
        {
            g_stMipiTx.ucTxPortNum = MIPI_2PORT; // TODO: 默认是CSI 8lane1901 如果超过600m
            g_stMipiTx.ucTxLaneNum = MIPI_PORT_4LANE;
        }
        //        else
        //        {
        //            g_stMipiTx.ucTxPortNum = MIPI_1PORT;
        //            g_stMipiTx.ucTxLaneNum = MIPI_PORT_4LANE;
        //        }
    }
#endif

    if (MIPITX_CPHY == g_stMipiTx.ucTxPhySel)
    {
        if (g_stMipiTx.ucTxLaneNum > MIPI_PORT_3LANE) // for cphy , up to 3lane
        {
            g_stMipiTx.ucTxLaneNum = MIPI_PORT_3LANE;
        }
    }
}

void Mod_MipiTx_CfgParaInit()
{
    u32 ulMipiInClk;
    g_stMipiTx.ucTxLaneNum = MIPI_LANE_NUM;
    g_stMipiTx.b1MipiClockburst = MIPI_CLOCK_BURST;
    g_stMipiTx.b1DSIVideoMode = MIPI_DSI_VIDEO_MODE;
    g_stMipiTx.ucTxPhySel = MIPITX_PHY_SEL;
    g_stMipiTx.ucTxFormat = MIPITX_VIDEO_FORMAT;

#if RX_PORT_SIGN == DP_PORT
#if CUSTOM_EDID_SWITCH == ENABLED

#else
    g_stMipiTx.ucTxPortNum = MIPI_PORT_NUM;
    g_stMipiTx.uc3DMode = MIPITX_3D_MODE_SEL;
#endif
#endif

#if RX_PORT_SIGN == HDMI_PORT
    g_stMipiTx.ucTxPortNum = MIPI_PORT_NUM;
    g_stMipiTx.uc3DMode = MIPITX_3D_MODE_SEL;
#endif

    g_stMipiTx.ucBpp = Mod_MipiTx_BppCalculate(g_stMipiTx.ucTxFormat);
    g_stMipiTx.b1MIPITXStreamOn = OFF;

    g_stMipiTx.b1MIPITXProSel = MIPITX_PRO_SEL;
    // Get input BPP
    ulMipiInClk = Drv_MipiTx_GetMipiInClk();
    if (0 != ulMipiInClk)
    {
        g_stMipiTx.ulMipiInClk = ulMipiInClk;
    }
    // adjust port or lane
    Mod_MipiTx_PortLaneAdj();
}
void Mod_MipiTx_DataRateAdj()
{
    if (MIPITX_DPHY == g_stMipiTx.ucTxPhySel)
    {
        g_stMipiTx.ulMipiDataRate = g_stMipiTx.ulMipiInClk * 2 * g_stMipiTx.ucBpp / (g_stMipiTx.ucTxPortNum * g_stMipiTx.ucTxLaneNum);
    }
    else
    {
        g_stMipiTx.ulMipiDataRate = g_stMipiTx.ulMipiInClk * 2 * g_stMipiTx.ucBpp * 7 / (16 * g_stMipiTx.ucTxPortNum * g_stMipiTx.ucTxLaneNum);
    }

    if (MIPI_NO_3D_MODE != g_stMipiTx.uc3DMode) // ref 1901
    {
        g_stMipiTx.ulMipiDataRate += 115000;
    }
    else
    {
        g_stMipiTx.ulMipiDataRate += 80000;
    }

    if (g_stMipiTx.b1MipiClockburst) // ref 2102
    {
        g_stMipiTx.ulMipiDataRate += 80000;
        LTLog(LOG_INFO, "Burst Mode lane rate increase 80M");
    }

    g_stMipiTx.ulMipiDataRate += 50000; // MIPI 速率增加50M

    if (g_stMipiTx.ulMipiDataRate < MIPITX_PLL_LOW) // set byteclk minium value to 50M , phyclk minium value is 400M
    {
        g_stMipiTx.ulMipiDataRate = MIPITX_PLL_LOW;
    }
    if (g_stMipiTx.ulMipiDataRate > MIPITX_PLL_HIGH) // set byteclk maxmum value to 312.5M , phyclk maxmum value is 2.5G
    {
        g_stMipiTx.ulMipiDataRate = MIPITX_PLL_HIGH;
    }
}

void Mod_MipiTx_SetDataType(u8 ucVideoFormat)
{
#if MIPITX_PRO_SEL == MIPITX_DSI
    u8 ucDataType = 0x3E;
    u8 ucBppAndFmtSel = 0x21; // rgb 888
#else
    u8 ucDataType = 0x1E;
    u8 ucBppAndFmtSel = 0x01; // CSI 422 8bit
#endif
    u8 ucIndex = 0;

#if MIPITX_DSC != ENABLED
    for (ucIndex = 0; ucIndex < sizeof(g_MipiVideoFmtCfg) / sizeof(g_MipiVideoFmtCfg[0]); ucIndex++)
    {
        if (ucVideoFormat == g_MipiVideoFmtCfg[ucIndex].ucVideoFmt)
        {
            ucDataType = g_MipiVideoFmtCfg[ucIndex].ucDatatype;
            ucBppAndFmtSel = g_MipiVideoFmtCfg[ucIndex].ucBppAndFmtsel;
            break;
        }
    }
#else
    // todo:
    ucDataType = 0x0B;
    ucBppAndFmtSel = 0x25;
#endif

#if RX_PORT_SIGN == DP_PORT
#if (DPRX_DSC_BYPASS_SUPPORT == ENABLED)
    if (Drv_DpRxDscBy_SwitchGet() == ENABLED)
    {
        ucDataType = 0x0B;
        ucBppAndFmtSel = 0x25;
    }
#endif
#endif

#if RX_PORT_SIGN == HDMI_PORT
#if (HDMIRX_DSC_BYPASS_SUPPORT == ENABLED)
    if (Drv_HdmiRxDscBy_SwitchGet() == ENABLED)
    {
        ucDataType = 0x0B;
        ucBppAndFmtSel = 0x25;
    }
#endif
#endif

    Drv_MipiTx_DataTypeSet(ucDataType, ucBppAndFmtSel);
}

void Mod_MipiTx_Resolution_Config()
{
    // 获取timing信息
    memset(&g_stMipiTxVideoTiming, 0, sizeof(StructTiming));
    Drv_VideoCheckAll_Get(&g_stMipiTxVideoTiming);
    LTLog(LOG_INFO, "RX[H]: Htotal:%d,Hactive:%d,Hsw:%d,Hfp:%d,Hbp:%d,Hspol:%bd", g_stMipiTxVideoTiming.Htotal, g_stMipiTxVideoTiming.Hactive, g_stMipiTxVideoTiming.Hsw, g_stMipiTxVideoTiming.Hfp, g_stMipiTxVideoTiming.Hbp, g_stMipiTxVideoTiming.Hspol);
    LTLog(LOG_INFO, "RX[V]: Vtotal:%d,Vactive:%d,Vsw:%d,Vfp:%d,Vbp:%d,Vspol:%bd", g_stMipiTxVideoTiming.Vtotal, g_stMipiTxVideoTiming.Vactive, g_stMipiTxVideoTiming.Vsw, g_stMipiTxVideoTiming.Vfp, g_stMipiTxVideoTiming.Vbp, g_stMipiTxVideoTiming.Vspol);
    // 设置mipi timing信息
    Drv_MipiTx_TimingSet(&g_stMipiTxVideoTiming);

    // 极性获取
    Drv_MipiTx_InHSyncPol_Sel(g_stMipiTxVideoTiming.Hspol);
    Drv_MipiTx_InVSyncPol_Sel(g_stMipiTxVideoTiming.Vspol);
}

void Mod_MipiTx_Digital_Config()
{
    Drv_MipiTx_Rst(ENABLED);
    Drv_MipiTx_LaneSwap(); // if need adjust lane,please modify
    Drv_MipiTx_PortSwap(g_stMipiTx.ucTxPortNum);
    Drv_MipiTx_PortNumSet(g_stMipiTx.ucTxPortNum);
    Drv_MipiTx_LaneNumSet(g_stMipiTx.ucTxLaneNum);
    LTLog(LOG_INFO, "Port: %02bx, Lane: %02bx", g_stMipiTx.ucTxPortNum, g_stMipiTx.ucTxLaneNum);
#if MIPITX_PHY_SEL == MIPITX_CPHY
    Drv_MipiTx_CPhyEn(ENABLED);
    LTLog(LOG_INFO, "select Mipi Cphy");
    // TODO: 这里没有clk 可以选择，数字和模拟都未提供，不影响Dphy以及非8lane Dphy CSI
    SET_BIT(BKA3_7B_REG, BIT2);
#else
    Drv_MipiTx_DPhyClkDataSet();
    Drv_MipiTx_DPhyClkModeSet(g_stMipiTx.b1MipiClockburst);
#if MIPITX_PRO_SEL == MIPITX_DSI
    Drv_MipiTx_DSIVideoModeSet(g_stMipiTx.b1DSIVideoMode);
#endif
    CLEAR_BIT(BKA3_7B_REG, BIT2);
    if (g_stMipiTx.b1DphyCsi8Lane)
    {
        // TODO: DPHY CSI 8Lane 无法选择write clk
        SET_BIT(BKA3_7B_REG, BIT2);
        Drv_MipiTx_DPhyCSI8LaneEn(ENABLED);
    }
    Drv_MipiTx_EotpSet(ENABLED);

#endif
    Drv_MipiTx_PhyModeSet(g_stMipiTx.ucTxPhySel);
    Drv_MipiTx_LmtxModeSet(g_stMipiTx.ucTxPhySel);
    Drv_MipiTx_LmtxSrcSet();
    Drv_MipiTx_LmtxInputDataSet();
    Drv_MipiTx_LmtxSramInputSet();
    // TODO: 0xF97A bit 4 - MIPI protocol vactive select:HW or SW?
#if (MIPITX_PRO_SEL == MIPITX_CSI)
    // 开启 CSI frame number enable.
    Drv_MipiTx_FrameCntSet(ON);
#else
    Drv_MipiTx_HssLP_En(MIPITX_HSS_BURST_EN);
    Drv_MipiTx_FrameCntSet(OFF);
#endif

    Drv_MipiTx_3DModeSet(g_stMipiTx.uc3DMode);

    Mod_MipiTx_SetDataType(g_stMipiTx.ucTxFormat);

#if RX_PORT_SIGN == DP_PORT
#if (DPRX_DSC_BYPASS_SUPPORT == ENABLED)
    if (Drv_DpRxDscBy_SwitchGet() == ENABLED)
    {
        LTLog(LOG_INFO, "DSC soft wordcnt;");
        Drv_MipiTx_WordCnt_Set(SW_MODE, g_stDpRxDscByTiming.usHact / g_stMipiTx.ucTxPortNum, g_stMipiTx.ucTxPortNum);
        Drv_MipiTx_Dsc_Split(g_stMipiTxVideoTiming.Hactive, g_stMipiTx.ucTxPortNum);
    }
#endif
#endif

#if MIPITX_DSC == ENABLED
    LTLog(LOG_INFO, "DSC soft wordcnt;");
    Drv_MipiTx_WordCnt_Set(SW_MODE, g_stMipiTxDscEncVideoTiming.Hactive / g_stMipiTx.ucTxPortNum, g_stMipiTx.ucTxPortNum);
    Drv_MipiTx_Dsc_Split(g_stMipiTxVideoTiming.Hactive, g_stMipiTx.ucTxPortNum);
#endif
}

void Mod_MipiTx_Anolog_Config()
{
    Drv_MipiTx_PhySet(MP0_EN, MP1_EN, MP2_EN, MP3_EN);
}

void Mod_MipiTx_HssSet()
{
    u16 Hss = 0x0A;
#if (MIPITX_PRO_SEL == MIPITX_CSI)
    if (MIPITX_DPHY == g_stMipiTx.ucTxPhySel)
    {
        if (g_stMipiTx.b1MipiClockburst == ENABLED)
        {
            Hss = (3 * Drv_mipiTx_GetHsRqstPre() + Drv_MipiTx_GetHsTrail() + 9) / 2 + 20;
        }
        else
        {
            Hss = (Drv_mipiTx_GetHsRqstPre() + (Drv_MipiTx_GetHsTrail() + 13) / 2) + 20;
        }
    }
#else
    if (MIPITX_CPHY == g_stMipiTx.ucTxPhySel)
    {
        if (3 != g_stMipiTx.ucTxLaneNum)
        {
            Hss = 0x20;
        }
    }
#if MIPITX_HSCMD_EN == ENABLED
    {
        Hss = MIPITX_HSCMD_HSSLEN;
    }
#endif
#endif

    Drv_MipiTx_Hss_Set(Hss);
}

void Mod_MipiTx_FifoRddly_Config()
{
    u16 rdpixclk, rdbyteclk, rdhss, rgodhact;
    u32 rddly, rddly_max, rddly_min1, rddly_min2;
    u32 Temp;

    rdpixclk = (u16)(g_stMipiTx.ulMipiInClk / 1000);
    rdbyteclk = (u16)(g_stMipiTx.ulMipiDataRate / 2000);
    if (MIPITX_DPHY == g_stMipiTx.ucTxPhySel)
    {
        rdbyteclk /= 8;
    }
    else
    {
        rdbyteclk /= 7;
    }

    if ((ENABLED == g_stMipiTx.b1DphyCsi8Lane) || (MIPITX_CPHY == g_stMipiTx.ucTxPhySel))
    {
        rdbyteclk <<= 1;
    }
    rdbyteclk *= g_stMipiTx.ucTxPortNum;
    rdhss = Drv_MipiTx_Hss_Get();
    rgodhact = Drv_MipiTx_FSMHact_Get();

    LTLog(LOG_DEBUG, "rdbyteclk:%d, rdpixclk:%d ", rdbyteclk, rdpixclk);
    LTLog(LOG_DEBUG, "hsw:%d, hbp:%d hactive:%d", g_stMipiTxVideoTiming.Hsw, g_stMipiTxVideoTiming.Hbp, g_stMipiTxVideoTiming.Hactive);

    Temp = (rdbyteclk * (g_stMipiTxVideoTiming.Hsw / 2 + g_stMipiTxVideoTiming.Hbp / 2) / rdpixclk);
    if (Temp > rdhss)
    {
        rddly_min1 = (rdbyteclk * (g_stMipiTxVideoTiming.Hsw / 2 + g_stMipiTxVideoTiming.Hbp / 2) / rdpixclk) - rdhss;
    }
    else
    {
        rddly_min1 = 0;
    }

    if (1 == g_stMipiTx.ucTxPortNum)
    {
        rddly_min2 = (u32)rdbyteclk * (g_stMipiTxVideoTiming.Hsw / 2 + g_stMipiTxVideoTiming.Hbp / 2 + g_stMipiTxVideoTiming.Hactive / 2);
        Temp = ((u32)rddly_min2 / (u32)rdpixclk);
        if (Temp > (rdhss + rgodhact))
        {
            rddly_min2 = (u32)(((u32)rddly_min2 / (u32)rdpixclk) - rdhss - rgodhact);
        }
        else
        {
            rddly_min2 = 0;
        }
    }
    else
    {
        rddly_min2 = rddly_min1;
    }

    if (rddly_min1 > rddly_min2)
    {
        rddly_min2 = rddly_min1;
    }

    LTLog(LOG_DEBUG, "ucBpp 0x%02bx;", g_stMipiTx.ucBpp);

    rddly_max = 0x8000 / (g_stMipiTx.ucBpp << 1);
    rddly_max = rdbyteclk * (rddly_max + g_stMipiTxVideoTiming.Hsw / 2 + g_stMipiTxVideoTiming.Hbp / 2);
    rddly_max = rddly_max / (u32)rdpixclk - rdhss;
    // rddly = (rddly_max - rddly_min2) / 20 + rddly_min2;
    rddly = (rddly_max / 7) + rddly_min2;

    if (2 == g_stMipiTx.ucTxPortNum && g_stMipiTxVideoTiming.Hbp > 1000) // 720P 25Hz hbp=2268 以上公式不可用
    {
        rddly = rddly_max / 7 + rddly_min2 / 2;
    }

    LTLog(LOG_INFO, "read delay:%lu", rddly);

    Drv_MipiTx_FifoDelay_Set(rddly);
}

void Mod_MipiTx_ByteClk_Chk(void)
{
    u32 TempClock = 0;

    Drv_System_FmSet(TOP_FM, 0x31);
    Ocm_Delay1ms(5);
    TempClock = Drv_System_FmGet(TOP_FM, 0);
    LTLog(LOG_INFO, "Ad_lmtx_write_clk = %lukhz", TempClock);

    Drv_System_FmSet(TOP_FM, 0x30);
    Ocm_Delay1ms(5);
    TempClock = Drv_System_FmGet(TOP_FM, 0);
    LTLog(LOG_INFO, "Ad_lmtx_read_clk = %lukhz", TempClock);
}

void Mod_MipiTx_StateHandler()
{
    switch (g_stMipiTx.ucTxState)
    {
    case STATE_MIPITX_POWER_ON_1:
        Mod_MipiTx_SetState(STATE_MIPITX_UPSTREAM_DEVICE_READY_2);
        break;

    case STATE_MIPITX_UPSTREAM_DEVICE_READY_2:
        if (g_stMipiTx.ucTxStateChangeFlag)
        {
            g_stMipiTx.ucTxStateChangeFlag = FALSE;
            Drv_MipiTx_VideoSet(OFF);
            Drv_GPIO19Vsync_Set(DISABLED);
#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD))
            g_stHdmiRx.b1DownstreamDeviceReady = TRUE;
#if EDID_FLASH == ENABLED
            {
                Custom_EDID_LoadFromFlash();
            }
#else
            memcpy(szEdidData, szMipiEdid, 512);
#endif
#endif

#if ((CHIP_SEL == LT7911UXE_DP) || (CHIP_SEL == LT6911GXD_DP))
            g_stDpRx.b1DownstreamDeviceReady = TRUE;
#if EDID_FLASH == ENABLED
            {
                Custom_EDID_LoadFromFlash();
            }
#else
#if CUSTOM_EDID_SWITCH == ENABLED

#else
            memcpy(szEdidData, szMipiEdid, 512);
#endif
#endif
#endif
        }

        if (g_stMipiTx.b1UpstreamDeviceReady)
        {
            Mod_MipiTx_SetState(STATE_MIPITX_UPSTREAM_VIDEO_READY_3);
        }
        break;
    case STATE_MIPITX_UPSTREAM_VIDEO_READY_3:
        if (g_stMipiTx.ucTxStateChangeFlag)
        {
            g_stMipiTx.ucTxStateChangeFlag = FALSE;
            Drv_MipiTx_VideoSet(OFF);
            Drv_GPIO19Vsync_Set(DISABLED);
        }

        if (g_stMipiTx.b1UpstreamVideoReady)
        {
            Mod_MipiTx_SetState(STATE_MIPITX_CONFIG_VIDEO_AUDIO_4);
#if MIPITX_DSC == ENABLED
            Drv_Sys_EncPowerDomain(FALSE);
            // Drv_Gpio_ModeSet(GPIO6_D2, OUT_PP_2x | NO_PU_PD, VOL_3_3);//led 适配飞线
            Mod_MipiTxDscEnc_Config();
            Ocm_Delay1ms(20);
#endif

            Drv_Sys_DHTxPowerDomain(FALSE);
        }
        break;

    case STATE_MIPITX_CONFIG_VIDEO_AUDIO_4:
        Mod_MipiTx_CfgParaInit();
        Mod_MipiTx_DataRateAdj();
        Mod_MipiTx_PllSet();

        if (!Mod_MipiTx_PllCaliIfSucc())
        {
            return;
        }
        Mod_MipiTx_Resolution_Config();
        Mod_MipiTx_PhyTimingSet();
        Mod_MipiTx_Digital_Config(); // TODO:
        Mod_MipiTx_Anolog_Config();  // TODO:

        Mod_MipiTx_HssSet();
        Mod_MipiTx_FifoRddly_Config();
        Mod_MipiTx_ByteClk_Chk();

        Mod_MipiTx_SetState(STATE_MIPITX_VIDEO_OUT_5);
        break;
    case STATE_MIPITX_VIDEO_OUT_5:
        if (g_stMipiTx.b1MIPITXStreamOn == ON)
        {
            Drv_MipiTx_Rst(ENABLED);
#if (MIPITX_PRO_SEL == MIPITX_DSI)
            // 25090302: GPIO Control
            Drv_Gpio_ModeSet(GPIO12_D1_VDET, OUT_PP_2x | NO_PU_PD, VOL_1_8);
            Drv_IOSoftLevel_Set(GPIO12_D1_VDET, HIGH); // GPIO12 1.8V供电
            Ocm_Delay1ms(50);

            Drv_Gpio_ModeSet(GPIO0_EARCN, OUT_PP_2x | NO_PU_PD, VOL_3_3);
            Drv_IOSoftLevel_Set(GPIO0_EARCN, HIGH); // GPIO0 正负电压
            Ocm_Delay1ms(50);

            Drv_Gpio_ModeSet(GPIO15_D2_VDET, OUT_PP_2x | NO_PU_PD, VOL_3_3);
            Drv_IOSoftLevel_Set(GPIO15_D2_VDET, HIGH); // GPIO15 复位
            Ocm_Delay1ms(5);
            Drv_Gpio_ModeSet(GPIO1_EARCP, OUT_PP_2x | NO_PU_PD, VOL_3_3);
            Drv_IOSoftLevel_Set(GPIO1_EARCP, HIGH); // GPIO1 复位
            Ocm_Delay1ms(200);

            Mod_DCS_Init(); // 下发屏参指令
            Ocm_Delay1ms(200);

            Drv_Gpio_ModeSet(GPIO3_DHRX_DCAUXP, OUT_PP_2x | NO_PU_PD, VOL_3_3);
            Drv_IOSoftLevel_Set(GPIO3_DHRX_DCAUXP, HIGH); // GPIO3 背光
            Ocm_Delay1ms(50);

            Drv_Gpio_ModeSet(GPIO24_PWM2, OUT_PP_2x | NO_PU_PD, VOL_3_3);
            Drv_IOSoftLevel_Set(GPIO24_PWM2, HIGH); // GPIO24 PWM
            Ocm_Delay1ms(50);

#endif

            if (MIPITX_DPHY == g_stMipiTx.ucTxPhySel)
            {
                Drv_MipiTx_DPhyClkHsTrig();
                Drv_MipiTx_DPhySkewCali();
            }

            Drv_MipiTx_VideoSet(ON);
            Mod_MipiTx_SetState(STATE_MIPITX_AUDIO_OUT_6);
        }
        break;
    case STATE_MIPITX_AUDIO_OUT_6:
        Drv_Audio_Init();
#if TDM_SUPPORT == ENABLED
        Drv_Audio_TdmOutInit();
#endif
        Mod_MipiTx_SetState(STATE_MIPITX_PLAY_BACK_7);
        break;
    case STATE_MIPITX_PLAY_BACK_7:
        break;
    default:
        break;
    }
}

void Mod_MipiTx_Handler(void)
{
    Mod_MipiTx_StateHandler();
    Mod_MipiTx_EventProc();
}

void Mod_MIPITx_Pattern(void)
{
#if MIPITX_VID_PATTERN_MODE != NO_PATTERN
    ModPattern_Init();
    g_stMipiTx.b1UpstreamVideoReady = TRUE;
    g_stMipiTx.b1UpstreamDeviceReady = TRUE;

#if CSC_SUPPORT == ENABLED

#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD))
    LT6911GXE_HdmiRxCscOrEncSel();
    LT6911GXE_HdmiRxCscCvt();
#endif

#if ((CHIP_SEL == LT7911UXE_DP) || (CHIP_SEL == LT6911GXD_DP))
    LT7911GXE_DpRxCscOrEncSel();
    LT7911GXE_DpRxCscCvt();
#endif

#endif
    while (1)
    {
        Mod_MipiTx_Handler();
    }
#endif
}

#endif
