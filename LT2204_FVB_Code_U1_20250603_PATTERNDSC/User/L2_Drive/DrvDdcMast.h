//////////////////////////////////////
//Project:   LT2101
//Filename:  DdcMast.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DDCMAST_H
#define _DDCMAST_H

#include "LtType.h"

#if TX_PORT_SIGN == HDMI_PORT

extern void Drv_HdmiTx_DdcMstRst(void);
extern void Drv_HdmiTx_WriteI2CByte(u16 usRegAddr, u8 ucValue);
extern u8 Drv_HdmiTx_ReadI2CByteN(u8 ucSegmentAddr,u16 usRegAddr, u8 *pucValue,u8 ucNum);
extern u8 Drv_HdmiTx_ReadI2CByte(u16 usRegAddr);

#endif

#endif

