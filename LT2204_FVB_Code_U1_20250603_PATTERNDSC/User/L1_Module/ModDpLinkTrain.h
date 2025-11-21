/******************************************************************************
  * @project: LT2204
  * @file: ChipDpTx.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.05.30
/******************************************************************************/

#ifndef _DPLINKTRAIN_H
#define _DPLINKTRAIN_H

#include "LtType.h"

#if TX_PORT_SIGN == DP_PORT

typedef enum
{
    STATE_LINK_NOTSTRAT_0 = 0,
    STATE_LINK_INIT_1 = 1,
    STATE_LINK_TXPLLCAL_2,
    STATE_LINK_FECPLLCAL_3,
    STATE_LINK_CONFIG_4,
    STATE_LINK_TPS1TPN_5,
    STATE_LINK_TPS2TPN_6,
    STATE_LINK_VIDPTN_7,
    STATE_LINK_SUCCESS_8,
    STATE_LINK_FAIL_9,
    STATE_LINK_PALYBACK_10,
}EnumDpTxLinkTrainingState;

extern u8 Tx_Buff[16];
extern u8 Rx_Buff[16];
extern DpTxAuX_S g_stAuxDpTx;

extern u32 Mod_DpTx_LinkBandWidthGet(void);
extern u8 Mod_DpTx_LaneGet(void);
extern void Mod_DpTxLink_SinkCapRead(void);
extern u8 Mod_DpTx_LinkTraining(void);
extern void Mod_DpTxLink_SinkEdidRead(u8 *pucEdidData);
extern void Mod_DpTxLink_DpcdRead(u8 addrhigh,u16 addr, u8 *buf, u8 len);
extern void Mod_DpTxLink_DpcdWrite(u8 addrhigh, u16 addr, u8 *buf, u8 len);
extern void Mod_DpTx_SendSwingAdjReq(void);
extern void Mod_DpTx_Automated_Test_Init(void);

#endif
#endif