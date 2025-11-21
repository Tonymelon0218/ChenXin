//////////////////////////////////////
// Project:   LT2204
// Filename:  LT7911GXE.c
// Version:   V1.0
// Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

#if ((CHIP_SEL == LT7911UXE_DP) || (CHIP_SEL == LT6911GXD_DP))

volatile u8 l_ucTriggerEn = 0;

volatile u8 l_ucBrightness;
volatile u8 l_ucPreBrightness;
//========================================================================
// Func Name   : LT7911GXE_PowerOnInit
// Description :
// Input       : None
// Output      : None
// Return      :
//========================================================================
void LT7911GXE_PowerOnInit(void)
{
#if TYPECRX_EN == ENABLED
    Mod_CC1Vari_Init();
    Mod_CC2Vari_Init();
#endif
    Mod_DpRx_PowerOnInit();
#if TX_PORT_SIGN == MIPI_PORT
    Mod_MipiTx_PowerOnInit();
#endif

#if TX_PORT_SIGN == LVDS_PORT
    Mod_LvdsTx_PowerOnInit();
#endif
    Drv_Sys_DecPowerDomain(TRUE);
    Drv_Sys_EncPowerDomain(TRUE);
    // Drv_Sys_DHTxPowerDomain(TRUE);// dhtx rest
#if (DPRX_HDCP_DEC_MODE == NO_HDCP)
    Drv_Sys_LT7911gxe_HdcpRx_PowerDomain(TRUE);
#endif
#if (TX_PORT_SIGN == MIPI_PORT)
    Drv_Sys_LT7911gxe_MipiTx_PowerDomain(TRUE);
#endif
#if (TX_PORT_SIGN == LVDS_PORT)
    Drv_Sys_LT7911gxe_LvdsTx_PowerDomain(TRUE);
#endif

/**********************LT7911UXE INT IO************************/
#if CHIP_SEL == LT7911UXE_DP
    Drv_Gpio_ModeSet(INT, OUT_PP_2x | NO_PU_PD, VOL_3_3);
    Drv_IOSoftLevel_Set(INT, HIGH); // INT default high
#endif

/**********************LT6911GXD INT(GPIO25_PWM3) IO************************/
#if CHIP_SEL == LT6911GXD_DP
    Drv_Gpio_ModeSet(GPIO25_PWM3, OUT_PP_2x | NO_PU_PD, VOL_3_3);
    Drv_IOSoftLevel_Set(GPIO25_PWM3, HIGH); // GPIO25 default high
#endif

    LT7911GXE_I2SGPIO_Init();

#if PWM_OUT == ENABLED
    {
        PWM_Init(PWM_GPIO, PWM_FREQ, PWM_DUTY);
    }
#endif

    l_ucTriggerEn = DISABLED;
    TX_Event_Init();

#if CUSTOM_EDID_SWITCH == ENABLED
    Custom_Init();
#endif

#if TX_PORT_SIGN == MIPI_PORT
    App_Brightness_Init();
#endif
}

void LT7911GXE_DpRxVarInit(void)
{
#if CUSTOM_EDID_SWITCH == ENABLED

#else
    g_stDpRx.ucRxMaxLinkRate = DPRX_LINK_RATE;
    g_stDpRx.ucRxMaxLaneCount = DPRX_LANE_COUNT;
#endif
    g_stDpRx.b1Ssc_Support = DPRX_SSC_SUPPORT_EN;
    g_stDpRx.b1Tps3_Support = DPRX_TPS3_SUPPORT_EN;
    g_stDpRx.b1Tps4_Support = DPRX_TPS4_SUPPORT_EN;
    memset(&g_stAuxStatus, 0x00, sizeof(AuxStatus_S));
#if DPRX_MST_MODE_EN == ENABLED
    memset(&g_stMstRxStatus, 0, sizeof(MstRxStatus_S));
    g_stMstRxStatus.payload_update = 1;
    g_stMstRxStatus.payload_clear = 1; // payload_update and payload_clear set to 1, is clear vc playload id
    g_stMstRxStatus.sink_cnt = DPRX_MST_SINK_CNT;
    g_stAuxStatus.FecFlag = 0x00;
#endif
}

