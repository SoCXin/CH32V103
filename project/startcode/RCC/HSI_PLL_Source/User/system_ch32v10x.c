/********************************** (C) COPYRIGHT *******************************
* File Name          : system_ch32v10x.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : CH32V10x Device Peripheral Access Layer System Source File.
*********************************************************************************/
#include "ch32v10x.h" 

/* 
* Uncomment the line corresponding to the desired System clock (SYSCLK) frequency (after 
*/

//#define SYSCLK_FREQ_24MHz  24000000
//#define SYSCLK_FREQ_48MHz  48000000
#define SYSCLK_FREQ_72MHz  72000000

/* Clock Definitions */
#ifdef SYSCLK_FREQ_24MHz
  uint32_t SystemCoreClock         = SYSCLK_FREQ_24MHz;        /* System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_48MHz
  uint32_t SystemCoreClock         = SYSCLK_FREQ_48MHz;        /* System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_72MHz
  uint32_t SystemCoreClock         = SYSCLK_FREQ_72MHz;        /* System Clock Frequency (Core Clock) */
#endif

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};


/* ch32v10x_system_private_function_proto_types */
static void SetSysClock(void);

#ifdef SYSCLK_FREQ_24MHz
  static void SetSysClockTo24(void);
#elif defined SYSCLK_FREQ_48MHz
  static void SetSysClockTo48(void);
#elif defined SYSCLK_FREQ_72MHz
  static void SetSysClockTo72(void);
#endif


/******************************************************************************************
* Function Name  : SystemInit
* Description    : Setup the microcontroller system Initialize the Embedded Flash Interface, 
*                  the PLL and update the SystemCoreClock variable.
* Input          : None
* Return         : None
*******************************************************************************************/
void SystemInit (void)
{
  RCC->CTLR |= (uint32_t)0x00000001;
  RCC->CFGR0 &= (uint32_t)0xF8FF0000;
  RCC->CTLR &= (uint32_t)0xFEF6FFFF;
  RCC->CTLR &= (uint32_t)0xFFFBFFFF;
  RCC->CFGR0 &= (uint32_t)0xFF80FFFF;
  RCC->INTR = 0x009F0000;    
  SetSysClock();
}


/******************************************************************************************
* Function Name  : SystemCoreClockUpdate
* Description    : Update SystemCoreClock variable according to Clock Register Values.
* Input          : None
* Return         : None
*******************************************************************************************/
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0;
	
  tmp = RCC->CFGR0 & RCC_SWS;
  
  switch (tmp)
  {
    case 0x00:
      SystemCoreClock = HSI_VALUE;
      break;
    case 0x04:  
      SystemCoreClock = HSE_VALUE;
      break;
    case 0x08: 
      pllmull = RCC->CFGR0 & RCC_PLLMULL;
      pllsource = RCC->CFGR0 & RCC_PLLSRC; 
      pllmull = ( pllmull >> 18) + 2;
      if (pllsource == 0x00)
      {
        if(EXTEN->EXTEN_CTR & EXTEN_PLL_HSI_PRE){
        SystemCoreClock = (HSI_VALUE) * pllmull;
        }
        else{
        SystemCoreClock = (HSI_VALUE >>1) * pllmull;
        }
      }
      else
      {    
        if ((RCC->CFGR0 & RCC_PLLXTPRE) != (uint32_t)RESET)
        {
          SystemCoreClock = (HSE_VALUE >> 1) * pllmull;
        }
        else
        {
          SystemCoreClock = HSE_VALUE * pllmull;
        }
      }
      break;
    default:
      SystemCoreClock = HSI_VALUE;
      break;
  }
 
  tmp = AHBPrescTable[((RCC->CFGR0 & RCC_HPRE) >> 4)];
  SystemCoreClock >>= tmp;  
}


/******************************************************************************************
* Function Name  : SetSysClock
* Description    : Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers. 
* Input          : None
* Return         : None
*******************************************************************************************/
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_24MHz
  SetSysClockTo24();
#elif defined SYSCLK_FREQ_48MHz
  SetSysClockTo48();
#elif defined SYSCLK_FREQ_72MHz
  SetSysClockTo72();
#endif
}


#ifdef SYSCLK_FREQ_24MHz

/******************************************************************************************
* Function Name  : SetSysClockTo24
* Description    : Sets System clock frequency to 24MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
* Input          : None
* Return         : None
*******************************************************************************************/
static void SetSysClockTo24(void)
{

#if (PLL_Source == HSI)
  EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;

#endif

    /* Enable Prefetch Buffer */
    FLASH->ACTLR |= FLASH_ACTLR_PRFTBE;

    /* Flash 0 wait state */
    FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
    FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_0;    

    /* HCLK = SYSCLK */
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;   
    /* PCLK2 = HCLK */
    RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1; 
    /* PCLK1 = HCLK */
    RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV1;

    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));

#if (PLL_Source == HSI)
    /*  PLL configuration: PLLCLK = HSI * 3 = 48 MHz */
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL3);

#else
  /*  PLL configuration: PLLCLK = HSI/2 * 6 = 48 MHz */
  RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL6);

#endif

    /* Enable PLL */
    RCC->CTLR |= RCC_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CTLR & RCC_PLLRDY) == 0)
    {
    }
    /* Select PLL as system clock source */
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;    
    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08)
    {
    }
}


#elif defined SYSCLK_FREQ_48MHz

/******************************************************************************************
* Function Name  : SetSysClockTo48
* Description    : Sets System clock frequency to 48MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
* Input          : None
* Return         : None
*******************************************************************************************/
static void SetSysClockTo48(void)
{

#if (PLL_Source == HSI)
  EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;

#endif
    /* Enable Prefetch Buffer */
    FLASH->ACTLR |= FLASH_ACTLR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
    FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_1;    

    /* HCLK = SYSCLK */
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;    
    /* PCLK2 = HCLK */
    RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;  
    /* PCLK1 = HCLK */
    RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;

    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));

#if (PLL_Source == HSI)
    /*  PLL configuration: PLLCLK = HSI * 6 = 48 MHz */
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL6);

#else
  /*  PLL configuration: PLLCLK = HSI/2 * 12 = 48 MHz */
  RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL12);
  
#endif
    /* Enable PLL */
    RCC->CTLR |= RCC_PLLON;
    /* Wait till PLL is ready */
    while((RCC->CTLR & RCC_PLLRDY) == 0)
    {
    }
    /* Select PLL as system clock source */
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;    
    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08)
    {
    }
}

#elif defined SYSCLK_FREQ_72MHz

/******************************************************************************************
* Function Name  : SetSysClockTo72
* Description    : Sets System clock frequency to 72MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
* Input          : None
* Return         : None
*******************************************************************************************/
static void SetSysClockTo72(void)
{

#if (PLL_Source == HSI)
  EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;

#endif
    /* Enable Prefetch Buffer */
    FLASH->ACTLR |= FLASH_ACTLR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
    FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_2;    

    /* HCLK = SYSCLK */
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1; 
    /* PCLK2 = HCLK */
    RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1; 
    /* PCLK1 = HCLK */
    RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;


    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE |
                                                                            RCC_PLLMULL));

    /*  PLL configuration: PLLCLK = HSI * 9 = 72 MHz */
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL9);

    /* Enable PLL */
    RCC->CTLR |= RCC_PLLON;
    /* Wait till PLL is ready */
    while((RCC->CTLR & RCC_PLLRDY) == 0)
    {
    }    
    /* Select PLL as system clock source */
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;    
    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08)
    {
    }
}
#endif



    
