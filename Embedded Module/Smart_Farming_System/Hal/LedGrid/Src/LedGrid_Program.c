/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  LedGrid_Program.c
 *		  Layer:  Hal
 *       Module:  LedGrid
 *		Version:  1.0
 *	
 *  Description: A LED grid driver that turn on and off the LED grid using electrical/electromechanical switch
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "LedGrid_Private.h"
#include "LedGrid_Interface.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsLedGridConfigValid(LedGrid_Config_t *Copy_LedGridConfig)
* \Description     : Check the LED grid configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LedGridConfig    Pointer to structure of LedGrid configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsLedGridConfigValid(LedGrid_Config_t *Copy_LedGridConfig)
{
    if ((Copy_LedGridConfig->PinId > GPIO_PIN_K15) || (Copy_LedGridConfig->PinId < GPIO_PIN_A0)
        || (Copy_LedGridConfig->ActivationType > LEDGRID_ACTIVE_HIGH)|| (Copy_LedGridConfig->ActivationType < LEDGRID_ACTIVE_LOW))
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t LedGrid_TurnOn(LedGrid_Config_t *Copy_LedGridConfig)
* \Description     : Turn the LED grid on
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LedGridConfig    Pointer to structure of LedGrid configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t LedGrid_TurnOn(LedGrid_Config_t *Copy_LedGridConfig)
{
    ErrorState_t Local_ErrorState = E_OK;

    /* Check the function arguments */
    if (NULL == Copy_LedGridConfig)
    {
        return E_NULL_POINTER;
    }
    else if (!IsLedGridConfigValid(Copy_LedGridConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Turn the switch on depending on its type: If LEDGRID_ACTIVE_HIGH (switch is active high), needs a logical one to be enabled
                                                 If LEDGRID_ACTIVE_LOW (switch is avtive low), needs a logical zero to be enabled */
    Local_ErrorState = Gpio_WritePin(Copy_LedGridConfig->PinId, Copy_LedGridConfig->ActivationType);

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t LedGrid_TurnOff(LedGrid_Config_t *Copy_LedGridConfig)
* \Description     : Turn the LED grid off
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LedGridConfig    Pointer to structure of LedGrid configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t LedGrid_TurnOff(LedGrid_Config_t *Copy_LedGridConfig)
{
    ErrorState_t Local_ErrorState = E_OK;

    /* Check the function arguments */
    if (NULL == Copy_LedGridConfig)
    {
        return E_NULL_POINTER;
    }
    else if (!IsLedGridConfigValid(Copy_LedGridConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Turn the switch off depending on its type: If LEDGRID_ACTIVE_HIGH (switch is active high), needs a logical zero to be disabled
                                                  If LEDGRID_ACTIVE_LOW (switch is avtive low), needs a logical one to be disabled */
    Local_ErrorState = Gpio_WritePin(Copy_LedGridConfig->PinId, !(Copy_LedGridConfig->ActivationType));

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t LedGrid_GetState(LedGrid_Config_t *Copy_LedGridConfig, u8 *Copy_LedGridState)
* \Description     : Get the LED grid current state(on or off)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LedGridConfig    Pointer to structure of LedGrid configuration
* \Parameters (out): Copy_LedGridState     Pointer to assign the LedGrid current state to this variable
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t LedGrid_GetState(LedGrid_Config_t *Copy_LedGridConfig, u8 *Copy_LedGridState)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_PinValue;

    /* Check the function arguments then early return */
    if ((NULL == Copy_LedGridConfig) || (NULL == Copy_LedGridState))
    {
        return E_NULL_POINTER;
    }
    else if (!IsLedGridConfigValid(Copy_LedGridConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Get the LED grid state depending on its type: If LEDGRID_ACTIVE_HIGH LED grid state will turned on if pin is high, turned off if pin is low 
                                                     If LEDGRID_ACTIVE_LOW LED grid state will turned on if pin is low, turned off if pin is high  */
    Local_ErrorState = Gpio_ReadPin(Copy_LedGridConfig->PinId, &Local_PinValue);

    /* Get the LED grid state for each type of electrical/electromechanical switches */
    if (LEDGRID_ACTIVE_HIGH == Copy_LedGridConfig->ActivationType)
    {
        if (GPIO_HIGH == Local_PinValue)
        {
            *Copy_LedGridState = LEDGRID_TURNED_ON;
        }
        else if (GPIO_LOW == Local_PinValue)
        {
            *Copy_LedGridState = LEDGRID_TURNED_OFF;
        }
    }
    else if (LEDGRID_ACTIVE_LOW == Copy_LedGridConfig->ActivationType)
    {
        if (GPIO_LOW == Local_PinValue)
        {
            *Copy_LedGridState = LEDGRID_TURNED_ON;
        }
        else if (GPIO_HIGH == Local_PinValue)
        {
            *Copy_LedGridState = LEDGRID_TURNED_OFF;
        }
    }

    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  END OF FILE: LedGrid_Program.c
 *********************************************************************************************************************/
