#include "mpu9150.h"
#include "usart.h"	
#include "struct.h"
unsigned char TX_DATA[4];

unsigned int BUF[10]={0,0,0,0,0,0,0,0,0,0};       //�������ݻ�����
short A_X,A_Y,A_Z,G_X,G_Y,G_Z,T_T,M_X,M_Y,M_Z;		 //X,Y,Z�ᣬ�¶�,�ų�


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

//��ʼ��MPU9250��������Ҫ��ο�pdf�����޸�************************
void Init_MPU9250(void)
{
  Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//�������״̬
	Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x07);
	Single_Write(GYRO_ADDRESS,CONFIG, 0x06);
	Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);
	Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);

  //----------------
//	Single_Write(GYRO_ADDRESS,0x6A,0x00);//close Master Mode	

}

//*********���¾�������*****************************
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



//******��ȡMPU9250����****************************************
void READ_MPU9250_ACCEL(void)
{ 

   BUF[0]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_L); 
   BUF[1]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_H);
   A_X=	(BUF[1]<<8)|BUF[0];
   A_X=A_X*MPU6050A_2mg*100; 						   //��ȡ����X������

   BUF[2]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_L);
   BUF[3]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_H);
   A_Y=	(BUF[3]<<8)|BUF[2];
   A_Y=A_Y*MPU6050A_2mg*100; 						   //��ȡ����Y������
   BUF[4]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_L);
   BUF[5]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_H);
   A_Z=	(BUF[5]<<8)|BUF[4];
   A_Z=A_Z*MPU6050A_2mg*100; 					       //��ȡ����Z������
 
}

void READ_MPU9250_GYRO(void)
{ 

   BUF[0]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_L); 
   BUF[1]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_H);
   G_X=	(BUF[1]<<8)|BUF[0];
   G_X=G_X*MPU6050G_s2000dps; 						   //��ȡ����X������

   BUF[2]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_L);
   BUF[3]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_H);
   G_Y=	(BUF[3]<<8)|BUF[2];
   G_Y=G_Y*MPU6050G_s2000dps; 						   //��ȡ����Y������
	
   BUF[4]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_L);
   BUF[5]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_H);
   G_Z=	(BUF[5]<<8)|BUF[4];
   G_Z=G_Z*MPU6050G_s2000dps; 					       //��ȡ����Z������
 
 
  // BUF[6]=Single_Read(GYRO_ADDRESS,TEMP_OUT_L); 
  // BUF[7]=Single_Read(GYRO_ADDRESS,TEMP_OUT_H); 
  // T_T=(BUF[7]<<8)|BUF[6];
  // T_T = 35+ ((double) (T_T + 13200)) / 280;// ��ȡ������¶�
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
   						   //��ȡ����Y������
	 
   BUF[4]=Single_Read(MAG_ADDRESS,MAG_ZOUT_L);
   BUF[5]=Single_Read(MAG_ADDRESS,MAG_ZOUT_H);
   M_Z=(BUF[5]<<8)|BUF[4];
 					       //��ȡ����Z������
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

