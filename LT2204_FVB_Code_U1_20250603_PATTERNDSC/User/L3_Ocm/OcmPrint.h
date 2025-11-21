//////////////////////////////////////
//Project:   LT2101
//Filename:  Printf.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _PRINT_H
#define _PRINT_H
#include "LtType.h"

#define DEBUGGING       ENABLED
#define INIT_PRINT_LVL  PRINT_PRIO_TEST

extern u8 Ocm_Print_LevelGet(void);
extern void Ocm_Print_LevelSet(IN u8 ucLvl);
extern void printLT(u8 ucLvl, const char* fmt, ...);
extern void LTLog(u8 ucLvl, const char* fmt, ...);

#endif
