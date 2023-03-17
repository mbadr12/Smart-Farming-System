/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Adc_Interface.h
 *		  Layer:  Mcal
 *       Module:  Adc
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Adc_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t Adc_Init(Adc_Num Copy_Adc, Adc_Resolution Copy_AdcRes, Adc_DataAlignment Copy_DataAlignment)
 * \Description     : Initialize the ADC
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Adc   	  		The ADC number to be configured
 * 					  Copy_AdcRes	  		The ADC resolution
 * 					  Copy_DataAlignment	The conversion output alignment
 * \Parameters (out): None
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Adc_Init(Adc_Num Copy_Adc, Adc_Resolution Copy_AdcRes, Adc_DataAlignment Copy_DataAlignment);

/******************************************************************************
 * \Syntax          : ErrorState_t Adc_StartConversionSynch(Adc_ConversionConfig_t* Copy_ConvConfig, u16* Copy_Reading)
 * \Description     : Convert channel in a synchronous way
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_ConvConfig   	The configuration of channel
 * \Parameters (out): Copy_Reading			The conversion output
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Adc_StartConversionSynch(Adc_ConversionConfig_t* Copy_ConvConfig, u16* Copy_Reading);

/******************************************************************************
 * \Syntax          : ErrorState_t Adc_StartConversionAsynch(Adc_ConversionConfig_t* Copy_ConvConfig, u16* Copy_Reading, void(*Copy_NotificationFunc)(void))
 * \Description     : Convert channel in an asynchronous way
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_ConvConfig   		The configuration of channel
 * 					  Copy_NotificationFunc		pointer to notification function to notify the end of conversion
 * \Parameters (out): Copy_Reading				The conversion output
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Adc_StartConversionAsynch(Adc_ConversionConfig_t* Copy_ConvConfig, u16* Copy_Reading, void(*Copy_NotificationFunc)(void));

/******************************************************************************
 * \Syntax          : ErrorState_t Adc_StartChainConversionSynch(Adc_ChainConvConfig_t* Copy_ChainConfig, u16* Copy_Reading)
 * \Description     : Convert chain of channels in a synchronous way
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_ConvConfig   	The configuration of the chain of channels
 * \Parameters (out): Copy_Reading			The conversion output
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Adc_StartChainConversionSynch(Adc_ChainConvConfig_t* Copy_ChainConfig, u16* Copy_Reading);

/******************************************************************************
 * \Syntax          : ErrorState_t Adc_StartChainConversionAsynch(Adc_ChainConvConfig_t* Copy_ChainConfig, u16* Copy_Reading, void(*Copy_NotificationFunc)(void))
 * \Description     : Convert chain of channels in an asynchronous way
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_ConvConfig   		The configuration of the chain of channels
 * 					  Copy_NotificationFunc		pointer to notification function to notify the end of conversion
 * \Parameters (out): Copy_Reading				The conversion output
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Adc_StartChainConversionAsynch(Adc_ChainConvConfig_t* Copy_ChainConfig, u16* Copy_Reading, void(*Copy_NotificationFunc)(void));
 
#endif  /* ADC_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Adc_Interface.h
 *********************************************************************************************************************/
