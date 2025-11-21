/******************************************************************************
 *  Copyright (C), 2006-2022, Lontium Tech.
 *  Project       : LT2102
 *  File Name     : DrvDCS.c
 *  Version       : V1.0
 *  Author        : AndyWang
 *  Created       : 2022/10/22
 *  Description   : MIPI DSI LP Command
 *
 *  History:
 *  2022/10/22     AndyWang      Created File
 ******************************************************************************/

#include "Include.h"

#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD) || (CHIP_SEL == LT7911UXE_DP) || (CHIP_SEL == LT6911GXD_DP))

#define LPK_DI 0x29
#define SPK_DI 0x15
#define LPT_DI 0x39
#define SPT_DI 0x15

code u8 Sleep_Out[] = {0x05, 0x11, 0x00};
code u8 Display_On[] = {0x05, 0x29, 0x00};
code u8 Sleep_In[] = {0x05, 0x10, 0x00};
code u8 Display_Off[] = {0x05, 0x28, 0x00};
code u8 Set_address_mode[] = {0x15, 0x36, 0xC6};
/** 
code u8 DCS_S1[] = {0x15, 0xB0, 0x00};
code u8 DCS_S2[] = {0x29, 0xB9, 0x15, 0x46, 0x01, 0xEA};
code u8 DCS_S3[] = {0x29, 0xEC, 0x05, 0xD8};
code u8 DCS_S4[] = {0x15, 0xD6, 0x00};
code u8 DCS_S5[] = {0x15, 0xB0, 0x03};
code u8 DCS_S6[] = {0x15, 0x35, 0x00};
code u8 DCS_S7[] = {0x15, 0x36, 0x40};
code u8 DCS_S8[] = {0x15, 0x26, 0x01};
code u8 DCS_S9[] = {0x15, 0x03, 0x01};
*/

// 2160x2160@120Hz
code u8 DCS_S1[] = {0x15, 0xB0, 0x00};
code u8 DCS_S2[] = {0x29, 0xB9, 0x0F, 0xE4, 0x01, 0x6F};
code u8 DCS_S3[] = {0x15, 0xD6, 0x00};
code u8 DCS_S4[] = {0x15, 0xB0, 0x03};
code u8 DCS_S5[] = {0x15, 0x35, 0x00};
code u8 DCS_S6[] = {0x15, 0x36, 0x00};


void Mod_DCS_Init(void)
{
    Drv_MipiTx_Dsidcs_Init();
    Ocm_Delay1ms(20);

    Drv_MipiTx_DcsPktWrite(DCS_S1[0], sizeof(DCS_S1) - 1, &DCS_S1[1]);
    Drv_MipiTx_DcsPktWrite(DCS_S2[0], sizeof(DCS_S2) - 1, &DCS_S2[1]);
    Drv_MipiTx_DcsPktWrite(DCS_S3[0], sizeof(DCS_S3) - 1, &DCS_S3[1]);
    Drv_MipiTx_DcsPktWrite(DCS_S4[0], sizeof(DCS_S4) - 1, &DCS_S4[1]);
    Drv_MipiTx_DcsPktWrite(DCS_S5[0], sizeof(DCS_S5) - 1, &DCS_S5[1]);
    Drv_MipiTx_DcsPktWrite(DCS_S6[0], sizeof(DCS_S6) - 1, &DCS_S6[1]);

    Ocm_Delay1ms(150);
    Drv_MipiTx_DcsPktWrite(Display_On[0], (sizeof(Display_On) - 1), &Display_On[1]);
    Ocm_Delay1ms(150);
    Drv_MipiTx_DcsPktWrite(Sleep_Out[0], (sizeof(Sleep_Out) - 1), &Sleep_Out[1]);
    Ocm_Delay1ms(200);

    Drv_MipiTx_Dsidcs_End();
    LTLog(LOG_INFO, "Mipi DCS END");
}

#endif