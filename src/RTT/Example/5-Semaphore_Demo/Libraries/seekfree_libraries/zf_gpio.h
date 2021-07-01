/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_gpio
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/

 
#ifndef _zf_gpio_h
#define _zf_gpio_h

#include "common.h"




#define GPIO_PIN_CONFIG (SPEED_50MHZ | OUT_PP)     //�궨��GPIO���ŵ�Ĭ�����ã����ڳ�ʼ��GPIOʱ������д�����������Ҫ���������������޸�
#define GPIO_INT_CONFIG (IN_PULLUP)                 //�궨��GPIO�ж����ŵ�Ĭ�����ã����ڳ�ʼ��GPIO�ж�ʱ������д�����������Ҫ���������������޸�


typedef enum    // ö�ٴ�����ʽ
{
    RISING = 0x08,
    FALLING = 0x0C,
    BOTH = 0x10
}TRIGGER_enum;

typedef enum    //ö��GPIO�ٶ�
{
    SPEED_10MHZ = 0x100,
    SPEED_2MHZ = 0x200,
    SPEED_50MHZ = 0x300
}GPIOSPEED_enum;


typedef enum    //ö��GPIO����
{
    IN_AIN = 0x00,              //ģ������ģʽ
    IN_FLOAT = 0x04,            //��������ģʽ
    IN_PULLDOWN = 0x28,         //��������
    IN_PULLUP = 0x48,           //��������

    OUT_PP = 0x10,              //ͨ���������ģʽ
    OUT_OD = 0x14,              //ͨ�ÿ�©���ģʽ
    OUT_AF_PP = 0x18,           //���ù����������ģʽ
    OUT_AF_OD = 0x1C,           //���ù��ܿ�©���ģʽ

}GPIOMODE_enum;


typedef enum    //ö�ٶ˿ڷ���
{
    GPI = 0, //����ܽ����뷽��
    GPO = 1, //����ܽ��������
}GPIODIR_enum;



extern const uint32 GPION[4];

//��ȡGPIO��ַ
//X = 0����A=�˿� , X = 1����B�˿� ,��������
//X = 0,Y = 0���� A0�˿ڵ�ַ �� X = 0,Y = 1���� A8�˿ڵ�ַ
#define GPIO_IDR_ADDR(X,Y)  (0x40010808 + X*0x400 + Y)

//GPIO��λ
#define GPIO_PIN_RESET(x)   ((GPIO_TypeDef *)(GPION[(uint8)((x & 0xE0) >> 5)]))->BCR  = (uint16)(1 << (x & 0x1F))
//GPIO��λ
#define GPIO_PIN_SET(x)     ((GPIO_TypeDef *)(GPION[(uint8)((x & 0xE0) >> 5)]))->BSHR  = (uint16)(1 << (x & 0x1F))
//�жϱ�־λ���   
#define CLEAR_GPIO_FLAG(pin) GPIO_ClearPinsInterruptFlags(PORTPTR[pin>>5], 1<<(pin&0x1f));

void gpio_init(PIN_enum pin, GPIODIR_enum dir, uint8 dat, uint32 pinconf);
void gpio_set(PIN_enum pin, uint8 dat);
uint8 gpio_get(PIN_enum pin);
void gpio_toggle(PIN_enum pin);
void gpio_interrupt_init(PIN_enum pin, TRIGGER_enum trigger, uint32 pinconf);




#endif
