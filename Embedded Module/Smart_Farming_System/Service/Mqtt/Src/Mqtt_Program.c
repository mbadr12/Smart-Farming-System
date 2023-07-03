/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Mqtt_Program.c
 *		  Layer:  Service
 *       Module:  Mqtt
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Esp_Interface.h"
#include "Mqtt_Interface.h"
#include "Mqtt_Config.h"
#include "Mqtt_Private.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 Mqtt_Packet[MQTT_MAX_PACKET_LEN]={0};

static u8 Mqtt_PacketIndex=0;

static u8 Mqtt_BrokerResponse[MAX_RESPONSE_LEN]={0};

static u8 Mqtt_ConnectAck[CON_ACK_LEN]=CONNECT_ACK;

static u8 Mqtt_PubAck[PUB_ACK_LEN]=PUB_ACK;

static u8 Mqtt_SubAck[SUB_ACK_LEN]=SUB_ACK;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : static u8 Mqtt_Strlen(char* Copy_String)
 * \Description     : Function Calculates the string Length
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_String     The string you want to calculate its length
 * \Parameters (out): None
 * \Return value:   : u8 	The length of string
 *******************************************************************************/
static u8 Mqtt_Strlen(char* Copy_String)
{
	u8 Local_Counter=0;
	while(Copy_String[Local_Counter] != '\0')
	{
		Local_Counter++;
	}
	return Local_Counter;
}

/******************************************************************************
 * \Syntax          : static void Mqtt_StrCopy(u8* Copy_DestSArr, char* Copy_Str)
 * \Description     : Function copy string into array
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_DestSArr   The array you want to copy string on
 * 					  Copy_String     The string you want to copy in to array
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
static void Mqtt_StrCopy(u8* Copy_DestSArr, char* Copy_Str)
{
	u8 Local_Index=0;
	while(Copy_Str[Local_Index] != '\0')
	{
		Copy_DestSArr[Local_Index]=Copy_Str[Local_Index];
		Local_Index++;
	}
}

/******************************************************************************
 * \Syntax          : static bool Mqtt_ValidateResponse(u8* Copy_Response, u8* Copy_CorrectResponse, u8 Copy_Length)
 * \Description     : Function validates the broker response
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Response     		The Response of broker
 * 					  Copy_CorrectResponse		The Correct response needed
 * 					  Copy_Length	  			The length of response
 * \Parameters (out): None
 * \Return value:   : bool 	TRUE
 * 								FALSE
 *******************************************************************************/
static bool Mqtt_ValidateResponse(u8* Copy_Response, u8* Copy_CorrectResponse, u8 Copy_Length)
{
	bool Local_Result=TRUE;
	u8 Local_Counter=0;
	for(Local_Counter=0;Local_Counter < Copy_Length; Local_Counter++)
	{
		if(Copy_CorrectResponse[Local_Counter] != Copy_Response[Local_Counter])
		{
			break;
		}
	}
	if(Local_Counter != Copy_Length)
	{
		Local_Result=FALSE;
	}
	return Local_Result;
}

