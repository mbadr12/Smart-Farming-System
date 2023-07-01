/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  WtrTank_Program.c
 *		  Layer:  Service
 *       Module:  WtrTank
 *		Version:  1.0
 *	
 *  Description:  A water tank driver to get tank current state(full or not empty)
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "Gpio_Interface.h"
#include "Exti_Interface.h"
#include "SysTick_Interface.h"

#include "Switch_Interface.h"

#include "WtrTank_Interface.h"
#include "WtrTank_Config.h"
#include "WtrTank_Private.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsWaterTankConfigValid(WtrTank_Config_t *Copy_WaterTankConfig)
* \Description     : Check the water tank configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_WaterTankConfig    Pointer to structure of water tank configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsWaterTankConfigValid(WtrTank_Config_t *Copy_WaterTankConfig)
{
    if ((Copy_WaterTankConfig->HlsInitState > WTRTANK_SWITCH_NORMALLY_OPENED)
        || (Copy_WaterTankConfig->HlsInitState < WTRTANK_SWITCH_NORMALLY_CLOSED)
        || (Copy_WaterTankConfig->LlsInitState > WTRTANK_SWITCH_NORMALLY_OPENED)
        || (Copy_WaterTankConfig->LlsInitState < WTRTANK_SWITCH_NORMALLY_CLOSED))
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t WtrTank_Init(WtrTank_Config_t *Copy_WaterTankConfig)
* \Description     : Initialize the water tank module to use external interrupt if configured
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_WaterTankConfig    Pointer to structure of WtrTank configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t WtrTank_Init(WtrTank_Config_t *Copy_WaterTankConfig)
{
    ErrorState_t Local_ErrorState = E_OK;
    Switch_Config_t Local_HlsConfig = {
        .PinId = Copy_WaterTankConfig->HlsPinId,
        .SwitchType = SWITCH_TEMPORARY,
        .PullType = Copy_WaterTankConfig->HlsPullingType,
        .InterruptEnable = Copy_WaterTankConfig->HlsInterruptEnable,
        .ExtiPinConfig = Copy_WaterTankConfig->HlsExtiPinConfig
    };
    Switch_Config_t Local_LlsConfig = {
        .PinId = Copy_WaterTankConfig->LlsPinId,
        .SwitchType = SWITCH_TEMPORARY,
        .PullType = Copy_WaterTankConfig->LlsPullingType,
        .InterruptEnable = Copy_WaterTankConfig->LlsInterruptEnable,
        .ExtiPinConfig = Copy_WaterTankConfig->LlsExtiPinConfig
    };
    
    if (WTRTANK_SWITCH_INT_ENABLE == Copy_WaterTankConfig->HlsInterruptEnable)
    {
        Switch_Init(&Local_HlsConfig);
    }

    if (WTRTANK_SWITCH_INT_ENABLE == Copy_WaterTankConfig->LlsInterruptEnable)
    {
        Switch_Init(&Local_LlsConfig);
    }

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t WtrTank_GetState(WtrTank_Config_t *Copy_WaterTankConfig, WtrTank_State_t *Copy_WaterTankState)
* \Description     : Get the water tank current state(full or empty)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_WaterTankConfig    Pointer to structure of water tank configuration
* \Parameters (out): Copy_WaterTankState     Pointer to return the tank current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t WtrTank_GetState(WtrTank_Config_t *Copy_WaterTankConfig, WtrTank_State_t *Copy_WaterTankState)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_HlsState;
    u8 Local_LlsState;
    Switch_Config_t Local_HlsConfig = {
        .PinId = Copy_WaterTankConfig->HlsPinId,
        .SwitchType = SWITCH_TEMPORARY,
        .PullType = Copy_WaterTankConfig->HlsPullingType,
        .InterruptEnable = Copy_WaterTankConfig->HlsInterruptEnable,
        .ExtiPinConfig = Copy_WaterTankConfig->HlsExtiPinConfig
    };
    Switch_Config_t Local_LlsConfig = {
        .PinId = Copy_WaterTankConfig->LlsPinId,
        .SwitchType = SWITCH_TEMPORARY,
        .PullType = Copy_WaterTankConfig->LlsPullingType,
        .InterruptEnable = Copy_WaterTankConfig->LlsInterruptEnable,
        .ExtiPinConfig = Copy_WaterTankConfig->LlsExtiPinConfig
    };

    /* Check the function arguments then early return */
    if ((NULL == Copy_WaterTankConfig) || (NULL == Copy_WaterTankState))
    {
        return E_NULL_POINTER;
    }
    else if (!IsWaterTankConfigValid(Copy_WaterTankConfig))
    {
        return E_WRONG_OPTION;
    }

#if SOFTWARE_DEBOUNCING == USED
    /* Get the current state of high level switch(HLS) (pressed or not pressed) */
    Local_ErrorState = Switch_GetStateDebounce(&Local_HlsConfig, &Local_HlsState, &SysTick_Delay, DEBOUNCING_TIME);
    /* Get the current state of low level switch(LLS) (pressed or not pressed) */
    Local_ErrorState = Switch_GetStateDebounce(&Local_LlsConfig, &Local_LlsState, &SysTick_Delay, DEBOUNCING_TIME);
#elif SOFTWARE_DEBOUNCING == NOT_USED
    /* Get the current state of high level switch(HLS) (pressed or not pressed) */
    Local_ErrorState = Switch_GetState(&Local_HlsConfig, &Local_HlsState);
    /* Get the current state of low level switch(LLS) (pressed or not pressed) */
    Local_ErrorState = Switch_GetState(&Local_LlsConfig, &Local_LlsState);
#else
#error "Wrong SOFTWARE_DEBOUNCING configuration option"
#endif

    if ((WTRTANK_SWITCH_NORMALLY_OPENED == Copy_WaterTankConfig->HlsInitState) && (WTRTANK_SWITCH_NORMALLY_CLOSED == Copy_WaterTankConfig->LlsInitState))
    {
        if ((SWITCH_PRESSED == Local_HlsState) && (SWITCH_NOT_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_FULL;
        }
        else if ((SWITCH_NOT_PRESSED == Local_HlsState) && (SWITCH_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_EMPTY;
        }
        else if ((SWITCH_NOT_PRESSED == Local_HlsState) && (SWITCH_NOT_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_STANDBY;
        }
    }
    else if ((WTRTANK_SWITCH_NORMALLY_CLOSED == Copy_WaterTankConfig->HlsInitState) && (WTRTANK_SWITCH_NORMALLY_OPENED == Copy_WaterTankConfig->LlsInitState))
    {
        if ((SWITCH_NOT_PRESSED == Local_HlsState) && (SWITCH_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_FULL;
        }
        else if ((SWITCH_PRESSED == Local_HlsState) && (SWITCH_NOT_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_EMPTY;
        }
        else if ((SWITCH_PRESSED == Local_HlsState) && (SWITCH_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_STANDBY;
        }
    }
    else if ((WTRTANK_SWITCH_NORMALLY_CLOSED == Copy_WaterTankConfig->HlsInitState) && (WTRTANK_SWITCH_NORMALLY_CLOSED == Copy_WaterTankConfig->LlsInitState))
    {
        if ((SWITCH_NOT_PRESSED == Local_HlsState) && (SWITCH_NOT_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_FULL;
        }
        else if ((SWITCH_PRESSED == Local_HlsState) && (SWITCH_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_EMPTY;
        }
        else if ((SWITCH_PRESSED == Local_HlsState) && (SWITCH_NOT_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_STANDBY;
        }
    }
    else if ((WTRTANK_SWITCH_NORMALLY_OPENED == Copy_WaterTankConfig->HlsInitState) && (WTRTANK_SWITCH_NORMALLY_OPENED == Copy_WaterTankConfig->LlsInitState))
    {
        if ((SWITCH_PRESSED == Local_HlsState) && (SWITCH_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_FULL;
        }
        else if ((SWITCH_NOT_PRESSED == Local_HlsState) && (SWITCH_NOT_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_EMPTY;
        }
        else if ((SWITCH_NOT_PRESSED == Local_HlsState) && (SWITCH_PRESSED == Local_LlsState))
        {
            *Copy_WaterTankState = WTRTANK_STANDBY;
        }
    }
    
    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  END OF FILE: WtrTank_Interface.h
 *********************************************************************************************************************/