void LT7911GXE_I2SGPIO_Init(void)
{
#if GPIO_1P8V == ENABLED
    Drv_I2sGpio_1P8VSet();
#endif
    //	Drv_Gpio_ModeSet(GPIO31_MCLKB, OUT_PP_2x|NO_PU_PD, VOL_3_3);
    //	Drv_Gpio_ModeSet(GPIO32_SCLKB, OUT_PP_2x|NO_PU_PD, VOL_3_3);
    //	Drv_Gpio_ModeSet(GPIO30_WSB, OUT_PP_2x|NO_PU_PD, VOL_3_3);
    //	Drv_Gpio_ModeSet(GPIO29_SD0B, OUT_PP_2x|NO_PU_PD, VOL_3_3);
    //	Drv_Gpio_ModeSet(GPIO28_SD1B, OUT_PP_2x|NO_PU_PD, VOL_3_3);
    //	Drv_Gpio_ModeSet(GPIO27_SD2B, OUT_PP_2x|NO_PU_PD, VOL_3_3);
    //	Drv_Gpio_ModeSet(GPIO26_SD3B, OUT_PP_2x|NO_PU_PD, VOL_3_3);
}

void GPIO_Trigger_Hdl(void)
{
    static u32 ulCurrentTime = 0;

    /**********************LT7911UXE INT IO************************/
#if CHIP_SEL == LT7911UXE_DP
    if (l_ucTriggerEn)
    {
        if (Drv_GPIO_INT_level_Get() == HIGH)
        {
            Drv_IOSoftLevel_Set(INT, LOW);
            Ocm_Timer_UpdLocalTime(&ulCurrentTime);
            printLT(PRINT_PRIO_HIG, "\nGPIO Trigger Low");
        }
    }

    if (l_ucTriggerEn)
    {
        if (Drv_GPIO_INT_level_Get() == LOW)
        {
            if (Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_50) == TRUE)
            {
                l_ucTriggerEn = DISABLED;
                Drv_IOSoftLevel_Set(INT, HIGH);
                ;
                printLT(PRINT_PRIO_HIG, "\nGPIO Trigger High");
            }
        }
    }
#endif

    /**********************LT6911GXD INT(GPIO25_PWM3) IO************************/
#if CHIP_SEL == LT6911GXD_DP
    if (l_ucTriggerEn)
    {
        if (Drv_GPIO25_PWM3_level_Get() == HIGH)
        {
            Drv_IOSoftLevel_Set(GPIO25_PWM3, LOW);
            Ocm_Timer_UpdLocalTime(&ulCurrentTime);
            printLT(PRINT_PRIO_HIG, "\nGPIO Trigger Low");
        }
    }

    if (l_ucTriggerEn)
    {
        if (Drv_GPIO25_PWM3_level_Get() == LOW)
        {
            if (Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_50) == TRUE)
            {
                l_ucTriggerEn = DISABLED;
                Drv_IOSoftLevel_Set(GPIO25_PWM3, HIGH);
                ;
                printLT(PRINT_PRIO_HIG, "\nGPIO Trigger High");
            }
        }
    }
#endif
}

void LT7911GXE_CCGpioInit(void)
{
#if TYPECRX_EN == ENABLED

#if CUSTOM_EDID_SWITCH == ENABLED
    UCCStatus.uclaneCount = g_stDpRx.ucRxMaxLaneCount;
#else
    UCCStatus.uclaneCount = DPRX_LANE_COUNT;
    g_stDpRx.ucRxMaxLaneCount = UCCStatus.uclaneCount;
#endif
    UCCStatus.b1UCcInput_type = FEMALE;
    printLT(PRINT_PRIO_HIG, "\nFEMALE = 0x%02bx", UCCStatus.b1UCcInput_type);
    printLT(PRINT_PRIO_HIG, "\nL_C = 0x%02bx", UCCStatus.uclaneCount);

    /**************LT7911UXE EVB PD Control IO******************/
#if CHIP_SEL == LT7911UXE_DP
    Drv_Gpio_ModeSet(GPIO4_SPDIFA, OUT_PP_1x | PD_100K, VOL_3_3);
    DISCSOURCE_GPIO_CTRL(LOW);

    Drv_Gpio_ModeSet(GPIO16_MCLKA, OUT_PP_1x | PD_100K, VOL_3_3);
    DISCADAPTER_GPIO_CTRL(LOW);

    Drv_Gpio_ModeSet(GPIO24_PWM2, OUT_PP_1x | PD_100K, VOL_3_3);
    SOURCE_GPIO_CTRL(LOW);

    Drv_Gpio_ModeSet(GPIO25_PWM3, OUT_PP_1x | PD_100K, VOL_3_3);
    ADAPTER_GPIO_CTRL(LOW);

    Drv_Gpio_ModeSet(GPIO17_SCLKA, OUT_PP_1x | PD_100K, VOL_3_3);
    Drv_Gpio_ModeSet(GPIO18_WSA, OUT_PP_1x | PD_100K, VOL_3_3);
    Mod_CC1Vconn_Off();
#endif

    /**************LT6911GXD EVB PD Control IO******************/
#if CHIP_SEL == LT6911GXD_DP
    Drv_Gpio_ModeSet(GPIO19_SD0A_VSYNC, OUT_PP_1x | PD_100K, VOL_3_3);
    DISCSOURCE_GPIO_CTRL(LOW);

    Drv_Gpio_ModeSet(GPIO28_SD1B, OUT_PP_1x | PD_100K, VOL_3_3);
    DISCADAPTER_GPIO_CTRL(LOW);

    Drv_Gpio_ModeSet(GPIO26_SD3B, OUT_PP_1x | PD_100K, VOL_3_3);
    SOURCE_GPIO_CTRL(LOW);

    Drv_Gpio_ModeSet(GPIO27_SD2B, OUT_PP_1x | PD_100K, VOL_3_3);
    ADAPTER_GPIO_CTRL(LOW);

    Drv_Gpio_ModeSet(GPIO0_EARCN, OUT_PP_1x | PD_100K, VOL_3_3);
    Drv_Gpio_ModeSet(GPIO1_EARCP, OUT_PP_1x | PD_100K, VOL_3_3);
    Mod_CC1Vconn_Off();
#endif

#endif
}

