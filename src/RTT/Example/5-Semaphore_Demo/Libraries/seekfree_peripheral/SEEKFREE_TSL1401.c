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
                                                ģ��ܽ�                                     ��Ƭ���ܽ�
                        CCD_AO          �鿴SEEKFREE_TSL1401.h�ļ��е�AD_CHANNEL �궨��
                        CCD_CLK         �鿴SEEKFREE_TSL1401.h�ļ��е�CCD_CLK_PIN�궨��
                        CCD_SI          �鿴SEEKFREE_TSL1401.h�ļ��е�CCD_SI_PIN �궨��
                    ------------------------------------
 ********************************************************************************************************************/




#include "zf_adc.h"
#include "zf_pit.h"
#include "SEEKFREE_TSL1401.h"
uint8 tsl1401_finish_flag;
uint16 ccd_data[128];                           //CCD����

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401����CCD��ʼ��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void ccd_init(void)     
{       
    gpio_init(CCD_CLK_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(CCD_SI_PIN, GPO, 1, GPIO_PIN_CONFIG);
    adc_init(AD_CHANNEL);
    timer_pit_interrupt_ms(PIT_TIMER_CH, EXPOSURE_TIME);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401����CCDͼ��������λ���鿴ͼ��
//  @param      uart_n          ���ں�
//  @param      uart_n          ����CCD����ָ��
//  @return     void
//  @since      v1.0
//  Sample usage:               ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
void ccd_send_data(UARTN_enum uart_n ,uint16 *dat)
{
   uint8 i = 0;
   uart_putchar(uart_n, 0x00); 
   uart_putchar(uart_n, 0xff);
   uart_putchar(uart_n, 0x01);
   uart_putchar(uart_n, 0x00);
   
    for(i=0; i<128; i++)
    {
        uart_putchar(uart_n, dat[i]>>8);   //���͸�8λ
        uart_putchar(uart_n, dat[i]&0XFF); //���͵�8λ
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401����CCD���ݲɼ�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:               ��isr.c�����ȴ�����Ӧ���жϺ�����Ȼ����øú���(֮�����������жϱ�־λ)
//-------------------------------------------------------------------------------------------------------------------
void ccd_collect(void)
{
    uint8 i = 0;

    CCD_CLK(1);
    CCD_SI(0);
    CCD_CLK(0);
    CCD_SI(1);
    CCD_CLK(1);
    CCD_SI(0);

    for(i=0;i<128;i++)
    {
        CCD_CLK(0);
        //�������ͬʱ�ɼ�����CCD����
        ccd_data[i] = adc_convert(AD_CHANNEL, AD_RESOLUTION);
        //ccd_data_two[i] = adc_convert(AD_CHANNEL, AD_RESOLUTION);
        CCD_CLK(1);
    }

    //�ɼ���ɱ�־λ��1
    tsl1401_finish_flag = 1;

}
