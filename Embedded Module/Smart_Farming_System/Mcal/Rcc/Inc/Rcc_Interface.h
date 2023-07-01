/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Rcc_Interface.h
 *  	  Layer:  Mcal
 *       Module:  Rcc
 *		Version:  1.00
 *	
 *  Description:  Rcc module driver APIs   
 *  
 *********************************************************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H 

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Rcc_Types.h"
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErroState_t RCC_EnablePericlock(Rcc_PeripheralId_t Copy_PeripheralId, bool Copy_LowPowerMode)        
* \Description     : Enable The clock to a peripheral and choose if in low power mode for the peripheral to
*						continue working while in sleep mode.                                                                                                               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_PeripheralId, Copy_LowePowerMode
* \Parameters (out): None
* \Return value:   : ErroState_t
*******************************************************************************/
ErrorState_t Rcc_EnablePericlock(Rcc_PeripheralId_t Copy_PeripheralId, bool Copy_PeripheralClkMode);

/******************************************************************************
* \Syntax          : ErroState_t RCC_DisablePericlock(Rcc_PeripheralId_t Copy_PeripheralId)        
* \Description     : Disable any clock connected to a peripheral.
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_PeripheralId
* \Parameters (out): None
* \Return value:   : ErroState_t
*******************************************************************************/
ErrorState_t Rcc_DisablePericlock(Rcc_PeripheralId_t Copy_PeripheralId);

/******************************************************************************
* \Syntax          : ErroState_t RCC_SetClkState(Rcc_ClkType_t Copy_ClkType, bool Copy_ClkState, Rcc_PllConfig_t *Copy_PllConfigPtr)        
* \Description     : Turn on/off different clok sources. In stm32f429 I have 5 different clock sources:
*                            1. HSI 2. HSE 3. PLL 4. PLLI2s 5. PLLSAI                                                   
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_PeripheralId
* \Parameters (out): None
* \Return value:   : ErroState_t
*******************************************************************************/
ErrorState_t Rcc_SetClkState(Rcc_ClkType_t Copy_ClkType, bool Copy_ClkState, Rcc_PllConfig_t *Copy_PllConfigPtr);

/******************************************************************************
* \Syntax          : ErroState_t RCC_SetSysClkSrc (Rcc_ClkType_t Copy_ClkType)        
* \Description     : Choose the source for the SYSCLK: 1. HSI 2. HSE 3. PLL
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_ClkType
* \Parameters (out): None
* \Return value:   : ErroState_t
*******************************************************************************/
ErrorState_t Rcc_SetSysClkSrc (Rcc_ClkType_t Copy_ClkType);

/*Configure Buses Prescaler (AHB,APB1,APB2)*/
void Rcc_BusesPrescaler (void);

void Rcc_Mco1Enable(Rcc_Mco1Src_t Copy_Src, Rcc_McoPrescaler_t Copy_Prescaler);

void Rcc_Mco2Enable(Rcc_Mco2Src_t Copy_Src, Rcc_McoPrescaler_t Copy_Prescaler);

#endif  /* RCC_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Rcc_Interface.h
 *********************************************************************************************************************/
