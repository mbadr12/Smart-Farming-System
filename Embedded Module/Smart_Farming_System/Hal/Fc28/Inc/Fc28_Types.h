/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Fc28_Types.h
 *		  Layer:  Hal
 *       Module:  Fc28
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the API types of the fc28(soil moisture) module. And it includes standard types
 *  
 *********************************************************************************************************************/
#ifndef FC28_TYPES_H
#define FC28_TYPES_H

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

/* Soil moisture state type */
typedef enum
{
    FC28_DRY_SOIL=0,
    FC28_HUMID_SOIL
} Fc28_MoistureState_t;

/* Interrupt enable type */
typedef enum
{
    FC28_INT_DISABLE=0,
    FC28_INT_ENABLE
} Fc28_DigPinIntEnable_t;

/* FC-28 configuration structure */
typedef struct
{
    Gpio_PinId_t AnalogPinId;
    Gpio_PinId_t DigitalPinId;
    Adc_Resolution Adc_Resolution;
    Adc_ConversionConfig_t *Adc_ConversionConfig;
    Fc28_DigPinIntEnable_t DigitalPinInterruptEnable;
    Exti_PinConfig_t *ExtiPinConfig;
} Fc28_Config_t;

#endif  /* FC28_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Fc28_Types.h
 *********************************************************************************************************************/
