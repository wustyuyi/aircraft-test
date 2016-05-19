#include "menu.h"

void menu_Showsen()
{	
		OLED_ShowNum(16,0,sen.high,3,16,1);
		OLED_ShowFloat(16,2,sen.angle.pitch,3);
		OLED_ShowFloat(16,4,sen.angle.roll,3);
		OLED_ShowFloat(16,6,sen.angle.yaw,3);
}



void menu_Showtime()
{	
		OLED_ShowNum(0,0,Time/3600,2,16,0);
//		OLED_ShowString(16,0,":");
		OLED_ShowNum(24,0,Time%3600/60,2,16,0);
//		OLED_ShowString(40,0,":");
		OLED_ShowNum(48,0,Time%60,2,16,0);
}



void menu_Setsen()
{
	u8 position = 1;
	while(1)
	{
		switch(Key_Scan())
		{
			case 1:
				OLED_Clear(120,position*2-2,127,position*2-2+1);
				position++;
				if(position>4)
					position = 1;
				OLED_ShowChar(120,position*2-2,'S');
			break;
			case 2:
				OLED_Clear(120,position*2-2,127,position*2-2+1);
				position--;
			  if(position<1)
					position = 4;
				OLED_ShowChar(120,position*2-2,'S');
			break;
			case 3:
				if(position==1)
				{
					Expect.hight++;
				}
				else if(position==2)
				{
					sen.angle_test_offset.pitch+=0.01f;
				}
				else if(position==3)
				{
					sen.angle_test_offset.roll+=0.01f;
				}
				else if(position==4)
				{
					sen.angle_test_offset.yaw+=0.01f;
				}
			break;
			case 4:
				if(position==1)
				{
					Expect.hight--;
				}
				else if(position==2)
				{
					sen.angle_test_offset.pitch-=0.01f;
				}
				else if(position==3)
				{
					sen.angle_test_offset.roll-=0.01f;
				}
				else if(position==4)
				{
					sen.angle_test_offset.yaw-=0.01f;
				}
			break;
			case 5:
				
			break;
			case 6:
				goto ret;
			break;
			default:
				break;
		}
		
		OLED_ShowNum(72,0,Expect.hight,3,18,0);
		OLED_ShowFloat(72,2,sen.angle_test_offset.pitch - 10.00f,2);
		OLED_ShowFloat(72,4,sen.angle_test_offset.roll - 10.00f,2);
		OLED_ShowFloat(72,6,sen.angle_test_offset.yaw - 10.00f,2);	
	}
	ret: ;
		
}

void menu_Run()
{
	switch(menu_Mode)
	{
		case show_time_1:
			OLED_Clear(0,0,127,7);
			OLED_ShowString(16,0,":");
			OLED_ShowString(40,0,":");
		  menu_Showtime(); 
		  menu_Mode = show_time;
		break;
		case show_time : 
			menu_Showtime(); 		
		break;
		case show_sen_1:
			OLED_Clear(0,0,127,7);
			OLED_ShowString(16+24,0,"cm");	
			OLED_ShowString(0,0,"H:");
			OLED_ShowString(0,2,"P:");
			OLED_ShowString(0,4,"R:");
			OLED_ShowString(0,6,"Y:");
		  menu_Showsen();
			menu_Mode = show_sen;
		break;
		case show_sen : 			
			menu_Showsen();
		break;
		case set_sen_1:
			OLED_ShowString(0,0,"S_Height:");
			OLED_ShowString(0,2,"P_offset:");
			OLED_ShowString(0,4,"R_offset:");
			OLED_ShowString(0,6,"Y_offset:");
			OLED_ShowNum(72,0,Expect.hight,3,18,0);
			OLED_ShowFloat(72,2,sen.angle_test_offset.pitch - 10.00f,2);
		  OLED_ShowFloat(72,4,sen.angle_test_offset.roll - 10.00f,2);
		  OLED_ShowFloat(72,6,sen.angle_test_offset.yaw - 10.00f,2);
			OLED_ShowChar(120,0,'S');
			menu_Mode = set_sen;
		break;
		case set_sen:
			menu_Setsen();
		menu_Mode = show_time_1;
		break;
		default:
		break;
	}		
}

void menu_key()
{
	switch(Key_Scan())
	{
		case 1:
			menu_Mode = show_time_1;
		break;
		case 2:
			menu_Mode = show_sen_1;
		break;
		case 3:
			menu_Mode = set_sen_1;
		break;
		case 4:
			
		break;
		case 5:
			
		break;
		case 6:	
			menu_Mode = show_time_1;
		break;
		default:
			break;
	}
}



