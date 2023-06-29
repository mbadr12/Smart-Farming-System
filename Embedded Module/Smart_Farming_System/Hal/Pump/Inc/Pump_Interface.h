/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Pump_Interface.h
 *		  Layer:  Hal
 *       Module:  Pump (Mini Water Pump)
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the functions' prototypes of the pump
 *  
 *********************************************************************************************************************/

#ifndef PUMP_INTERFACE_H
#define PUMP_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Pump_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Pump_TurnOn(Pump_Config_t *Copy_PumpConfig)
* \Description     : Turn the mini water pump on
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_PumpConfig    Pointer to structure of pump configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Pump_TurnOn(Pump_Config_t *Copy_PumpConfig);

/******************************************************************************
* \Syntax          : ErrorState_t Pump_TurnOff(Pump_Config_t *Copy_PumpConfig)
* \Description     : Turn the mini water pump off
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_PumpConfig    Pointer to structure of pump configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Pump_TurnOff(Pump_Config_t *Copy_PumpConfig);

/******************************************************************************
* \Syntax          : ErrorState_t Pump_GetState(Pump_Config_t *Copy_PumpConfig, u8 *Copy_PumpState)
* \Description     : Get the pump current state(opened or closed)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_PumpConfig    Pointer to structure of pump configuration
* \Parameters (out): Copy_PumpState     Pointer to assign the pump current state to this variable
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Pump_GetState(Pump_Config_t *Copy_PumpConfig, u8 *Copy_PumpState);

#endif  /* PUMP_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Pump_Interface.h
 *********************************************************************************************************************/
