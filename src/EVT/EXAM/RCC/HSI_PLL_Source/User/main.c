/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : RCC configuration reference system_ch32v10x.h and 
                       system_ch32v10x.c file.
*******************************************************************************/

/*
 *@Note
 HSI��HSI/2��ΪPLL����ʱ�����̣�
 ��������ʾ��HSI��HSI/2��ΪPLL����ʱ�ӣ�ϵͳʱ����PLL��Ϊʱ��Դ��
 �ο�system_ch32v10x.c��system_ch32v10x.h��
 HSI��ΪPLL����ʱ�ӣ���ʾϵͳʱ��Ϊ 24MHz��48MHz��72MHz��
 HSI/2��ΪPLL����ʱ�ӣ���ʾϵͳʱ��Ϊ 24MHz��48MHz

*/
#include "debug.h"

#define HSI      0   //HSI
#define HSI_1_2  1   //HSI/2

#define PLL_Source   HSI
//#define PLL_Source   HSI_1_2

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);

    while(1);
}
