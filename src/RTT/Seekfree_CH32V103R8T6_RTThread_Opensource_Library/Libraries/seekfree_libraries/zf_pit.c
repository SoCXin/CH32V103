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
#include "ch32v10x_rcc.h"
#include "ch32v10x_gpio.h"
#include "ch32v10x_tim.h"
#include "ch32v10x_misc.h"

#include "zf_qtimer.h"
#include "zf_pit.h"
#include "zf_nvic.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʱ�������ж�
//  @param      timern      ��ʱ��ͨ��
//  @param      ms          ��ʱ����(1-32767)
//  @return     void
//  Sample usage:           timer_pit_interrupt(TIMER_1, 5); ʹ�ö�ʱ��1��Ϊ5msһ�ε������ж�
//-------------------------------------------------------------------------------------------------------------------
void timer_pit_interrupt_ms(TIMERN_enum timern, uint16 ms)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    if(TIMER_1 == timern)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);                //ʱ��ʹ��
    else if(TIMER_2 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                //ʱ��ʹ��
    else if(TIMER_3 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                //ʱ��ʹ��
    else if(TIMER_4 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);                //ʱ��ʹ��

    //��ʱ��TIM3��ʼ��,������
    //ATRLR�Ĵ�������Ϊ1 �������0��1��һ��2��
    assert(ms);


    TIM_TimeBaseStructure.TIM_Period = sys_clk/2000 - 1;                    //����44000
    TIM_TimeBaseStructure.TIM_Prescaler = 2*ms - 1;                      //����Ϊ1MHZ����һ��,Ҳ����1us����һ��

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                        //�ظ�����������Ϊ0
    TIM_TimeBaseInit((TIM_TypeDef *)TIMERN[timern], &TIM_TimeBaseStructure);//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig((TIM_TypeDef *)TIMERN[timern],TIM_IT_Update,ENABLE );      //ʹ��ָ����TIM�ж�,��������ж�
    TIM_ClearITPendingBit((TIM_TypeDef *)TIMERN[timern], TIM_IT_Update);

    //�ж����ȼ�NVIC����
    if(TIMER_1 == timern)
        nvic_init(TIM1_UP_IRQn, 1, 2, ENABLE);
    else if(TIMER_2 == timern)
        nvic_init(TIM2_IRQn, 1, 2, ENABLE);
    else if(TIMER_3 == timern)
        nvic_init(TIM3_IRQn, 1, 2, ENABLE);
    else if(TIMER_4 == timern)
        nvic_init(TIM4_IRQn, 1, 2, ENABLE);

    TIM_Cmd((TIM_TypeDef *)TIMERN[timern], ENABLE);  //ʹ��TIMx

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʱ�������ж�
//  @param      timern      ��ʱ��ͨ��
//  @param      us          ��ʱ����(1-65535)
//  @return     void
//  Sample usage:           timer_pit_interrupt(TIMER_1, 5); ʹ�ö�ʱ��1��Ϊ5msһ�ε������ж�
//-------------------------------------------------------------------------------------------------------------------
void timer_pit_interrupt_us(TIMERN_enum timern, uint16 us)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    if(TIMER_1 == timern)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);                //ʱ��ʹ��
    else if(TIMER_2 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                //ʱ��ʹ��
    else if(TIMER_3 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                //ʱ��ʹ��
    else if(TIMER_4 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);                //ʱ��ʹ��

    //��ʱ��TIM3��ʼ��,������
    //ATRLR�Ĵ�������Ϊ1 �������0��1��һ��2��
    assert(us);


    TIM_TimeBaseStructure.TIM_Period = sys_clk/1000000 - 1;                 //����88��
    TIM_TimeBaseStructure.TIM_Prescaler = us - 1;                           //��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                        //�ظ�����������Ϊ0
    TIM_TimeBaseInit((TIM_TypeDef *)TIMERN[timern], &TIM_TimeBaseStructure);//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig((TIM_TypeDef *)TIMERN[timern],TIM_IT_Update,ENABLE );      //ʹ��ָ����TIM�ж�,��������ж�
    TIM_ClearITPendingBit((TIM_TypeDef *)TIMERN[timern], TIM_IT_Update);

    //�ж����ȼ�NVIC����
    if(TIMER_1 == timern)
        nvic_init(TIM1_UP_IRQn, 1, 2, ENABLE);
    else if(TIMER_2 == timern)
        nvic_init(TIM2_IRQn, 1, 2, ENABLE);
    else if(TIMER_3 == timern)
        nvic_init(TIM3_IRQn, 1, 2, ENABLE);
    else if(TIMER_4 == timern)
        nvic_init(TIM4_IRQn, 1, 2, ENABLE);

    TIM_Cmd((TIM_TypeDef *)TIMERN[timern], ENABLE);  //ʹ��TIMx

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      us��ʱ����ʼ
//  @param      timern      ѡ��ģ���ͨ�� (ѡ��Χ ��TIMERN_enumö��ֵ������ȷ��)
//  @return     void
//  Sample usage:           pit_start_us(TIMER_1);  //��ʱ��0 ��ʼ������ÿ��us����һ��
//-------------------------------------------------------------------------------------------------------------------
void timer_pit_start_us(TIMERN_enum timern)
{
    if(TIMER_1 == timern)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);                //ʱ��ʹ��
    else if(TIMER_2 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                //ʱ��ʹ��
    else if(TIMER_3 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                //ʱ��ʹ��
    else if(TIMER_4 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);                //ʱ��ʹ��

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 65535;                               //����88��
    TIM_TimeBaseStructure.TIM_Prescaler = sys_clk/1000000 - 1;              //��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                        //�ظ�����������Ϊ0
    TIM_TimeBaseInit((TIM_TypeDef *)TIMERN[timern], &TIM_TimeBaseStructure);//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    ((TIM_TypeDef *)TIMERN[timern])->CNT = 0;
    TIM_Cmd((TIM_TypeDef *)TIMERN[timern], ENABLE);  //ʹ��TIMx
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ��ʱ��ֵ
//  @param      timern      ѡ��ģ���ͨ�� (ѡ��Χ ��TIMERN_enumö��ֵ������ȷ��)
//  @return     uint32      ����ֵ
//  Sample usage:           ������ͨ���û�������ģ������Ҫ��ȡ����ֵ��Ӧ�õ���h�ļ��ĺ궨�庯��������ʱ�䵥λ��
//-------------------------------------------------------------------------------------------------------------------
uint16 timer_pit_get_us(TIMERN_enum timern)
{
    return ((TIM_TypeDef *)TIMERN[timern])->CNT;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ر�PIT��ʱ��
//  @param      timern      ѡ��ģ���ͨ�� (ѡ��Χ ��TIMERN_enumö��ֵ������ȷ��)
//  @return     void
//  Sample usage:           �رն�ʱ���������־λ
//-------------------------------------------------------------------------------------------------------------------
void timer_pit_close(TIMERN_enum timern)
{
    TIM_Cmd((TIM_TypeDef *)TIMERN[timern], DISABLE);  //ʹ��TIMx
}



