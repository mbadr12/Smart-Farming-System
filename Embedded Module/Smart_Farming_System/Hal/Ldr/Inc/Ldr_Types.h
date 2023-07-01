/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Ldr_Types.h
 *		  Layer:  Hal
 *       Module:  Ldr
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the API types of the ldr module. And it includes standard types
 *  
 *********************************************************************************************************************/
#ifndef LDR_TYPES_H
#define LDR_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpio_Types.h"
#include "Exti_Types.h"
#include "Adc_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Illumination(ambiance light) state type */
typedef enum
{
    LDR_DARK=0,
    LDR_BRIGHT
} Ldr_IlluminationState_t;

/* Interrupt enable type */
typedef enum
{
    LDR_INT_DISABLE=0,
    LDR_INT_ENABLE
} Ldr_DigPinIntEnable_t;

/* LDR configuration structure */
typedef struct
{
    Gpio_PinId_t AnalogPinId;
    Gpio_PinId_t DigitalPinId;
    Adc_Resolution Adc_Resolution;
    Adc_ConversionConfig_t *Adc_ConversionConfig;
    Ldr_DigPinIntEnable_t DigitalPinInterruptEnable;
    Exti_PinConfig_t *ExtiPinConfig;
} Ldr_Config_t;

#endif  /* LDR_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Ldr_Types.h
 *********************************************************************************************************************/
