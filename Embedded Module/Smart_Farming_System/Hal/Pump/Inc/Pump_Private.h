/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Pump_Private.h
 *		  Layer:  Hal
 *       Module:  Pump (Mini Water Pump)
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the macros and private functions used only in the program file and not needed outside this module
 *  
 *********************************************************************************************************************/

#ifndef PUMP_PRIVATE_H
#define PUMP_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsPumpConfigValid(Pump_Config_t *Copy_PumpConfig)
* \Description     : Check the pump configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_PumpConfig    Pointer to structure of pump configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsPumpConfigValid(Pump_Config_t *Copy_PumpConfig);

#endif  /* PUMP_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Pump_Private.h
 *********************************************************************************************************************/
