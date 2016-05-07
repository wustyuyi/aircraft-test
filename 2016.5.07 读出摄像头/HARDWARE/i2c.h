#ifndef __I2C_H
#define __I2C_H

#include "sys.h"


#define GPIO_PORT_I2C	GPIOB
#define RCC_I2C_PORT RCC_APB2Periph_GPIOB
#define I2C_SCL_PIN	GPIO_Pin_10
#define I2C_SDA_PIN	GPIO_Pin_11

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
					
#define I2c_SDA_READ GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)
					
					
void I2c_Init(void);
static void I2c_Delay(void);
void I2c_Start(void);
void I2c_Stop(void);
u8 I2c_WaitAck(void);
void I2c_Ack(void);
void I2c_NAck(void);
void I2c_SendByte(u8 byte);
u8 I2c_ReadByte(void);
u8 I2c_Check(u8 address);


#endif
