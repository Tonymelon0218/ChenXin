//////////////////////////////////////
//Project:   LT2204
//Filename:  ModMipiDscEncTx.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _MOD_MIPIDSCENCTX_H
#define _MOD_MIPIDSCENCTX_H

#include "include.h"

#if TX_PORT_SIGN == MIPI_PORT 
#if MIPITX_DSC == ENABLED

extern void Mod_MipiTxDscEnc_Config();

typedef struct DSCConfig
{
    u8 ucOutBpp;
    u8 ucDscNumber;
    u8 ucSliceNum;
    u8 ucColorSpace;
    u8 ucColorDepth;
    u8 ucCompressRatio;
    u8 ucExtraHact;
    u8 ucGroupUnit;
    u16 usSliceGroup;
    u16 usSliceHeight;
    u16 usSliceWidth;
    u16 usChunkSize;
    u16 usExtraBits;
    u8 ucSecLineOffset;
    
}DSCConfig_Stru;

extern DSCConfig_Stru g_stMipiTxDscEncConfig;

#endif
#endif

#endif