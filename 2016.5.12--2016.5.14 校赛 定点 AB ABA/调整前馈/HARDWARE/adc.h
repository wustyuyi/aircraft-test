#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"

  #define ADCx                     ADC1
  #define ADCx_CLK                 RCC_APB2Periph_ADC1
  #define DMA_CHANNELx             DMA_Channel_0
  #define DMA_STREAMx              DMA2_Stream0
  #define ADCx_DR_ADDRESS          ((uint32_t)0x4001204C)
	#define ADCx_CHANNEL_GPIO_CLK    RCC_AHB1Periph_GPIOC
  #define GPIO_PIN                 GPIO_Pin_3
  #define GPIO_PORT                GPIOC

extern __IO uint16_t uhADCConvertedValue;
extern __IO uint32_t uwVBATVoltage;

void ADC_Config(void);

#endif //__ADC_H
