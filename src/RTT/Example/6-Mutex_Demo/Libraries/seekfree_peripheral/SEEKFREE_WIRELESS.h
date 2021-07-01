/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            ��ɿƼ�����ת����ģ��
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ3184284598)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        IAR 8.3 or MDK 5.28
 * @Taobao          https://seekfree.taobao.com/
 * @date            2019-03-27
 * @note
                    ���߶��壺
                    ------------------------------------
                        ����ת����       ��Ƭ��
                        RX              �鿴SEEKFREE_WIRELESS.h�ļ��е�WIRELESS_UART_TX�궨��
                        TX              �鿴SEEKFREE_WIRELESS.h�ļ��е�WIRELESS_UART_RX�궨��
                        RTS             �鿴SEEKFREE_WIRELESS.h�ļ��е�RTS_PIN�궨��
                        CMD             ���ջ�������
                    ------------------------------------
 ********************************************************************************************************************/

#ifndef _SEEKFREE_WIRELESS
#define _SEEKFREE_WIRELESS


#include "common.h"

#define DOUBLE_CORE 		 0   			//˫������Ϊ1
                        					//��������Ϊ0

#if (DOUBLE_CORE == 0)
#define WIRELESS_UART        UART_3         //����ת����ģ�� ��ʹ�õ��Ĵ���
#define WIRELESS_UART_TX     UART3_TX_C10
#define WIRELESS_UART_RX     UART3_RX_C11

#elif (DOUBLE_CORE == 1)
#define WIRELESS_UART        UART_1         //����ת����ģ�� ��ʹ�õ��Ĵ���
#define WIRELESS_UART_TX     UART1_TX_A9
#define WIRELESS_UART_RX     UART1_RX_A10
#endif

#define WIRELESS_UART_BAUD   115200
#define RTS_PIN              C12             //��������λ����  ָʾ��ǰģ���Ƿ���Խ�������  0���Լ�������  1�����Լ�������

void    seekfree_wireless_init(void);
uint32  seekfree_wireless_send_buff(uint8 *buff, uint32 len);

#endif 
