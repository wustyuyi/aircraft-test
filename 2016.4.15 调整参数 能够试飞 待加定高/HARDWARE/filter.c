#include "filter.h"

float acc_lpf,gyro_lpf,gyro_cf;

/*----------------------ÂË²¨Æ÷³õÊ¼»¯-------------------------*/
void Filter_Init()
{
	acc_lpf = LPF_1st_Factor_Cal(IMU_LOOP_TIME*1e-6,ACC_LPF_CUT);
	
	gyro_lpf = LPF_1st_Factor_Cal(IMU_LOOP_TIME*1e-6,GYRO_LPF_CUT);
	
	gyro_cf=CF_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_CF_TAU);
	
	LPF_2nd_Factor_Cal(IMU_LOOP_TIME * 1e-6, ACC_LPF_CUT, &Acc_lpf_2nd);
	
	LPF_2nd_Factor_Cal(IMU_LOOP_TIME * 1e-6, GYRO_LPF_CUT, &Gyro_lpf_2nd);
	
}



/*----------------------Ò»½×µÍÍ¨ÂË²¨Æ÷ÏµÊı¼ÆËã-------------------------*/
float LPF_1st_Factor_Cal(float deltaT, float Fcut)
{
	return deltaT / (deltaT + 1 / (2 * M_PI * Fcut));
}

/*----------------------Ò»½×µÍÍ¨ÂË²¨Æ÷------------------------*/
void LPF_1st(Vector3f *oldData, Vector3f *newData, float lpf_factor)
{
	oldData->x = oldData->x * (1 - lpf_factor) + newData->x * lpf_factor;
	oldData->y = oldData->y * (1 - lpf_factor) + newData->y * lpf_factor;
	oldData->z = oldData->z * (1 - lpf_factor) + newData->z * lpf_factor;
}
void LPF_1st_gyro(float *oldData,float *newData, float lpf_factor)
{
	*oldData = (*oldData) * (1 - lpf_factor) + (*newData) * lpf_factor;
}
/*----------------------¶ş½×µÍÍ¨ÂË²¨Æ÷ÏµÊı¼ÆËã-------------------------*/
void LPF_2nd_Factor_Cal(float deltaT, float Fcut, LPF2ndData_t* lpf_data)
{
	float a = 1 / (2 * M_PI * Fcut * deltaT);
	lpf_data->b0 = 1 / (a*a + 3*a + 1);
	lpf_data->a1 = (2*a*a + 3*a) / (a*a + 3*a + 1);
	lpf_data->a2 = (a*a) / (a*a + 3*a + 1);
}

/*----------------------¶ş½×µÍÍ¨ÂË²¨Æ÷------------------------*/
Vector3f LPF_2nd(LPF2ndData_t* lpf_2nd, Vector3f newData)
{
	Vector3f lpf_2nd_data;
	
	lpf_2nd_data.x = newData.x * lpf_2nd->b0 + lpf_2nd->lastout.x * lpf_2nd->a1 - lpf_2nd->preout.x * lpf_2nd->a2;
	lpf_2nd_data.y = newData.y * lpf_2nd->b0 + lpf_2nd->lastout.y * lpf_2nd->a1 - lpf_2nd->preout.y * lpf_2nd->a2;
	lpf_2nd_data.z = newData.z * lpf_2nd->b0 + lpf_2nd->lastout.z * lpf_2nd->a1 - lpf_2nd->preout.z * lpf_2nd->a2;
	
	lpf_2nd->preout = lpf_2nd->lastout;
	lpf_2nd->lastout = lpf_2nd_data;
	
	return lpf_2nd_data;
}
float LPF_2nd_gyro(LPF2ndData_t* lpf_2nd, float newData)
{
	Vector3f lpf_2nd_data;
	
	lpf_2nd_data.x = newData * lpf_2nd->b0 + lpf_2nd->lastout.x * lpf_2nd->a1 - lpf_2nd->preout.x * lpf_2nd->a2;
//	lpf_2nd_data.y = newData.y * lpf_2nd->b0 + lpf_2nd->lastout.y * lpf_2nd->a1 - lpf_2nd->preout.y * lpf_2nd->a2;
//	lpf_2nd_data.z = newData.z * lpf_2nd->b0 + lpf_2nd->lastout.z * lpf_2nd->a1 - lpf_2nd->preout.z * lpf_2nd->a2;
	
	lpf_2nd->preout = lpf_2nd->lastout;
	lpf_2nd->lastout.x = lpf_2nd_data.x;
	
	return lpf_2nd_data.x;
}

/*----------------------»¥²¹ÂË²¨Æ÷ÏµÊı¼ÆËã-------------------------*/
float CF_Factor_Cal(float deltaT, float tau)
{
	return tau / (deltaT + tau);
}

/*----------------------Ò»½×»¥²¹ÂË²¨Æ÷-----------------------------*/
Vector3f CF_1st(Vector3f gyroData, Vector3f accData, float cf_factor)
{ 
	Vector3f temp;
	temp.x = gyroData.x * cf_factor + accData.x *(1 - cf_factor);
	temp.y = gyroData.y * cf_factor + accData.y *(1 - cf_factor);
	temp.z = gyroData.z * cf_factor + accData.z *(1 - cf_factor);
	return temp;
}


#define Filter_Num 2

void Gyro_Filter(Vector3f *Gyro_in , Vector3f *Gyro_out)
{
	
	static int16_t Filter_x[Filter_Num],Filter_y[Filter_Num],Filter_z[Filter_Num];
	static uint8_t Filter_count;
	int32_t Filter_sum_x=0,Filter_sum_y=0,Filter_sum_z=0;
	uint8_t i=0;
	
	Filter_x[Filter_count] = Gyro_in->x;
	Filter_y[Filter_count] = Gyro_in->y;
	Filter_z[Filter_count] = Gyro_in->z;

	for(i=0;i<Filter_Num;i++)
	{
		Filter_sum_x += Filter_x[i];
		Filter_sum_y += Filter_y[i];
		Filter_sum_z += Filter_z[i];
	}	
	
	Gyro_out->x = Filter_sum_x / Filter_Num;
	Gyro_out->y = Filter_sum_y / Filter_Num;
	Gyro_out->z = Filter_sum_z / Filter_Num;
	
	Filter_count++;
	if(Filter_count == Filter_Num)
		Filter_count=0;
}
