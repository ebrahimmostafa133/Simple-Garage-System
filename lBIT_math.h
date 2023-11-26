/************************************/
/*  Author 	   : Ebrahim Mostafa	*/
/*	SWC		   : BIT MATH           */
/*  Date	   : Aug. 1				*/
/*  version    : 1.0				*/
/*  Last Edit  : N/A				*/
/*  Layer 	   : Library			*/
/************************************/

#ifndef _lBIT_math_H_
#define _lBIT_math_H_

#define CLEAR_BIT(reg,bit)       reg&=~(1<<bit)
#define SET_BIT(reg,bit)        reg |=(1<<bit)
#define TOGGLE_BIT(reg,bit)     reg ^=(1<<bit)
#define GET_BIT(reg,bit)        (((reg)>>(bit))&0x01)

#endif




