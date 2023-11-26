/************************************/
/*	Author	  :	EBRAHIM MOSTAFA		*/
/*	SWC		  : Timers				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	November 25, 2023	*/
/*	Last Edit :	N/A					*/
/************************************/

#ifndef _MTIM_INTERFACE_H_
#define _MTIM_INTERFACE_H_

#define	MTIM_TIMER0					0
#define MTIM_TIMER1					1
#define MTIM_TIMER2					2

#define MTIM_MODE_NORMAL			0
#define MTIM_MODE_CTC				1
#define MTIM_MODE_FASTPWM			2
#define MTIM_MODE_PHASECORRECTPWM	3

#define MTIM_CS_NOCLOCK				0
#define MTIM_CS_PRESCALER_1			1
#define MTIM_CS_PRESCALER_8			2
#define MTIM_CS_PRESCALER_64		3
#define MTIM_CS_PRESCALER_256		4
#define MTIM_CS_PRESCALER_1024		5
#define MTIM_CS_T0_FALLING			6
#define MTIM_CS_T0_RISING			7

#define MTIM_HWPIN_DISCONNECTED		0
#define MTIM_HWPIN_TOGGLE			1
#define MTIM_HWPIN_CLEAR			2
#define MTIM_HWPIN_SET				3
#define MTIM_HWPIN_NONINVERTING_PWM	2
#define MTIM_HWPIN_INVERTING_PWM	3

#define MTIM_INTERRUPT_T0_OVF		0
#define MTIM_INTERRUPT_T0_OCM		1

#ifndef F_CPU
#define F_CPU	8000000UL
#warning F_CPU not define. Assuming 8MHz Clock.
#endif

void MTIM_voidInit(u8 ARG_u8TimerNo, u8 ARG_u8Mode, u8 ARG_u8ClockSource, u8 ARG_u8HWPinMode);

void MTIM_voidForceOutputCompare(u8 ARG_u8TimerNo);

void MTIM_voidEnableInterrupt(u8 ARG_u8InterruptSource);
void MTIM_voidDisableInterrupt(u8 ARG_u8InterruptSource);
void MTIM_voidSetCallback(void (*ARG_pvoidfUserFunction)(void), u8 ARG_u8InterruptSource);

void MTIM_voidStartTimer(u8 ARG_u8TimerNo);
void MTIM_voidStopTimer(u8 ARG_u8TimerNo);

void MTIM_voidSetTimerValue(u8 ARG_u8TimerNO ,u16 ARG_u16Value);
u16 MTIM_voidGetTimerValue(u8 ARG_u8TimerNO );
void MTIM_voidResetTimer(u8 ARG_u8TimerNO );

void Timerl_Fast_PWM_Init(u8 duty_cycle);
void MTIM_voidSetOCR(u8 ARG_u8TimerNo, u16 ARG_u16OCRValue);

void MTIM_voidTimerDelay(u8 ARG_u8TimerNo, u32 ARG_u32Delay);



#endif
