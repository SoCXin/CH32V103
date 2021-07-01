/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_spi
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

#include "zf_gpio.h"
#include "zf_spi.h"
#include "stddef.h"



const uint32 SPIN[2] = {SPI1_BASE, SPI2_BASE};

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI���ų�ʼ��
//  @param      sck_pin     SCK����(��ѡ��Χ��zf_spi.h��SPI_PIN_enumö��ֵȷ��)
//  @param      mosi_pin    MOSI����(��ѡ��Χ��zf_spi.h��SPI_PIN_enumö��ֵȷ��)
//  @param      miso_pin    MISO����(��ѡ��Χ��zf_spi.h��SPI_PIN_enumö��ֵȷ��)
//  @param      cs_pin      Ƭѡ����(��ѡ��Χ��common.h��PIN_enumö��ֵȷ��)
//  @return     void
//  Sample usage:           �ڲ�ʹ��  �û��������
//-------------------------------------------------------------------------------------------------------------------
void spi_gpio_init(SPI_PIN_enum sck_pin, SPI_PIN_enum mosi_pin, SPI_PIN_enum miso_pin, PIN_enum cs_pin)
{
    if(SPI1_SCK_PA5 == sck_pin) gpio_init(A5, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else if(SPI1_SCK_PB3 == sck_pin) gpio_init(B3, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else if(SPI2_SCK_PB13 == sck_pin) gpio_init(B13, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else assert(0);         //�޴˲����������

    if(SPI1_MOSI_PA7 == mosi_pin) gpio_init(A7, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else if(SPI1_MOSI_PB5 == mosi_pin) gpio_init(B5, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else if(SPI2_MOSI_PB15 == mosi_pin) gpio_init(B15, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else assert(0);         //�޴˲����������

    if(SPI1_MISO_PA6 == miso_pin) gpio_init(A6, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else if(SPI1_MISO_PB4 == miso_pin) gpio_init(B4, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else if(SPI2_MISO_PB14 == miso_pin) gpio_init(B14, GPO, 1, SPEED_50MHZ|OUT_AF_PP);
    else if(SPI_MISO_NULL == miso_pin)  miso_pin = SPI_MISO_NULL;
    else  assert(0);         //�޴˲����������


    gpio_init(cs_pin, GPO, 1, SPEED_50MHZ|OUT_PP);

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI��ʼ��
//  @param      spi_n               ѡ��SPIģ��   (SPI_1-SPI_2)
//  @param      sck_pin             SCK����(��ѡ��Χ��zf_spi.h��SPI_PIN_enumö��ֵȷ��)
//  @param      mosi_pin            MOSI����(��ѡ��Χ��zf_spi.h��SPI_PIN_enumö��ֵȷ��)
//  @param      miso_pin            MISO����(��ѡ��Χ��zf_spi.h��SPI_PIN_enumö��ֵȷ��)
//  @param      cs_pin              Ƭѡ����(��ѡ��Χ��common.h��PIN_enumö��ֵȷ��) ʹ�����CS����
//  @param      mode                SPIģʽ 0��CPOL=0 CPHA=0    1��CPOL=0 CPHA=1   2��CPOL=1 CPHA=0   3��CPOL=1 CPHA=1 //����ϸ�ڿ����аٶ�
//  @param      BaudRatePrescaler   SPI����������Ϊϵͳʱ�ӵĶ��ٷ�Ƶ
//  @return     void
//  Sample usage:               spi_init(SPI_1, SPI1_SCK_PA5, SPI1_MOSI_PA7, SPI1_MISO_PA6, A0, 0, FPCLK_DIV_2);//Ӳ��SPI��ʼ��  ģʽ0 ������Ϊϵͳʱ��Ƶ��/2
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ50000
//-------------------------------------------------------------------------------------------------------------------
void spi_init(
        SPIN_enum spi_n,
        SPI_PIN_enum sck_pin,
        SPI_PIN_enum mosi_pin,
        SPI_PIN_enum miso_pin,
        PIN_enum cs_pin,
        uint8 mode,
        SPI_SPEED_enum BaudRatePrescaler)
{

    SPI_InitTypeDef  SPI_InitStructure;

    if(SPI_1 == spi_n)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO, ENABLE);                //SPI1ʱ��ʹ��
    }
    else if(SPI_2 == spi_n)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB2Periph_AFIO, ENABLE);                //SPI2ʱ��ʹ��
    }

    spi_gpio_init(sck_pin, mosi_pin, miso_pin, cs_pin);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      //SPI����Ϊ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                           //����SPI����ģʽ:����Ϊ��SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ

    switch(mode)
    {
        case 0:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                      //����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                    //����ͬ��ʱ�ӵĵ�һ�������أ��������½������ݱ�����
        }break;
        case 1:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                      //����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                    //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
        }break;
        case 2:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                     //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                    //����ͬ��ʱ�ӵĵ�һ�������أ��������½������ݱ�����
        }break;
        case 3:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                     //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                    //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
        }break;
    }

    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               //����ģʽ��ʹ���������NSS����
    SPI_InitStructure.SPI_BaudRatePrescaler = BaudRatePrescaler << 3;       //���岨����Ԥ��Ƶ��ֵ
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;                                //CRCֵ����Ķ���ʽ
    SPI_Init((SPI_TypeDef *)(SPIN[spi_n]), &SPI_InitStructure);             //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���

    if(SPI1_SCK_PB3 == sck_pin) GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);

    SPI_Cmd(((SPI_TypeDef *)(SPIN[spi_n])), ENABLE);                         //ʹ��SPI����

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI���ͽ��պ���
//  @param      spi_n           ѡ��SPIģ��   (SPI_1-SPI_2)
//  @param      modata          ���͵����ݻ�������ַ
//  @param      midata          ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
//  @param      len             ���͵��ֽ���
//  @return     void
//  @since      v2.0
//  Sample usage:               spi_mosi(SPI_1, buf, buf, 1);    //����modata�����ݣ������յ�midata�����Ϊ1�ֽ�
//-------------------------------------------------------------------------------------------------------------------
void spi_mosi(SPIN_enum spi_n, uint8 *modata, uint8 *midata, uint32 len)
{
    while(len--)
    {
        while((((SPI_TypeDef *)(SPIN[spi_n]))->STATR & SPI_I2S_FLAG_TXE) == RESET);
        ((SPI_TypeDef *)(SPIN[spi_n]))->DATAR = *(modata++);
        if(NULL != midata)
        {
            while((((SPI_TypeDef *)(SPIN[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
            *(midata++) = ((SPI_TypeDef *)(SPIN[spi_n]))->DATAR;
        }
    }
}

