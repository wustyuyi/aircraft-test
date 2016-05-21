#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"

//IO方向设置
#define SCCB_SDA_IN()  {GPIOB->MODER&=~(3<<(0*2));GPIOB->MODER|=0<<0*2;}	//PA12 输入
#define SCCB_SDA_OUT() {GPIOB->MODER&=~(3<<(0*2));GPIOB->MODER|=1<<0*2;} 	//PD12 输出


//IO操作函数	 
#define SCCB_SCL    		PCout(5)	 	//SCL
#define SCCB_SDA    		PBout(0) 		//SDA	 

#define SCCB_READ_SDA   PBin(0)  		//输入SDA    
#define SCCB_ID   			0x42			//捕食者的ID

#define SDA_Pin         GPIO_Pin_0
#define SCL_Pin         GPIO_Pin_5
 
#define IIC_SDA_PORT        GPIOB
#define IIC_SCL_PORT				GPIOC
#define IIC_PORT_CLK    RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOB

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif













