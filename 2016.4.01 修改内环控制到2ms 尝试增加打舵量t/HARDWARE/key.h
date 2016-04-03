#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#define GPIO_Key GPIOE

#define KEY0_Pin  GPIO_Pin_9
#define KEY1_Pin  GPIO_Pin_10
#define KEY2_Pin  GPIO_Pin_11
#define KEY3_Pin  GPIO_Pin_12
#define KEY4_Pin  GPIO_Pin_13
#define KEY5_Pin  GPIO_Pin_14

#define Read_KEY_0 GPIO_ReadInputDataBit(GPIO_Key,KEY0_Pin)
#define Read_KEY_1 GPIO_ReadInputDataBit(GPIO_Key,KEY1_Pin)
#define Read_KEY_2 GPIO_ReadInputDataBit(GPIO_Key,KEY2_Pin)
#define Read_KEY_3 GPIO_ReadInputDataBit(GPIO_Key,KEY3_Pin)
#define Read_KEY_4 GPIO_ReadInputDataBit(GPIO_Key,KEY4_Pin)
#define Read_KEY_5 GPIO_ReadInputDataBit(GPIO_Key,KEY5_Pin)

void Key_Init(void);
u8 Key_Scan(void);

#endif
