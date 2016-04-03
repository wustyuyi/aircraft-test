#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define ON 1
#define OFF 0


#define LED(x) if(x) \
							 GPIO_ResetBits(GPIOD,GPIO_Pin_4);\
							 else  \
							 GPIO_SetBits(GPIOD,GPIO_Pin_4)
							 
							 
void Led_Init(void);

#endif
