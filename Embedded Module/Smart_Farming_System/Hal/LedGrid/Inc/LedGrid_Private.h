/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  LedGrid_Private.h
 *		  Layer:  Hal
 *       Module:  LedGrid
 *		Version:  1.0
 *	
 *  Description:  A header file that contains local macros and functions used only in the program file of the LED grid module and not needed outside the scope of this module.
 *  
 *********************************************************************************************************************/

#ifndef LEDGRID_PRIVATE_H
#define LEDGRID_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsLedGridConfigValid(LedGrid_Config_t *Copy_LedGridConfig)
* \Description     : Check the LED grid configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LedGridConfig    Pointer to structure of LedGrid configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsLedGridConfigValid(LedGrid_Config_t *Copy_LedGridConfig);

#endif  /* LEDGRID_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: LedGrid_Private.h
 *********************************************************************************************************************/