/******************************************************************************
  * @project: LT2204
  * @file: FrlRx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.06.27
/******************************************************************************/
#ifndef _DPLINKCTS_H
#define _DPLINKCTS_H
#include "LtType.h"

#if TX_PORT_SIGN == DP_PORT

extern void Mod_DpTx_TestEdid(u8 b1IsInrq,u8 *pucEDID_Data);
extern void Mod_DpTx_HpdIrqHdl(void);

#endif
#endif