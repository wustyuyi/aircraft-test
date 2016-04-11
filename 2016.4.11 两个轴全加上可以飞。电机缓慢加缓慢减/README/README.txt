修改电机控制 CONTROL到pwm的5ms中断里。（为了精确控制）

将向上位机发送数据放在主循环100ms中。因为三个发送占用5ms时间。尽量少的发送。

油门由程序中默认 rc=450；

调整上位机pid格式

pitch_p_out   pitch_i_out   pitch_d_out
pitch_p_in    pitch_i_in    pitch_d_in
roll_p_out   roll_i_out   roll_d_out
roll_p_in    roll_i_in    roll_d_in
null          null           null
null          null           rc

2016-4-10



stop停止位扩展了几个状态
从0加速到指定值 缓慢加上去
中间过程修改油门是突变。
停止时缓慢减速到到100然后给0锁定。
在缓慢降落状态再发送stop紧急停机直接全0



能飞啦////


2016-4-11