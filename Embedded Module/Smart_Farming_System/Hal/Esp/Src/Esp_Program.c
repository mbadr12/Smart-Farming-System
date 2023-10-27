/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Esp_Program.c
 *		  Layer:  Hal
 *       Module:  Esp
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Bit_Math.h"

#include "Usart_Interface.h"
#include "Esp_Interface.h"
#include "Esp_Private.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 Esp_Response[MAX_RESPONSE]={0};

u8 Esp_NumStr[10]={0};

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : static bool Esp_ValidateCmd(u8* Copy_Response, char* Copy_Correct)
 * \Description     : Validate the response of Esp to sent commands
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Response   The response of ESP
 * 					  Copy_Correct	   The correct response wanted
 * \Parameters (out): None
 * \Return value:   : bool	TRUE
 * 							FALSE
 *******************************************************************************/
static bool Esp_ValidateCmd(u8* Copy_Response, char* Copy_Correct)
{
	bool Local_Result=TRUE;
	u8 Local_Index=0;
	u8 Local_ResponseLen=0;
	while(Copy_Correct[Local_Index] != '\0')
	{
		Local_ResponseLen++;
		Local_Index++;
	}
	for(Local_Index=0; Local_Index<Local_ResponseLen ; Local_Index++)
	{
		if(Copy_Response[Local_Index] != Copy_Correct[Local_Index])
		{
			break;
		}
	}
	if(Local_Index < Local_ResponseLen)
	{
		Local_Result=FALSE;
	}
	return Local_Result;
}

/******************************************************************************
 * \Syntax          : static void Esp_ConvertNumToStr(u16 Copy_Number, char* Copy_String)
 * \Description     : Convert number to string to send in UTF-8 format
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Number   Number to be converted
 * \Parameters (out): Copy_String	Converted number as string
 * \Return value:   : void
 *******************************************************************************/
static void Esp_ConvertNumToStr(u16 Copy_Number, char* Copy_String)
{
	u8 Local_Length = 0;
	u8 Local_Counter=0;
	u16 Local_Rest=Copy_Number;
	while(Local_Rest !=0)
	{
		Local_Length++;
		Local_Rest/=10;
	}
	for(Local_Counter=0;Local_Counter<Local_Length;Local_Counter++)
	{
		Local_Rest=Copy_Number%10;
		Copy_Number/=10;
		Copy_String[Local_Length-Local_Counter-1]=Local_Rest+'0';
	}
	Copy_String[Local_Length]='\0';
}

/******************************************************************************
 * \Syntax          : static void Esp_Delay(u32 Copy_Delay)
 * \Description     : generate delay
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Delay   	Number to clock cycle wanted multiplied by 4
 * \Parameters (out): Copy_String	Converted number as string
 * \Return value:   : void
 *******************************************************************************/
static void Esp_Delay(u32 Copy_Delay)
{
	u32 Local_Counter=0;
	for(Local_Counter=0; Local_Counter<Copy_Delay; Local_Counter++)
	{
		__asm volatile("NOP");
	}
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t Esp_Init(Esp_UsartNum Copy_UsartNum)
 * \Description     : Initialize the ESP module
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART the ESP connected to
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Esp_Init(Esp_UsartNum Copy_UsartNum)
{
	bool Local_Reply=TRUE;
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_Counter=0;
	Usart_config_t Esp_Usart={Copy_UsartNum,USART_ASYNCH,115200,USART_EIGHT_BIT,USART_PARITY_DISABLED,USART_ONE_STOP_BIT,USART_UC_TRANCEIVER};
	Local_ErrorState=Usart_Init(&Esp_Usart);
	if(Local_ErrorState == E_OK)
	{
		/*Close the Echo*/
		Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "ATE0\r\n");
		Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, 11);
		/*Test the response of chip*/
		do
		{
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "AT\r\n");
			Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, 7);
			Local_Reply=Esp_ValidateCmd(Esp_Response, ESP_REPLY);
			Local_Counter++;
		}while((Local_Reply == FALSE) && (Local_Counter < ESP_TIMEOUT));
		if(Local_Counter != ESP_TIMEOUT)
		{
			/*Choose the mode as station*/
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "AT+CWMODE=1\r\n");
			/*check for the configuration is done*/
			Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, ESP_REPLY_LEN);
			Local_Reply=Esp_ValidateCmd(Esp_Response, ESP_REPLY);
			if(Local_Reply == FALSE)
			{
				Local_ErrorState=E_NOK;
			}
		}
		else
		{
			Local_ErrorState=E_NO_RESPOSE;
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Esp_ConnectWifi(Esp_UsartNum Copy_UsartNum, char* Copy_Username, char* Copy_Password)
 * \Description     : Connect ESP to Wi-Fi
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART the ESP connected to
 * 					  Copy_Username	  The Wi-Fi user name
 * 					  Copy_Password	  The Wi-Fi Password
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Esp_ConnectWifi(Esp_UsartNum Copy_UsartNum, char* Copy_Username, char* Copy_Password)
{
	ErrorState_t Local_ErrorState=E_OK;
	bool Local_Reply=TRUE;
	u8 Local_Counter=0;
	if(Copy_Username == NULL || Copy_Password == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		do
		{
			/*Disconnect from old Wi-Fi connection if any*/
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "AT+CWQAP\r\n");
			/*send command to start connection*/
			Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, 23);
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "AT+CWJAP_CUR=");
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, '"');
			/*Enter the user name*/
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, Copy_Username);
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, '"');
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, ',');
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, '"');
			/*Enter the password*/
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, Copy_Password);
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, '"');
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "\r\n");
			/*Validate the connection*/
			Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, 35);
			Esp_Delay(10000000);
			Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, (Esp_Response+35), 35);
			Local_Reply = Esp_ValidateCmd(Esp_Response, ESP_WIFI_CONNECTED);
			if(Local_Reply == FALSE)
			{
				Local_Reply = Esp_ValidateCmd(Esp_Response, ESP_REPLY);
			}
			Local_Counter++;
		}while((Local_Reply==FALSE)&& (Local_Counter < ESP_TIMEOUT));
		if(Local_Counter== ESP_TIMEOUT)
		{
			Local_ErrorState=E_CONNECTION_FAILED;
		}
		else
		{
			Local_ErrorState=E_OK;
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Esp_ConnectServer(Esp_UsartNum Copy_UsartNum, char* Copy_ServerIp, char* Copy_ConnectionType, u16 Copy_PortNum)
 * \Description     : Connect the ESP module to Server
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   		The USART the ESP connected to
 * 					  Copy_ServerIp	  		The IP / DNS of the server you want to connect to
 * 					  Copy_ConnectionType 	The server Connection type (TCP / UDP)
 * 					  Copy_PortNum		 	The Port number to be connected
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Esp_ConnectServer(Esp_UsartNum Copy_UsartNum, char* Copy_ServerIp, char* Copy_ConnectionType, u16 Copy_PortNum)
{
	ErrorState_t Local_ErrorState=E_OK;
	bool Local_Reply=TRUE;
	u8 Local_Counter=0;
	char Local_NumStr[6]={0};
	if(Copy_ConnectionType == NULL || Copy_ServerIp == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		do
		{
			/*send server connection command*/
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "AT+CIPSTART=");
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, '"');
			/*Choose the connection type TCP / UDP*/
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, Copy_ConnectionType);
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, '"');
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, ',');
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, '"');
			/*Enter the server IP or DNS to connect it*/
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, Copy_ServerIp);
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, '"');
			Local_ErrorState=Usart_SendCharSynch(Copy_UsartNum, ',');
			Esp_ConvertNumToStr(Copy_PortNum,Local_NumStr);
			/*Enter the Port number chosen for connection*/
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, Local_NumStr);
			Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "\r\n");
			Esp_Delay(5);
			/*Validate connection*/
			Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, 17);
			Esp_Delay(1100);
			Local_Reply = Esp_ValidateCmd(Esp_Response, ESP_ERROR);
			Local_Counter++;
		}
		while((Local_Reply==TRUE) && (Local_Counter < ESP_TIMEOUT));
		if(Local_Counter== ESP_TIMEOUT)
		{
			Local_ErrorState=E_CONNECTION_FAILED;
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Esp_SendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength)
 * \Description     : Send Data to the server
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART the ESP connected to
 * 					  Copy_Data		  The Data to be sent to the server
 * 					  Copy_DataLength The length of Data to be sent to server
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Esp_SendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength)
{
	ErrorState_t Local_ErrorState=E_OK;
	bool Local_Reply=TRUE;
	char Local_NumStr[6]={0};
	if(Copy_Data == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		/*send command to set the length of data will be sent*/
		Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "AT+CIPSEND=");
		/*Add 2 to send \r\n at the end of data*/
		Esp_ConvertNumToStr(Copy_DataLength, Local_NumStr);
		/*send the length of data*/
		Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, Local_NumStr);
		Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "\r\n");
		/*check for the configuration is done*/
		Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, ESP_SEND_REPLY);
		Local_Reply=Esp_ValidateCmd(Esp_Response, ESP_REPLY);
		if(Local_Reply == TRUE)
		{
			/*Send Data*/
			Local_ErrorState=Usart_SendBufferSynch(Copy_UsartNum, Copy_Data, Copy_DataLength);
			Esp_Delay(5);
			Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, ESP_SEND_ACK);
		}
		else
		{
			Local_ErrorState=E_NOK;
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Esp_SendDataWithCont(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength, u16 Copy_InitialLength)
 * \Description     : Send Data to the server initial send
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   		The USART the ESP connected to
 * 					  Copy_Data		  		The Data to be sent to the server
 * 					  Copy_DataLength 		The length of Data to be sent to server
 * 					  Copy_InitialLength	The initial Data length
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Esp_SendDataWithCont(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength, u16 Copy_InitialLength)
{
	ErrorState_t Local_ErrorState=E_OK;
	bool Local_Reply=TRUE;
	char Local_NumStr[6]={0};
	if(Copy_Data == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		/*send command to set the length of data will be sent*/
		Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "AT+CIPSEND=");
		/*Add 2 to send \r\n at the end of data*/
		Esp_ConvertNumToStr(Copy_DataLength, Local_NumStr);
		/*send the length of data*/
		Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, Local_NumStr);
		Local_ErrorState=Usart_SendStringSynch(Copy_UsartNum, "\r\n");
		/*check for the configuration is done*/
		Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, ESP_SEND_REPLY);
		Local_Reply=Esp_ValidateCmd(Esp_Response, ESP_REPLY);
		if(Local_Reply == TRUE)
		{
			/*Send Data*/
			Local_ErrorState=Usart_SendBufferSynch(Copy_UsartNum, Copy_Data, Copy_InitialLength);
		}
		else
		{
			Local_ErrorState=E_NOK;
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Esp_ContSendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength)
 * \Description     : Continue Sending Data to the server
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART the ESP connected to
 * 					  Copy_Data		  The Data to be sent to the server
 * 					  Copy_DataLength The length of Data to be sent to server
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Esp_ContSendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_Data == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		Local_ErrorState=Usart_SendBufferSynch(Copy_UsartNum, Copy_Data, Copy_DataLength);
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Esp_EndSendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength)
 * \Description     : last Sending Data to the server
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART the ESP connected to
 * 					  Copy_Data		  The Data to be sent to the server
 * 					  Copy_DataLength The length of Data to be sent to server
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Esp_EndSendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_Data == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		Local_ErrorState=Usart_SendBufferSynch(Copy_UsartNum, Copy_Data, Copy_DataLength);
		Esp_Delay(5);
		Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Esp_Response, ESP_SEND_ACK);
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Esp_ReceiveData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength, Esp_Recv_t Copy_RecvType, void (*Copy_NotificationFunc)(void))
 * \Description     : Receive data from the server
 *
 * \Sync\Async      : Synchronous / Asynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   		The USART the ESP connected to
 * 					  Copy_DataLength 		The length of Data to be Received From server
 * 					  Copy_RecvType   		The Type of reception of Data (Synch - Asynch)
 * 					  Copy_NotificationFunc The notification of reception complete in case of Asynch
 * \Parameters (out): Copy_Data		  Data to be Received From server
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Esp_ReceiveData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength, Esp_Recv_t Copy_RecvType, void (*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_Data == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		switch(Copy_RecvType)
		{
		case ESP_SYNCH: Local_ErrorState=Usart_ReceiveBufferSynch(Copy_UsartNum, Copy_Data, Copy_DataLength); break;
		case ESP_ASYNCH: Local_ErrorState=Usart_ReceiveBufferASynch(Copy_UsartNum, Copy_Data, Copy_DataLength, Copy_NotificationFunc); break;
		default: Local_ErrorState=E_WRONG_OPTION;
		}
	}
	return Local_ErrorState;
}
/**********************************************************************************************************************
 *  END OF FILE: Esp_Program.c
 *********************************************************************************************************************/
