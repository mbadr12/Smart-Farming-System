/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Switch_Private.c
 *		  Layer:  Hal
 *       Module:  Switch
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the macros and private functions used only in the program file and not needed outside this module
 *  
 *********************************************************************************************************************/

#ifndef SWITCH_PRIVATE_H
#define SWITCH_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define ENABLED                 1
#define NOT_ENABLED             0

#define USED 					1
#define NOT_USED             	0

#define WAIT_AND_DOUBLE_CHECK   0

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsSwitchConfigValid(Switch_Config_t *SwitchConfig)
* \Description     : Check the switch configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_SwitchConfig    Pointer to structure of switch configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
// static bool IsSwitchConfigValid(Switch_Config_t *Copy_SwitchConfig);

#endif /* SWITCH_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Switch_Private.h
 *********************************************************************************************************************/
