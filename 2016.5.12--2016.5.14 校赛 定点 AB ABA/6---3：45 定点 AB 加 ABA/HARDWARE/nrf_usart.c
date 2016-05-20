#include "nrf_usart.h"

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

void NRF_UART_SetValue8(uint8_t Data)//无线串口发送数据 8位
{
   while (USART_GetFlagStatus(NRF_USART, USART_FLAG_TC) == RESET);
	 USART_SendData(NRF_USART, (uint8_t) Data);
}

void NRF_UART_SetValue16(uint16_t Data)//数据串口发送数据 16位
{
   while (USART_GetFlagStatus(NRF_USART, USART_FLAG_TC) == RESET);
	 USART_SendData(NRF_USART, (uint8_t)Data&0xFF);
   while (USART_GetFlagStatus(NRF_USART, USART_FLAG_TC) == RESET);
	 USART_SendData(NRF_USART, (uint8_t)(Data>>8));
}
void NRF_UART_SetValue32(uint32_t Data)//数据串口发送数据 32位
{
   while (USART_GetFlagStatus(NRF_USART, USART_FLAG_TC) == RESET);
	 USART_SendData(NRF_USART, (uint8_t)Data&0xFF);
   while (USART_GetFlagStatus(NRF_USART, USART_FLAG_TC) == RESET);
	 USART_SendData(NRF_USART, (uint8_t)(Data>>8)&0xFF);
   while (USART_GetFlagStatus(NRF_USART, USART_FLAG_TC) == RESET);
	 USART_SendData(NRF_USART, (uint8_t)(Data>>16)&0xFF);
   while (USART_GetFlagStatus(NRF_USART, USART_FLAG_TC) == RESET);
	 USART_SendData(NRF_USART, (uint8_t)(Data>>24));
}

void NRF_UART_SetData(uint8_t* P_Data,uint32_t Count) //无线串口发送数组数据
{
   uint32_t i=0;
   for(i=0;i<Count;i++)
	{
		while (USART_GetFlagStatus(NRF_USART, USART_FLAG_TC) == RESET);
		USART_SendData(NRF_USART, (uint8_t)*P_Data++);
	}
}
void send()
{
	NRF_USART_RST_L;
	delay_ms(100);
	NRF_USART_RST_H;
	delay_ms(100);
	NRF_USART_RST_H;
	delay_ms(100);
	NRF_UART_SetValue8(0x05); 
	NRF_UART_SetValue8(0x04); 
	NRF_UART_SetValue8(0x03); 
	NRF_UART_SetValue8(0x02);
	NRF_UART_SetValue8(0x01); 
	NRF_UART_SetValue32(NRF_USARTBaud);
	NRF_UART_SetValue32(NRF_Delay_Us);
	NRF_UART_SetValue16(100000);
	NRF_UART_SetValue8(DataNum);
	NRF_UART_SetValue8(Par_Num);
	NRF_UART_SetValue8(NRF_CHANAL);
	delay_ms(100);
}

