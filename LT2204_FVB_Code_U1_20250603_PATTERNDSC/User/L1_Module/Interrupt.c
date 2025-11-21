//////////////////////////////////////
//Project:   LT2101
//Filename:  Interrupt.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

void Mod_IT0_InterruptService(void) interrupt 0
{
    #if RX_PORT_SIGN == DP_PORT
    if(Drv_System_IntFlagGet(IRQ_DPRX_AUX_INT))//aux rx_int flag
    {
        Drv_System_IntClr(IRQ_DPRX_AUX_INT);
        Mod_DpRx_AuxTask();
        Drv_DpRx_AcAuxTermCtrl(ENABLED);
    }
    #endif
    #if RX_PORT_SIGN == HDMI_PORT
    #if HDMIRX_MAX_FRL_RATE != FRL_NOT_SPT
    if(BKE5_41_REG & BIT4_1)//Hrx21_int
    {
        BKE5_31_REG |= BIT4_1;//[5]hdmi21 rx int clr en
        BKE5_31_REG &= BIT4_0;//[5]hdmi21 rx int clr dis
        Mod_FrlRx_FrlTask();
    }
    #endif
    #endif
    
}

void Mod_IT1_InterruptService(void) interrupt 2
{
	#if BB_EN == ENABLED
	if((BKE5_10_REG & BIT6_1)==0x00)
	{
		if(BKE5_40_REG & BIT6_1)//BB intr
		{    
			//printLT(PRINT_PRIO_HIG, "\nBB = 0x%02bx,0x%02bx,0x%02bx",BKC5_21_REG,BKC5_22_REG,BKC5_23_REG);
			BKE5_30_REG |= BIT6_1;//[5]clear bb_ininterrupt en
			BKE5_30_REG &= BIT6_0;//[5]clear bb_ininterrupt dis
			Drv_BB_Interrupt();
		}
	}
    #endif
    #if ((CHIP_SEL == LT8711GXE)||(CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP)||(CHIP_SEL == LT6711GXE))
    #if TYPECRX_EN == ENABLED
    if(Drv_System_IntFlagGet(IRQ_CC1_INT))  //CC1 int
    {
        Drv_System_IntClr(IRQ_CC1_INT);
        Mod_CC1Pd_Interrupt();
    }
    if(Drv_System_IntFlagGet(IRQ_CC2_INT))  //CC2 int
    {
        Drv_System_IntClr(IRQ_CC2_INT);
        #if TYPECTX_EN == ENABLED
        Mod_CC2Pd_Interrupt();
        #endif
    }
    #endif
    #endif

    
}

void Mod_IT2_InterruptService(void) interrupt 8 /////
{    
    EXIF = 0x00;//soft clear the ex2
}

void Mod_Time2_InterruptService(void) interrupt 5// 0.25us per count,can be set by register
{
    TF2 = 0;
    TR2 = 0;
    #if ((CHIP_SEL == LT8711GXE)||(CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP)||(CHIP_SEL == LT6711GXE))
//    #if DPRX_CDR_MODE != ANACDR
//    while((g_stAuxStatus.ucTps_Pattern >= TPS1) && (g_stAuxStatus.usDelayCnt < 0x4E20)) //to fix cdr loop unlock issue.
//    {
//        DRV_DpRxCdr_FreqMonitor(g_stAuxStatus.ucLink_Count);
//        g_stAuxStatus.usDelayCnt++;
//    }
//    #endif
    
    #if TYPECRX_EN == ENABLED
    if(UCCStatus.b1PsRdy_Send== TRUE)//PS_RDY send
    {
        #if TYPECTX_EN == ENABLED
        Mod_CC1PsRdy_Send();
        #endif
    }
    else //Message resend
    {      
        Mod_CC1MsgSend_Retry();
        #if TYPECTX_EN == ENABLED
        Mod_CC2MsgSend_Retry();
        #endif
    }
    #endif
    #endif
}
