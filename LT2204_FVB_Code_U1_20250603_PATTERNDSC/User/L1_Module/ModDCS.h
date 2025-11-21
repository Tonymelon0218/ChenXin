/******************************************************************************
*  Copyright (C), 2006-2022, Lontium Tech.
*  Project       : LT2204
*  File Name     : ModDCS.h
*  Version       : V1.0
*  Author        : AndyWang
*  Created       : 2022/10/22
*  Description   : MIPI DSI LP Command
*  
*  History:
*  2022/10/22     AndyWang      Created File
******************************************************************************/

#ifndef __MODDCS_H__
#define __MODDCS_H__
#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD) || (CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))
extern void Mod_DCS_Init(void);
#endif
#endif /* __MODDCS_H__ */
