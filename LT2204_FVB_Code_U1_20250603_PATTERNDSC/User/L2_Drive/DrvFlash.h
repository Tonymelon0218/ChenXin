#ifndef _DRVFLASH_H
#define _DRVFLASH_H

#if ((CHIP_SEL == LT6911GXD_HD) || (CHIP_SEL == LT7911UXE_HD) || (CHIP_SEL == LT7911UXE_DP)||(CHIP_SEL == LT6911GXD_DP))

void Drv_Sector_Erease(u32 Add);
void Drv_Flash_Wr(u32 Add,u8 *buff,u16 length);
void Drv_Flash_Rd(u32 Add,u8 *buff,u16 length);

typedef union TUN32
{
	u32 ulData;
	u8  ucBuff[4]; 
}UN32;

#endif




#endif