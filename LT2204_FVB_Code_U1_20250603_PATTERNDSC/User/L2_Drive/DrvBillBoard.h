//////////////////////////////////////
//Project:   LT2101
//Filename:  BillBoard.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _BILLBOARD_H
#define _BILLBOARD_H

#include "LtType.h"

#if BB_EN == ENABLED
//bb
#define NONE_ADDR  0xff
#define WRITE_FLASH_LEN     32 

typedef struct BB
{
    u8 b1Bb_Mode;
    u8 ucEraseIniCnt;
    u8 ucCrcIniCnt;
    u8 ucbUpdate_Cnt;
    u8 *pDataId;
    u8 ucPkt_Lenth;
    u8 szSend_Data[10];
    u8 szRevUpdateData[32];
    u32 ulAddrInit;
	u8 ucDevAddr;
	u8 UsbUpgradeFlow;
    u8 b1IsUpdateMode;
    u8 ucBBSumCnt;
} StructBB;

extern void Drv_BB_Interrupt(void);
extern void Drv_BB_Init(u8 b1Function);

#endif

#endif
