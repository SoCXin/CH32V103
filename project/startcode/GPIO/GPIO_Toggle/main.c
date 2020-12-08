/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/
#include "debug.h"

/* Global define */


/* Global Variable */


/*******************************************************************************
* Function Name  : GPIO_Toggle_INIT
* Description    : Initializes GPIOA.0
* Input          : None
* Return         : None
*******************************************************************************/
void GPIO_Toggle_INIT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{
	u8 i=0;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);

	printf("GPIO Toggle TEST\r\n");
	GPIO_Toggle_INIT();

	while(1)
  {
		Delay_Ms(250);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i==0) ? (i=Bit_SET):(i=Bit_RESET));
	}
}
