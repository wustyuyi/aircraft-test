#include "mpu9150.h"
#include "usart.h"	
#include "struct.h"
unsigned char TX_DATA[4];

unsigned int BUF[10]={0,0,0,0,0,0,0,0,0,0};       //接收数据缓存区
short A_X,A_Y,A_Z,G_X,G_Y,G_Z,T_T,M_X,M_Y,M_Z;		 //X,Y,Z轴，温度,磁场


void GY_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

//初始化MPU9250，根据需要请参考pdf进行修改************************
void Init_MPU9250(void)
{
  Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x07);
	Single_Write(GYRO_ADDRESS,CONFIG, 0x06);
	Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);
	Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);

  //----------------
//	Single_Write(GYRO_ADDRESS,0x6A,0x00);//close Master Mode	

}

//*********更新九轴数据*****************************
void READ_MPU9250()
{
	READ_MPU9250_ACCEL();
	READ_MPU9250_GYRO();
	READ_MPU9250_MAG();
	
	acc.x = A_X+offset_acc.x;
	acc.y = A_Y+offset_acc.y;
	acc.z = A_Z+offset_acc.z;
	
	gyro.x = G_X+offset_gyro.x;
	gyro.y = G_Y+offset_gyro.y;
	gyro.z = G_Z+offset_gyro.z;
	
	mag.x = M_X;
	mag.y = M_Y;
	mag.z = M_Z;
}



//******读取MPU9250数据****************************************
void READ_MPU9250_ACCEL(void)
{ 

   BUF[0]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_L); 
   BUF[1]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_H);
   A_X=	(BUF[1]<<8)|BUF[0];
   A_X=A_X*MPU6050A_2mg*100; 						   //读取计算X轴数据

   BUF[2]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_L);
   BUF[3]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_H);
   A_Y=	(BUF[3]<<8)|BUF[2];
   A_Y=A_Y*MPU6050A_2mg*100; 						   //读取计算Y轴数据
   BUF[4]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_L);
   BUF[5]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_H);
   A_Z=	(BUF[5]<<8)|BUF[4];
   A_Z=A_Z*MPU6050A_2mg*100; 					       //读取计算Z轴数据
 
}

void READ_MPU9250_GYRO(void)
{ 

   BUF[0]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_L); 
   BUF[1]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_H);
   G_X=	(BUF[1]<<8)|BUF[0];
   G_X=G_X*MPU6050G_s2000dps; 						   //读取计算X轴数据

   BUF[2]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_L);
   BUF[3]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_H);
   G_Y=	(BUF[3]<<8)|BUF[2];
   G_Y=G_Y*MPU6050G_s2000dps; 						   //读取计算Y轴数据
	
   BUF[4]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_L);
   BUF[5]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_H);
   G_Z=	(BUF[5]<<8)|BUF[4];
   G_Z=G_Z*MPU6050G_s2000dps; 					       //读取计算Z轴数据
 
 
  // BUF[6]=Single_Read(GYRO_ADDRESS,TEMP_OUT_L); 
  // BUF[7]=Single_Read(GYRO_ADDRESS,TEMP_OUT_H); 
  // T_T=(BUF[7]<<8)|BUF[6];
  // T_T = 35+ ((double) (T_T + 13200)) / 280;// 读取计算出温度
}


void READ_MPU9250_MAG(void)
{ 
   Single_Write(GYRO_ADDRESS,0x37,0x02);//turn on Bypass Mode 
   delay_ms(10);
   Single_Write(MAG_ADDRESS,0x0A,0x01);
   delay_ms(10);
   BUF[0]=Single_Read (MAG_ADDRESS,MAG_XOUT_L);
   BUF[1]=Single_Read (MAG_ADDRESS,MAG_XOUT_H);
   M_X=(BUF[1]<<8)|BUF[0];

   BUF[2]=Single_Read(MAG_ADDRESS,MAG_YOUT_L);
   BUF[3]=Single_Read(MAG_ADDRESS,MAG_YOUT_H);
   M_Y=	(BUF[3]<<8)|BUF[2];
   						   //读取计算Y轴数据
	 
   BUF[4]=Single_Read(MAG_ADDRESS,MAG_ZOUT_L);
   BUF[5]=Single_Read(MAG_ADDRESS,MAG_ZOUT_H);
   M_Z=(BUF[5]<<8)|BUF[4];
 					       //读取计算Z轴数据
}

