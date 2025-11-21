//////////////////////////////////////
//Project:   LT2101
//Filename:  Timer.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _TIMER_H
#define _TIMER_H

#include "LtType.h"

#define RX_BUFF_MAX 20
#define TX_BUFF_MAX 20

#define BAUDRATE    62500//18750,37500,62500, 52000,63550(for FPGA)
#define INT_TIME    250//an interrupt is generated every 250us for timer0
#define MS_COUNT    (u8)(1000/(INT_TIME))

#define MS          MS_COUNT
#define MS_2        (MS)*2
#define MS_3        (MS)*3
#define MS_5        (MS)*5
#define MS_10       (MS)*10
#define MS_20       (MS)*20
#define MS_26       (MS)*26
#define MS_27       (MS)*27
#define MS_30       (MS)*30
#define MS_40       (MS)*40
#define MS_50       (MS)*50
#define MS_60       (MS)*60
#define MS_70       (MS)*70
#define MS_80       (MS)*80
#define MS_90       (MS)*90
#define MS_100      (MS)*100
#define MS_120      (MS)*120
#define MS_150      (MS)*150
#define MS_200      (MS)*200
#define MS_260      (MS)*260
#define MS_300      (MS)*300
#define MS_400      (MS)*400
#define MS_435      (MS)*435
#define MS_450      (MS)*450
#define MS_500      (MS)*500
#define MS_520      (MS)*520
#define MS_550      (MS)*550
#define MS_600      (MS)*600
#define MS_800      (MS)*800
#define MS_835      (MS)*835
#define MS_1200     (MS)*1200
#define MS_1500     (MS)*1500
#define SECOND_1    (MS)*1000
#define SECOND_2    (MS)*2000
#define SECOND_3    (MS)*3000
#define SECOND_4    (MS)*4000
#define SECOND_5    (MS)*5000 
#define SECOND_6    (MS)*6000 
#define SECOND_8    (MS)*8000 
#define SECOND_12   (unsigned int)(MS)*12000

typedef struct
{
    u8 RxData[RX_BUFF_MAX];//Data received by the uart rx
    u8 RxNumber;//The current number of valid data(rx), cleared after use
    u8 RxSwitch;//Switch to receive data for uart rx
    u8 TxData[TX_BUFF_MAX];//Data sent by the uart tx
    u8 TxNumber;//The current number of valid data(tx), cleared after use
}UartData_S;

extern void Ocm_Timer2_Set(void);

extern void Ocm_Timer_UpdLocalTime(INOUT u32 *pstCurtTime);
extern void Ocm_Timer_Init(void);
extern void Ocm_Delay1ms(IN u16 var);
extern void Ocm_Delay1us(IN u16 var);
extern void Ocm_TR2_ValueSet(void);//4ms
extern u8 Ocm_Timer_IsOverFlow(INOUT u32 *ulSource, IN u32 ulDelay);
extern void Ocm_Timer2ForPsRdy_Set(void);
#endif

