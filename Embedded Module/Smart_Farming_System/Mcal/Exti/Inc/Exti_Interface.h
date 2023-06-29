/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Exti_Interface.h
 *		  Layer:  Mcal
 *       Module:  Exti
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef Exti_INTERFACE_H
#define Exti_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Exti_Types.h"

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Exti_PinInit(const Exti_PinConfig_t* Copy_PinConfig)
* \Description     : Initialize the pin as EXTI pin
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Exti_PinConfig_t   The pin configuration needed
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Exti_PinInit(const Exti_PinConfig_t* Copy_PinConfig);

/******************************************************************************
* \Syntax          : void Exti_ClearPendingFlag(Exti_Pin_t Copy_Pin)
* \Description     : Clear the Pending flag
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_Pin   The pin required to clear its pending flag
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void Exti_ClearPendingFlag(Exti_Pin_t Copy_Pin);

/******************************************************************************
* \Syntax          : void Exti_IntEnable(Exti_Pin_t Copy_Pin)
* \Description     : Enable the interrupt
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_Pin   The pin required to Enable its Interrupt
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void Exti_IntEnable(Exti_Pin_t Copy_Pin);

/******************************************************************************
* \Syntax          : void Exti_IntDisable(Exti_Pin_t Copy_Pin)
* \Description     : Disable the interrupt
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_Pin   The pin required to Disable its Interrupt
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void Exti_IntDisable(Exti_Pin_t Copy_Pin);

#endif  /* Exti_INTERFACE_H */
/**********************************************************************************************************************
 *  END OF FILE: Exti_Interface.h
 *********************************************************************************************************************/
