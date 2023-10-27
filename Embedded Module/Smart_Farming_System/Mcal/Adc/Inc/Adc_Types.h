/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Adc_Types.h
 *		  Layer:  Mcal
 *       Module:  Adc
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef ADC_TYPES_H
#define ADC_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define NOT_USED	17

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
	ADC_1=0,
	ADC_2,
	ADC_3
}Adc_Num;

typedef enum
{
	ADC_CHANNEL0=0,
	ADC_CHANNEL1,
	ADC_CHANNEL2,
	ADC_CHANNEL3,
	ADC_CHANNEL4,
	ADC_CHANNEL5,
	ADC_CHANNEL6,
	ADC_CHANNEL7,
	ADC_CHANNEL8,
	ADC_CHANNEL9,
	ADC_CHANNEL10,
	ADC_CHANNEL11,
	ADC_CHANNEL12,
	ADC_CHANNEL13,
	ADC_CHANNEL14,
	ADC_CHANNEL15
}Adc_ChannelNum;

typedef enum
{
	ADC_12BIT=0,
	ADC_10BIT,
	ADC_8BIT,
	ADC_6BIT
}Adc_Resolution;

typedef enum
{
	ADC_SW_TRIGGER=0,
	ADC_EXT_TRIGGER
}Adc_TriggerType;

typedef enum
{
	ADC_DETECT_DISABLE=0,
	ADC_DETECT_RAISING,
	ADC_DETECT_FAILLING,
	ADC_DETECT_RAISING_AND_FAILLING
}Adc_ExtTriggerSense;

typedef enum
{
	ADC_TIMER1_CC1=0,
	ADC_TIMER1_CC2,
	ADC_TIMER1_CC3,
	ADC_TIMER2_CC2,
	ADC_TIMER2_CC3,
	ADC_TIMER2_CC4,
	ADC_TIMER2_TRGO,
	ADC_TIMER3_CC1,
	ADC_TIMER3_TRGO,
	ADC_TIMER4_CC4,
	ADC_TIMER5_CC1,
	ADC_TIMER5_CC2,
	ADC_TIMER5_CC3,
	ADC_TIMER8_CC1,
	ADC_TIMER8_TRGO,
	ADC_EXTI_11
}Adc_RegularExtTrigger;

typedef enum
{
	ADC_TIMER1_CC4=0,
	ADC_TIMER1_TRGO,
	ADC_TIMER2_CC1,
	ADC_TIMER2_TRGO1,
	ADC_TIMER3_CC2,
	ADC_TIMER3_CC4,
	ADC_TIMER4_CC1,
	ADC_TIMER4_CC2,
	ADC_TIMER4_CC3,
	ADC_TIMER4_TRGO,
	ADC_TIMER5_CC4,
	ADC_TIMER5_TRGO,
	ADC_TIMER8_CC2,
	ADC_TIMER8_CC3,
	ADC_TIMER8_CC4,
	ADC_EXTI_15
}Adc_InjectedExtTrigger;

typedef enum
{
	ADC_DATA_RIGHT_ALIGNMENT=0,
	ADC_DATA_LEFT_ALIGNMENT
}Adc_DataAlignment;

typedef enum
{
	ADC_3_CYCLES=0,
	ADC_15_CYCLES,
	ADC_28_CYCLES,
	ADC_56_CYCLES,
	ADC_84_CYCLES,
	ADC_112_CYCLES,
	ADC_144_CYCLES,
	ADC_480_CYCLES
}Adc_ChannelSampleTime;

typedef enum
{
	ADC_REGULAR_CHANNEL=0,
	ADC_INJECTED_CHANNEL
}Adc_ChannelType;

typedef enum
{
	ADC_CONT=0,
	ADC_SCAN,
	ADC_DISCONT
}Adc_ChainConvType;

typedef struct
{
	Adc_Num Adc;
	Adc_ChannelType ChannelType;
	Adc_ChannelNum Channel;
	Adc_TriggerType TriggerType;
	Adc_ExtTriggerSense Sense;
	Adc_RegularExtTrigger ExtTrigger;
	Adc_ChannelSampleTime SampleTime;
}Adc_ConversionConfig_t;

typedef struct
{
	Adc_Num Adc;
	Adc_ChannelType ChannelType;
	Adc_ChainConvType ConvType;
	Adc_ChannelNum *Channel;
	u8 ConversionsNumber;
	Adc_TriggerType TriggerType;
	Adc_ExtTriggerSense Sense;
	Adc_RegularExtTrigger ExtTrigger;
	Adc_ChannelSampleTime* SampleTime;
}Adc_ChainConvConfig_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#endif  /* ADC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Adc_Types.h
 *********************************************************************************************************************/
