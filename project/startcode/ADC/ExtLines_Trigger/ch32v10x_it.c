/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32v10x_it.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main Interrupt Service Routines.
*******************************************************************************/
#include "ch32v10x_it.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void ADC1_2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles analog watchdog exception.
* Input          : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler()
{
	u16 ADC_val;

	if(ADC_GetITStatus( ADC1, ADC_IT_JEOC)){
		printf("ADC Extline trigger conversion...\r\n");
		ADC_val = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
		printf( "JADC%04d\r\n", ADC_val );
	}

	ADC_ClearITPendingBit( ADC1, ADC_IT_JEOC);
}


