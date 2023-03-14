/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Nvic_Interface.h
 *		  Layer:  Mcal
 *       Module:  Nvic
 *		Version:  1.00
 *	
 *  Description:  api for the Nvic module
 *  
 *********************************************************************************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Nvic_Types.h"
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define NVIC_ENABLE_ALL_INT() __asm volatile("CPSIE i")
#define NVIC_DISABLE_ALL_INT() __asm volatile("CPSID i")

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*Enta bthazar ya mezo .. ahm mn الشغل zabth*/
/*Give me documentation for every function*/
ErrorState_t Nvic_EnableIRQ(Nvic_IRQn_t Copy_IRQ);
ErrorState_t Nvic_DisableIRQ(Nvic_IRQn_t Copy_IRQ);

ErrorState_t Nvic_SetPendingIRQ(Nvic_IRQn_t Copy_IRQ);
ErrorState_t Nvic_ClearPendingIRQ(Nvic_IRQn_t Copy_IRQ);
ErrorState_t Nvic_GetPendingIRQ(Nvic_IRQn_t Copy_IRQ, bool *pState);

ErrorState_t Nvic_GetActive(Nvic_IRQn_t Copy_IRQ, bool *pState);

ErrorState_t Nvic_SetPriorityGrouping(Nvic_PrioGroup_t Copy_PrioGroup);
ErrorState_t Nvic_SetPriority(Nvic_IRQn_t Copy_IRQ, u8 Copy_Prio);
ErrorState_t Nvic_GetPriority(Nvic_IRQn_t Copy_IRQ, u8 *pPrio);

ErrorState_t Nvic_GenerateInterrupt(Nvic_IRQn_t Copy_IRQ); //by software
                                                           
#endif /* NVIC_INTERFACE_H_H */

/**********************************************************************************************************************
 *  END OF FILE: Nvic_Interface.h
 *********************************************************************************************************************/
