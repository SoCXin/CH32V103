/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            isr
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/


#include "headfile.h"




void WWDG_IRQHandler(void) __attribute__((interrupt()));
void HardFault_Handler(void) __attribute__((interrupt()));
void NMI_Handler(void) __attribute__((interrupt()));
void EXTI0_IRQHandler(void) __attribute__((interrupt()));
void EXTI1_IRQHandler(void) __attribute__((interrupt()));
void EXTI2_IRQHandler(void) __attribute__((interrupt()));
void EXTI3_IRQHandler(void) __attribute__((interrupt()));
void EXTI4_IRQHandler(void) __attribute__((interrupt()));
void DMA1_Channel1_IRQHandler(void) __attribute__((interrupt()));
void DMA1_Channel2_IRQHandler(void) __attribute__((interrupt()));
void DMA1_Channel3_IRQHandler(void) __attribute__((interrupt()));
void DMA1_Channel4_IRQHandler(void) __attribute__((interrupt()));
void DMA1_Channel5_IRQHandler(void) __attribute__((interrupt()));
void DMA1_Channel6_IRQHandler(void) __attribute__((interrupt()));
void DMA1_Channel7_IRQHandler(void) __attribute__((interrupt()));
void ADC1_2_IRQHandler(void) __attribute__((interrupt()));
void EXTI9_5_IRQHandler(void) __attribute__((interrupt()));
void TIM1_BRK_IRQHandler(void) __attribute__((interrupt()));
void TIM1_UP_IRQHandler(void) __attribute__((interrupt()));
void TIM1_TRG_COM_IRQHandler(void) __attribute__((interrupt()));
void TIM1_CC_IRQHandler(void) __attribute__((interrupt()));

void TIM3_IRQHandler(void) __attribute__((interrupt()));
void TIM4_IRQHandler(void) __attribute__((interrupt()));
//void I2C1_EV_IRQHandler(void) __attribute__((interrupt()));
//void I2C1_ER_IRQHandler(void) __attribute__((interrupt()));
//void I2C2_EV_IRQHandler(void) __attribute__((interrupt()));
//void I2C2_ER_IRQHandler(void) __attribute__((interrupt()));
//void SPI1_IRQHandler(void) __attribute__((interrupt()));
//void SPI2_IRQHandler(void) __attribute__((interrupt()));

void USART2_IRQHandler(void) __attribute__((interrupt()));
void USART3_IRQHandler(void) __attribute__((interrupt()));
void EXTI15_10_IRQHandler(void) __attribute__((interrupt()));
//void RTCAlarm_IRQHandler(void) __attribute__((interrupt()));
//void USBWakeUp_IRQHandler(void) __attribute__((interrupt()));
//void USBHD_IRQHandler(void) __attribute__((interrupt()));

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();   //�����ж�

    if(SET == EXTI_GetITStatus(EXTI_Line0))
    {

        EXTI_ClearITPendingBit(EXTI_Line0);
    }

    rt_interrupt_leave();   //�˳��ж�
}

void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();   //�����ж�

    if(SET == EXTI_GetITStatus(EXTI_Line1))
    {
        if(camera_type == CAMERA_BIN_UART)
            ov7725_uart_vsync();
        else if(camera_type == CAMERA_GRAYSCALE)
            mt9v03x_vsync();
        EXTI_ClearITPendingBit(EXTI_Line1);
    }

    rt_interrupt_leave();   //�˳��ж�
}

void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();    //�����ж�

    if(SET == EXTI_GetITStatus(EXTI_Line2))
    {

        EXTI_ClearITPendingBit(EXTI_Line2);
    }

    rt_interrupt_leave();    //�˳��ж�
}

void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();   //�����ж�

    if(SET == EXTI_GetITStatus(EXTI_Line3))
    {

        EXTI_ClearITPendingBit(EXTI_Line3);
    }

    rt_interrupt_leave();   //�˳��ж�
}

void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();    //�����ж�

    if(SET == EXTI_GetITStatus(EXTI_Line4))
    {

        EXTI_ClearITPendingBit(EXTI_Line4);
    }

    rt_interrupt_leave();    //�˳��ж�
}

