/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/

/*
 *@Note
 TouchKey检测例程：
 本例程演示 通道2(PA2)，做 Touchkey 应用。
 
*/

#include "debug.h"

/* Global define */
#define TKEY_CR   ADC1->CTLR1
#define TKEY_CH   ADC1->RSQR3
#define TKEY_SR   ADC1->RDATAR


/*******************************************************************************
* Function Name  : Touch_Key_Init
* Description    : Initializes Touch Key collection.
* Input          : None
* Return         : None
*******************************************************************************/
void Touch_Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_Cmd(ADC1, ENABLE);

	TKEY_CR |= 0x51000000;   // Enable TouchKey
}

/*******************************************************************************
* Function Name  : Touch_Key_Adc
* Description    : Returns ADCx conversion result data.
* Input          : ch: ADC channel.
*                    ADC_Channel_0: ADC Channel0 selected.
*                    ADC_Channel_1: ADC Channel1 selected.
*                    ADC_Channel_2: ADC Channel2 selected.
*                    ADC_Channel_3: ADC Channel3 selected.
*                    ADC_Channel_4: ADC Channel4 selected.
*                    ADC_Channel_5: ADC Channel5 selected.
*                    ADC_Channel_6: ADC Channel6 selected.
*                    ADC_Channel_7: ADC Channel7 selected.
*                    ADC_Channel_8: ADC Channel8 selected.
*                    ADC_Channel_9: ADC Channel9 selected.
*                    ADC_Channel_10: ADC Channel10 selected.
*                    ADC_Channel_11: ADC Channel11 selected.
*                    ADC_Channel_12: ADC Channel12 selected.
*                    ADC_Channel_13: ADC Channel13 selected.
*                    ADC_Channel_14: ADC Channel14 selected.
*                    ADC_Channel_15: ADC Channel15 selected.
* Return         : val: The Data conversion value.
*******************************************************************************/
u16 Touch_Key_Adc(u8 ch)
{
  u16 val;

  TKEY_CH =ch;     // TouchKey Channel

  while(!(TKEY_CR & 0x08000000));
  val = (u16)TKEY_SR;

	return val;
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{
	u16 ADC_val;

	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);

	Touch_Key_Init();

	while(1)
	{
		ADC_val = Touch_Key_Adc(ADC_Channel_2);
		printf( "TouchKey:%04d\r\n",  ADC_val );

		if(ADC_val & 0x8000)
		{
			printf("This value is discarded\r\n");
		}

		TKEY_CR |=0x08000000;  //Clear Flag
	}
}
