/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Fc28_Interface.h
 *		  Layer:  Hal
 *       Module:  Fc28
 *		Version:  1.0
 *	
 *  Description:  A header file that contains function prototypes of the fc28(soil moisture) module and includes its types.
 *  
 *********************************************************************************************************************/
#ifndef FC28_INTERFACE_H 
#define FC28_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Fc28_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Fc28_Init(Fc28_Config_t *Copy_Fc28Config)
* \Description     : Initialize the FC-28 module
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_Fc28Config    Pointer to structure of fc28 configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Fc28_Init(Fc28_Config_t *Copy_Fc28Config);

/******************************************************************************
* \Syntax          : ErrorState_t Fc28_GetSoilMoisturePercentage(Fc28_Config_t *Copy_Fc28Config, u8 *Copy_MoisturePercentage)
* \Description     : Get the soil moisture current percentage
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_Fc28Config    Pointer to structure of fc28 configuration
* \Parameters (out): Copy_MoisturePercentage     Pointer to return the soil moisture percentage
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Fc28_GetSoilMoisturePercentage(Fc28_Config_t *Copy_Fc28Config, u8 *Copy_MoisturePercentage);

/******************************************************************************
* \Syntax          : ErrorState_t Fc28_GetSoilMoistureStateDig(Fc28_Config_t *Copy_Fc28Config, Fc28_MoistureState_t *Copy_MoistureState)
* \Description     : Get the soil moisture current state using digital pins: - Dry Soil - Humid Soil
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_Fc28Config    Pointer to structure of fc28 configuration
* \Parameters (out): Copy_MoistureState     Pointer to return the soil moisture current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Fc28_GetSoilMoistureStateDig(Fc28_Config_t *Copy_Fc28Config, Fc28_MoistureState_t *Copy_MoistureState);

#endif  /* FC28_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Fc28_Interface.h
 *********************************************************************************************************************/
