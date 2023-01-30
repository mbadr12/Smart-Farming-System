/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  -
 *	   	   File:  BIT_MATH.h
 *		  Layer:  LIB
 *       Module:  BIT_MATH
 *		Version:  1.00
 *	
 *  Description:  Bit manipulation Function Like Macros       
 *  
 *********************************************************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define Set_Bit(Var,BitNo) 		(Var|=(1<<BitNo))
#define Clr_Bit(Var,BitNo) 		(Var&=(~(1<<BitNo)))
#define Toggle_Bit(Var,BitNo)	(Var^=(1<<BitNo))
#define Get_Bit(Var,BitNo) 		((Var>>BitNo)&1)

#endif