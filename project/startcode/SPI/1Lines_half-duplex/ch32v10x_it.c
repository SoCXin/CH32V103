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
void SPI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

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
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 exception.
* Input          : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{
#if (SPI_MODE == HOST_MODE)
	if( SPI_I2S_GetITStatus( SPI1, SPI_I2S_IT_TXE ) != RESET )
	{
		SPI_I2S_SendData( SPI1, TxData[Txval++] );
		if( Txval == 18 )
		{
			SPI_I2S_ITConfig( SPI1, SPI_I2S_IT_TXE , DISABLE );
		}
	}

#elif (SPI_MODE == SLAVE_MODE)
	RxData[Rxval++] = SPI_I2S_ReceiveData( SPI1 );

#endif
}


