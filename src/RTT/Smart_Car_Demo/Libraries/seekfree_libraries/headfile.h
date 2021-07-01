/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		headfile
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.26
 * @Target core		NXP RT1021DAG5A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-02-18
 ********************************************************************************************************************/
 
#ifndef _headfile_h
#define _headfile_h

#include "common.h"
#include <stdint.h>
#include "board.h"

//------CH32V103 SDKͷ�ļ�
#include "ch32v10x.h"
#include "ch32v10x_adc.h"
#include "ch32v10x_bkp.h"
#include "ch32v10x_crc.h"
#include "ch32v10x_dbgmcu.h"
#include "ch32v10x_dma.h"
#include "ch32v10x_exti.h"
#include "ch32v10x_flash.h"
#include "ch32v10x_gpio.h"
#include "ch32v10x_i2c.h"
#include "ch32v10x_iwdg.h"
#include "ch32v10x_pwr.h"
#include "ch32v10x_rcc.h"
#include "ch32v10x_rtc.h"
#include "ch32v10x_spi.h"
#include "ch32v10x_tim.h"
#include "ch32v10x_usart.h"
#include "ch32v10x_wwdg.h"
#include "ch32v10x_usb.h"
#include "ch32v10x_usb_host.h"
#include "ch32v10x_misc.h"


//------��ɿƼ���Ƭ����������ͷ�ļ�
#include "zf_adc.h"
#include "zf_camera.h"
#include "zf_flash.h"
#include "zf_gpio.h"
#include "zf_nvic.h"
#include "zf_pwm.h"
#include "zf_spi.h"
#include "zf_systick.h"
#include "zf_qtimer.h"
#include "zf_uart.h"
#include "zf_pit.h"

//------RTTͷ�ļ�
#include "rtthread.h"

//------��ɿƼ���Ʒ����ͷ�ļ�
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_PRINTF.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_UART_7725.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_TSL1401.h"
#include "SEEKFREE_ABSOLUTE_ENCODER.h"

#endif