void EXTI9_5_IRQHandler(void)
{
    rt_interrupt_enter();   //�����ж�

    if(SET == EXTI_GetITStatus(EXTI_Line9))
    {

        EXTI_ClearITPendingBit(EXTI_Line9);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line8))
    {

        EXTI_ClearITPendingBit(EXTI_Line8);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line7))
    {

        EXTI_ClearITPendingBit(EXTI_Line7);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line6))
    {

        EXTI_ClearITPendingBit(EXTI_Line6);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line5))
    {

        EXTI_ClearITPendingBit(EXTI_Line5);
    }

    rt_interrupt_leave();       //�˳��ж�
}

void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();   //�����ж�

    if(SET == EXTI_GetITStatus(EXTI_Line15))
    {

        EXTI_ClearITPendingBit(EXTI_Line15);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line14))
    {

        EXTI_ClearITPendingBit(EXTI_Line14);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line13))
    {

        EXTI_ClearITPendingBit(EXTI_Line13);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line12))
    {

        EXTI_ClearITPendingBit(EXTI_Line12);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line11))
    {

        EXTI_ClearITPendingBit(EXTI_Line11);
    }
    else if(SET == EXTI_GetITStatus(EXTI_Line10))
    {

        EXTI_ClearITPendingBit(EXTI_Line10);
    }

    rt_interrupt_leave();       //�˳��ж�
}

void ADC1_2_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}

void TIM1_BRK_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    if(TIM_GetITStatus(TIM1, TIM_IT_Break) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Break);

    }

    rt_interrupt_leave();       //�˳��ж�
}

void TIM1_UP_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�


    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

    }

    rt_interrupt_leave();       //�˳��ж�
}

void TIM1_TRG_COM_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    if(TIM_GetITStatus(TIM1, TIM_IT_Trigger) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Trigger);

    }
    if(TIM_GetITStatus(TIM1, TIM_IT_COM) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_COM);

    }

    rt_interrupt_leave();       //�˳��ж�
}

void TIM1_CC_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);

    }
    if(TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);

    }
    if(TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);

    }
    if(TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);

    }

    rt_interrupt_leave();       //�˳��ж�
}

void TIM2_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update );
        ccd_collect();//CCD���ݲɼ�
    }

    rt_interrupt_leave();       //�˳��ж�
}

void TIM3_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update );

    }

    rt_interrupt_leave();       //�˳��ж�
}

void TIM4_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update );

    }

    rt_interrupt_leave();       //�˳��ж�
}

//����1 ��������board.c�У����ڽ��մ������ݲ�ͨ���ʼ����͸�finsh�߳�
//void USART1_IRQHandler(void)
//{
//    rt_interrupt_enter();       //�����ж�
//
//    //��ȡ�жϱ�־λ
//    //����жϱ�־λ
//
//    rt_interrupt_leave();       //�˳��ж�
//}

void USART2_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        //USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        if(camera_type == CAMERA_BIN_UART)
            ov7725_cof_uart_interrupt();
        else if(camera_type == CAMERA_GRAYSCALE)
            mt9v03x_uart_callback();
    }

    rt_interrupt_leave();       //�˳��ж�
}

void USART3_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}

void DMA1_Channel4_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    if(SET == DMA_GetFlagStatus(DMA1_FLAG_TC4))
    {
        DMA_ClearFlag(DMA1_FLAG_TC4);
        if(camera_type == CAMERA_BIN_UART)
            ov7725_uart_dma();
        else if(camera_type == CAMERA_GRAYSCALE)
            mt9v03x_dma();
    }

    rt_interrupt_leave();       //�˳��ж�
}

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}

void HardFault_Handler(void)
{
    rt_interrupt_enter();       //�����ж�

    while(1);

    rt_interrupt_leave();       //�˳��ж�
}



void WWDG_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}

void TAMPER_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void RTC_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void FLASH_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void RCC_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void DMA1_Channel1_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void DMA1_Channel2_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void DMA1_Channel3_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void DMA1_Channel5_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void DMA1_Channel6_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}
void DMA1_Channel7_IRQHandler(void)
{
    rt_interrupt_enter();       //�����ж�

    //��ȡ�жϱ�־λ
    //����жϱ�־λ

    rt_interrupt_leave();       //�˳��ж�
}


