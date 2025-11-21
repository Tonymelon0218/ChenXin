//////////////////////////////////////
// Project:   LT2101
// Filename:  main.c
// Version:   V1.0
// Copyright: Lontium
//////////////////////////////////////
#include "Include.h"
//===========================================
// func  :main
// input :N/A
// output:N/A
// return:void
// Info  :N/A
//===========================================
void App_ChipFw_Read(void)
{
    BKE0_80_REG = CBYTE[0x01000]; // customer ID
    BKE0_81_REG = CBYTE[0x01001]; // Major Version
    BKE0_82_REG = CBYTE[0x01002]; // Middle Version
    BKE0_83_REG = CBYTE[0x01003]; // Minor Version
}

void main(void)
{
    Drv_System_XtalSet(); // xtal set
    Ocm_Timer_Init();
    Drv_IO_UartSet();
    App_ChipFw_Read();
#if CHIP_SEL == LT6711GXE
    LT6711GXE_PowerOnInit();
    printLT(PRINT_PRIO_HIG, "\nLT6711GXE");
#endif

#if CHIP_SEL == LT8711GXE
    LT8711GXE_PowerOnInit();
    printLT(PRINT_PRIO_HIG, "\nLT8711GXE");
#endif

#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD))
    LT6911GXE_PowerOnInit();
    printLT(PRINT_PRIO_HIG, "\nLT6911GXE");
#endif

#if ((CHIP_SEL == LT7911UXE_DP) || (CHIP_SEL == LT6911GXD_DP))
    LT7911GXE_PowerOnInit();
    printLT(PRINT_PRIO_HIG, "\nChipPowerOn");
#endif

#if CHIP_SEL == LT86121GXE
    LT86121GXE_PowerOnInit();
    printLT(PRINT_PRIO_HIG, "\nLT86121GXE");
#endif

    printLT(PRINT_PRIO_HIG, "\nFW_VER = 0x%02bx,0x%02bx,0x%02bx", BKE0_81_REG, BKE0_82_REG, BKE0_83_REG);

#if BB_EN == ENABLED
    Drv_BB_Init(ENABLED);
#endif

    while (1)
    {
#if HDMITX_VID_PATTERN_SEL != NO_PATTERN
        Mod_HdmiTx_Pattern();
#endif

#if DPTX_VID_PATTERN_SEL != NO_PATTERN
        Mod_DpTx_Pattern();
#endif

#if LVDXTX_VID_PATTERN_MODE != NO_PATTERN
        Mod_LvdsTx_Pattern();
#endif

#if MIPITX_VID_PATTERN_MODE != NO_PATTERN
        Mod_MIPITx_Pattern();
#endif

#if CHIP_SEL == LT6711GXE
        LT6711GXE_Main_Scan();
#endif

#if CHIP_SEL == LT8711GXE
        LT8711GXE_Main_Scan();
#endif

#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD))
        LT6911GXE_Main_Scan();
#endif

#if ((CHIP_SEL == LT7911UXE_DP) || (CHIP_SEL == LT6911GXD_DP))
        LT7911GXE_Main_Scan();
#endif

#if CHIP_SEL == LT86121GXE
        LT86121GXE_Main_Scan();
#endif
    }
}
