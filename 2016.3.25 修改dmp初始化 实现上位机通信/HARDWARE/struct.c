#include "struct.h"

Vector3f  acc;			//原始数据
Vector3f gyro;
Vector3f mag;
////////////////////////////////////////////
Vector3f  filter_acc;	//滤波后数据
Vector3f  LPF_2nd_acc;
Vector3f  filter_gyro;
Vector3f  filter_mag;
////////////////////////////////////////////
Vector3f  offset_acc;	//零偏数据
Vector3f offset_gyro;
Vector3f  offset_mag;
////////////////////////////////////////////
Angle angle;   //姿态角
///////////////////////////////////////////
LPF2ndData_t Acc_lpf_2nd; //二阶低通滤波
///////////////////////////////////////////
Sche Scheduler;       //总时间调度控制
///////////////////////////////////////////
Matrix3f dcm;          //矩阵
//////////////////////////////////////////
Quaternion Q;           //四元数
/////////////////////////////////////////
u16 throttle1=0,throttle2=0,throttle3=0,throttle4=0; //各电机油门
////////////////////////////////////////
float rc=0; //电机基础转速

void Struct_Init()
{
	
	offset_acc.x = 0;
	offset_acc.y = 0;
	offset_acc.z = 0;
	
	offset_gyro.x = 0;
	offset_gyro.y = 0;
	offset_gyro.z = 0;
	
	Q.q1 = 1;
	Q.q2 = 0;
	Q.q3 = 0;
	Q.q4 = 0;

}


