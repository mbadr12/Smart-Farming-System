/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Gpio_Interface.h
 *		  Layer:  Mcal
 *       Module:  Gpio
 *		Version:  2.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Gpio_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
ErrorState_t Gpio_PinInit(const Gpio_PinConfig_t *Copy_PinConfig);

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
ErrorState_t Gpio_SetPinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_Pin,Gpio_PinState_t Copy_PinValue);

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
ErrorState_t Gpio_SetPortValue(Gpio_Port_t Copy_Port,u16 Copy_PortValue);

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
ErrorState_t Gpio_GetPinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_Pin,Gpio_PinState_t* Copy_PinValue);

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
ErrorState_t Gpio_GetPortValue(Gpio_Port_t Copy_Port,u16* Copy_PortValue);

/******************************************************************************
* \Syntax          : Gpio_TogglePinValue(Gpio_Port_t Copy_Port,Gpio_PIN_t Copy_u8Pin)
* \Description     : the function Toggles the value of output pin                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : 1- Copy_Port     : the the required output port, refer to port possible options
*                    2- Copy_PortValue: the required pin state, refer to Port value possible options 
* \Parameters (out): None                                                   
* \Return value:   : ErrorState_t                                
*******************************************************************************/
ErrorState_t Gpio_TogglePinValue(Gpio_Port_t Copy_u8Port,Gpio_PIN_t Copy_Pin);
 
#endif  /* GPIO_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpio_Interface.h
 *********************************************************************************************************************/
