/******************************************************************************
  * @project: LT2204
  * @file: DrvHdmiRx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.06.07
/******************************************************************************/
#ifndef _DRVHDMIRX_H
#define _DRVHDMIRX_H

#include "LtType.h"

#if RX_PORT_SIGN == HDMI_PORT

extern void Drv_HdmiRx_Tmds_CdrSet(u8 ucOpt);

extern void Drv_HdmiRx_HpdSet(u8 b1IsHigh);
extern void Drv_HdmiRx_PhySet(u8 ucOpt);
extern void Drv_HdmiRx_TenBitSet(void);
extern void Drv_HdmiRx_PllModeSet(u8 ucOpt);
extern void Drv_HdmiRx_Tmds_PiSet(u8 ucOpt);
extern void Drv_HdmiRx_Tmds_PllCali(void);
extern void Drv_HdmiRx_Tmds_PllVcoReset(void);
extern void Drv_HdmiRx_Frl_CdrSet(u8 ucFrlRate);
extern void Drv_HdmiRx_Frl_PiSet(u8 ucFrlRate);
extern void Drv_HdmiRx_Frl_PllBandSet(u8 frlrate);
extern void Drv_HdmiRx_DigInit(u8 ucOpt);
extern void Drv_HdmiRx_PowerOnInit(void);
extern void Drv_HdmiRx_SecPcrPower(u8 ucOpt);
extern void Drv_HdmiRx_SettingInit(void);
extern void Drv_HdmiRx_RtermCali(void);
extern void Drv_HdmiRx_PowerDown(void);
extern void Drv_HdmiRx_EdidLoad(u8 *pEDID_Data);
extern void Drv_HdmiRx_AudioInfoGet(AudioChlInfo_S *pstInfo);
extern void Drv_HdmiRx_RxpllDivSet(u8 ucOpt);
extern void Drv_HdmiRx_ScrambeTimerSet(u8 ucOpt);
extern void Drv_HdmiRx_NewErrorStatistic(u8 ucOpt);
extern void Drv_HdmiRx_PhyRst(void);
extern void Drv_HdmiRx_Frl_PhyCtleSet(u8 ucFrlRate);
extern void Drv_HdmiRx_Tmds_PhyCtleSet(u8 ucOpt);
extern void Drv_HdmiRx_ClkMux(u8 ucOpt);
extern void Drv_HdmiRx_PcrClkMux(void);
extern void Drv_HdmiRx_SecPcrClkMux(void);
extern void Drv_HdmiRx_RxTimingGet(LtTiming_S *pstTiming);
extern void Drv_HdmiRx_ColorInfoGet(ColorInfo_S *pstInfo);
extern void Drv_HdmiRx_LogicalReset(void);
extern void Drv_HdmiRx_Frl_ErrClr(void);
extern void Drv_HdmiRx_Frl_FecErrClr(void);
extern void Drv_HdmiRx_Tmds_ErrClr(void);
extern void Drv_HdmiRx_SyncPolSet(u8 ucOpt);
extern void Drv_HdmiRx_ErrValidClr(u8 ucOpt);
extern void Drv_HdmiRx_Reset(EnumHdmiRstType ucOpt);
extern void Drv_HdmiRx_PktClr(EnumHdmiRstType ucOpt);
extern u8 Drv_HdmiRx_PacketInfoCheck(void);
extern u8 Drv_HdmiRx_DscDecState(void);
extern u8 Drv_HdmiRx_VersionGet(void);
extern u8 Drv_HdmiRx_DeSkewCheck(void);
extern u8 Drv_HdmiRx_LinkVidTimingChk(void);
extern u8 Drv_HdmiRx_Tmds_RxPllCaliCheck(void);
extern u8 Drv_HdmiRx_VrrDet(void);
extern u8 Drv_HdmiRx_HdmiModeGet(void);
extern void Drv_HdmiRx_Frl_HwEqEn(void);
extern void Drv_HdmiRx_Frl_HwEqInit(void);
extern void Drv_HdmiRx_Tmds_HwEqEn(void);
extern void Drv_HdmiRx_Tmds_HwEqInit(void);
extern u8 Drv_HdmiRx_Tmds_ClkStbChk(void);
extern void Drv_HdmiRx_TmdsPcrPllDis(void);
extern void Drv_HdmiRx_TmdsPcrPllCal(u32 ulTmdsClk);
extern u8 Drv_HdmiRx_AudioChangeDetect();
extern u8 Drv_HdmiRx_VideoDisappearDetect();

#endif

#endif
