������λ�� �ָ�Ĭ��ֵ���趨Ϊ�����ɻ���


���ڷ���ռ��ʱ���ر𳤡�������������������
//1ms
ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,0,0,stop);   
//2ms
ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,PID_Pitch.Pout_In,PID_Pitch.Iout_In,PID_Pitch.Dout_In,0); 
//2ms
ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		


��ѭ���趨10s ����������ִ���˼��Ρ�

����ͦ��Ӱ�졣

�����ѵ��������Timer4 ��pwm���Ƶ��ж��5ms��