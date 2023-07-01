/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Ldr_Program.c
 *		  Layer:  Hal
 *       Module:  Ldr
 *		Version:  1.0
 *	
 *  Description: A Ldr driver that get the illumination(ambiance light) current state(dark or bright)
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "Gpio_Interface.h"
#include "Adc_Interface.h"

#include "Ldr_Interface.h"
#include "Ldr_Private.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsLdrConfigValid(Ldr_Config_t *Copy_LdrConfig)
* \Description     : Check the Ldr configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_LdrConfig    Pointer to structure of Ldr configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsLdrConfigValid(Ldr_Config_t *Copy_LdrConfig)
{
    if ((Copy_LdrConfig->AnalogPinId > GPIO_PIN_K15) || (Copy_LdrConfig->AnalogPinId < GPIO_PIN_A0)
        || (Copy_LdrConfig->DigitalPinId > GPIO_PIN_K15) || (Copy_LdrConfig->DigitalPinId < GPIO_PIN_A0)
        || (Copy_LdrConfig->Adc_Resolution > ADC_6BIT) || (Copy_LdrConfig->Adc_Resolution < ADC_12BIT)
        || (NULL == Copy_LdrConfig->Adc_ConversionConfig))
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Ldr_Init(Ldr_Config_t *Copy_LdrConfig)
* \Description     : Initialize the LDR module
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_LdrConfig    Pointer to structure of Ldr configuration
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Ldr_Init(Ldr_Config_t *Copy_LdrConfig)
{
    ErrorState_t Local_ErrorState = E_OK;

    /* Initialize the ADC */
    Local_ErrorState = Adc_Init(Copy_LdrConfig->Adc_ConversionConfig->Adc, Copy_LdrConfig->Adc_Resolution, ADC_DATA_RIGHT_ALIGNMENT);

    /* Check if the pin interrupt is enabled then initialize the EXTI and enable it */
    if (LDR_INT_ENABLE == Copy_LdrConfig->DigitalPinInterruptEnable)
    {
        Local_ErrorState = Exti_PinInit(Copy_LdrConfig->ExtiPinConfig);
        Exti_IntEnable(Copy_LdrConfig->ExtiPinConfig->Pin);
    }

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Ldr_GetLuminancePercentage(Ldr_Config_t *Copy_LdrConfig, u8 *Copy_LuminancePercentage)
* \Description     : Get the luminance(ambiance light) current percentage
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_LdrConfig    Pointer to structure of Ldr configuration
* \Parameters (out): Copy_LuminancePercentage     Pointer to return the luminance(ambiance light) current percentage
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Ldr_GetLuminancePercentage(Ldr_Config_t *Copy_LdrConfig, u8 *Copy_LuminancePercentage)
{
    ErrorState_t Local_ErrorState = E_OK;
    u16 Local_AdcReading;
    u32 Local_AdcMaxValue = (1 << Copy_LdrConfig->Adc_Resolution) - 1;

    /* Check the function arguments then early return */
    if ((NULL == Copy_LdrConfig) || (NULL == Copy_LuminancePercentage))
    {
        return E_NULL_POINTER;
    }
    else if (!IsLdrConfigValid(Copy_LdrConfig))
    {
        return E_WRONG_OPTION;
    }

    /* Get the ADC reading */
    Local_AdcReading = Adc_StartConversionSynch(Copy_LdrConfig->Adc_ConversionConfig, &Local_AdcReading);

    /* Convert ADC voltage into soil moisture */
    *Copy_LuminancePercentage = Local_AdcReading * 100UL / Local_AdcMaxValue;

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Ldr_GetIlluminationStateDig(Ldr_Config_t *Copy_LdrConfig, Ldr_IlluminationState_t *Copy_IlluminationState)
* \Description     : Get the illumination(ambiance light) current state using digital pins: - Dark - Bright
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_LdrConfig    Pointer to structure of Ldr configuration
* \Parameters (out): Copy_IlluminationState     Pointer to return the illumination(ambiance light) current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Ldr_GetIlluminationStateDig(Ldr_Config_t *Copy_LdrConfig, Ldr_IlluminationState_t *Copy_IlluminationState)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_PinValue;

    /* Check the function arguments then early return */
    if ((NULL == Copy_LdrConfig) || (NULL == Copy_IlluminationState))
    {
        return E_NULL_POINTER;
    }
    else if (!IsLdrConfigValid(Copy_LdrConfig))
    {
        return E_WRONG_OPTION;
    }
    
    /* Get the Digital pin value */
    Local_ErrorState = Gpio_ReadPin(Copy_LdrConfig->DigitalPinId, &Local_PinValue);

    if (GPIO_LOW == Local_PinValue)
    {
        *Copy_IlluminationState = LDR_BRIGHT;
    }
    else if (GPIO_HIGH == Local_PinValue)
    {
        *Copy_IlluminationState = LDR_DARK;
    }

    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  END OF FILE: Ldr_Program.c
 *********************************************************************************************************************/
