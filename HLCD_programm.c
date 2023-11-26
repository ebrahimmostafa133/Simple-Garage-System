/************************************/
/*  Author 	   : Ebrahim Mostafa	*/
/*	SWC		   : PROGRAMM           */
/*  Layer 	   : HAL				*/
/*  Date	   : Oct. 2		2023	*/
/*  version    : 1.0				*/
/*  Last Edit  : N/A				*/
/************************************/

#define F_CPU 8000000UL
#include "util/delay.h"

#include "lSTD_types.h"
#include "lBIT_math.h"


#include "MDIO_interface.h"
#include "HLCD_interface.h"
#include "HLCD_config.h"

static u8static_Init=0;
void HLCD_voidInit(void)
{
	MDIO_voidSetPortDirection(HLCD_DATA_PORT,0xff);
	MDIO_voidSetPinDirection(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_OUTPUT);
	_delay_ms(30);
	HLCD_voidWriteCmd(0x20);
	HLCD_voidWriteCmd(0x20);
	HLCD_voidWriteCmd(0x80);
	_delay_ms(1);
	HLCD_voidWriteCmd(0x00);
	HLCD_voidWriteCmd(0xf0);
	_delay_ms(1);
	HLCD_voidWriteCmd(0x00);
	HLCD_voidWriteCmd(0x10);
	_delay_ms(2);
	
	u8static_Init=1;
	
	
}

void HLCD_voidWriteChar(u8 ARG_ccharChar)
{
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_LOW);
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_HIGH);
	
	MDIO_voidSetPinValue(MDIO_PORTA,4,GET_BIT(ARG_ccharChar,4));
	MDIO_voidSetPinValue(MDIO_PORTA,5,GET_BIT(ARG_ccharChar,5));
	MDIO_voidSetPinValue(MDIO_PORTA,6,GET_BIT(ARG_ccharChar,6));
	MDIO_voidSetPinValue(MDIO_PORTA,7,GET_BIT(ARG_ccharChar,7));

	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_HIGH);
	_delay_us(1);
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_LOW);

	MDIO_voidSetPinValue(MDIO_PORTA,4,GET_BIT(ARG_ccharChar,0));
	MDIO_voidSetPinValue(MDIO_PORTA,5,GET_BIT(ARG_ccharChar,1));
	MDIO_voidSetPinValue(MDIO_PORTA,6,GET_BIT(ARG_ccharChar,2));
	MDIO_voidSetPinValue(MDIO_PORTA,7,GET_BIT(ARG_ccharChar,3));
	
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_HIGH);
	_delay_us(1);
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_LOW);

	
	_delay_ms(2);
}

void HLCD_voidWriteCmd(const u8 ARG_cu8Cmd)
{
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_LOW);
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_LOW);
	
	MDIO_voidSetPinValue(MDIO_PORTA,4,GET_BIT(ARG_cu8Cmd,4));
	MDIO_voidSetPinValue(MDIO_PORTA,5,GET_BIT(ARG_cu8Cmd,5));
	MDIO_voidSetPinValue(MDIO_PORTA,6,GET_BIT(ARG_cu8Cmd,6));
	MDIO_voidSetPinValue(MDIO_PORTA,7,GET_BIT(ARG_cu8Cmd,7));

	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_HIGH);
	_delay_us(1);
	MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_LOW);

	if(u8static_Init)
	{
		MDIO_voidSetPinValue(MDIO_PORTA,4,GET_BIT(ARG_cu8Cmd,0));
		MDIO_voidSetPinValue(MDIO_PORTA,5,GET_BIT(ARG_cu8Cmd,1));
		MDIO_voidSetPinValue(MDIO_PORTA,6,GET_BIT(ARG_cu8Cmd,2));
		MDIO_voidSetPinValue(MDIO_PORTA,7,GET_BIT(ARG_cu8Cmd,3));
	
		MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_HIGH);
		_delay_us(1);
		MDIO_voidSetPinValue(HLCD_CTRL_PORT,HLCD_EN_PIN,MDIO_LOW);
	
	}
	
	_delay_ms(2);

}

void HLCD_voidClearScreen(void)
{
	HLCD_voidWriteCmd(0x01);
	_delay_ms(2);
}

void HLCD_voidSetCursor(u8 ARG_u8Row, u8 ARG_u8Col)
{
	if((ARG_u8Row<=1)&&(ARG_u8Col<=15))
	{
		HLCD_voidWriteCmd((1<<7)|(ARG_u8Row<<6)|ARG_u8Col);
	}
	else
	{
		/*Report an error*/
	}
}

void HLCD_voidWriteString(const char* ARG_ccharpString,u8 ARG_u8Row, u8 ARG_u8Col)
{	
	HLCD_voidSetCursor( ARG_u8Row, ARG_u8Col);
	u8 L_u8i=0;
	u8 L_u8Line0=0;
	
	while(ARG_ccharpString[L_u8i]!='\0' &&((ARG_u8Row*16)+(L_u8i +ARG_u8Col))<32)
	{
		if(((ARG_u8Row*16)+(L_u8i+ARG_u8Col))<16)
		{
			HLCD_voidWriteChar(ARG_ccharpString[L_u8i]);
			L_u8i++;
		}
		else if(((ARG_u8Row*16)+(L_u8i+ARG_u8Col))==16&&L_u8Line0==0)
		{
			HLCD_voidSetCursor(1,0);
			L_u8Line0++;
		}
		else if(((ARG_u8Row*16)+(L_u8i+ARG_u8Col))<32)//&&L_u8Line0==1
		{
			HLCD_voidWriteChar(ARG_ccharpString[L_u8i]);
			L_u8i++;
		}
	}
}


void HLCD_voidSetCustomChar(u8* L_u8pattern,u8 L_u8CGRAMIndex)
{
	u8 L_u8address;
	u8 L_u8index;
	if(L_u8CGRAMIndex<8)
	{
		L_u8address=L_u8CGRAMIndex*8;
		L_u8address=SET_BIT(L_u8address,6);
		HLCD_voidWriteCmd(L_u8address);
		for(L_u8index=0;L_u8index<=7;L_u8index++)
		{
			HLCD_voidWriteChar(L_u8pattern[L_u8index]);
		}
	}
	HLCD_voidWriteCmd(0x02);
}


void HLCD_voidDisplayCustomChar(u8 L_u8CGRAMIndex,u8 ARG_u8Row, u8 ARG_u8Col)
{
	HLCD_voidSetCursor(ARG_u8Row,ARG_u8Col);
	HLCD_voidWriteChar(L_u8CGRAMIndex);
}
