/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Gpio_Program.c
 *		  Layer:  Mcal
 *       Module:  Gpio
 *		Version:  2.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F446xx.h"
#include "BIT_MATH.h"

#include "Gpio_Interface.h"
#include "Gpio_Private.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
/*Array of Pointers With The GPIO Ports*/
static Gpio_RegDef_t *Gpio_PortArr[PORT_NUM]={GPIOA , GPIOB , GPIOC , GPIOD , GPIOE, GPIOF , GPIOG , GPIOH};
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Gpio_PinInit(const Gpio_PinConfig_t *Copy_PinConfig)       
* \Description     : The Function Initializes the Required Pin Configuration options                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : 1- PinConfig: const pointer to GPIO_PinConfig_t structure which holds the configurations                     
* \Parameters (out): None                                                   
* \Return value:   : ErrorState_t                                
*******************************************************************************/
ErrorState_t Gpio_PinInit(const Gpio_PinConfig_t *Copy_PinConfig)
{
	ErrorState_t Local_ErrorState=E_OK;
	/*Check For the Pointer*/
	if(Copy_PinConfig != NULL)
	{
		if(Copy_PinConfig->Port < PORT_NUM && Copy_PinConfig->PinNum <= GPIO_PIN15)
		{
			/*1- Set Pin Mode Configuration*/
			Gpio_PortArr[Copy_PinConfig->Port]->MODER &= ~(MODE_BIT_MASK << (2*Copy_PinConfig->PinNum));
			Gpio_PortArr[Copy_PinConfig->Port]->MODER |= Copy_PinConfig->Mode <<(2*Copy_PinConfig->PinNum);
			/*2- Set Pin Pull Up / Down Configuration*/
			Gpio_PortArr[Copy_PinConfig->Port]->PUPDR &= ~(PUD_BIT_MASK<<(2*Copy_PinConfig->PinNum));
			Gpio_PortArr[Copy_PinConfig->Port]->PUPDR |= Copy_PinConfig->PullUpDown <<(2*Copy_PinConfig->PinNum);
			if(Copy_PinConfig->Mode == GPIO_PIN_OUTPUT)
			{
				/*3- Set The Output Type ConfigurationIf the Pin Mode OutPut*/
				switch(Copy_PinConfig->OutputType)
				{
				case GPIO_OUTPUT_PUSH_PULL: Clr_Bit(Gpio_PortArr[Copy_PinConfig->Port]->OTYPER,Copy_PinConfig->PinNum); break;
				case GPIO_OUTPUT_OPEN_DRAIN: Set_Bit(Gpio_PortArr[Copy_PinConfig->Port]->OTYPER,Copy_PinConfig->PinNum); break;
				default: Local_ErrorState=E_WRONG_OPTION;
				}
				/*- Set The Output Speed Configuration If the Pin Mode OutPut*/
				Gpio_PortArr[Copy_PinConfig->Port]->OSPEEDER &= ~(SPEED_BIT_MASK<<(2*Copy_PinConfig->PinNum));
				Gpio_PortArr[Copy_PinConfig->Port]->OSPEEDER |= Copy_PinConfig->OutputSpeed <<(2*Copy_PinConfig->PinNum);
			}
			if(Copy_PinConfig->Mode == GPIO_PIN_ALTFunc)
			{
				/*4- Set The Alternative Function Option If the Pin Mode Alternative Function*/
				if(Copy_PinConfig->PinNum<8 && Copy_PinConfig->PinNum>=0)
				{
					Gpio_PortArr[Copy_PinConfig->Port]->AFR[0] &= ~(ALT_FUNC_BIT_MASK << (4*Copy_PinConfig->PinNum));
					Gpio_PortArr[Copy_PinConfig->Port]->AFR[0] |= Copy_PinConfig->AlternateFuncOption<<(4*Copy_PinConfig->PinNum);
				}
				else if(Copy_PinConfig->PinNum<16 && Copy_PinConfig->PinNum>7)
				{
					Gpio_PortArr[Copy_PinConfig->Port]->AFR[1] &= ~(ALT_FUNC_BIT_MASK << (4*Copy_PinConfig->PinNum));
					Gpio_PortArr[Copy_PinConfig->Port]->AFR[1] |= (Copy_PinConfig->AlternateFuncOption-8)<<(4*Copy_PinConfig->PinNum);
				}
				else
				{
					Local_ErrorState=E_WRONG_OPTION;
				}
			}
		}
		else
		{
			Local_ErrorState=E_WRONG_OPTION;
		}
	}
	else
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Gpio_SetPinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_Pin,Gpio_PinState_t Copy_PinValue)
* \Description     : the function sets an output values on the output pin                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : 1- Copy_Port    : the port of the required output pin, refer to port possible options
*                    2- Copy_pin     : the pin number of the required output pin, refer to pin number possible options
*                    3- Copy_PinValue: the required pin state, refer to pin value possible options
* \Parameters (out): None                                                   
* \Return value:   : ErrorState_t                                
*******************************************************************************/
ErrorState_t Gpio_SetPinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_Pin,Gpio_PinState_t Copy_PinValue)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_Port < PORT_NUM && Copy_Pin <= GPIO_PIN15)
	{
		switch(Copy_PinValue)
		{
			case GPIO_PIN_LOW: Gpio_PortArr[Copy_Port]->BSRR=1<<(Copy_Pin+16); break;
			case GPIO_PIN_HIGH: Gpio_PortArr[Copy_Port]->BSRR=1<<Copy_Pin; break;
			default: Local_ErrorState=E_WRONG_OPTION;
		}
	}
	else
	{
		Local_ErrorState=E_WRONG_OPTION;
	}
	return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Gpio_SetPortValue(Gpio_Port_t Copy_Port,u16 Copy_PortValue)
