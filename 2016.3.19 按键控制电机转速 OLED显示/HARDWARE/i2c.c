#include "i2c.h"

void I2c_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* 打开GPIO时钟 */

	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //推挽输出
	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);
}

static void I2c_Delay(void)
{
   u8 i=30; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   } 
}

void I2c_Start()
{
	I2c_CLK(1);
	I2c_SDA(1);
	I2c_Delay();
	I2c_SDA(0);
	I2c_Delay();
	I2c_CLK(0);
	I2c_Delay();
}

void I2c_Stop()
{
	I2c_SDA(0);
	I2c_CLK(1);
	I2c_Delay();
	I2c_SDA(1);
}

u8 I2c_WaitAck()
{
	u8 re;

	I2c_SDA(1);	/* CPU释放SDA总线 */
	I2c_Delay();
	I2c_CLK(1);	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	I2c_Delay();
	if (I2c_SDA_READ)	/* CPU读取SDA口线状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	I2c_CLK(0);
	I2c_Delay();
	return re;
}

void I2c_Ack()
{
	I2c_SDA(0);
	I2c_Delay();
	I2c_CLK(1);
	I2c_Delay();
	I2c_CLK(0);
	I2c_Delay();
	I2c_SDA(1);
}

void I2c_NAck()
{
	I2c_SDA(1);
	I2c_Delay();
	I2c_CLK(1);
	I2c_Delay();
	I2c_CLK(0);
	I2c_Delay();
}

void I2c_SendByte(u8 byte)
{
	u8 i=0;
	
	for(i=0;i<8;i++)
	{
		if(byte&0x80)
		{
			I2c_SDA(1);
		}
		else
		{
			I2c_SDA(0);
		}
		I2c_Delay();
		I2c_CLK(1);
		I2c_Delay();	
		I2c_CLK(0);
		byte <<= 1;	/* 左移一个bit */
		I2c_Delay();
	}
	
	I2c_SDA(1); // 释放总线
	
}

u8 I2c_ReadByte()
{
	u8 byte,i;
	
	for(i=0;i<8;i++)
	{
		byte<<=1;
		I2c_CLK(1);
		I2c_Delay();
		if(I2c_SDA_READ)
		{
			byte++;
		}
		I2c_CLK(0);
		I2c_Delay();
	}
	return byte;
}


u8 I2c_Check(u8 address)
{
	u8 ucAck;
	
	I2c_Init();
	
	I2c_Start();
	
	I2c_SendByte(address|I2C_WR);
	
	ucAck = I2c_WaitAck();
	
	I2c_Stop();
	
	return ucAck;
	
}

