#ifndef _data_sent_H
#define _data_sent_H

#include "main.h"

#define UINT          0x00
#define IINT          0x01 
#define FLOAT         0x02 

typedef union
{
	uint32_t DataU32;
	float Dataf32;
}Fest;


#define TX_BUF_SIZE 800
#define RX_BUF_SIZE 128

#define NRF_CHANAL     110
#define NRF_USARTBaud  4500000
#define NRF_Delay_Us   1

#define Image_FitDataLen  0 //拟图数据长度

#define ParMODE       0x01 //参数模式
#define PicMODE    		0x03 //二值图像模式      
#define Send_Mode     PicMODE //设置发送模式

//自动计算出数据长度
#define  Buff_Sub             4  //补偿 防止DMA或者单片机不稳定所导致的数组溢出问题
#define  Ver_Sub              7  //验证及各种信息
#define  ParValue_Length     ((DataNum<<3)+ (Par_Num<<3))//参数长度

#if(Send_Mode==PicMODE)
	#define  Pixels_Length       ((Image_Width*Image_Height)>>3)//存储图像大小，为了减少计算,编译器优化
	#define  Data_Length         (Pixels_Length+Image_FitDataLen) //数据长度计算,编译器优化 Image_FitDataLen拟图数据长度
	#define  Data_All_Length     (ParValue_Length + Ver_Sub +Buff_Sub)
															 //(Data_Length+ParValue_Length+Ver_Sub +Buff_Sub) //数据和参数信息总长度,编译器优化 
#elif(Send_Mode==ParMODE)
	#define  Pixels_Length       (Image_Width*Image_Height)//存储图像大小，为了减少计算,编译器优化
	#define  Data_Length         (Pixels_Length+Image_FitDataLen) //数据长度计算,编译器优化 Image_FitDataLen拟图数据长度
	#define  Data_All_Length     (ParValue_Length + Ver_Sub +Buff_Sub) //数据和参数信息总长度,编译器优化 
#endif

#define Pardefault    0
#define Typedefault   UINT   
#define Namedefault   "Val" 

#define DataNum       7

