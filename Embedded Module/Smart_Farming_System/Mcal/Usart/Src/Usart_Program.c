/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Usart_Program.c
 *		  Layer:  Mcal
 *       Module:  Usart
 *		Version:  1.00
 *	
 *  Description:  the implementation of USART functions
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "Usart_Interface.h"
#include "Usart_Config.h"
#include "Usart_Private.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

static Usart_RegDef_t* Usart_Arr[USART_NUM]={USART1, USART2, USART3, UART4, UART5, USART6};

static Peripheral_State Usart_State[USART_NUM]={IDLE};

static void (*Usart_CallBackFunc[USART_NUM])(void)={NULL};

static u16 Usart_Data[USART_NUM]={0};

static char *Usart_pData[USART_NUM]={NULL};

static ISR_Src Usart_ISRSource[USART_NUM]={SEND_CHAR};

static u16 Usart_BufferSize=0;

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_Init(Usart_config_t* Copy_config)
 * \Description     : initialize USART
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_config     Structure of USART configuration
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_Init(Usart_config_t* Copy_config)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_config ==NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if(Copy_config->Num >= USART_NUM)
		{
			Local_ErrorState = E_WRONG_OPTION;
		}
		else
		{
			/*initialize all control registers with zero*/
			USART_CR1=0;
			USART_CR2=0;
			USART_CR3=0;
			/*Choose synchronization mode*/
			USART_CR2|= (Copy_config->Mode <<CLKEN);
			/*Choose Parity mode*/
			USART_CR1 |= (Copy_config->Parity<<PS);
			/*Choose Data length*/
			USART_CR1 |= (Copy_config->DataLength>>M);
			/*Enable Transmitter and receiver*/
			SET_BIT(USART_CR1,TE);
			SET_BIT(USART_CR1,RE);
			/*Choose number of Stop bits*/
			USART_CR2 |= (Copy_config->StopBitNo<<STOP);
			/*Choose Transfer mode*/
			USART_CR3 |= (Copy_config->DataTransMode << DMAT);
			/*Choose the baud rate*/
			USART_BRR = Usart_BRRRegisterValue(Copy_config->BuadRate);
			/*Enable USART*/
			SET_BIT(USART_CR1,UE);
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_SendCharSynch(Usart_Number_t Copy_UsartNum, u16 Copy_Data)
 * \Description     : Send a character through USART in Synchronous way
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to send char by
 * 					  Copy_Data		  Data to be sent by USART
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_SendCharSynch(Usart_Number_t Copy_UsartNum, u16 Copy_Data)
{
	ErrorState_t Local_ErrorState=E_OK;
	u32 Local_Counter=0;
	if(Copy_UsartNum >= USART_NUM)
	{
		Local_ErrorState = E_WRONG_OPTION;
	}
	else
	{
		/*Check if USART Idle or not*/
		if(Usart_State[Copy_UsartNum] == IDLE)
		{
			/*Make the peripheral Busy*/
			Usart_State[Copy_UsartNum] = BUSY;
			/*Busy waiting for Data register empty*/
			while((GET_BIT(USART_SR,TXE)==0) && (Local_Counter < USART_TIME_OUT))
			{
				Local_Counter++;
			}
			if(Local_Counter==USART_TIME_OUT)
			{
				Local_ErrorState=E_TIME_OUT;
			}
			else
			{
				/*Clear the transmit complete flag*/
				CLR_BIT(USART_SR,TC);
				/*send data*/
				USART_DR=Copy_Data;
				/*Make USART IDLE*/
				Usart_State[Copy_UsartNum] = IDLE;
			}
		}
		else
		{
			Local_ErrorState=E_BUSY_FUNC;
		}
	}
	return Local_ErrorState;	
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_SendCharASynch(Usart_Number_t Copy_UsartNum, u16 Copy_Data , void (*Copy_NotificationFunc)(void))
 * \Description     : Send a character through USART in Asynchronous way
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to send char by
 * 					  Copy_Data		  Data to be sent by USART
 * 					  (*Copy_NotificationFunc)(void) Pointer to Function hold the notification of transmission
 * \Parameters (out): None
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_SendCharASynch(Usart_Number_t Copy_UsartNum, u16 Copy_Data , void (*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_UsartNum >= USART_NUM)
	{
		Local_ErrorState = E_WRONG_OPTION;
	}
	else
	{
		/*Check if USART Idle or not*/
		if(Usart_State[Copy_UsartNum] == IDLE)
		{
			if(Copy_NotificationFunc == NULL)
			{
				Local_ErrorState=E_NULL_POINTER;
			}
			else
			{
				/*Make the peripheral busy*/
				Usart_State[Copy_UsartNum] = BUSY;
				/*Make ISR source Send Char*/
				Usart_ISRSource[Copy_UsartNum]=SEND_CHAR;
				/*Pass the Data and call Back Function to Global Variables*/
				Usart_CallBackFunc[Copy_UsartNum]=Copy_NotificationFunc;
				Usart_Data[Copy_UsartNum]=Copy_Data;
				/*USART Data Empty Interrupt Enable*/
				SET_BIT(Usart_Arr[Copy_UsartNum]->CR1,TXEIE);
			}
		}
		else
		{
			Local_ErrorState=E_BUSY_FUNC;
		}
	}
	return Local_ErrorState;	
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_SendStringSynch(Usart_Number_t Copy_UsartNum, char* Copy_String)
 * \Description     : Send a String through USART in Synchronous way
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to send char by
 * 					  Copy_String	  String to be sent by USART
 * \Parameters (out): None
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_SendStringSynch(Usart_Number_t Copy_UsartNum, char* Copy_String)
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_Index=0;
	if(Copy_String == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if(Copy_UsartNum >= USART_NUM)
		{
			Local_ErrorState = E_WRONG_OPTION;
		}
		else
		{
			/*Send the string to its end*/
			while(Copy_String[Local_Index] != '\0')
			{
				Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, Copy_String[Local_Index]);
				Local_Index++;
			}
		}
	}
	return Local_ErrorState;	
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_SendStringASynch(Usart_Number_t Copy_UsartNum, char* Copy_String, void (*Copy_NotificationFunc)(void))
 * \Description     : Send a String through USART in ASynchronous way
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to send char by
 * 					  Copy_String	  String to be sent by USART
 * 					  (*Copy_NotificationFunc)(void) Pointer to Function hold the notification of transmission
 * \Parameters (out): None
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_SendStringASynch(Usart_Number_t Copy_UsartNum, char* Copy_String, void (*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_UsartNum >= USART_NUM)
	{
		Local_ErrorState = E_WRONG_OPTION;
	}
	else
	{
		/*Check if USART Idle or not*/
		if(Usart_State[Copy_UsartNum] == IDLE)
		{
			if((Copy_NotificationFunc == NULL) || (Copy_String == NULL))
			{
				Local_ErrorState=E_NULL_POINTER;
			}
			else
			{
				/*Make the peripheral busy*/
				Usart_State[Copy_UsartNum] = BUSY;
				/*Make the ISR source send string*/
				Usart_ISRSource[Copy_UsartNum]=SEND_STRING;
				/*Pass the Data and call Back Function to Global Variables*/
				Usart_CallBackFunc[Copy_UsartNum]=Copy_NotificationFunc;
				Usart_pData[Copy_UsartNum]=Copy_String;
				/*USART Data Empty Interrupt Enable*/
				SET_BIT(Usart_Arr[Copy_UsartNum]->CR1,TXEIE);
			}
		}
		else
		{
			Local_ErrorState=E_BUSY_FUNC;
		}
	}
	return Local_ErrorState;	
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_SendBufferSynch(Usart_Number_t Copy_UsartNum, u16* Copy_Buffer, u16 Copy_BufferSize)
 * \Description     : Send a Buffer through USART in Synchronous way
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to Send Buffer by
 * 					  Copy_BufferSize The size of received Buffer
 * 					  Copy_Buffer	  Buffer to be Sent by USART
 * \Parameters (out): None
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_SendBufferSynch(Usart_Number_t Copy_UsartNum, u8* Copy_Buffer, u16 Copy_BufferLen)
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_Index=0;
	if(Copy_Buffer == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if(Copy_UsartNum >= USART_NUM)
		{
			Local_ErrorState = E_WRONG_OPTION;
		}
		else
		{
			/*Send the Buffer to its end*/
			for(Local_Index=0; Local_Index<Copy_BufferLen; Local_Index++)
			{
				Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, Copy_Buffer[Local_Index]);

			}
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_SendBufferASynch(Usart_Number_t Copy_UsartNum, u16* Copy_Buffer, u16 Copy_BufferSize, void (*Copy_NotificationFunc)(void))
 * \Description     : Send a Buffer through USART in ASynchronous way
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to Send Buffer by
 * 					  Copy_BufferSize The size of received Buffer
 * 					  (*Copy_NotificationFunc)(void) Pointer to Function hold the notification of Send
 * 					  Copy_Buffer	  Buffer to be Sent by USART
 * \Parameters (out): None
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_SendBufferASynch(Usart_Number_t Copy_UsartNum, char* Copy_Buffer, u16 Copy_BufferLen, void (*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_UsartNum >= USART_NUM)
	{
		Local_ErrorState = E_WRONG_OPTION;
	}
	else
	{
		/*Check if USART Idle or not*/
		if(Usart_State[Copy_UsartNum] == IDLE)
		{
			if((Copy_NotificationFunc == NULL) || (Copy_Buffer == NULL))
			{
				Local_ErrorState=E_NULL_POINTER;
			}
			else
			{
				/*Make the peripheral busy*/
				Usart_State[Copy_UsartNum] = BUSY;
				/*Make the ISR source send Buffer*/
				Usart_ISRSource[Copy_UsartNum]=SEND_BUFFER;
				/*Take the Buffer size*/
				Usart_BufferSize=Copy_BufferLen;
				/*Pass the Data and call Back Function to Global Variables*/
				Usart_CallBackFunc[Copy_UsartNum]=Copy_NotificationFunc;
				Usart_pData[Copy_UsartNum]=Copy_Buffer;
				/*USART Data Empty Interrupt Enable*/
				SET_BIT(Usart_Arr[Copy_UsartNum]->CR1,TXEIE);
			}
		}
		else
		{
			Local_ErrorState=E_BUSY_FUNC;
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_ReceiveCharSynch(Usart_Number_t Copy_UsartNum, u16* Copy_Data)
 * \Description     : Receive a character through USART in Synchronous way
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to Receive char by
 * \Parameters (out): Copy_Data		  Data to be Received by USART
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_ReceiveCharSynch(Usart_Number_t Copy_UsartNum, u8* Copy_Data)
{
	u32 Local_Counter=0;
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_UsartNum >= USART_NUM)
	{
		Local_ErrorState = E_WRONG_OPTION;
	}
	else
	{
		/*Check if USART Idle or not*/
		if(Usart_State[Copy_UsartNum] == IDLE)
		{
			if(Copy_Data == NULL)
			{
				Local_ErrorState=E_NULL_POINTER;
			}
			else
			{
				/*Make the peripheral Busy*/
				Usart_State[Copy_UsartNum] = BUSY;
				/*Busy waiting for Read Data register Not empty*/
				while((GET_BIT(USART_SR,RXNE)==0) && (Local_Counter<USART_TIME_OUT))
				{
					Local_Counter++;
				}
				if(Local_Counter==USART_TIME_OUT)
				{
					Local_ErrorState=E_TIME_OUT;
					/*Make USART IDLE*/
					Usart_State[Copy_UsartNum] = IDLE;
				}
				else
				{
					/*Clear Read Data register Not empty flag*/
					CLR_BIT(USART_SR,RXNE);
					/*Receive data*/
					*Copy_Data=USART_DR;
					/*Make USART IDLE*/
					Usart_State[Copy_UsartNum] = IDLE;
				}
			}
		}
		else
		{
			Local_ErrorState=E_BUSY_FUNC;
		}
	}
	return Local_ErrorState;	
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_ReceiveCharASynch(Usart_Number_t Copy_UsartNum, u16* Copy_Data)
 * \Description     : Receive a character through USART in ASynchronous way
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to Receive char by
 * 					  (*Copy_NotificationFunc)(void) Pointer to Function hold the notification of Reception
 * \Parameters (out): Copy_Data		  Data to be Received by USART
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_ReceiveCharASynch(Usart_Number_t Copy_UsartNum, u16* Copy_Data, void (*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_UsartNum >= USART_NUM)
	{
		Local_ErrorState = E_WRONG_OPTION;
	}
	else
	{
		/*Check if USART Idle or not*/
		if(Usart_State[Copy_UsartNum] == IDLE)
		{
			if((Copy_Data == NULL) || (Copy_NotificationFunc == NULL))
			{
				Local_ErrorState=E_NULL_POINTER;
			}
			else
			{
				/*Make the peripheral Busy*/
				Usart_State[Copy_UsartNum] = BUSY;
				/*Make the ISR source Receive*/
				Usart_ISRSource[Copy_UsartNum]=RECEIVE_CHAR;
				/*Pass the Data and call Back Function to Global Variables*/
				Usart_CallBackFunc[Copy_UsartNum]=Copy_NotificationFunc;
				Usart_pData[Copy_UsartNum]=(char*)Copy_Data;
				/*USART RXNE interrupt Enable*/
				SET_BIT(Usart_Arr[Copy_UsartNum]->CR1,RXNEIE);
			}
		}
		else
		{
			Local_ErrorState=E_BUSY_FUNC;
		}
	}
	return Local_ErrorState;	
}

/******************************************************************************
 * \Syntax          : ErrorState_t Usart_ReceiveBufferSynch(Usart_Number_t Copy_UsartNum, u16* Copy_Buffer, u16 Copy_BufferSize)
 * \Description     : Receive a Buffer through USART in Synchronous way
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to Receive Buffer by
 * 					  Copy_BufferSize The size of received Buffer
 * \Parameters (out): Copy_Buffer	  Buffer to be Received by USART
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_ReceiveBufferSynch(Usart_Number_t Copy_UsartNum, u8* Copy_Buffer, u16 Copy_BufferSize)
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_Index=0;
	if(Copy_UsartNum >= USART_NUM)
	{
		Local_ErrorState = E_WRONG_OPTION;
	}
	else
	{
		if(Copy_Buffer == NULL)
		{
			Local_ErrorState=E_NULL_POINTER;
		}
		else
		{
			/*Check if USART Idle or not*/
			if(Usart_State[Copy_UsartNum] == IDLE)
			{
				for(Local_Index=0 ; Local_Index < Copy_BufferSize ; Local_Index++)
				{
					Local_ErrorState=Usart_ReceiveCharSynch(Copy_UsartNum, &Copy_Buffer[Local_Index]);
				}
				Copy_Buffer[Copy_BufferSize]='\0';
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
 * \Syntax          : ErrorState_t Usart_ReceiveBufferASynch(Usart_Number_t Copy_UsartNum, u16* Copy_Buffer, u16 Copy_BufferSize, void (*Copy_NotificationFunc)(void))
 * \Description     : Receive a Buffer through USART in ASynchronous way
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   USART Number you want to Receive Buffer by
 * 					  Copy_BufferSize The size of received Buffer
 * 					  (*Copy_NotificationFunc)(void) Pointer to Function hold the notification of Reception
 * \Parameters (out): Copy_Buffer	  Buffer to be Received by USART
 * \Return value    : ErrorState_t
 *******************************************************************************/
ErrorState_t Usart_ReceiveBufferASynch(Usart_Number_t Copy_UsartNum, u8* Copy_Buffer, u16 Copy_BufferSize, void (*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_UsartNum >= USART_NUM)
	{
		Local_ErrorState = E_WRONG_OPTION;
	}
	else
	{
		/*Check if USART Idle or not*/
		if(Usart_State[Copy_UsartNum] == IDLE)
		{
			if((Copy_Buffer == NULL) || (Copy_NotificationFunc == NULL))
			{
				Local_ErrorState=E_NULL_POINTER;
			}
			else
			{
				/*Make the peripheral Busy*/
				Usart_State[Copy_UsartNum] = BUSY;
				/*Make the ISR source Receive*/
				Usart_ISRSource[Copy_UsartNum]=RECEIVE_BUFFER;
				/*Pass the Data and call Back Function to Global Variables*/
				Usart_CallBackFunc[Copy_UsartNum]=Copy_NotificationFunc;
				Usart_pData[Copy_UsartNum]=(char*)Copy_Buffer;
				Usart_BufferSize=Copy_BufferSize;
				/*USART RXNE interrupt Enable*/
				SET_BIT(Usart_Arr[Copy_UsartNum]->CR1,RXNEIE);
			}
		}
		else
		{
			Local_ErrorState=E_BUSY_FUNC;
		}
	}
	return Local_ErrorState;	
}

/******************************************************************************
 * \Syntax          : u16 Usart_BRRRegisterValue(u32 Copy_BaudRate)
 * \Description     : Function Used to calculate the BRR Register value (Fraction and mantissa)
 *					  through the desired Baud rate
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : Copy_BaudRate   the desired baud rate
 * \Parameters (out): None
 * \Return value:   : u16 	The BRR Register Value
 *******************************************************************************/
u16 Usart_BRRRegisterValue(u32 Copy_BaudRate)
{
	u32 Local_UsartDiv= (CLK_FRequancy*25)/(4*Copy_BaudRate);
	u16 Local_Mantissa= (Local_UsartDiv/100)<<4;
	u16 Local_Fraction= (Local_UsartDiv%100)*16;
	u8 Local_FrctnReminder= Local_Fraction%100;
	Local_Fraction/=100;
	if(Local_FrctnReminder >=50)
	{
		Local_Fraction++;
	}
	return (Local_Fraction+Local_Mantissa);
}

/******************************************************************************
 * \Syntax          : void USART1_IRQHandler(void)
 * \Description     : The IRQ Handler of Usart1
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void USART1_IRQHandler(void)
{
	static u16 Local_Index=0;
	if(Usart_ISRSource[USART_1] == SEND_CHAR)
	{
		/*Send Data*/
		Usart_Arr[USART_1]->DR=Usart_Data[USART_1];
		/*Make Peripheral idle*/
		Usart_State[USART_1]=IDLE;
		/*Disable USART Data Empty interrupt*/
		CLR_BIT(Usart_Arr[USART_1]->CR1,TXEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[USART_1] != NULL)
		{
			Usart_CallBackFunc[USART_1]();
		}
	}
	else if(Usart_ISRSource[USART_1] == SEND_STRING)
	{
		/*Send Data*/
		Usart_Arr[USART_1]->DR=Usart_pData[USART_1][Local_Index];
		Local_Index++;
		if(Usart_pData[USART_1][Local_Index] == '\0')
		{
			/*Make Peripheral idle*/
			Usart_State[USART_1]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[USART_1]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_1] != NULL)
			{
				Usart_CallBackFunc[USART_1]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[USART_1] == SEND_BUFFER)
	{
		/*Send Data*/
		Usart_Arr[USART_1]->DR=Usart_pData[USART_1][Local_Index];
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			/*Make Peripheral idle*/
			Usart_State[USART_1]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[USART_1]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_1] != NULL)
			{
				Usart_CallBackFunc[USART_1]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[USART_1] == RECEIVE_CHAR)
	{
		/*Receive Data*/
		*Usart_pData[USART_1] = Usart_Arr[USART_1]->DR;
		/*Make Peripheral idle*/
		Usart_State[USART_1]=IDLE;
		/*USART RXNE interrupt Disable*/
		SET_BIT(Usart_Arr[USART_1]->CR1,RXNEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[USART_1] != NULL)
		{
			Usart_CallBackFunc[USART_1]();
		}
	}
	else if(Usart_ISRSource[USART_1] == RECEIVE_BUFFER)
	{
		/*Receive Data*/
		Usart_pData[USART_1][Local_Index] = Usart_Arr[USART_1]->DR;
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			Usart_pData[USART_1][Usart_BufferSize] ='\0';
			/*Make Peripheral idle*/
			Usart_State[USART_1]=IDLE;
			/*USART RXNE interrupt Disable*/
			SET_BIT(Usart_Arr[USART_1]->CR1,RXNEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_1] != NULL)
			{
				Usart_CallBackFunc[USART_1]();
			}
			Local_Index=0;
		}
	}
}

/******************************************************************************
 * \Syntax          : void USART2_IRQHandler(void)
 * \Description     : The IRQ Handler of Usart2
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void USART2_IRQHandler(void)
{
	static u16 Local_Index=0;
	if(Usart_ISRSource[USART_2] == SEND_CHAR)
	{
		/*Send Data*/
		Usart_Arr[USART_2]->DR=Usart_Data[USART_2];
		/*Make Peripheral idle*/
		Usart_State[USART_2]=IDLE;
		/*Disable USART Data Empty interrupt*/
		CLR_BIT(Usart_Arr[USART_2]->CR1,TXEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[USART_2] != NULL)
		{
			Usart_CallBackFunc[USART_2]();
		}
	}
	else if(Usart_ISRSource[USART_2] == SEND_STRING)
	{
		/*Send Data*/
		Usart_Arr[USART_2]->DR=Usart_pData[USART_2][Local_Index];
		Local_Index++;
		if(Usart_pData[USART_2][Local_Index] == '\0')
		{
			/*Make Peripheral idle*/
			Usart_State[USART_2]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[USART_2]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_2] != NULL)
			{
				Usart_CallBackFunc[USART_2]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[USART_2] == SEND_BUFFER)
	{
		/*Send Data*/
		Usart_Arr[USART_2]->DR=Usart_pData[USART_2][Local_Index];
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			/*Make Peripheral idle*/
			Usart_State[USART_2]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[USART_2]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_2] != NULL)
			{
				Usart_CallBackFunc[USART_2]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[USART_2] == RECEIVE_CHAR)
	{
		/*Receive Data*/
		*Usart_pData[USART_2] = Usart_Arr[USART_2]->DR;
		/*Make Peripheral idle*/
		Usart_State[USART_2]=IDLE;
		/*USART RXNE interrupt Disable*/
		SET_BIT(Usart_Arr[USART_2]->CR1,RXNEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[USART_2] != NULL)
		{
			Usart_CallBackFunc[USART_2]();
		}
	}
	else if(Usart_ISRSource[USART_2] == RECEIVE_BUFFER)
	{
		/*Receive Data*/
		Usart_pData[USART_2][Local_Index] = Usart_Arr[USART_2]->DR;
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			Usart_pData[USART_2][Usart_BufferSize] ='\0';
			/*Make Peripheral idle*/
			Usart_State[USART_2]=IDLE;
			/*USART RXNE interrupt Disable*/
			SET_BIT(Usart_Arr[USART_2]->CR1,RXNEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_2] != NULL)
			{
				Usart_CallBackFunc[USART_2]();
			}
			Local_Index=0;
		}
	}
}

