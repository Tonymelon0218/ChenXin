//////////////////////////////////////
//Project:   LT2101
//Filename:  EqScan.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DPRX_EQ_SCAN_H
#define _DPRX_EQ_SCAN_H

#include "LtType.h"

#if RX_PORT_SIGN == DP_PORT
#if DPRX_EQ_SCAN_MODE == SW_SCANVALIDEQ_EXT
extern u8 code SzEq_Stg0[33];
extern u8 code SzEq_Stg1[33];
#else
extern u8 code SzEq_Stg0[16];
extern u8 code SzEq_Stg1[16];
#endif
extern void Mod_DpRx_SoftEqSet(void);
extern void Mod_DpRx_EqSet(void);
extern u8 Mod_DpRx_8b10bErrorChk(void);

#endif

#endif


