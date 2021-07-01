/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_systick
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
#ifndef _zf_systick_h
#define _zf_systick_h

#include "common.h"



//------------------------------------���º궨������SYSTICK��ʱ------------------------------------
#define systick_delay_ms(time)      systick_delay2(time)                    //����SYSTICK��ʱʱ��  ��λms
#define systick_delay_us(time)      systick_delay(time)                     //����SYSTICK��ʱʱ��  ��λus

//------------------------------------���º궨�����ڻ�ȡ��ǰʱ��------------------------------------
#define systick_getval_ms()         systick_getval()/(sys_clk/8000)         //��ȡ��ǰ��ʱʱ��  ��λms
#define systick_getval_us()         systick_getval()/(sys_clk/8000000)      //��ȡ��ǰ��ʱʱ��  ��λus
#define systick_getval_ns()         systick_getval()/(sys_clk/8000000000)   //��ȡ��ǰ��ʱʱ��  ��λns


void systick_delay(uint16 time);
void systick_delay2(uint64 time);

uint32 systick_getval(void);


#endif