/******************************************************************************
 * \Syntax          : void USART3_IRQHandler(void)
 * \Description     : The IRQ Handler of Usart3
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void USART3_IRQHandler(void)
{
	static u16 Local_Index=0;
	if(Usart_ISRSource[USART_3] == SEND_CHAR)
	{
		/*Send Data*/
		Usart_Arr[USART_3]->DR=Usart_Data[USART_3];
		/*Make Peripheral idle*/
		Usart_State[USART_3]=IDLE;
		/*Disable USART Data Empty interrupt*/
		CLR_BIT(Usart_Arr[USART_3]->CR1,TXEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[USART_3] != NULL)
		{
			Usart_CallBackFunc[USART_3]();
		}
	}
	else if(Usart_ISRSource[USART_3] == SEND_STRING)
	{
		/*Send Data*/
		Usart_Arr[USART_3]->DR=Usart_pData[USART_3][Local_Index];
		Local_Index++;
		if(Usart_pData[USART_3][Local_Index] == '\0')
		{
			/*Make Peripheral idle*/
			Usart_State[USART_3]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[USART_3]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_3] != NULL)
			{
				Usart_CallBackFunc[USART_3]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[USART_3] == SEND_BUFFER)
	{
		/*Send Data*/
		Usart_Arr[USART_3]->DR=Usart_pData[USART_3][Local_Index];
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			/*Make Peripheral idle*/
			Usart_State[USART_3]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[USART_3]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_3] != NULL)
			{
				Usart_CallBackFunc[USART_3]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[USART_3] == RECEIVE_CHAR)
	{
		/*Receive Data*/
		*Usart_pData[USART_3] = Usart_Arr[USART_3]->DR;
		/*Make Peripheral idle*/
		Usart_State[USART_3]=IDLE;
		/*USART RXNE interrupt Disable*/
		SET_BIT(Usart_Arr[USART_3]->CR1,RXNEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[USART_3] != NULL)
		{
			Usart_CallBackFunc[USART_3]();
		}
	}
	else if(Usart_ISRSource[USART_3] == RECEIVE_BUFFER)
	{
		/*Receive Data*/
		Usart_pData[USART_3][Local_Index] = Usart_Arr[USART_3]->DR;
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			Usart_pData[USART_3][Usart_BufferSize] ='\0';
			/*Make Peripheral idle*/
			Usart_State[USART_3]=IDLE;
			/*USART RXNE interrupt Disable*/
			SET_BIT(Usart_Arr[USART_3]->CR1,RXNEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_3] != NULL)
			{
				Usart_CallBackFunc[USART_3]();
			}
			Local_Index=0;
		}
	}
}

