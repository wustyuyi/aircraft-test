修改电机控制 CONTROL到pwm的5ms中断里。（为了精确控制）

将向上位机发送数据放在主循环100ms中。因为三个发送占用5ms时间。尽量少的发送。

油门由程序中默认 rc=450；




stop停止位扩展了几个状态
从0加速到指定值 缓慢加上去
中间过程修改油门是突变。
停止时缓慢减速到到100然后给0锁定。
在缓慢降落状态再发送stop紧急停机直接全0



能飞啦////


2016-4-11


调整上位机pid格式

pitch_p_out   pitch_i_out   pitch_d_out   hight_p_out   hight_i_out   hight_d_out   
pitch_p_in    pitch_i_in    pitch_d_in    hight_p_in    hight_i_in    hight_d_in
roll_p_out    roll_i_out    roll_d_out    null          null          rc
roll_p_in     roll_i_in     roll_d_in
yaw_p_out     yaw_i_out     yaw_d_out
yaw_p_in      yaw_i_in      yaw_d_in

增加陀螺仪校准为紧急停机


调整pid中的积分系数  之前是除以100（10s）  现在改为除以200（5s）
积分比例系数×2 由原来0.2 -- 0.4



加yaw pid
加hight pid


2016-4-12

380油门 试飞，飞一段一个大抖动。。

读姿态放在PWM5ms中断中。
超声波放在控制主循环的Timer3的中断中
Timer3改为10ms中断一次 超声波50ms读一次。

2016-4-14

重新整定参数 
尽量减小pitch roll的内环p和d
增加了内环i积分的作用
烤四轴油门350测试效果不错

修改yaw参数 能够稳定

准备试飞



试飞成功 。 感觉yaw不够大。
~~~


2016-4-15


加了定高pid
但是注意//PID_Hight.LastAngle_Erro初值很重要 不然会出现不必要的反向积分


2016-4-17