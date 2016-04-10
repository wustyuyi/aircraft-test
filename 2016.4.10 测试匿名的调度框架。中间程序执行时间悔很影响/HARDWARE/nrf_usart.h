#ifndef __NRF_USART_H
#define __NRF_USART_H

#include "sys.h"

/* Definition for NRF_USART resources ******************************************/
#define NRF_USART                           USART2
#define NRF_USART_CLK                       RCC_APB1Periph_USART2
#define NRF_USART_CLK_INIT                  RCC_APB1PeriphClockCmd
#define NRF_USART_IRQn                      USART2_IRQn
#define NRF_USART_IRQHandler                USART2_IRQHandler

#define NRF_USART_TX_PIN                    GPIO_Pin_2                
#define NRF_USART_TX_GPIO_PORT              GPIOA                      
#define NRF_USART_TX_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define NRF_USART_TX_SOURCE                 GPIO_PinSource2
#define NRF_USART_TX_AF                     GPIO_AF_USART2

#define NRF_USART_RX_PIN                    GPIO_Pin_3       
#define NRF_USART_RX_GPIO_PORT              GPIOA     
#define NRF_USART_RX_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define NRF_USART_RX_SOURCE                 GPIO_PinSource3
#define NRF_USART_RX_AF                     GPIO_AF_USART2
/* Definition for for commond pin resources ********************************************/
#define NRF_USART_RST_PIN                   GPIO_Pin_0
#define NRF_USART_RST_PORT              		GPIOD
#define NRF_USART_RST_CLK               		RCC_AHB1Periph_GPIOD
#define NRF_USART_RST_SOURCE                GPIO_PinSource0

/* Definition for for commond pin resources ********************************************/
#define NRF_USART_RST_H 										NRF_USART_RST_PORT->BSRRL=NRF_USART_RST_PIN
#define NRF_USART_RST_L 										NRF_USART_RST_PORT->BSRRH=NRF_USART_RST_PIN



#define NRF_CHANAL     110
#define NRF_USARTBaud  4500000
#define NRF_Delay_Us   1

#define DataNum       2
#define Par_Num						4



void NRF_USART_Config(void);
void NRF_UART_SetValue8(uint8_t Data);
void NRF_UART_SetValue16(uint16_t Data);
void NRF_UART_SetValue32(uint32_t Data);
void NRF_UART_SetData(uint8_t* P_Data,uint32_t Count);
void send(void);




#endif
