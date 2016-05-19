#ifndef __IMAGE_H
#define __IMAGE_H

#include "sys.h"
#include "ov7620.h"
#include <math.h>
#include "usart_dma.h"
#include "nrf24l01_usart.h"
#include "struct.h"

typedef struct {
	short pt1x,pt1y;
	short pt2x,pt2y;
}LINE_S;


typedef struct
{
	uint16_t CerPtx,CerPty,CerR;
	LINE_S Line[2];
	u32 time;
	uint8_t rate;
	u8 update;
}IMAGE_INF;

extern IMAGE_INF img;

void GetCenter(void);
uint16_t CheckCenterR(uint16_t *px,uint16_t *py,uint16_t m,uint16_t n,uint16_t maxR);
void sort(int *a, uint16_t n) ;

uint8_t isOnLine(int dx1,int dy1,int dx2,int dy2);
uint8_t CheckLine(uint16_t x, uint16_t y, LINE_S *pLine, uint16_t range,uint8_t dir);

uint8_t CheckLineY(void);
uint8_t CheckLineX(void);

void CameraRun(void);


void GetBitImage(void *pbuf);
void PutPixel(void *pbuf, uint16_t x, uint16_t y);

void LCD_DrawUniLine(void *pbuf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);


#endif
