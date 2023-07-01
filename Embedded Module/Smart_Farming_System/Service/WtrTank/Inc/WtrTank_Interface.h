/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  WtrTank_Interface.c
 *		  Layer:  Service
 *       Module:  WtrTank
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the functions' prototypes of the water tank and including its types
 *  
 *********************************************************************************************************************/

#ifndef WTRTANK_INTERFACE_H
#define WTRTANK_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "WtrTank_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t WtrTank_Init(WtrTank_Config_t *Copy_WaterTankConfig)
* \Description     : Initialize the water tank module to use external interrupt if configured
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_WaterTankConfig    Pointer to structure of WtrTank configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t WtrTank_Init(WtrTank_Config_t *Copy_WaterTankConfig);

/******************************************************************************
* \Syntax          : ErrorState_t WtrTank_GetState(WtrTank_Config_t *Copy_WaterTankConfig, WtrTank_State_t *Copy_WaterTankState)
* \Description     : Get the water tank current state(full or empty)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_WaterTankConfig    Pointer to structure of water tank configuration
* \Parameters (out): Copy_WaterTankState     Pointer to return the tank current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t WtrTank_GetState(WtrTank_Config_t *Copy_WaterTankConfig, WtrTank_State_t *Copy_WaterTankState);

#endif /* WTRTANK_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: WtrTank_Interface.h
 *********************************************************************************************************************/
