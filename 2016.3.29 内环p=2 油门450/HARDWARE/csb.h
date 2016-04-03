#ifndef __CSB_H
#define __CSB_H

#include "sys.h"


#define GPIO_PORT_I2C	GPIOE
#define RCC_I2C_PORT RCC_AHB1Periph_GPIOE
#define I2C_SCL_PIN	GPIO_Pin_8
#define I2C_SDA_PIN	GPIO_Pin_7

#define H 1
#define L 0

#define I2C_WR 0
#define I2C_RD 1

#define	I2c_CLK(x) if (x) 		\
					GPIO_SetBits(GPIO_PORT_I2C,I2C_SCL_PIN);\
					else		\
					GPIO_ResetBits(GPIO_PORT_I2C,I2C_SCL_PIN)
#define I2c_SDA(x) if (x)			\
					GPIO_SetBits(GPIO_PORT_I2C,I2C_SDA_PIN);\
					else		\
					GPIO_ResetBits(GPIO_PORT_I2C,I2C_SDA_PIN)			

#define SDA_IN()  {GPIOE->MODER&=~(3<<(7*2));GPIOE->MODER|=0<<7*2;}	//PE7 输入
#define SDA_OUT() {GPIOE->MODER&=~(3<<(7*2));GPIOE->MODER|=1<<7*2;} 	//PE7 输出
					
#define I2c_SDA_READ GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)
#define I2c_SCL_READ GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SCL_PIN)
					
void CSB_Init(void);
static void I2c_Delay(void);
void CSB_I2c_Start(void);
void CSB_I2c_Stop(void);
u8 CSB_I2c_WaitAck(void);
void CSB_I2c_Ack(void);
void CSB_I2c_NAck(void);
void CSB_I2c_SendByte(u8 byte);
u8 CSB_I2c_ReadByte(u8 ack);
					
					
					
					
//设备的IIC地址
#define SlaveAddress1   0xe8    //默认地址，写地址+1
#define SlaveAddress2   0xd0
#define SlaveAddress3   0xd2
#define SlaveAddress4   0xd4
#define SlaveAddress5   0xd6
#define SlaveAddress6   0xd8
#define SlaveAddress7   0xda
#define SlaveAddress8   0xdc
#define SlaveAddress9   0xde
#define SlaveAddress10  0xe0
#define SlaveAddress11  0xe2
#define SlaveAddress12  0xe4
#define SlaveAddress13  0xe6
#define SlaveAddress14  0xea
#define SlaveAddress15  0xec
#define SlaveAddress16  0xee
#define SlaveAddress17  0xf8
#define SlaveAddress18  0xfa
#define SlaveAddress19  0xfc
#define SlaveAddress20  0xfe


					
void CSB_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
u8 CSB_Read(u8 SlaveAddress,u8 REG_Address);					
void CSB_Change_Addr(u8 OldAdddr , u8 NewAddr);					
u16 Read_KS10X(u8 SlaveAddress);


#endif
