/******************************************************************************
  * @project: LT2101
  * @file: ChipDpRx.c
  * @author: qihan
  * @company: LONTIUM
  * @date: 2021.10.12
/******************************************************************************/
#include "include.h"

#if RX_PORT_SIGN == DP_PORT

#define DPRX_MSAMODE    BKF3_05_REG
#define DPRX_HTOTAL_H8    BKF3_06_REG
#define DPRX_HTOTAL_L8    BKF3_07_REG

#define PPS_VERSION          BKEE_00_REG
#define PPS_COLORDEPTH       BKEE_03_REG
#define PPS_INFOLOAD         BKEE_AD_REG
StructDpRx g_stDpRx;

void Mod_DpRx_PowerOnInit(void)
{
    memset(&g_stDpRx,0,sizeof(StructDpRx));
    g_stDpRx.ucRxState = STATE_DPRX_POWER_ON_1;
}

void Mod_DpRx_GpioInit(void)
{
    #if CHIP_SEL == LT8711GXE
    LT8711GXE_CCGpioInit();
    #endif
    #if ((CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))
    LT7911GXE_CCGpioInit();
    #endif
}

void Mod_DpRx_DpOrTypecDet(void)
{
    #if CHIP_SEL == LT8711GXE
    LT8711GXE_DpRxDpOrTypecDet();
    #endif
    
    #if ((CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))
    LT7911GXE_DpRxDpOrTypecDet();
    #endif
}

void Mod_DpRx_VarInit(void)
{
    #if CHIP_SEL == LT8711GXE
    LT8711GXE_DpRxVarInit();
    #endif
    #if ((CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))
    LT7911GXE_DpRxVarInit();
    #endif
}

void Mod_DpRx_MsgNotify(u8 ucEvent)
{
    #if CHIP_SEL == LT8711GXE
    LT8711GXE_DpRxMsgNotify(ucEvent);
    #endif
    #if ((CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))
    LT7911GXE_DpRxMsgNotify(ucEvent);
    #endif
}

#if DPRX_LINK_CTS == ENABLED
u8 Mod_DpRx_UpStreamVidReadyGet()
{
    return g_stHdmiTx.b1UpstreamVideoReady;
}
#endif

u8 Mod_DpRx_SourceDetection(void)
{
    if(g_stDpRx.b1Input_Type_Sel == DP_INTF)
    {
        return Drv_DpRx_AuxDcDet();
    }
    #if TYPECRX_EN == ENABLED
    else if(g_stDpRx.b1Input_Type_Sel == TYPEC_INTF)
    {
        return Mod_CC1ComDone_Get();
    }
    #endif

    return FALSE;
}

void Mod_DpRx_SourceChannelSet(void) 
{
    if(g_stDpRx.b1Input_Type_Sel == DP_INTF)
    {
        Drv_DpRx_DpRxChlSwap();
        Drv_DpRx_HpdSet(HPD_HIGH, IRQ_LOW);
    }
    #if TYPECRX_EN == ENABLED
    else
    {
        if(UCCStatus.b1UCcInput_type == MALE)
        {
            Drv_DpRx_TypecRxChlSwap(TYPEC_MALE,UCCStatus);
        }
        else
        {
             if(UCCStatus.b1IsFlip == FALSE)
             {
                Drv_DpRx_TypecRxChlSwap(TYPEC_FEMALE_NOFLIP,UCCStatus);
             }
             else
             {
                Drv_DpRx_TypecRxChlSwap(TYPEC_FEMALE_FLIP,UCCStatus);
             }
        }
        UCCStatus.b2AttentionType = ATTENTION_HIGH;
    }
    #endif
}

void Mod_DpRx_PeakClkCal(void)
{
    u8 ucBitDepth; 
    u8 b1IsDscSimple422 = FALSE;
    Drv_System_FmSet(TOP_FM,TOPFM_PCRPLL_PCR_CLK);
    Ocm_Delay1ms(3);//为什么要10ms？
    //get Pixel clock ,not Half one
    g_stDpRx.ulRxPixelClk = Drv_System_FmGet(TOP_FM,HALF_PIX_CLK)<<1;//Hlaf Pixel clock

    ucBitDepth = g_stDpRx.ucBitDepth;
    #if DPRX_DSC_DEC_SUPPORT == ENABLED
    if (Drv_DpRxDscDec_SwitchGet() == ENABLED)
    {
        switch(Drv_DpRxDscDec_ColorDepthGet())
        {
            case BPC10:
            case BPC12:
                ucBitDepth = DPRX_10BIT_2;
                break;        
            default:
                ucBitDepth = DPRX_8BIT_1;
                break;
        } 
        if(Drv_DpRxDscDec_ColorSpaceGet() == SIMPLE422_5)
        {
            b1IsDscSimple422 = TRUE;    
        }
    }
    #endif
    switch(ucBitDepth)
    {
        case DPRX_6BIT_0:
            ucBitDepth = 6;
            break;
        case DPRX_10BIT_2:
            ucBitDepth = 10;
            break;
        case DPRX_12BIT_3:
            ucBitDepth = 12;
            break;        
        default:
            ucBitDepth = 8;
            break;
    } 
    //not support 16bit
    //for HDMI output,get TMDS Clock
    g_stDpRx.ulRxPeakClk = (g_stDpRx.ulRxPixelClk*ucBitDepth)>>3;
    //
    if((g_stDpRx.ucPixelEncoding == YCbCr422_1)&&(b1IsDscSimple422 == FALSE))
    {
        g_stDpRx.ulRxPeakClk = (g_stDpRx.ulRxPeakClk<<1)/3;
    }
    else
    {
        ;
    }
}

#if DPRX_TIMING_HBE == ENABLED
u8 Chip_Timing_Check(LtTiming_S stRxTimingInfo)
{
    if((stRxTimingInfo.usHtol >= TIMING_HBE_HTOTAL_4k60Hz_MIN)&& (stRxTimingInfo.usHtol <= TIMING_HBE_HTOTAL_4k60Hz_MAX))
    {
        return HBE_4K60;
    }    
    else if((stRxTimingInfo.usHtol >= TIMING_HBE_HTOTAL_4k50Hz_MIN)&& (stRxTimingInfo.usHtol <= TIMING_HBE_HTOTAL_4k50Hz_MAX))
    {
        return HBE_4K50;
    }
    return HBE_NONE;
}
u8 Chip_DpRx_JudgeTimingHBE(void)
{
    LtTiming_S  stRxTimingInfo; 
    //get MSA info from SDP register.
    Drv_DpRx_RxTimingGet(&stRxTimingInfo);

    if ((Chip_Timing_Check(stRxTimingInfo) == HBE_4K60)
        && (stRxTimingInfo.usVtol == 2250)&& (stRxTimingInfo.usHact == 3840)&& (stRxTimingInfo.usVact == 2160))
    {
        g_stDpRx.b2IsTimingHBE = HBE_TYPE_UHD_60Hz;               
    }
    else if (((Chip_Timing_Check(stRxTimingInfo) == HBE_4K50)
        && (stRxTimingInfo.usVtol == 2250)&& ((stRxTimingInfo.usHact == 3840)||(stRxTimingInfo.usHact==4096))&&(stRxTimingInfo.usVact == 2160)))
    {
        if(stRxTimingInfo.usHact == 3840)
        {
            g_stDpRx.b2IsTimingHBE = HBE_TYPE_UHD_50Hz;
        }
        else if(stRxTimingInfo.usHact == 4096)
        {
            g_stDpRx.b2IsTimingHBE = HBE_TYPE_4K2K_50Hz;
        }
    }
    else 
    {      
        g_stDpRx.b2IsTimingHBE = HBE_NONE;
    }
    return g_stDpRx.b2IsTimingHBE;
}

