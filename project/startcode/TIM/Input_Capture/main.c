/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/
#include "debug.h"

/*******************************************************************************
* Function Name  : Input_Capture_Init
* Description    : Initializes TIM1 input capture.
* Input          : arr: the period value.
*                  psc: the prescaler value.
*									 ccp: the pulse value.
* Return         : None
*******************************************************************************/
void Input_Capture_Init( u16 arr, u16 psc )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits( GPIOA, GPIO_Pin_8 );

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter =  0x00;
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;

	TIM_PWMIConfig( TIM1, &TIM_ICInitStructure );

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig( TIM1, TIM_IT_CC1 | TIM_IT_CC2, ENABLE );

	TIM_SelectInputTrigger( TIM1, TIM_TS_TI1FP1 );
	TIM_SelectSlaveMode( TIM1, TIM_SlaveMode_Reset );
	TIM_SelectMasterSlaveMode( TIM1, TIM_MasterSlaveMode_Enable );
	TIM_Cmd( TIM1, ENABLE );
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);

  Input_Capture_Init( 0xFFFF, 48000-1 );

	while(1);
}
