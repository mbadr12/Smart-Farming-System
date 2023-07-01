/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  WtrTank_Private.c
 *		  Layer:  Service
 *       Module:  WtrTank
 *		Version:  1.0
 *	
 *  Description:  A header file that contains private functions used only in the program file and not needed outside this module
 *  
 *********************************************************************************************************************/

#ifndef WTRTANK_PRIVATE_H
#define WTRTANK_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define USED 					1
#define NOT_USED             	2

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsWaterTankConfigValid(WtrTank_Config_t *Copy_WaterTankConfig)
* \Description     : Check the water tank configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_WaterTankConfig    Pointer to structure of water tank configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsWaterTankConfigValid(WtrTank_Config_t *Copy_WaterTankConfig);

#endif /* WTRTANK_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: WtrTank_Private.h
 *********************************************************************************************************************/
