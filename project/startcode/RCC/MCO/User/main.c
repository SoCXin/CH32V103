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
 MCO����ʱ��������̣�
 MCO(PA8)
 ��������ʾ MCO(PA8) �������ϵͳʱ�ӡ�

*/

#include "debug.h"


/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

/* MCO Output GPIOA 8 */
	RCC_MCOConfig( RCC_MCO_SYSCLK );

	while(1);
}