void Printf_Mpudata()
{
	READ_MPU9250_ACCEL();
	READ_MPU9250_GYRO();
	READ_MPU9250_MAG();
	
	printf("Acc_x: %d  Acc_y: %d Acc_z: %d  ",A_X,A_Y,A_Z);
	printf("Gyro_x: %d  Gyro_y: %d Gyro_z: %d  ",G_X,G_Y,G_Z);
	printf("Mag_x: %d  Mag_y: %d Mag_z: %d",M_X,M_Y,M_Z);
	printf("\r\n");
}

//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    MPU_I2c_Start(); 
	MPU_I2c_SendByte((addr<<1)|0);//发送器件地址+写命令	
	if(MPU_I2c_WaitAck())	//等待应答
	{
		MPU_I2c_Stop();		 
		return 1;		
	}
    MPU_I2c_SendByte(reg);	//写寄存器地址
    MPU_I2c_WaitAck();		//等待应答
	for(i=0;i<len;i++)
	{
		MPU_I2c_SendByte(buf[i]);	//发送数据
		if(MPU_I2c_WaitAck())		//等待ACK
		{
			MPU_I2c_Stop();	 
			return 1;		 
		}		
	}    
    MPU_I2c_Stop();	 
	return 0;	
} 
//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	MPU_I2c_Start(); 
	MPU_I2c_SendByte((addr<<1)|0);//发送器件地址+写命令	
	if(MPU_I2c_WaitAck())	//等待应答
	{
		MPU_I2c_Stop();		 
		return 1;		
	}
    MPU_I2c_SendByte(reg);	//写寄存器地址
    MPU_I2c_WaitAck();		//等待应答
   MPU_I2c_Start();
	MPU_I2c_SendByte((addr<<1)|1);//发送器件地址+读命令	
    MPU_I2c_WaitAck();		//等待应答 
	while(len)
	{
		if(len==1)*buf=MPU_I2c_ReadByte(0);//读数据,发送nACK 
		else *buf=MPU_I2c_ReadByte(1);		//读数据,发送ACK  
		len--;
		buf++; 
	}    
    MPU_I2c_Stop();	//产生一个停止条件 
	return 0;	
}
//IIC写一个字节 
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    MPU_I2c_Start(); 
	MPU_I2c_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
	if(MPU_I2c_WaitAck())	//等待应答
	{
		MPU_I2c_Stop();		 
		return 1;		
	}
    MPU_I2c_SendByte(reg);	//写寄存器地址
    MPU_I2c_WaitAck();		//等待应答 
	MPU_I2c_SendByte(data);//发送数据
	if(MPU_I2c_WaitAck())	//等待ACK
	{
		MPU_I2c_Stop();	 
		return 1;		 
	}		 
    MPU_I2c_Stop();	 
	return 0;
}
//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    MPU_I2c_Start(); 
	MPU_I2c_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
	MPU_I2c_WaitAck();		//等待应答 
    MPU_I2c_SendByte(reg);	//写寄存器地址
    MPU_I2c_WaitAck();		//等待应答
   MPU_I2c_Start();
	MPU_I2c_SendByte((MPU_ADDR<<1)|1);//发送器件地址+读命令	
    MPU_I2c_WaitAck();		//等待应答 
	res=MPU_I2c_ReadByte(0);//读取数据,发送nACK 
    MPU_I2c_Stop();			//产生一个停止条件 
	return res;		
}

static void MPU_I2c_Delay(void)
{
   u8 i=250; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   } 
}

void MPU_I2c_Start()
{
	MPU_SDA_OUT();
	MPU_I2c_CLK(1);
	MPU_I2c_SDA(1);
	MPU_I2c_Delay();
	MPU_I2c_SDA(0);
	MPU_I2c_Delay();
	MPU_I2c_CLK(0);
	MPU_I2c_Delay();
}

