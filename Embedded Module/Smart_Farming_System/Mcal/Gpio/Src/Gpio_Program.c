/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Gpio_Program.c
 *		  Layer:  Mcal
 *       Module:  Gpio
 *		Version:  2.00
 *	
 *  Description:  Gpio driver implementation.     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "Gpio_Interface.h"
#include "Gpio_Config.h"
#include "Gpio_Private.h"
#include "Rcc_Interface.h"

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

static Gpio_RegDef_t *Gpios[] = {
    GPIOA, GPIOB, GPIOC,
    GPIOD, GPIOE, GPIOF,
    GPIOG, GPIOH, GPIOI,
    GPIOJ, GPIOK
};

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
ErrorState_t Gpio_ControlClock(const Gpio_PortId_t Copy_Id, const bool Copy_EnorDi){

    if(!IS_PORT_ID(Copy_Id)){
        return E_WRONG_OPTION;
    }

    if(!IS_BOOL(Copy_EnorDi)){
        return E_WRONG_OPTION;
    }

    if(Copy_EnorDi == ENABLE){
        Rcc_EnablePericlock((Rcc_PeripheralId_t)Copy_Id, FALSE);
    } 
    else{
        Rcc_DisablePericlock((Rcc_PeripheralId_t)Copy_Id);
    }

    return E_OK;
}


ErrorState_t Gpio_Init(const Gpio_PinId_t Copy_Id, const Gpio_Config_t *pConfig){ 
    u32 Local_Temp = 0;

    if(pConfig == NULL){
         return E_NULL_POINTER;
    }

    if(!IS_PIN_ID(Copy_Id)){
        return E_WRONG_OPTION;
    }

    u32 Local_PinId, Local_PortId;
    Local_PortId = Copy_Id / NUMBER_OF_PINS_PER_PORT;
    Local_PinId = Copy_Id % NUMBER_OF_PINS_PER_PORT;

    /* 1- Pin Mode */
    if(!IS_PIN_MODE(pConfig->PinMode)){
        return E_WRONG_OPTION;
    }
    else{
        Local_Temp = Gpios[Local_PortId]->MODER;
        Local_Temp &= ~(0x3 << Local_PinId * 2);
        Local_Temp |= (pConfig->PinMode << Local_PinId * 2);
        Gpios[Local_PortId]->MODER = Local_Temp;
    }

    /* 2- Pin Output Type */
    if(!IS_PIN_OUTPUT_TYPE(pConfig->PinOutputType)){
        return E_WRONG_OPTION;
    }
    else{
        Local_Temp = Gpios[Local_PortId]->OTYPER;
        Local_Temp &= ~(0x1 << Local_PinId);
        Local_Temp |= (pConfig->PinOutputType << Local_PinId);
        Gpios[Local_PortId]->OTYPER = Local_Temp;
    }

    /* 3- Pin Output Speed */
    if(!IS_PIN_OUTPUT_SPEED(pConfig->PinOutputSpeed)){
        return E_WRONG_OPTION;
    }
    else{
        Local_Temp = Gpios[Local_PortId]->OSPEEDER;
        Local_Temp &= ~(0x3 << Local_PinId*2);
        Local_Temp |= (pConfig->PinOutputSpeed << Local_PinId*2);
        Gpios[Local_PortId]->OSPEEDER = Local_Temp;
    }

    /* 4- Pin Internal Attach */
    if(!IS_PIN_INTERNAL_ATTACH(pConfig->PinInternalAttach)){
        return E_WRONG_OPTION;
    }
    else{
        Local_Temp = Gpios[Local_PortId]->PUPDR;
        Local_Temp &= ~(0x3 << Local_PinId*2);
        Local_Temp |= (pConfig->PinInternalAttach << Local_PinId*2);
        Gpios[Local_PortId]->PUPDR = Local_Temp;
    }

    /* 5- Pin Alternate Function */
    if(!IS_PIN_AF(pConfig->PinAF)){
        return E_WRONG_OPTION;
    }
    else{
        Local_Temp = Gpios[Local_PortId]->AFR[Local_PinId/8];
        Local_Temp &= ~(0xf << Local_PinId*4);
        Local_Temp |= (pConfig->PinAF << Local_PinId*4);
        Gpios[Local_PortId]->AFR[Local_PinId/8] = Local_Temp;
    }
    return E_OK;
}


