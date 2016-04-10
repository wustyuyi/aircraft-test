匿名上位机 恢复默认值被设定为锁定飞机。


串口发送占用时间特别长。。。。。。尽量少用
//1ms
ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,0,0,stop);   
//2ms
ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,PID_Pitch.Pout_In,PID_Pitch.Iout_In,PID_Pitch.Dout_In,0); 
//2ms
ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		


主循环设定10s 看各个调度执行了几次。

会有挺大影响。

决定把电机控制用Timer4 即pwm控制的中断里（5ms）