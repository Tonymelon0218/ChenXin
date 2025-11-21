//////////////////////////////////////
//Project:   LT2101
//Filename:  Timer.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

#define TEMP_T0 (65535 - (48 * INT_TIME) / 12)//25MHZ
#define T0_TH   (u8)((TEMP_T0) >> 8)
#define T0_TL   (u8)(TEMP_T0)

//T1_TH = T1TL = 256 - 40MHz * 2 / (384 * BAUDRATE)
#if BAUDRATE == 18750
#define T1_TH   246
#define T1_TL   246
#elif BAUDRATE == 37500
#define T1_TH   251
#define T1_TL   251
#elif BAUDRATE == 62500//for 48M sysclk
#define T1_TH   252
#define T1_TL   252
#elif BAUDRATE == 52000//for 40M sysclk
#define T1_TH   252
#define T1_TL   252
#endif

u32 g_ulSystemTime;

//===========================================
//func  :used to that delay is required
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Ocm_Delay1ms(IN u16 var)          
{
    u16 i;
    while(var--)
    {
        #if SYSCLK == SYS_CLK_40M
        for(i = 0; i< 600 ; i++);
        #endif
        #if SYSCLK == SYS_CLK_48M
        for(i = 0; i< 628; i++);
        #endif
    }
}

//===========================================
//func  :used to that delay is required
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Ocm_Delay1us(IN u16 var)          
{
    while(var--)//0.97us each cycle
    {
        ;
    }
}

//===========================================
//func  :timer0 init
//input :N/A
//output:N/A
//return:void
//Info  :g_ulSystemTime is count by this timer
//===========================================
void Ocm_Timer0_SysTimerInit(void)
{
    TMOD |= 0x01;
    TH0 = T0_TH;
    TL0 = T0_TL;
    
    EA =  1;
    ET0 = 1;
    TR0 = 1;
}

//=================
//Func  :uart band rate set
//InPut :N/A
//OutPut:N/A
//return:void
//Info  :macro define BAUDRATE determine rate
//TH1=256-(fosc*S_MOD)/(baudrate*12*32);//SMOD=1,
//TL1=256-(fosc*S_MOD)/(baudrate*12*32);
//=================
void Ocm_Timer1_UartBaudRateSet(void)
{
    SCON = 0x50;
    PCON |=0x80;//smod=1, the baud rate is double
    TMOD |=0x20;
    TH1 = T1_TH;
    TL1 = T1_TL;
    TR1 = 1;
    TI  = 1;//for printf function must setting TI = 1

    REN = 1;
    RI  = 1;
}
//=================
//Func  : external int0
//InPut :N/A
//OutPut:N/A
//return:void
//Info  :external int for dprx typec rx or other external int need
//=================

void Ocm_External0_IntSet(void)
{
    IT0 = 0;//TCON = 0x05; ext0 dianpingchufa
    EX0 = 1;
    PX0 = 1;// EX0 max priorty
    EA =  1;
}
//=================
//Func  : external int1
//InPut :N/A
//OutPut:N/A
//return:void
//Info  :external int for dprx typec rx or other external int need
//=================

void Ocm_External1_IntSet(void)
{
    IT1 = 0;//TCON = 0x05; ext1 dianpingchufa
    EX1 = 1;
    EA =  1;
}

void Ocm_TR2_ValueSet(void)//4ms
{
    TH2 = 0xF1;//700us
    TL2 = 0xA6;
}
//============================
//Func  : external int2
//InPut :N/A
//OutPut:N/A
//return:void
//Info  :external int for dprx typec rx or other external int need
//=============================

void Ocm_External2_IntSet(void)
{
    EIP = 0x00;//ex2 low pority
    EIE = 0x01;//enable ex2
    EA =  1;
}

//=================
//Func  : external it2
//InPut :N/A
//OutPut:N/A
//return:void
//Info  :timer2 for send typec ps rdy
//=================

void Ocm_Timer2_Set(void)
{
    TH2 = 0x00;//
    TL2 = 0x00;
    TR2 = 1;   //enable Time0
}