#if(DataNum)   
#if(DataNum>=1)
#define    DefaultParValue1             ((float)throttle1)
#define    DefaultParName1              ((Namedefault<<2)|0x01)
#endif
#if(DataNum>=2)
#define    DefaultParValue2             ((float)throttle2)
#define    DefaultParName2              ((Namedefault<<2)|0x02)
#endif
#if(DataNum>=3)
#define    DefaultParValue3             ((float)throttle3)
#define    DefaultParName3              ((Namedefault<<2)|0x03)
#endif
#if(DataNum>=4)
#define    DefaultParValue4             ((float)throttle4)
#define    DefaultParName4              ((Namedefault<<2)|0x04)
#endif
#if(DataNum>=5)
#define    DefaultParValue5             angle.roll
#define    DefaultParName5              ((Namedefault<<2)|0x05)
#endif
#if(DataNum>=6)
#define    DefaultParValue6             angle.pitch
#define    DefaultParName6              ((Namedefault<<2)|0x06)
#endif
#if(DataNum>=7)
#define    DefaultParValue7             angle.yaw
#define    DefaultParName7              ((Namedefault<<2)|0x07)
#endif
#if(DataNum>=8)
#define    DefaultParValue8             Pardefault
#define    DefaultParName8              ((Namedefault<<2)|0x08)
#endif
#if(DataNum>=9)
#define    DefaultParValue9             Pardefault
#define    DefaultParName9              ((Namedefault<<2)|0x09)
#endif
#if(DataNum>=10)
#define    DefaultParValue10            Pardefault
#define    DefaultParName10             ((Namedefault<<2)|0x0A)
#endif
#if(DataNum>=11)
#define    DefaultParValue11            Pardefault
#define    DefaultParName11             ((Namedefault<<2)|0x0B)
#endif
#if(DataNum>=12)
#define    DefaultParValue12            Pardefault
#define    DefaultParName12             ((Namedefault<<2)|0x0C)
#endif
#if(DataNum>=13)
#define    DefaultParValue13            Pardefault
#define    DefaultParName13             ((Namedefault<<2)|0x0D)
#endif
#if(DataNum>=14)
#define    DefaultParValue14            Pardefault
#define    DefaultParName14             ((Namedefault<<2)|0x0E)
#endif
#if(DataNum>=15)
#define    DefaultParValue15            Pardefault
#define    DefaultParName15             ((Namedefault<<2)|0x0F)
#endif
#if(DataNum>=16)
#define    DefaultParValue16            Pardefault
#define    DefaultParName16             ((Namedefault<<2)|0x10)
#endif
#if(DataNum>=17)
#define    DefaultParValue17            Pardefault
#define    DefaultParName17             ((Namedefault<<2)|0x11)
#endif
#if(DataNum>=18)
#define    DefaultParValue18            Pardefault
#define    DefaultParName18             ((Namedefault<<2)|0x12)
#endif
#if(DataNum>=19)
#define    DefaultParValue19            Pardefault
#define    DefaultParName19             ((Namedefault<<2)|0x13)
#endif
#if(DataNum>=20)
#define    DefaultParValue20            Pardefault
#define    DefaultParName20             ((Namedefault<<2)|0x14)
#endif
#if(DataNum>=21)
#define    DefaultParValue21            Pardefault
#define    DefaultParName21             ((Namedefault<<2)|0x15)
#endif
#if(DataNum>=22)
#define    DefaultParValue22            Pardefault
#define    DefaultParName22             ((Namedefault<<2)|0x16)
#endif
#if(DataNum>=23)
#define    DefaultParValue23            Pardefault
#define    DefaultParName23             ((Namedefault<<2)|0x17)
#endif
#if(DataNum>=24)
#define    DefaultParValue24            Pardefault
#define    DefaultParName24             ((Namedefault<<2)|0x18)
#endif
#if(DataNum>=25)
#define    DefaultParValue25            Pardefault
#define    DefaultParName25             ((Namedefault<<2)|0x19)
#endif
#if(DataNum>=26)
#define    DefaultParValue26            Pardefault
#define    DefaultParName26             ((Namedefault<<2)|0x1A)
#endif
#if(DataNum>=27)
#define    DefaultParValue27            Pardefault
#define    DefaultParName27             ((Namedefault<<2)|0x1B)
#endif
#if(DataNum>=28)
#define    DefaultParValue28            Pardefault
#define    DefaultParName28             ((Namedefault<<2)|0x1C)
#endif
#if(DataNum>=29)
#define    DefaultParValue29            Pardefault
#define    DefaultParName29             ((Namedefault<<2)|0x1D)
#endif
#if(DataNum>=30)
#define    DefaultParValue30            Pardefault
#define    DefaultParName30             ((Namedefault<<2)|0x1E)
#endif
#if(DataNum>=31)
#define    DefaultParValue31            Pardefault
#define    DefaultParName31             ((Namedefault<<2)|0x1F)
#endif
#if(DataNum>=32)
#define    DefaultParValue32            Pardefault
#define    DefaultParName32             ((Namedefault<<2)|0x20)
#endif
#if(DataNum>=33)
#define    DefaultParValue33            Pardefault
#define    DefaultParName33             ((Namedefault<<2)|0x21)
#endif
#if(DataNum>=34)
#define    DefaultParValue34            Pardefault
#define    DefaultParName34             ((Namedefault<<2)|0x22)
#endif
#if(DataNum>=35)
#define    DefaultParValue35            Pardefault
#define    DefaultParName35             ((Namedefault<<2)|0x23)
#endif
#if(DataNum>=36)
#define    DefaultParValue36            Pardefault
#define    DefaultParName36             ((Namedefault<<2)|0x24)
#endif
#if(DataNum>=37)
#define    DefaultParValue37            Pardefault
#define    DefaultParName37             ((Namedefault<<2)|0x25)
#endif
#if(DataNum>=38)
#define    DefaultParValue38            Pardefault
#define    DefaultParName38             ((Namedefault<<2)|0x26)
#endif
#if(DataNum>=39)
#define    DefaultParValue39            Pardefault
#define    DefaultParName39             ((Namedefault<<2)|0x27)
#endif
#if(DataNum>=40)
#define    DefaultParValue40            Pardefault
#define    DefaultParName40             ((Namedefault<<2)|0x28)
#endif
#endif