* \Description     : the function sets an output values on the output port                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : 1- Copy_Port     : the the required output port, refer to port possible options
*                    2- Copy_PortValue: the required pin state, refer to Port value possible options 
* \Parameters (out): None                                                   
* \Return value:   : ErrorState_t                                
*******************************************************************************/
ErrorState_t Gpio_SetPortValue(Gpio_Port_t Copy_Port,u16 Copy_PortValue)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_Port < PORT_NUM)
	{
		Gpio_PortArr[Copy_Port]->ODR=Copy_PortValue;
	}
	else
	{
		Local_ErrorState=E_WRONG_OPTION;
	}
	return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Gpio_GetPinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_Pin,Gpio_PinState_t* Copy_PinValue)
* \Description     : The function Reads an Input value Of the required Pin                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : 1- Copy_Port : the port of the required Input pin, refer to port possible options
*                    2- Copy_pin  : the pin number of the required Input pin, refer to pin number possible option
* \Parameters (out): 1- Copy_PinValue: pointer to get the required pin state                                                   
* \Return value:   : ErrorState_t                                
*******************************************************************************/
ErrorState_t Gpio_GetPinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_Pin,Gpio_PinState_t* Copy_PinValue)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_PinValue != NULL)
	{
		if(Copy_Port < PORT_NUM && Copy_Pin <= GPIO_PIN15)
		{
			*Copy_PinValue = (Gpio_PinState_t)((Gpio_PortArr[Copy_Port]->IDR>>Copy_Pin)&1);
		}
		else
		{
			Local_ErrorState=E_WRONG_OPTION;
		}
	}
	else
	{
		Local_ErrorState=NULL_POINTER;
	}
	return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Gpio_GetPortValue(Gpio_Port_t Copy_Port,u16* Copy_PortValue)
* \Description     : The function Reads an Input value Of the required Port                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : 1- Copy_Port : the port of the required Input pin, refer to port possible options
* \Parameters (out): 1- Copy_PortValue: pointer to get the required Port value                                                   
* \Return value:   : ErrorState_t                                
*******************************************************************************/
ErrorState_t Gpio_GetPortValue(Gpio_Port_t Copy_Port,u16* Copy_PortValue)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_PortValue != NULL)
	{
		if(Copy_Port < PORT_NUM)
		{
			*Copy_PortValue = Gpio_PortArr[Copy_Port]->IDR;
		}
		else
		{
			Local_ErrorState=E_WRONG_OPTION;
		}
	}
	else
	{
		Local_ErrorState=NULL_POINTER;
	}
	return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : Gpio_TogglePinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_Pin)
* \Description     : the function Toggles the value of output pin                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : 1- Copy_Port: the the required output port, refer to port possible options
*                    2- Copy_Pin: the required pin state, refer to Port value possible options
* \Parameters (out): None                                                   
* \Return value:   : ErrorState_t                                
*******************************************************************************/
ErrorState_t Gpio_TogglePinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_Pin)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_Port < PORT_NUM && Copy_Pin <= GPIO_PIN15)
	{
		Gpio_PortArr[Copy_Port]->ODR ^= (1<<Copy_Pin);
	}
	else
	{
		Local_ErrorState=E_WRONG_OPTION;
	}
	return Local_ErrorState;
}

/**********************************************************************************************************************
 *  END OF FILE: Gpio_Program.c
 *********************************************************************************************************************/
