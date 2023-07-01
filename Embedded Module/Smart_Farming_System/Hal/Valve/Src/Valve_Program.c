/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Valve_Program.c
 *		  Layer:  Hal
 *       Module:  Valve (Solenoid Valve (Mini))
 *		Version:  1.0
 *	
 *  Description:  A solenoid valve driver to turn on and off the valve using switches
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "Gpio_Interface.h"

#include "Valve_Interface.h"
#include "Valve_Private.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsValveConfigValid(Valve_Config_t *Copy_ValveConfig)
* \Description     : Check the valve configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_ValveConfig    Pointer to structure of Valve configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsValveConfigValid(Valve_Config_t *Copy_ValveConfig)
{
    if ((Copy_ValveConfig->PinId > GPIO_PIN_K15) || (Copy_ValveConfig->PinId < GPIO_PIN_A0)
        || (Copy_ValveConfig->ActivationType > VALVE_ACTIVE_HIGH)|| (Copy_ValveConfig->ActivationType < VALVE_ACTIVE_LOW))
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Valve_Open(Valve_Config_t *Copy_ValveConfig)
* \Description     : Open the valve to let the fluid go through
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_ValveConfig    Pointer to structure of valve configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Valve_Open(Valve_Config_t *Copy_ValveConfig)
{
    ErrorState_t Local_ErrorState = E_OK;

    /* Check the function arguments then early return */
    if (NULL == Copy_ValveConfig)
    {
        return E_NULL_POINTER;
    }
    else if (!IsValveConfigValid(Copy_ValveConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Turn the switch on depending on its type: If VALVE_ACTIVE_HIGH switch needs a logical one to be enabled
                                                 If VALVE_ACTIVE_LOW switch needs a logical zero to be enabled */
    Local_ErrorState = Gpio_WritePin(Copy_ValveConfig->PinId, Copy_ValveConfig->ActivationType);

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Valve_Close(Valve_Config_t *Copy_ValveConfig)
* \Description     : Close the valve to stop the fluid from going through
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_ValveConfig    Pointer to structure of valve configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Valve_Close(Valve_Config_t *Copy_ValveConfig)
{
    ErrorState_t Local_ErrorState = E_OK;

    /* Check the function arguments then early return */
    if (NULL == Copy_ValveConfig)
    {
        return E_NULL_POINTER;
    }
    else if (!IsValveConfigValid(Copy_ValveConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Turn the switch on depending off its type: If VALVE_ACTIVE_HIGH switch needs a logical zero to be disabled
                                                  If VALVE_ACTIVE_LOW switch needs a logical one to be disabled */
    Local_ErrorState = Gpio_WritePin(Copy_ValveConfig->PinId, !(Copy_ValveConfig->ActivationType));

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Valve_GetState(Valve_Config_t *Copy_ValveConfig, u8 *Copy_ValveState)
* \Description     : Get the valve current state(opened or closed)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_ValveConfig    Pointer to structure of valve configuration
* \Parameters (out): Copy_ValveState     Pointer to assign the valve current state to this variable
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Valve_GetState(Valve_Config_t *Copy_ValveConfig, u8 *Copy_ValveState)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_PinValue;

    /* Check the function arguments then early return */
    if ((NULL == Copy_ValveConfig) || (NULL == Copy_ValveState))
    {
        return E_NULL_POINTER;
    }
    else if (!IsValveConfigValid(Copy_ValveConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Get the valve state depending on its type: If VALVE_ACTIVE_HIGH valve state will opened if pin is high, closed if pin is low
                                                  If VALVE_ACTIVE_LOW valve state will opened if pin is low, closed if pin is high */
    Local_ErrorState = Gpio_ReadPin(Copy_ValveConfig->PinId, &Local_PinValue);

    /* Get the valve state for each type of electrical switches */
    if (VALVE_ACTIVE_HIGH == Copy_ValveConfig->ActivationType)
    {
        if (GPIO_HIGH == Local_PinValue)
        {
            *Copy_ValveState = VALVE_OPENED;
        }
        else if (GPIO_LOW == Local_PinValue)
        {
            *Copy_ValveState = VALVE_CLOSED;
        }
    }
    else if (VALVE_ACTIVE_LOW == Copy_ValveConfig->ActivationType)
    {
        if (GPIO_LOW == Local_PinValue)
        {
            *Copy_ValveState = VALVE_OPENED;
        }
        else if (GPIO_HIGH == Local_PinValue)
        {
            *Copy_ValveState = VALVE_CLOSED;
        }
    }

    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  END OF FILE: Valve_Program.c
 *********************************************************************************************************************/