static void Mqtt_EncodeRemLen(u16 Copy_RemLen)
{
	u16 Local_EncodedNum=0;
	do
	{
		Local_EncodedNum=Copy_RemLen%128;
		Copy_RemLen/=128;
		if(Copy_RemLen > 0)
		{
			Local_EncodedNum|=128;
		}
		Mqtt_Packet[Mqtt_PacketIndex++]=Local_EncodedNum;
	}while(Copy_RemLen > 0);
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
 * \Syntax          : ErrorState_t Mqtt_Connect(Mqtt_UsartNum Copy_UsartNum ,char* Copy_ClientId, Mqtt_EspConnection* Copy_EspConfig)
 * \Description     : Function initializes the whole Connection and Sends the Connect Packet to broker
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART Connected to WiFi module
 *					  Copy_ClientId	  The id of client (MCU) to communicate with broker
 *					  Copy_EspConfig  The configuration of ESP module
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Mqtt_Connect(Mqtt_UsartNum Copy_UsartNum ,Mqtt_Connect_t* Copy_Connect, Mqtt_EspConnection* Copy_EspConfig)
{
	ErrorState_t Local_ErrorState=E_OK;
	u16 Local_Len=0;
	u8 Local_ConnectFlag=0x02;
	bool Local_Result=TRUE;
	if((Copy_Connect == NULL) || (Copy_EspConfig == NULL))
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		/*Initialize the Wi-Fi module*/
		Local_ErrorState=Esp_Init(Copy_UsartNum);
		/*Connect Wi-Fi module to Internet*/
		Local_ErrorState=Esp_ConnectWifi(Copy_UsartNum, Copy_EspConfig->WifiName, Copy_EspConfig->WifiPassword);
		if(Local_ErrorState == E_OK)
		{
			Mqtt_PacketIndex=0;
			/*Start composition of the connect Packet by the fixed header*/
			/*Start with the Packet type*/
			Mqtt_Packet[Mqtt_PacketIndex++]=CONNECT_PACKET;
			/*Calculate the Remaining length*/
			Local_Len = VAR_HEADER_LEN + UTF_LEN_BYTES + Mqtt_Strlen(Copy_Connect->ClientId);
			/*Add username and password to remaining length if there*/
			if(Copy_Connect->UserName != NULL)
			{
				Local_Len += (IDENTITY_BYTES + Mqtt_Strlen(Copy_Connect->UserName));
				/*Set username flag in connect flags*/
				Local_ConnectFlag |=  USERNAMEFLAG;
			}
			if(Copy_Connect->Password != NULL)
			{
				Local_Len += (IDENTITY_BYTES + Mqtt_Strlen(Copy_Connect->Password));
				/*Set Password flag in connect flags*/
				Local_ConnectFlag |= PASSWORDFLAG;
			}
			Mqtt_EncodeRemLen(Local_Len);
			/*Put the variable Header*/
			/*Put the Length of protocol Name as MSB LSB*/
			Local_Len=Mqtt_Strlen(PROTOCOL_NAME);
			Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len>>BYTE);
			Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len);
			/*Put the Protocol Name*/
			Mqtt_StrCopy((Mqtt_Packet+Mqtt_PacketIndex), PROTOCOL_NAME);
			Mqtt_PacketIndex+=Local_Len;
			/*Protocol Level*/
			Mqtt_Packet[Mqtt_PacketIndex++]=PROTOCOL_LEVEL;
			/*Connect Flags for Public broker*/
			Mqtt_Packet[Mqtt_PacketIndex++]=Local_ConnectFlag;
			/*Put Keep alive time as Max Value*/
			Mqtt_Packet[Mqtt_PacketIndex++]=KAT;
			Mqtt_Packet[Mqtt_PacketIndex++]=KAT;
			/*the Pay-load*/
			/*Put the Length of ClientId as MSB LSB*/
			Local_Len=Mqtt_Strlen(Copy_Connect->ClientId);
			Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len>>BYTE);
			Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len);
			/*Put the ClientId*/
			Mqtt_StrCopy((Mqtt_Packet+Mqtt_PacketIndex), Copy_Connect->ClientId);
			Mqtt_PacketIndex+=Local_Len;
			if(Copy_Connect->UserName != NULL)
			{
				/*Put the Length of username as MSB LSB*/
				Local_Len=Mqtt_Strlen(Copy_Connect->UserName);
				Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len>>BYTE);
				Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len);
				/*Put the username*/
				Mqtt_StrCopy((Mqtt_Packet+Mqtt_PacketIndex), Copy_Connect->UserName);
				Mqtt_PacketIndex+=Local_Len;
			}
			if(Copy_Connect->Password != NULL)
			{
				/*Put the Length of Password as MSB LSB*/
				Local_Len=Mqtt_Strlen(Copy_Connect->Password);
				Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len>>BYTE);
				Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len);
				/*Put the ClientId*/
				Mqtt_StrCopy((Mqtt_Packet+Mqtt_PacketIndex), Copy_Connect->Password);
				Mqtt_PacketIndex+=Local_Len;
			}
			/*Initiate TCP connection between Wi-Fi module and the broker*/
			do
			{
				Local_ErrorState=Esp_ConnectServer(Copy_UsartNum, Copy_EspConfig->BrokerDNS, "TCP", Copy_EspConfig->BrokerTcpPort);
				/*Send Connect Packet to broker*/
				Local_ErrorState=Esp_SendData(Copy_UsartNum, Mqtt_Packet, Mqtt_PacketIndex);
				/*Receive The Connect Acknowledge*/
				Local_ErrorState=Esp_ReceiveData(Copy_UsartNum, Mqtt_BrokerResponse, BROKER_REPLY_LEN, ESP_SYNCH, NULL);
				Local_Result=Mqtt_ValidateResponse((Mqtt_BrokerResponse+DATA_INDEX), Mqtt_ConnectAck, CON_ACK_LEN);
			}while(Local_Result == FALSE);
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Mqtt_Publish(Mqtt_UsartNum Copy_UsartNum, Mqtt_Publish_t* Copy_PubPacket)
 * \Description     : Function Sends the publish Packet to broker
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART Connected to WiFi module
 *					  Copy_PubPacket  The publish packet configuration
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Mqtt_Publish(Mqtt_UsartNum Copy_UsartNum, Mqtt_Publish_t* Copy_PubPacket)
{
	ErrorState_t Local_ErrorState=E_OK;
	u32 Local_Len=0;
	bool Local_Result=TRUE;
	static u16 Local_PacketId=0;
	if(Copy_PubPacket == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		Mqtt_PacketIndex=0;
		/*Calculate the Packet remaining length*/
		Local_Len=UTF_LEN_BYTES+Mqtt_Strlen(Copy_PubPacket->TopicName)+Copy_PubPacket->MsgLen;
		if(Copy_PubPacket->Telemetry != NULL)
		{
			Local_Len+=Copy_PubPacket->TelLen+5;
		}
		/*Fixed header*/
		switch(Copy_PubPacket->Qos)
		{
		case MQTT_QOS0: Mqtt_Packet[Mqtt_PacketIndex++]=PUB_PACKET_QOS0; break;
		case MQTT_QOS1: Mqtt_Packet[Mqtt_PacketIndex++]=PUB_PACKET_QOS1; Local_Len+=PACKET_ID; break; /*Add the two bytes of Packet Id*/
		default: Local_ErrorState=E_WRONG_OPTION;
		}
		Mqtt_EncodeRemLen(Local_Len);
		/*Put the variable Header*/
		/*Put the Length of Topic Name as MSB LSB*/
		Local_Len=Mqtt_Strlen(Copy_PubPacket->TopicName);
		Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len>>BYTE);
		Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len);
		/*Put the Topic Name*/
		Mqtt_StrCopy((Mqtt_Packet+Mqtt_PacketIndex), Copy_PubPacket->TopicName);
		Mqtt_PacketIndex+=Local_Len;
		if(Copy_PubPacket->Qos > MQTT_QOS0)
		{
			/*Put the Packet Identifier*/
			Local_PacketId++;
			Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_PacketId>>BYTE);
			Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_PacketId);
			/*update the PUBACK with the new Packet Identifier*/
			Mqtt_PubAck[2]=(u8)(Local_PacketId>>BYTE);
			Mqtt_PubAck[3]=(u8)(Local_PacketId);
		}
		/*Send The Headers using ESP*/
		Local_Len=Mqtt_PacketIndex+Copy_PubPacket->MsgLen;
		if(Copy_PubPacket->Telemetry != NULL)
		{
			Local_Len+=Copy_PubPacket->TelLen+5;
		}
		Esp_SendDataWithCont(Copy_UsartNum, Mqtt_Packet , Local_Len ,Mqtt_PacketIndex);
		/*Telemetry Send*/
		if(Copy_PubPacket->Telemetry != NULL)
		{
			Esp_ContSendData(Copy_UsartNum, (u8*)"{\"", 2);
			Esp_ContSendData(Copy_UsartNum, (u8*)Copy_PubPacket->Telemetry, Copy_PubPacket->TelLen);
			Esp_ContSendData(Copy_UsartNum, (u8*)"\":", 2);
		}
		/*Message send*/
		if(Copy_PubPacket->Telemetry != NULL)
		{
			Esp_ContSendData(Copy_UsartNum,(u8*) Copy_PubPacket->Msg, Copy_PubPacket->MsgLen);
			Esp_EndSendData(Copy_UsartNum,(u8*) "}", 1);
		}
		else
		{
			Esp_EndSendData(Copy_UsartNum,(u8*) Copy_PubPacket->Msg, Copy_PubPacket->MsgLen);
		}
		if(Copy_PubPacket->Qos > MQTT_QOS0)
		{
			Local_ErrorState=Esp_ReceiveData(Copy_UsartNum, Mqtt_BrokerResponse, BROKER_REPLY_LEN, ESP_SYNCH, NULL);
			Local_Result=Mqtt_ValidateResponse((Mqtt_BrokerResponse+DATA_INDEX), Mqtt_PubAck, PUB_ACK_LEN);
			if(Local_Result == FALSE)
			{
				Local_ErrorState=E_CONNECTION_FAILED;
			}
		}
	}
	return Local_ErrorState;
}

