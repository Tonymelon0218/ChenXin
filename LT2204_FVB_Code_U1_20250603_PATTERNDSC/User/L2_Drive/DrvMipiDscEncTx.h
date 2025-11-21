//////////////////////////////////////
//Project:   LT2204
//Filename:  DrvMipi.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DRV_MIPIDSCENCTX_H
#define _DRV_MIPIDSCENCTX_H

#include "include.h"
#include "LtType.h"

#if TX_PORT_SIGN == MIPI_PORT
#if MIPITX_DSC == ENABLED

extern void Drv_MipiTxDscEnc_DataMux();
extern void Drv_MipiTxDscEnc_ClkMux();
extern void Drv_MipiTxDscEnc_ClkMuxForPattern();
extern void Drv_MipiTxDscEnc_RxParamSet(void);
extern void Drv_MipiTxDscEnc_ExtraHactSet();
extern void Drv_MipiTxDscEnc_TimingSet();
extern void Drv_MipiTxDscEnc_MuxWordDly(void);
extern void Drv_MipiTxDscEnc_PpsSet(u8 *ucuzEncPPS );
extern void Drv_MipiTxDscEnc_ColorSpaceSet();
extern void Drv_MipiTxDscEnc_PpsDynamicSet(void);
extern void Drv_MipiTxDscEnc_ParamSet(void);

extern void Drv_MipiTxDscEnc_Init(void);
extern void Drv_MipiTxDscEnc_InitForPattern(void);
extern void Drv_MipiTxDscEnc_PpsParaInit();
extern void Drv_MipiTxDscEnc_InfoGet(void);
extern StructTiming g_stMipiTxDscEncVideoTiming;
#endif
#endif

#endif