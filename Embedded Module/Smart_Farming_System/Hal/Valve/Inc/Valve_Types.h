/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Valve_Types.h
 *		  Layer:  Hal
 *       Module:  Valve (Solenoid Valve (Mini))
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the types used to configure the valve
 *  
 *********************************************************************************************************************/

#ifndef VALVE_TYPES_H
#define VALVE_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpio_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Valve current state value */
typedef enum
{
    VALVE_CLOSED=0,
    VALVE_OPENED
} Valve_State_t;

/* Switch Activation Value */
typedef enum
{
    VALVE_ACTIVE_LOW=0,
    VALVE_ACTIVE_HIGH
} Valve_Activation_t;

/* Valve configuration structure */
typedef struct
{
    Gpio_PinId_t PinId;
    Valve_Activation_t ActivationType;
} Valve_Config_t;

#endif  /* VALVE_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Valve_Types.h
 *********************************************************************************************************************/
