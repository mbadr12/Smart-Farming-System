/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Ldr_Private.h
 *		  Layer:  Hal
 *       Module:  Ldr
 *		Version:  1.0
 *	
 *  Description:  A header file that contains local macros and functions used only in the program file of the ldr module and not needed outside the scope of this module.
 *  
 *********************************************************************************************************************/

#ifndef LDR_PRIVATE_H
#define LDR_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsLdrConfigValid(Ldr_Config_t *Copy_LdrConfig)
* \Description     : Check the Ldr configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LdrConfig    Pointer to structure of Ldr configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsLdrConfigValid(Ldr_Config_t *Copy_LdrConfig);

#endif  /* LDR_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Ldr_Private.h
 *********************************************************************************************************************/