void MPU_I2c_Stop()
{
	MPU_SDA_OUT();
	MPU_I2c_SDA(0);
	MPU_I2c_CLK(1);
	MPU_I2c_Delay();
	MPU_I2c_SDA(1);
}

u8 MPU_I2c_WaitAck()
{
	u8 re;
  MPU_SDA_OUT();
	MPU_I2c_SDA(1);	/* CPU释放SDA总线 */
	MPU_SDA_IN();
	MPU_I2c_Delay();
	MPU_I2c_CLK(1);	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	MPU_I2c_Delay();
	while(MPU_I2c_SDA_READ)	/* CPU读取SDA口线状态 */
	{
		re++;
		if(re>250)
		{
			MPU_I2c_Stop();
			return 1;
		}
		delay_us(3);
	}
	MPU_I2c_CLK(0);
	MPU_I2c_Delay();
	return 0;
}

void MPU_I2c_Ack()
{
	MPU_SDA_OUT();
	MPU_I2c_SDA(0);
	MPU_I2c_Delay();
	MPU_I2c_CLK(1);
	MPU_I2c_Delay();
	MPU_I2c_CLK(0);
	MPU_I2c_Delay();
	MPU_I2c_SDA(1);
}

void MPU_I2c_NAck()
{
	MPU_SDA_OUT();
	MPU_I2c_SDA(1);
	MPU_I2c_Delay();
	MPU_I2c_CLK(1);
	MPU_I2c_Delay();
	MPU_I2c_CLK(0);
	MPU_I2c_Delay();
}

void MPU_I2c_SendByte(u8 byte)
{
	u8 i=0;
	MPU_SDA_OUT();
	for(i=0;i<8;i++)
	{
		if(byte&0x80)
		{
			MPU_I2c_SDA(1);
		}
		else
		{
			MPU_I2c_SDA(0);
		}
		MPU_I2c_Delay();
		MPU_I2c_CLK(1);
		MPU_I2c_Delay();	
		MPU_I2c_CLK(0);
		byte <<= 1;	/* 左移一个bit */
		MPU_I2c_Delay();
	}
	
	MPU_I2c_SDA(1); // 释放总线
	
}

u8 MPU_I2c_ReadByte(u8 ack)
{
	u8 byte,i;
	MPU_SDA_IN();
	for(i=0;i<8;i++)
	{
		byte<<=1;
		MPU_I2c_CLK(1);
		MPU_I2c_Delay();
		if(MPU_I2c_SDA_READ)
		{
			byte++;
		}
		MPU_I2c_CLK(0);
		MPU_I2c_Delay();
	}
	if(!ack)
		MPU_I2c_NAck();
	else
		MPU_I2c_Ack();
	return byte;
}

//ZRX          
//单字节写入*******************************************

u8 Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data)		     //void
{
  	MPU_I2c_Start();
    MPU_I2c_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(MPU_I2c_WaitAck()){MPU_I2c_Stop(); return 1;}
    MPU_I2c_SendByte(REG_Address);   //设置低起始地址      
    MPU_I2c_WaitAck();	
    MPU_I2c_SendByte(REG_data);
    MPU_I2c_WaitAck();   
    MPU_I2c_Stop(); 
    return 0;
}

//单字节读取*****************************************
u8 Single_Read(u8 SlaveAddress,u8 REG_Address)
{   
		u8 REG_data;     	
		MPU_I2c_Start();
    MPU_I2c_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(MPU_I2c_WaitAck()){MPU_I2c_Stop(); return 0;}
    MPU_I2c_SendByte(REG_Address);   //设置低起始地址      
    MPU_I2c_WaitAck();
    MPU_I2c_Start();
    MPU_I2c_SendByte(SlaveAddress+1);
    MPU_I2c_WaitAck();

		REG_data= MPU_I2c_ReadByte(0);
    MPU_I2c_NAck();
    MPU_I2c_Stop();
		return REG_data;
}	