void Chip_DpRx_TimingHBE(void)
{
    u8 usTiming594M_H_Type1[8] = {0x11,0x30,0x01,0x7c,0x00,0x58,0x0F,0x00};
    u8 usTiming594M_H_Type2[8] = {0x14,0xA0,0x01,0x7C,0x00,0x58,0x0F,0x00};
    u8 usTiming594M_H_Type3[8] = {0x14,0xA0,0x00,0xD4,0x00,0x58,0x10,0x00};
    u8 usTiming594M_V[8] = {0x08,0xCA,0x00,0x52,0x00,0x0A,0x08,0x70};
    u8 ucTmpF30A;
    
    ucTmpF30A = BKF3_0A_REG & 0x80;
    if(g_stDpRx.b2IsTimingHBE==HBE_TYPE_UHD_60Hz)
    {
        memcpy(&BKF3_06_REG,&usTiming594M_H_Type1[0],8);
    }
    else if(g_stDpRx.b2IsTimingHBE==HBE_TYPE_UHD_50Hz)
    {
        memcpy(&BKF3_06_REG,&usTiming594M_H_Type2[0],8);
    }
    else if(g_stDpRx.b2IsTimingHBE==HBE_TYPE_4K2K_50Hz)
    {
        memcpy(&BKF3_06_REG,&usTiming594M_H_Type3[0],8);
    }
    BKF3_0A_REG &= 0x7f; //clear bit0-7,default not 0
    BKF3_0A_REG |= ucTmpF30A;

    memcpy(&BKF3_0E_REG, &usTiming594M_V[0], 8);    
    
    BKF3_05_REG |= BIT6_1; //soft msa enable
    BKF3_00_REG = 0x80;//如果8K HBE需要改成D0
}
#endif

bool Mod_DpRx_PcrColorSpaceUpdate(void)
{
//    u8 ucPixelDepth;
    ColorInfo_S stColorInfo;
    Drv_DpRx_VidColorInfoGet(&stColorInfo);
    //no need updata.
    if ((g_stDpRx.ucPixelEncoding     == stColorInfo.ucPixelEncoding) &&
//        (g_stDpRx.ucColorimetryFormat == stColorInfo.ucColorimetryFormat) &&
        (g_stDpRx.ucBitDepth          == stColorInfo.ucBitDepth) &&
        (g_stDpRx.b1VscPkg            == stColorInfo.b1VscPkg))
    {
        return FALSE;
    }

    //colorspace info need to be updata.
    g_stDpRx.b1VscPkg            = stColorInfo.b1VscPkg;
    g_stDpRx.ucPixelEncoding     = stColorInfo.ucPixelEncoding;//00 rgb 01 ycc422 10 ycc444 11 ycc420
    g_stDpRx.ucColorimetryFormat = stColorInfo.ucColorimetryFormat;
    g_stDpRx.ucBitDepth          = stColorInfo.ucBitDepth;     //1-8bit, 2-10bit, 3-12bit

    if(g_stDpRx.b1VscPkg == TRUE)
    {
        Drv_DpRx_420DetectMode(HARDWARE);
    }
    else
    {
        Drv_DpRx_420DetectMode(SOFTMODE);
    }
    #if DPRX_MST_MODE_EN == ENABLED
    if(g_stAuxStatus.b1MstFlag == TRUE)
    {
        BKF3_16_REG = 0x80|(BKF3_16_REG&0x1f);//[7:5]the value of lane_cnt in soft mode: 100'b-4lane
        BKF3_12_REG |= BIT7_1;//[7]rg_lane_cnt_soft_mode: 1-soft en, 0-soft dis
    }
    else
    {
        BKF3_16_REG &= 0x1f;//[7:5]the value of lane_cnt in soft mode: 100'b-4lane
        BKF3_12_REG &= BIT7_0;//[7]rg_lane_cnt_soft_mode: 1-soft en, 0-soft dis

    }
    #endif
    return TRUE;
}

void Mod_DpRx_ColorimetryUpdata(void)
{
    ColorInfo_S stColorInfo;
    Drv_DpRx_VidColorInfoGet(&stColorInfo);
    //no need updata.
    if(g_stDpRx.ucColorimetryFormat == stColorInfo.ucColorimetryFormat)
    {
        return;
    }  
    //colorspace info need to be updata.
    g_stDpRx.ucColorimetryFormat = stColorInfo.ucColorimetryFormat;
    printLT(PRINT_PRIO_HIG, "\nColorimetry change = 0x%02bx",g_stDpRx.ucColorimetryFormat);
    Mod_DpRx_MsgNotify(DPRX_COLORRIMETRY_CHG_EVENT);
}

#if (DPRX_TIMING_HBE == ENABLED)
//========================================================================
// Func Name   : Mod_DpRx_JudgeTimingHBE
// Description : judge is not Horizontal Blanking Expansion
//                  v direction is same as 4k60 594M,vtotal is 2250,vactive is 2160
//                  H direction is not same, htotal is 3930~3940, hblank is 90~100,hactive is 3840
// Input       : void  
// Output      : None
// Return      : bool
//========================================================================
u8 Mod_DpRx_JudgeTimingHBE(void)
{
    return g_stDpRx.b2IsTimingHBE;
}
#endif

bool Mod_DpRx_PcrMsaUpdate(void)
{
    LtTiming_S stRxTimingInfo;
    if(Drv_System_IntFlagGet(IRQ_DPRX_MSA_INT) == FALSE)
    {
        return UNKNOWN;
    }
    Drv_DpRx_RxTimingGet(&stRxTimingInfo);
    if ((g_stDpRx.usHotal == stRxTimingInfo.usHtol) &&(g_stDpRx.usHactive == stRxTimingInfo.usHact))
    {
        return FALSE; //msa not chg
    }
    g_stDpRx.usHotal   = stRxTimingInfo.usHtol;
    g_stDpRx.usHactive = stRxTimingInfo.usHact;
    return TRUE;
}

