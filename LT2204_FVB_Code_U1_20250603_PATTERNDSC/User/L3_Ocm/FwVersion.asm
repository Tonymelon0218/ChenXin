CSEG AT 0x1000		//
/*
版本号说明
版本号的基地址：bin文件的0x002000h
FW主版本：			CFG_BYTE_12:  0x0200B=0x25	//跟随工程文件
FW子版本：			CFG_BYTE_13:  0x0200C=0x34	//跟随工程文件
FW编译日期年：		CFG_BYTE_14:  0x0200D=年	//编译的年低2位，例如2023就填0x23
FW编译日期月：		CFG_BYTE_15:  0x0200E=月	//编译的月，例如2月就填0x02
FW编译日期日：		CFG_BYTE_16:  0x0200F=日	//编译的日，例如3月就填0x03
FW编译对应日期计数：CFG_BYTE_17:  0x02010=日	//编译当天的版本计数，例如当天的第一个版本可以填0x01

累计计数：这个主要是针对某个客户开始发布版本累计计数，三字节表示的6位十进制数，为0代表未正式发布的版本，正式版本后每发布一个版本都要加1
计数器高位：
计数器中位：
计数器低位：

如下为固件将版本号写入到芯片内部的寄存器：
BKD2_0C_REG(0xD20C) = CBYTE[0x02002];	//FW主版本
BKD2_0D_REG(0xD20D) = CBYTE[0x02003];	//FW子版本
BKD2_0E_REG(0xD20E) = CBYTE[0x02004];	//FW编译日期年
BKD2_0F_REG(0xD20F) = CBYTE[0x02005];	//FW编译日期月
BKD2_10_REG(0xD210) = CBYTE[0x02006];	//FW编译日期日
BKD2_11_REG(0xD211) = CBYTE[0x02007];	//FW编译对应日期计数
	
*/

/*
//寄存器需要获取的版本信息
BKD2_0C_REG = CBYTE[0x02002];//FW主版本
BKD2_0D_REG = CBYTE[0x02003];//FW子版本
BKD2_0E_REG = CBYTE[0x02004];//FW编译日期年
BKD2_0F_REG = CBYTE[0x02005];//FW编译日期月
BKD2_10_REG = CBYTE[0x02006];//FW编译日期日
BKD2_11_REG = CBYTE[0x02007];//FW编译对应日期计数
*/

/*
如下会占用FW空间
*/
/*
CFG_BYTE_00:   DB  0x19		//芯片chip ID高八位	
CFG_BYTE_01:   DB  0x01		//芯片chip ID低八位	
CFG_BYTE_02:   DB  0x03		//芯片ECO版本，例如U3配置为0x03
	
CFG_BYTE_03:   DB  0x34		//FW主版本	
CFG_BYTE_04:   DB  0x23		//FW子版本	
CFG_BYTE_05:   DB  0x02		//FW编译日期年
CFG_BYTE_06:   DB  0x21		//FW编译日期月
CFG_BYTE_07:   DB  0x01		//FW编译日期日
CFG_BYTE_08:   DB  0x00		//FW编译对应日期计数
	
CFG_BYTE_09:   DB  0x00
CFG_BYTE_0A:   DB  0x00		
CFG_BYTE_0B:   DB  0x00		//发布版本的累计计数,0x000000代表未发布	
	
CFG_BYTE_0C:   DB  'L'		//芯片完整型号，共计8个byte，不足的用-代替
CFG_BYTE_0D:   DB  'T'
CFG_BYTE_0E:   DB  '8'
CFG_BYTE_0F:   DB  '6'
CFG_BYTE_10:   DB  '6'
CFG_BYTE_11:   DB  '8'
CFG_BYTE_12:   DB  'S'
CFG_BYTE_13:   DB  'X'
CFG_BYTE_14:   DB  '-'
CFG_BYTE_15:   DB  '-'		
CFG_BYTE_16:   DB  '-'	
CFG_BYTE_17:   DB  '-'
	
CFG_BYTE_18:   DB  '*'		//以下字节保留，未使用,用户自定义标识字段可以占用这些字节		
CFG_BYTE_19:   DB  '*'
CFG_BYTE_1A:   DB  '*'
CFG_BYTE_1B:   DB  '*'
CFG_BYTE_1C:   DB  '*'
CFG_BYTE_1D:   DB  '*'
CFG_BYTE_1E:   DB  '*'
CFG_BYTE_1F:   DB  '*'
*/
CFG_BYTE_00:   DB  0x25		//客户ID
	
CFG_BYTE_01:   DB  0x11		//FW主版本	
CFG_BYTE_02:   DB  0x11		//FW中版本
CFG_BYTE_03:   DB  0x03		//FW小版本

CFG_BYTE_04:   DB  0xff		//FW编译日期年
CFG_BYTE_05:   DB  0xff		//FW编译日期月
CFG_BYTE_06:   DB  0xff		//FW编译日期日
	
CFG_BYTE_07:   DB  0xff		//FW编译日期年
CFG_BYTE_08:   DB  0xff		//FW编译日期月
CFG_BYTE_09:   DB  0xff		//FW编译日期日
	
CFG_BYTE_0A:   DB  0xff		//FW编译日期年
CFG_BYTE_0B:   DB  0xff		//FW编译日期月
CFG_BYTE_0C:   DB  0xff		//FW编译日期日
	
CFG_BYTE_0D:   DB  0xff		//FW编译日期年
CFG_BYTE_0E:   DB  0xff		//FW编译日期月
CFG_BYTE_0F:   DB  0xff		//FW编译日期日
END
	
