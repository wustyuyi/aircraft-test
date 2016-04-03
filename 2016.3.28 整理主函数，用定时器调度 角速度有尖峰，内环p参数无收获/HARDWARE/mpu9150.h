#ifndef __MPU9150_H
#define __MPU9150_H


#include "sys.h"


#define	MPU_I2c_CLK(x) if (x) 		\
					GPIO_SetBits(GPIOB,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define MPU_I2c_SDA(x) if (x)			\
					GPIO_SetBits(GPIOB,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_11)			

#define MPU_SDA_IN()  {GPIOB->MODER&=~(3<<(11*2));GPIOB->MODER|=0<<11*2;}	//PB11 输入
#define MPU_SDA_OUT() {GPIOB->MODER&=~(3<<(11*2));GPIOB->MODER|=1<<11*2;} 	//PB11 输出
					
#define MPU_I2c_SDA_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)
#define MPU_I2c_SCL_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)




// 定义MPU9250内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48

		
#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08


#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		  0x75	//IIC地址寄存器(默认数值0x68，只读)


//****************************

#define	GYRO_ADDRESS   0xD0	  //陀螺地址
#define MAG_ADDRESS    0x18   //磁场地址
#define ACCEL_ADDRESS  0xD0
#define MPU_ADDR 0x68

#define PI 3.1415927f
#define Radian_to_Angle	   57.2957795f
#define Angle_to_Radian   0.01745329f


#define MPU6050A_2mg                ((float)0.00006104f)//((float)0.00006103f)  // 0.00006250 g/LSB   2g/(2^16/2)=0.0000610356
#define MPU6050A_4mg                ((float)0.00012207f)  // 0.00012500 g/LSB		4g/(2^16/2)=0.0001220703
#define MPU6050A_8mg                ((float)0.00024414f)  // 0.00025000 g/LSB		8g/(2^16/2)=0.0002441406

#define MPU6050G_s250dps            ((float)0.0076294f)//((float)0.0076335f)  // 0.0087500 dps/LSB		250°/(2^16/2)=0.007629394
#define MPU6050G_s500dps            ((float)0.0152588f)//((float)0.0152671f)  // 0.0175000 dps/LSB		500°/(2^16/2)=0.015258789
#define MPU6050G_s2000dps           ((float)0.0610352f)//((float)0.0609756f)  // 0.0700000 dps/LSB		2000°/(2^16/2)=0.061035156


void GY_GPIO_Config(void);
void Init_MPU9250(void);
void READ_MPU9250(void);
void READ_MPU9250_ACCEL(void);
void READ_MPU9250_GYRO(void);
void READ_MPU9250_MAG(void);
void Printf_Mpudata(void);
void printf_data(void);

u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf);
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf);
u8 MPU_Write_Byte(u8 reg,u8 data);
u8 MPU_Read_Byte(u8 reg);

static void MPU_I2c_Delay(void);
void MPU_I2c_Start(void);
void MPU_I2c_Stop(void);
u8 MPU_I2c_WaitAck(void);
void MPU_I2c_Ack(void);
void MPU_I2c_NAck(void);
void MPU_I2c_SendByte(u8 byte);
u8 MPU_I2c_ReadByte(u8 ack);
u8 Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
u8 Single_Read(u8 SlaveAddress,u8 REG_Address);
void delay5ms(void);




#endif