void Mod_DpRx_InfoDisplay(void)
{
    LtTiming_S stTiming;
    Drv_DpRx_RxTimingGet(&stTiming);
    
    printLT(PRINT_PRIO_HIG, "\nDpRxINFO:");
    printLT(PRINT_PRIO_TEST, "\nHbp    : %-8d  Vbp    : %-8d", stTiming.usHbp,stTiming.usVbp);
    printLT(PRINT_PRIO_TEST, "\nHfp    : %-8d  Vfp    : %-8d", stTiming.usHfp,stTiming.usVfp);
    printLT(PRINT_PRIO_TEST, "\nHsync  : %-8d  Vsync  : %-8d", stTiming.usHsync,stTiming.usVsync);
    printLT(PRINT_PRIO_TEST, "\nHact   : %-8d  Vact   : %-8d", stTiming.usHact,stTiming.usVact);
    printLT(PRINT_PRIO_TEST, "\nHtol   : %-8d  Vtol   : %-8d", stTiming.usHtol,stTiming.usVtol);
    printLT(PRINT_PRIO_TEST, "\nDepth  : %-8bd  Space  : %-8bd", (g_stDpRx.ucBitDepth << 1) + 6,g_stDpRx.ucPixelEncoding);
    printLT(PRINT_PRIO_TEST, "\nPixClk : %-8ld  PeakClk: %-8ld", g_stDpRx.ulRxPixelClk, g_stDpRx.ulRxPeakClk);
}

void Mod_DpRx_FrameRate_Get(LtTiming_S *pstRxTimingInfo)
{
	u32 ulPixelClock;
	u16 usHcTotal = 0x00;
	//soft MSA，包括DSC BYpass，HBE模式等
	if(DPRX_MSAMODE & BIT6_1)//soft MSA
	{
		usHcTotal = ((u16)DPRX_HTOTAL_H8<<8) + DPRX_HTOTAL_L8;
	}
	else
	{
		usHcTotal = pstRxTimingInfo->usHtol;
	}
	ulPixelClock = (u32)usHcTotal * pstRxTimingInfo->usVtol;
//	printLT(PRINT_PRIO_TEST, "\nulRxPixelClk = 0x%08lx", g_stDpRx.ulRxPixelClk);
//	printLT(PRINT_PRIO_TEST, "\nulPixelClock = 0x%08lx", ulPixelClock);
//if 420 mode and frame rate is EVEN, it is better Multiplication before division
	if(g_stDpRx.ucPixelEncoding == YCbCr420_3)//
	{
        //pstRxTimingInfo->usFramerate = (((g_stDpRx.ulRxPixelClk * 2000)+(ulPixelClock/2))/ulPixelClock);//四舍五入
		pstRxTimingInfo->usFramerate = floor((((float)g_stDpRx.ulRxPixelClk * 2000)/ulPixelClock)+0.5);//四舍五入
	}
	else
	{
        //pstRxTimingInfo->usFramerate = (((g_stDpRx.ulRxPixelClk * 1000)+ulPixelClock/2)/ulPixelClock);//四舍五入
		pstRxTimingInfo->usFramerate = floor((((float)g_stDpRx.ulRxPixelClk * 1000)/ulPixelClock)+0.5);//四舍五入
	}
	printLT(PRINT_PRIO_TEST, "\nRefreshRate = %d",pstRxTimingInfo->usFramerate);
}

void Mod_DpRx_HpdLowAction(void)
{
    //pull hpd to low.
    if(g_stDpRx.b1Input_Type_Sel == DP_INTF)
    {
        Drv_DpRx_HpdSet(HPD_LOW, IRQ_LOW);
    }
    #if TYPECRX_EN == ENABLED
    else
    {
        UCCStatus.b2AttentionType = ATTENTION_LOW;
    }
    #endif
    
    #if DPRX_HDCP_DEC_MODE != NO_HDCP
    Drv_System_IntSet(IRQ_RXHDCP1X_INT,OFF);//
    Drv_System_IntSet(IRQ_RXHDCP2X_INT,OFF);//
    Drv_HdcpRx_StateClear();
    #endif
    
    Drv_DpRx_PhyShut();
    Drv_DpRx_Reset(DP_FEC_DEC_RST);
    Drv_DpRx_Reset(DP_MLC_DAT_RST);  //solve mst dpcd200c not clr issue 
    Drv_DpRx_Reset(DP_MLC_DPCD_RST); //solve 3080 mst dpcd not clr issue
    //DP_MLC_DAT_RST 后需要至少加2ms复位再关掉RXPHY
//    Ocm_Delay1ms(10);
    g_stDpRx.ucHdcpVersion = NO_HDCP;
    Mod_DpRx_MsgNotify(DPRX_HDCP_VER_CHG_EVENT);
    Mod_DpRx_MsgNotify(DPRX_VIDEO_OFF_EVENT);
}

void Mod_DpRx_HpdIrq(void)
{
    if(g_stDpRx.b1Input_Type_Sel == DP_INTF)
    {
        Drv_DpRx_HpdSet(HPD_HIGH, IRQ_HIGH);
    }
    #if TYPECRX_EN == ENABLED
    else
    {
        UCCStatus.b2AttentionType = ATTENTION_IRQ;
    }
    #endif
}
#if DPRX_MST_MODE_EN == ENABLED
void Mod_DpRx_MstHandler(void)
{
    if(g_stDpRx.ucRxState > STATE_DPRX_SET_HPD_5)
    {
        Mod_Mst_MsgHandle();
    }
}
#endif
u8 Mod_DpRx_ColorSpace(void)
{
    return g_stDpRx.ucPixelEncoding;
}

u8 Mod_DpRx_ColorDepth(void)
{
    return g_stDpRx.ucBitDepth;
}

void Mod_DpRx_SetState(u8 ucState)
{
    u8 ucLastState;
    if(ucState != g_stDpRx.ucRxState)
    {    
        ucLastState = g_stDpRx.ucRxState;
        g_stDpRx.ucRxState = ucState;
        g_stDpRx.b1RxStateChanged = TRUE;
        printLT(PRINT_PRIO_TEST, "\nRxState = %bd",ucState);
        
        // other state-->STATE_DPRX_PLAY_BACK_16,need notify video on
        if(g_stDpRx.ucRxState == STATE_DPRX_PLAY_BACK_16)
        {
            Mod_DpRx_MsgNotify(DPRX_VIDEO_ON_EVENT);
        }
        
        //STATE_DPRX_PLAY_BACK_16-->other state,need notify video off
        if(ucLastState == STATE_DPRX_PLAY_BACK_16)
        {
            Mod_DpRx_MsgNotify(DPRX_VIDEO_OFF_EVENT);
        }
    }
}