void LT7911GXE_DpRxDpOrTypecDet(void)
{
#if TYPECRX_EN == ENABLED
    g_stDpRx.b1Input_Type_Sel = TYPEC_INTF;
#else
    g_stDpRx.b1Input_Type_Sel = DP_INTF;
#endif
}

void LT7911GXE_DpRxAudioInfoCvt(void)
{
    AudioChlInfo_S stInfo;
    Drv_DpRx_AudioInfoGet(&stInfo);

#if TX_PORT_SIGN == MIPI_PORT

#endif
#if TX_PORT_SIGN == LVDS_PORT

#endif
}

void LT7911GXE_DpRxColorInfoCvt(void)
{
    ColorInfo_S stInfo;
    LtTiming_S stRxTimingInfo;

    Drv_DpRx_VidColorInfoGet(&stInfo);
    printLT(PRINT_PRIO_HIG, "\nDp Rx vid info:");
    printLT(PRINT_PRIO_HIG, "\nColorSpace[%bd]", stInfo.ucPixelEncoding);
    printLT(PRINT_PRIO_HIG, "\nColorDepth[%bd]", stInfo.ucBitDepth);

#if DPRX_DSC_DEC_SUPPORT == ENABLED
    if (Drv_DpRxDscDec_SwitchGet() == ENABLED)
    {
        Drv_DpRxDscDec_ColorInfoGet(&stInfo);
    }
#endif
    Drv_DpRx_RxTimingGet(&stRxTimingInfo); //

#if TX_PORT_SIGN == MIPI_PORT

#endif
#if TX_PORT_SIGN == LVDS_PORT

#endif
}

void LT7911GXE_DpRxCscOrEncSel(void)
{
    g_stDpRx.b1CscRxEnable = DISABLED;
    printLT(PRINT_PRIO_HIG, "\nRx_Peak_clk =  %ld", g_stDpRx.ulRxPeakClk);

#if CSC_SUPPORT == ENABLED
#if TX_PORT_SIGN == MIPI_PORT
    g_stMipiTx.ucTxFormat = MIPITX_VIDEO_FORMAT;
    switch (g_stMipiTx.ucTxFormat)
    {
    case DSI_RGB_565:
    case DSI_RGB_666:
    case DSI_RGB_888:
    case DSI_RGB_30:
    case CSI_RGB_565:
    case CSI_RGB_666:
    case CSI_RGB_888:
        g_stDpRx.b1CscRxOutFormat = RGB_0;
        printLT(PRINT_PRIO_HIG, "\nCscRx out RGB_0");
        break;

    case DSI_YUV422_16Bit:
    case DSI_YUV422_20Bit:
    case DSI_YUV422_24Bit:
    case CSI_YUV422_8Bit:
    case CSI_YUV422_10Bit:
        g_stDpRx.b1CscRxOutFormat = YCbCr422_1;
        printLT(PRINT_PRIO_HIG, "\nCscRx out YCbCr422_1");
        break;

    case DSI_YUV420_12Bit:
    case CSI_YUV420_8Bit:
        g_stDpRx.b1CscRxOutFormat = YCbCr420_3;
        printLT(PRINT_PRIO_HIG, "\nCscRx out YCbCr420_3");
        break;

    default:
        break;
    }
#else
    g_stLvdsTx.ucLvdsTxDataMap = LVDS_DATAMAP;
    switch (g_stLvdsTx.ucLvdsTxDataMap)
    {
    case VESA_RGB_8Bit:
    case JEIDA_RGB_8Bit:
        g_stDpRx.b1CscRxOutFormat = RGB_0;
        printLT(PRINT_PRIO_HIG, "\nCscRx out RGB_0");
        break;
    case SONY_YUV422_8Bit:
        g_stDpRx.b1CscRxOutFormat = YCbCr422_1;
        printLT(PRINT_PRIO_HIG, "\nCscRx out YCbCr422_1");
        break;
    default:
        break;
    }
#endif
    g_stDpRx.b1CscRxEnable = ENABLED;
    printLT(PRINT_PRIO_HIG, "\nCsc enable");
#endif
}

