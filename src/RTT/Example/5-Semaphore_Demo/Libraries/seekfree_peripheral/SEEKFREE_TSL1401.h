/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            main
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MDK FOR C51 V9.60
 * @Target core     STC8A8K64S4
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-4-14
 * @note
                    TSL1401���߶��壺
                    ------------------------------------
                        ģ��ܽ�        ��Ƭ���ܽ�
                        CCD_AO          �鿴SEEKFREE_TSL1401.h�ļ��е�AD_CHANNEL �궨��
                        CCD_CLK         �鿴SEEKFREE_TSL1401.h�ļ��е�CCD_CLK_PIN�궨��
                        CCD_SI          �鿴SEEKFREE_TSL1401.h�ļ��е�CCD_SI_PIN �궨��
                    ------------------------------------
 ********************************************************************************************************************/


#ifndef _TSL1401_c
#define _TSL1401_c
#include "common.h"
#include "zf_uart.h"
#include "zf_gpio.h"


#define CCD_CLK_PIN     C2                  //CCD��CLK���Ŷ���
#define CCD_SI_PIN      C3                  //CCD��SI ���Ŷ���
#define AD_CHANNEL      ADC_IN10_C0         //����AD�ɼ�ͨ�� ADC_P13
#define EXPOSURE_TIME   10                  //����CCD�ع�ʱ�� ��λMS
#define PIT_TIMER_CH    TIMER_2             //ʹ�������ж�PCA_0
#define AD_RESOLUTION   ADC_12BIT           //ADת��12λ

#define CCD_CLK(x)     ((x == 0)? (GPIO_PIN_RESET(CCD_CLK_PIN))  :(GPIO_PIN_SET(CCD_CLK_PIN)))
#define CCD_SI(x)      ((x == 0)? (GPIO_PIN_RESET(CCD_SI_PIN))  :(GPIO_PIN_SET(CCD_SI_PIN)))


extern uint16 ccd_data[128];                   //CCD����
extern uint8 tsl1401_finish_flag;

void ccd_init(void);
void ccd_collect(void);
void ccd_send_data(UARTN_enum uart_n ,uint16 *dat);

#endif
