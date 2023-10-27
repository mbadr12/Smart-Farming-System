/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Exti_Program.c
 *		  Layer:  Mcal
 *       Module:  Exti
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

#include "Exti_Interface.h"
#include "Exti_Private.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
 static void (*Exti_CallBackFuncArr[EXTI_NUM])(void)={NULL};
 
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

 /******************************************************************************
 * \Syntax          : static s8 Exti_GetPendingFlag(void)
 * \Description     : Get the raised bending flag
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : s8
 *******************************************************************************/
static s8 Exti_GetPendingFlag(void)
{
	u8 Local_ExtiIterator=0;
	u8 Local_PendingState=0;
	for(Local_ExtiIterator=EXTI_PIN5 ; Local_ExtiIterator <= EXTI_PIN15 ; Local_ExtiIterator++)
	{
		Local_PendingState=(((EXTI->PR)>>Local_ExtiIterator) & 1);
		if(Local_PendingState == 1)
		{
			return Local_ExtiIterator;
		}
	}
	return -1;
}
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
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
ErrorState_t Exti_PinInit(const Exti_PinConfig_t* Copy_PinConfig)
{
	 ErrorState_t Local_ErrorState=E_OK;
	 if(Copy_PinConfig == NULL)
	 {
		 Local_ErrorState=E_NULL_POINTER;
	 }
	 else
	 {
		 /*Choose The Port to Have the EXTI*/
		 u8 Local_IntCnfgReg = Copy_PinConfig->Pin / EXTI_REGISTER_SELECTOR;
		 u8 Local_IntCnfgBit = (Copy_PinConfig->Pin % EXTI_Bit_SELECTOR);
		 SYSCFG->EXTICR[Local_IntCnfgReg] &= ~(EXTI_PORT_MASK<<(Local_IntCnfgBit*4));
		 SYSCFG->EXTICR[Local_IntCnfgReg] |= ((Copy_PinConfig->Port)<<(Local_IntCnfgBit*4));
		 /*Choose Trigger Type*/
		 switch(Copy_PinConfig->Trigger)
		 {
		 case EXTI_RAISING_TRIGGER: EXTI->RTSR |= 1<< Copy_PinConfig->Pin;
								   EXTI->FTSR &= ~(1<< Copy_PinConfig->Pin); break;
		 case EXTI_FALLING_TRIGGER: EXTI->FTSR |= 1<< Copy_PinConfig->Pin;
								   EXTI->RTSR &= ~(1<< Copy_PinConfig->Pin); break;
		 case EXTI_RIS_FALL_TRIGGER: EXTI->RTSR |= 1<< Copy_PinConfig->Pin;
									EXTI->FTSR |= 1<< Copy_PinConfig->Pin; break;
		 default: Local_ErrorState = E_NOK;
		 }
		 /*Pass the CallBack Function to The Global Array*/
		 Exti_CallBackFuncArr[Copy_PinConfig->Pin] = Copy_PinConfig->CallBackFunc;
		 /*Enable EXTI Interrupt for the selected pin*/
		 Exti_IntEnable(Copy_PinConfig->Pin);
	 }
	 return Local_ErrorState;
}

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
void Exti_ClearPendingFlag(Exti_Pin_t Copy_Pin)
{
	/*Clear Pending Flag*/
	EXTI->PR = 1<<Copy_Pin;
}

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
void Exti_IntEnable(Exti_Pin_t Copy_Pin)
{
	EXTI->IMR |= 1<<Copy_Pin;
}

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
void Exti_IntDisable(Exti_Pin_t Copy_Pin)
{
	EXTI->IMR &= ~(1<<Copy_Pin);
}

/******************************************************************************
* \Syntax          : void EXTI0_IRQHandler(void)
* \Description     : The ISR of EXTI0
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
	/*Make Sure That CallBack Function No Null*/
	if(Exti_CallBackFuncArr[EXTI_PIN0] !=NULL)
	{
		/*Call The Call Back Function*/
		Exti_CallBackFuncArr[EXTI_PIN0]();
		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_PIN0);
	}
	else
	{
		/*Do Nothing*/
	}
}

/******************************************************************************
* \Syntax          : void EXTI1_IRQHandler(void)
* \Description     : The ISR of EXTI1
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
	/*Make Sure That CallBack Function No Null*/
	if(Exti_CallBackFuncArr[EXTI_PIN1] !=NULL)
	{
		/*Call The Call Back Function*/
		Exti_CallBackFuncArr[EXTI_PIN1]();
		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_PIN1);
	}
	else
	{
		/*Do Nothing*/
	}
}

/******************************************************************************
* \Syntax          : void EXTI2_IRQHandler(void)
* \Description     : The ISR of EXTI2
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
	/*Make Sure That CallBack Function No Null*/
	if(Exti_CallBackFuncArr[EXTI_PIN2] !=NULL)
	{
		/*Call The Call Back Function*/
		Exti_CallBackFuncArr[EXTI_PIN2]();
		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_PIN2);
	}
	else
	{
		/*Do Nothing*/
	}
}

/******************************************************************************
* \Syntax          : void EXTI2_IRQHandler(void)
* \Description     : The ISR of EXTI2
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void EXTI3_IRQHandler(void)
{
	/*Make Sure That CallBack Function No Null*/
	if(Exti_CallBackFuncArr[EXTI_PIN3] !=NULL)
	{
		/*Call The Call Back Function*/
		Exti_CallBackFuncArr[EXTI_PIN3]();
		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_PIN3);
	}
	else
	{
		/*Do Nothing*/
	}
}

/******************************************************************************
* \Syntax          : void EXTI4_IRQHandler(void)
* \Description     : The ISR of EXTI4
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
	/*Make Sure That CallBack Function No Null*/
	if(Exti_CallBackFuncArr[EXTI_PIN4] !=NULL)
	{
		/*Call The Call Back Function*/
		Exti_CallBackFuncArr[EXTI_PIN4]();
		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_PIN4);
	}
	else
	{
		/*Do Nothing*/
	}
}

/******************************************************************************
* \Syntax          : void EXTI9_5_IRQHandler(void)
* \Description     : The ISR of EXTI from 5 to 9
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
	/*Get to Know the pin caused the handler*/
	s8 Local_ExtiNum= Exti_GetPendingFlag();
	/*Make Sure That CallBack Function No Null*/
	if(Exti_CallBackFuncArr[Local_ExtiNum] !=NULL)
	{
		/*Call The Call Back Function*/
		Exti_CallBackFuncArr[Local_ExtiNum]();
		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(Local_ExtiNum);
	}
	else
	{
		/*Do Nothing*/
	}
}

/******************************************************************************
* \Syntax          : void EXTI15_10_IRQHandler(void)
* \Description     : The ISR of EXTI from 10 to 15
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	/*Get to Know the pin caused the handler*/
	s8 Local_ExtiNum= Exti_GetPendingFlag();
	/*Make Sure That CallBack Function No Null*/
	if(Exti_CallBackFuncArr[Local_ExtiNum] !=NULL)
	{
		/*Call The Call Back Function*/
		Exti_CallBackFuncArr[Local_ExtiNum]();
		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(Local_ExtiNum);
	}
	else
	{
		/*Do Nothing*/
	}
}
/**********************************************************************************************************************
 *  END OF FILE: Exti_Program.c
 *********************************************************************************************************************/