#if CSC_SUPPORT == ENABLED
void LT7911GXE_DpRxCscCvt(void)
{
    if (g_stDpRx.b1CscRxEnable == ENABLED)
    {
        if ((g_stDpRx.b1CscRxOutFormat == RGB_0) || (g_stDpRx.b1CscRxOutFormat == RGB_WIDE_4))
        {
            g_stDpRx.b1CscRxOutRange = FULL_RANGE;
        }
        else
        {
            g_stDpRx.b1CscRxOutRange = LIMIT_RANGE;
        }
        Drv_CscRx_RxtoTx(&g_stDpRx);
    }
}
#endif

#if TX_PORT_SIGN == MIPI_PORT
void App_Brightness_Init(void)
{
    l_ucBrightness = MIPITX_HSCMD_REG;
    l_ucPreBrightness = l_ucBrightness;
}

void App_Brightness_Ctrl(void)
{
#if 0
    code u8 ucaBrightness[7][3] = 
    {
        {0x51,0x00,0x00},/*0nit*/
        {0x51,0x00,0x01},/*4nit*/
        {0x51,0x00,0xD3},/*10nit*/
        {0x51,0x01,0x72},/*25nit*/
        {0x51,0x03,0x30},/*90nit*/
        {0x51,0x07,0xFF},/*400nit*/
        {0x51,0x0F,0xFF},/*600nit*/
    };        
    /*
    ucBrightness:
    7: 600nit
    6: 400nit
    5: 90nit
    4: 25nit
    3: 10nit
    2: 4nit
    1: 0nit
    */
    static u8 ucBrightness = 6;/*400nit default*/
    
    if (g_stMipiTx.ucTxState == STATE_MIPITX_PLAY_BACK_7)
    {
        if (Drv_GetIO_State(BRIGHTNESS_UP_GPIO) == LOW)/*Detect Brightness+ Button pressed*/
        //if (BKE0_C0_REG != 0)/*For I2C verify*/
        {
            ucBrightness ++ ;
            if (ucBrightness > 7)
            {
                ucBrightness = 7;
                return;
            }
            while(Drv_GetIO_State(BRIGHTNESS_UP_GPIO) == LOW);/*Wait Brightness+ Button Released*/
            //while(BKE0_C0_REG != 0);/*For I2C verify*/
            LTLog(LOG_INFO, "Bright+");
        }
        
        if (Drv_GetIO_State(BRIGHTNESS_DOWN_GPIO) == LOW)/*Detect Brightness- Button pressed*/
        //if (BKE0_C1_REG != 0)/*For I2C verify*/
        {
            ucBrightness -- ;
            if (ucBrightness < 1)
            {
                ucBrightness = 1;
                return;
            }
            while(Drv_GetIO_State(BRIGHTNESS_DOWN_GPIO) == LOW);/*Wait Brightness- Button Released*/
            //while(BKE0_C1_REG != 0);/*For I2C verify*/
            LTLog(LOG_INFO, "Bright-");
        }
        Drv_MipiTx_HsCmd_En(ENABLED);
        Drv_MipiTx_DcsPktWrite(0x39,0x03,&ucaBrightness[ucBrightness - 1][0]);
        Ocm_Delay1ms(50);/*Delay more than 1 frame*/
        Drv_MipiTx_HsCmd_En(DISABLED);
    }
    else
    {
        return;
    }
#else

    u16 ucBrightness = 0;
    u8 ucaBrightness[3] = {0};
    if (g_stMipiTx.ucTxState == STATE_MIPITX_PLAY_BACK_7)
    {
        l_ucBrightness = MIPITX_HSCMD_REG;

        if (l_ucBrightness != l_ucPreBrightness) /*Detect Brightness Change*/
        {

            l_ucPreBrightness = l_ucBrightness;

            ucBrightness = (l_ucBrightness + 1) * 16;
            ucBrightness = ucBrightness - 1;

            ucaBrightness[0] = 0x51;
            ucaBrightness[1] = ucBrightness >> 8;
            ucaBrightness[2] = ucBrightness;
            LTLog(LOG_DEBUG, "ucaBrightness[1]:0x%02bx, ucaBrightness[2]:0x%02bx", ucaBrightness[1], ucaBrightness[2]);

            LET_BITS(BKF9_B8_REG, 1, 0, 0x3); // U3
            Drv_MipiTx_HsCmd_En(ENABLED);

            Drv_MipiTx_DcsPktWrite(0x39, 0x03, &ucaBrightness[0]);

            Ocm_Delay1ms(50); /*Delay more than 1 frame*/
            Drv_MipiTx_HsCmd_En(DISABLED);
            CLEAR_BITS(BKF9_B8_REG, 1, 0);
        }
    }
    else
    {
        return;
    }
#endif
}
#endif

