/************************************/
/*	Author	  :	EBRAHIM 			*/
/*	SWC		  : Timers				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	November 25, 2023	*/
/*	Last Edit :	N/A					*/
/************************************/

#include "lSTD_types.h"
#include "lBIT_math.h"

#include "MTIM_interface.h"
#include "MTIM_private.h"

static u8 MTIM_u8Timer0Clock = MTIM_CS_NOCLOCK;

static volatile u16 MTIM_u16Timer0OVFCount = 0;
static volatile u8	MTIM_u8Timer0Preload = 0;

static void (*MTIM_pvoidfUserFunctionT0OVF)(void) = NULL_POINTER;
static void (*MTIM_pvoidfUserFunctionT0OCM)(void) = NULL_POINTER;

void MTIM_voidInit(u8 ARG_u8TimerNo, u8 ARG_u8Mode, u8 ARG_u8ClockSource, u8 ARG_u8HWPinMode)
{
	if((ARG_u8TimerNo<=2)&&(ARG_u8Mode<=3)&&(ARG_u8ClockSource<=7)&&(ARG_u8HWPinMode<=3))
	{
		switch(ARG_u8TimerNo)
		{
			case MTIM_TIMER0:
			{
				switch(ARG_u8Mode)
				{
					case MTIM_MODE_NORMAL:
					{
						CLEAR_BIT(TCCR0, WGM01);
						CLEAR_BIT(TCCR0, WGM00);
						break;
					}
					case MTIM_MODE_CTC:
					{
						SET_BIT(TCCR0, WGM01);
						CLEAR_BIT(TCCR0, WGM00);
						break;
					}
					case MTIM_MODE_FASTPWM:
					{
						SET_BIT(TCCR0, WGM01);
						SET_BIT(TCCR0, WGM00);
						break;
					}
					case MTIM_MODE_PHASECORRECTPWM:
					{
						CLEAR_BIT(TCCR0, WGM01);
						SET_BIT(TCCR0, WGM00);
						break;
					}
					default: break; /* Report an Error */
				}
				TCCR0 = (TCCR0&0xCF) | (ARG_u8HWPinMode << COM00);
				MTIM_u8Timer0Clock = ARG_u8ClockSource;				
				break;
			}
			case MTIM_TIMER1:
			{
				switch(ARG_u8Mode)
				{
				case MTIM_MODE_NORMAL:
					{
						CLEAR_BIT(TCCR1B, WGM13);
						CLEAR_BIT(TCCR1B, WGM12);
						CLEAR_BIT(TCCR1A, WGM11);
						CLEAR_BIT(TCCR1A, WGM10);
						break;
					}
				}
				break;
			}
			case MTIM_TIMER2:
			{
				break;
			}
			default: break; /* Report an Error */
		}
	}
	else
	{
		/* Report an Error */
	}
}
/*********************************************************************************/
void Timerl_Fast_PWM_Init(u8 duty_cycle) {
	TCNT1 = 0;
	ICR1 = 2499;
	OCR1A = duty_cycle;

	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);

}
void MTIM_voidSetTimerValue(u8 ARG_u8TimerNO ,u16 ARG_u16Value)
{
	switch(ARG_u8TimerNO)
	{
	case MTIM_TIMER0 :TCNT0 =(u8) ARG_u16Value; break;
	case MTIM_TIMER1 :TCNT1 = ARG_u16Value; break;
	case MTIM_TIMER2 :break;
	default : break;
	}
}

u16 MTIM_voidGetTimerValue(u8 ARG_u8TimerNO )
{
	u16 L_u16ReturnValue =0;
	switch(ARG_u8TimerNO)
		{
		case MTIM_TIMER0 :L_u16ReturnValue=(u16)TCNT0; break;
		case MTIM_TIMER1 : L_u16ReturnValue=TCNT1; break;
		case MTIM_TIMER2 :break;
		default : break;
		}
	return L_u16ReturnValue;
}

void MTIM_voidResetTimer(u8 ARG_u8TimerNO )
{
	switch(ARG_u8TimerNO)
		{
		case MTIM_TIMER0 :TCNT0=0x00; break;
		case MTIM_TIMER1 :TCNT1=0x0000; break;
		case MTIM_TIMER2 :break;
		default : break;
		}
}

void MTIM_voidForceOutputCompare(u8 ARG_u8TimerNo)
{
	SET_BIT(TCCR0, FOC0);
}

