能够读出原始数据 acc和gyro有毛刺 mag更加乱。
读出dmp中姿态角，各姿态角基本处在0.5波动范围内    一上电roll会偏出2度，然后慢慢恢复

dmp初始化中 自检中result原来为0x3 结果读出只有0x7

run_self_test()->mpu_run_self_test()->compass_self_test()->中的result等于0了。。

结果强制将run_self_test()中的判断改为了==0x7

