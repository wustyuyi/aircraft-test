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
float rc=450; //�������ת��
/////////////////////////////////////////
int Hight=0;  //�߶� ��λcm
u8 USEHIGHT = 0; //0��ʹ�ö��� 1ʹ�ö���
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
	
}


