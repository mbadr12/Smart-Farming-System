/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Gpio_Interface.h
 *		  Layer:  Mcal
 *       Module:  Gpio
 *		Version:  1.00
 *	
 *  Description:  Gpio module API
 *  
 *********************************************************************************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Gpio_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/* Clock control*/
ErrorState_t Gpio_ControlClock(const Gpio_PortId_t Copy_Id, const bool Copy_EnorDi); 

/* Init and De-Init*/
ErrorState_t Gpio_Init(const Gpio_PinId_t Copy_Id, const Gpio_Config_t *pConfig); 
ErrorState_t Gpio_DeInit(const Gpio_PinId_t Copy_Id);

/* IO operations */
ErrorState_t Gpio_ReadPin(const Gpio_PinId_t Copy_Id, Gpio_PinLevel_t *pLevel);
ErrorState_t Gpio_WritePin(const Gpio_PinId_t Copy_Id, const Gpio_PinLevel_t Copy_Level);
ErrorState_t Gpio_TogglePin(const Gpio_PinId_t Copy_Id, Gpio_PinLevel_t *pLevel);

ErrorState_t Gpio_ReadPort(const Gpio_PortId_t Copy_Id, Gpio_PortLevel_t *pLevel);
ErrorState_t Gpio_WritePort(const Gpio_PortId_t Copy_Id, const Gpio_PortLevel_t Copy_Level);

 
#endif  /* GPIO_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpio_Interface.h
 *********************************************************************************************************************/
