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

#include "ch32v10x_spi.h"
#include "ch32v10x_rcc.h"
#include "ch32v10x_gpio.h"
#include "ch32v10x_adc.h"

#include "zf_gpio.h"
#include "zf_adc.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC���ų�ʼ��
//  @param      ch          chͨ��(��ѡ��Χ��zf_adc.h��ADCCH_enumö��ֵȷ��)
//  @return     void
//  Sample usage:           �ڲ�ʹ��  �û��������
//-------------------------------------------------------------------------------------------------------------------
void adc_gpio_init(ADCCH_enum ch)
{
    if(ADC_IN0_A0 == ch)            gpio_init(A0, GPI, 0, IN_AIN);
    else if(ADC_IN1_A1 == ch)       gpio_init(A1, GPI, 0, IN_AIN);
    else if(ADC_IN2_A2 == ch)       gpio_init(A2, GPI, 0, IN_AIN);
    else if(ADC_IN3_A3 == ch)       gpio_init(A3, GPI, 0, IN_AIN);
    else if(ADC_IN4_A4 == ch)       gpio_init(A4, GPI, 0, IN_AIN);
    else if(ADC_IN5_A5 == ch)       gpio_init(A5, GPI, 0, IN_AIN);
    else if(ADC_IN6_A6 == ch)       gpio_init(A6, GPI, 0, IN_AIN);
    else if(ADC_IN7_A7 == ch)       gpio_init(A7, GPI, 0, IN_AIN);
    else if(ADC_IN8_B0 == ch)       gpio_init(B0, GPI, 0, IN_AIN);
    else if(ADC_IN9_B1 == ch)       gpio_init(B1, GPI, 0, IN_AIN);
    else if(ADC_IN10_C0 == ch)      gpio_init(C0, GPI, 0, IN_AIN);
    else if(ADC_IN11_C1 == ch)      gpio_init(C1, GPI, 0, IN_AIN);
    else if(ADC_IN12_C2 == ch)      gpio_init(C2, GPI, 0, IN_AIN);
    else if(ADC_IN13_C3 == ch)      gpio_init(C3, GPI, 0, IN_AIN);
    else if(ADC_IN14_C4 == ch)      gpio_init(C4, GPI, 0, IN_AIN);
    else if(ADC_IN15_C5 == ch)      gpio_init(C5, GPI, 0, IN_AIN);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC��ʼ��
//  @param      ch              ѡ��ADCͨ��
//  @return     void
//  Sample usage:               adc_init(ADC_IN0_A0);//��ʼ��A0����ΪADC����
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADCCH_enum ch)
{
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1 , ENABLE );   //ʹ��ADC1ͨ��ʱ��

    adc_gpio_init(ch);

    if(sys_clk > 84000000)  RCC_ADCCLKConfig(RCC_PCLK2_Div8);           //����ADC��Ƶ���ӣ�ADC������ʲ��ܳ���14M
    else RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADC1);                                                   //��λADC1

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  //ADC����ģʽ:ADC1�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       //ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 //ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             //˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC1, &ADC_InitStructure);                                 //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

    ADC_Cmd(ADC1, ENABLE);                                              //ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC1);                                         //ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1));                         //�ȴ���λУ׼����
    ADC_StartCalibration(ADC1);                                         //����ADУ׼
    while(ADC_GetCalibrationStatus(ADC1));                              //�ȴ�У׼����

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADCת��һ��
//  @param      ch              ѡ��ADCͨ��
//  @param      resolution      �ֱ���(8λ 10λ 12λ)
//  @return     void
//  Sample usage:               adc_convert(ADC_IN0_A0, ADC_8BIT);  //�ɼ�A0�˿ڷ���8λ�ֱ��ʵ�ADֵ
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert(ADCCH_enum ch, ADCRES_enum resolution)
{
    //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
    ADC_RegularChannelConfig(ADC1, (uint8)ch, 1, ADC_SampleTime_1Cycles5);  //ADC1,ADCͨ��,����ʱ��Ϊ1.5����
    ADC1->CTLR2 |= ((uint32_t)0x00500000);                                  //ʹ��ָ����ADC1�����ת����������
    while((ADC1->STATR & ADC_FLAG_EOC) == (uint8_t)RESET);                  //�ȴ�ת������
    return ((ADC1->RDATAR)>>resolution);                                    //�������һ��ADC1�������ת�����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADCת��N��
//  @param      ch              ѡ��ADCͨ��
//  @param      resolution      �ֱ���(8λ 10λ 12λ)
//  @param      count           ת������
//  @return     void
//  Sample usage:               adc_convert(ADC_IN0_A0, ADC_8BIT,5);  //�ɼ�A0�˿ڷ���8λ�ֱ��ʵ�ADֵ���ɼ����ȡƽ��ֵ
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter(ADCCH_enum ch, ADCRES_enum resolution, uint8 count)
{
    uint8 i;
    uint32 sum;

    assert(count);//���Դ�������Ϊ0

    sum = 0;
    for(i=0; i<count; i++)
    {
        sum += adc_convert(ch, resolution);
    }

    sum = sum/count;
    return sum;
}

