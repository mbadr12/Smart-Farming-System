/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Adc_Private.h
 *		  Layer:  Mcal
 *       Module:  Adc
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define ADC_DIV_BY_2		0
#define ADC_DIV_BY_4		1
#define ADC_DIV_BY_6		2
#define ADC_DIV_BY_8		3

#define ADC_5_ADC_CLK		0
#define ADC_6_ADC_CLK		1
#define ADC_7_ADC_CLK		2

#define ADCS_NUM			3

#define CR1					0
#define CR2					1

#define RES_SELECT			24

#define ALIGN_SELECT		11

#define EOCIE				5
#define SWSTART				30
#define JEOCIE				7
#define JSWSTART			22
#define INJ_TRIGGER_MASK	~(0b1111111<<16)
#define TRIGGER_MASK		~(0b1111111<<24)
#define EXT_TRG_SELECT		24
#define INJ_EXT_TRG_SENSE	20
#define INJ_EXT_TRG_SELECT	16
#define EXT_TRG_SENSE		28
#define JSQ4				15
#define SQR1				0
#define SQR2				1
#define SQR3				2
#define EOC_FLAG			1
#define JEOC_FLAG			2
#define CONT				1
#define SCAN				8
#define EOCS				10
#define DISCEN				11
#define JDISCEN				12
#define MAX_DISCEN			6
#define DISCNUM				13
#define MAX_REG_CH			16
#define MAX_INJ_CH			4
#define JL					20
#define DELAY				8
#define JEOC				2

#define SAMPLE_MASK			~(0b111)

#define ADC_NUM				Copy_ConvConfig->Adc

#define ADC_CH_NUM			Copy_ChainConfig->Adc

#define ADC_REG				Adc_Arr[Copy_ConvConfig->Adc]

#define ADC_CH_REG			Adc_Arr[Copy_ChainConfig->Adc]

#define CONV_NUM			(Copy_ChainConfig->ConversionsNumber)

#define PRESCALER_MASK		~((u32)(0b11<<16))

#define INJ_SHIFT			(5*(3-Local_Counter))

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
#endif  /* ADC_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Adc_Private.h
 *********************************************************************************************************************/