/*****************************************************************************************************************/

#define Par_Num						2

#if(Par_Num)   
#if(Par_Num>=1)
#define    DefaultFlashValue1            rc
#define    DefaultFlashType1             FLOAT
#endif

#if(Par_Num>=2)
#define    DefaultFlashValue2            rc
#define    DefaultFlashType2             FLOAT
#endif

#if(Par_Num>=3)
#define    DefaultFlashValue3            Pardefault
#define    DefaultFlashType3             UINT
#endif

#if(Par_Num>=4)
#define    DefaultFlashValue4            Pardefault
#define    DefaultFlashType4             FLOAT
#endif

#if(Par_Num>=5)
#define    DefaultFlashValue5            Pardefault
#define    DefaultFlashType5             FLOAT
#endif

#if(Par_Num>=6)
#define    DefaultFlashValue6            Pardefault
#define    DefaultFlashType6             FLOAT
#endif

#if(Par_Num>=7)
#define    DefaultFlashValue7            Pardefault
#define    DefaultFlashType7             FLOAT
#endif

#if(Par_Num>=8)
#define    DefaultFlashValue8            Pardefault
#define    DefaultFlashType8             FLOAT
#endif

#if(Par_Num>=9)
#define    DefaultFlashValue9            Pardefault
#define    DefaultFlashType9             FLOAT
#endif

#if(Par_Num>=10)
#define    DefaultFlashValue10            Pardefault
#define    DefaultFlashType10             FLOAT
#endif

#if(Par_Num>=11)
#define    DefaultFlashValue11            Pardefault
#define    DefaultFlashType11             FLOAT
#endif

#if(Par_Num>=12)
#define    DefaultFlashValue12            Pardefault
#define    DefaultFlashType12             FLOAT
#endif

#if(Par_Num>=13)
#define    DefaultFlashValue13            Pardefault
#define    DefaultFlashType13             FLOAT
#endif

#if(Par_Num>=14)
#define    DefaultFlashValue14            Pardefault
#define    DefaultFlashType14             Typedefault
#endif

#if(Par_Num>=15)
#define    DefaultFlashValue15            Pardefault
#define    DefaultFlashType15             Typedefault
#endif

#if(Par_Num>=16)
#define    DefaultFlashValue16            Pardefault
#define    DefaultFlashType16             Typedefault
#endif

#if(Par_Num>=17)
#define    DefaultFlashValue17            Pardefault
#define    DefaultFlashType17             Typedefault
#endif

#if(Par_Num>=18)
#define    DefaultFlashValue18            Pardefault
#define    DefaultFlashType18             Typedefault
#endif

#if(Par_Num>=19)
#define    DefaultFlashValue19            Pardefault
#define    DefaultFlashType19             Typedefault
#endif

#if(Par_Num>=20)
#define    DefaultFlashValue20            Pardefault
#define    DefaultFlashType20             Typedefault
#endif

#if(Par_Num>=21)
#define    DefaultFlashValue21            Pardefault
#define    DefaultFlashType21             Typedefault
#endif

#if(Par_Num>=22)
#define    DefaultFlashValue22            Pardefault
#define    DefaultFlashType22             Typedefault
#endif

