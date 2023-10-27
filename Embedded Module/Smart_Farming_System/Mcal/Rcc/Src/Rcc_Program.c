/*********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Rcc_Program.c
 *		  Layer:  Mcal
 *       Module:  Rcc
 *		Version:  1.00
 *	
 *  Description:  Rcc module driver implementation.     
 *  
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "Rcc_Interface.h"
#include "Rcc_Config.h"
#include "Rcc_Private.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/*Mashy ya sedy shokran kfaya .. Ehna hanhazar?*/
/* TODO:: Handle non default initilization */
static void Rcc_InitPLL(Rcc_PllConfig_t *Copy_PllConfigPtr){
    /* If user passes NULL leave the PLL at default rest value initialization (PLL General Clock Output = 96Mhz)*/
    if(Copy_PllConfigPtr == NULL) return;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t RCC_EnablePericlock(Rcc_PeripheralId_t Copy_PeripheralId, bool Copy_LowPowerMode)        
* \Description     : Enable The clock to a peripheral and choose if in low power mode for the peripheral to
*						continue working while in sleep mode.                                                                                                               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_PeripheralId, Copy_LowePowerMode
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Rcc_EnablePericlock(Rcc_PeripheralId_t Copy_PeripheralId, bool Copy_LowPowerMode){
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_RegisterIndex = Copy_PeripheralId/32;
    u8 Local_BitIndex = Copy_PeripheralId % 32;
    if(Local_RegisterIndex > 4){
        Local_ErrorState = E_NOK;
        return Local_ErrorState;
    }
    if(Copy_LowPowerMode == 0){
        switch(Local_RegisterIndex){
            case 0:
                if(Local_BitIndex == RCC_AHB1_FLITF_LP || Local_BitIndex == RCC_AHB1_SRAM1_LP || Local_BitIndex == RCC_AHB1_SRAM2_LP){
                    Local_ErrorState = E_WRONG_OPTION;
                }
                SET_BIT( RCC->AHB1ENR , Local_BitIndex);
                break;
            case 1:
                SET_BIT( RCC->AHB2ENR , Local_BitIndex);
                break;
            case 2:
                SET_BIT( RCC->AHB3ENR , Local_BitIndex);
                break;
            case 3:
                SET_BIT( RCC->APB1ENR , Local_BitIndex);
                break;
            case 4:
                SET_BIT( RCC->APB2ENR , Local_BitIndex);
                break;
        }
    }
    else{
        switch(Local_RegisterIndex){
            case 0:
                if(Local_BitIndex == RCC_AHB1_CCMDATARAM){
                    Local_ErrorState = E_WRONG_OPTION;
                    break;
                }
                SET_BIT( RCC->AHB1LPENR , Local_BitIndex);
                break;
            case 1:
                SET_BIT( RCC->AHB2LPENR , Local_BitIndex);
                break;
            case 2:
                SET_BIT( RCC->AHB3LPENR , Local_BitIndex);
                break;
            case 3:
                SET_BIT( RCC->APB1LPENR , Local_BitIndex);
                break;
            case 4:
                SET_BIT( RCC->APB2LPENR , Local_BitIndex);
                break;
        }
    }
    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t RCC_DisablePericlock(Rcc_PeripheralId_t Copy_PeripheralId)        
* \Description     : Disable any clock connected to a peripheral.
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_PeripheralId
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Rcc_DisablePericlock(Rcc_PeripheralId_t Copy_PeripheralId){
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_RegisterIndex = Copy_PeripheralId/32;
    u8 Local_BitIndex = Copy_PeripheralId % 32;
    if(Local_RegisterIndex > 4){
        Local_ErrorState = E_NOK;
        return Local_ErrorState;
    }
    switch(Local_RegisterIndex){
        case 0:
            if(Local_BitIndex == RCC_AHB1_FLITF_LP || Local_BitIndex == RCC_AHB1_SRAM1_LP || Local_BitIndex == RCC_AHB1_SRAM2_LP){
                CLR_BIT( RCC->AHB1LPENR , Local_BitIndex);
                break;
            }
            else if(Local_BitIndex == RCC_AHB1_CCMDATARAM){
                CLR_BIT( RCC->AHB1ENR , Local_BitIndex);
                break;
            }
            CLR_BIT( RCC->AHB1LPENR , Local_BitIndex);
            CLR_BIT( RCC->AHB1ENR , Local_BitIndex);
            break;
        case 1:
            CLR_BIT( RCC->AHB2ENR , Local_BitIndex);
            CLR_BIT( RCC->AHB2LPENR , Local_BitIndex);
            break;
        case 2:
            CLR_BIT( RCC->AHB3ENR , Local_BitIndex);
            CLR_BIT( RCC->AHB3LPENR , Local_BitIndex);
            break;
        case 3:
            CLR_BIT( RCC->APB1ENR , Local_BitIndex);
            CLR_BIT( RCC->APB1LPENR , Local_BitIndex);
            break;
        case 4:
            CLR_BIT( RCC->APB2ENR , Local_BitIndex);
            CLR_BIT( RCC->APB2LPENR , Local_BitIndex);
            break;
    }
    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t RCC_SetClkState(Rcc_ClkType_t Copy_ClkType, bool Copy_ClkState, Rcc_PllConfig_t *Copy_PllConfigPtr)        
* \Description     : Turn on/off different clok sources. In stm32f429 I have 5 different clock sources:
*                            1. HSI 2. HSE 3. PLL 4. PLLI2s 5. PLLSAI                                                   
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_PeripheralId
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Rcc_SetClkState(Rcc_ClkType_t Copy_ClkType, bool Copy_ClkState, Rcc_PllConfig_t *Copy_PllConfigPtr){
    ErrorState_t Local_ErrorState = E_OK;
    if(Copy_ClkState > 1){
        Local_ErrorState = E_WRONG_OPTION;
        return Local_ErrorState;
    }
    switch(Copy_ClkType){
        case RCC_HSE_CRYSTAL:{
            if(Copy_ClkState == ON)
            {
                /*Enable Clock Security System*/
                SET_BIT(RCC->CR, RCC_CR_CSSON);
                /*Disable Bypassing HSE oscillator */
                CLR_BIT(RCC->CR, RCC_CR_HSEBYP);
                /*Enable HSE*/
                SET_BIT(RCC->CR, RCC_CR_HSEON);
                /*wait until HSE is ready*/
                while(GET_BIT(RCC->CR,RCC_CR_HSERDY) == 0);
            }
            else
            {
                /*Disable HSE*/
                CLR_BIT(RCC->CR, RCC_CR_HSEON);
            }
            break;
        }

        case RCC_HSE_RC:{
            if(Copy_ClkState == ON)
            {
                /*Enable Clock Security System*/
                SET_BIT(RCC->CR, RCC_CR_CSSON);
                /*Enable Bypassing HSE oscillator */
                SET_BIT(RCC->CR, RCC_CR_HSEBYP); // This has to be done first before enabling HSE.
                /*Enable HSE*/
                SET_BIT(RCC->CR, RCC_CR_HSEON);
                /*wait until HSE is ready*/
                while(GET_BIT(RCC->CR,RCC_CR_HSERDY) == 0);
            }
            else
            {
                /*Disable HSE*/
                CLR_BIT(RCC->CR, RCC_CR_HSEON);
            }
            break;
        }
        case RCC_PLL:{
            if(Copy_ClkState == ON)
            {
                /* Configure PLL */
                Rcc_InitPLL(Copy_PllConfigPtr);
                /* Enable PLL */
                SET_BIT(RCC->CR, RCC_CR_PLLON);
                /*wait until PLL is ready*/
                while(GET_BIT(RCC->CR, RCC_CR_PLLRDY) == 0);
            }
            else
            {
                /* Disable PLL */
                CLR_BIT(RCC->CR, RCC_CR_PLLON);
            }
            break;
        }
        case RCC_PLLI2S:{
            if(Copy_ClkState == ON)
            {
                /* Configure PLLI2S */
                Rcc_InitPLL(Copy_PllConfigPtr);
                /* Enable PLLI2S */
                SET_BIT(RCC->CR, RCC_CR_PLLI2SON);
                /*wait until PLLI2S is ready*/
                while(GET_BIT(RCC->CR, RCC_CR_PLLI2SRDY) == 0);
            }
            else
            {
                /* Disable PLL */
                CLR_BIT(RCC->CR, RCC_CR_PLLI2SON);
            }
            break;

            break;
        }
        case RCC_PLLSAI:{
            if(Copy_ClkState == ON)
            {
                /* Configure PLLSAI */
                Rcc_InitPLL(Copy_PllConfigPtr);
                /* Enable PLLSAI */
                SET_BIT(RCC->CR, RCC_CR_PLLSAION);
                /*wait until PLLSAI is ready*/
                while(GET_BIT(RCC->CR, RCC_CR_PLLSAIRDY) == 0);
            }
            else
            {
                /* Disable PLL */
                CLR_BIT(RCC->CR, RCC_CR_PLLSAION);
            }
            break;
        }
        default: {
            Local_ErrorState = E_WRONG_OPTION;
            break;
        }
    }
    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t RCC_SetSysClkSrc (Rcc_ClkType_t Copy_ClkType)        
* \Description     : Choose the source for the SYSCLK: 1. HSI 2. HSE 3. PLL
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_ClkType
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Rcc_SetSysClkSrc (Rcc_ClkType_t Copy_ClkType)
{
	ErrorState_t Local_ErrorSate = E_OK;

	switch (Copy_ClkType)
	{
        case RCC_HSI :
        {
            /*HSI oscillator selected as system clock*/
            CLR_BIT(RCC->CFGR, RCC_CFGR_SW0);
            CLR_BIT(RCC->CFGR, RCC_CFGR_SW1);
            break;
        }
        case RCC_PLL :
        {
            /*PLL selected as system clock*/
            CLR_BIT(RCC->CFGR, RCC_CFGR_SW0);
            SET_BIT(RCC->CFGR, RCC_CFGR_SW1);
            break;
        }
        case RCC_HSE_CRYSTAL :
        case RCC_HSE_RC      :
        {
            /*HSE oscillator selected as system clock*/
            CLR_BIT(RCC->CFGR, RCC_CFGR_SW1);
            SET_BIT(RCC->CFGR, RCC_CFGR_SW0);
            break;
        }
        default:{
            Local_ErrorSate = E_WRONG_OPTION; 
            break;
        } 
	}
	return Local_ErrorSate;
}


void Rcc_Mco1Enable(Rcc_Mco1Src_t Copy_Src, Rcc_McoPrescaler_t Copy_Prescaler)
{
    /* Set source */
    RCC->CFGR &= ~RCC_CFGR_MCO1_MSK;
    RCC->CFGR |= (Copy_Src << RCC_CFGR_MCO1_POS);
    /* Set Prescaler */
    RCC->CFGR &= ~RCC_CFGR_MCO1PRE_MSK;
    RCC->CFGR |= (Copy_Prescaler << RCC_CFGR_MCO1PRE_POS);
}

void Rcc_Mco2Enable(Rcc_Mco2Src_t Copy_Src, Rcc_McoPrescaler_t Copy_Prescaler)
{
    /* Set source */
    RCC->CFGR &= ~RCC_CFGR_MCO2_MSK;
    RCC->CFGR |= (Copy_Src << RCC_CFGR_MCO2_POS);
    /* Set Prescaler */
    RCC->CFGR &= ~RCC_CFGR_MCO2PRE_MSK;
    RCC->CFGR |= (Copy_Prescaler << RCC_CFGR_MCO2PRE_POS);
}

/**********************************************************************************************************************
 *  END OF FILE: Rcc_Program.c
 *********************************************************************************************************************/
