#ifndef __COMMUNICATE_H
#define __COMMUNICATE_H

#include "stm32f4xx.h"

#define ParMODE       0x01 //参数模式
#define PicMODE    		0x03 //二值图像模式      
#define Send_Mode         PicMODE      //设置发送模式

#define DataNum           4
#define Par_Num						2

//自动计算出数据长度
#define  Buff_Sub                        4  //补偿 防止DMA或者单片机不稳定所导致的数组溢出问题
#define  Ver_Sub                         7  //验证及各种信息
#define  ParValue_Length     ((DataNum<<3)+ (Par_Num<<3))//参数长度
  
#define Image_Width          80
#define Image_Height         60
#define Image_FitDataLen     0

#if(Send_Mode==PicMODE)
	#define  Pixels_Length       ((Image_Width*Image_Height)>>3)//存储图像大小，为了减少计算,编译器优化
	#define  Data_Length         (Pixels_Length+Image_FitDataLen) //数据长度计算,编译器优化 Image_FitDataLen拟图数据长度
	#define  Data_All_Length     (Data_Length+ParValue_Length+Ver_Sub +Buff_Sub) //数据和参数信息总长度,编译器优化 
#elif(Send_Mode==ParMODE)
	#define  Pixels_Length       (Image_Width*Image_Height)//存储图像大小，为了减少计算,编译器优化
	#define  Data_Length         (Pixels_Length+Image_FitDataLen) //数据长度计算,编译器优化 Image_FitDataLen拟图数据长度
	#define  Data_All_Length     (ParValue_Length + Ver_Sub +Buff_Sub) //数据和参数信息总长度,编译器优化 
#endif

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

typedef struct 
{
    uint8_t Verific[5];
    uint8_t Pixels_width;
    uint8_t Pixels_height;
    uint8_t Coefficient_Num;
    uint8_t Parameter_Num;
    uint8_t Data_Con[DataNum*8];
    uint8_t Par_Con[Par_Num*8];
}Data_Type;

typedef enum
{
  Freeing=0x00,//空闲
	Read_Paring=0x01,   //读取数据中	
	Read_Picing=0x02
}NRF_State;

typedef enum
{  
  True=1 ,            
  False=0,           
}Boolean;     


void NRF_Usart_Pin_Init(void);
void  NRF_Read_Live_Init(void);
void  NRF_UART_Connect(void);
void DataLoad(void);

void OnReadPar(void);

#endif //__COMMUNICATE_H