// TODO:: implement reset function
ErrorState_t Gpio_DeInit(const Gpio_PinId_t Copy_Id){
    
    return E_OK;
}

/******************************************************************************
 * \Syntax          : Gpio_LevelType Gpio_ReadPin(Gpio_PinType channelId); 
 * \Description     : read level from channel 
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : channelId   Identifies what channel to read 
 * \Parameters (out): None
 * \Return value:   : Error_State_t
 *******************************************************************************/

ErrorState_t Gpio_ReadPin(const Gpio_PinId_t Copy_Id, Gpio_PinLevel_t *pLevel){

    if(pLevel  == NULL ){
         return E_NULL_POINTER;
    }

    if(!IS_PIN_ID(Copy_Id)){
         return E_WRONG_OPTION;
    }

    u32 Local_PinId, Local_PortId;
    Local_PortId = Copy_Id / NUMBER_OF_PINS_PER_PORT;
    Local_PinId = Copy_Id % NUMBER_OF_PINS_PER_PORT;

    *pLevel = (Gpios[Local_PortId]->IDR >> Local_PinId) & 1;

    return E_OK;
}

/******************************************************************************
 * \Syntax          : void Gpio_WritePin(Gpio_PinType channelId, Gpio_LevelType level)
 * \Description     : Write level to channel 
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : channelId   Identifies what channel to write
 level       The value to be written on the channel
 * \Parameters (out): None
 * \Return value:   : ErrorState_t  
 *******************************************************************************/
ErrorState_t Gpio_WritePin(const Gpio_PinId_t Copy_Id, const Gpio_PinLevel_t Copy_Level){

    if(!IS_PIN_LEVEL(Copy_Level)){
        return E_WRONG_OPTION;
    }

    if(!IS_PIN_ID(Copy_Id)){
        return E_WRONG_OPTION;
    }

    u32 Local_PinId, Local_PortId;
    Local_PortId = Copy_Id / NUMBER_OF_PINS_PER_PORT;
    Local_PinId = Copy_Id % NUMBER_OF_PINS_PER_PORT;

    if(Copy_Level == GPIO_HIGH){
        Gpios[Local_PortId]->BSRR = (1 << Local_PinId);
    }
    else{
        Gpios[Local_PortId]->BSRR = (1 << (Local_PinId+16U));
    }

    return E_OK;
}

/******************************************************************************
 * \Syntax          : Gpio_PortLevelType Gpio_ReadPort(Gpio_PortType portId) 
 * \Description     : Read level from port 
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : portId         Identifies the port 
 * \Parameters (out): None
 * \Return value:   : Error_State_t
 *******************************************************************************/
ErrorState_t Gpio_ReadPort(const Gpio_PortId_t Copy_Id, Gpio_PortLevel_t *pLevel){

    if(pLevel == NULL){
        return E_NULL_POINTER;
    }
    if(!IS_PORT_ID(Copy_Id)){
        return E_WRONG_OPTION;
    }

    *pLevel = Gpios[Copy_Id]->IDR;

    return E_OK;
}

/******************************************************************************
 * \Syntax          : void Gpio_WritePort(Gpio_PortType portId, Gpio_PortLevelType level) 
 * \Description     : Write level to port 
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : portId  Identifies the port 
 level   The value to be written on the port
 * \Parameters (out): None
 * \Return value:   : Error_State_t
 *******************************************************************************/
ErrorState_t Gpio_WritePort(const Gpio_PortId_t Copy_Id, const Gpio_PortLevel_t Copy_Level){

    if(!IS_PORT_ID(Copy_Id)){
         return  E_WRONG_OPTION;
    }

    if(!IS_PORT_LEVEL(Copy_Level)){
         return E_WRONG_OPTION;
    }

    else{
        Gpios[Copy_Id]->ODR = Copy_Level;
    }

    return E_OK;
}

/**********************************************************************************************************************
 *  END OF FILE: Gpio_Program.c
 *********************************************************************************************************************/
