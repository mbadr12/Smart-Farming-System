/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud, Mazen and Musa
 *	   	   File:  Dcmi_Interface.h
 *		  Layer:  Mcal
 *       Module:  Dcmi
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef DCMI_INTERFACE_H
#define DCMI_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Dcmi_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : void Dcmi_CaptureImage(void)
 * \Description     : initialize the DCMI peripheral
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Dcmi_Init(void);

/******************************************************************************
 * \Syntax          : void Dcmi_CaptureImage(void)
 * \Description     : start the capture of frame
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Dcmi_CaptureImage(void);

/******************************************************************************
 * \Syntax          : ErrorState_t Dcmi_ControlInt(Dcmi_InterruptId_t Copy_IntId, Dcmi_InterruptState_t Copy_IntState, void(*Copy_CallBackFunc)(void))
 * \Description     : control the state of the interrupts
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_IntId: The interrupt id
 * 					  Copy_IntState: The Interrupt state
 * 					  (*Copy_CallBackFunc)(void): the callback function
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Dcmi_ControlInt(Dcmi_InterruptId_t Copy_IntId, Dcmi_InterruptState_t Copy_IntState, void(*Copy_CallBackFunc)(void));
 
#endif  /* DCMI_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Dcmi_Interface.h
 *********************************************************************************************************************/
