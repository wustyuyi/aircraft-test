#include "usart_dma.h"
#include "systick.h"

uint8_t aTxBuffer[TX_BUF_SIZE];
uint8_t aRxBuffer [RX_BUF_SIZE];

void NRF_USART_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(NRF_USART_TX_GPIO_CLK | NRF_USART_RX_GPIO_CLK, ENABLE);
  
  /* Enable USART clock */
  NRF_USART_CLK_INIT(NRF_USART_CLK, ENABLE);
  
  /* NRF_USART GPIO configuration -----------------------------------------------*/ 
  /* Connect USART pins to AF7 */
  GPIO_PinAFConfig(NRF_USART_TX_GPIO_PORT, NRF_USART_TX_SOURCE, NRF_USART_TX_AF);
  GPIO_PinAFConfig(NRF_USART_RX_GPIO_PORT, NRF_USART_RX_SOURCE, NRF_USART_RX_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  
	GPIO_InitStructure.GPIO_Pin = NRF_USART_TX_PIN;
	GPIO_Init(NRF_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = NRF_USART_RX_PIN;
	GPIO_Init(NRF_USART_RX_GPIO_PORT, &GPIO_InitStructure);
 
  USART_InitStructure.USART_BaudRate =  9600;//115200;460800;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* When using Parity the word length must be configured to 9 bits */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(NRF_USART, &USART_InitStructure);
  USART_ITConfig(NRF_USART, USART_IT_RXNE, ENABLE);

  /* Enable USART */
  USART_Cmd(NRF_USART, ENABLE);
}

void NRF_USART_DMA_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(NRF_USART_TX_GPIO_CLK | NRF_USART_RX_GPIO_CLK, ENABLE);
  
  /* Enable USART clock */
  NRF_USART_CLK_INIT(NRF_USART_CLK, ENABLE);
  
  /* Enable the DMA clock */
  RCC_AHB1PeriphClockCmd(NRF_USART_DMAx_CLK, ENABLE);
  
  /* NRF_USART GPIO configuration -----------------------------------------------*/ 
  /* Connect USART pins to AF7 */
  GPIO_PinAFConfig(NRF_USART_TX_GPIO_PORT, NRF_USART_TX_SOURCE, NRF_USART_TX_AF);
  GPIO_PinAFConfig(NRF_USART_RX_GPIO_PORT, NRF_USART_RX_SOURCE, NRF_USART_RX_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  
  GPIO_InitStructure.GPIO_Pin = NRF_USART_TX_PIN;
  GPIO_Init(NRF_USART_TX_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = NRF_USART_RX_PIN;
  GPIO_Init(NRF_USART_RX_GPIO_PORT, &GPIO_InitStructure);
 
  /* NRF_USART configuration ----------------------------------------------------*/
  /* Enable the USART OverSampling by 8 */
  USART_OverSampling8Cmd(NRF_USART, ENABLE); 
  
  /* NRF_USART configured as follows:
        - BaudRate = 5250000 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		     is: (USART APB Clock / 8) 
			 Example: 
			    - (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
			    - (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 16
		     is: (USART APB Clock / 16) 
			 Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
			 Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
        - Word Length = 8 Bits
        - one Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */ 
  USART_InitStructure.USART_BaudRate = 4500000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* When using Parity the word length must be configured to 9 bits */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(NRF_USART, &USART_InitStructure);

  /* Configure DMA controller to manage USART TX and RX DMA request ----------*/ 
   
  /* Configure DMA Initialization Structure */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(NRF_USART->DR)) ;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  /* Configure TX DMA */
  DMA_InitStructure.DMA_BufferSize = TX_BUF_SIZE;
  DMA_InitStructure.DMA_Channel = NRF_USART_TX_DMA_CHANNEL ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)aTxBuffer ;
  DMA_Init(NRF_USART_TX_DMA_STREAM,&DMA_InitStructure);
  /* Configure RX DMA */
  DMA_InitStructure.DMA_BufferSize = RX_BUF_SIZE;
  DMA_InitStructure.DMA_Channel = NRF_USART_RX_DMA_CHANNEL ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)aRxBuffer ; 
  DMA_Init(NRF_USART_RX_DMA_STREAM,&DMA_InitStructure);
         
  /* Enable USART */
  USART_Cmd(NRF_USART, ENABLE);
}

