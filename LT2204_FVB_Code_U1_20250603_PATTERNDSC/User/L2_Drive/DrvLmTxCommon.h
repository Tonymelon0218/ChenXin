#ifndef _DRV_LMTX_COMMOM_H
#define _DRV_LMTX_COMMOM_H

#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD) || (CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))

typedef  enum
{
    HTOTAL_POS= 0,
    HACTIVE_POS,
    HFP_POS,
    HSW_POS,
    HBP_POS,
    VTOTAL_POS,
    VACTIVE_POS,
    VFP_POS,
    VSW_POS,
    VBP_POS,
    HSPOL_POS,
    VSPOL_POS,
}PosIndex;

typedef struct TIMING
{
		u32 PixClk;	
    u16 Htotal;
    u16 Hactive;
    u16 Hfp;
    u16 Hsw;
    u16 Hbp;
    u16 Vtotal;
    u16 Vactive;
    u16 Vfp;
    u16 Vsw;
    u16 Vbp;
    u8 Hspol;
    u8 Vspol;
}StructTiming;


extern void Drv_VideoCheckAll_Get(OUT StructTiming *video_time);
extern u32 Drv_VideoCheckSingle_Get(u8 para);
#endif

#endif

