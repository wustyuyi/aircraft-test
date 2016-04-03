#include "csb.h"

void CSB_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_I2C_PORT,ENABLE);	/* 打开GPIO时钟 */

	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //外部无上拉。。
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);
	
	delay_ms(1000);
	CSB_Write(SlaveAddress1,0x02,0x75);
	delay_ms(2000);
}

static void I2c_Delay(void)
{
   u8 i=250; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   } 
}

void CSB_I2c_Start()
{
	SDA_OUT();
	I2c_CLK(1);
	I2c_SDA(1);
	I2c_Delay();
	I2c_SDA(0);
	I2c_Delay();
	I2c_CLK(0);
	I2c_Delay();
}

void CSB_I2c_Stop()
{
	SDA_OUT();
	I2c_SDA(0);
	I2c_CLK(1);
	I2c_Delay();
	I2c_SDA(1);
}

u8 CSB_I2c_WaitAck()
{
	u8 re;
  SDA_OUT();
	I2c_SDA(1);	/* CPU释放SDA总线 */
	SDA_IN();
	I2c_Delay();
	I2c_CLK(1);	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	I2c_Delay();
	while(I2c_SDA_READ)	/* CPU读取SDA口线状态 */
	{
		re++;
		if(re>250)
		{
			CSB_I2c_Stop();
			return 1;
		}
		delay_us(3);
	}
	I2c_CLK(0);
	I2c_Delay();
	return 0;
}

void CSB_I2c_Ack()
{
	SDA_OUT();
	I2c_SDA(0);
	I2c_Delay();
	I2c_CLK(1);
	I2c_Delay();
	I2c_CLK(0);
	I2c_Delay();
	I2c_SDA(1);
}

void CSB_I2c_NAck()
{
	SDA_OUT();
	I2c_SDA(1);
	I2c_Delay();
	I2c_CLK(1);
	I2c_Delay();
	I2c_CLK(0);
	I2c_Delay();
}

void CSB_I2c_SendByte(u8 byte)
{
	u8 i=0;
	SDA_OUT();
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

u8 CSB_I2c_ReadByte(u8 ack)
{
	u8 byte,i;
	SDA_IN();
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
	if(!ack)
		CSB_I2c_NAck();
	else
		CSB_I2c_Ack();
	return byte;
}

void CSB_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
	CSB_I2c_Start();
	CSB_I2c_SendByte(SlaveAddress);
	while(CSB_I2c_WaitAck());
	
	CSB_I2c_SendByte(REG_Address);
	while(CSB_I2c_WaitAck());
	
	CSB_I2c_SendByte(REG_data);
	while(CSB_I2c_WaitAck());
	CSB_I2c_Stop();
}

u8 CSB_Read(u8 SlaveAddress,u8 REG_Address)
{
	u8 REG_data = 0;
	
	CSB_I2c_Start();
	CSB_I2c_SendByte(SlaveAddress);
	while(CSB_I2c_WaitAck());
	CSB_I2c_SendByte(REG_Address);
	while(CSB_I2c_WaitAck());
	
	CSB_I2c_Start();
	CSB_I2c_SendByte(SlaveAddress+1);
	while(CSB_I2c_WaitAck());
	delay_us(50);
	REG_data = CSB_I2c_ReadByte(0);
	CSB_I2c_Stop();
	return REG_data;
}

void CSB_Change_Addr(u8 OldAdddr , u8 NewAddr)
{
	CSB_Write(OldAdddr,0x02,0x9a);
	delay_ms(2);
	CSB_Write(OldAdddr,0x02,0x92);
	delay_ms(2);	
	CSB_Write(OldAdddr,0x02,0x9e);
	delay_ms(2);
	CSB_Write(OldAdddr,0x02,NewAddr);
	delay_ms(150);
}

u16 Read_KS10X(u8 SlaveAddress)
{
	u16 sum = 0;

	sum = CSB_Read(SlaveAddress,0x02);
	sum<<=8;
	sum += CSB_Read(SlaveAddress,0x03);
	
	CSB_Write(SlaveAddress,0x02,0x1e);
	
	sum /= 57.7;

	return sum;
}

