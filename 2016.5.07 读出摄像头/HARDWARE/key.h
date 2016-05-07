#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#define GPIO_Key GPIOE

#define KEY0_Pin  GPIO_Pin_9
#define KEY1_Pin  GPIO_Pin_10
#define KEY2_Pin  GPIO_Pin_11

#define Read_KEY_0 GPIO_ReadInputDataBit(GPIO_Key,KEY0_Pin)
#define Read_KEY_1 GPIO_ReadInputDataBit(GPIO_Key,KEY1_Pin)
#define Read_KEY_2 GPIO_ReadInputDataBit(GPIO_Key,KEY2_Pin)

void Key_Init(void);
u8 Key_Scan(void);

#endif
