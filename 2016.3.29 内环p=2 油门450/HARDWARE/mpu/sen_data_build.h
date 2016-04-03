#ifndef __SEN_DATA_BUILD_H
#define __SEN_DATA_BUILD_H

#include "stdint.h"
#include <math.h>
//#include "arm_math.h"
#include "struct.h"

#define EXTRA_PRECISION 5 // trick to add more precision to the pressure and temp readings
#define GRAVITY         (9.793f)
#define q30  (1073741824.0f)

#define _abs(x) ((x)>=0?(x):-(x))
#define _min(x,y) (x>y?y:x)
#define _max(x,y) (x>y?x:y)
#define _maxmin(x,mx,mi) (mx<(x) ?  mx : (mi<(x) ? (x) : mi))





void inv_build_gyro(short *gyro,unsigned long timestamp);
void inv_build_accel(short *accel, unsigned long timestamp);
void inv_build_quat(long *quat, unsigned long timestamp);
void inv_build_compass(short *compass_short, unsigned long timestamp);



#endif //__SEN_DATA_BUILD_H
