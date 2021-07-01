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
#ifndef _zf_spi_h
#define _zf_spi_h

#include "common.h"


//��ö�ٶ��岻�����û��޸�
typedef enum //ö�ٴ��ں�
{
    SPI_1 = 0x00,
    SPI_2 = 0x01
}SPIN_enum;


typedef enum //ö�ٴ��ں�
{
    //----------SPI1----------
    SPI1_SCK_PA5 = 0x00,
    SPI1_MOSI_PA7,
    SPI1_MISO_PA6,

    //��ӳ��
    SPI1_SCK_PB3 = 0x10,
    SPI1_MOSI_PB5,
    SPI1_MISO_PB4,

    //----------SPI2----------
    SPI2_SCK_PB13 = 0x20,
    SPI2_MOSI_PB15,
    SPI2_MISO_PB14,

    SPI_MISO_NULL
}SPI_PIN_enum;



typedef enum //ö�ٴ��ں�
{
    FPCLK_DIV_2 = 0x00,
    FPCLK_DIV_4,
    FPCLK_DIV_16,
    FPCLK_DIV_32,
    FPCLK_DIV_64,
    FPCLK_DIV_128,
    FPCLK_DIV_256,
}SPI_SPEED_enum;

void spi_init(
        SPIN_enum spi_n,
        SPI_PIN_enum sck_pin,
        SPI_PIN_enum mosi_pin,
        SPI_PIN_enum miso_pin,
        PIN_enum cs_pin,
        uint8 mode,
        SPI_SPEED_enum BaudRatePrescaler);
void spi_mosi(SPIN_enum spi_n, uint8 *modata, uint8 *midata, uint32 len);




#endif
