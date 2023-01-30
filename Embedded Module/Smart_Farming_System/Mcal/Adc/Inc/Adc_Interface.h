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
ErrorState_t Adc_Init(Adc_Num Copy_Adc, Adc_Resolution Copy_AdcRes, Adc_DataAlignment Copy_DataAlignment);

ErrorState_t Adc_StartConversionSynch(Adc_ConversionConfig_t* Copy_ConvConfig);

ErrorState_t Adc_StartConversionAsynch(Adc_ConversionConfig_t* Copy_ConvConfig, void(*Copy_NotificationFunc));

ErrorState_t Adc_StartChainConversionSynch(Adc_ChainConvConfig_t* Copy_ChainConfig);

ErrorState_t Adc_StartChainConversionAsynch(Adc_ChainConvConfig_t* Copy_ChainConfig, void(*Copy_NotificationFunc));
 
#endif  /* ADC_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Adc_Interface.h
 *********************************************************************************************************************/