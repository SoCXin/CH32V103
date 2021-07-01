/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_uart
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
#ifndef _zf_uart_h
#define _zf_uart_h

#include "common.h"


//��ö�ٶ��岻�����û��޸�
//��ʼ����ʱ�򣬱���ʹ��ͬһ���������磬UART1_TX_A9��UART1_RX_A10��һ������
typedef enum //ö�ٴ�������
{

    UART1_TX_A9 = 0x00,     UART1_RX_A10,   //Ĭ������
    UART1_TX_B6,            UART1_RX_B7,    //��ӳ��

    UART2_TX_A2 = 0x10,     UART2_RX_A3,    //Ĭ������

    UART3_TX_B10 = 0x20,    UART3_RX_B11,   //Ĭ������
    UART3_TX_C10,           UART3_RX_C11    //������ӳ��

}UARTPIN_enum;


typedef enum //ö�ٴ�������
{
    UART_1 = 0,
    UART_2,
    UART_3
}UARTN_enum;



extern const uint32 UARTN[];



void uart_init(UARTN_enum uartn, uint32 baud, UARTPIN_enum tx_pin, UARTPIN_enum rx_pin);
void uart_putchar(UARTN_enum uartn, uint8 dat);
void uart_putbuff(UARTN_enum uartn, uint8 *buff, uint32 len);
void uart_putstr(UARTN_enum uartn, const uint8 *str);
void uart_getchar(UARTN_enum uartn, uint8 *dat);
uint8 uart_query(UARTN_enum uartn, uint8 *dat);
void uart_tx_irq(UARTN_enum uartn,uint8 status);
void uart_rx_irq(UARTN_enum uartn,uint8 status);
//void uart_set_handle(UARTN_enum uartn, lpuart_handle_t *handle, lpuart_transfer_callback_t callback, uint8 *tx_buff, uint32 tx_count, uint8 *rx_buff, uint32 rx_count);




#endif
