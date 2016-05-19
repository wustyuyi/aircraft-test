#ifndef _OV7620_H
#define _OV7620_H

#include "dcmi.h"
#define IMG_H 240
#define IMG_W 320
extern uint8_t IMAGE[IMG_H][IMG_W];
extern __IO uint8_t DCMI_FINSH;

void OV7620_Config(void);

#endif

