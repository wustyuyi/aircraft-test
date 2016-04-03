#include "NRF_UART.h"

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
  USART_InitStructure.USART_BaudRate = NRF_USARTBaud;
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

uint8_t  Get_NRF_UART_Cmd(void)//获取无线射频串口的命令
{
	#ifdef NRF_UART_GCONTINUOUS
	 return (((NRF_UART_C0_PORT->IDR) >>NRF_UART_C0_SOURCE)& 0x0f);
	#else
   return (((NRF_UART_C0_PORT->IDR >> NRF_UART_C0_SOURCE)& 0x01) 
           | (((NRF_UART_C1_PORT->IDR >> NRF_UART_C1_SOURCE)& 0x01)<<1)
           | (((NRF_UART_C2_PORT->IDR >> NRF_UART_C2_SOURCE)& 0x01)<<2)
           | (((NRF_UART_C3_PORT->IDR >> NRF_UART_C3_SOURCE)& 0x01)<<3));
	#endif
}

void NRF_Usart_Pin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(NRF_USART_RST_CLK | NRF_USART_BACK_CLK | NRF_UART_C0_CLK |
													NRF_UART_C1_CLK | NRF_UART_C2_CLK | NRF_UART_C3_CLK, ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_InitStructure.GPIO_Pin = NRF_USART_RST_PIN;
	GPIO_Init(NRF_USART_RST_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = NRF_USART_BACK_PIN;
	GPIO_Init(NRF_USART_BACK_PORT, &GPIO_InitStructure);
	
	NRF_USART_RST_H;
	NRF_USART_BACK_H;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_InitStructure.GPIO_Pin = NRF_UART_C0_PIN;
	GPIO_Init(NRF_UART_C0_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = NRF_UART_C1_PIN;
	GPIO_Init(NRF_UART_C1_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = NRF_UART_C2_PIN;
	GPIO_Init(NRF_UART_C2_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = NRF_UART_C3_PIN;
	GPIO_Init(NRF_UART_C3_PORT, &GPIO_InitStructure);
}

void  NRF_Read_Live_Init(void)
{
	NRF_USART_Config();
	NRF_USART_RST_L;
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
	NRF_UART_SetValue16(Data_All_Length);
	NRF_UART_SetValue8(DataNum);
	NRF_UART_SetValue8(Par_Num);
	NRF_UART_SetValue8(NRF_CHANAL);
	delay_ms(100);
	USART_DeInit(NRF_USART);
	NRF_USART_DMA_Config();
}

void NRF_UART_Connect(void)//数据链接传输
{
  int i;
  static NRF_State State_Flag=Freeing;//状态标记
  static Boolean first_wt_flag=True;//标记位
  uint8_t Command=Get_NRF_UART_Cmd();//获取端口指令
	
  if(State_Flag==Freeing)//当前状态空闲时
  {
    switch(Command)
    {
			case Write_Data://输出数据
			{
				if(Get_NRF_UART_SET_DMA_State() || first_wt_flag)//当前DMA是否空闲
				{				
					 DataLoad();

					 NRF_USART_BACK_L;//反馈总线拉低
				
					 for(i=0;i<80;i++) __NOP() ;//延时
				
					 NRF_USART_BACK_H;//反馈总线拉高

					 first_wt_flag=False;//非第一次通讯

					 NRF_USART_DMA_Send(Data_All_Length);//发送数据包
				}
			}break;
			case Write_Par://输出数据
			{
				NRF_USART_BACK_L;//反馈总线拉低
		
				for(i=0;i<80;i++) __NOP() ;//延时
		
				NRF_USART_BACK_H;//反馈总线拉高
				
			}break;
			case Read_Par://读入数据
			{
				 NRF_USART_DMA_Receive(9);//读取参数
				 for(i=0;i<30;i++) __NOP() ;//延时          
				 NRF_USART_BACK_L;//反馈总线拉低            
				 for(i=0;i<30;i++) __NOP() ;//延时            
				 NRF_USART_BACK_H;//反馈总线拉高
				 State_Flag=Read_Paring;//状态转换为读取数据    
			}break;
			case Stop_Car://读入数据
			{         
					NRF_USART_BACK_L;//反馈总线拉低            
					for(i=0;i<80;i++) __NOP() ;//延时            
					NRF_USART_BACK_H;//反馈总线拉高
						Stop();//停止四轴
					NRF_Read_Live_Init();
			}break;
			case UcStop_Car://自定义停车
			{
					NRF_USART_BACK_L;//反馈总线拉低            
					for(i=0;i<80;i++) __NOP() ;//延时            
					NRF_USART_BACK_H;//反馈总线拉高
				
				
			}break;
			default:
			{
					
			}break;					
    }
  }
  else if(State_Flag==Read_Paring)//当前状态为在读取参数时
  {
    if(Get_NRF_UART_GET_DMA_State())//检查DMA是否传输完毕
    {
			OnReadPar();//处理读取参数
			State_Flag=Freeing;//当前状态设置为空闲
    }     
  }
}




