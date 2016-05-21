#ifndef _DCMI_H
#define _DCMI_H
#include "sys.h"    									

void DCMI_Config(void);
void DCMI_DMA_Init(u32 DMA_Memory0BaseAddr,u16 DMA_BufferSize,u32 DMA_MemoryDataSize,u32 DMA_MemoryInc);
void DCMI_Start(void);
void DCMI_Stop(void);

#endif