void NRF_USART_DMA_Send(uint16_t count)
{
  /* Clear DMA Transfer Complete Flags */
  DMA_ClearFlag(NRF_USART_TX_DMA_STREAM,NRF_USART_TX_DMA_FLAG_TCIF);
	
	DMA_SetCurrDataCounter(NRF_USART_TX_DMA_STREAM,count);
	/* Enable DMA USART TX Stream */
  DMA_Cmd(NRF_USART_TX_DMA_STREAM,ENABLE);
	/* Enable USART DMA TX Requsts */
  USART_DMACmd(NRF_USART, USART_DMAReq_Tx, ENABLE);
}

void NRF_USART_DMA_Receive(uint16_t count)
{      
  /* Clear DMA Transfer Complete Flags */
  DMA_ClearFlag(NRF_USART_RX_DMA_STREAM,NRF_USART_RX_DMA_FLAG_TCIF);
	
	DMA_SetCurrDataCounter(NRF_USART_RX_DMA_STREAM,count);
	/* Enable DMA USART RX Stream */
  DMA_Cmd(NRF_USART_RX_DMA_STREAM,ENABLE);
  
  /* Enable USART DMA RX Requsts */
  USART_DMACmd(NRF_USART, USART_DMAReq_Rx, ENABLE);
}

uint8_t Get_NRF_UART_SET_DMA_State(void)
{
	return (DMA_GetFlagStatus(NRF_USART_TX_DMA_STREAM,NRF_USART_TX_DMA_FLAG_TCIF)==SET);	
}

uint8_t Get_NRF_UART_GET_DMA_State(void)
{
	return (DMA_GetFlagStatus(NRF_USART_RX_DMA_STREAM,NRF_USART_RX_DMA_FLAG_TCIF)==SET);
}

///////////////////////////////////////////////////////////////////////////////

uint8_t CAM_TxBuffer[TX_BUF_SIZE];
uint8_t CAM_RxBuffer[632];

