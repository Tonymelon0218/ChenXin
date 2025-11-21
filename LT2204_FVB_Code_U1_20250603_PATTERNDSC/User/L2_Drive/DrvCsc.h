//////////////////////////////////////
//Project:   LT2101
//Filename:  Csc.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CSC_H
#define _CSC_H

#include "LtType.h"

#if CSC_SUPPORT == ENABLED

typedef enum
{
    NO_CSC_FUNC_0 = 0,
    RGB_TO_Y444_1,
    RGB_TO_Y422_2,
    RGB_TO_Y420_3,
    Y444_TO_RGB_4,
    Y444_TO_Y422_5,
    Y444_TO_Y420_6,
    Y422_TO_RGB_7,
    Y422_TO_Y444_8,
    Y422_TO_Y420_9,
    Y420_TO_RGB_10,
    Y420_TO_Y444_11,
    Y420_TO_Y422_12,
}EnumCscType;

extern void Drv_CscRx_Init(void);
extern void Drv_CscRx_Set(u8 CscType);

#if ((RX_PORT_SIGN == HDMI_PORT) &&(TX_PORT_SIGN == DP_PORT))
extern void Drv_CscRx_RxtoTx(IN StructHdmiRx *pstRxInfo,OUT DpTx_S *pstDpTx);
#endif

#if ((RX_PORT_SIGN == DP_PORT) &&(TX_PORT_SIGN == DP_PORT))
extern void Drv_CscRx_RxtoTx(IN StructDpRx *pstRxInfo,OUT DpTx_S *pstDpTx);
#endif

#if ((RX_PORT_SIGN == HDMI_PORT) &&(TX_PORT_SIGN == HDMI_PORT))
extern void Drv_CscRx_RxtoTx(IN StructHdmiRx *pstRxInfo,OUT HdmiTx_S *pstHdmiTx);

#endif

#if ((RX_PORT_SIGN == DP_PORT) &&(TX_PORT_SIGN == HDMI_PORT))
extern void Drv_CscRx_RxtoTx(IN StructDpRx *pstRxInfo,OUT HdmiTx_S *pstHdmiTx) ;
#endif

#if ((RX_PORT_SIGN == DP_PORT) &&(TX_PORT_SIGN == MIPI_PORT))
extern void Drv_CscRx_RxtoTx(StructDpRx *pstRxInfo);
#endif

#if ((RX_PORT_SIGN == DP_PORT) &&(TX_PORT_SIGN == LVDS_PORT))
extern void Drv_CscRx_RxtoTx(StructDpRx *pstRxInfo);
#endif

#if ((RX_PORT_SIGN == HDMI_PORT) &&(TX_PORT_SIGN == MIPI_PORT))
extern void Drv_CscRx_RxtoTx(StructHdmiRx *pstRxInfo);
#endif

#if ((RX_PORT_SIGN == HDMI_PORT) &&(TX_PORT_SIGN == LVDS_PORT))
extern void Drv_CscRx_RxtoTx(StructHdmiRx *pstRxInfo);
#endif

#endif

#endif