void MTIM_voidEnableInterrupt(u8 ARG_u8InterruptSource)
{
	if(ARG_u8InterruptSource<=7)
	{
		SET_BIT(TIMSK, ARG_u8InterruptSource);
	}
	else
	{
		/* Report an Error */
	}
}

void MTIM_voidDisableInterrupt(u8 ARG_u8InterruptSource)
{
	if(ARG_u8InterruptSource<=7)
	{
		CLEAR_BIT(TIMSK, ARG_u8InterruptSource);
	}
	else
	{
		/* Report an Error */
	}
}

void MTIM_voidSetCallback(void (*ARG_pvoidfUserFunction)(void), u8 ARG_u8InterruptSource)
{
	if(ARG_pvoidfUserFunction!=NULL_POINTER)
	{
		switch(ARG_u8InterruptSource)
		{
			case MTIM_INTERRUPT_T0_OVF: MTIM_pvoidfUserFunctionT0OVF = ARG_pvoidfUserFunction; break;
			case MTIM_INTERRUPT_T0_OCM: MTIM_pvoidfUserFunctionT0OCM = ARG_pvoidfUserFunction; break;
			default: break; /* Report an Error */
		}
	}
	else
	{
		/* Report an Error */
	}
}

void MTIM_voidStartTimer(u8 ARG_u8TimerNo)
{
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0: TCCR0 = (TCCR0 & 0xF8) | MTIM_u8Timer0Clock; break;
		case MTIM_TIMER1: break;
		case MTIM_TIMER2: break;
		default: break; /* Report an Error */
	}
}

void MTIM_voidStopTimer(u8 ARG_u8TimerNo)
{
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0: TCCR0 = (TCCR0 & 0xF8) | MTIM_CS_NOCLOCK; break;
		case MTIM_TIMER1: break;
		case MTIM_TIMER2: break;
		default: break; /* Report an Error */
	}
}

void MTIM_voidSetOCR(u8 ARG_u8TimerNo, u16 ARG_u16OCRValue)
{
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0: OCR0 = (u8)ARG_u16OCRValue; break;
		case MTIM_TIMER1: break;
		case MTIM_TIMER2: break;
		default: break; /* Report an Error */
	}
}

void MTIM_voidTimerDelay(u8 ARG_u8TimerNo, u32 ARG_u32Delay)
{
	f32 L_f32TickTime, L_f32OVFTime;
	u16 L_u16Prescaler;
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0:
		{
			switch(MTIM_u8Timer0Clock)
			{
				case MTIM_CS_PRESCALER_1:		L_u16Prescaler = 1;		break;
				case MTIM_CS_PRESCALER_8:		L_u16Prescaler = 8;		break;
				case MTIM_CS_PRESCALER_64:		L_u16Prescaler = 64;	break;
				case MTIM_CS_PRESCALER_256:		L_u16Prescaler = 256;	break;
				case MTIM_CS_PRESCALER_1024:	L_u16Prescaler = 1024;	break;
				default: break; /* Error */
			}
			L_f32TickTime = (f32)L_u16Prescaler / F_CPU;
			L_f32OVFTime = L_f32TickTime * 256;
			MTIM_u16Timer0OVFCount = ((f32)ARG_u32Delay / 1000) / L_f32OVFTime;
			MTIM_u8Timer0Preload = 256 - ((ARG_u32Delay / 1000) % (u32)L_f32OVFTime);
			TCNT0 = MTIM_u8Timer0Preload;
			break;
		}
		case MTIM_TIMER1: break;
		case MTIM_TIMER2: break;
		default: break; /* Error */
	}
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)	/* T0 OCM Vector */
{
	
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)	/* T0 OVF Vector */
{
	static volatile u16 L_u16OVFCounter = 0;
	L_u16OVFCounter++;
	if(L_u16OVFCounter == (MTIM_u16Timer0OVFCount+1))
	{
		TCNT0 = MTIM_u8Timer0Preload;
		L_u16OVFCounter = 0;
		if(MTIM_pvoidfUserFunctionT0OVF!=NULL_POINTER)
		{
			(*MTIM_pvoidfUserFunctionT0OVF)();
		}
		else
		{
			/* Do nothing (MISRA) */
		}
	}
	else
	{
		/* Do nothing (MISRA) */
	}
}
