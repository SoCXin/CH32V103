/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_camera
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
#include "ch32v10x_dma.h"
#include "ch32v10x_rcc.h"
#include "ch32v10x_tim.h"
#include "ch32v10x.h"

#include "zf_gpio.h"
#include "zf_camera.h"
#include "zf_qtimer.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ͷDMA��ʼ��
//  @param      dma_ch              DAMͨ��
//  @param      src_addr            Դ��ַ
//  @param      des_addr            Ŀ���ַ
//  @param      size                ���ݳ���
//  @return     void
//  Sample usage:                   camera_dma_init(DMA1_Channel4, GPIOA->ODR, GPIOC->ODR, 8);
//-------------------------------------------------------------------------------------------------------------------
void camera_dma_init(DMA_Channel_TypeDef* dma_ch,uint32 src_addr, uint32 des_addr, uint32 size)
{
    DMA_InitTypeDef DMA_InitStructure;

    if(DMA1_Channel1 == dma_ch || DMA1_Channel2 == dma_ch || DMA1_Channel3 == dma_ch || DMA1_Channel4 == dma_ch ||
       DMA1_Channel5 == dma_ch || DMA1_Channel6 == dma_ch || DMA1_Channel7 == dma_ch)
    {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//DMA1���߳�ʼ��
    }
    else if(DMA2_Channel1 == dma_ch || DMA2_Channel2 == dma_ch || DMA2_Channel3 == dma_ch ||  DMA2_Channel4 == dma_ch ||
            DMA2_Channel5 == dma_ch)
    {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);//DMA2���߳�ʼ��
    }

    DMA_DeInit(dma_ch);

    //MDA���ó�ʼ��
    DMA_InitStructure.DMA_PeripheralBaseAddr = src_addr;                    //Դ��ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = des_addr;                        //Ŀ���ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      //������ΪԴ
    DMA_InitStructure.DMA_BufferSize = size;                                //������ٸ�����
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //�����ַ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //�ڴ��ַ����+1
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //����ÿ�δ���һ���ֽ�
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //�ڴ�ÿ�δ���һ���ֽ�
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           //��ѭ��ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 //���ȼ����
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            //���ڴ浽�ڴ�ģʽ
    DMA_Init(dma_ch, &DMA_InitStructure);

    DMA_ITConfig(dma_ch, DMA_IT_TC, ENABLE);                                //����DMA��������ж�
    DMA_Cmd(dma_ch, ENABLE);                                                //����DMA1

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ͷGPIO������ʱ����ʼ��
//  @param      timern              ��ʱ��ͨ��
//  @param      pin                 ���ź�
//  @return     void
//  Sample usage:                   camera_tim_etr_init(TIMER_1, A12);  //��ʱ��ERT�����ǹ̶������Ž�ֹ�����޸�
//-------------------------------------------------------------------------------------------------------------------
void camera_tim_etr_init(TIMERN_enum timern, PIN_enum pin)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    if(TIMER_1 == timern)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    else if(TIMER_2 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    else if(TIMER_3 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    else if(TIMER_4 == timern)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    gpio_init(pin, GPI, 0, IN_FLOAT);

    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit((TIM_TypeDef*)(TIMERN[timern]), &TIM_TimeBaseStructure);

    TIM_ETRClockMode1Config((TIM_TypeDef*)(TIMERN[timern]), TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_Inverted, 0x00);
    TIM_SelectInputTrigger((TIM_TypeDef*)(TIMERN[timern]), TIM_TS_ETRF);
    TIM_SelectSlaveMode((TIM_TypeDef*)(TIMERN[timern]), TIM_SlaveMode_Reset);                   //TIM��ģʽ�������źŵ����������³�ʼ���������ʹ����Ĵ����ĸ����¼�
    TIM_SelectMasterSlaveMode((TIM_TypeDef*)(TIMERN[timern]), TIM_MasterSlaveMode_Enable);      //������ʱ���ı�������

    TIM_Cmd((TIM_TypeDef*)(TIMERN[timern]), ENABLE);
    TIM_DMACmd((TIM_TypeDef*)(TIMERN[timern]), TIM_DMA_Trigger, ENABLE);                        //ʹ��TIM_DMA
}











