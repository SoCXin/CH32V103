/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_adc
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
#ifndef _zf_adc_h
#define _zf_adc_h

#include "common.h"

//CH32V103ֻ��һ��ADC�����Է�ʱ�����ںܶ��ͨ������


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
    ADC_IN0_A0 = 0,
    ADC_IN1_A1,
    ADC_IN2_A2,
    ADC_IN3_A3,
    ADC_IN4_A4,
    ADC_IN5_A5,
    ADC_IN6_A6,
    ADC_IN7_A7,
    ADC_IN8_B0,
    ADC_IN9_B1,
    ADC_IN10_C0,
    ADC_IN11_C1,
    ADC_IN12_C2,
    ADC_IN13_C3,
    ADC_IN14_C4,
    ADC_IN15_C5,
}ADCCH_enum;


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
    ADC_8BIT = 4,     //8λ�ֱ���
    ADC_10BIT = 2,    //10λ�ֱ���
    ADC_12BIT = 0,    //12λ�ֱ���

}ADCRES_enum;





void adc_init(ADCCH_enum ch);
uint16 adc_convert(ADCCH_enum ch, ADCRES_enum resolution);
uint16 adc_mean_filter(ADCCH_enum ch, ADCRES_enum resolution, uint8 count);

#endif