/******************************************************************************
 * \Syntax          : void UART4_IRQHandler(void)
 * \Description     : The IRQ Handler of Uart4
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void UART4_IRQHandler(void)
{
	static u16 Local_Index=0;
	if(Usart_ISRSource[UART_4] == SEND_CHAR)
	{
		/*Send Data*/
		Usart_Arr[UART_4]->DR=Usart_Data[UART_4];
		/*Make Peripheral idle*/
		Usart_State[UART_4]=IDLE;
		/*Disable USART Data Empty interrupt*/
		CLR_BIT(Usart_Arr[UART_4]->CR1,TXEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[UART_4] != NULL)
		{
			Usart_CallBackFunc[UART_4]();
		}
	}
	else if(Usart_ISRSource[UART_4] == SEND_STRING)
	{
		/*Send Data*/
		Usart_Arr[UART_4]->DR=Usart_pData[UART_4][Local_Index];
		Local_Index++;
		if(Usart_pData[UART_4][Local_Index] == '\0')
		{
			/*Make Peripheral idle*/
			Usart_State[UART_4]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[UART_4]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[UART_4] != NULL)
			{
				Usart_CallBackFunc[UART_4]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[UART_4] == SEND_BUFFER)
	{
		/*Send Data*/
		Usart_Arr[UART_4]->DR=Usart_pData[UART_4][Local_Index];
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			/*Make Peripheral idle*/
			Usart_State[UART_4]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[UART_4]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[UART_4] != NULL)
			{
				Usart_CallBackFunc[UART_4]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[UART_4] == RECEIVE_CHAR)
	{
		/*Receive Data*/
		*Usart_pData[UART_4] = Usart_Arr[UART_4]->DR;
		/*Make Peripheral idle*/
		Usart_State[UART_4]=IDLE;
		/*USART RXNE interrupt Disable*/
		SET_BIT(Usart_Arr[UART_4]->CR1,RXNEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[UART_4] != NULL)
		{
			Usart_CallBackFunc[UART_4]();
		}
	}
	else if(Usart_ISRSource[UART_4] == RECEIVE_BUFFER)
	{
		/*Receive Data*/
		Usart_pData[UART_4][Local_Index] = Usart_Arr[UART_4]->DR;
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			Usart_pData[UART_4][Usart_BufferSize] ='\0';
			/*Make Peripheral idle*/
			Usart_State[UART_4]=IDLE;
			/*USART RXNE interrupt Disable*/
			SET_BIT(Usart_Arr[UART_4]->CR1,RXNEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[UART_4] != NULL)
			{
				Usart_CallBackFunc[UART_4]();
			}
			Local_Index=0;
		}
	}
}

