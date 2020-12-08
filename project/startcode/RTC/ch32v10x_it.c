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
void RTC_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

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
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC Handler.
* Input          : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)   /* Seconds interrupt */
	{
    RTC_Get();
 	}
	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)     /* Alarm clock interrupt */
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);
    RTC_Get();
  }

	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);
	RTC_WaitForLastTask();
}


/*******************************************************************************
* Function Name  : RVNVIC_INTCFG
* Description    : Set Fast Interrupt and Set Interrupt Priority.
* Input          : None
* Return         : None
*******************************************************************************/
void RVNVIC_INTCFG(void)
{
  /* Set Fast Interrupt */

  /* Set Interrupt Priority */

}

