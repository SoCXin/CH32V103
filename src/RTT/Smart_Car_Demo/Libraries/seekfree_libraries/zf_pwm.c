/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_pwm
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
#include "zf_pwm.h"
#include "zf_gpio.h"
#include "zf_systick.h"
#include "zf_qtimer.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM���ų�ʼ��
//  @param      pwmch       PWMͨ��(��ѡ��Χ��zf_pwm.h��PWMCH_enumö��ֵȷ��)
//  @return     void
//  Sample usage:           �ڲ�ʹ��  �û��������
//-------------------------------------------------------------------------------------------------------------------
void pwm_gpio_init(PWMCH_enum pwmch)
{
    switch(pwmch)
    {

        case PWM1_CH1_A8:
            gpio_init(A8, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM1_CH2_A9:
            gpio_init(A9, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM1_CH3_A10:
            gpio_init(A10, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM1_CH4_A11:
            gpio_init(A11, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;

//        case PWM1_CH1N_B13:
//            gpio_init(B13, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
//            break;
//        case PWM1_CH2N_B14:
//            gpio_init(B14, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
//            break;
//        case PWM1_CH3N_B15:
//            gpio_init(B15, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
//            break;
//
//        case PWM1_CH1N_A7:
//            gpio_init(A7, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
//            break;
//        case PWM1_CH2N_B0:
//            gpio_init(B0, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
//            break;
//        case PWM1_CH3N_B1:
//            gpio_init(B1, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
//            break;

        case PWM2_CH1_A0:
            gpio_init(A0, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM2_CH2_A1:
            gpio_init(A1, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM2_CH3_A2:
            gpio_init(A2, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM2_CH4_A3:
            gpio_init(A3, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;

        case PWM2_CH1_A15:
            gpio_init(A15, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM2_CH2_B3:
            gpio_init(B3, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM2_CH3_B10:
            gpio_init(B10, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM2_CH4_B11:
            gpio_init(B11, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;

        case PWM3_CH1_A6:
            gpio_init(A6, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM3_CH2_A7:
            gpio_init(A7, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM3_CH3_B0:
            gpio_init(B0, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM3_CH4_B1:
            gpio_init(B1, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;

        case PWM3_CH1_C6:
            gpio_init(C6, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM3_CH2_C7:
            gpio_init(C7, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM3_CH3_C8:
            gpio_init(C8, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM3_CH4_C9:
            gpio_init(C9, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;

        case PWM3_CH1_B4:
            gpio_init(B4, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM3_CH2_B5:
            gpio_init(B5, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;

        case PWM4_CH1_B6:
            gpio_init(B6, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM4_CH2_B7:
            gpio_init(B7, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM4_CH3_B8:
            gpio_init(B8, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        case PWM4_CH4_B9:
            gpio_init(B9, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
            break;
        default:
            //����
            break;
    }
}







//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM��ʼ��
//  @param      pwmch           PWMͨ���ż�����
//  @param      freq            PWMƵ��
//  @param      duty            PWMռ�ձ�
//  @return     void
//  Sample usage:               pwm_init(PWM1_CH1_A8, 50, 5000);   //��ʼ��PWM1 ͨ��1 ʹ������A8  ���PWMƵ��50HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ50000
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(PWMCH_enum pwmch, uint32 freq, uint32 duty)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    uint16 match_temp;                                          //ռ�ձ�ֵ
    uint16 period_temp;                                         //����ֵ
    uint16 freq_div = 0;                                        //��Ƶֵ

    pwm_gpio_init(pwmch);                                       //PWM���ų�ʼ��

    if((pwmch >> 8) == 0x00)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //ʹ�ܶ�ʱ��1ʱ��
    else if((pwmch >> 8) == 0x01)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //ʹ�ܶ�ʱ��2ʱ��
    else if((pwmch >> 8) == 0x02)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��
    else if((pwmch >> 8) == 0x03)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //ʹ�ܶ�ʱ��4ʱ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //ʹ��AFIO���ù���ģ��ʱ��

    //������ӳ��
    if((pwmch >> 4) == 0x10)        //PWM1�Ĳ�����ӳ��
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
    else if((pwmch >> 4) == 0x11)   //PWM2����ȫ��ӳ��
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
    else if((pwmch >> 4) == 0x21)   //PWM3����ȫ��ӳ��
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
    else if((pwmch >> 4) == 0x22)   //PWM3�Ĳ�����ӳ��
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    //��ȡϵͳ��Ƶ
    sys_clk = 8000000 * (((RCC->CFGR0 >> 18)&0x0F) + 2);

    freq_div = (uint16)((sys_clk / freq) >> 16);                            //���ٷ�Ƶ
    period_temp = (uint16)(sys_clk/(freq*(freq_div + 1)));                  //����
    match_temp = period_temp * duty / PWM_DUTY_MAX;                         //ռ�ձ�

    //��ʼ��TIM1-4
    TIM_TimeBaseStructure.TIM_Period = period_temp - 1;                     //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = freq_div;                         //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    //��ʼ��TIM1-4 PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                       //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_Pulse = match_temp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                //�������:TIM����Ƚϼ��Ը�
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;               //�������:TIM����Ƚϼ��Ը�
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

    TIM_TimeBaseInit(((TIM_TypeDef *) TIMERN[pwmch>>8]), &TIM_TimeBaseStructure);  //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//        if(PWM1_CH1N_B13 <= pwmch)                                         //��ͨ��ΪNͨ��
//        {
//            TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //Pͨ��
//            TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Enable;  //Nͨ��
//        }
    if((pwmch & 0x03) == 0x00)                                          //ͨ��ѡ��
    {
        TIM_OC1Init(((TIM_TypeDef *) TIMERN[pwmch>>8]), &TIM_OCInitStructure );                       //��ʱ��ͨ��1��ʼ��
        TIM_OC1PreloadConfig(((TIM_TypeDef *) TIMERN[pwmch>>8]), TIM_OCPreload_Enable);               //��ʱ��Ԥװ������
        TIM_OC1FastConfig(((TIM_TypeDef *) TIMERN[pwmch>>8]), TIM_OC1FE);                             //�Ƚϲ���ͨ������ʹ��
    }
    else if((pwmch & 0x03) == 0x01)
    {
        TIM_OC2Init(((TIM_TypeDef *) TIMERN[pwmch>>8]), &TIM_OCInitStructure );
        TIM_OC2PreloadConfig(((TIM_TypeDef *) TIMERN[pwmch>>8]), TIM_OCPreload_Enable);
        TIM_OC2FastConfig(((TIM_TypeDef *) TIMERN[pwmch>>8]), TIM_OC2FE);                             //�Ƚϲ���ͨ������ʹ��
    }
    else if((pwmch & 0x03) == 0x02)
    {
        TIM_OC3Init(((TIM_TypeDef *) TIMERN[pwmch>>8]), &TIM_OCInitStructure );
        TIM_OC3PreloadConfig(((TIM_TypeDef *) TIMERN[pwmch>>8]), TIM_OCPreload_Enable);
        TIM_OC3FastConfig(((TIM_TypeDef *) TIMERN[pwmch>>8]), TIM_OC3FE);                             //�Ƚϲ���ͨ������ʹ��
    }
    else if((pwmch & 0x03) == 0x03)
    {
        TIM_OC4Init(((TIM_TypeDef *) TIMERN[pwmch>>8]), &TIM_OCInitStructure );
        TIM_OC4PreloadConfig(((TIM_TypeDef *) TIMERN[pwmch>>8]), TIM_OCPreload_Enable);
        TIM_OC4FastConfig(((TIM_TypeDef *) TIMERN[pwmch>>8]), TIM_OC4FE);                             //�Ƚϲ���ͨ������ʹ��
    }
    TIM_Cmd(((TIM_TypeDef *) TIMERN[pwmch>>8]), ENABLE);                                              //��ʱ��ʹ��
    TIM_CtrlPWMOutputs(((TIM_TypeDef *) TIMERN[pwmch>>8]), ENABLE );
    //TIM_ARRPreloadConfig( TIM1, ENABLE );
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWMռ�ձ��趨
//  @param      pwmch           PWMͨ���ż�����
//  @param      duty            PWMռ�ձ�
//  @return     void
//  Sample usage:               pwm_duty(PWM1_CH1_A8, 5000);   //PWM1 ͨ��1 ʹ������A8 ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ50000
//-------------------------------------------------------------------------------------------------------------------
void pwm_duty(PWMCH_enum pwmch, uint32 duty)
{
    uint16 match_temp;
    uint16 period_temp;
    //const uint32 TIMERN[] = {TIM1_BASE, TIM2_BASE, TIM3_BASE, TIM4_BASE};
    //��ȡ����ֵ
    //����ռ�ձ�

    period_temp = ((TIM_TypeDef *) TIMERN[pwmch>>8])->ATRLR;    //��ȡ��ʱ��������ֵ
    match_temp = period_temp * duty / PWM_DUTY_MAX;             //ռ�ձ�

    if((pwmch >> 8) == 0x00)
    {
        (*(volatile uint32*)(0x40012C34 + (pwmch&0x03) * 0x04)) = match_temp;
        //0x40012C34 TIM1->CH1CVR
        //0x40012C38 TIM1->CH2CVR
        //0x40012C3C TIM1->CH3CVR
        //0x40012C40 TIM1->CH4CVR
    }
    else if((pwmch >> 8) == 0x01)
    {
        (*(volatile uint32*)(0x40000034 + (pwmch&0x03) * 0x04)) = match_temp;
        //0x40000034 TIM2->CH1CVR
        //0x40000038 TIM2->CH2CVR
        //0x4000003C TIM2->CH3CVR
        //0x40000040 TIM2->CH4CVR
    }
    else if((pwmch >> 8) == 0x02)
    {
        (*(volatile uint32*)(0x40000434 + (pwmch&0x03) * 0x04)) = match_temp;
        //0x40000434 TIM3->CH1CVR
        //0x40000438 TIM3->CH2CVR
        //0x4000043C TIM3->CH3CVR
        //0x40000440 TIM3->CH4CVR
    }
    else if((pwmch >> 8) == 0x03)
    {
        (*(volatile uint32*)(0x40000834 + (pwmch&0x03) * 0x04)) = match_temp;
        //0x40000834 TIM4->CH1CVR
        //0x40000838 TIM4->CH2CVR
        //0x4000083C TIM4->CH3CVR
        //0x40000840 TIM4->CH4CVR
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWMƵ���趨
//  @param      pwmch           PWMͨ���ż�����
//  @param      freq            PWMƵ��
//  @param      duty            PWMռ�ձ�
//  @return     void
//  Sample usage:               pwm_freq(PWM1_CH1_A8, 60, 5000);   //ʹ������A8  ���PWMƵ��60HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ50000
//-------------------------------------------------------------------------------------------------------------------
void pwm_freq(PWMCH_enum pwmch, uint32 freq, uint32 duty)
{
    uint16 period_temp = 0;                                     //����ֵ
    uint16 freq_div = 0;                                        //��Ƶֵ
    uint16 match_temp;

    freq_div = (uint16)((sys_clk / freq) >> 16);                //������ٷ�Ƶ
    period_temp = (uint16)(sys_clk/(freq*(freq_div + 1)));      //��������

    ((TIM_TypeDef *) TIMERN[pwmch>>8])->ATRLR = period_temp - 1 ;
    ((TIM_TypeDef *) TIMERN[pwmch>>8])->PSC = freq_div;
    match_temp = period_temp * duty / PWM_DUTY_MAX;             //ռ�ձ�
    if((pwmch >> 8) == 0x00)
    {
        (*(volatile uint32*)(0x40012C34 + (pwmch&0x03) * 0x04)) = match_temp;
    }
    else if((pwmch >> 8) == 0x01)
    {
        (*(volatile uint32*)(0x40000034 + (pwmch&0x03) * 0x04)) = match_temp;
    }
    else if((pwmch >> 8) == 0x02)
    {
        (*(volatile uint32*)(0x40000434 + (pwmch&0x03) * 0x04)) = match_temp;
    }
    else if((pwmch >> 8) == 0x03)
    {
        (*(volatile uint32*)(0x40000834 + (pwmch&0x03) * 0x04)) = match_temp;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWMֹͣ���
//  @param      pwmch           PWMͨ���ż�����
//  @return     void
//  Sample usage:               pwm_freq(PWM1_CH1_A8, 60, 5000);   //ʹ������A8  ���PWMƵ��60HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ50000
//-------------------------------------------------------------------------------------------------------------------
void pwm_stop(PWMCH_enum pwmch)
{
    TIM_Cmd(((TIM_TypeDef *) TIMERN[pwmch>>8]), DISABLE);         //��ʱ��ʧ��
}
