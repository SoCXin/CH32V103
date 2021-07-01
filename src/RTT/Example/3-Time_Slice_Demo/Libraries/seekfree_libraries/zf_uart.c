/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            zf_uart
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
#include "ch32v10x_usart.h"
#include "ch32v10x_misc.h"
#include "zf_gpio.h"
#include "zf_uart.h"
#include "zf_nvic.h"


const uint32 UARTN[] = {USART1_BASE, USART2_BASE, USART3_BASE ,UART4_BASE};
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ų�ʼ��
//  @param      tx_pin      ���ڷ������ź�
//  @param      rx_pin      ���ڽ������ź�
//  @return     void
//  Sample usage:           �ڲ�ʹ�ã��û��������
//-------------------------------------------------------------------------------------------------------------------
void uart_gpio_init(UARTPIN_enum tx_pin, UARTPIN_enum rx_pin)
{
    if(tx_pin == UART1_TX_A9 && rx_pin == UART1_RX_A10)
    {
        gpio_init(A9, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
        gpio_init(A10, GPI, 0, IN_FLOAT);
    }
    else if(tx_pin == UART1_TX_B6)
    {
        gpio_init(B6, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
        gpio_init(B7, GPI, 0, IN_FLOAT);

    }
    else if(tx_pin == UART2_TX_A2)
    {
        gpio_init(A2, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
        gpio_init(A3, GPI, 0, IN_FLOAT);

    }
    else if(tx_pin == UART3_TX_B10)
    {
        gpio_init(B10, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
        gpio_init(B11, GPI, 0, IN_FLOAT);

    }
    else if(tx_pin == UART3_TX_C10)
    {
        gpio_init(C10, GPO, 0, SPEED_50MHZ|OUT_AF_PP);
        gpio_init(C11, GPI, 0, IN_FLOAT);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڳ�ʼ��
//  @param      uartn       ����ͨ��
//  @param      baud        ������
//  @param      tx_pin      ���ڷ������ź�
//  @param      rx_pin      ���ڽ������ź�
//  @return     void
//  Sample usage:           uart_init(UART_1, 115200, UART1_TX_A9, UART1_RX_A10); //����1��ʼ�����ź�,TXΪA9,RXΪA10
//-------------------------------------------------------------------------------------------------------------------
void uart_init(UARTN_enum uartn, uint32 baud, UARTPIN_enum tx_pin, UARTPIN_enum rx_pin)
{
    USART_InitTypeDef USART_InitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    //���ų�ʼ��
    uart_gpio_init(tx_pin, rx_pin);

    if(UART1_TX_B6 == tx_pin && UART1_RX_B7 == rx_pin)                         //������ӳ��
        GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    if(UART3_TX_C10 == tx_pin && UART3_RX_C11 == rx_pin)
        GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);

    //��������ʹ��
    if(UART_1 == uartn) RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    else if(UART_2 == uartn) RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    else if(UART_3 == uartn) RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    //���ڲ�������
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    //ʹ�ܴ���
    USART_Init((USART_TypeDef*)UARTN[uartn], &USART_InitStructure);
    USART_Cmd((USART_TypeDef*)UARTN[uartn], ENABLE);


}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ���һ���ֽ�
//  @param      uartn       ����ͨ��
//  @param      dat         ��������
//  @return     void
//  Sample usage:           uart_putchar(UART_1, 0x43);        //����1����0x43��
//-------------------------------------------------------------------------------------------------------------------
void uart_putchar(UARTN_enum uartn, uint8 dat)
{
    while((((USART_TypeDef*)UARTN[uartn])->STATR & USART_FLAG_TXE)==0);
    ((USART_TypeDef*)UARTN[uartn])->DATAR = dat;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ�������
//  @param      uartn       ����ͨ��
//  @param      buff        Ҫ���͵������ַ
//  @param      len         ���ݳ���
//  @return     void
//  Sample usage:           uart_putbuff(UART_1, buff, 10);     //����1����10��buff���顣
//-------------------------------------------------------------------------------------------------------------------
void uart_putbuff(UARTN_enum uartn, uint8 *buff, uint32 len)
{
    while(len--)
        uart_putchar(uartn, *buff++);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ����ַ���
//  @param      uartn       ����ͨ��
//  @param      str         �ַ����׵�ַ
//  @return     void
//  Sample usage:           uart_putstr(UART_1, (uint8 *)"12345")   //����1����12345����ַ���
//-------------------------------------------------------------------------------------------------------------------
void uart_putstr(UARTN_enum uartn, const uint8 *str)
{
    while(*str)
    {
        uart_putchar(uartn, *str++);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �򿪴��ڽ����ж�
//  @param      uartn       ����ͨ��
//  @param      status      ʹ�ܻ���ʧ��
//  @return     void
//  Sample usage:           uart_rx_irq(UART_1, ENABLE);        //�򿪴���1�����ж�
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_irq(UARTN_enum uartn,uint8 status)
{
    USART_ITConfig(((USART_TypeDef*)UARTN[uartn]), USART_IT_RXNE, ENABLE);
    nvic_init(USART1_IRQn + uartn, 1, 0, status);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �򿪴��ڷ����ж�
//  @param      uartn       ����ͨ��
//  @param      status      ʹ�ܻ���ʧ��
//  @return     void
//  Sample usage:           uart_tx_irq(UART_1, DISABLE);       //�رմ���1���� �ж�
//-------------------------------------------------------------------------------------------------------------------
void uart_tx_irq(UARTN_enum uartn,uint8 status)
{
    USART_ITConfig(((USART_TypeDef*)UARTN[uartn]), USART_IT_TXE, ENABLE);
    nvic_init(USART1_IRQn + uartn, 1, 0, status);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ���ڽ��յ����ݣ�whlie�ȴ���
//  @param      uartn           ����ģ���(UART_1,UART_2,UART_3,UART_4)
//  @param      *dat            �������ݵĵ�ַ
//  @return     void
//  Sample usage:               uint8 dat; uart_getchar(USART_1,&dat);       // ���մ���1����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
void uart_getchar(UARTN_enum uartn, uint8 *dat)
{
    while((((USART_TypeDef*)UARTN[uartn])->STATR & USART_FLAG_RXNE) == 0);
    *dat = (uint16_t)(((USART_TypeDef*)UARTN[uartn])->DATAR & (uint16_t)0x01FF);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ���ڽ��յ����ݣ���ѯ���գ�
//  @param      uartn           ����ģ���(UART_1,UART_2,UART_3,UART_4)
//  @param      *dat            �������ݵĵ�ַ
//  @return     uint8           1�����ճɹ�   0��δ���յ�����
//  Sample usage:               uint8 dat; uart_query(USART_1,&dat);       // ���մ���1����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query(UARTN_enum uartn, uint8 *dat)
{
    if((((USART_TypeDef*)UARTN[uartn])->STATR & USART_FLAG_RXNE) != 0)
    {
        *dat = (uint16_t)(((USART_TypeDef*)UARTN[uartn])->DATAR & (uint16_t)0x01FF);
        return 1;
    }
    return 0;
}





