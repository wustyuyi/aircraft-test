#ifndef __FILTER_H
#define __FILTER_H

#include "sys.h"
#include "struct.h"


#define M_PI 3.14159265f
#define IMU_LOOP_TIME					10000	//单位为uS
#define ACC_LPF_CUT 10.0f		//加速度低通滤波器截止频率10Hz
#define GYRO_LPF_CUT 20.0f
#define GYRO_CF_TAU 1.2f

	
	//滤波器初始化
	void Filter_Init(void);
	
	//一阶低通滤波器系数计算
	float LPF_1st_Factor_Cal(float deltaT, float Fcut);
	
	
	//二阶低通滤波器系数计算
	void LPF_2nd_Factor_Cal(float deltaT, float Fcut, LPF2ndData_t* lpf_data);

	//互补滤波器系数计算
	float CF_Factor_Cal(float deltaT, float tau);
	
	//一阶低通滤波器
  void LPF_1st(Vector3f *oldData, Vector3f *newData, float lpf_factor);
	void LPF_1st_gyro(float *oldData,float *newData, float lpf_factor);
	
	//二阶低通滤波器
	Vector3f LPF_2nd(LPF2ndData_t* lpf_2nd, Vector3f newData);
	float LPF_2nd_gyro(LPF2ndData_t* lpf_2nd, float newData);
	
	//互补滤波器
	Vector3f CF_1st(Vector3f gyroData, Vector3f accData, float cf_factor);
	
	//窗口圆滑滤波
	void Gyro_Filter(Vector3f *Gyro_in , Vector3f *Gyro_out);
	
	
	extern float acc_lpf,gyro_lpf,gyro_cf;

#endif
