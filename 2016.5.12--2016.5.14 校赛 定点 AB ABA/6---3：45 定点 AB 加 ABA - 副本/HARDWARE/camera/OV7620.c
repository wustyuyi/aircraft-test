#include "OV7620.h"
#include "sccb.h"

uint8_t IMAGE[IMG_H][IMG_W];             //��ԭʼ������
__IO uint8_t DCMI_FINSH=0;

void OV7620_Config(void)
{
	SCCB_Init();
	
	SCCB_WR_Reg(0x2d,0x91);      //����Ĵ����ĵ���λΪ0��ʾ������0x06�Ĵ�������,�����Զ�����
	SCCB_WR_Reg(0x06,0x0f);      //��������Ĵ�����������
	SCCB_WR_Reg(0x11,0x80);      //�������OV7620ʱ������ٶȣ��ϵ���Ĭ��0x00,���Ա���д�룬��������ٶ�̫��
	SCCB_WR_Reg(0x14,0x24);			 //320X240
//	SCCB_WR_Reg(0x14,0x04);		 //640X480
	SCCB_WR_Reg(0x28,0x00);      //����ɨ��
//	SCCB_WR_Reg(0x28,0x20);    //����ɨ��
	
	SCCB_WR_Reg(0x17,0x2f);//ˮƽ���ڵĿ�ʼ0x2F
	SCCB_WR_Reg(0x18,0xcf);//ˮƽ���ڵĽ���0xCF
	SCCB_WR_Reg(0x19,0x06);//��ֱ���ڿ�ʼ0x06
	SCCB_WR_Reg(0x1a,0xf5);//��ֱ���ڽ���0xF5
//	SCCB_WR_Reg(0x17,0x57);//ˮƽ���ڵĿ�ʼ0x57
//	SCCB_WR_Reg(0x18,0xA7);//ˮƽ���ڵĽ���0xA7
//	SCCB_WR_Reg(0x19,0x45);//��ֱ���ڿ�ʼ0x45
//	SCCB_WR_Reg(0x1a,0xbc);//��ֱ���ڽ���0xbc
	
	SCCB_WR_Reg(0x16,0x03);
	SCCB_WR_Reg(0x07,0xC7);//��Ե��

	DCMI_Config();			//DCMI����	
//	DCMI_DMA_Init((u32)&LCD->LCD_RAM,1,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Disable);//DCMI DMA���� 
	DCMI_DMA_Init((u32)&IMAGE,38400,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA���� 
}





