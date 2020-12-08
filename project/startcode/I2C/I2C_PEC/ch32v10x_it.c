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
void I2C1_ER_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

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
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function IIC PEC error exception.
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void I2C1_ER_IRQHandler(void )
{
	if( I2C_GetITStatus( I2C1, I2C_IT_PECERR ) != RESET )
	{
		printf( "PECEER\r\n" );
		I2C_ClearITPendingBit( I2C1, I2C_IT_PECERR );
	}
}


