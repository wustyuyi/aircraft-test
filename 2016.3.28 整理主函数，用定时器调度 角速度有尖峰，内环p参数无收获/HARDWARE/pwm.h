#ifndef __PWM_H
#define __PWM_H

#include "sys.h"
#include "struct.h"



void Pwm_Gpio_Init(void);
void MotoPwm_Init(void);
void Moto_PwmUpdate(uint16_t MOTO1_PWM, uint16_t MOTO2_PWM, uint16_t MOTO3_PWM, uint16_t MOTO4_PWM);
void Stop(void);

#endif
