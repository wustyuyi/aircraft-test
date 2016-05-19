#ifndef __USART_DMA_H
#define __USART_DMA_H

#include "stm32f4xx.h"

#define TX_BUF_SIZE 1024
#define RX_BUF_SIZE 128

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

/* Definition for DMAx resources ********************************************/
#define NRF_USART_DR_ADDRESS                ((uint32_t)USART2 + 0x04) 

#define NRF_USART_DMA                       DMA1
#define NRF_USART_DMAx_CLK                  RCC_AHB1Periph_DMA1
	 
#define NRF_USART_TX_DMA_CHANNEL            DMA_Channel_4
#define NRF_USART_TX_DMA_STREAM             DMA1_Stream6
#define NRF_USART_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF6
#define NRF_USART_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF6
#define NRF_USART_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF6
#define NRF_USART_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF6
#define NRF_USART_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF6
						
#define NRF_USART_RX_DMA_CHANNEL            DMA_Channel_4
#define NRF_USART_RX_DMA_STREAM             DMA1_Stream5
#define NRF_USART_RX_DMA_FLAG_FEIF          DMA_FLAG_FEIF5
#define NRF_USART_RX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF5
#define NRF_USART_RX_DMA_FLAG_TEIF          DMA_FLAG_TEIF5
#define NRF_USART_RX_DMA_FLAG_HTIF          DMA_FLAG_HTIF5
#define NRF_USART_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF5

#define NRF_USART_DMA_TX_IRQn               DMA1_Stream6_IRQn
#define NRF_USART_DMA_RX_IRQn               DMA1_Stream5_IRQn
#define NRF_USART_DMA_TX_IRQHandler         DMA1_Stream6_IRQHandler
#define NRF_USART_DMA_RX_IRQHandler         DMA1_Stream5_IRQHandler


extern uint8_t aTxBuffer[TX_BUF_SIZE];
extern uint8_t aRxBuffer [RX_BUF_SIZE];

void NRF_USART_Config(void);
void NRF_USART_DMA_Config(void);
void NRF_USART_DMA_Send(uint16_t count);
void NRF_USART_DMA_Receive(uint16_t count);
uint8_t Get_NRF_UART_SET_DMA_State(void);
uint8_t Get_NRF_UART_GET_DMA_State(void);

///////////////////////////////////////////////////////////////////////////

	
/* Definition for CAM_USART resources ******************************************/
#define CAM_USART                           USART3
#define CAM_USART_CLK                       RCC_APB1Periph_USART3
#define CAM_USART_CLK_INIT                  RCC_APB1PeriphClockCmd
#define CAM_USART_IRQn                      USART3_IRQn
#define CAM_USART_IRQHandler                USART3_IRQHandler

#define CAM_USART_TX_PIN                    GPIO_Pin_8                
#define CAM_USART_TX_GPIO_PORT              GPIOD                 
#define CAM_USART_TX_GPIO_CLK               RCC_AHB1Periph_GPIOD
#define CAM_USART_TX_SOURCE                 GPIO_PinSource8
#define CAM_USART_TX_AF                     GPIO_AF_USART3

#define CAM_USART_RX_PIN                    GPIO_Pin_9              
#define CAM_USART_RX_GPIO_PORT              GPIOD              
#define CAM_USART_RX_GPIO_CLK               RCC_AHB1Periph_GPIOD
#define CAM_USART_RX_SOURCE                 GPIO_PinSource9
#define CAM_USART_RX_AF                     GPIO_AF_USART3

/* Definition for DMAx resources ********************************************/
#define CAM_USART_DR_ADDRESS                ((uint32_t)USART3 + 0x04) 

#define CAM_USART_DMA                       DMA1
#define CAM_USART_DMAx_CLK                  RCC_AHB1Periph_DMA1
	 
#define CAM_USART_TX_DMA_CHANNEL            DMA_Channel_4
#define CAM_USART_TX_DMA_STREAM             DMA1_Stream3
#define CAM_USART_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF3
#define CAM_USART_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF3
#define CAM_USART_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF3
#define CAM_USART_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF3
#define CAM_USART_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF3
						
#define CAM_USART_RX_DMA_CHANNEL            DMA_Channel_4
#define CAM_USART_RX_DMA_STREAM             DMA1_Stream1
#define CAM_USART_RX_DMA_FLAG_FEIF          DMA_FLAG_FEIF1
#define CAM_USART_RX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF1
#define CAM_USART_RX_DMA_FLAG_TEIF          DMA_FLAG_TEIF1
#define CAM_USART_RX_DMA_FLAG_HTIF          DMA_FLAG_HTIF1
#define CAM_USART_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF1

#define CAM_USART_DMA_TX_IRQn               DMA1_Stream3_IRQn
#define CAM_USART_DMA_RX_IRQn               DMA1_Stream1_IRQn
#define CAM_USART_DMA_TX_IRQHandler         DMA1_Stream3_IRQHandler
#define CAM_USART_DMA_RX_IRQHandler         DMA1_Stream1_IRQHandler


extern uint8_t CAM_TxBuffer[TX_BUF_SIZE];
extern uint8_t CAM_RxBuffer [632];

void CAM_USART_Config(void);
void CAM_USART_DMA_Config(void);
void CAM_USART_DMA_Send(uint16_t count);
void CAM_USART_DMA_Receive(uint16_t count);
uint8_t Get_CAM_UART_SET_DMA_State(void);
uint8_t Get_CAM_UART_GET_DMA_State(void);
void Clear_FLAG_TCIF(void);

#endif //__USART_DMA_H
