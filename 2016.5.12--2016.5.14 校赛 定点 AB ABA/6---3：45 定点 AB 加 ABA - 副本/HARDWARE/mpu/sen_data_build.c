#include "sen_data_build.h"




void inv_build_gyro(short *gyro,unsigned long timestamp)
{
	sen.gyro_raw.x = gyro[0];
	sen.gyro_raw.y = gyro[1];
	sen.gyro_raw.z = gyro[2];
	sen.gyro_time = timestamp;
	sen.gyro.x = (float)gyro[0] * sen.gyro_fsr / 32768;
	sen.gyro.y = (float)gyro[1] * sen.gyro_fsr / 32768;
	sen.gyro.z = (float)gyro[2] * sen.gyro_fsr / 32768;
}

void inv_build_accel(short *accel, unsigned long timestamp)
{
	sen.accel_raw.x = accel[0];
	sen.accel_raw.y = accel[1];
	sen.accel_raw.z = accel[2];
	
	sen.accel.x = (float)(accel[0]) * sen.accel_fsr * GRAVITY / 327.68f;
	sen.accel.y = (float)(accel[1]) * sen.accel_fsr * GRAVITY / 327.68f;
	sen.accel.z = (float)(accel[2]) * sen.accel_fsr * GRAVITY / 327.68f - 1000;
//	sen.vel_x+=(timestamp-sen.accel_time)*(sen.ACC_X-sen.ax_off)/1000;
//	sen.vel_y+=(timestamp-sen.accel_time)*(sen.ACC_Y-sen.ay_off)/1000;
	sen.accel_time = timestamp;
//	get_acc_offset();
}

void inv_build_quat(long *quat, unsigned long timestamp)
{
	float q0, q1, q2, q3;
	q0 = quat[0] / q30;
	q1 = quat[1] / q30;
	q2 = quat[2] / q30;
	q3 = quat[3] / q30;
	sen.angle.pitch = asin(2 * q0 * q2 - 2 * q1 * q3) * 57.29578f - sen.angle_offset.pitch + (sen.angle_test_offset.pitch - 10);
	sen.angle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.29578f - sen.angle_offset.roll + (sen.angle_test_offset.roll - 10);
	sen.angle.yaw = atan2(2 * (q1*q2 + q0*q3), q0*q0 + q1*q1 - q2*q2 - q3*q3) * 57.29578f - sen.angle_offset.yaw + (sen.angle_test_offset.yaw - 10);
	if(sen.angle.yaw<-180)
		sen.angle.yaw+=360;
	else if(sen.angle.yaw>180)
		sen.angle.yaw-=360;
	sen.quat_time = timestamp;
}

void inv_build_compass(short *compass_short, unsigned long timestamp)
{
	sen.compass_raw.x = compass_short[0];
	sen.compass_raw.y = compass_short[1];
	sen.compass_raw.z = compass_short[2];
	sen.compass_time = timestamp;
}


