/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Adc_Program.c
 *		  Layer:  Mcal
 *       Module:  Adc
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "Adc_Interface.h"
#include "Adc_Private.h"
#include "Adc_Config.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static Adc_RegDef_t* Adc_Arr[ADCS_NUM]={ADC1, ADC2, ADC3};

static Peripheral_State Adc_State[ADCS_NUM]={IDLE};

static void(*Adc_CallBackFunc[ADCS_NUM])(void)={NULL};

static ISR_Src Adc_ISRSrc[ADCS_NUM]={SINGLE_CONVERSION};

static Adc_ChannelType Adc_ChType[ADCS_NUM]={ADC_REGULAR_CHANNEL};

static u16 *Adc_Result[ADCS_NUM]={NULL};

static u8 Adc_ConvNum[ADCS_NUM]={0};

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
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
ErrorState_t Adc_Init(Adc_Num Copy_Adc, Adc_Resolution Copy_AdcRes, Adc_DataAlignment Copy_DataAlignment)
{
	ErrorState_t Local_ErrorState=E_OK;
	if((Copy_Adc > ADC_3) || (Copy_AdcRes >ADC_6BIT) || (Copy_DataAlignment >ADC_DATA_LEFT_ALIGNMENT))
	{
		Local_ErrorState=E_WRONG_OPTION;
	}
	else
	{
		/*Reset the control registers*/
		Adc_Arr[Copy_Adc]->CR[CR1]=0;
		Adc_Arr[Copy_Adc]->CR[CR2]=0;
		/*Set the resolution of ADC*/
		Adc_Arr[Copy_Adc]->CR[CR1] |= Copy_AdcRes<<RES_SELECT;
		/*Set the Alignment of Data*/
		Adc_Arr[Copy_Adc]->CR[CR2] |= Copy_DataAlignment<<ALIGN_SELECT;
		/*Set the Pre-Scaler of ADC*/
		ADC_COMMON->CCR &= PRESCALER_MASK;
		ADC_COMMON->CCR |= ADC_PRESCALER<<16;
		/*Choose the delay between every two conversions*/
		ADC_COMMON->CCR |= ADC_DELAY<<DELAY;
		/*Enable the ADC*/
		Adc_Arr[Copy_Adc]->CR[CR2] |=1;
	}
	return Local_ErrorState;
}

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
ErrorState_t Adc_StartConversionSynch(Adc_ConversionConfig_t* Copy_ConvConfig, u16* Copy_Reading)
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_SampleReg=0;
	u8 Local_SampleShift=0;
	u16 Local_Counter=0;
	if((Copy_ConvConfig == NULL) || (Copy_Reading == NULL))
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if((ADC_NUM > ADC_3) || (Copy_ConvConfig->Channel > ADC_CHANNEL15))
		{
			Local_ErrorState = E_WRONG_OPTION;
		}
		else
		{
			if(Adc_State[ADC_NUM] == IDLE)
			{
				/*make ADC busy*/
				Adc_State[ADC_NUM]=BUSY;
				/*choose the sampling time of channel*/
				Local_SampleReg= 1-(Copy_ConvConfig->Channel/10);
				Local_SampleShift =3*(Copy_ConvConfig->Channel%10);
				ADC_REG->SMPR[Local_SampleReg] &= SAMPLE_MASK<<Local_SampleShift;
				ADC_REG->SMPR[Local_SampleReg] |= (Copy_ConvConfig->SampleTime)<<Local_SampleShift;
				/*check the channel type*/
				switch(Copy_ConvConfig->ChannelType)
				{
				case ADC_REGULAR_CHANNEL:
					/*make sure that the interrupt is disabled */
					CLR_BIT(ADC_REG->CR[CR1],EOCIE);
					/*Put the channel as first channel in the sequence of channels*/
					ADC_REG->SQR[SQR1]=0;
					ADC_REG->SQR[SQR3]=0;
					ADC_REG->SQR[SQR3] |=Copy_ConvConfig->Channel;
					/*choose the conversion trigger*/
					ADC_REG->CR[CR2] &= TRIGGER_MASK;
					SET_BIT(ADC_REG->CR[CR2],SWSTART);
					/*busy waiting in the End of conversion flag*/
					while((GET_BIT(ADC_REG->SR,EOC_FLAG)==0) && (Local_Counter< ADC_TIME_OUT))
					{
						Local_Counter++;
					}
					if(Local_Counter == ADC_TIME_OUT)
					{
						Local_ErrorState=E_TIME_OUT;
					}
					else
					{
						*Copy_Reading=ADC_REG->DR;
					}break;
				case ADC_INJECTED_CHANNEL:
					/*make sure that the interrupt is disabled */
					CLR_BIT(ADC_REG->CR[CR1],JEOCIE);
					/*Put the channel as first channel in the sequence of channels*/
					ADC_REG->JSQR=0;
					ADC_REG->JSQR |= Copy_ConvConfig->Channel<<JSQ4;
					/*choose the conversion trigger*/
					ADC_REG->CR[CR2] &= INJ_TRIGGER_MASK;
					SET_BIT(ADC_REG->CR[CR2],JSWSTART);
					/*busy waiting in the End of conversion flag*/
					while((GET_BIT(ADC_REG->SR,JEOC_FLAG)==0) && (Local_Counter< ADC_TIME_OUT))
					{
						Local_Counter++;
					}
					if(Local_Counter == ADC_TIME_OUT)
					{
						Local_ErrorState=E_TIME_OUT;
					}
					else
					{
						/*get the reading*/
						*Copy_Reading=ADC_REG->JDR[0];
						/*clear the end of conversion flag*/
						CLR_BIT(ADC_REG->SR,JEOC);
					}break;
				default: Local_ErrorState=E_WRONG_OPTION;
				}
				/*Make ADC idle*/
				Adc_State[ADC_NUM]=IDLE;
			}
			else
			{
				Local_ErrorState=E_BUSY_FUNC;
			}
		}
	}
	return Local_ErrorState;
}

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
ErrorState_t Adc_StartConversionAsynch(Adc_ConversionConfig_t* Copy_ConvConfig, u16* Copy_Reading, void(*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_SampleReg=0;
	u8 Local_SampleShift=0;
	if((Copy_ConvConfig == NULL) || (Copy_Reading == NULL))
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if((ADC_NUM > ADC_3) || (Copy_ConvConfig->Channel > ADC_CHANNEL15))
		{
			Local_ErrorState = E_WRONG_OPTION;
		}
		else
		{
			if(Adc_State[ADC_NUM] == IDLE)
			{
				/*make ADC busy*/
				Adc_State[ADC_NUM]=BUSY;
				/*Make interrupt source as single conversion*/
				Adc_ISRSrc[ADC_NUM]=SINGLE_CONVERSION;
				/*copy the parameters needed to global variables*/
				if(Copy_NotificationFunc !=NULL)
				{
					Adc_CallBackFunc[ADC_NUM] = Copy_NotificationFunc;
				}
				Adc_Result[ADC_NUM]=Copy_Reading;
				Adc_ChType[ADC_NUM]=Copy_ConvConfig->ChannelType;
				/*choose the sampling time of channel*/
				Local_SampleReg= 1-(Copy_ConvConfig->Channel/10);
				Local_SampleShift =3*(Copy_ConvConfig->Channel%10);
				ADC_REG->SMPR[Local_SampleReg] &= SAMPLE_MASK<<Local_SampleShift;
				ADC_REG->SMPR[Local_SampleReg] |= Copy_ConvConfig->SampleTime<<Local_SampleShift;
				/*check the channel type*/
				switch(Copy_ConvConfig->ChannelType)
				{
				case ADC_REGULAR_CHANNEL:
					/*Put the channel as first channel in the sequence of channels*/
					ADC_REG->SQR[SQR1]=0;
					ADC_REG->SQR[SQR3]=0;
					ADC_REG->SQR[SQR3] |=Copy_ConvConfig->Channel;
					/*choose the conversion trigger*/
					ADC_REG->CR[CR2] &= TRIGGER_MASK;
					switch(Copy_ConvConfig->TriggerType)
					{
					case ADC_SW_TRIGGER: SET_BIT(ADC_REG->CR[CR2],SWSTART); break;
					case ADC_EXT_TRIGGER: ADC_REG->CR[CR2] |= Copy_ConvConfig->Sense<<EXT_TRG_SENSE | Copy_ConvConfig->ExtTrigger<<EXT_TRG_SELECT; break;
					default: Local_ErrorState=E_WRONG_OPTION; break;
					}
					/*the interrupt is enabled */
					SET_BIT(ADC_REG->CR[CR1],EOCIE); break;
					case ADC_INJECTED_CHANNEL:
						/*Put the channel as first channel in the sequence of channels*/
						ADC_REG->JSQR=0;
						ADC_REG->JSQR |= Copy_ConvConfig->Channel<<JSQ4;
						/*choose the conversion trigger*/
						ADC_REG->CR[CR2] &= INJ_TRIGGER_MASK;
						switch(Copy_ConvConfig->TriggerType)
						{
						case ADC_SW_TRIGGER: SET_BIT(ADC_REG->CR[CR2],JSWSTART); break;
						case ADC_EXT_TRIGGER: ADC_REG->CR[CR2] |= (Copy_ConvConfig->Sense<<INJ_EXT_TRG_SENSE) | (Copy_ConvConfig->ExtTrigger<<INJ_EXT_TRG_SELECT); break;
						default: Local_ErrorState=E_WRONG_OPTION;
						}						
						/*the interrupt is enable */
						SET_BIT(ADC_REG->CR[CR1],JEOCIE); break;
						default: Local_ErrorState=E_WRONG_OPTION;
				}
			}
			else
			{
				Local_ErrorState=E_BUSY_FUNC;
			}
		}
	}
	return Local_ErrorState;
}

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
ErrorState_t Adc_StartChainConversionSynch(Adc_ChainConvConfig_t* Copy_ChainConfig, u16* Copy_Reading)
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_Reg=0;
	u8 Local_Shift=0;
	u8 Local_Counter=0;
	u16 Local_TimeEclapsed=0;
	if((Copy_ChainConfig == NULL) || (Copy_Reading == NULL))
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if(ADC_CH_NUM > ADC_3)
		{
			Local_ErrorState = E_WRONG_OPTION;
		}
		else
		{
			if(Adc_State[ADC_CH_NUM] == IDLE)
			{
				/*Make ADC Busy*/
				Adc_State[ADC_CH_NUM]=BUSY;
				/*put the sampling time for each channel*/
				for(Local_Counter=0;Local_Counter<CONV_NUM;Local_Counter++)
				{
					Local_Reg= 1-(Copy_ChainConfig->Channel[Local_Counter]/10);
					Local_Shift =3*(Copy_ChainConfig->Channel[Local_Counter]%10);
					ADC_CH_REG->SMPR[Local_Reg] &= SAMPLE_MASK<<Local_Shift;
					ADC_CH_REG->SMPR[Local_Reg] |= (Copy_ChainConfig->SampleTime[Local_Counter])<<Local_Shift;
				}
				/*Check for channel type*/
				switch(Copy_ChainConfig->ChannelType)
				{
				case ADC_REGULAR_CHANNEL:
					if(CONV_NUM > MAX_REG_CH)
					{
						Local_ErrorState=E_WRONG_OPTION;
					}
					else
					{
						/*put the sequence of channels*/
						ADC_CH_REG->SQR[SQR1]=0;
						ADC_CH_REG->SQR[SQR2]=0;
						ADC_CH_REG->SQR[SQR3]=0;
						ADC_CH_REG->SQR[SQR1]=(CONV_NUM-1)<<20;
						for(Local_Counter=0; Local_Counter<CONV_NUM; Local_Counter++)
						{
							Local_Reg=2-(Local_Counter/6);
							Local_Shift=4*(Local_Counter%6);
							ADC_CH_REG->SQR[Local_Reg] |= (Copy_ChainConfig->Channel[Local_Counter])<<Local_Shift;
						}
						switch(Copy_ChainConfig->ConvType)
						{
						case ADC_CONT: 		SET_BIT(ADC_CH_REG->CR[CR2],CONT); CLR_BIT(ADC_CH_REG->CR[CR1],SCAN); CLR_BIT(ADC_CH_REG->CR[CR1],DISCEN); break;
						case ADC_SCAN: 		SET_BIT(ADC_CH_REG->CR[CR1],SCAN); CLR_BIT(ADC_CH_REG->CR[CR2],CONT); CLR_BIT(ADC_CH_REG->CR[CR1],DISCEN); break;
						default: Local_ErrorState=E_WRONG_OPTION; break;
						}
						/*Make sure the interrupt is closed*/
						CLR_BIT(ADC_CH_REG->CR[CR1],EOCIE);
						/*make the EOC flag raise at the end of every conversion*/
						SET_BIT(ADC_CH_REG->CR[CR2],EOCS);
						/*fire the SW conversion*/
						SET_BIT(ADC_CH_REG->CR[CR2],SWSTART);
						for(Local_Counter=0; Local_Counter<CONV_NUM; Local_Counter++)
						{
							while((GET_BIT(ADC_CH_REG->SR,EOC_FLAG)==0) && (Local_TimeEclapsed< ADC_TIME_OUT))
							{
								Local_TimeEclapsed++;
							}
							if(Local_TimeEclapsed == ADC_TIME_OUT)
							{
								Local_ErrorState=E_TIME_OUT;
							}
							else
							{
								Copy_Reading[Local_Counter]=ADC_CH_REG->DR;
								Local_TimeEclapsed=0;
							}
						}
					}break;
				case ADC_INJECTED_CHANNEL:
					if(CONV_NUM > MAX_INJ_CH)
					{
						Local_ErrorState=E_WRONG_OPTION;
					}
					else
					{
						/*Put the sequence of channels*/
						ADC_CH_REG->JSQR=0;
						ADC_CH_REG->JSQR=(CONV_NUM-1)<<JL;
						for(Local_Counter=0; Local_Counter<CONV_NUM; Local_Counter++)
						{
							ADC_CH_REG->JSQR |= Copy_ChainConfig->Channel[Local_Counter] << INJ_SHIFT;
						}
						switch(Copy_ChainConfig->ConvType)
						{
						case ADC_SCAN: SET_BIT(ADC_CH_REG->CR[CR1],SCAN); CLR_BIT(ADC_CH_REG->CR[CR1],JDISCEN); break;
						default: Local_ErrorState=E_WRONG_OPTION;
						}
						/*make sure the interrupt id closed*/
						CLR_BIT(ADC_CH_REG->CR[CR1],JEOCIE);
						/*Fire the SW trigger to start conversion*/
						SET_BIT(ADC_CH_REG->CR[CR2],JSWSTART);
						while((GET_BIT(ADC_CH_REG->SR,JEOC_FLAG)==0) && (Local_TimeEclapsed< ADC_TIME_OUT))
						{
							Local_TimeEclapsed++;
						}
						if(Local_TimeEclapsed == ADC_TIME_OUT)
						{
							Local_ErrorState=E_TIME_OUT;
						}
						else
						{
							for(Local_Counter=0; Local_Counter<CONV_NUM; Local_Counter++)
							{
								Copy_Reading[Local_Counter]=ADC_CH_REG->JDR[Local_Counter];
							}
							/*clear JEOC flag*/
							CLR_BIT(ADC_CH_REG->SR,JEOC);
						}
					}break;
				default: Local_ErrorState=E_WRONG_OPTION;
				}
				Adc_State[ADC_CH_NUM]=IDLE;
			}
			else
			{
				Local_ErrorState=E_BUSY_FUNC;
			}
		}
	}
	return Local_ErrorState;
}

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
ErrorState_t Adc_StartChainConversionAsynch(Adc_ChainConvConfig_t* Copy_ChainConfig, u16* Copy_Reading, void(*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_Reg=0;
	u8 Local_Shift=0;
	u8 Local_Counter=0;
	if((Copy_ChainConfig == NULL) || (Copy_Reading == NULL))
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if(ADC_CH_NUM > ADC_3)
		{
			Local_ErrorState = E_WRONG_OPTION;
		}
		else
		{
			if(Adc_State[ADC_CH_NUM] == IDLE)
			{
				/*Make ADC Busy*/
				Adc_State[ADC_CH_NUM]=BUSY;
				/*put the sampling time for each channel*/
				for(Local_Counter=0;Local_Counter<CONV_NUM;Local_Counter++)
				{
					Local_Reg= 1-(Copy_ChainConfig->Channel[Local_Counter]/10);
					Local_Shift =3*(Copy_ChainConfig->Channel[Local_Counter]%10);
					ADC_CH_REG->SMPR[Local_Reg] &= SAMPLE_MASK<<Local_Shift;
					ADC_CH_REG->SMPR[Local_Reg] |= (Copy_ChainConfig->SampleTime[Local_Counter])<<Local_Shift;
				}
				/*Passing arguments to global variables*/
				Adc_ChType[ADC_CH_NUM]=Copy_ChainConfig->ChannelType;
				Adc_ConvNum[ADC_CH_NUM]=Copy_ChainConfig->ConversionsNumber;
				Adc_Result[ADC_CH_NUM]=Copy_Reading;
				Adc_CallBackFunc[ADC_CH_NUM]=Copy_NotificationFunc;
				Adc_ISRSrc[ADC_CH_NUM]=CHAIN_CONVERSION;
				/*Check for channel type*/
				switch(Copy_ChainConfig->ChannelType)
				{
				case ADC_REGULAR_CHANNEL:
					if(CONV_NUM > MAX_REG_CH)
					{
						Local_ErrorState=E_WRONG_OPTION;
					}
					else
					{
						/*put the sequence of channels*/
						ADC_CH_REG->SQR[SQR1]=0;
						ADC_CH_REG->SQR[SQR2]=0;
						ADC_CH_REG->SQR[SQR3]=0;
						ADC_CH_REG->SQR[SQR1]=(CONV_NUM-1)<<20;
						for(Local_Counter=0; Local_Counter<CONV_NUM; Local_Counter++)
						{
							Local_Reg=2-(Local_Counter/6);
							Local_Shift=4*(Local_Counter%6);
							ADC_CH_REG->SQR[Local_Reg] |= (Copy_ChainConfig->Channel[Local_Counter])<<Local_Shift;
						}
						switch(Copy_ChainConfig->ConvType)
						{
						case ADC_CONT: 		SET_BIT(ADC_CH_REG->CR[CR2],CONT); CLR_BIT(ADC_CH_REG->CR[CR1],SCAN); CLR_BIT(ADC_CH_REG->CR[CR1],DISCEN); break;
						case ADC_SCAN: 		SET_BIT(ADC_CH_REG->CR[CR1],SCAN); CLR_BIT(ADC_CH_REG->CR[CR2],CONT); CLR_BIT(ADC_CH_REG->CR[CR1],DISCEN); break;
						case ADC_DISCONT:	SET_BIT(ADC_CH_REG->CR[CR1],DISCEN); CLR_BIT(ADC_CH_REG->CR[CR2],CONT); CLR_BIT(ADC_CH_REG->CR[CR1],SCAN);
						if(CONV_NUM <= MAX_DISCEN)
						{
							ADC_CH_REG->CR[CR1] |= (CONV_NUM-1)<<DISCNUM;
						}
						else
						{
							ADC_CH_REG->CR[CR1] |= (MAX_DISCEN-1)<<DISCNUM;
						}break;
						default: Local_ErrorState=E_WRONG_OPTION; break;
						}
						/*make the EOC flag raise at the end of every conversion*/
						SET_BIT(ADC_CH_REG->CR[CR2],EOCS);
						/*Enable the interrupt*/
						SET_BIT(ADC_CH_REG->CR[CR1],EOCIE);
						/*choose the conversion trigger*/
						ADC_CH_REG->CR[CR2] &= TRIGGER_MASK;
						switch(Copy_ChainConfig->TriggerType)
						{
						case ADC_SW_TRIGGER: SET_BIT(ADC_CH_REG->CR[CR2],SWSTART); break;
						case ADC_EXT_TRIGGER: ADC_CH_REG->CR[CR2] |= Copy_ChainConfig->Sense<<EXT_TRG_SENSE | Copy_ChainConfig->ExtTrigger<<EXT_TRG_SELECT; break;
						default: Local_ErrorState=E_WRONG_OPTION; break;
						}
					}break;
				case ADC_INJECTED_CHANNEL:
					if(CONV_NUM > MAX_INJ_CH)
					{
						Local_ErrorState=E_WRONG_OPTION;
					}
					else
					{
						/*Put the sequence of channels*/
						ADC_CH_REG->JSQR=0;
						ADC_CH_REG->JSQR=(CONV_NUM-1)<<JL;
						for(Local_Counter=0; Local_Counter<CONV_NUM; Local_Counter++)
						{
							ADC_CH_REG->JSQR |= Copy_ChainConfig->Channel[Local_Counter] << INJ_SHIFT;
						}
						switch(Copy_ChainConfig->ConvType)
						{
						case ADC_SCAN: 		SET_BIT(ADC_CH_REG->CR[CR1],SCAN); CLR_BIT(ADC_CH_REG->CR[CR1],JDISCEN); break;
						case ADC_DISCONT:	SET_BIT(ADC_CH_REG->CR[CR1],JDISCEN); CLR_BIT(ADC_CH_REG->CR[CR1],SCAN); break;
						default: Local_ErrorState=E_WRONG_OPTION;
						}
						/*Enable the interrupt*/
						SET_BIT(ADC_CH_REG->CR[CR1],JEOCIE);
						/*choose the conversion trigger*/
						ADC_CH_REG->CR[CR2] &= INJ_TRIGGER_MASK;
						switch(Copy_ChainConfig->TriggerType)
						{
						case ADC_SW_TRIGGER: SET_BIT(ADC_CH_REG->CR[CR2],JSWSTART); break;
						case ADC_EXT_TRIGGER: ADC_CH_REG->CR[CR2] |= (Copy_ChainConfig->Sense<<INJ_EXT_TRG_SENSE) | (Copy_ChainConfig->ExtTrigger<<INJ_EXT_TRG_SELECT); break;
						default: Local_ErrorState=E_WRONG_OPTION;
						}
					}break;
				default: Local_ErrorState=E_WRONG_OPTION;
				}
			}
			else
			{
				Local_ErrorState=E_BUSY_FUNC;
			}
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : void ADC_IRQHandler(void)
 * \Description     : The IRQ of all ADCs
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value    : void
 *******************************************************************************/
void ADC_IRQHandler(void)
{
	u8 Local_Counter=0;
	u8 Local_Num=0;
	static u8 Local_Index[ADCS_NUM]={0};
	/*check Which ADC is the Source of interrupt*/
	for(Local_Counter=0;Local_Counter<ADCS_NUM;Local_Counter++)
	{
		if((GET_BIT(Adc_Arr[Local_Counter]->SR,EOC_FLAG)==1) || (GET_BIT(Adc_Arr[Local_Counter]->SR,JEOC_FLAG)==1))
		{
			/*check for the source of interrupt*/
			if(Adc_ISRSrc[Local_Counter]== SINGLE_CONVERSION)
			{
				/*know the type of channel to take the data*/
				switch(Adc_ChType[Local_Counter])
				{
				case ADC_REGULAR_CHANNEL:  *Adc_Result[Local_Counter]=Adc_Arr[Local_Counter]->DR; break;
				case ADC_INJECTED_CHANNEL: *Adc_Result[Local_Counter]=Adc_Arr[Local_Counter]->JDR[0]; CLR_BIT(Adc_Arr[Local_Counter]->SR,JEOC); break;
				}
				if(Adc_CallBackFunc[Local_Counter] != NULL)
				{
					Adc_CallBackFunc[Local_Counter]();
				}
				/*Make ADC idle*/
				Adc_State[Local_Counter]=IDLE;
			}
			else if(Adc_ISRSrc[Local_Counter]==CHAIN_CONVERSION)
			{
				/*know the type of channel to take the data*/
				switch(Adc_ChType[Local_Counter])
				{
				case ADC_REGULAR_CHANNEL:
					Adc_Result[Local_Counter][Local_Index[Local_Counter]]=Adc_Arr[Local_Counter]->DR;
					Local_Index[Local_Counter]++;
					if(Local_Index[Local_Counter] == Adc_ConvNum[Local_Counter])
					{
						/*Make ADC idle*/
						Adc_State[Local_Counter]=IDLE;
						Local_Index[Local_Counter]=0;
						if(Adc_CallBackFunc[Local_Counter] != NULL)
						{
							Adc_CallBackFunc[Local_Counter]();
						}
					}break;
				case ADC_INJECTED_CHANNEL:
					for(Local_Num=0; Local_Num<Adc_ConvNum[Local_Counter]; Local_Num++)
					{
						Adc_Result[Local_Counter][Local_Num]=Adc_Arr[Local_Counter]->JDR[Local_Num];
					}
					/*Make ADC idle*/
					Adc_State[Local_Counter]=IDLE;
					if(Adc_CallBackFunc[Local_Counter] != NULL)
					{
						Adc_CallBackFunc[Local_Counter]();
					}
					CLR_BIT(Adc_Arr[Local_Counter]->SR,JEOC); break;
				}
			}
		}
	}
}

/**********************************************************************************************************************
 *  END OF FILE: Adc_Program.c
 *********************************************************************************************************************/
