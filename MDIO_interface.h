/************************************/
/*  Author 	   : Ebrahim Mostafa	*/
/*	SWC		   : MDIO_interface     */
/*  Layer 	   : MCAL				*/
/*  Date	   : sep. 9		2023	*/
/*  version    : 1.1				*/
/*  Last Edit  : oct. 21	2023	*/
/************************************/

#ifndef _MDIO_INTERFACE_H_
#define _MDIO_INTERFACE_H_

#define MDIO_PORTA 0
#define MDIO_PORTB 1
#define MDIO_PORTC 2
#define MDIO_PORTD 3

#define MDIO_PORT_OUTPUT 0xff
#define MDIO_PORT_INPUT  0x00

#define MDIO_INPUT 10
#define MDIO_OUTPUT 11
#define MDIO_INPUT_PULLUP 12

#define MDIO_LOW  	0
#define MDIO_HIGH	1
#define MDIO_TOGGLE	2

		/*Port Access*/
void MDIO_voidSetPortDirection(u8 ARG_u8Port,u8 ARG_u8Direction);
void MDIO_voidSetPortValue(u8 ARG_u8Port,u8 ARG_u8Value );
u8 	 MDIO_u8GetPortValue(u8 ARG_u8Port);

		/*Pin Access*/
void MDIO_voidSetPinDirection(u8 ARG_u8Port,u8 ARG_u8Pin,u8 ARG_u8Direction);
void MDIO_voidSetPinValue(u8 ARG_u8Port,u8 ARG_u8Pin,u8 ARG_u8Value);
u8 MDIO_u8GetPinValue(u8 ARG_u8Port,u8 ARG_u8Pin);


#endif

