/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  LedGrid_Interface.h
 *		  Layer:  Hal
 *       Module:  LedGrid
 *		Version:  1.0
 *	
 *  Description:  A header file that contains function prototypes of the LED grid module and includes its types.
 *  
 *********************************************************************************************************************/
#ifndef LEDGRID_INTERFACE_H 
#define LEDGRID_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LedGrid_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t LedGrid_TurnOn(LedGrid_Config_t *Copy_LedGridConfig)
* \Description     : Turn the LED grid on
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LedGridConfig    Pointer to structure of LedGrid configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t LedGrid_TurnOn(LedGrid_Config_t *Copy_LedGridConfig);

/******************************************************************************
* \Syntax          : ErrorState_t LedGrid_TurnOff(LedGrid_Config_t *Copy_LedGridConfig)
* \Description     : Turn the LED grid off
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LedGridConfig    Pointer to structure of LedGrid configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t LedGrid_TurnOff(LedGrid_Config_t *Copy_LedGridConfig);

/******************************************************************************
* \Syntax          : ErrorState_t LedGrid_GetState(LedGrid_Config_t *Copy_LedGridConfig, u8 *Copy_LedGridState)
* \Description     : Get the LED grid current state(on or off)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LedGridConfig    Pointer to structure of LedGrid configuration
* \Parameters (out): Copy_LedGridState     Pointer to assign the LedGrid current state to this variable
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t LedGrid_GetState(LedGrid_Config_t *Copy_LedGridConfig, u8 *Copy_LedGridState);

#endif  /* LEDGRID_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: LedGrid_Interface.h
 *********************************************************************************************************************/
