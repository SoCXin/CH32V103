#ifndef _zf_board_h
#define _zf_board_h

#include "common.h"
#include "stdio.h"
#include "ch32v10x.h"
#include "zf_uart.h"


#define PRINTF_ENABLE           1                   //printfʹ��

#define DEBUG_UART              UART_1              //DEBUG����
#define DEBUG_UART_BAUD         115200              //DEBUG���ڲ�����
#define DEBUG_UART_TX_PIN       UART1_TX_A9         //DEBUG����TX����
#define DEBUG_UART_RX_PIN       UART1_RX_A10        //DEBUG����RX����

void board_init(void);




#endif
