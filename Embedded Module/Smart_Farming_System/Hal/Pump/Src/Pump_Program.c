/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Pump_Program.c
 *		  Layer:  Hal
 *       Module:  Pump (Mini Water Pump)
 *		Version:  1.0
 *	
 *  Description:  A mini water pump driver to turn on and off the pump using electrical switch
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "Gpio_Interface.h"

#include "Pump_Interface.h"
#include "Pump_Private.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsPumpConfigValid(Pump_Config_t *Copy_PumpConfig)
* \Description     : Check the pump configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_PumpConfig    Pointer to structure of pump configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsPumpConfigValid(Pump_Config_t *Copy_PumpConfig)
{
    if ((Copy_PumpConfig->PinId > GPIO_PIN_K15) || (Copy_PumpConfig->PinId < GPIO_PIN_A0)
        || (Copy_PumpConfig->ActivationType > PUMP_ACTIVE_HIGH)|| (Copy_PumpConfig->ActivationType < PUMP_ACTIVE_LOW))
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Pump_TurnOn(Pump_Config_t *Copy_PumpConfig)
* \Description     : Turn the mini water pump on
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_PumpConfig    Pointer to structure of pump configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Pump_TurnOn(Pump_Config_t *Copy_PumpConfig)
{
    ErrorState_t Local_ErrorState = E_OK;

    /* Check the function arguments */
    if (NULL == Copy_PumpConfig)
    {
        return E_NULL_POINTER;
    }
    else if (!IsPumpConfigValid(Copy_PumpConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Turn the switch on depending on its type: If PUMP_ACTIVE_HIGH switch needs a logical one to be enabled
                                                 If PUMP_ACTIVE_LOW switch needs a logical zero to be enabled */
    Local_ErrorState = Gpio_WritePin(Copy_PumpConfig->PinId, Copy_PumpConfig->ActivationType);

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Pump_TurnOff(Pump_Config_t *Copy_PumpConfig)
* \Description     : Turn the mini water pump off
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_PumpConfig    Pointer to structure of pump configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Pump_TurnOff(Pump_Config_t *Copy_PumpConfig)
{
    ErrorState_t Local_ErrorState = E_OK;

    /* Check the function arguments */
    if (NULL == Copy_PumpConfig)
    {
        return E_NULL_POINTER;
    }
    else if (!IsPumpConfigValid(Copy_PumpConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Turn the switch off depending on its type: If PUMP_ACTIVE_HIGH switch needs a logical zero to be disabled
                                                  If PUMP_ACTIVE_LOW switch needs a logical one to be disabled */
    Local_ErrorState = Gpio_WritePin(Copy_PumpConfig->PinId, !(Copy_PumpConfig->ActivationType));

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Pump_GetState(Pump_Config_t *Copy_PumpConfig, u8 *Copy_PumpState)
* \Description     : Get the pump current state(opened or closed)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_PumpConfig    Pointer to structure of pump configuration
* \Parameters (out): Copy_PumpState     Pointer to assign the pump current state to this variable
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Pump_GetState(Pump_Config_t *Copy_PumpConfig, u8 *Copy_PumpState)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_PinValue;

    /* Check the function arguments then early return */
    if ((NULL == Copy_PumpConfig) || (NULL == Copy_PumpState))
    {
        return E_NULL_POINTER;
    }
    else if (!IsPumpConfigValid(Copy_PumpConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Get the pump state depending on its type: If PUMP_ACTIVE_HIGH pump state will turned on if pin is high, turned off if pin is low 
                                                 If PUMP_ACTIVE_LOW pump state will turned on if pin is low, turned off if pin is high  */
    Local_ErrorState = Gpio_ReadPin(Copy_PumpConfig->PinId, &Local_PinValue);

    /* Get the pump state for each type of electrical switches */
    if (PUMP_ACTIVE_HIGH == Copy_PumpConfig->ActivationType)
    {
        if (GPIO_HIGH == Local_PinValue)
        {
            *Copy_PumpState = PUMP_TURNED_ON;
        }
        else if (GPIO_LOW == Local_PinValue)
        {
            *Copy_PumpState = PUMP_TURNED_OFF;
        }
    }
    else if (PUMP_ACTIVE_LOW == Copy_PumpConfig->ActivationType)
    {
        if (GPIO_LOW == Local_PinValue)
        {
            *Copy_PumpState = PUMP_TURNED_ON;
        }
        else if (GPIO_HIGH == Local_PinValue)
        {
            *Copy_PumpState = PUMP_TURNED_OFF;
        }
    }

    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  END OF FILE: Pump_Program.c
 *********************************************************************************************************************/
