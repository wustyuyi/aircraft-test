#include "nrf24l01_usart.h"
#include "image.h"
#include "systick.h"
#include "usart_dma.h"
//#include "usart.h"
#include "string.h"
#include "oled.h"
//#include "sen_data_build.h"
//#include "pwm.h"
//#include "control.h"

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

//#define NRF_UART_GCONTINUOUS
//#define NRF_USART      USART2
#define NRF_USARTBaud  4500000
#define NRF_CHANAL     1//110
#define NRF_Delay_Us   1


#if(Data_All_Length>TX_BUF_SIZE)
	#error TX_BUF_SIZE should bigger than Data_All_Length
#endif

//extern float Distance;
Data_Type *Sent_Data=(Data_Type*)aTxBuffer;

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
	NRF_UART_SetValue8(0x01);//?????  
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

//void ImageLoad(void)
//{
//	uint16_t i,j;
//	uint8_t (*pImg)[Image_Width>>3];
//	pImg=(uint8_t (*)[Image_Width>>3])(aTxBuffer+sizeof(Data_Type));
//	for(i=0;i<Image_Height;i++)
//	for(j=0;j<(Image_Width>>3);j++)
//	{
//		pImg[i][j]=0x0f;
//	}
//}

extern float Adist;

void DataLoad(void)
{
	float fdt;
	extern float dyaw;
	uint32_t idt;
	Sent_Data->Verific[0]=1;
  Sent_Data->Verific[1]=2;
  Sent_Data->Verific[2]=3;
  Sent_Data->Verific[3]=4;
  Sent_Data->Verific[4]=5; 
	Sent_Data->Parameter_Num=Par_Num;
	Sent_Data->Coefficient_Num=DataNum;
	
	fdt=0;    //1
	memcpy(Sent_Data->Data_Con,&fdt,4);
	memcpy(&idt,Sent_Data->Data_Con,4);
	idt=~idt;
	memcpy(Sent_Data->Data_Con+4,&idt,4);
	

//////////////////////////////////////////////////////
	fdt=get_timer();
	memcpy(Sent_Data->Par_Con,&fdt,4);  //1.时间
	memcpy(&idt,Sent_Data->Par_Con,4);
	idt=~idt;
	memcpy(Sent_Data->Par_Con+4,&idt,4);
	
		
#if(Send_Mode==ParMODE)
	Sent_Data->Pixels_height=0;
	Sent_Data->Pixels_width=0;
#elif(Send_Mode==PicMODE)
	Sent_Data->Pixels_height=Image_Height;
	Sent_Data->Pixels_width=Image_Width;
//	ImageLoad();
#endif
}

void OnReadPar(void)
{
	switch (aRxBuffer[8])
	{
		case 0xe0:
		{
			OLED_ShowChar(60,6,'o');
//			OnStop();
		}break;
		case 0xe1:
		{
			OLED_ShowChar(80,6,'d');
//			OnStart();
		}break;
		case 0xe2:
		{
				
		}break;
		case 0x01:
		{

		}break;
		case 0x02:
		{
			
		}break;
		case 0x03:
		{
			
		}break;
		case 0x04:
		{
			
		}break;
		case 0x05:
		{
			
		}break;
		case 0x06:
		{
			
		}break;
		case 0x07:
		{
			
		}break;
		case 0x08:
		{
			
		}break;
		case 0x09:
		{
			
		}break;
	}
}

void  NRF_UART_Connect(void)//数据链接传输
{
  int i;
  static NRF_State State_Flag=Freeing;//状态标记
  static Boolean first_wt_flag=True;//标记位
	static unsigned long tm=0;
  uint8_t Command=Get_NRF_UART_Cmd();//获取端口指令
	
	if(tm+3000<get_timer()&&(!first_wt_flag))//三秒没收到数据就视为断开连接
	{
		tm=get_timer();
//	OnStop();//停止飞行
	}
 // OLED_Write_Num4(9,0,Command);//显示当前模式
  if(State_Flag==Freeing)//当前状态空闲时
  {
    switch(Command)
    {
        case Write_Data://输出数据
        {
          if((Get_NRF_UART_SET_DMA_State() || first_wt_flag)&& tm+40<get_timer())//当前DMA是否空闲
          {
//               Compressed_Data();//压缩数据 并将数据转换成校验数据
//			
							 DataLoad();
              
               NRF_USART_BACK_L;//反馈总线拉低
            
               for(i=0;i<80;i++) __NOP() ;//延时
            
               NRF_USART_BACK_H;//反馈总线拉高

               first_wt_flag=False;//非第一次通讯

               NRF_USART_DMA_Send(Data_All_Length);//发送数据包
						
							 tm=get_timer();//跟新时间
          }
        }break;
        case Write_Par://输出数据
        {
//          if(Get_NRF_UART_SET_DMA_State() || first_wt_flag)//当前DMA是否空闲
//          {
//             // SetToData();//将拟图信息和控制信息赋给Data数组,以便存储到SD卡

//              SetFlashDataToCon();//固定参数压缩
//   
//              Set_DataToCon();//加校验            
//            
               NRF_USART_BACK_L;//反馈总线拉低
            
               for(i=0;i<80;i++) __NOP() ;//延时
            
               NRF_USART_BACK_H;//反馈总线拉高

//              first_wt_flag=False;//非第一次通讯
//             
//              NUC_Write_Par();//输出参数
//          }
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
	//					OnStop();//停止四轴
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

