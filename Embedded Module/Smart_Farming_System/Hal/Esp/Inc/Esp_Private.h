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

#define ESP_TIMEOUT			10

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : bool Esp_ValidateCmd(u8* Copy_Response, char* Copy_Correct)
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
bool Esp_ValidateCmd(u8* Copy_Response, char* Copy_Correct);

/******************************************************************************
 * \Syntax          : void Esp_ConvertNumToStr(u16 Copy_Number, char* Copy_String)
 * \Description     : Convert number to string to send in UTF-8 format
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Number   Number to be converted
 * \Parameters (out): Copy_String	Converted number as string
 * \Return value:   : void
 *******************************************************************************/
void Esp_ConvertNumToStr(u16 Copy_Number, char* Copy_String);
 
#endif  /* ESP_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Esp_Private.h
 *********************************************************************************************************************/
