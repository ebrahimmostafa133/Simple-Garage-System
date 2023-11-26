/************************************/
/*  Author 	   : Ebrahim Mostafa	*/
/*	SWC		   : INTERFACE          */
/*  Layer 	   : HAL				*/
/*  Date	   : Oct. 2		2023	*/
/*  version    : 1.0				*/
/*  Last Edit  : N/A				*/
/************************************/

#ifndef _HLCD_INTERFACE_H_
#define _HLCD_INTERFACE_H_

void HLCD_voidInit(void);
void HLCD_voidWriteChar(u8 ARG_ccharChar);
void HLCD_voidWriteCmd(const u8 ARG_cu8Cmd);
void HLCD_voidClearScreen(void);
void HLCD_voidWriteString(const char* ARG_ccharpString,u8 ARG_u8Row, u8 ARG_u8Col);
void HLCD_voidSetCursor(u8 ARG_u8Row, u8 ARG_u8Col);
void HLCD_voidSetCustomChar(u8* L_u8pattern,u8 L_u8CGRAMIndex);
void HLCD_voidDisplayCustomChar(u8 L_u8CGRAMIndex,u8 ARG_u8Row, u8 ARG_u8Col);

#endif