//////////////////////////////////////
//Project:   LT2101
//Filename:  Print.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

#define MAX_NUMBER_BYTES 128

u8 code g_ucPrintLvl = INIT_PRINT_LVL;

//example
//    codea = 0x01;
//    codeb = 0x0002;
//    codec = 0x00000003;
//    printLT(PRINT_PRIO_HIG, "\n1");  
//    printLT(PRINT_PRIO_HIG, "\nh'u8 is 0x%02bx", codea);
//    printLT(PRINT_PRIO_HIG, "\nh'u16 is 0x%04x", codeb);
//    printLT(PRINT_PRIO_HIG, "\nh'u32 is 0x%08lx",codec);
//    printLT(PRINT_PRIO_HIG, "\nd'u8 is %bd", codea);
//    printLT(PRINT_PRIO_HIG, "\nd'u16 is %d", codeb);
//    printLT(PRINT_PRIO_HIG, "\nd'u32 is %ld", codec);


//===========================================
//func  :print func
//input :first, print level, all remaining is print context
//output:N/A
//return:void
//Info  :N/A
//===========================================
void printLT(u8 ucLvl, const char* fmt, ...)
{
    #if DEBUGGING == ENABLED
    va_list args;
    char i;
    char buf[MAX_NUMBER_BYTES];
    if(ucLvl <= g_ucPrintLvl)
    {
        va_start(args, fmt);
        vsprintf((char *)buf, fmt, args);
        va_end(args);
        for(i = 0; i< strlen((char *)buf); i++)
        {
            putchar(buf[i]);
        }
    }
    #endif
}

u8 g_ucLogLevel = LOG_DEBUG;
RDATA char *messageTypeStr[] = {"DEBUG","INFO","WARN", "ERROR","CRIT"};

void LTLog(u8 ucLvl, const char* fmt, ...)
{
    char buf[MAX_NUMBER_BYTES] = {0};
    va_list args;
    if (ucLvl > LOG_NOTRACE)
    {
        return;
    }
    
    if(ucLvl >= g_ucLogLevel)
    {
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        va_end(args);
        printf("\n[%-5s] %s", messageTypeStr[ucLvl], buf);
    }
}

//===========================================
//func  :set print level
//input :current print level
//output:N/A
//return:void
//Info  :N/A
//===========================================
//void Ocm_Print_LevelSet(IN u8 ucLvl)
//{
//   g_ucPrintLvl = ucLvl;
//}

//===========================================
//func  :acquire current print level
//input :N/A
//output:N/A
//return:current print level
//Info  :N/A
//===========================================
//u8 Ocm_Print_LevelGet(void)
//{
//   return g_ucPrintLvl;
//}