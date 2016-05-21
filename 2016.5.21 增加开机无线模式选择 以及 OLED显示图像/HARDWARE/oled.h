#ifndef __OLED_H
#define __OLED_H
#include "sys.h"
#include "stdlib.h"	
//OLED模式设置
//4线串行模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    


//-----------------OLED端口定义----------------  					   


#define OLED_RST_Clr() GPIO_ResetBits(GPIOE,GPIO_Pin_4)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOE,GPIO_Pin_4)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOE,GPIO_Pin_5)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOE,GPIO_Pin_5)

#if OLED_MODE

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOD,GPIO_Pin_3)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOD,GPIO_Pin_3)

#define OLED_WR_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_14)
#define OLED_WR_Set() GPIO_SetBits(GPIOG,GPIO_Pin_14)

#define OLED_RD_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_13)
#define OLED_RD_Set() GPIO_SetBits(GPIOG,GPIO_Pin_13)



//PC0~7,作为数据线
#define DATAOUT(x) GPIO_Write(GPIOC,x);//输出  

#else
//使用4线串行接口时使用 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOE,GPIO_Pin_2)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOE,GPIO_Pin_2)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOE,GPIO_Pin_3)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOE,GPIO_Pin_3)

#endif
 		








/* OLED端口宏定义 */
#define OLED_SCL_PORT  GPIOE
#define OLED_SDA_PORT  GPIOE
#define OLED_RST_PORT  GPIOE
#define OLED_DC_PORT   GPIOE

#define OLED_SCL_PIN   GPIO_Pin_2     
#define OLED_SDA_PIN   GPIO_Pin_3     
#define OLED_RST_PIN   GPIO_Pin_4     
#define OLED_DC_PIN    GPIO_Pin_5     

#define OLED_SCL_CLK    RCC_AHB1Periph_GPIOE
#define OLED_SDA_CLK    RCC_AHB1Periph_GPIOE
#define OLED_RST_CLK    RCC_AHB1Periph_GPIOE
#define OLED_DC_CLK     RCC_AHB1Periph_GPIOE




/* OLED IO输出宏替换 */
#define OLED_D0_OL		GPIO_ResetBits(OLED_SCL_PORT,OLED_SCL_PIN)//D0 IO口输出低电平
#define OLED_D0_OH		GPIO_SetBits(OLED_SCL_PORT,OLED_SCL_PIN)  //D0 IO口输出高电平

#define OLED_D1_OL		GPIO_ResetBits(OLED_SDA_PORT,OLED_SDA_PIN)//D1 IO口输出低电平
#define OLED_D1_OH		GPIO_SetBits(OLED_SDA_PORT,OLED_SDA_PIN)  //D1 IO口输出高电平

#define OLED_RST_OL		GPIO_ResetBits(OLED_RST_PORT,OLED_RST_PIN)//RST IO口输出低电平
#define OLED_RST_OH		GPIO_SetBits(OLED_RST_PORT,OLED_RST_PIN)  //RST IO口输出高电平

#define OLED_DC_OL		GPIO_ResetBits(OLED_DC_PORT,OLED_DC_PIN)  //DC IO口输出低电平
#define OLED_DC_OH		GPIO_SetBits(OLED_DC_PORT,OLED_DC_PIN)    //DC IO口输出高电平


















#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define H 1 //横向画线
#define V 0 //纵向画线

//OLED控制用函数

void OLED_WrDat(uint8_t data);
void OLED_WrCmd(uint8_t cmd);
void OLED_Set_XY(uint8_t x, uint8_t y);


void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Delay_ms(uint16_t ms);
void OLED_Clear(u8 n0,u8 i0,u8 n,u8 i);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size,u8 mode);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Draw_Line(u8 t,u8 t1,u8 y,u8 mode);
void TV(void);
void OLED_ShowFloat(u8 x,u8 y,double n,u8 size);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
