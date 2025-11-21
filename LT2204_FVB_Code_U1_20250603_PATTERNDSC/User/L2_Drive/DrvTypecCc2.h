//////////////////////////////////////
//Project:   LT2101
//Filename:  DrvTypec.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DRVTYPECRXX_H
#define _DRVTYPECRXX_H

#include "LtType.h"

#if ((CHIP_SEL == LT8711GXE)||(CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP)||(CHIP_SEL == LT6711GXE))
#if ((TYPECRX_EN == ENABLED)||(TYPECTX_EN == ENABLED))

extern u8 Drv_CC2On_Det(IN u8 ucPow_Role);
extern void DRV_CCPHY_DigSet(void);
extern void Drv_CC1Flip_Scan(StructCcStatus *pCcState);
extern void DRV_CCRterm_Cali(u8 UCC_DCC);
extern void DRV_CCRXRate_Set(u8 UCC_DCC);	
extern void DRV_CCTXRate_Set(u8 UCC_DCC);	
extern void DRV_CCInt_Init(u8 UCC_DCC);	
extern void DRV_CCDebounce_Set(u8 UCC_DCC);	
extern void DRV_CCRxPHY_Set(u8 UCC_DCC);	
extern void DRV_CcOrder_Set(u8 UCC_DCC,u8 OrderType);
extern void DRV_RpCur_Sel(IN u8 CC_Port,IN u8 Rp_Cur);
extern void DRV_PowerRole_Set(IN u8 CC_Port,IN u8 ucPow_Role);
extern u8 Drv_CC1RpOn_Scan(void);
extern u8 Drv_CC1RdOn_Scan(void);
extern u8 Drv_Cc2VbusOff_Det(void);
extern void DRV_CC_LogicRst(u8 UCC_DCC);
extern void DRV_FrTrig_Send(void);
extern void Drv_CC1USB3Mux_Ctrl(StructCcStatus *pstCcState);
extern void Drv_CC1Flip_Judge(StructCcStatus *pstCcState);
extern void Drv_Cc2VbusDet_IntClr(u8 b1IsClr);
extern void Drv_Cc2VbusDet_IntSet(u8 b1IsSet);
#endif
#endif

#endif
