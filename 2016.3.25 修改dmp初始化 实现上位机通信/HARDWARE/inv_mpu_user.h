#ifndef __INV_MPU_USER_H
#define __INV_MPU_USER_H

#include "sys.h"
#include "mpu9150.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"


u8 run_self_test(void);
unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx);
unsigned short inv_row_2_scale(const signed char *row);
u8 mpu_dmp_init(void);
u8 mpu_dmp_get_data(float *roll,float *pitch,float *yaw);


#endif
