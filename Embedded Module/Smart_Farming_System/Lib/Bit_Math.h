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

#define SET_BIT(Var,BitNo) 		(Var|=(1<<BitNo))
#define CLR_BIT(Var,BitNo) 		(Var&=(~(1<<BitNo)))
#define TOGGLE_BIT(Var,BitNo)	(Var^=(1<<BitNo))
#define GET_BIT(Var,BitNo) 		((Var>>BitNo)&1)
#define MODIFY_REG(reg, val, msk) reg = ((reg & ~(msk)) | (val))

#endif
