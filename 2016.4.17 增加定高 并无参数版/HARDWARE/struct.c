#include "struct.h"

////////////////////////////////////////
struct sen_dat_s sen={0}; //姿态相关
////////////////////////////////////////
struct expect Expect;
////////////////////////////////////////////
//Vector3f  filter_acc;	//滤波后数据
//Vector3f  LPF_2nd_acc;
//Vector3f  filter_gyro;
//Vector3f  filter_mag;

//////////////////////////////////////////////
//Vector3f  offset_acc;	//零偏数据
//Vector3f  offset_gyro;
//Vector3f  offset_mag;
///////////////////////////////////////////
LPF2ndData_t Acc_lpf_2nd; //二阶低通滤波
LPF2ndData_t Gyro_lpf_2nd;
///////////////////////////////////////////
Sche Scheduler;       //总时间调度控制
///////////////////////////////////////////
Matrix3f dcm;          //矩阵
//////////////////////////////////////////
Quaternion Q;           //四元数
/////////////////////////////////////////
u16 throttle1=0,throttle2=0,throttle3=0,throttle4=0; //各电机油门
////////////////////////////////////////
float rc=100; //电机基础转速
/////////////////////////////////////////
int Hight=0;  //高度 单位cm
u8 USEHIGHT = 0; //0不使用定高 1使用定高
/////////////////////////////////////////


void Struct_Init()
{
	
//	offset_acc.x = 0.0;
//	offset_acc.y = 0.0;
//	offset_acc.z = 0.0;
//	
//	offset_gyro.x = 0.0;
//	offset_gyro.y = 0.0;
//	offset_gyro.z = 0.0;
	
	Q.q1 = 1;
	Q.q2 = 0;
	Q.q3 = 0;
	Q.q4 = 0;
	
	Expect.pitch = 0;
	Expect.roll = 0;
	Expect.yaw = 0;
	Expect.hight = 40;
	
	
	sen.angle_test_offset.pitch = 9.5;//10;
	sen.angle_test_offset.roll = 9.6;//10;
	sen.angle_test_offset.yaw = 10;
	
}


