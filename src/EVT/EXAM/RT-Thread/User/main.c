/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2020/04/30
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "ch32v10x.h"
#include <rtthread.h>
#include <rthw.h>
#include "drivers/pin.h"

/* Global typedef */

/* Global define */

/* LED0ͨ��rt��pin�����ӿ�����  */
#define LED0_PIN    15  //PA1

/* Global Variable */

/* LED1ͨ��ֱ�ӵ��õײ����� */
void LED1_BLINK_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/* mainֻ��һ���߳�֮һ������֮�⻹��tshell,idle
 *    ��mainֻ��һ��LED��˸��main�̵߳�ע����rtthread_startup
 *   ��
 * */
int main(void)
{
    rt_kprintf("\r\n MCU: CH32V103C8T6\r\n");
    rt_kprintf(" SysClk: %dHz\r\n", SystemCoreClock);
    rt_kprintf(" www.wch.cn\r\n");
    LED1_BLINK_INIT();

    GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    while(1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        rt_thread_mdelay(500);

        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        rt_thread_mdelay(500);
    }
}

/* ʹ�������ӿڲ���I/O�� */
int led(void)
{
    rt_uint8_t count;

    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    for(count = 0; count < 10; count++)
    {
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_kprintf("led on, count : %d\r\n", count);
        rt_thread_mdelay(500);

        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_kprintf("led off\r\n");
        rt_thread_mdelay(500);
    }
    return 0;
}
MSH_CMD_EXPORT(led, RT - Thread first led sample by using I / O driver);
