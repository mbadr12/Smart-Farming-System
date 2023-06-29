/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Aht21b_Interface.h
 *		  Layer:  Hal
 *       Module:  Aht21b
 *		Version:  1.0
 *	
 *  Description:  A header file that contains function prototypes of the aht21b module and includes its types.
 *  
 *********************************************************************************************************************/
#ifndef AHT21B_INTERFACE_H 
#define AHT21B_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Aht21b_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Aht21b_Init(void)
* \Description     : Initialize the AHT21B Module
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Aht21b_Init(void);

/******************************************************************************
* \Syntax          : ErrorState_t Aht21b_ReadTemperatureInCelsius(s8 *Copy_Temperature)
* \Description     : Get the enviornment temperature in degree celsius(from -40 to 80 'C)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant                     
* \Parameters (in) : None
* \Parameters (out): Copy_Temperature   Pointer to return the enviornment temperature in celsius
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Aht21b_ReadTemperatureInCelsius(s8 *Copy_Temperature);

/******************************************************************************
* \Syntax          : ErrorState_t Aht21b_ReadRelativeHumidity(u8 *Copy_Humidity)
* \Description     : Get the enviornment relative humidity(from 0 to 100 %RH)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): Copy_Humidity   Pointer to return the enviornment relative humidity
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Aht21b_ReadRelativeHumidity(u8 *Copy_Humidity);

#endif  /* AHT21B_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Aht21b_Interface.h
 *********************************************************************************************************************/
