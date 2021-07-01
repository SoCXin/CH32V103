/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            ����ʽ������
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ3184284598)
 * @version         �鿴LPC546XX_config.h�ļ��ڰ汾�궨��
 * @Software        IAR 8.3 or MDK 5.24a
 * @Target core     LPC54606J512BD100
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-01-13
 * @note
                    ���߶��壺
                    ------------------------------------
                    ģ��ܽ�                ��Ƭ���ܽ�
                    SCK                 �鿴SEEKFREE_ABSOLUTE_ENCODER.H�ļ�ABS_ENCODER_SPI_SCK_PIN �궨��
                    MISO                �鿴SEEKFREE_ABSOLUTE_ENCODER.H�ļ�ABS_ENCODER_SPI_MISO_PIN�궨��
                    MOSI                �鿴SEEKFREE_ABSOLUTE_ENCODER.H�ļ�ABS_ENCODER_SPI_MOSI_PIN�궨��
                    CS                  �鿴SEEKFREE_ABSOLUTE_ENCODER.H�ļ�ABS_ENCODER_SPI_PCS_PIN  �궨��
                    ------------------------------------
 ********************************************************************************************************************/

#ifndef _SEEKFREE_ABSOLUTE_ENCODER_H
#define _SEEKFREE_ABSOLUTE_ENCODER_H


#include "headfile.h"



#define ABS_ENCODER_SPI_NUM         SPI_2
#define ABS_ENCODER_SPI_SCK_PIN     SPI2_SCK_PB13
#define ABS_ENCODER_SPI_MISO_PIN    SPI2_MISO_PB14
#define ABS_ENCODER_SPI_MOSI_PIN    SPI2_MOSI_PB15

#define ABS_ENCODER_SPI_PC1_PIN     C9
#define ABS_ENCODER_SPI_PC2_PIN     C8
#define ABS_ENCODER_SPI_PC3_PIN     B12
#define ABS_ENCODER_SPI_PC4_PIN     A8

#define ABS_ENCODER_SPI_CSN(x)      ((x == 0)? (GPIO_PIN_RESET(ABS_ENCODER_SPI_PCS_PIN))  :(GPIO_PIN_SET(ABS_ENCODER_SPI_PCS_PIN)))


//�Ƕȴ���������
#define ABS_ENCODER_SPI_W       0x80
#define ABS_ENCODER_SPI_R       0x40


#define ZERO_L_REG              0x00
#define ZERO_H_REG              0x01
#define DIR_REG                 0X09




void encoder_init_spi(PIN_enum cs_pin);
uint16 encoder_angle_spi(PIN_enum cs_pin);
int16 encoder1_speed_spi(PIN_enum cs_pin);
int16 encoder2_speed_spi(PIN_enum cs_pin);
int16 encoder3_speed_spi(PIN_enum cs_pin);
int16 encoder4_speed_spi(PIN_enum cs_pin);


#endif

