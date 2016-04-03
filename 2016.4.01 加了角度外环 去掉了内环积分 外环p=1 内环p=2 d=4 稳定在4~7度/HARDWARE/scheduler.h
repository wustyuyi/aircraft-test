#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "main.h"

void Scheduler_Init(void);
void Scheduler_IRQ(void);

void Scheduler_Loop(void);

void Loop_1000Hz(void);
void Loop_500Hz(void);
void Loop_200Hz(void);
void Loop_100Hz(void);
void Loop_50Hz(void);

#endif
