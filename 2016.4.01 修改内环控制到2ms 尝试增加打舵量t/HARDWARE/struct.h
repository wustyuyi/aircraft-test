#ifndef __STRUCT_H
#define __STRUCT_H

#include "sys.h"

typedef struct //向量
{
	float x;
	float y;
	float z;
}Vector3f;


typedef struct //向量
{
	float roll; //横滚角
	float pitch; //俯仰角
	float yaw;  //航向角
}Angle;

typedef struct //矩阵
{
	Vector3f a;
	Vector3f b;
	Vector3f c;
}Matrix3f;

extern Matrix3f dcm;


typedef struct 			//四元数
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
	//角速度
	Vector3f gyro_raw;
	Vector3f gyro;
	unsigned long gyro_time;
	//加速度
	Vector3f accel_raw;
	Vector3f accel;
	unsigned long accel_time;
	//地磁
	Vector3f compass_raw;
	unsigned long compass_time;
	//温度
	long temp_raw;
	unsigned long temp_time;
	//四元数
	long quat_raw[4];
	unsigned long quat_time;
	//姿态角
	Angle angle;
	//MPU量程
	unsigned short gyro_fsr;
	unsigned char accel_fsr;
};

extern struct sen_dat_s sen;


extern u16 throttle1,throttle2,throttle3,throttle4;

extern float rc;

void Struct_Init(void);


#endif
