/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Valve_Interface.h
 *		  Layer:  Hal
 *       Module:  Valve (Solenoid Valve (Mini))
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the functions' prototypes of the valve
 *  
 *********************************************************************************************************************/

#ifndef VALVE_INTERFACE_H
#define VALVE_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Valve_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Valve_Open(Valve_Config_t *Copy_ValveConfig)
* \Description     : Open the valve to let the fluid go through
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_ValveConfig    Pointer to structure of valve configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Valve_Open(Valve_Config_t *Copy_ValveConfig);

/******************************************************************************
* \Syntax          : ErrorState_t Valve_Close(Valve_Config_t *Copy_ValveConfig)
* \Description     : Close the valve to stop the fluid from going through
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_ValveConfig    Pointer to structure of valve configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Valve_Close(Valve_Config_t *Copy_ValveConfig);

/******************************************************************************
* \Syntax          : ErrorState_t Valve_GetState(Valve_Config_t *Copy_ValveConfig, u8 *Copy_ValveState)
* \Description     : Get the valve current state(opened or closed)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_ValveConfig    Pointer to structure of valve configuration
* \Parameters (out): Copy_ValveState     Pointer to assign the valve current state to this variable
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Valve_GetState(Valve_Config_t *Copy_ValveConfig, u8 *Copy_ValveState);

#endif  /* VALVE_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Valve_Interface.h
 *********************************************************************************************************************/