void CAM_USART_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAM_USART_TX_GPIO_CLK | CAM_USART_RX_GPIO_CLK, ENABLE);
  
  /* Enable USART clock */
  CAM_USART_CLK_INIT(CAM_USART_CLK, ENABLE);
  
  /* CAM_USART GPIO configuration -----------------------------------------------*/ 
  /* Connect USART pins to AF7 */
  GPIO_PinAFConfig(CAM_USART_TX_GPIO_PORT, CAM_USART_TX_SOURCE, CAM_USART_TX_AF);
  GPIO_PinAFConfig(CAM_USART_RX_GPIO_PORT, CAM_USART_RX_SOURCE, CAM_USART_RX_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  
	GPIO_InitStructure.GPIO_Pin = CAM_USART_TX_PIN;
	GPIO_Init(CAM_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = CAM_USART_RX_PIN;
	GPIO_Init(CAM_USART_RX_GPIO_PORT, &GPIO_InitStructure);
 
  USART_InitStructure.USART_BaudRate =  9600;//115200;460800;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* When using Parity the word length must be configured to 9 bits */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(CAM_USART, &USART_InitStructure);
  USART_ITConfig(CAM_USART, USART_IT_RXNE, ENABLE);

  /* Enable USART */
  USART_Cmd(CAM_USART, ENABLE);
}

void CAM_USART_DMA_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAM_USART_TX_GPIO_CLK | CAM_USART_RX_GPIO_CLK, ENABLE);
  
  /* Enable USART clock */
  CAM_USART_CLK_INIT(CAM_USART_CLK, ENABLE);
  
  /* Enable the DMA clock */
  RCC_AHB1PeriphClockCmd(CAM_USART_DMAx_CLK, ENABLE);
  
  /* CAM_USART GPIO configuration -----------------------------------------------*/ 
  /* Connect USART pins to AF7 */
  GPIO_PinAFConfig(CAM_USART_TX_GPIO_PORT, CAM_USART_TX_SOURCE, CAM_USART_TX_AF);
  GPIO_PinAFConfig(CAM_USART_RX_GPIO_PORT, CAM_USART_RX_SOURCE, CAM_USART_RX_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  
  GPIO_InitStructure.GPIO_Pin = CAM_USART_TX_PIN;
  GPIO_Init(CAM_USART_TX_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = CAM_USART_RX_PIN;
  GPIO_Init(CAM_USART_RX_GPIO_PORT, &GPIO_InitStructure);
 
  /* CAM_USART configuration ----------------------------------------------------*/
  /* Enable the USART OverSampling by 8 */
  USART_OverSampling8Cmd(CAM_USART, ENABLE); 
  
  /* CAM_USART configured as follows:
        - BaudRate = 5250000 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		     is: (USART APB Clock / 8) 
			 Example: 
			    - (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
			    - (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 16
		     is: (USART APB Clock / 16) 
			 Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
			 Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
        - Word Length = 8 Bits
        - one Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */ 
  USART_InitStructure.USART_BaudRate = 2625000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* When using Parity the word length must be configured to 9 bits */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(CAM_USART, &USART_InitStructure);

  /* Configure DMA controller to manage USART TX and RX DMA request ----------*/ 
   
  /* Configure DMA Initialization Structure */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(CAM_USART->DR)) ;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  /* Configure TX DMA */
  DMA_InitStructure.DMA_BufferSize = TX_BUF_SIZE;
  DMA_InitStructure.DMA_Channel = CAM_USART_TX_DMA_CHANNEL ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)CAM_TxBuffer ;
  DMA_Init(CAM_USART_TX_DMA_STREAM,&DMA_InitStructure);
  /* Configure RX DMA */
  DMA_InitStructure.DMA_BufferSize = RX_BUF_SIZE;
  DMA_InitStructure.DMA_Channel = CAM_USART_RX_DMA_CHANNEL ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)CAM_RxBuffer ; 
  DMA_Init(CAM_USART_RX_DMA_STREAM,&DMA_InitStructure);
	
  NVIC_InitStructure.NVIC_IRQChannel = CAM_USART_DMA_TX_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	/* Enable DMA Stream Transfer Complete interrupt */
	DMA_ITConfig(CAM_USART_TX_DMA_STREAM, DMA_IT_TC, ENABLE); 
  /* Enable USART */
  USART_Cmd(CAM_USART, ENABLE);
}

void CAM_USART_DMA_Send(uint16_t count)
{
  /* Clear DMA Transfer Complete Flags */
  DMA_ClearFlag(CAM_USART_TX_DMA_STREAM,CAM_USART_TX_DMA_FLAG_TCIF);
	
	DMA_SetCurrDataCounter(CAM_USART_TX_DMA_STREAM,count);
	/* Enable DMA USART TX Stream */
  DMA_Cmd(CAM_USART_TX_DMA_STREAM,ENABLE);
	/* Enable USART DMA TX Requsts */
  USART_DMACmd(CAM_USART, USART_DMAReq_Tx, ENABLE);
}

void CAM_USART_DMA_Receive(uint16_t count)
{      
  /* Clear DMA Transfer Complete Flags */
  DMA_ClearFlag(CAM_USART_RX_DMA_STREAM,CAM_USART_RX_DMA_FLAG_TCIF);
	
	DMA_SetCurrDataCounter(CAM_USART_RX_DMA_STREAM,count);
	/* Enable DMA USART RX Stream */
  DMA_Cmd(CAM_USART_RX_DMA_STREAM,ENABLE);
  
  /* Enable USART DMA RX Requsts */
  USART_DMACmd(CAM_USART, USART_DMAReq_Rx, ENABLE);
}

void Clear_FLAG_TCIF(void)
{	
  /* Clear DMA Transfer Complete Flags */
  DMA_ClearFlag(CAM_USART_RX_DMA_STREAM,CAM_USART_RX_DMA_FLAG_TCIF);
}

uint8_t Get_CAM_UART_SET_DMA_State(void)
{
	return (DMA_GetFlagStatus(CAM_USART_TX_DMA_STREAM,CAM_USART_TX_DMA_FLAG_TCIF)==SET);	
}

uint8_t Get_CAM_UART_GET_DMA_State(void)
{
	return (DMA_GetFlagStatus(CAM_USART_RX_DMA_STREAM,CAM_USART_RX_DMA_FLAG_TCIF)==SET);
}