#if(Par_Num>=23)
#define    DefaultFlashValue23            Pardefault
#define    DefaultFlashType23             Typedefault
#endif

#if(Par_Num>=24)
#define    DefaultFlashValue24            Pardefault
#define    DefaultFlashType24             Typedefault
#endif

#if(Par_Num>=25)
#define    DefaultFlashValue25            Pardefault
#define    DefaultFlashType25             Typedefault
#endif

#if(Par_Num>=26)
#define    DefaultFlashValue26            Pardefault
#define    DefaultFlashType26             Typedefault
#endif

#if(Par_Num>=27)
#define    DefaultFlashValue27            Pardefault
#define    DefaultFlashType27             Typedefault
#endif

#if(Par_Num>=28)
#define    DefaultFlashValue28            Pardefault
#define    DefaultFlashType28             Typedefault
#endif

#if(Par_Num>=29)
#define    DefaultFlashValue29            Pardefault
#define    DefaultFlashType29             Typedefault
#endif

#if(Par_Num>=30)
#define    DefaultFlashValue30            Pardefault
#define    DefaultFlashType30             Typedefault
#endif

#if(Par_Num>=31)
#define    DefaultFlashValue31            Pardefault
#define    DefaultFlashType31             Typedefault
#endif

#if(Par_Num>=32)
#define    DefaultFlashValue32            Pardefault
#define    DefaultFlashType32             Typedefault
#endif

#if(Par_Num>=33)
#define    DefaultFlashValue33            Pardefault
#define    DefaultFlashType33             Typedefault
#endif

#if(Par_Num>=34)
#define    DefaultFlashValue34            Pardefault
#define    DefaultFlashType34             Typedefault
#endif

#if(Par_Num>=35)
#define    DefaultFlashValue35            Pardefault
#define    DefaultFlashType35             Typedefault
#endif

#if(Par_Num>=36)
#define    DefaultFlashValue36            Pardefault
#define    DefaultFlashType36             Typedefault
#endif

#if(Par_Num>=37)
#define    DefaultFlashValue37            Pardefault
#define    DefaultFlashType37             Typedefault
#endif

#if(Par_Num>=38)
#define    DefaultFlashValue38            Pardefault
#define    DefaultFlashType38             Typedefault
#endif

#if(Par_Num>=39)
#define    DefaultFlashValue39            Pardefault
#define    DefaultFlashType39             Typedefault
#endif

#if(Par_Num>=40)
#define    DefaultFlashValue40            Pardefault
#define    DefaultFlashType40             Typedefault
#endif

#endif

struct LCR 
{
	uint8_t Left_end;
	uint8_t Left_point;
	uint8_t Left_start;
	uint8_t Center;
	uint8_t Right_start;
	uint8_t Right_point;
	uint8_t Right_end;
};

typedef struct 
{
	uint8_t Verific[5];         //校验12345
	uint8_t Pixels_width;       //图像宽度
	uint8_t Pixels_height;      //图像高度
	uint8_t Coefficient_Num;    //固定参数个数
	uint8_t Parameter_Num;      //可由上位机调节的参数个数
	uint8_t Data_Con[DataNum*8];//一个参数32位+反码校验
	uint8_t Par_Con[Par_Num*8]; //一个参数32位+反码校验
	struct  LCR Lcr[70];
	uint8_t Image[70*(200>>3)];
}Data_Type;

typedef enum
{
  Freeing=0x00,//空闲
	Read_Paring=0x01,//读取数据中	
	Read_Picing=0x02
}NRF_State;

typedef enum
{  
  True=1 ,            
  False=0,           
}Boolean;     

extern uint8_t aTxBuffer[TX_BUF_SIZE];  //发送缓存
extern uint8_t aRxBuffer [RX_BUF_SIZE]; //接收缓存

void ImageLoad(void);
void DataLoad(void);
void OnReadPar(void);

void ReadData_Init(void);

#endif




