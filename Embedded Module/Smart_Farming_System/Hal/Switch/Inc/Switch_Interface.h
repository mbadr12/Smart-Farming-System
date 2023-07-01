/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Switch_Interface.c
 *		  Layer:  Hal
 *       Module:  Switch
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the functions' prototypes of the switch and including its types
 *  
 *********************************************************************************************************************/

#ifndef SWITCH_INTERFACE_H
#define SWITCH_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Switch_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Switch_Init(Switch_Config_t *Copy_SwitchConfig)
* \Description     : Initialize the switch module to use external interrupt if configured
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_SwitchConfig    Pointer to structure of switch configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Switch_Init(Switch_Config_t *Copy_SwitchConfig);

#if (SOFTWARE_DEBOUNCING == ENABLED) && (DEBOUNCING_TECHNIQUE == WAIT_AND_DOUBLE_CHECK)
/* Pointer to function for the delay used to debounce the switch */
typedef void (*Switch_Callback)(double);
#endif /* (SOFTWARE_DEBOUNCING == ENABLED) && (DEBOUNCING_TECHNIQUE == WAIT_AND_DOUBLE_CHECK) End */

#if (SOFTWARE_DEBOUNCING == ENABLED) && (DEBOUNCING_TECHNIQUE == WAIT_AND_DOUBLE_CHECK)
/******************************************************************************
* \Syntax          : ErrorState_t Switch_GetStateDebounce(Switch_Config_t *Copy_SwitchConfig, Switch_State_t *Copy_SwitchState, Switch_Callback Delay, double Copy_DelayAmount)
* \Description     : Get the switch current state(pressed or not pressed) after debouncing it
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : - Copy_SwitchConfig    Pointer to structure of switch configuration
*                    - Delay                Pointer to function for the delay used to debounce the switch
*                    - Copy_DelayAmount     The delay amount needed for debouncing the switch
* \Parameters (out): Copy_SwitchState     Pointer to return the switch current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Switch_GetStateDebounce(Switch_Config_t *Copy_SwitchConfig, Switch_State_t *Copy_SwitchState, Switch_Callback Delay, double Copy_DelayAmount);
#endif /* (SOFTWARE_DEBOUNCING == ENABLED) && (DEBOUNCING_TECHNIQUE == WAIT_AND_DOUBLE_CHECK) End */

#if IS_PERMANENT_SWITCH_USED == USED
/******************************************************************************
* \Syntax          : ErrorState_t Switch_GetState(Switch_Config_t *Copy_SwitchConfig, Switch_State_t *Copy_SwitchState)
* \Description     : Get the switch current state(pressed or not pressed)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_SwitchConfig    Pointer to structure of switch configuration
* \Parameters (out): Copy_SwitchState     Pointer to return the switch current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Switch_GetState(Switch_Config_t *Copy_SwitchConfig, Switch_State_t *Copy_SwitchState);
#endif /* IS_PERMANENT_SWITCH_USED == USED End */

#endif /* SWITCH_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Switch_Interface.h
 *********************************************************************************************************************/
