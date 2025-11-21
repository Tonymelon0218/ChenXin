//////////////////////////////////////
//Project:   LT2101
//Filename:  Gpio.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _GPIO_H
#define _GPIO_H

#include "LtType.h"

extern void Drv_IO_UartSet(void);
extern void Drv_IOSoftLevel_Set(IN u8 GpioN,IN u8 Softlevel);
extern void Drv_Gpio_OutSignalSet(IN u8 GpioN, IN u8 Function);
extern u8 Drv_GetIO_State(IN u8 ucGpioN);
extern void Drv_Gpio_ModeSet(IN u8 GpioN, IN u8 Rs_Os, IN u8 Vth);
#if ((TX_PORT_SIGN == MIPI_PORT) || (TX_PORT_SIGN == LVDS_PORT))
extern void Drv_GPIO19Vsync_Set(u8 IsEn);
#endif
#endif
