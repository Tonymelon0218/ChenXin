//////////////////////////////////////
//Project:   LT2101
//Filename:  DrvTypec.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _DRVTYPECTX_H
#define _DRVTYPECTX_H

#include "LtType.h"

//#if TYPECTX_EN == ENABLED


#define     IN
#define     OUT
#define     INOUT

#define   nBusyCount				5
#define   nCapsCount				50
#define   nDiscoverIdentityCount	20
#define   nHardResetCount			2
#define   nMessageIDCount			7
#define   nRetryCount_PD20			3
#define   nRetryCount_PD30			2

#define   DRD 					    3
#define   DFP 					    2
#define   UFP 					    1

#define   DRP 					    3
#define   SOURCE				    2
#define   SINK	 					1

#define   Rp_SinkTxOK				3
#define   Rp_SinkTxNG				2
#define   Rp_Default				1
#define   Rp_Invalid				0

#define   UCC  					    0
#define   DCC 					    1

#define   PD20                      0x01
#define   PD30                      0x02
#define   PD31                      0x03

#define   PDREQ						0x00
#define   PDACK						0x40
#define   PDNACK					0x80
#define   PDBUSY					0xc0

#define   INITIATE_NONE             0x00
#define   INITIATE_READY            0x01
#define   INITIATE_GOING            0x02
#define   INITIATE_DONE             0x03


#define   AMS_NONE             0x00
#define   AMS_READY            0x01
#define   AMS_GOING            0x02
#define   AMS_GOEXP            0x03
#define   AMS_DONE             0x04


#define   FRSWAP_NULL               0x00
#define   FRSWAP_INITIATE           0x01
#define   FRSWAP_RECEIVED           0x02
#define   FRSWAP_ONGOING            0x03

#define   PDSCANEND                 0x00
#define   PDSCANSTART               0x01
#define   PDSCANGOING               0x02

#define   SOP 						0x01
#define   SOP1 						0x02
#define   SOP2						0x03
#define   HardRst					0x04

//Control Msg Type
#define   GoodCRC     		  		0x01
#define   GotoMin     		  		0x02
#define   Accept     		    	0x03
#define   Reject      		  		0x04
#define   Ping        		  		0x05
#define   PS_RDY      		  		0x06
#define   Get_Source_Cap   	 		0x07
#define   Get_Sink_Cap      		0x08
#define   DR_Swap           		0x09
#define   PR_Swap           		0x0A
#define   VCONN_Swap        		0x0B
#define   Wait              		0x0C
#define   Soft_Reset        		0x0D
#define	  Not_Support				0x10
#define	  Get_Source_Cap_Extended	0x11
#define	  Get_Status				0x12
#define	  FR_Swap					0x13
#define	  Get_PPS_Status		 	0x14
#define	  Get_Country_Codes	 		0x15

//New to PD3.1
#define	  Get_Sink_Cap_Extended		0x16
#define	  Get_Source_Info	 		0x17
#define	  Get_Revision	 			0x18

//Data Msg Type
#define   Source_Capabilities     	0x01
#define   Request     		        0x02
#define   BIST     		            0x03
#define   Sink_Capabilities      	0x04
#define   Battery_Status	      	0x05
#define   Alert				      	0x06
#define   Get_Country_Info	      	0x07
#define   Vendor_Defined        	0x0f

//New to PD3.1
#define   Enter_USB	      			0x08
#define   EPR_Request		      	0x09//tbd
#define   EPR_Mode	      			0x0A//tbd
#define   Source_Info	      		0x0B
#define   Revision	      			0x0C

//*****Extended Msg Type******//
#define   Source_Cap_Extended     	0x01
#define   Status    		        0x02
#define   Get_Battery_Cap	        0x03
#define   Get_Battery_Status      	0x04
#define   Battery_Capabilities     	0x05
#define   Get_Manufacturer_Info   	0x06
#define   Manufacturer_Info	      	0x07
#define   Security_Request        	0x08
#define   Security_Response        	0x09
#define   Firmware_Update_Request  	0x0a
#define   Firmware_Update_Response	0x0b
#define   PPS_Status	        	0x0c
#define   Country_Info	        	0x0d
#define   Country_Codes	        	0x0e

//New to PD3.1
#define   Sink_Capabilities_Extended 0x0F
#define   Extended_Control	        0x10
#define   EPR_Source_Capabilities	0x11
#define   EPR_Sink_Capabilities	    0x12
#define   Vendor_Defined_Extended	0x1e

//Extended_Control Message Type
#define	  EPR_Get_Source_Cap		0x01
#define   EPR_Get_Sink_Cap			0x02
#define   EPR_KeepAlive				0x03
#define   EPR_KeepAlive_Ack			0x04

//SVDM
#define   Discover_Identity     	0x01
#define   Discover_SVIDs     	    0x02
#define   Discover_Modes     		0x03
#define   Enter_Mode      	        0x04
#define   Exit_Mode      	        0x05
#define   Attention        	        0x06
#define   DP_Status_Update        	0x10 //16
#define   DP_Config              	0x11 //17
#define   DP_Status_Updata_ACK	    0x50 //17
#define   DP_Config_ACK  			0x51
#define   DP_Config_NACK   			0x91


#define   Ctrl_Msg					0x00
#define   Data_Msg					0x01
#define   Ext_Msg					0x02
#define   Vdm_Msg					0x03

#define   StrVdm					0x80
#define   UnStrVdm					0x00

#define   HARDRESET                 0x14
#define   CABLERESET                0x15

#define   FRSWAP_NULL               0x00
#define   FRSWAP_INITIATE           0x01
#define   FRSWAP_RECEIVED           0x02
#define   FRSWAP_ONGOING            0x03

#define   PDSCANEND                 0x00
#define   PDSCANSTART               0x01
#define   PDSCANGOING               0x02

extern void Drv_Cc1Sw_Ctrl(u8 b1IsEn);
extern void Drv_CC1Ra_Det(void);
//#endif

#endif
