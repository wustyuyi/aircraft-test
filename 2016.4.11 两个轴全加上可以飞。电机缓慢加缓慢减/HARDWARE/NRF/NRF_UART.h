#ifndef _nrf_uart_H
#define _nrf_uart_H

#include "stm32f4xx.h"
#include "data_sent.h"

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

/* Definition for for commond pin resources ********************************************/
#define NRF_USART_RST_PIN                   GPIO_Pin_0
#define NRF_USART_RST_PORT              		GPIOD
#define NRF_USART_RST_CLK               		RCC_AHB1Periph_GPIOD
#define NRF_USART_RST_SOURCE                GPIO_PinSource0

#define NRF_USART_BACK_PIN                  GPIO_Pin_1
#define NRF_USART_BACK_PORT              		GPIOA
#define NRF_USART_BACK_CLK               		RCC_AHB1Periph_GPIOA
#define NRF_USART_BACK_SOURCE               GPIO_PinSource1

#define NRF_UART_C0_PIN                     GPIO_Pin_1
#define NRF_UART_C0_PORT                		GPIOD
#define NRF_UART_C0_CLK                 		RCC_AHB1Periph_GPIOD
#define NRF_UART_C0_SOURCE                  GPIO_PinSource1

#define NRF_UART_C1_PIN                     GPIO_Pin_2
#define NRF_UART_C1_PORT                		GPIOD
#define NRF_UART_C1_CLK                 		RCC_AHB1Periph_GPIOD
#define NRF_UART_C1_SOURCE                  GPIO_PinSource2

#define NRF_UART_C2_PIN                     GPIO_Pin_3
#define NRF_UART_C2_PORT                		GPIOD
#define NRF_UART_C2_CLK                 		RCC_AHB1Periph_GPIOD
#define NRF_UART_C2_SOURCE                  GPIO_PinSource3

#define NRF_UART_C3_PIN                     GPIO_Pin_0
#define NRF_UART_C3_PORT                		GPIOA
#define NRF_UART_C3_CLK                 		RCC_AHB1Periph_GPIOA
#define NRF_UART_C3_SOURCE                  GPIO_PinSource0

#define NRF_USART_RST_H 										NRF_USART_RST_PORT->BSRRL=NRF_USART_RST_PIN
#define NRF_USART_RST_L 										NRF_USART_RST_PORT->BSRRH=NRF_USART_RST_PIN

#define NRF_USART_BACK_H 										NRF_USART_BACK_PORT->BSRRL=NRF_USART_BACK_PIN
#define NRF_USART_BACK_L 										NRF_USART_BACK_PORT->BSRRH=NRF_USART_BACK_PIN

/***************************通讯指令定义********************************/
#define  Waitting               0x00    //等待
#define  Write_Data             0x01    //输出数据
#define  Read_Par               0x02    //读入参数
#define  InitParLen             0x03    //初始化参数  
#define  Write_Par              0x04    //输出参数信息
#define  Stop_Car               0x05    //停车
#define  UcStop_Car             0x06    //自定义停车
#define  Command7               0x07    //
#define  Command8               0x08    //
#define  Command9               0x09    //
#define  Command10              0x0A    //
#define  Command11              0x0B    //
#define  Command12              0x0C    //
#define  Command13              0x0D    //
#define  Command14              0x0E    //
#define  Command15              0x0F    //

void NRF_Usart_Pin_Init(void);
void NRF_Read_Live_Init(void);
void NRF_UART_Connect(void);

#endif

