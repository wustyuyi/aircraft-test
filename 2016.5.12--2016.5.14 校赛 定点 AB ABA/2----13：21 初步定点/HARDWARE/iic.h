#ifndef __IIC_H
#define __IIC_H

#include "sys.h"

#define TRUE 1
#define FALSE 0


#define SDA_H GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define SDA_L GPIO_ResetBits(GPIOB, GPIO_Pin_9)

#define SCL_H GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define SCL_L GPIO_ResetBits(GPIOB, GPIO_Pin_8)

#define SDA_read GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)

void I2C_delay(void);
void delay5ms(void);
u8 I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
u8 I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte);
unsigned char I2C_RadeByte(unsigned char ack);
u8 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);



#endif
