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
* Description    : This function handles analog wathdog exception.
* Input          : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{
	if(ADC_GetITStatus( ADC1, ADC_IT_AWD)){   		
		printf( "Enter AnalogWatchdog Interrupt\r\n" );
	}
	
	ADC_ClearITPendingBit( ADC1, ADC_IT_AWD); 
}


