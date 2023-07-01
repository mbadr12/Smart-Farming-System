/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Ldr_Interface.h
 *		  Layer:  Hal
 *       Module:  Ldr
 *		Version:  1.0
 *	
 *  Description:  A header file that contains function prototypes of the ldr module and includes its types.
 *  
 *********************************************************************************************************************/
#ifndef LDR_INTERFACE_H 
#define LDR_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Ldr_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Ldr_Init(Ldr_Config_t *Copy_LdrConfig)
* \Description     : Initialize the LDR module
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_LdrConfig    Pointer to structure of Ldr configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Ldr_Init(Ldr_Config_t *Copy_LdrConfig);

/******************************************************************************
* \Syntax          : ErrorState_t Ldr_GetLuminancePercentage(Ldr_Config_t *Copy_LdrConfig, u8 *Copy_LuminancePercentage)
* \Description     : Get the luminance(ambiance light) current percentage
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_LdrConfig    Pointer to structure of Ldr configuration
* \Parameters (out): Copy_LuminancePercentage     Pointer to return the luminance(ambiance light) current percentage
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Ldr_GetLuminancePercentage(Ldr_Config_t *Copy_LdrConfig, u8 *Copy_LuminancePercentage);

/******************************************************************************
* \Syntax          : ErrorState_t Ldr_GetIlluminationStateDig(Ldr_Config_t *Copy_LdrConfig, Ldr_IlluminationState_t *Copy_IlluminationState)
* \Description     : Get the illumination(ambiance light) current state using digital pins: - Dark - Bright
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_LdrConfig    Pointer to structure of Ldr configuration
* \Parameters (out): Copy_IlluminationState     Pointer to return the illumination(ambiance light) current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Ldr_GetIlluminationStateDig(Ldr_Config_t *Copy_LdrConfig, Ldr_IlluminationState_t *Copy_IlluminationState);

#endif  /* LDR_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Ldr_Interface.h
 *********************************************************************************************************************/
