/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Fc28_Program.c
 *		  Layer:  Hal
 *       Module:  Fc28
 *		Version:  1.0
 *	
 *  Description: A Fc28 driver that get the soil moisture current state(dry soil or humid soil)
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "Gpio_Interface.h"
#include "Adc_Interface.h"
#include "Exti_Interface.h"

#include "Fc28_Interface.h"
#include "Fc28_Private.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static DigitalPinId;

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsFc28ConfigValid(Fc28_Config_t *Copy_Fc28Config)
* \Description     : Check the fc28 configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_Fc28Config    Pointer to structure of fc28 configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsFc28ConfigValid(Fc28_Config_t *Copy_Fc28Config)
{
    if ((Copy_Fc28Config->AnalogPinId > GPIO_PIN_K15) || (Copy_Fc28Config->AnalogPinId < GPIO_PIN_A0)
        || (Copy_Fc28Config->DigitalPinId > GPIO_PIN_K15) || (Copy_Fc28Config->DigitalPinId < GPIO_PIN_A0)
        || (Copy_Fc28Config->Adc_Resolution > ADC_6BIT) || (Copy_Fc28Config->Adc_Resolution < ADC_12BIT))
        // || (NULL == Copy_Fc28Config->Adc_ConversionConfig))
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Fc28_Init(Fc28_Config_t *Copy_Fc28Config)
* \Description     : Initialize the FC-28 module
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_Fc28Config    Pointer to structure of fc28 configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Fc28_Init(Fc28_Config_t *Copy_Fc28Config)
{
    ErrorState_t Local_ErrorState = E_OK;

    /* Initialize the ADC */
    Local_ErrorState = Adc_Init(Copy_Fc28Config->Adc_ConversionConfig->Adc, Copy_Fc28Config->Adc_Resolution, ADC_DATA_RIGHT_ALIGNMENT);

    /* Check if the pin interrupt is enabled then initialize the EXTI and enable it */
    if (FC28_INT_ENABLE == Copy_Fc28Config->DigitalPinInterruptEnable)
    {
        Local_ErrorState = Exti_PinInit(Copy_Fc28Config->ExtiPinConfig);
        Exti_IntEnable(Copy_Fc28Config->ExtiPinConfig->Pin);
    }

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Fc28_GetSoilMoisturePercentage(Fc28_Config_t *Copy_Fc28Config, u8 *Copy_MoisturePercentage)
* \Description     : Get the soil moisture current percentage
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_Fc28Config    Pointer to structure of fc28 configuration
* \Parameters (out): Copy_MoisturePercentage     Pointer to return the soil moisture percentage
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Fc28_GetSoilMoisturePercentage(Fc28_Config_t *Copy_Fc28Config, u8 *Copy_MoisturePercentage)
{
    ErrorState_t Local_ErrorState = E_OK;
    u16 Local_AdcReading;
    u32 Local_AdcMaxValue = (1 << Copy_Fc28Config->Adc_Resolution) - 1;

    /* Check the function arguments then early return */
    if ((NULL == Copy_Fc28Config) || (NULL == Copy_MoisturePercentage))
    {
        return E_NULL_POINTER;
    }
    else if (!IsFc28ConfigValid(Copy_Fc28Config))
    {
        return E_WRONG_OPTION;
    }
    
    /* Get the ADC reading */
    Local_AdcReading = Adc_StartConversionSynch(Copy_Fc28Config->Adc_ConversionConfig, &Local_AdcReading);

    /* Convert ADC voltage into soil moisture */
    *Copy_MoisturePercentage = 100 - (Local_AdcReading * 100UL / Local_AdcMaxValue);

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Fc28_GetSoilMoistureStateDig(Fc28_Config_t *Copy_Fc28Config, Fc28_MoistureState_t *Copy_MoistureState)
* \Description     : Get the soil moisture current state using digital pins: - Dry Soil - Humid Soil
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_Fc28Config    Pointer to structure of fc28 configuration
* \Parameters (out): Copy_MoistureState     Pointer to return the soil moisture current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Fc28_GetSoilMoistureStateDig(Fc28_Config_t *Copy_Fc28Config, Fc28_MoistureState_t *Copy_MoistureState)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_PinValue;

    /* Check the function arguments then early return */
    if ((NULL == Copy_Fc28Config) || (NULL == Copy_MoistureState))
    {
        return E_NULL_POINTER;
    }
    else if (!IsFc28ConfigValid(Copy_Fc28Config))
    {
        return E_WRONG_OPTION;
    }
    
    /* Get the Digital pin value */
    Local_ErrorState = Gpio_ReadPin(Copy_Fc28Config->DigitalPinId, &Local_PinValue);

    if (GPIO_LOW == Local_PinValue)
    {
        *Copy_MoistureState = FC28_HUMID_SOIL;
    }
    else if (GPIO_HIGH == Local_PinValue)
    {
        *Copy_MoistureState = FC28_DRY_SOIL;
    }

    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  END OF FILE: Fc28_Program.c
 *********************************************************************************************************************/