//========================================================================
// Func Name   : Mod_DpRx_SourceDetProc
// Description : The process of source detection.
// Input       : void  
// Output      : None
// Return      : void
//========================================================================
void Mod_DpRx_SourceDetProc(void)
{
    if(g_stDpRx.ucRxState < STATE_DPRX_WAIT_SOURCE_3)
    {
        return;
    }
    //the last source detect is high.
    if(g_stDpRx.b1SourceDet == HIGH)
    {
        //the current source detect is low.
        if(Mod_DpRx_SourceDetection() == FALSE)
        {
            printLT(PRINT_PRIO_HIG, "\nDpRx Unplug");
            Mod_DpRx_SetState(STATE_DPRX_WAIT_SOURCE_3); //Typec Rx CC is done or dp is ok cc is open 09           
            Mod_DpRx_HpdLowAction();
            g_stDpRx.b1SourceDet = LOW;
            Mod_DpRx_MsgNotify(DPRX_SOURECE_UNPLUG_EVENT);
        }

    }
    //the last source detect is low.
    else
    {
        //the current source detect is high.
        if(Mod_DpRx_SourceDetection() == TRUE)
        {
            printLT(PRINT_PRIO_HIG, "\nRx Plug");
            g_stDpRx.b1SourceDet = HIGH; 
            Mod_DpRx_MsgNotify(DPRX_SOURECE_PLUG_EVENT);
        }
    }
}

