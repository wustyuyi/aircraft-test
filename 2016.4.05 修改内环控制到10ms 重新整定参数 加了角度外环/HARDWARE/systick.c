/**
  ******************************************************************************
  * @file    Project/User/systick.c 
  * @author  yeyinglong
  * @version V1.3.0
  * @date    11-4-2015
  * @brief   something about time
  ******************************************************************************/
	
	
/* Includes ------------------------------------------------------------------*/
#include "systick.h"
#include "stm32f4xx_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint32_t SystemCoreClock; 
static volatile uint32_t g_ul_ms_ticks=0;
static volatile uint32_t TimingDelay=0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


void SysTick_init(void)
{
	if (SysTick_Config (SystemCoreClock / TICK_FREQ)) {     // Setup SysTick Timer for 1 msec interrupts
		while (1);                                          // Handle Error
	}
}
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void delay_ms(unsigned long nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in us.
  * @retval None
  */
void delay_us(unsigned long nTime)
{
	u8 j;
	while(nTime--)
	for(j=0;j<45;j++);
}

unsigned long get_tick_count(unsigned long *count)
{
  count[0] = g_ul_ms_ticks;
	return 0;
}

unsigned long get_timer(void)
{
	return(g_ul_ms_ticks);
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  if (TimingDelay != 0x00)
		TimingDelay--;
  g_ul_ms_ticks++;
}

