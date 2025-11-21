//////////////////////////////////////
//Project:   LT2101
//Filename:  DrvSystem.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DRVSYSTEM_H
#define _DRVSYSTEM_H

#include "LtType.h"
#include "DrvLmTxCommon.h"

extern void Drv_System_XtalSet(void);
extern void Drv_System_VidPatternSet(void);
extern void Drv_Vid_TimingGet(LtTiming_S *pstTiming);
extern void Drv_System_AudioPatternSet(void);

extern void Drv_System_IntSet(EnumInterrupt ucIntType, u8 b1IsOn);
extern u8 Drv_System_IntSrcGet(EnumInterrupt ucIntType);
extern u8 Drv_System_IntFlagGet(EnumInterrupt ucIntType);
extern void Drv_System_IntClr(EnumInterrupt ucIntType);

extern void Drv_System_VidChkSet(u8 ucSrc);
extern void Drv_System_PktHeadSet(EnumPacktType ucType);
extern u8 Drv_System_VidChkStateGet(u8 b1GetEnable);
extern u8 Drv_System_PktDataChk(EnumPacktType ucType);

extern void Drv_System_FmSet(EnumFreqMeter emType, u8 ucSrc);
extern u32 Drv_System_FmGet(EnumFreqMeter emType, u8 ucOpt);
extern u8 Drv_System_FmStbGet(EnumFreqMeter emType);

extern void Drv_Sys_ChipRxSrcSel(u8 ucSel);
extern void Drv_System_SramPathSet(IN EnumSramPath ucPath);
extern void Drv_Sys_DhTxSrcSel(u8 ucSel);
extern void Drv_Sys_LmOutSel(u8 ucSel);
extern void Drv_Sys_HdcpKeyLoad(void);

extern void Drv_Sys_LmtxPowerDomain(u8 b1IsPowerOn);
extern void Drv_Sys_DHTxPowerDomain(u8 b1IsPowerOn);
extern void Drv_Sys_DHRxPowerDomain(u8 b1IsPowerOn);
extern void Drv_Sys_DecPowerDomain(u8 b1IsPowerOn);
extern void Drv_Sys_EncPowerDomain(u8 b1IsPowerOn);


#if ((LVDXTX_VID_PATTERN_MODE != NO_PATTERN) ||(MIPITX_VID_PATTERN_MODE != NO_PATTERN))
extern void Drv_PtnClk_Set(u8 Value_0xA32A,u8 Value_0xA32B);
extern void Drv_PtnPCR_Init(void);
extern void Drv_PtnTiming_Set(struct TIMING *CustomTiming);
extern void Drv_PtnType_Sel(void);
extern void Drv_PtnDataClk_Mux(void);
#endif

#if ((CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))

#define AUD_FS_ZERO		0
#define AUD_FS_48K		48
#define AUD_FS_44K		44
#define AUD_FS_32K		32
#define AUD_FS_88K		88
#define AUD_FS_96K		96
#define AUD_FS_176K		176
#define AUD_FS_192K		192
#define AUD_FS_VOID     0xFF

#if TX_PORT_SIGN == MIPI_PORT
extern void Drv_MipiTx_Info_Update(u8 ucEvent);
#endif

extern u8 Drv_DPRX_AudFs_Update(void);
extern void Drv_Aud_Info_Update(u8 IsTrue);

extern void Drv_Sys_LT7911gxe_HdcpRx_PowerDomain(u8 b1IsPowerOn);

#if CHIP_SEL == LT7911UXE_DP
extern u8 Drv_GPIO_INT_level_Get(void);
#endif

#if CHIP_SEL == LT6911GXD_DP
extern u8 Drv_GPIO25_PWM3_level_Get(void);
#endif


#endif


#if ((TX_PORT_SIGN == MIPI_PORT) || (TX_PORT_SIGN == LVDS_PORT))
extern void Custom_EDID_LoadFromFlash(void);
extern void Drv_I2sGpio_1P8VSet(void);

extern void Drv_PWM0_Sel(u16 CycleFreq , u16 Cycle);
extern void Drv_PWM1_Sel(u16 CycleFreq , u16 Cycle);
extern void Drv_PWM2_Sel(u16 CycleFreq , u16 Cycle);
extern void Drv_PWM3_Sel(u16 CycleFreq , u16 Cycle);

typedef enum TX_EVENT
{
 	TX_SINK_PLUG_EVENT_1 = 1,
	TX_SINK_UNPLUG_EVENT_2,
	TX_VIDEO_ON_EVENT_3,
	TX_VIDEO_OFF_EVENT_4,
	TX_AUDIO_CHANGE_EVENT_5,	
	//add more
}TX_EVENT_ENUM;

extern void TX_Event_Init(void);
extern void TX_Event_Set(u8 TxEvent);
extern u8 TX_Event_Get(void);
extern u8 TX_Event_Trig(void);
extern void TX_Event_Clr(void);
#endif

#if ((RX_PORT_SIGN == DP_PORT) &&(TX_PORT_SIGN == MIPI_PORT))
void Drv_Sys_LT7911gxe_MipiTx_PowerDomain(u8 b1IsPowerOn);
#endif

#if  ((RX_PORT_SIGN == DP_PORT) && (TX_PORT_SIGN == LVDS_PORT))
void Drv_Sys_LT7911gxe_LvdsTx_PowerDomain(u8 b1IsPowerOn);
#endif

#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD))
void Drv_Sys_LT6911GXE_PowerDomain();
#endif

#endif
