#ifndef __STRUCT_H
#define __STRUCT_H

#include "sys.h"

typedef struct //����
{
	float x;
	float y;
	float z;
}Vector3f;


typedef struct //����
{
	float roll; //�����
	float pitch; //������
	float yaw;  //�����
}Angle;

typedef struct //����
{
	Vector3f a;
	Vector3f b;
	Vector3f c;
}Matrix3f;

extern Matrix3f dcm;


typedef struct 			//��Ԫ��
{	
	float q1;
	float q2;
	float q3;
	float q4;
}Quaternion;

extern Quaternion Q;

typedef struct 
{
	int16_t x;
	int16_t y;
	int16_t z;
}Vector3i;


typedef struct 
{
	
	float b0;
	float a1;
	float a2;
	
	Vector3f	preout;
	Vector3f	lastout;
	
}LPF2ndData_t;

extern LPF2ndData_t Acc_lpf_2nd;

typedef struct 			
{	
	uint16_t cnt_1ms;
	uint16_t cnt_2ms;
	uint16_t cnt_5ms;
	uint16_t cnt_10ms;
	uint16_t cnt_20ms;	
}Sche;

extern Sche Scheduler;

struct sen_dat_s {
	//���ٶ�
	Vector3f gyro_raw;
	Vector3f gyro;
	unsigned long gyro_time;
	//���ٶ�
	Vector3f accel_raw;
	Vector3f accel;
	unsigned long accel_time;
	//�ش�
	Vector3f compass_raw;
	unsigned long compass_time;
	//�¶�
	long temp_raw;
	unsigned long temp_time;
	//��Ԫ��
	long quat_raw[4];
	unsigned long quat_time;
	//��̬��
	Angle angle;
	//MPU����
	unsigned short gyro_fsr;
	unsigned char accel_fsr;
};

extern struct sen_dat_s sen;


extern u16 throttle1,throttle2,throttle3,throttle4;

extern float rc;

void Struct_Init(void);


#endif
