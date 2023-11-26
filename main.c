/*
 * main.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Ebrahim mostafa
 */


#define F_CPU 8000000UL
#include <util/delay.h>
#include "lSTD_types.h"
#include "lBIT_math.h"


#include "MDIO_interface.h"
#include "HLCD_interface.h"
#include "MTIM_interface.h"

int main(void) {

	MDIO_voidSetPinDirection(MDIO_PORTD, 5, MDIO_OUTPUT);
	MDIO_voidSetPortDirection(MDIO_PORTA, 0xff);
	MDIO_voidSetPortDirection(MDIO_PORTB, 0xff);
	MDIO_voidSetPortDirection(MDIO_PORTC, 0x00);
	HLCD_voidInit();
	u8 flag_input = 0, flag_output = 0, number_of_cars = 0;
	u8 state1 = 'E', state2 = 'E', state3 = 'E', state4 = 'E';

	while (1) {
		if (MDIO_u8GetPinValue(MDIO_PORTC, 0) == 1 && MDIO_u8GetPinValue(MDIO_PORTC, 1) == 1) {

			HLCD_voidWriteString("P1:", 0, 0);
			HLCD_voidWriteChar(state1);
			HLCD_voidWriteString("P2:", 0, 5);
			HLCD_voidWriteChar(state2);
			HLCD_voidWriteString("P3:", 0, 10);
			HLCD_voidWriteChar(state3);
			HLCD_voidWriteString("P4:", 1, 0);
			HLCD_voidWriteChar(state4);

			HLCD_voidWriteString(" cars: ", 1,5);
			HLCD_voidWriteChar(number_of_cars + '0');
			HLCD_voidSetCursor(1, 12);
		}

		if (MDIO_u8GetPinValue(MDIO_PORTC, 0) == 0) {

			if (flag_input == 0 && number_of_cars < 4 && flag_output == 0) {
				HLCD_voidClearScreen();
				HLCD_voidWriteString("Car is entering", 0, 0);
				flag_input = 1;
				Timerl_Fast_PWM_Init(200);
			} else if (flag_output == 1 && number_of_cars != 0) {
				Timerl_Fast_PWM_Init(50);
				number_of_cars--;
				flag_output = 0;
				_delay_ms(1500);
			}

			else {
				if(number_of_cars==4)
				{
				HLCD_voidClearScreen();
				HLCD_voidWriteString(" Garage is full", 0, 0);
				MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_HIGH);
				}
			}
			while (MDIO_u8GetPinValue(MDIO_PORTC, 0) == 0)
			{
				if (flag_input == 1 && number_of_cars < 4 && flag_output == 0) {

					HLCD_voidWriteString("Car is entering                            ", 0, 0);
				}
			}
				;
			HLCD_voidClearScreen();
		}

		if (MDIO_u8GetPinValue(MDIO_PORTC, 1) == 0) {
			if (flag_input) {
				Timerl_Fast_PWM_Init(50);
				number_of_cars++;
				flag_input = 0;
				_delay_ms(1500);
			} else {
				if (number_of_cars != 0 && flag_output==0) {
					Timerl_Fast_PWM_Init(200);
					HLCD_voidClearScreen();
					HLCD_voidWriteString("Car is outing", 0, 0);
					flag_output = 1;
				}
			}
			while (MDIO_u8GetPinValue(MDIO_PORTC, 1) == 0)
			{
				if(number_of_cars != 0 && flag_output==1) {
					HLCD_voidWriteString("Car is outing                          ", 0, 0);
				}
			}
				;
			HLCD_voidClearScreen();
		}

		if (MDIO_u8GetPinValue(MDIO_PORTC, 2) == 0) {
			state1 = 'F';
		} else {
			state1 = 'E';
		}
		if (MDIO_u8GetPinValue(MDIO_PORTC, 3) == 0) {
			state2 = 'F';
		} else {
			state2 = 'E';
		}
		if (MDIO_u8GetPinValue(MDIO_PORTC, 4) == 0) {
			state3 = 'F';
		} else {
			state3 = 'E';
		}
		if (MDIO_u8GetPinValue(MDIO_PORTC, 5) == 0) {
			state4 = 'F';
		} else {
			state4 = 'E';
		}
		MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_LOW);
	}

}