/******************************************************************************
 * \Syntax          : void UART5_IRQHandler(void)
 * \Description     : The IRQ Handler of Uart5
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void UART5_IRQHandler(void)
{
	static u16 Local_Index=0;
	if(Usart_ISRSource[UART_5] == SEND_CHAR)
	{
		/*Send Data*/
		Usart_Arr[UART_5]->DR=Usart_Data[UART_5];
		/*Make Peripheral idle*/
		Usart_State[UART_5]=IDLE;
		/*Disable USART Data Empty interrupt*/
		CLR_BIT(Usart_Arr[UART_5]->CR1,TXEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[UART_5] != NULL)
		{
			Usart_CallBackFunc[UART_5]();
		}
	}
	else if(Usart_ISRSource[UART_5] == SEND_STRING)
	{
		/*Send Data*/
		Usart_Arr[UART_5]->DR=Usart_pData[UART_5][Local_Index];
		Local_Index++;
		if(Usart_pData[UART_5][Local_Index] == '\0')
		{
			/*Make Peripheral idle*/
			Usart_State[UART_5]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[UART_5]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[UART_5] != NULL)
			{
				Usart_CallBackFunc[UART_5]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[UART_5] == SEND_BUFFER)
	{
		/*Send Data*/
		Usart_Arr[UART_5]->DR=Usart_pData[UART_5][Local_Index];
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			/*Make Peripheral idle*/
			Usart_State[UART_5]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[UART_5]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[UART_5] != NULL)
			{
				Usart_CallBackFunc[UART_5]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[UART_5] == RECEIVE_CHAR)
	{
		/*Receive Data*/
		*Usart_pData[UART_5] = Usart_Arr[UART_5]->DR;
		/*Make Peripheral idle*/
		Usart_State[UART_5]=IDLE;
		/*USART RXNE interrupt Disable*/
		SET_BIT(Usart_Arr[UART_5]->CR1,RXNEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[UART_5] != NULL)
		{
			Usart_CallBackFunc[UART_5]();
		}
	}
	else if(Usart_ISRSource[UART_5] == RECEIVE_BUFFER)
	{
		/*Receive Data*/
		Usart_pData[UART_5][Local_Index] = Usart_Arr[UART_5]->DR;
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			Usart_pData[UART_5][Usart_BufferSize] ='\0';
			/*Make Peripheral idle*/
			Usart_State[UART_5]=IDLE;
			/*USART RXNE interrupt Disable*/
			SET_BIT(Usart_Arr[UART_5]->CR1,RXNEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[UART_5] != NULL)
			{
				Usart_CallBackFunc[UART_5]();
			}
			Local_Index=0;
		}
	}
}

