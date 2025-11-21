/******************************************************************************
  * @project: LT2204
  * @file: ChipDpMst.h
  * @author: wtt
  * @company: LONTIUM
  * @date: 2022.06.07
/******************************************************************************/
#ifndef _CHIPDPMST_H
#define _CHIPDPMST_H

#include "LtType.h"

#if RX_PORT_SIGN == DP_PORT

#if DPRX_MST_MODE_EN == ENABLED

#define MST_MSG_VERSION           0x00
#define MST_LINK_ADDR             0x01
#define MST_STATUS_NOTIFY         0x02
#define MST_ENUM_PATH_RESRC       0x10
#define MST_ALLOCATE_PAYLOAD      0x11
#define MST_QUERY_PAYLOAD         0x12
#define MST_RESRC_STATUS_NOTIFY   0x13
#define MST_CLR_PAYLOAD_ID_TAB    0x14
#define MST_REMOTE_DPCD_READ      0x20
#define MST_REMOTE_DPCD_WRITE     0x21
#define MST_REMOTE_I2C_READ       0x22
#define MST_REMOTE_I2C_WRITE      0x23
#define MST_POWER_UP_PHY          0x24
#define MST_POWER_DOWN_PHY        0x25
#define MST_SINK_EVENT_NOTIFY     0x30
#define MST_QUERY_STREAM_STATUS   0x38


typedef struct MST_RX
{
    bool payload_update;
    bool reply_done;
    bool calc_flag;
    bool payload_flag;
    bool payload_done_flag;
    bool payload_clear;
    bool reply_rdy;
    bool block_reply_done;
    bool pbn_update;
    bool request_flag;
    bool pbn_flag[4];
    u8 count1400;
    u8 count2c0;
    u8 port_num;
    u8 sink_cnt;
    u8 wr_lenth;//address offset lenth
    u8 total_wr_lenth;//total data lenth
    u8 request_lenth;//dpcd 1000 head+body
    u8 reply_addr; //reply address
    u8 reply_lenth;//reply lenth
    u8 reply_block_lenth;// actual reply one block lenth
    u8 reply_body_lenth;// expected reply one block body lenth
    u8 reply_data_lenth;//actual reply total data lenth
    u8 reply_total_lenth;//expected reply total data lenth
    u8 i2c_read_cnt;
    u8 payload_cnt;
    u16 delay_cnt;
    u8 linkwidth;
    u8 linkcount;
    u8 MsgRxData[16];
    u8 payload_table[3];
    u8 reply_buf[48];
    u8 reply_buf_last[48];
}MstRxStatus_S;

extern MstRxStatus_S g_stMstRxStatus ;
extern bool Mod_DpRxMst_PayloadUpdate(void);
extern bool Mod_DpRxMst_PayloadDone(void);
extern void Mod_Mst_MsgHandle(void);

#endif

#endif

#endif
