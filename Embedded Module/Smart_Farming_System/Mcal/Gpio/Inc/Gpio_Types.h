/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Gpio_Types.h
 *		  Layer:  Mcal
 *       Module:  Gpio
 *		Version:  2.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef GPIO_TYPES_H
#define GPIO_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Std_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*Common Port Value Possible Options*/
#define GPIO_Port_LOW	0
#define GPIO_Port_HigH	0xFFFF

#define NONE			30

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	GPIO_PORTA=0,
	GPIO_PORTB,
	GPIO_PORTC,
	GPIO_PORTD,
	GPIO_PORTE,
	GPIO_PORTF,
	GPIO_PORTG,
	GPIO_PORTH
}Gpio_Port_t;

typedef enum
{
	GPIO_PIN0=0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15
}Gpio_PIN_t;

typedef enum
{
	GPIO_PIN_INPUT=0,
	GPIO_PIN_OUTPUT,
	GPIO_PIN_ALTFunc,
	GPIO_PIN_Analog
}Gpio_PinMode_t;

typedef enum
{
	GPIO_OUTPUT_PUSH_PULL=0,
	GPIO_OUTPUT_OPEN_DRAIN
}Gpio_PinOutput_t;

typedef enum
{
	GPIO_LOW_SPEED=0,
	GPIO_MEDIUM_SPEED,
	GPIO_FAST_SPEED,
	GPIO_HIGH_SPEED
}Gpio_OutputSpeed_t;

typedef enum
{
	GPIO_PIN_FLOATING=0,
	GPIO_PIN_PULL_UP,
	GPIO_PIN_PULL_DOWN
}Gpio_PinPullUpDown_t;

typedef enum
{
	GPIO_PIN_AF0=0,
	GPIO_PIN_AF1,
	GPIO_PIN_AF2,
	GPIO_PIN_AF3,
	GPIO_PIN_AF4,
	GPIO_PIN_AF5,
	GPIO_PIN_AF6,
	GPIO_PIN_AF7,
	GPIO_PIN_AF8,
	GPIO_PIN_AF9,
	GPIO_PIN_AF10,
	GPIO_PIN_AF11,
	GPIO_PIN_AF12,
	GPIO_PIN_AF13,
	GPIO_PIN_AF14,
	GPIO_PIN_AF15,
}Gpio_PinAltFunOption_t;

typedef enum
{
	GPIO_PIN_LOW=0,
	GPIO_PIN_HIGH
}Gpio_PinState_t;

typedef struct
{
	Gpio_Port_t Port;                           	/*Refer to Port Possible values*/
	Gpio_PIN_t PinNum;                         		/*Refer to Pin Number Possible values*/
	Gpio_PinMode_t Mode;                           	/*Refer to Mode Possible values*/
	Gpio_PinOutput_t OutputType;					/*Refer to Output Type Possible values*/
	Gpio_OutputSpeed_t OutputSpeed;              	/*Refer to Output Speed Possible values*/
	Gpio_PinPullUpDown_t PullUpDown;                /*Refer to Pull Up / Down Possible values*/
	Gpio_PinAltFunOption_t AlternateFuncOption;     /*Refer to Alternate FuncOption Possible values*/
}Gpio_PinConfig_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#endif  /* GPIO_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpio_Types.h
 *********************************************************************************************************************/