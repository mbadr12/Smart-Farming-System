/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Exti_Types.h
 *		  Layer:  Mcal
 *       Module:  Exti
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef EXTI_TYPES_H
#define EXTI_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Std_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC,
	EXTI_PORTD,
	EXTI_PORTE,
	EXTI_PORTF,
	EXTI_PORTG,
	EXTI_PORTH
}Exti_Port_t;

typedef enum
{
	EXTI_PIN0,
	EXTI_PIN1,
	EXTI_PIN2,
	EXTI_PIN3,
	EXTI_PIN4,
	EXTI_PIN5,
	EXTI_PIN6,
	EXTI_PIN7,
	EXTI_PIN8,
	EXTI_PIN9,
	EXTI_PIN10,
	EXTI_PIN11,
	EXTI_PIN12,
	EXTI_PIN13,
	EXTI_PIN14,
	EXTI_PIN15
}Exti_Pin_t;

typedef enum
{
	EXTI_RAISING_TRIGGER,
	EXTI_FALLING_TRIGGER,
	EXTI_RIS_FALL_TRIGGER
}Exti_Trigger_t;

typedef struct
{
	Exti_Port_t Port;
	Exti_Pin_t Pin;
	Exti_Trigger_t Trigger;
	void(*CallBackFunc)(void);
}Exti_PinConfig_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#endif  /* EXTI_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Exti_Types.h
 *********************************************************************************************************************/
