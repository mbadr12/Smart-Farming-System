/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Usart_Interface.h
 *		  Layer:  Mcal
 *       Module:  Usart
 *		Version:  1.00
 *	
 *  Description:  File contains the functions used by user to configure uart     
 *  
 *********************************************************************************************************************/
 
#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Usart_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
ErrorState_t Usart_Init(Usart_config_t* Copy_config);

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
ErrorState_t Usart_SendCharSynch(Usart_Number_t Copy_UsartNum, u16 Copy_Data);

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
ErrorState_t Usart_SendCharASynch(Usart_Number_t Copy_UsartNum, u16 Copy_Data , void (*Copy_NotificationFunc)(void));

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
ErrorState_t Usart_SendStringSynch(Usart_Number_t Copy_UsartNum, char* Copy_String);

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
ErrorState_t Usart_SendStringASynch(Usart_Number_t Copy_UsartNum, char* Copy_String, void (*Copy_NotificationFunc)(void));

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
ErrorState_t Usart_SendBufferSynch(Usart_Number_t Copy_UsartNum, u8* Copy_Buffer, u16 Copy_BufferLen);

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
ErrorState_t Usart_SendBufferASynch(Usart_Number_t Copy_UsartNum, char* Copy_Buffer, u16 Copy_BufferLen, void (*Copy_NotificationFunc)(void));

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
ErrorState_t Usart_ReceiveCharSynch(Usart_Number_t Copy_UsartNum, u8* Copy_Data);

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
ErrorState_t Usart_ReceiveCharASynch(Usart_Number_t Copy_UsartNum, u16* Copy_Data, void (*Copy_NotificationFunc)(void));

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
ErrorState_t Usart_ReceiveBufferSynch(Usart_Number_t Copy_UsartNum, u8* Copy_Buffer, u16 Copy_BufferSize);

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
ErrorState_t Usart_ReceiveBufferASynch(Usart_Number_t Copy_UsartNum, u8* Copy_Buffer, u16 Copy_BufferSize, void (*Copy_NotificationFunc)(void));
 
#endif  /* USART_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Usart_Interface.h
 *********************************************************************************************************************/
