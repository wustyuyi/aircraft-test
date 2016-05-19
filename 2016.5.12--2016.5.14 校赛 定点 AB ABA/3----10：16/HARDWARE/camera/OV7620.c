#include "OV7620.h"
#include "sccb.h"

uint8_t IMAGE[IMG_H][IMG_W];             //最原始的数据
__IO uint8_t DCMI_FINSH=0;

void OV7620_Config(void)
{
	SCCB_Init();
	
	SCCB_WR_Reg(0x2d,0x91);      //这个寄存器的第四位为0表示亮度由0x06寄存器控制,否则自动控制
	SCCB_WR_Reg(0x06,0x0f);      //控制这个寄存器控制亮度
	SCCB_WR_Reg(0x11,0x80);      //这个控制OV7620时钟输出速度，上电后会默认0x00,所以必须写入，否则输出速度太大
	SCCB_WR_Reg(0x14,0x24);			 //320X240
//	SCCB_WR_Reg(0x14,0x04);		 //640X480
	SCCB_WR_Reg(0x28,0x00);      //隔行扫描
//	SCCB_WR_Reg(0x28,0x20);    //逐行扫描
	
	SCCB_WR_Reg(0x17,0x2f);//水平窗口的开始0x2F
	SCCB_WR_Reg(0x18,0xcf);//水平窗口的结束0xCF
	SCCB_WR_Reg(0x19,0x06);//垂直窗口开始0x06
	SCCB_WR_Reg(0x1a,0xf5);//垂直窗口结束0xF5
//	SCCB_WR_Reg(0x17,0x57);//水平窗口的开始0x57
//	SCCB_WR_Reg(0x18,0xA7);//水平窗口的结束0xA7
//	SCCB_WR_Reg(0x19,0x45);//垂直窗口开始0x45
//	SCCB_WR_Reg(0x1a,0xbc);//垂直窗口结束0xbc
	
	SCCB_WR_Reg(0x16,0x03);
	SCCB_WR_Reg(0x07,0xC7);//边缘锐化

	DCMI_Config();			//DCMI配置	
//	DCMI_DMA_Init((u32)&LCD->LCD_RAM,1,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Disable);//DCMI DMA配置 
	DCMI_DMA_Init((u32)&IMAGE,38400,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA配置 
}