/******************************************************************************
 * \Syntax          : ErrorState_t Mqtt_Subscribe(Mqtt_UsartNum Copy_UsartNum, char* Copy_TopicName, Mqtt_Qos_t Copy_MaxQos)
 * \Description     : Function Sends the subscribe Packet to broker
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART Connected to WiFi module
 *					  Copy_TopicName  The Topic name to subscribe
 *					  Copy_MaxQos	  The Max Supported quality of service
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Mqtt_Subscribe(Mqtt_UsartNum Copy_UsartNum, char* Copy_TopicName, Mqtt_Qos_t Copy_MaxQos)
{
	ErrorState_t Local_ErrorState=E_OK;
	static u16 Local_PacketId=0;
	u16 Local_Len=0;
	bool Local_Result=TRUE;
	if(Copy_TopicName == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		Mqtt_PacketIndex=0;
		/*Start composition of the Subscribe Packet by the fixed header*/
		/*Start with the Packet type*/
		Mqtt_Packet[Mqtt_PacketIndex++]=SUB_PACKET;
		/*Calculate the Remaining length*/
		Local_Len= PACKET_ID + UTF_LEN_BYTES + Mqtt_Strlen(Copy_TopicName) + MAX_QOS_BYTE;
		Mqtt_EncodeRemLen(Local_Len);
		/*Composition of variable header*/
		/*Put the Packet Identifier*/
		Local_PacketId++;
		Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_PacketId>>BYTE);
		Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_PacketId);
		/*update the SubACK with the new Packet Identifier*/
		Mqtt_SubAck[2]=(u8)(Local_PacketId>>BYTE);
		Mqtt_SubAck[3]=(u8)(Local_PacketId);
		/*The Pay-load -> topic filter*/
		/*Put the Length of Topic Name as MSB LSB*/
		Local_Len=Mqtt_Strlen(Copy_TopicName);
		Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len>>BYTE);
		Mqtt_Packet[Mqtt_PacketIndex++]=(u8)(Local_Len);
		/*Put the Topic Name*/
		Mqtt_StrCopy((Mqtt_Packet+Mqtt_PacketIndex), Copy_TopicName);
		Mqtt_PacketIndex+=Local_Len;
		/*Put Max Supported QoS*/
		Mqtt_Packet[Mqtt_PacketIndex++]=Copy_MaxQos;
		/*Update the SUBACK with the Max QOS*/
		Mqtt_SubAck[4]=Copy_MaxQos;
		/*Send the subscribe packet to broker*/
		Local_ErrorState=Esp_SendData(Copy_UsartNum, Mqtt_Packet, Mqtt_PacketIndex);
		/*Receive The subscribe Acknowledge*/
		Local_ErrorState=Esp_ReceiveData(Copy_UsartNum, Mqtt_BrokerResponse, BROKER_REPLY_LEN, ESP_SYNCH, NULL);
		Local_Result=Mqtt_ValidateResponse((Mqtt_BrokerResponse+DATA_INDEX), Mqtt_SubAck, SUB_ACK_LEN);
		if(Local_Result == FALSE)
		{
			Local_ErrorState=E_CONNECTION_FAILED;
		}
	}
	return Local_ErrorState;
}
/* TODO : : if needed
ErrorState_t Mqtt_ReceiveSubData(Mqtt_UsartNum Copy_UsartNum, char* Copy_TopicName, u8* Copy_Container, u8 Copy_MsgLen)
{

}
*/
/**********************************************************************************************************************
 *  END OF FILE: Mqtt_Program.c
 *********************************************************************************************************************/