//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    MPU_I2c_Start(); 
	MPU_I2c_SendByte((addr<<1)|0);//����������ַ+д����	
	if(MPU_I2c_WaitAck())	//�ȴ�Ӧ��
	{
		MPU_I2c_Stop();		 
		return 1;		
	}
    MPU_I2c_SendByte(reg);	//д�Ĵ�����ַ
    MPU_I2c_WaitAck();		//�ȴ�Ӧ��
	for(i=0;i<len;i++)
	{
		MPU_I2c_SendByte(buf[i]);	//��������
		if(MPU_I2c_WaitAck())		//�ȴ�ACK
		{
			MPU_I2c_Stop();	 
			return 1;		 
		}		
	}    
    MPU_I2c_Stop();	 
	return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	MPU_I2c_Start(); 
	MPU_I2c_SendByte((addr<<1)|0);//����������ַ+д����	
	if(MPU_I2c_WaitAck())	//�ȴ�Ӧ��
	{
		MPU_I2c_Stop();		 
		return 1;		
	}
    MPU_I2c_SendByte(reg);	//д�Ĵ�����ַ
    MPU_I2c_WaitAck();		//�ȴ�Ӧ��
   MPU_I2c_Start();
	MPU_I2c_SendByte((addr<<1)|1);//����������ַ+������	
    MPU_I2c_WaitAck();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=MPU_I2c_ReadByte(0);//������,����nACK 
		else *buf=MPU_I2c_ReadByte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    MPU_I2c_Stop();	//����һ��ֹͣ���� 
	return 0;	
}
//IICдһ���ֽ� 
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    MPU_I2c_Start(); 
	MPU_I2c_SendByte((MPU_ADDR<<1)|0);//����������ַ+д����	
	if(MPU_I2c_WaitAck())	//�ȴ�Ӧ��
	{
		MPU_I2c_Stop();		 
		return 1;		
	}
    MPU_I2c_SendByte(reg);	//д�Ĵ�����ַ
    MPU_I2c_WaitAck();		//�ȴ�Ӧ�� 
	MPU_I2c_SendByte(data);//��������
	if(MPU_I2c_WaitAck())	//�ȴ�ACK
	{
		MPU_I2c_Stop();	 
		return 1;		 
	}		 
    MPU_I2c_Stop();	 
	return 0;
}
//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    MPU_I2c_Start(); 
	MPU_I2c_SendByte((MPU_ADDR<<1)|0);//����������ַ+д����	
	MPU_I2c_WaitAck();		//�ȴ�Ӧ�� 
    MPU_I2c_SendByte(reg);	//д�Ĵ�����ַ
    MPU_I2c_WaitAck();		//�ȴ�Ӧ��
   MPU_I2c_Start();
	MPU_I2c_SendByte((MPU_ADDR<<1)|1);//����������ַ+������	
    MPU_I2c_WaitAck();		//�ȴ�Ӧ�� 
	res=MPU_I2c_ReadByte(0);//��ȡ����,����nACK 
    MPU_I2c_Stop();			//����һ��ֹͣ���� 
	return res;		
}

static void MPU_I2c_Delay(void)
{
   u8 i=250; //��������Ż��ٶ�	����������͵�5����д��
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
	MPU_I2c_SDA(1);	/* CPU�ͷ�SDA���� */
	MPU_SDA_IN();
	MPU_I2c_Delay();
	MPU_I2c_CLK(1);	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	MPU_I2c_Delay();
	while(MPU_I2c_SDA_READ)	/* CPU��ȡSDA����״̬ */
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
		byte <<= 1;	/* ����һ��bit */
		MPU_I2c_Delay();
	}
	
	MPU_I2c_SDA(1); // �ͷ�����
	
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
//���ֽ�д��*******************************************

u8 Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data)		     //void
{
  	MPU_I2c_Start();
    MPU_I2c_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(MPU_I2c_WaitAck()){MPU_I2c_Stop(); return 1;}
    MPU_I2c_SendByte(REG_Address);   //���õ���ʼ��ַ      
    MPU_I2c_WaitAck();	
    MPU_I2c_SendByte(REG_data);
    MPU_I2c_WaitAck();   
    MPU_I2c_Stop(); 
    return 0;
}

//���ֽڶ�ȡ*****************************************
u8 Single_Read(u8 SlaveAddress,u8 REG_Address)
{   
		u8 REG_data;     	
		MPU_I2c_Start();
    MPU_I2c_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(MPU_I2c_WaitAck()){MPU_I2c_Stop(); return 0;}
    MPU_I2c_SendByte(REG_Address);   //���õ���ʼ��ַ      
    MPU_I2c_WaitAck();
    MPU_I2c_Start();
    MPU_I2c_SendByte(SlaveAddress+1);
    MPU_I2c_WaitAck();

		REG_data= MPU_I2c_ReadByte(0);
    MPU_I2c_NAck();
    MPU_I2c_Stop();
		return REG_data;
}	
