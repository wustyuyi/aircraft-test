/*********************************************************************
File    : gpio.h
Purpose : 
**********************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

/************************** Includes ***********************************/
/****************************** Defines *******************************/
#define ENABLE_INV_INTERRUPTS  EnableInvInterrupt()
#define DISABLE_INV_INTERRUPTS DisableInvInterrupt()

#define COIN_UP (GPIOD->BSRRL = GPIO_Pin_9)
#define COIN_DOWN (GPIOD->BSRRH = GPIO_Pin_9)

/***************************Globals *******************************************/
/***************************** Prototypes *****************************/
void GPIO_Config(void);
void EnableInvInterrupt(void);
void DisableInvInterrupt(void);
#endif // __GPIO_H__

