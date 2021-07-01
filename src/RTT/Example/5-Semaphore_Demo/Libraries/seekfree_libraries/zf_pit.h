/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_pit
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/

#ifndef _zf_pit_h
#define _zf_pit_h

#include "common.h"
#include "zf_qtimer.h"

//-------------�����ж�-------------------
void timer_pit_interrupt_ms(TIMERN_enum timern, uint16 ms);
void timer_pit_interrupt_us(TIMERN_enum timern, uint16 us);


//-------------��ʱ����ʱ-------------------
void timer_pit_start_us(TIMERN_enum timern);
uint16 timer_pit_get_us(TIMERN_enum timern);
void timer_pit_close(TIMERN_enum timern);


#endif
