#ifndef __SYSTICK_H
#define __SYSTICK_H

#define TICK_FREQ (1000u)


#define mdelay delay_ms
#define udelay delay_us

void SysTick_init(void);
unsigned long get_tick_count(unsigned long *count);
unsigned long get_timer(void);
void delay_ms(unsigned long nTime);
void delay_us(unsigned long nTime);
void SysTick_Handler(void);




#endif	/* __SYSTICK_H */