/******************************************************************************
 * \Syntax          : void USART6_IRQHandler(void)
 * \Description     : The IRQ Handler of Usart6
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void USART6_IRQHandler(void)
{
	static u16 Local_Index=0;
	if(Usart_ISRSource[USART_6] == SEND_CHAR)
	{
		/*Send Data*/
		Usart_Arr[USART_6]->DR=Usart_Data[USART_6];
		/*Make Peripheral idle*/
		Usart_State[USART_6]=IDLE;
		/*Disable USART Data Empty interrupt*/
		CLR_BIT(Usart_Arr[USART_6]->CR1,TXEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[USART_6] != NULL)
		{
			Usart_CallBackFunc[USART_6]();
		}
	}
	else if(Usart_ISRSource[USART_6] == SEND_STRING)
	{
		/*Send Data*/
		Usart_Arr[USART_6]->DR=Usart_pData[USART_6][Local_Index];
		Local_Index++;
		if(Usart_pData[USART_6][Local_Index] == '\0')
		{
			/*Make Peripheral idle*/
			Usart_State[USART_6]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[USART_6]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_6] != NULL)
			{
				Usart_CallBackFunc[USART_6]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[USART_6] == SEND_BUFFER)
	{
		/*Send Data*/
		Usart_Arr[USART_6]->DR=Usart_pData[USART_6][Local_Index];
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			/*Make Peripheral idle*/
			Usart_State[USART_6]=IDLE;
			/*Disable USART Data Empty interrupt*/
			CLR_BIT(Usart_Arr[USART_6]->CR1,TXEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_6] != NULL)
			{
				Usart_CallBackFunc[USART_6]();
			}
			Local_Index=0;
		}
	}
	else if(Usart_ISRSource[USART_6] == RECEIVE_CHAR)
	{
		/*Receive Data*/
		*Usart_pData[USART_6] = Usart_Arr[USART_6]->DR;
		/*Make Peripheral idle*/
		Usart_State[USART_6]=IDLE;
		/*USART RXNE interrupt Disable*/
		SET_BIT(Usart_Arr[USART_6]->CR1,RXNEIE);
		/*Invoke the call back function*/
		if(Usart_CallBackFunc[USART_6] != NULL)
		{
			Usart_CallBackFunc[USART_6]();
		}
	}
	else if(Usart_ISRSource[USART_6] == RECEIVE_BUFFER)
	{
		/*Receive Data*/
		Usart_pData[USART_6][Local_Index] = Usart_Arr[USART_6]->DR;
		Local_Index++;
		if(Local_Index==Usart_BufferSize)
		{
			Usart_pData[USART_6][Usart_BufferSize] ='\0';
			/*Make Peripheral idle*/
			Usart_State[USART_6]=IDLE;
			/*USART RXNE interrupt Disable*/
			SET_BIT(Usart_Arr[USART_6]->CR1,RXNEIE);
			/*Invoke the call back function*/
			if(Usart_CallBackFunc[USART_6] != NULL)
			{
				Usart_CallBackFunc[USART_6]();
			}
			Local_Index=0;
		}
	}
}

/**********************************************************************************************************************
 *  END OF FILE: Usart_Program.c
 *********************************************************************************************************************/
