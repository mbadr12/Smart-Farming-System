/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  -
 *	   	   File:  Platform_Types.h
 *		  Layer:  LIB
 *       Module:  Platform_Types
 *		Version:  1.00
 *	
 *  Description:  Compiler Dependent types definitions      
 *  
 *********************************************************************************************************************/

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#define NUMBER_OF_PINS_PER_PORT 16

#define WORD_LENGTH_BITS 32u
#define WORD_LENGTH_BYTES 4u

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;

typedef float f32;
typedef double f64;

#endif /* PLATFORM_TYPES_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Platform_Types.h
 *********************************************************************************************************************/