void LT7911GXE_DpRx_Audio_Handle(void)
{
    if (g_stDpRx.ucRxState > STATE_DPRX_AUDIO_INFO_CHK_15)
    {

        if (Drv_DPRX_AudFs_Update() == TRUE)
        {
            if (g_stDpRx.ucFsValue != AUD_FS_ZERO)
            {
                Drv_Gpio_ModeSet(GPIO31_MCLKB, OUT_PP_2x | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO32_SCLKB, OUT_PP_2x | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO30_WSB, OUT_PP_2x | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO29_SD0B, OUT_PP_2x | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO28_SD1B, OUT_PP_2x | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO27_SD2B, OUT_PP_2x | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO26_SD3B, OUT_PP_2x | NO_PU_PD, VOL_3_3);
            }
            else
            {
                Drv_Gpio_ModeSet(GPIO31_MCLKB, OUT_DISABLE | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO32_SCLKB, OUT_DISABLE | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO30_WSB, OUT_DISABLE | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO29_SD0B, OUT_DISABLE | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO28_SD1B, OUT_DISABLE | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO27_SD2B, OUT_DISABLE | NO_PU_PD, VOL_3_3);
                Drv_Gpio_ModeSet(GPIO26_SD3B, OUT_DISABLE | NO_PU_PD, VOL_3_3);

                Drv_Aud_Info_Update(FALSE);
                l_ucTriggerEn = ENABLED;
            }
        }
    }
}

