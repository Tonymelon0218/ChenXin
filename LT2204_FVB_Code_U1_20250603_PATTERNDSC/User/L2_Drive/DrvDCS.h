/******************************************************************************
*  Copyright (C), 2006-2022, Lontium Tech.
*  Project       : LT2102
*  File Name     : DrvDCS.h
*  Version       : V1.0
*  Author        : AndyWang
*  Created       : 2022/10/22
*  Description   : MIPI DSI LP Command
*  
*  History:
*  2022/10/22     AndyWang      Created File
******************************************************************************/

#ifndef __DRVDCS_H__
#define __DRVDCS_H__
#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD) || (CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))

extern void Drv_MipiTx_Dsidcs_Init();
extern void Drv_MipiTx_DcsPktWrite(u8 DCS_DI, u8 Len, u8* Ptr );
extern void Drv_MipiTx_Dsidcs_End();
#endif
#endif /* __DRVDCS_H__ */
