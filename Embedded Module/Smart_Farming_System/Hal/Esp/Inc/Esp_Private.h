/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Esp_Private.h
 *		  Layer:  Hal
 *       Module:  Esp
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

#ifndef ESP_PRIVATE_H
#define ESP_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define MAX_RESPONSE		70

#define ESP_TIMEOUT			3

#define ESP_REPLY_LEN		7

#define ESP_SEND_REPLY		8

#define ESP_SEND_ACK		30

#define ESP_REPLY				"\r\nOK\r\n"

#define ESP_WIFI_CONNECTED		"\r\nOK\r\nWIFI DISWIFI CONNECTED\r\n"

#define ESP_SERVER_CONNECTED	"CONNECT\r\n\r\nOK\r\n"

#define ESP_ERROR				"ERROR"

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
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
static bool Esp_ValidateCmd(u8* Copy_Response, char* Copy_Correct);

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
static void Esp_ConvertNumToStr(u16 Copy_Number, char* Copy_String);

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
static void Esp_Delay(u32 Copy_Delay);

#endif  /* ESP_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Esp_Private.h
 *********************************************************************************************************************/
