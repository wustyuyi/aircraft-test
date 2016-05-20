#include "data_sent.h"
#include "string.h"


float ParaOne = 10,ParaTwo = 20;
uint32_t ParaThree = 30,ParaFour = 40;



uint32_t *P_INI[Par_Num + 6];
uint16_t P_TYPE[Par_Num + 6];

uint8_t aTxBuffer[TX_BUF_SIZE];
uint8_t aRxBuffer [RX_BUF_SIZE];
//uint16_t temp_addr=sizeof(Data_Type);


//两个指针指向相同的内容
Data_Type *Sent_Data=(Data_Type*)aTxBuffer;

void DataNum_load(void)
{
	float    temp_float;
	uint32_t temp_32=0;
	int  cont=0;
	
  #if(DataNum>=1)
	{			
		temp_float=DefaultParValue1;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}	
	#endif
	#if(DataNum>=2)
	{
		temp_float=DefaultParValue2;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=3)
	{
		temp_float=DefaultParValue3;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=4)
	{
		temp_float=DefaultParValue4;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=5)
	{
		temp_float=DefaultParValue5;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=6)
	{
		temp_float=DefaultParValue6;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=7)
	{
		temp_float=DefaultParValue7;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=8)
	{
		temp_float=DefaultParValue8;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=9)
	{
		temp_float=DefaultParValue9;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=10)
	{
		temp_float=DefaultParValue10;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=11)
	{
		temp_float=DefaultParValue11;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=12)
	{
		temp_float=DefaultParValue12;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=13)
	{
		temp_float=DefaultParValue13;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=14)
	{
		temp_float=DefaultParValue14;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=15)
	{
		temp_float=DefaultParValue15;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=16)
	{
		temp_float=DefaultParValue16;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=17)
	{
		temp_float=DefaultParValue17;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=18)
	{
		temp_float=DefaultParValue18;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=19)
	{
		temp_float=DefaultParValue19;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=20)
	{
		temp_float=DefaultParValue20;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=21)
	{
		temp_float=DefaultParValue21;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=22)
	{
		temp_float=DefaultParValue22;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=23)
	{
		temp_float=DefaultParValue23;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=24)
	{
		temp_float=DefaultParValue24;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=25)
	{
		temp_float=DefaultParValue25;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=26)
	{
		temp_float=DefaultParValue26;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=27)
	{
		temp_float=DefaultParValue27;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=28)
	{
		temp_float=DefaultParValue28;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=29)
	{
		temp_float=DefaultParValue29;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=30)
	{
		temp_float=DefaultParValue30;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&temp_float,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=31)
	{
		temp_float=DefaultParValue31;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue31,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=32)
	{
		temp_float=DefaultParValue32;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue32,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=33)
	{
		temp_float=DefaultParValue33;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue33,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=34)
	{
		temp_float=DefaultParValue34;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue34,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=35)
	{
		temp_float=DefaultParValue35;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue35,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=36)
	{
		temp_float=DefaultParValue36;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue36,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=37)
	{
		temp_float=DefaultParValue37;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue37,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=38)
	{
		temp_float=DefaultParValue38;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue38,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=39)
	{
		temp_float=DefaultParValue39;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue39,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
	#if(DataNum>=40)
	{
		temp_float=DefaultParValue40;
		memcpy(Sent_Data->Data_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultParValue40,4);cont+=4;	
		temp_32=(uint32_t)(~temp_32);
		memcpy(Sent_Data->Data_Con+cont,&temp_32,4);cont+=4;	
	}
	#endif
}
	

void ParNum_load(void)
{
	float    temp_float;
	uint32_t temp_32=0;
	int  cont=0;

	#if(Par_Num>=1)
	{
		temp_float=DefaultFlashValue1;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue1,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=2)
	{
		temp_float=DefaultFlashValue2;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue2,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=3)
	{
		temp_float=DefaultFlashValue3;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue3,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=4)
	{
		temp_float=DefaultFlashValue4;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue4,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=5)
	{
		temp_float=DefaultFlashValue5;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue5,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=6)
	{
		temp_float=DefaultFlashValue6;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue6,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=7)
	{
		temp_float=DefaultFlashValue7;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue7,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=8)
	{
		temp_float=DefaultFlashValue8;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue8,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=9)
	{
		temp_float=DefaultFlashValue9;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue9,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=10)
	{
		temp_float=DefaultFlashValue10;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue10,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=11)
	{
		temp_float=DefaultFlashValue11;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue11,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=12)
	{
		temp_float=DefaultFlashValue12;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue12,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=13)
	{
		temp_float=DefaultFlashValue13;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue13,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=14)
	{
		temp_float=DefaultFlashValue14;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue14,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=15)
	{
		temp_float=DefaultFlashValue15;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue15,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=16)
	{
		temp_float=DefaultFlashValue16;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue16,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=17)
	{
		temp_float=DefaultFlashValue17;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue17,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=18)
	{
		temp_float=DefaultFlashValue18;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue18,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=19)
	{
		temp_float=DefaultFlashValue19;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue19,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=20)
	{
		temp_float=DefaultFlashValue20;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue20,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=21)
	{
		temp_float=DefaultFlashValue21;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue21,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=22)
	{
		temp_float=DefaultFlashValue22;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue22,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=23)
	{
			temp_float=DefaultFlashValue23;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue23,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=24)
	{
		temp_float=DefaultFlashValue24;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue24,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=25)
	{
		temp_float=DefaultFlashValue25;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue25,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=26)
	{
		temp_float=DefaultFlashValue26;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue26,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=27)
	{
		temp_float=DefaultFlashValue27;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue27,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=28)
	{
		temp_float=DefaultFlashValue28;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue28,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=29)
	{
		temp_float=DefaultFlashValue29;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue29,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=30)
	{
		temp_float=DefaultFlashValue30;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue30,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=31)
	{
		temp_float=DefaultFlashValue31;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue31,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=32)
	{
		temp_float=DefaultFlashValue32;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue32,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=33)
	{
		temp_float=DefaultFlashValue33;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue33,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=34)
	{
		temp_float=DefaultFlashValue34;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue34,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=35)
	{
		temp_float=DefaultFlashValue35;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue35,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=36)
	{
		temp_float=DefaultFlashValue36;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue36,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=37)
	{
		temp_float=DefaultFlashValue37;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue37,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=38)
	{
		temp_float=DefaultFlashValue38;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue38,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=39)
	{
		temp_float=DefaultFlashValue39;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue39,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
	#if(Par_Num>=40)
	{
		temp_float=DefaultFlashValue40;
		memcpy(Sent_Data->Par_Con+cont,&temp_float,4);
		memcpy(&temp_32,&DefaultFlashValue40,4);cont+=4;	
		temp_32=~temp_32;
		memcpy(Sent_Data->Par_Con+cont,&temp_32,4);cont+=4;
	}
	#endif
}
	

//void ImageLoad(void)
//{
//	uint8_t row,line,i,temp_data=0;
//	
//  uint8_t *Data_Image=Sent_Data->Image;
//	
//	for(row=0;row<70;row++)
//	{
//		for(line=0;line<(200>>3);line++)
//		{		
//			if(line<10&&row<60)
//			{
//				temp_data=0x00;
//				for(i=0;i<4;i++)
//				{
//					temp_data|=BIT_IMAGE[row][line*8+i]<<(7-i*2);
//					temp_data|=BIT_IMAGE[row][line*8+i]<<(7-i*2-1);
//				}
//				*Data_Image++=temp_data;
//				temp_data=0x00;
//				for(i=4;i<8;i++)
//				{
//					temp_data|=BIT_IMAGE[row][line*8+i]<<(7-(i-4)*2);
//					temp_data|=BIT_IMAGE[row][line*8+i]<<(7-(i-4)*2-1);
//				}
//				*Data_Image++=temp_data;
//			}
//			else if(line>=20||row>=60)*Data_Image++=0xff;
//		}
//	}
//}

void DataLoad(void)
{
	Sent_Data->Verific[0]=1;
  Sent_Data->Verific[1]=2;
  Sent_Data->Verific[2]=3;
  Sent_Data->Verific[3]=4;
  Sent_Data->Verific[4]=5; 
	Sent_Data->Parameter_Num=Par_Num;
	Sent_Data->Coefficient_Num=DataNum;
	
	DataNum_load();
	ParNum_load();
	
#if(Send_Mode==ParMODE)
	Sent_Data->Pixels_height=0;
	Sent_Data->Pixels_width=0;
#elif(Send_Mode==PicMODE)
	Sent_Data->Pixels_height=70;
	Sent_Data->Pixels_width=200;
//	ImageLoad();
#endif
}


void SetBuffToData(Fest Data,uint8_t Addr)
{
	switch(P_TYPE[Addr])
	{
		case UINT: *P_INI[Addr] = Data.Dataf32;break;
		
		case IINT: *P_INI[Addr] = Data.Dataf32;break;
		
		case FLOAT:*P_INI[Addr] = Data.DataU32;break;
		
		default:break;
	}	
}



void OnReadPar(void)
{
	uint8_t *P_GetBuff = (uint8_t *)aRxBuffer;
	Fest *tmp = (Fest *)aRxBuffer;
//		switch(P_TYPE[P_GetBuff[8]])
//    {
//			case UINT: *P_INI[P_GetBuff[8]] = (uint32_t)*(float *)(P_GetBuff);break;
//			
//			case IINT: *P_INI[P_GetBuff[8]] = (int)*(float *)(P_GetBuff);break;
//			
//			case FLOAT:*(uint32_t *)P_INI[P_GetBuff[8]] = *(uint32_t *)(P_GetBuff);break;
//			
//			default:break;
//		}
	
	SetBuffToData(*tmp,P_GetBuff[8]);
//		OLED_Write_Value(10,6,P_GetBuff[8]);
		
		
}





void ReadData_Init()
{
	#if(Par_Num >= 1)
	{
		P_INI[0] = (uint32_t *)&DefaultFlashValue1;
    P_TYPE[0] = DefaultFlashType1;
	}
	#endif
	#if(Par_Num >= 2)
	{
		P_INI[1] = (uint32_t *)&DefaultFlashValue2;
    P_TYPE[1] = DefaultFlashType2;
	}
	#endif
	#if(Par_Num >= 3)
	{
		P_INI[2] = (uint32_t *)&DefaultFlashValue3;
    P_TYPE[2] = DefaultFlashType3;
	}
	#endif
	#if(Par_Num >= 4)
	{
		P_INI[3] = (uint32_t *)&DefaultFlashValue4;
    P_TYPE[3] = DefaultFlashType4;
	}
	#endif
	#if(Par_Num >= 5)
	{
		P_INI[4] = (uint32_t *)&DefaultFlashValue5;
    P_TYPE[4] = DefaultFlashType5;
	}
	#endif
	#if(Par_Num >= 6)
	{
		P_INI[5] = (uint32_t *)&DefaultFlashValue6;
    P_TYPE[5] = DefaultFlashType6;
	}
	#endif
	#if(Par_Num >= 7)
	{
		P_INI[6] = (uint32_t *)&DefaultFlashValue7;
    P_TYPE[6] = DefaultFlashType7;
	}
	#endif
	#if(Par_Num >= 8)
	{
		P_INI[7] = (uint32_t *)&DefaultFlashValue8;
    P_TYPE[7] = DefaultFlashType8;
	}
	#endif
	#if(Par_Num >= 9)
	{
		P_INI[8] = (uint32_t *)&DefaultFlashValue9;
    P_TYPE[8] = DefaultFlashType9;
	}
	#endif
	#if(Par_Num >= 10)
	{
		P_INI[9] = (uint32_t *)&DefaultFlashValue10;
    P_TYPE[9] = DefaultFlashType10;
	}
	#endif
	#if(Par_Num >= 11)
	{
		P_INI[10] = (uint32_t *)&DefaultFlashValue11;
    P_TYPE[10] = DefaultFlashType11;
	}
	#endif
	#if(Par_Num >= 12)
	{
		P_INI[11] = (uint32_t *)&DefaultFlashValue12;
    P_TYPE[11] = DefaultFlashType12;
	}
	#endif
	#if(Par_Num >= 13)
	{
		P_INI[12] = (uint32_t *)&DefaultFlashValue13;
    P_TYPE[12] = DefaultFlashType13;
	}
	#endif
	#if(Par_Num >= 14)
	{
		P_INI[13] = (uint32_t *)&DefaultFlashValue14;
    P_TYPE[13] = DefaultFlashType14;
	}
	#endif
	#if(Par_Num >= 15)
	{
		P_INI[14] = (uint32_t *)&DefaultFlashValue15;
    P_TYPE[14] = DefaultFlashType15;
	}
	#endif
	#if(Par_Num >= 16)
	{
		P_INI[15] = (uint32_t *)&DefaultFlashValue16;
    P_TYPE[15] = DefaultFlashType16;
	}
	#endif
	#if(Par_Num >= 17)
	{
		P_INI[16] = (uint32_t *)&DefaultFlashValue17;
    P_TYPE[16] = DefaultFlashType17;
	}
	#endif
	#if(Par_Num >= 18)
	{
		P_INI[17] = (uint32_t *)&DefaultFlashValue18;
    P_TYPE[17] = DefaultFlashType18;
	}
	#endif
	#if(Par_Num >= 19)
	{
		P_INI[18] = (uint32_t *)&DefaultFlashValue19;
    P_TYPE[18] = DefaultFlashType19;
	}
	#endif
	#if(Par_Num >= 20)
	{
		P_INI[19] = (uint32_t *)&DefaultFlashValue20;
    P_TYPE[19] = DefaultFlashType20;
	}
	#endif

}

