//////////////////////////////////////
//Project:   LT2101
//Filename: Drv HdmiTx.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DRVHDMITX_H
#define _DRVHDMITX_H

#include "LtType.h"

#if TX_PORT_SIGN == HDMI_PORT

#define  TXRTERM_45     0
#define  TXRTERM_50     1
#define  TXRTERM_55     2
#define  TXRTERM_60     3
#define  TXRTERM_65     4
#define  TXRTERM_70     5
#define  TXRTERM_75     6
#define  TXRTERM_80     7

extern u8 Drv_HdmiTx_HpdDet(void);
extern u8 Drv_HdmiTx_ResenState(void);
extern u8 Drv_HmdiTx_EdidRead(u8 *pucEDID_Data);

extern void Drv_HdmiTx_DdcInit(void);
extern void Drv_HdmiTx_PhyInit(void);
extern void Drv_HdmiTx_RtermCali(u8 TxRtermSel);
extern void Drv_HdmiTx_TmdsVideoOn(void);
extern void Drv_HdmiTx_PhyDis(void);
extern void Drv_HdmiTx_ColorInfoSet(IN HdmiTx_S  pstHdmiTx);
extern void Drv_HdmiTx_TxPllInit(void);
extern void Drv_HdmiTx_EncPath(void);
extern void Drv_HdmiTx_StaticHdrEnable(void);
extern void Drv_HdmiTx_DoblyHdrEnable(void);
extern void Drv_HdmiTx_DymicHdrEnable(void);
extern void Drv_HdmiTx_DebounceSet(void);
extern void Drv_HmdiTx_PowerOnInit(void);
extern u16 Drv_HdmiTx_FrlJitGet(void);
extern void Drv_HdmiTx_AudioInfoSet(HdmiTx_S pstHdmiTx);
extern void Drv_HdmiTx_FrlTxPhySet(u8 ucFrlRate);
extern void Drv_HdmiTx_FrlTxPllCal(u8 ucFrlRate);
extern void Drv_HdmiTx_ParaSet(OUT HdmiTx_S *pstHdmiTx);
extern void Drv_HdmiTx_FrlFecLinClkCal(OUT HdmiTx_S *pstHdmiTx);
extern void Drv_HdmiTx_FrlTxRst(u8 b1ResetEn);
#if HDMITX_VRR_SUPPORT == ENABLED
extern void Drv_HdmiTx_VrrEnable(void);
#endif
extern void Drv_HdmiTx_GcpSet(u8 b1En);
extern void Drv_HdmiTx_SpdSet(u8 b1En);
extern void Drv_HdmiTx_VicUD0Set(u8 b1En);
extern void Drv_HdmiTx_VicSet(u8 b1En);
extern void Drv_HdmiTx_AviInfoSet(HdmiTx_S pstHdmiTx);
extern void Drv_HdmiTx_SpdInfoSet(void);
extern u8 Drv_HdmiTx_FrlUpdateChg(void);
extern void Drv_HdmiTx_Reset(EnumHdmiTxRstType ucOpt,u8 ucFunctional);
#endif

#endif
