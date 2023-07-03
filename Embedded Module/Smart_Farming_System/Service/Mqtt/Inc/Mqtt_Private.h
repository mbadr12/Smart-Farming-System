/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Mqtt_Private.h
 *		  Layer:  Service
 *       Module:  Mqtt
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

#ifndef MQTT_PRIVATE_H
#define MQTT_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define CONNECT_PACKET				0x10

#define VAR_HEADER_LEN				0x0A

#define UTF_LEN_BYTES				0x02

#define PROTOCOL_NAME				"MQTT"

#define BYTE						0x08

#define PROTOCOL_LEVEL				0x04

#define USERNAMEFLAG				1<<6

#define PASSWORDFLAG				1<<7

#define KAT							0xff

#define CONNECT_ACK					{0x20, 0x2, 0x00, 0x00}

#define PUB_ACK						{0x40, 0x02, 0x00, 0x01}

#define SUB_ACK						{0x90, 0x03, 0x00, 0x01, 0x00}

#define CON_ACK_LEN					0x04

#define PUB_ACK_LEN					0x04

#define SUB_ACK_LEN					0x05

#define MAX_RESPONSE_LEN			0xf

#define PUB_PACKET_QOS0				0x30

#define PUB_PACKET_QOS1				0x32

#define SUB_PACKET					0x82

#define PACKET_ID					0x02

#define MAX_QOS_BYTE				0x01

#define DATA_INDEX					0x07

#define BROKER_REPLY_LEN			0x0C

#define IDENTITY_BYTES				0x02

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
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
static u8 Mqtt_Strlen(char* Copy_String);

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
static void Mqtt_StrCopy(u8* Copy_DestSArr, char* Copy_Str);


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
static bool Mqtt_ValidateResponse(u8* Copy_Response, u8* Copy_CorrectResponse, u8 Copy_Length);

#endif  /* MQTT_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Mqtt_Private.h
 *********************************************************************************************************************/