void Mod_DpRx_EccErrAbnormalHdl(u8 ucOpt)
{
    static u8 ucCount = 0;

    if (ucOpt == DISABLED)
    {
        ucCount = 0;
        return;
    }

    if(ucCount >= 0x05)//1s
    {
        ucCount++;
        if((Drv_DpRx_NoErrCheck(g_stAuxStatus.ucLink_Count) == TRUE)&&(g_stAuxStatus.FecFlag == TRUE))
        {
            printLT(PRINT_PRIO_HIG, "\nWait ECC");
            #if CHIP_VERSION_SEL == U1_VERSION
            Drv_DpRx_FecSoftModeSet(TRUE);//Softmode
            #else
            //maximum wait time equal ((512*256)/810M)*2 = 324us
            Drv_DpRx_FecAbnormalDet();
            #endif
        }
        else
        {
            Drv_DpcdError_Clear(0x0f);
        }
    }
    else
    {
        ucCount++;
        Drv_DpRx_Reset(DP_RX_SDP_RST);
        printLT(PRINT_PRIO_HIG, "\nEcc err");
    }
}
#if ((DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
u8 Mod_DpRx_DecByp_Sel(void)
{
    u32 ulFrequency = 0x00;
    u8 ucBitDepth = 0x00;
    u8 ucColorDepth = 0x00;
    u8 ucSliceNum = 0;
//    g_stDpRx.ucDscSel = SELNODSC;
    #if (DPRX_DSC_DEC_SUPPORT == ENABLED)
    Drv_DpRxDscDec_Set(DISABLED);
    #endif
    #if (DPRX_DSC_BYPASS_SUPPORT == ENABLED)
    Drv_DpRxDscBy_Set(DISABLED);
    #endif
    if(Drv_DpRx_PixelStableCheck() == TRUE)//Frequency Stable
    {
        //load pps to sram and get color depth
        Ocm_Delay1us(10);//must be wait load success
        PPS_INFOLOAD = 0xff;//important, ee00 ~ ee80 update, must be set
        Ocm_Delay1ms(1);
        if ((PPS_VERSION >= 0x11) && (PPS_VERSION <= 0x13))
        {
            printLT(PRINT_PRIO_HIG, "\nPPs LOAD SUCCEED");
        }
        else
        {
            return 0x00;//wait
        }
    //color space and depth get
        ucColorDepth = (PPS_COLORDEPTH >> 5);//8 bit = 0x04, so >> 4 and /2，is >> 5      
        switch(ucColorDepth)
        {
            case BPC10:
                ucBitDepth = 10;
                break;
            case BPC12:
                ucBitDepth = 12;
                break;        
            default:
                ucBitDepth = 8;
                break;
        }
        ulFrequency = Drv_DpRx_PixFreqGet();
        ulFrequency = (ulFrequency*ucBitDepth)/4;// 4 = 8/2
        ucSliceNum = Drv_DpRxDsc_SliceNum();
        if (ucSliceNum > 4)
        {
            printLT(PRINT_PRIO_HIG, "\nSlice >  4");
            #if (DPRX_DSC_BYPASS_SUPPORT == ENABLED)
            Drv_DpRxDscBy_Set(ENABLED);
            #endif
            return 0x01;//DSC Judge Done
        }
        
        if ((ulFrequency > Mod_HdmiTx_LinkBandWidthGet())&&(g_stHdmiEdidInfo.ucMaxFrlDscRate != FRL_NOT_SPT))
        {
            #if (DPRX_DSC_BYPASS_SUPPORT == ENABLED)
            Drv_DpRxDscBy_Set(ENABLED);
            #endif
        }
        else
        {
            #if (DPRX_DSC_DEC_SUPPORT == ENABLED)
            Drv_DpRxDscDec_Set(ENABLED);
            #endif
        }
        printLT(PRINT_PRIO_TEST, "\nPixelClock = 0x%08lx, 0x%08lx", ulFrequency,Mod_HdmiTx_LinkBandWidthGet());
        return 0x01;//DSC Judge Done
    }
    else
    {
        return 0x00;//wait
    }
}
#endif
void Mod_DpRx_StateJudge(void)
{
    u8 ucMinState = 0xff;
    #if DPRX_HDCP_DEC_MODE != NO_HDCP
    u8 ucHdpcVer;
    #endif
    #if ((DPRX_LINK_CTS == ENABLED) && (DPRX_DSC_DEC_SUPPORT == ENABLED))
    u8 ucHpdIrqCnt;
    #endif
    
    //source detect low, no need judge
    if(g_stDpRx.b1SourceDet == LOW)
    {
        return;
    }
    
    //monitor down stream is present or not.
    if(g_stDpRx.ucRxState > STATE_DPRX_DOWNSTREAM_READY_4) 
    {
        if(g_stDpRx.b1DownstreamDeviceReady == FALSE)
        {
            Mod_DpRx_HpdLowAction(); //pull low hpd.
            ucMinState = MIN(ucMinState,STATE_DPRX_DOWNSTREAM_READY_4);
        }
    }
    
    //monitor re-training event.
    if(g_stDpRx.ucRxState > STATE_DPRX_WAIT_LINK_TRAIN_6)
    {
        if(Mod_Aux_GetRetrainStatus() == TRUE)//re training
        {
            printLT(PRINT_PRIO_HIG, "\nRx re-training");
            Mod_DpRx_SetState(STATE_DPRX_WAIT_LINK_TRAIN_6);
        }
        #if (DPRX_HDCP_DEC_MODE != NO_HDCP)   
        if((Drv_Hdcp13_IntGet() == TRUE)||(Drv_Hdcp2X_IntGet() == TRUE))
        {
            printLT(PRINT_PRIO_HIG, "\nHDCP INT");
            Mod_DpRx_HpdIrq();
        }
        #endif
    }
    
    #if DPRX_MST_MODE_EN == ENABLED
    if(g_stDpRx.ucRxState > STATE_DPRX_WAIT_MST_DONE_7)
    {
        if(Mod_DpRxMst_PayloadUpdate() == TRUE)
        {
            printLT(PRINT_PRIO_HIG, "\nPayload update");
            ucMinState = MIN(ucMinState, STATE_DPRX_WAIT_MST_DONE_7);//STATE_DPRX_WAIT_MST_DONE_7;
        }
    }
    #endif

    //monitor fec det
    #if ((DPRX_FEC_SUPPORT == ENABLED)||(DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
    if(g_stDpRx.ucRxState > STATE_DPRX_DESKEW_CHECK_9)
    {
        if (Drv_DpRx_FecDecDet() == TRUE)
        {
            Drv_DpRx_FecDataPathSet(ENABLED);
            Drv_DpRx_Reset(DP_FEC_DEC_RST);
        }
        else if(Drv_DpRx_FecDecDet() == FALSE)
        {
            Drv_DpRx_FecDataPathSet(DISABLED);
        }
    }
    #endif
    if(g_stDpRx.ucRxState == STATE_DPRX_DEPACKET_CHECK_10)
    {
        if((Drv_DpRx_DeSkewCheck() == FAIL)&&(g_stAuxStatus.ucLink_Count > ONE_LANE))
        {
            printLT(PRINT_PRIO_HIG, "\nSKew Unlock");
            ucMinState = MIN(ucMinState, STATE_DPRX_DESKEW_CHECK_9);//-wangtt- wait confirm
        }
    }
    //monitor MSA changes event and updata MSA info.
    if(g_stDpRx.ucRxState > STATE_DPRX_MSA_CHECK_11)
    {
        //monitor color space changes event and updata color space info.
        if (Mod_DpRx_PcrColorSpaceUpdate() == TRUE)
        {
            printLT(PRINT_PRIO_HIG, "\nColor space change");
            ucMinState = MIN(ucMinState, STATE_DPRX_DEPACKET_CHECK_10);//-wangtt- wait confirm
        }
        if(Mod_DpRx_PcrMsaUpdate() == TRUE)
        {
            printLT(PRINT_PRIO_HIG, "\nMsa change");
            ucMinState = MIN(ucMinState,STATE_DPRX_DEPACKET_CHECK_10);
        }
		if(g_stDpRx.b1CompressedStream != Drv_DpRx_DscDecState())
		{
			printLT(PRINT_PRIO_HIG, "\nDSC CHNG");
            ucMinState = MIN(ucMinState, STATE_DPRX_DEPACKET_CHECK_10);
		}
    }
    #if ((DPRX_LINK_CTS == ENABLED) && (DPRX_DSC_DEC_SUPPORT == ENABLED))
    if(g_stDpRx.ucRxState > STATE_DPRX_PPS_CHECK_12)
    {
        //slove StemDeck PPS issue,just send PPS packet for a while
        if(Drv_System_IntFlagGet(IRQ_DPRX_PPS_DATA_CHG_INT) == TRUE)
        {
            Drv_System_IntClr(IRQ_DPRX_PPS_DATA_CHG_INT);
            if(Drv_DpRxDscDec_DscParaCheck() == FALSE)
            {
                if(ucHpdIrqCnt == 0)
                {
                    Mod_DpRx_HpdIrq();
                    ucHpdIrqCnt++;
                }
            }
            else
            {
                ucHpdIrqCnt = 0;
            }
        }
    }
    #endif

    //monitor PCR unstable event, just for debug
    if(g_stDpRx.ucRxState > STATE_DPRX_PCR_CONFIG_13)
    {
        if ((Drv_DpRx_PcrStableCheck() == UNSTABLE)||(DRV_DpRx_VideoStreamFlag() == FALSE))
        {
            printLT(PRINT_PRIO_HIG, "\nGoto PCR");
            ucMinState = MIN(ucMinState, STATE_DPRX_DEPACKET_CHECK_10);
        }
    }
    
    //monitor hdcp verison change
    #if DPRX_HDCP_DEC_MODE != NO_HDCP
    if (g_stDpRx.ucRxState > STATE_DPRX_HDCP_VER_CHK_14)
    {
        ucHdpcVer = Drv_HdcpRx_VerGet();
        if (g_stDpRx.ucHdcpVersion != ucHdpcVer)
        {
            g_stDpRx.ucHdcpVersion = ucHdpcVer;
            printLT(PRINT_PRIO_TEST, "\nHcdp upate");
            Mod_DpRx_MsgNotify(DPRX_HDCP_VER_CHG_EVENT);
        }
    }
    #endif

    //monitor audio 8 channel
    if(g_stDpRx.ucRxState > STATE_DPRX_AUDIO_INFO_CHK_15)
    {
        Drv_DpRx_AudioFormatSet();
//        if ((Drv_Audio_AcrMute() == FALSE) && (Mod_DpRx_AudioChannelUpdata() == TRUE))
		if(Drv_Audio_FsValStbCheck() == TRUE)
        {	
			Drv_AudioSdm_SwEn();
            printLT(PRINT_PRIO_TEST, "\nAudio chg");
            Mod_DpRx_MsgNotify(DPRX_AUDIO_CHG_EVENT);
        }
        #if DPRX_CDR_MODE == ANACDR
        if(Drv_DpRxPll_LockGet() == FALSE)
        {
            printLT(PRINT_PRIO_TEST, "\nACDR Unlock");
            ucMinState = MIN(ucMinState, STATE_DPRX_DESKEW_CHECK_9);
        }
        #endif
        #if DPRX_DSC_DEC_SUPPORT == ENABLED
        if((g_stDpRx.ucDscFifoEmpty | g_stDpRx.ucDscFifoEmpty) == 0x00)
        {
            if((g_stDpRx.ucDscFifoEmpty != Drv_DpRx_DscFifoEmptyGet())||(g_stDpRx.ucDscFifoFull != Drv_DpRx_DscFifoFullGet()))
            {
                Drv_DpRxDscDec_Rst();
                printLT(PRINT_PRIO_TEST, "\nDSCFIFO ERR");
                
//                ucMinState = MIN(ucMinState, STATE_DPRX_DESKEW_CHECK_9);
            }
        }  
        #endif
    }
    //monitor hdr
    if((g_stDpRx.ucRxState >= STATE_DPRX_PLAY_BACK_16)&&(ucMinState >= STATE_DPRX_PLAY_BACK_16))    
    {
        // monitor dobly hdr
        if((Drv_System_IntFlagGet(IRQ_DPRX_VSI_INT) == TRUE))
        {
            Drv_System_IntClr(IRQ_DPRX_VSI_INT);
            g_stDpRx.b1HdrEn = ENABLED;
            Mod_DpRx_MsgNotify(DPRX_DOBLY_HDR_NOTIFY_EVENT);
        }
        //monitor static HDR
        if(Drv_System_IntFlagGet(IRQ_DPRX_STATICHDR_INT) == TRUE)
        {
            Drv_System_IntClr(IRQ_DPRX_STATICHDR_INT);
            g_stDpRx.b1HdrEn = ENABLED;
            Mod_DpRx_MsgNotify(DPRX_STATIC_HDR_NOTIFY_EVENT);
        }
        //monitor dynamic HDR
        if(Drv_System_IntFlagGet(IRQ_DPRX_DYNAMICHDR_INT) == TRUE)
        {
            Drv_System_IntClr(IRQ_DPRX_DYNAMICHDR_INT);
            g_stDpRx.b1HdrEn = ENABLED;
            Mod_DpRx_MsgNotify(DPRX_DYNAMIC_HDR_NOTIFY_EVENT);
        }
        //adapter sync
        #if DPRX_ADAPTIVE_SYNC == ENABLED
        if(Drv_System_IntFlagGet(IRQ_DPRX_ADAPTIVE_SYNC_INT) == TRUE)
        {
            Drv_System_IntClr(IRQ_DPRX_ADAPTIVE_SYNC_INT);
            g_stAuxStatus.ucMsaIgnoreEn = ENABLED;
            g_stDpRx.b1AdaptiveSyncEn = ENABLED;
            Mod_DpRx_MsgNotify(DPRX_VRR_NOTIFY_EVENT);
        }
        else if(g_stAuxStatus.ucMsaIgnoreEn&BIT7_1)//DPCD Write 107
        {
            g_stAuxStatus.ucMsaIgnoreEn &= BIT7_0;//clear
            g_stDpRx.b1AdaptiveSyncEn = (g_stAuxStatus.ucMsaIgnoreEn&BIT7_0);
            Mod_DpRx_MsgNotify(DPRX_VRR_NOTIFY_EVENT);
        }    
        #endif
    }    
    if (ucMinState != 0xff)
    {
        Mod_DpRx_SetState(ucMinState); 
    }
}

