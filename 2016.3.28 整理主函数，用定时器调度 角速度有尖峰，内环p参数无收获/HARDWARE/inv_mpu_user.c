#include "inv_mpu_user.h"

//q30��ʽ,longתfloatʱ�ĳ���.
#define q30  1073741824.0f

#define Moci(x,last) ((abs(x-last))<-200 ? last : ((abs(x-last))>200 ? last : x))

//�����Ƿ�������
static signed char gyro_orientation[9] = { 1, 0, 0,
                                           0, 1, 0,
                                           0, 0, 1};
//MPU6050�Բ���
//����ֵ:0,����
//    ����,ʧ��
u8 run_self_test(void)
{
	int result;
	//char test_packet[4] = {0};
	long gyro[3], accel[3]; 
	result = mpu_run_self_test(gyro, accel);
	if (result == 0x7) //sun_ds      ֮ǰ��==0x3
	{
		/* Test passed. We can trust the gyro data here, so let's push it down
		* to the DMP.
		*/
		float sens;
		unsigned short accel_sens;
		mpu_get_gyro_sens(&sens);
		gyro[0] = (long)(gyro[0] * sens);
		gyro[1] = (long)(gyro[1] * sens);
		gyro[2] = (long)(gyro[2] * sens);
		dmp_set_gyro_bias(gyro);
		mpu_get_accel_sens(&accel_sens);
		accel[0] *= accel_sens;
		accel[1] *= accel_sens;
		accel[2] *= accel_sens;
		dmp_set_accel_bias(accel);
		return 0;
	}else return 1;
}
//�����Ƿ������
unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar; 
    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}
//����ת��
unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

//mpu6050,dmp��ʼ��
//����ֵ:0,����
//    ����,ʧ��
u8 mpu_dmp_init(void)
{
	GY_GPIO_Config(); 		//��ʼ��IIC����
	if(mpu_init()==0)	//��ʼ��MPU9150
	{	 
		if(mpu_set_sensors(INV_XYZ_GYRO|INV_XYZ_ACCEL|INV_XYZ_COMPASS)) //��������Ҫ�Ĵ�����
		return 1; else printf("mpu_set_sensor complete ......\r\n");
		if(mpu_configure_fifo(INV_XYZ_GYRO|INV_XYZ_ACCEL))//����FIFO
		return 2; else printf("mpu_configure_fifo complete ......\r\n");
		if(mpu_set_sample_rate(DEFAULT_MPU_HZ))//���ò�����
		return 3; else printf("mpu_set_sample_rate complete ......\r\n");
		if(mpu_set_compass_sample_rate(1000 / COMPASS_READ_MS))//���ò�����
		return 4; else printf("mpu_set_compass_sample_rate complete ......\r\n");
		if(dmp_load_motion_driver_firmware())		//����dmp�̼�
		return 5; else printf("dmp_load_motion_driver_firmware complete ......\r\n");
		if(dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))//���������Ƿ���
		return 6; else printf("dmp_set_orientation complete ......\r\n");
		if(dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT|DMP_FEATURE_TAP|	//����dmp����
		    DMP_FEATURE_ANDROID_ORIENT|DMP_FEATURE_SEND_RAW_ACCEL|DMP_FEATURE_SEND_CAL_GYRO|
		    DMP_FEATURE_GYRO_CAL))
		return 7; else printf("dmp_enable_feature complete ......\r\n");
		if(dmp_set_fifo_rate(DEFAULT_MPU_HZ))	//����DMP�������(��󲻳���200Hz)
		return 8; else printf("dmp_set_fifo_rate complete ......\r\n");
		if(run_self_test())		//�Լ�
		return 9; else printf("run_self_test complete  ......\r\n");
		if(mpu_set_dmp_state(1))	//ʹ��DMP
		return 10; else printf("mpu_set_dmp_state complete  ......\r\n");
	}
	return 0;
}
//�õ�dmp����������(ע��,��������Ҫ�Ƚ϶��ջ,�ֲ������е��)
//pitch:������ ����:0.1��   ��Χ:-90.0�� <---> +90.0��
//roll:�����  ����:0.1��   ��Χ:-180.0��<---> +180.0��
//yaw:�����   ����:0.1��   ��Χ:-180.0��<---> +180.0��
//����ֵ:0,����
//    ����,ʧ��
u8 mpu_dmp_get_data()
{
	float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
	unsigned long sensor_timestamp;
	short _gyro[3], _accel[3], sensors;
	short compass_short[3];
	unsigned char more;
	long quat[4]; 
	if(dmp_read_fifo(_gyro, _accel, quat, &sensor_timestamp, &sensors,&more))return 1;	 
	/* Gyro and accel data are written to the FIFO by the DMP in chip frame and hardware units.
	 * This behavior is convenient because it keeps the gyro and accel outputs of dmp_read_fifo and mpu_read_fifo consistent.
	**/
	if (sensors & INV_XYZ_GYRO )
	{
		Gyro.x = Moci(((double)_gyro[0] * MPU6050G_s2000dps+offset_gyro.x),Gyro.x);
		Gyro.y = Moci(((double)_gyro[1] * MPU6050G_s2000dps+offset_gyro.y),Gyro.y);
		Gyro.z = Moci(((double)_gyro[2] * MPU6050G_s2000dps+offset_gyro.z),Gyro.z);
		
//		Gyro.x = (double)_gyro[0] * MPU6050G_s2000dps+offset_gyro.x;
//		Gyro.y = (double)_gyro[1] * MPU6050G_s2000dps+offset_gyro.y;
//		Gyro.z = (double)_gyro[2] * MPU6050G_s2000dps+offset_gyro.z;
	}else return 1;
	if (sensors & INV_XYZ_ACCEL)
	{
		acc.x = (double)_accel[0] * MPU6050A_2mg*100+offset_acc.x;
		acc.y = (double)_accel[1] * MPU6050A_2mg*100+offset_acc.y;
		acc.z = (double)_accel[2] * MPU6050A_2mg*100+offset_acc.z;
	}else return 2;
	/* Unlike gyro and accel, quaternions are written to the FIFO in the body frame, q30.
	 * The orientation is set by the scalar passed to dmp_set_orientation during initialization. 
	**/
	if(sensors&INV_WXYZ_QUAT) 
	{
		q0 = quat[0] / q30;	//q30��ʽת��Ϊ������
		q1 = quat[1] / q30;
		q2 = quat[2] / q30;
		q3 = quat[3] / q30; 
		//����õ�������/�����/�����
		angle.pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;	// pitch
		angle.roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;	// roll
		angle.yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw
	}else return 3;
	if(!mpu_get_compass_reg(compass_short, &sensor_timestamp)) 
	{
		mag.x = compass_short[0];
		mag.y = compass_short[1];
		mag.z = compass_short[2];
	}else return 4;
	return 0;
}
