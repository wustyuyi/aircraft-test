#ifndef __STRUCT_H
#define __STRUCT_H

#include "sys.h"

typedef struct //向量
{
	float x;
	float y;
	float z;
}Vector3f;

extern Vector3f acc;
extern Vector3f filter_acc;
extern Vector3f LPF_2nd_acc;
extern Vector3f offset_acc;

extern Vector3f gyro;
extern Vector3f filter_gyro;
extern Vector3f offset_gyro;

extern Vector3f mag;
extern Vector3f filter_mag;
extern Vector3f offset_mag;


typedef struct //向量
{
	float roll; //横滚角
	float pitch; //俯仰角
	float yaw;  //航向角
}Angle;


extern Angle angle;


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



extern u16 throttle1,throttle2,throttle3,throttle4;

extern float rc;

void Struct_Init(void);


#endif