void Ocm_Timer2_IntSet(void)
{
    T2CON = 0x01;//EXEN2
    TL2 = 0x00;//time 0 disable
    TH2 = 0x00;//time 1 disable
    TR2 = 0;
    ET2 = 1;
    EA =  1;
}

void Ocm_Timer2ForPsRdy_Set(void)
{
    TH2 = 0xC0;//4ms
    TL2 = 0x00;
    TR2 = 1;   //enable Time0
}
//===========================================
//func  :update system time to local
//input :*pstCurtTime is local time
//output:*pstCurtTime will become system time
//return:void
//Info  :N/A
//===========================================
void Ocm_Timer_UpdLocalTime(INOUT u32 *pstCurtTime)
{
    u32 ulPresentTime = g_ulSystemTime;

    if (abs(g_ulSystemTime - ulPresentTime) > 0x7f)
    {
        ulPresentTime = g_ulSystemTime;
    }
    *pstCurtTime = ulPresentTime;
}

//===========================================
//func  :system time init
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Ocm_Timer_ParaInit(void)
{
    g_ulSystemTime = 0;
}

//===========================================
//func  :check current time whether overflows
//input :*ulSource is local time, ulDelay is current delay time
//output:*ulSource will become system time
//return:TRUE-overflow, FALSE-not
//Info  :N/A
//===========================================
u8 Ocm_Timer_IsOverFlow(INOUT u32 *ulSource, IN u32 ulDelay)
{
    u32 ulTimeS;
    u32 ulTimeG;

    ulTimeG = g_ulSystemTime;
    ulTimeS = *ulSource;

    if(ulTimeS > ulTimeG)
    {
        *ulSource = ulTimeG;
        ulTimeS = ulTimeG;
        return FALSE;
    }
    if((ulTimeS + ulDelay) < ulTimeG)
    {
        return TRUE;
    }
    return FALSE;
}
//===========================================
//func  :uart struct data init
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Ocm_Timer_UartParaInit(void)
{
    #if 0
    g_stUartData.RxSwitch = OFF;
    #endif
}

//===========================================
//func  :acquire uart rx data, and save to g_stUartData.RxData
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Ocm_Timer_UartDataGet(void)
{
    #if 0
    if (RI == 0)
    {
        return;
    }
    if((g_stUartData.RxSwitch == ON) && ((g_stUartData.RxNumber + 1) < RX_BUFF_MAX))
    {
        g_stUartData.RxData[g_stUartData.RxNumber++] = (u8)SBUF;
    }
    RI = 0;
    #endif
}
//===========================================
//func  :common init
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Ocm_Timer_Init(void)
{
    Ocm_Timer_ParaInit();
    Ocm_Timer0_SysTimerInit();
    Ocm_Timer1_UartBaudRateSet();
    Ocm_External0_IntSet();
    Ocm_External1_IntSet();
    Ocm_External2_IntSet();
    Ocm_Timer2_IntSet();
    Ocm_Timer_UartParaInit();
}

//===========================================
//func  :timer0 interrupt
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Timer0Interrupt(void) interrupt 1
{
    TH0 = T0_TH;
    TL0 = T0_TL;
    g_ulSystemTime++;
    Ocm_Timer_UartDataGet();
    #if ((CHIP_SEL == LT8711GXE)||(CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP)||(CHIP_SEL == LT6711GXE))
    #if TYPECRX_EN == ENABLED
    #if TYPEC_FRSWAP_EN == ENABLED
    if(UCCStatus.ucFlow_Step != 0x01)
    {
        return;
    }
    if((DCCStatus.b1FrTriggle == TRUE)&&(UCCStatus.b1PrDone == TRUE))
    {
        if(BKE5_A1_REG & BIT0_1)
        {
            DRV_FrTrig_Send();
            UCCStatus.ucFRSwaping = FRSWAP_INITIATE;
//            SOURCE_GPIO_CTRL(LOW);
            Mod_CC2PowerLost_VarIni();
        }
    }
    #endif
    #endif
    #endif
}