void LT7911GXE_DpRxMsgNotify(u8 ucEvent)
{
    Mod_LMTx_EventMonitor(ucEvent);
    switch (ucEvent)
    {
    case DPRX_SOURECE_PLUG_EVENT:
        break;

    case DPRX_SOURECE_UNPLUG_EVENT:
        g_stDpRx.ucFsValue = 0;
        //							#if TX_PORT_SIGN == MIPI_PORT
        //							LTLog(LOG_INFO, "DPRX_SOURECE_UNPLUG_EVENT");
        //							Drv_MipiTx_Info_Update(DPRX_SOURECE_UNPLUG_EVENT);
        //							#endif
        //							Drv_GPIO19Vsync_Set(DISABLED);
        //							l_ucTriggerEn = ENABLED;
        Drv_Sys_DHTxPowerDomain(FALSE);
        break;

    case DPRX_VIDEO_ON_EVENT:
        Mod_DpRx_PeakClkCal();
        LT7911GXE_DpRxCscOrEncSel();
        LT7911GXE_DpRxColorInfoCvt();
#if CSC_SUPPORT == ENABLED
        LT7911GXE_DpRxCscCvt();
#endif
        break;

    case DPRX_VIDEO_OFF_EVENT:
        Drv_DpRx_SyncPolSet(DISABLED);
        Drv_Sys_DecPowerDomain(TRUE);
        Drv_Sys_EncPowerDomain(TRUE);
#if CSC_SUPPORT == ENABLED
        Drv_CscRx_Init();
#endif
        TX_Event_Set(TX_VIDEO_OFF_EVENT_4);

        Drv_Sys_DHTxPowerDomain(FALSE);
        break;

    case DPRX_HDCP_VER_CHG_EVENT:
        break;

    case DPRX_COLORINFO_CHG_EVENT:
        break;
    case DPRX_TIMING_CHG_EVENT:
        break;
    case DPRX_PACKET_CHG_EVENT:
        break;
    case DPRX_VRR_NOTIFY_EVENT:
        break;
    case DPRX_STATIC_HDR_NOTIFY_EVENT:
#if TX_PORT_SIGN == MIPI_PORT
        if ((g_stMipiTx.b1SrcStaticHdrChg == FALSE) && (g_stMipiTx.ucTxState >= STATE_MIPITX_PLAY_BACK_7) && (l_ucTriggerEn == DISABLED))
        {
            g_stMipiTx.b1SrcStaticHdrEn = g_stDpRx.b1HdrEn;
            g_stMipiTx.b1SrcStaticHdrChg = TRUE;

            LTLog(LOG_INFO, "DPRX_STATIC_HDR_NOTIFY_EVENT");
            Drv_MipiTx_Info_Update(DPRX_STATIC_HDR_NOTIFY_EVENT);

            l_ucTriggerEn = ENABLED;
        }
#endif

#if TX_PORT_SIGN == LVDS_PORT

#endif
        break;
    case DPRX_DYNAMIC_HDR_NOTIFY_EVENT:
        break;
    case DPRX_AUDIO_CHG_EVENT:
        TX_Event_Set(TX_AUDIO_CHANGE_EVENT_5);

        break;

    case DPRX_FEC_NOTIFY_EVENT:
        break;
    default:
        break;
    }
}

void LT7911GXE_TxSystem_Run(void)
{
    u8 TxEvent;

    GPIO_Trigger_Hdl();

    if ((TX_Event_Trig() == TRUE) && (l_ucTriggerEn == DISABLED))
    {
        TxEvent = TX_Event_Get();
        TX_Event_Clr();
        switch (TxEvent)
        {
        case TX_SINK_PLUG_EVENT_1:
            break;
        case TX_SINK_UNPLUG_EVENT_2:
            break;
        case TX_VIDEO_ON_EVENT_3:

#if TX_PORT_SIGN == MIPI_PORT
            LTLog(LOG_INFO, "TX_VIDEO_ON_EVENT_3");
            Drv_MipiTx_Info_Update(TX_VIDEO_ON_EVENT_3);
#endif
            Drv_GPIO19Vsync_Set(ENABLED);
            l_ucTriggerEn = ENABLED;
            Drv_Sys_DHTxPowerDomain(TRUE); // DHTxPoweroff
            break;
        case TX_VIDEO_OFF_EVENT_4:
#if TX_PORT_SIGN == MIPI_PORT
            LTLog(LOG_INFO, "DPRX_VIDEO_OFF_EVENT");
            Drv_MipiTx_Info_Update(DPRX_VIDEO_OFF_EVENT);
#endif
            Drv_GPIO19Vsync_Set(DISABLED);
            l_ucTriggerEn = ENABLED;

            break;

        case TX_AUDIO_CHANGE_EVENT_5:
            LT7911GXE_DpRxAudioInfoCvt();
            Drv_Aud_Info_Update(TRUE);
            l_ucTriggerEn = ENABLED;
            break;
        default:
            break;
        }
    }
}

void LT7911GXE_Main_Scan(void)
{
#if TYPECRX_EN == ENABLED
    Mod_CC1Rx_Loop();
#endif
    // rx handler
    Mod_DpRx_Handler();

// tx handler
#if TX_PORT_SIGN == LVDS_PORT
    Mod_LvdsTx_Handler();
#endif
#if TX_PORT_SIGN == MIPI_PORT
    Mod_MipiTx_Handler();
#endif

#if PWM_OUT == ENABLED
    {
        if (PWM_DUTY_REG != PWM_DUTY)
        {
            PWM_Init(PWM_GPIO, PWM_FREQ, PWM_DUTY_REG);
        }
        else
        {
            PWM_Init(PWM_GPIO, PWM_FREQ, PWM_DUTY);
        }
    }
#endif

    LT7911GXE_TxSystem_Run();

#if CUSTOM_EDID_SWITCH == ENABLED
    Custom_Handler();
#endif

    LT7911GXE_DpRx_Audio_Handle();

#if TX_PORT_SIGN == MIPI_PORT
    App_Brightness_Ctrl();
#endif
}

#endif
