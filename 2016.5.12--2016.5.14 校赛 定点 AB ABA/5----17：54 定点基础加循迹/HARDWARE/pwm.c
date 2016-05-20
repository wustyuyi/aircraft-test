#include "pwm.h"

void Pwm_Gpio_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  /* GPIOD Configuration: TIM4 CH1 (PD12), TIM4 CH2 (PD13), TIM4 CH3 (PD14) and TIM4 CH4 (PD15) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure); 

  /* Connect TIM4 pins to AF2 */  
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4); 
}

void MotoPwm_Init(void)
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	uint16_t PrescalerValue = 0;
  /* TIM Configuration */
  Pwm_Gpio_Init();
  
	  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
  RCC_TIMCLKPresConfig(RCC_TIMPrescActivated);	//将定时器的时钟加倍 由默认90M->180M

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1; //SystemCoreClock = 180M

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 5000-1;			// 自动重载值 5000
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;	//预分频值 PrescalerValue = 180-1  180M/180 = 1M pwm频率 1M / 5000 =200Hz 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; 		//
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //pwm调制模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //比较输出使能
  TIM_OCInitStructure.TIM_Pulse = 1000;	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//	输出极性高

  TIM_OC1Init(TIM4, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1000;

  TIM_OC2Init(TIM4, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1000;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1000;

  TIM_OC4Init(TIM4, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM4->EGR|=TIM_EGR_UG;
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);
	
	Moto_PwmUpdate(0,0,0,0);
}

void Moto_PwmUpdate(uint16_t MOTO1_PWM, uint16_t MOTO2_PWM, uint16_t MOTO3_PWM, uint16_t MOTO4_PWM)
{
	TIM_SetCompare1(TIM4, MOTO3_PWM+1000);	
	TIM_SetCompare2(TIM4, MOTO4_PWM+1000);	
	TIM_SetCompare3(TIM4, MOTO2_PWM+1000);	
	TIM_SetCompare4(TIM4, MOTO1_PWM+1000);
}

void PWM_IT_ENABLE(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;   
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


