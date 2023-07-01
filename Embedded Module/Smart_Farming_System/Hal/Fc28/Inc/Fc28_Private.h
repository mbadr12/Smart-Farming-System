/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Fc28_Private.h
 *		  Layer:  Hal
 *       Module:  Fc28
 *		Version:  1.0
 *	
 *  Description:  A header file that contains local macros and functions used only in the program file of the fc28(soil moisture) module and not needed outside the scope of this module.
 *  
 *********************************************************************************************************************/

#ifndef FC28_PRIVATE_H
#define FC28_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsFc28ConfigValid(Fc28_Config_t *Copy_Fc28Config)
* \Description     : Check the fc28 configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_Fc28Config    Pointer to structure of fc28 configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsFc28ConfigValid(Fc28_Config_t *Copy_Fc28Config);

#endif  /* FC28_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Fc28_Private.h
 *********************************************************************************************************************/
