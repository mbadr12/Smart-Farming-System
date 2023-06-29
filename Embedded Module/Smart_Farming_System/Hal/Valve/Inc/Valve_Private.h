/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Valve_Private.h
 *		  Layer:  Hal
 *       Module:  Valve (Solenoid Valve (Mini))
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the macros and private functions used only in the program file and not needed outside this module
 *  
 *********************************************************************************************************************/

#ifndef VALVE_PRIVATE_H
#define VALVE_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsValveConfigValid(Valve_Config_t *Copy_ValveConfig)
* \Description     : Check the valve configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_ValveConfig    Pointer to structure of valve configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsValveConfigValid(Valve_Config_t *Copy_ValveConfig);

#endif  /* VALVE_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Valve_Private.h
 *********************************************************************************************************************/
