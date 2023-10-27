/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud, Mazen and Musa
 *	   	   File:  Dcmi_Program.c
 *		  Layer:  Mcal
 *       Module:  Dcmi
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "Dcmi_Interface.h"
#include "Dcmi_Config.h"
#include "Dcmi_Private.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static void (*Dcmi_CallBackFunc[5])(void)={NULL};

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
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
void Dcmi_Init(void)
{
	/*Reinitialize*/
	DCMI->CR=0;
	/*set the data bits number*/
	DCMI->CR|=DATA_BITS;
	/*set the polarities*/
	DCMI->CR|=(VSYNCH_POLARITY<<VSPOL)|(HSYNCH_POLARITY<<HSPOL)|(PXLCLK_POLARITY<<PCKPOL);
	/*Set Synchronization source*/
	DCMI->CR|=SYNCH_SOURCE;
	/*Set Capture mode*/
	DCMI->CR|=CAPTURE_MODE;
	/*DCMI enable*/
	DCMI->CR|=ENABLE;
}

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
void Dcmi_CaptureImage(void)
{
	DCMI->CR|=CAPTURE;
}

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
ErrorState_t Dcmi_ControlInt(Dcmi_InterruptId_t Copy_IntId, Dcmi_InterruptState_t Copy_IntState, void(*Copy_CallBackFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_Counter=0;
	if((Copy_CallBackFunc == NULL) && (Copy_IntState == DCMI_INT_ENABLE))
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if((Copy_IntId >= DCMI_END_OF_FRAME) && (Copy_IntId <= DCMI_END_OF_LINE))
		{
			switch(Copy_IntState)
			{
			case DCMI_INT_ENABLE: DCMI->IER |= Copy_IntId;
			while((Copy_IntId>>1)!=0)
			{
				Copy_IntId >>=1;
				Local_Counter++;
			}
			Dcmi_CallBackFunc[Local_Counter]=Copy_CallBackFunc;
			case DCMI_INT_DISABLE: DCMI->IER &= ~(Copy_IntId); break;
			default: Local_ErrorState = E_WRONG_OPTION;
			}
		}
		else
		{
			Local_ErrorState=E_WRONG_OPTION;
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : void DCMI_IRQHandler(void)
 * \Description     : The interrupt request handler
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DCMI_IRQHandler(void)
{
	u8 Local_Counter=0;
	for(Local_Counter=0;Local_Counter<5;Local_Counter++)
	{
		if(GET_BIT((DCMI->MIS),Local_Counter)==1)
		{
			/*invoice the callback function*/
			Dcmi_CallBackFunc[Local_Counter]();
			/*clear the interrupt flag*/
			DCMI->ICR = (1<<Local_Counter);
		}
	}
}

/**********************************************************************************************************************
 *  END OF FILE: Dcmi_Program.c
 *********************************************************************************************************************/
