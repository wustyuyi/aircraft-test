#include "struct.h"

////////////////////////////////////////
struct sen_dat_s sen={0}; //��̬���
////////////////////////////////////////
struct expect Expect;
////////////////////////////////////////////
//Vector3f  filter_acc;	//�˲�������
//Vector3f  LPF_2nd_acc;
//Vector3f  filter_gyro;
//Vector3f  filter_mag;

//////////////////////////////////////////////
//Vector3f  offset_acc;	//��ƫ����
//Vector3f  offset_gyro;
//Vector3f  offset_mag;
///////////////////////////////////////////
LPF2ndData_t Acc_lpf_2nd; //���׵�ͨ�˲�
LPF2ndData_t Gyro_lpf_2nd;
///////////////////////////////////////////
Sche Scheduler;       //��ʱ����ȿ���
///////////////////////////////////////////
Matrix3f dcm;          //����
//////////////////////////////////////////
Quaternion Q;           //��Ԫ��
/////////////////////////////////////////
u16 throttle1=0,throttle2=0,throttle3=0,throttle4=0; //���������
////////////////////////////////////////
float rc=2.0,rc1 = 2.0; //pitch �������
/////////////////////////////////////////
int High = 0;
u8 USEHIGHT = 0; //0��ʹ�ö��� 1ʹ�ö���
/////////////////////////////////////////
u8 FLYMODE = 0; //����ģʽ
/////////////////////////////////////////
u16 th1,th2,th3,th4;  //���������
////////////////////////////////////////
u8 I_Lock = 0; //������
u8 OPEN_POINT = 0; //0:�رն��� 1���򿪶���
/////////////////////////////////////
int menu_Mode = show_time_1; // menuģʽ
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


