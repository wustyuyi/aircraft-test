#ifndef __PID_H
#define __PID_H

#include "sys.h"
#include "struct.h"
#include "pwm.h"
#include "sen_data_build.h"
#include "ANO_DT.h"
#include "filter.h"
#include "image.h"



#define MaxAngle 40
#define MinAngle -40

typedef struct
{
	float Kp_O,Ki_O,Kd_O;
	float Kp_I,Ki_I,Kd_I;
	float Angle_Erro,LastAngle_Erro,Gyro_Erro,LastGyro_Erro,Target_Gyro;
	float Gyro_Diff,Gyro_Diff_Filter,Gyro_Diff_Filter_Ln2;
	float Target_rate;
	float Output,Pout_In,Iout_In,Dout_In,Pout_Out,Iout_Out,Dout_Out;
}pid;

extern pid PID_Pitch;
extern pid PID_Roll;
extern pid PID_Yaw;

extern pid PID_Hight;

extern pid DIRY_PID,DIRX_PID;


extern float roll0,pitch0,yaw0;

typedef struct CARMAN
{
	//以下变量用于卡尔曼滤波
float x_last;	      //上次最优解,预测值,现在最优解
float p_last;		  //上次均方差，预测均方差，现在均方差
//R代表测量误差，越大则越相信测量值，那么滤波效果越差，但是延时越小
//Q取值小的效果和R取值大的效果差不多,都是比较相信测量值
float Q,R;                                     //卡尔曼增益        
float *measure;												//卡尔曼滤波对象
}CARMAN;







void SetHight(void);
void Shigh(void);
void FlyControl_Hight(int _hight);
void FlyControl_Yaw(float _gyro_z,float _angle_yaw);
void FlyControl_Pitch(float _gyro_y,float _angle_pitch);
void FlyControl_Roll(float _gyro_x,float _angle_roll);
void Pid_Init(void);
void CONTROL(void);
void Stop(void);

float CarManCulculate(CARMAN *pCarMan);

void DirCtrl(uint16_t xx,uint16_t yy);

void CtrlDirX(pid *pPID);
void CtrlDirY(pid *pPID);

void LineCtrl(LINE_S line,short fn);


#endif
