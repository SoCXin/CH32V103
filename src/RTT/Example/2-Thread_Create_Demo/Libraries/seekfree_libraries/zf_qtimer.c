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
#include "ch32v10x_rcc.h"
#include "ch32v10x_gpio.h"
#include "ch32v10x_tim.h"
#include "ch32v10x_misc.h"

#include "zf_gpio.h"
#include "zf_qtimer.h"
#include "zf_nvic.h"

const uint32 TIMERN[] = {TIM1_BASE, TIM2_BASE, TIM3_BASE, TIM4_BASE};



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ų�ʼ��
//  @param      phaseA      ͨ��A�Լ�����
//  @param      phaseB      ͨ��B�Լ�����
//  @return     void
//  Sample usage:           �ڲ�ʹ�ã��û��������
//-------------------------------------------------------------------------------------------------------------------
void timer_gpio_quad_init(TIMER_PIN_enum phaseA, TIMER_PIN_enum phaseB)
{
    if(TIMER1_CHA_A8 == phaseA)       gpio_init(A8, GPI, 0, IN_FLOAT);
    else if(TIMER2_CHA_A0 == phaseA)  gpio_init(A0, GPI, 0, IN_FLOAT);
    else if(TIMER2_CHA_A15 == phaseA) gpio_init(A15, GPI, 0, IN_FLOAT);
    else if(TIMER3_CHA_A6 == phaseA)  gpio_init(A6, GPI, 0, IN_FLOAT);
    else if(TIMER3_CHA_C6 == phaseA)  gpio_init(C6, GPI, 0, IN_FLOAT);
    else if(TIMER3_CHA_B4 == phaseA)  gpio_init(B4, GPI, 0, IN_FLOAT);
    else if(TIMER4_CHA_B6 == phaseA)  gpio_init(B6, GPI, 0, IN_FLOAT);

    if(TIMER1_CHB_A9 == phaseB)       gpio_init(A9, GPI, 0, IN_FLOAT);
    else if(TIMER2_CHB_A1 == phaseB)  gpio_init(A1, GPI, 0, IN_FLOAT);
    else if(TIMER2_CHB_B3 == phaseB)  gpio_init(B3, GPI, 0, IN_FLOAT);
    else if(TIMER3_CHB_A7 == phaseB)  gpio_init(A7, GPI, 0, IN_FLOAT);
    else if(TIMER3_CHB_C7 == phaseB)  gpio_init(C7, GPI, 0, IN_FLOAT);
    else if(TIMER3_CHB_B5 == phaseB)  gpio_init(B5, GPI, 0, IN_FLOAT);
    else if(TIMER4_CHB_B7 == phaseB)  gpio_init(B7, GPI, 0, IN_FLOAT);

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����������ʼ��
//  @param      timern      ��ʱ��ö����
//  @param      phaseA      ͨ��A�Լ�����
//  @param      phaseB      ͨ��B�Լ�����
//  @return     void
//  Sample usage:           �Ƽ�ʹ�����������������
//-------------------------------------------------------------------------------------------------------------------
void timer_quad_init(TIMERN_enum timern, TIMER_PIN_enum phaseA, TIMER_PIN_enum phaseB)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    if(TIMER_1 == timern)       RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//ʹ�ܶ�ʱ��1��ʱ��
    else  if(TIMER_2 == timern) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��2��ʱ��
    else  if(TIMER_3 == timern) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ�ܶ�ʱ��3��ʱ��
    else  if(TIMER_4 == timern) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��

    timer_gpio_quad_init(phaseA, phaseB);                                           //��ʼ������

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                            //ʹ��AFIO���ù���ģ��ʱ��

    if(TIMER2_CHA_A15 == phaseA && TIMER2_CHB_B3 == phaseB)                         //������ӳ��
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
    else    if(TIMER3_CHA_C6 == phaseA && TIMER3_CHB_C7 == phaseB)
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
    else    if(TIMER3_CHA_B4 == phaseA && TIMER3_CHB_B5 == phaseB)
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 1;                                        //Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                                      //�趨�������Զ���װֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                         //ѡ��ʱ�ӷ�Ƶ������Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                     //TIM���ϼ���
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                                //�ظ�������
    TIM_TimeBaseInit((TIM_TypeDef*)(TIMERN[timern]), &TIM_TimeBaseStructure);       //��ʼ���ṹ��
    TIM_EncoderInterfaceConfig((TIM_TypeDef*)(TIMERN[timern]), TIM_EncoderMode_TI2 , TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ

    TIM_Cmd((TIM_TypeDef*)(TIMERN[timern]), ENABLE);                                //��ʱ��ʹ��
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʱ������������ȡֵ
//  @param      timern      ��ʱ��ö����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int16 timer_quad_get(TIMERN_enum timern)
{
    int16 count = ((TIM_TypeDef*)(TIMERN[timern]))->CNT;
    return count;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʱ���ļ��������
//  @param      timern      ��ʱ��ö����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void timer_quad_clear(TIMERN_enum timern)
{
    ((TIM_TypeDef*)(TIMERN[timern]))->CNT = 0;
}


