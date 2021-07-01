/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_timer
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/

#ifndef _zf_timer_h
#define _zf_timer_h

#include "common.h"


typedef enum    //TIMER����ö��
{
    TIMER1_CHA_A8,
    TIMER1_CHB_A9,
    TIMER2_CHA_A0,
    TIMER2_CHB_A1,
    TIMER2_CHA_A15,              //��ȫӳ��
    TIMER2_CHB_B3,               //��ȫӳ��

    TIMER3_CHA_A6,
    TIMER3_CHB_A7,

    TIMER3_CHA_C6,               //��ȫӳ��
    TIMER3_CHB_C7,               //��ȫӳ��
    TIMER3_CHA_B4,               //����ӳ��
    TIMER3_CHB_B5,               //����ӳ��

    TIMER4_CHA_B6,
    TIMER4_CHB_B7,

}TIMER_PIN_enum;

//��ö�ٶ��岻�����û��޸�
typedef enum
{
    TIMER_1,
    TIMER_2,
    TIMER_3,
    TIMER_4,
}TIMERN_enum;

extern const uint32 TIMERN[] ;

void timer_quad_init(TIMERN_enum timern, TIMER_PIN_enum phaseA, TIMER_PIN_enum phaseB);
int16 timer_quad_get(TIMERN_enum timern);
void timer_quad_clear(TIMERN_enum timern);




#endif
