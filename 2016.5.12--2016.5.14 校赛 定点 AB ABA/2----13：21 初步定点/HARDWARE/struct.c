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
float rc=2.0,rc1 = 2.0; //pitch 起飞期望
/////////////////////////////////////////
int High = 0;
u8 USEHIGHT = 0; //0不使用定高 1使用定高
/////////////////////////////////////////
u8 FLYMODE = 0; //飞行模式
/////////////////////////////////////////
u16 th1,th2,th3,th4;  //各电机油门
////////////////////////////////////////
u8 I_Lock = 0; //积分锁
u8 OPEN_POINT = 0; //0:关闭定点 1：打开定点
/////////////////////////////////////
int menu_Mode = show_time_1; // menu模式
////////////////////////////////////////
u8 moto1_add = 15/*23*/,moto2_add = 0,moto3_add = 0,moto4_add = 12/* 17*/;
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
	Expect.hight = 110;
	
	
	sen.angle_test_offset.pitch = 10.00;//9.55;//10;
	sen.angle_test_offset.roll = 9.50;//9.20;//9.15;//10;
	sen.angle_test_offset.yaw = 10;
	
}