void Mod_DpRx_StateHandler(void)
{
    static u32 ulCurrentTime = 0;
    #if ((DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
	static u8 b1DscPpsDone = NOT_SUPPORT;
    static u8 ucTryToLoadPPS = 0x00;
    #endif
    static u8 ucWaitPcrStableCnt;
//    static u8 ucDscSelect = 0x00;
    switch(g_stDpRx.ucRxState)
    {
        case STATE_DPRX_POWER_ON_1:
            Mod_DpRx_GpioInit();
            #if TYPECRX_EN == ENABLED
            DRV_CCPHY_DigSet();
            #endif
            Drv_DpRx_PowerOnInit();
            Drv_DpRx_PhyShut();//close Rterm for USB3.0 Switch use
            Mod_DpRx_SetState(STATE_DPRX_INPUT_TYPE_DET_2);
            break;

        case STATE_DPRX_INPUT_TYPE_DET_2:
            if(g_stDpRx.b1RxStateChanged == TRUE)
            {
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                g_stDpRx.b1RxStateChanged = FALSE;
            }
            if(Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_10) == TRUE)
            {
                Mod_DpRx_DpOrTypecDet();
                Mod_DpRx_SetState(STATE_DPRX_WAIT_SOURCE_3);
            }
            break;

        case STATE_DPRX_WAIT_SOURCE_3:
            if(g_stDpRx.b1SourceDet == HIGH)
            {
                Mod_DpRx_SetState(STATE_DPRX_DOWNSTREAM_READY_4);
            }
            break;

        case STATE_DPRX_DOWNSTREAM_READY_4:
            if (g_stDpRx.b1DownstreamDeviceReady == TRUE) //hdmi tx edid read OK
            {
                Mod_DpRx_SetState(STATE_DPRX_SET_HPD_5);
            }
            break;

        case STATE_DPRX_SET_HPD_5:
             if(g_stDpRx.b1RxStateChanged == TRUE)
             {              
                 Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                 Drv_Sys_ChipRxSrcSel(CHIPRX_SRC_SEL_DPRX);
                 g_stDpRx.b1RxStateChanged = FALSE;
             }
             if(Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_300) == TRUE)
             {
                Mod_DpRx_VarInit();
                Drv_DpRx_SettingInit();
				#if ((DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
                 //to clear DSC abnormal handle logic
                g_stDpRx.b1DscAbnormal = FALSE;
				#endif
                Mod_DpRx_SourceChannelSet();
                Mod_DpRx_SetState(STATE_DPRX_WAIT_LINK_TRAIN_6);
                Drv_System_IntClr(IRQ_DPRX_PPS_PKT_INT);
                Drv_System_IntSet(IRQ_DPRX_PPS_PKT_INT,ON);
             }
             break;

        case STATE_DPRX_WAIT_LINK_TRAIN_6://06
            if(Mod_Aux_GetTrainDoneStatus() == TRUE)//rx trainig done
            {              
                #if DPRX_LINK_CTS == ENABLED //solution for DPRX link CTS.//5.3.2.1 IRQ HPD Pulse Due to Loss of Symbol Lock and Clock Recovery Lock 
                if(g_stDpRx.b1RxStateChanged == TRUE)
                {
                    Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                    Drv_DpcdError_Clear(0x0F);
                    g_stDpRx.b1RxStateChanged = FALSE;
                }

                if(Mod_DpRx_8b10bErrorChk() == TRUE)
                {
                    printLT(PRINT_PRIO_HIG, "\nloss lock");
                    Mod_Aux_DealLossLock();
                    Mod_DpRx_HpdIrq();
                    #if ((DPRX_FEC_SUPPORT == ENABLED)||(DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
                    Drv_DpRx_FecSoftModeSet(FALSE);
                    #endif
                }
                #endif
                if(Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_20) == TRUE)
                {
                    #if DPRX_MST_MODE_EN == ENABLED
                    if(g_stAuxStatus.b1MstFlag == 1)  
                    {
                        Mod_DpRx_SetState(STATE_DPRX_WAIT_MST_DONE_7);
                    }
                    else
                    #endif
                    {
                        
                        Mod_DpRx_SetState(STATE_DPRX_EQ_FINE_TUNE_8);
                    }
                }
            }
            break;

        #if DPRX_MST_MODE_EN == ENABLED        
        case STATE_DPRX_WAIT_MST_DONE_7:
            if(g_stDpRx.b1RxStateChanged == TRUE)//26 bytes
            {
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                g_stDpRx.b1RxStateChanged    = FALSE;
            }
            if (g_stAuxStatus.b1MstFlag == 1)
            {
                if((g_stMstRxStatus.request_flag == 1)||(g_stMstRxStatus.payload_flag == 0)||(Mod_DpRxMst_PayloadDone() == TRUE))
                {
                    Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                    g_stMstRxStatus.request_flag = 0;
                    g_stMstRxStatus.payload_done_flag = 0;
                }
                if((Ocm_Timer_IsOverFlow(&ulCurrentTime,MS_400) == TRUE))
                {
                    #if ((DPRX_FEC_SUPPORT == ENABLED)||(DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
                    Drv_DpRx_FecSoftModeSet(g_stAuxStatus.FecFlag);
                    #endif
                    Mod_DpRx_SetState(STATE_DPRX_EQ_FINE_TUNE_8);
                }
            }
            break;
        #endif

        case STATE_DPRX_EQ_FINE_TUNE_8:
            if(g_stDpRx.b1RxStateChanged == TRUE)
            {
//                Drv_DpcdError_Clear(0x0F);
                #if ((DPRX_FEC_SUPPORT == ENABLED)||(DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
                Drv_DpRx_FecDataPathSet(DISABLED);
                #endif
                g_stDpRx.b1RxStateChanged = FALSE;
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                printLT(PRINT_PRIO_TEST, "\nRATE_LANE = 0x%02bx,0x%02bx",g_stAuxStatus.ucLink_Rate, g_stAuxStatus.ucLink_Count);
            }
            if((Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_800) == TRUE)||(DRV_DpRx_VideoStreamFlag()== TRUE))
            {
                Mod_DpRx_EqSet();
                Mod_DpRx_SetState(STATE_DPRX_DESKEW_CHECK_9);
            }
            break;

        case STATE_DPRX_DESKEW_CHECK_9:
            if(g_stDpRx.b1RxStateChanged == TRUE)
            {
                g_stDpRx.b1RxStateChanged = FALSE;
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
            }
            if(Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_100) == TRUE)
            {
                //one lane has no skew issue
                //if((Drv_DpRx_DeSkewCheck() == FAIL)&&(g_stAuxStatus.ucLink_Count > ONE_LANE))
                if(Drv_DpRx_DeSkewCheck() == FAIL)
                {
                    Drv_DpRx_Reset(DP_RX_FIFO_RST);
                    printLT(PRINT_PRIO_HIG, "\nDe-skew err");
                    Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                }
                else
                {
                    Mod_DpRx_SetState(STATE_DPRX_DEPACKET_CHECK_10);
                    
                }
            }
            break;

        case STATE_DPRX_DEPACKET_CHECK_10:
            if(g_stDpRx.b1RxStateChanged == TRUE)
            {
                #if ((DPRX_FEC_SUPPORT == ENABLED)||(DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
                Drv_DpRx_FecSoftModeSet(FALSE);//hardmode
                #endif
                #if (DPRX_TIMING_HBE == ENABLED)
                g_stDpRx.b2IsTimingHBE = HBE_NONE;
                #endif
                //remove sdp reset
                //SDP reset is needed in case of Depacket error
                //必须要保留
                Drv_DpRx_Reset(DP_RX_SDP_RST);//
                Drv_DpRx_Reset(DP_RX_PCR_RST);//New for TEST
                #if DPRX_DSC_DEC_SUPPORT == ENABLED
                Drv_DpRxDscDec_Init();
                #endif
                #if DPRX_DSC_BYPASS_SUPPORT == ENABLED
                Drv_DpRxDscBy_Init();
                #endif
                g_stDpRx.b1RxStateChanged = FALSE;
                Mod_DpRx_EccErrAbnormalHdl(DISABLED);
                Drv_DpRx_EccErrorCheck();
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);            
            }
            if(Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_100) == TRUE)
            {
                if(Drv_DpRx_EccErrorCheck() == FAIL)
                {
                    Mod_DpRx_EccErrAbnormalHdl(ENABLED);
                    Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                }
                else
                {
                    Mod_DpRx_SetState(STATE_DPRX_MSA_CHECK_11);
                }
            }
            break;

        case STATE_DPRX_MSA_CHECK_11:
            if (g_stDpRx.b1RxStateChanged == TRUE)
            {
                Drv_Sys_DecPowerDomain(FALSE);
                Drv_DpRx_MsaPktDetEn();
                Drv_DpRx_420DetectMode(SOFTMODE);
                g_stDpRx.ucPixelEncoding     = 0xff;
                g_stDpRx.ucColorimetryFormat = 0xff;
                g_stDpRx.ucBitDepth          = 0xff;
                #if (DPRX_TIMING_HBE == ENABLED)
                g_stDpRx.b2IsTimingHBE       = HBE_NONE;
                #endif
                g_stDpRx.usHotal             = 0;
                g_stDpRx.usHactive           = 0;
                g_stDpRx.b1RxStateChanged    = FALSE;
                g_stDpRx.b1VscPkg = 0x00;
                
            }
            Mod_DpRx_PcrColorSpaceUpdate();
            if(Mod_DpRx_PcrMsaUpdate() == FALSE)
            {             
                if (Drv_DpRx_DscDecState() == ENABLED)
                {                  
                    #if DPRX_DSC_DEC_SUPPORT == ENABLED                   
                    Drv_DpRxDscDec_RxInit();
                    Drv_DpRxDscDec_ParaInit();
                    #endif
                    #if DPRX_DSC_BYPASS_SUPPORT == ENABLED
//                    Drv_DpRxDscBy_RxInit();
                    Drv_DpRxDscBy_ParaInit();
                    #endif                    
					g_stDpRx.b1CompressedStream = ENABLED;
                    Mod_DpRx_SetState(STATE_DPRX_PPS_CHECK_12);
                }
                else
                {
                    #if DPRX_TIMING_HBE == ENABLED
                    if(Chip_DpRx_JudgeTimingHBE() != HBE_NONE)
                    {
                        Chip_DpRx_TimingHBE();
                    }
                    else
                    {
                        ;
                    }
                    #endif
                    Drv_Sys_DecPowerDomain(TRUE);
					g_stDpRx.b1CompressedStream = DISABLED;
                    Mod_DpRx_SetState(STATE_DPRX_PCR_CONFIG_13); 
                }
            }
            break;
        #if ((DPRX_DSC_DEC_SUPPORT == ENABLED)||(DPRX_DSC_BYPASS_SUPPORT == ENABLED))
        case STATE_DPRX_PPS_CHECK_12:
            if (g_stDpRx.b1RxStateChanged == TRUE)
            {           
                if(Drv_System_IntFlagGet(IRQ_DPRX_PPS_PKT_INT) == TRUE)
                {
                    ucTryToLoadPPS = 0x80;
                }
                else
                {
                    ucTryToLoadPPS = 0x00;
                }
                printLT(PRINT_PRIO_HIG, "\nPPSPKT = 0x%02bx",ucTryToLoadPPS);
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                g_stDpRx.b1RxStateChanged = FALSE;
				Drv_System_IntClr(IRQ_DPRX_PPS_PKT_INT);
                g_stDpRx.b1DscAbnormal = FALSE;
				b1DscPpsDone = NOT_SUPPORT; 
//                ucDscSelect = 0x00;
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
            }
            if (Ocm_Timer_IsOverFlow(&ulCurrentTime, SECOND_2) == TRUE)
            {
                if (Drv_DpRx_DscDecState() == ENABLED)
                {
                    if(Drv_DpRx_PpsInfoCheck() == FAIL)
                    {
                        g_stDpRx.b1DscAbnormal = TRUE;
                        Mod_DpRx_SetState(STATE_DPRX_WAIT_SOURCE_3); //Typec Rx CC is done or dp is ok cc is open 09           
                        Mod_DpRx_HpdLowAction();
                        g_stDpRx.b1SourceDet = LOW;
                        Mod_DpRx_MsgNotify(DPRX_SOURECE_UNPLUG_EVENT);
                    }
                }
                
                //Mod_DpRx_SetState(STATE_DPRX_DEPACKET_CHECK_10);
            }
            if (Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_1500) == TRUE)
            {
                if (Drv_DpRx_DscDecState() == ENABLED)
                {
                    ucTryToLoadPPS |= BIT0_1; 
                }
                else
                {
                    ucTryToLoadPPS = 0x00;
                }
            }
            if(Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_5) == TRUE)
            {
//                printLT(PRINT_PRIO_HIG, "\nSatble = 0x%02bx,0x%02bx",BKF3_DF_REG,BKF3_E2_REG);
//                printLT(PRINT_PRIO_HIG, "\nFreq = 0x%02bx,0x%02bx,0x%02bx",BKF3_F8_REG,BKF3_F9_REG,BKF3_FA_REG);
//                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                if ((Drv_DpRx_PpsInfoCheck() == SUCCESS)||(ucTryToLoadPPS == 0x81))
                {                  
                    if(Mod_DpRx_DecByp_Sel() == 0x00)
                    {
                        return;
                    }
                    #if DPRX_DSC_DEC_SUPPORT == ENABLED
//                    if(g_stDpRx.ucDscSel == SELDSCDECODE)//DECODEs
                    if(Drv_DpRxDscDec_SwitchGet() == ENABLED)
                    {
                        
                        Drv_DpRxDscDec_TimingGet();
                        b1DscPpsDone = Drv_DpRxDscDec_DscInfoGet();
                        #if DPRX_LINK_CTS == ENABLED
                        Drv_DpRx_DscPpsDataChg_IntSet(ENABLED);
                        Drv_System_IntSet(IRQ_DPRX_PPS_DATA_CHG, ON);
                        #endif
                        
                    }
                    #endif
                    #if DPRX_DSC_BYPASS_SUPPORT == ENABLED
                    if(Drv_DpRxDscBy_SwitchGet() == ENABLED)
                    {           
                        Drv_DpRxDscBy_RxInit();
                        Drv_DpRxDscBy_TimingGet();
                        b1DscPpsDone = Drv_DpRxDscBy_DscInfoGet();
                        Mod_DpRx_SetState(STATE_DPRX_PCR_CONFIG_13);
                        
                    }
                    #endif
                    if(b1DscPpsDone == CAN_RUNNING)
					{                       
						Mod_DpRx_SetState(STATE_DPRX_PCR_CONFIG_13);                    
					}					
                }
                
            }
            break;
        #endif
        case STATE_DPRX_PCR_CONFIG_13:
            if (g_stDpRx.b1RxStateChanged == TRUE)
            {           
                #if DPRX_DSC_BYPASS_SUPPORT == ENABLED
                if(Drv_DpRxDscBy_SwitchGet() == ENABLED)
                {
                    if (Drv_DpRx_DscDecState() == ENABLED)
                    {
                        Drv_DpRx_SyncPolSet(ENABLED);
                        Drv_DpRxDscBy_ModuleEnable();//first dsc bypass en, then pcr stable
                    }
                }
                #endif
                //no need to check MSA again
//                Mod_DpRx_PcrColorSpaceUpdata();
//                Drv_DpRx_Reset(DP_RX_PCR_RST);
                Drv_DpRx_VidFreqSetCheck(DISABLED);
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                printLT(PRINT_PRIO_TEST,"\nWait pcr stable...");
                g_stDpRx.b1RxStateChanged = FALSE;
                ucWaitPcrStableCnt = 0;
//                Drv_DpRx_HsyncPcrErrSet(g_stDpRx);
            }
            Drv_DpRx_VidFreqSetCheck(ENABLED);
            if (Ocm_Timer_IsOverFlow(&ulCurrentTime, MS_100) == TRUE)
            {
                //if (Drv_DpRx_PcrStableCheck() == STABLE)//first pcr stable, then dsc dec
                if((Drv_DpRx_PcrStableCheck() == STABLE)&&(DRV_DpRx_VideoStreamFlag()== TRUE))
                {
                    #if DPRX_DSC_DEC_SUPPORT == ENABLED
                    if(Drv_DpRxDscDec_SwitchGet() == ENABLED)
                    {
                        if (Drv_DpRx_DscDecState() == ENABLED)
                        {
                            Drv_DpRx_SyncPolSet(ENABLED);
                            Drv_DpRxDscDec_ModuleEnable();
                        }
                    }
                    #endif
                    Mod_DpRx_SetState(STATE_DPRX_HDCP_VER_CHK_14);
                }
                else if(DRV_DpRx_VideoStreamFlag()== FALSE)
                {
                    return;
                }
            }
            //in case of PCRPLL unlock issue
            if(Ocm_Timer_IsOverFlow(&ulCurrentTime,MS_500) == TRUE)
            {           
                ucWaitPcrStableCnt++;
                if(ucWaitPcrStableCnt == 10)
                {
                    #if REMOVE_UART == DISABLED
                    printLT(PRINT_PRIO_HIG, "\nPCR HARD RESET");
                    #endif
                    #if DPRX_PCRPLL_HRST == DISABLED
                    Drv_DpRx_PcrPllRst(ENABLED);
                    #endif
                    Drv_DpRx_Reset(DP_RX_PCR_RST);
                    Ocm_Delay1ms(2);
                    #if DPRX_PCRPLL_HRST == DISABLED
                    Drv_DpRx_PcrPllRst(DISABLED);
                    #endif
                    ucWaitPcrStableCnt = 0;
                }
               //DRV_DpRx_VidPcrReset();
               Ocm_Timer_UpdLocalTime(&ulCurrentTime);
            }
            break;

        case STATE_DPRX_HDCP_VER_CHK_14:
            if (g_stDpRx.b1RxStateChanged == TRUE)
            {              
                g_stDpRx.ucHdcpVersion = NO_HDCP;
                g_stDpRx.b1RxStateChanged = FALSE;
                Ocm_Timer_UpdLocalTime(&ulCurrentTime);
                g_stDpRx.ucDscFifoEmpty = Drv_DpRx_DscFifoEmptyGet();
                g_stDpRx.ucDscFifoFull = Drv_DpRx_DscFifoFullGet();
            }
            Mod_DpRx_SetState(STATE_DPRX_AUDIO_INFO_CHK_15);
            break;

        case STATE_DPRX_AUDIO_INFO_CHK_15://0d
            if (g_stDpRx.b1RxStateChanged == TRUE)
            {
                g_stDpRx.b1RxStateChanged = FALSE;
            }
            Mod_DpRx_SetState(STATE_DPRX_PLAY_BACK_16);
            break;

        case STATE_DPRX_PLAY_BACK_16://0d
            Mod_DpRx_ColorimetryUpdata();
            break;

        default:
            break;
    }
}

void Mod_DpRx_Handler(void)
{
    Mod_DpRx_SourceDetProc();
    Mod_DpRx_StateJudge();
    Mod_DpRx_StateHandler();
    #if DPRX_MST_MODE_EN == ENABLED
    Mod_DpRx_MstHandler();
    #endif
}
#endif
