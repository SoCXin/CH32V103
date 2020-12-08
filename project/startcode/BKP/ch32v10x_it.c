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
void TAMPER_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

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
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
  if( BKP_GetITStatus() == SET )
	{
		printf("TAMPER_IRQHandler\r\n");
		printf( "BKP_DR1:%08x\r\n", BKP->DATAR1 );
	  printf( "BKP_DR2:%08x\r\n", BKP->DATAR2 );
	  printf( "BKP_DR3:%08x\r\n", BKP->DATAR3 );
    printf( "BKP_DR4:%08x\r\n", BKP->DATAR4 );
	}

	BKP_ClearITPendingBit();
}



