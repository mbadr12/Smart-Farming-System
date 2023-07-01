/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Switch_Types.c
 *		  Layer:  Hal
 *       Module:  Switch
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the types used to configure a switch
 *  
 *********************************************************************************************************************/

#ifndef SWITCH_TYPES_H
#define SWITCH_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpio_Types.h"
#include "Exti_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Switch type */
typedef enum
{
    SWITCH_PERMANENT=0,
    SWITCH_TEMPORARY
} Switch_Type_t;

/* Switch pull type */
typedef enum
{
    SWITCH_PULL_UP=0,
    SWITCH_PULL_DOWN
} Switch_Pull_t;

/* Switch state type */
typedef enum
{
    SWITCH_PRESSED=0,
    SWITCH_NOT_PRESSED
} Switch_State_t;

/* Interrupt enable type */
typedef enum
{
    SWITCH_INT_DISABLE=0,
    SWITCH_INT_ENABLE
} Switch_IntEnable_t;

/* Switch configuration structure */
typedef struct
{
    Gpio_PinId_t PinId;
    Switch_Type_t SwitchType;
    Switch_Pull_t PullType;
    Switch_IntEnable_t InterruptEnable;
    Exti_PinConfig_t *ExtiPinConfig;
} Switch_Config_t;

#endif /* SWITCH_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Switch_Types.h
 *********************************************************************************************************************/
