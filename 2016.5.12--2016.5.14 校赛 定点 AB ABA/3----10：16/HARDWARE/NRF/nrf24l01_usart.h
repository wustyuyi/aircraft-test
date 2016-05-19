#ifndef __COMMUNICATE_H
#define __COMMUNICATE_H

#include "stm32f4xx.h"

#define ParMODE       0x01 //����ģʽ
#define PicMODE    		0x03 //��ֵͼ��ģʽ      
#define Send_Mode         PicMODE      //���÷���ģʽ

#define DataNum           4
#define Par_Num						2

//�Զ���������ݳ���
#define  Buff_Sub                        4  //���� ��ֹDMA���ߵ�Ƭ�����ȶ������µ������������
#define  Ver_Sub                         7  //��֤��������Ϣ
#define  ParValue_Length     ((DataNum<<3)+ (Par_Num<<3))//��������
  
#define Image_Width          80
#define Image_Height         60
#define Image_FitDataLen     0

#if(Send_Mode==PicMODE)
	#define  Pixels_Length       ((Image_Width*Image_Height)>>3)//�洢ͼ���С��Ϊ�˼��ټ���,�������Ż�
	#define  Data_Length         (Pixels_Length+Image_FitDataLen) //���ݳ��ȼ���,�������Ż� Image_FitDataLen��ͼ���ݳ���
	#define  Data_All_Length     (Data_Length+ParValue_Length+Ver_Sub +Buff_Sub) //���ݺͲ�����Ϣ�ܳ���,�������Ż� 
#elif(Send_Mode==ParMODE)
	#define  Pixels_Length       (Image_Width*Image_Height)//�洢ͼ���С��Ϊ�˼��ټ���,�������Ż�
	#define  Data_Length         (Pixels_Length+Image_FitDataLen) //���ݳ��ȼ���,�������Ż� Image_FitDataLen��ͼ���ݳ���
	#define  Data_All_Length     (ParValue_Length + Ver_Sub +Buff_Sub) //���ݺͲ�����Ϣ�ܳ���,�������Ż� 
#endif

/***************************ͨѶָ���********************************/
#define  Waitting               0x00    //�ȴ�
#define  Write_Data             0x01    //�������
#define  Read_Par               0x02    //�������
#define  InitParLen             0x03    //��ʼ������  
#define  Write_Par              0x04    //���������Ϣ
#define  Stop_Car               0x05    //ͣ��
#define  UcStop_Car             0x06    //�Զ���ͣ��
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
  Freeing=0x00,//����
	Read_Paring=0x01,   //��ȡ������	
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
