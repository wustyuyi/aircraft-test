#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 

u8 oldsize=0;

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   

//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_DC_Set();   	  
} 
//设置坐标 x：0~127 y：0~7
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(u8 n0,u8 i0,u8 n1,u8 i1)  
{ 
	u8 i,n;
	for(i=i0;i<=i1;i++)
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (n0&0x0f,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte ((n0>>4)|0x10,OLED_CMD);      //设置显示位置—列高地址
		for(n=n0;n<=n1;n++)
			OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~7
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^n函数
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size,u8 mode)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode)
				OLED_ShowChar(x+(size/2)*t,y,' ');
				else
				OLED_ShowChar(x+(size/2)*t,y,'0');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 
//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 
//t<t1 :0~127 y:1~64 mode:0/1
void OLED_Draw_Line(u8 t,u8 t1,u8 y,u8 mode)
{
	u8 y0,y1,dat,sum;
	if(mode)											
	{
		y0=(y-1)/8;
		y1=(y-1)%8;
		OLED_Set_Pos(t,y0);
		dat=0x80>>(8-y1-1);
		for(;t<=t1;t++)
		{
			OLED_WR_Byte(dat,OLED_DATA);
		}
	}
	else
	{
		y0=(t-1)/8;
		y1=(t-1)%8;
		sum=y0;
		OLED_Set_Pos(y,sum++);
		if(!(t1-t+y1+1)/8)
		{
			dat=(0xff<<(y1-1))&(0xff>>(8-y1));
			OLED_WR_Byte(dat,OLED_DATA);
			return;
		}
		else
		{
			dat=0xff<<y1;
		}
		OLED_WR_Byte(dat,OLED_DATA);
		y0=(t1-t-7+y1)/8;
		y1=(t1-t-7+y1)%8;
		for(;y0>0;y0--)
		{
			OLED_Set_Pos(y,sum++);
			OLED_WR_Byte(0xff,OLED_DATA);
		}
		if(y1)
		{
			OLED_Set_Pos(y,sum);
			dat=0xff>>(8-y1);
			OLED_WR_Byte(dat,OLED_DATA);
		}
	}
}
//n化成整数要小于4294967295。。。
void OLED_ShowFloat(u8 x,u8 y,double n,u8 size)
{
	
	u8 temp=0,t=0;
	int l=n;
	u32 num;
	
	do{
		num=n*oled_pow(10,t);
	}while((n*oled_pow(10,t++)-num)&&t<=size);
	do{
		l=l/10;
		temp++;
	}while(l);
	if(oldsize!=(temp+t))
	{
		OLED_Clear(x,y,x+8*oldsize,y+1);
		oldsize = temp+t;
	}	
	OLED_ShowNum(x,y,n,temp,SIZE,0);
	OLED_ShowChar(x+8*temp,y,'.');
	OLED_ShowNum(x+8*temp+8,y,num,t-1,SIZE,0);
}

void TV()
{
	  OLED_Draw_Line(1,15,15,H);	//上边框
		OLED_Draw_Line(5,15,16,V);
		OLED_Draw_Line(17,45,5,H);
		OLED_Draw_Line(5,15,46,V);
		OLED_Draw_Line(47,79,15,H);
		OLED_Draw_Line(5,15,80,V);
		OLED_Draw_Line(81,109,5,H);
		OLED_Draw_Line(5,15,110,V); 
		
		OLED_Draw_Line(111,126,15,H); //下以及左右边框
		OLED_Draw_Line(15,64,0,V);
		OLED_Draw_Line(15,64,127,V);
		OLED_Draw_Line(1,126,64,H);
		
    OLED_Draw_Line(55,73,48,H); //嘴
		
		OLED_Draw_Line(20,42,30,H); //眼
		OLED_Draw_Line(84,106,30,H);
	
    OLED_Delay_ms(500);
		OLED_Draw_Line(50,78,40,H);
		OLED_Draw_Line(50,78,56,H);
		OLED_Draw_Line(40,56,49,V);
		OLED_Draw_Line(40,56,79,V);

		OLED_Delay_ms(500);
		OLED_Clear(0,0,127,7); 
}




//初始化SSD1306					    
void OLED_Init(void)
{ 	
 
 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	 //使能PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOE, &GPIO_InitStructure);	  //初始化GPIOE2,3,4,5

  OLED_RST_Set();
	OLED_Delay_ms(100);
	OLED_RST_Clr();
	OLED_Delay_ms(100);
	OLED_RST_Set(); 
			  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
		
	OLED_Clear(0,0,127,7); 
	OLED_Set_Pos(0,0); 	
}

/*
 *  延时函数
 */
void OLED_Delay_ms(uint16_t ms)
{                         
	uint16_t a;

	while (ms)
	{
		a = 13350;
		while (a--);
		ms --;
	}
	return;
}

