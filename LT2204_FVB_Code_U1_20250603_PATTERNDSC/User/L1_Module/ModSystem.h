//////////////////////////////////////
//Project:   LT2101
//Filename:  ChipSystem.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CHIPSYSTEM_H
#define _CHIPSYSTEM_H

#include "LtType.h"

#if TX_PORT_SIGN == DP_PORT

extern void Mod_Audio_DpTxInfoCvt(IN AudioChlInfo_S *pstRxInfo,OUT DpTx_S *pstDpTx ); 
extern void Mod_DpTx_ColorDepthCal(IN ColorInfo_S *pstRxInfo,OUT DpTx_S *pstDpTx );
extern void Mod_DpTx_ColorSpaceCal(IN ColorInfo_S *pstRxInfo,OUT DpTx_S *pstDpTx );
extern void Mod_DpTx_ColorRangeCal(IN ColorInfo_S *pstRxInfo,OUT DpTx_S *pstDpTx );
extern void Mod_DpTx_ColorimetryCal(IN ColorInfo_S *pstRxInfo,OUT DpTx_S *pstDpTx );
#endif


#if TX_PORT_SIGN == HDMI_PORT
extern void Mod_Audio_HdmiTxInfoCvt(IN AudioChlInfo_S *pstRxInfo,OUT HdmiTx_S *pstHdmiTx);
extern void Mod_HdmiTx_ColorSpaceCal(IN ColorInfo_S *pstRxInfo,OUT HdmiTx_S *pstHdmiTx);
extern void Mod_HdmiTx_ColorRangeCal(IN ColorInfo_S *pstRxInfo,OUT HdmiTx_S *pstHdmiTx);
extern void Mod_HdmiTx_ColorimetryCal(IN ColorInfo_S *pstRxInfo,OUT HdmiTx_S *pstHdmiTx);
extern void Mod_HdmiTx_AspectRatioCal(HdmiTx_S *pstHdmiTx);
extern void Mod_HdmiTx_VicCal(IN LtTiming_S *pstRxTimingInfo,OUT HdmiTx_S *pstHdmiTx);
extern void Mod_HdmiTx_ColorDepthCal(IN ColorInfo_S *pstRxInfo,OUT HdmiTx_S *pstHdmiTx);
#endif

#if ((TX_PORT_SIGN == MIPI_PORT) || (TX_PORT_SIGN == LVDS_PORT))
extern void PWM_Init(u8 ucPwmGPIO , u8 ucPwmKhz , u8 ucValue);

#if RX_PORT_SIGN == DP_PORT
#if CUSTOM_EDID_SWITCH == ENABLED
extern void Custom_EDID_Select(void);
extern void Custom_EDID_Switch(void);
extern void Custom_EDID_Config(u8 *szEdidData);
extern void Custom_Init(void);
extern void Custom_Handler(void);
#endif
#endif
#endif

#if ((LVDXTX_VID_PATTERN_MODE != NO_PATTERN) ||(MIPITX_VID_PATTERN_MODE != NO_PATTERN))
extern void ModPattern_Init(void);
#endif

#endif

