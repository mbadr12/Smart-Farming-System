/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Esp_Interface.h
 *		  Layer:  Hal
 *       Module:  Esp
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Esp_Types.h"
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
ErrorState_t Esp_Init(Esp_UsartNum Copy_UsartNum);

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
ErrorState_t Esp_ConnectWifi(Esp_UsartNum Copy_UsartNum, char* Copy_Username, char* Copy_Password);

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
ErrorState_t Esp_ConnectServer(Esp_UsartNum Copy_UsartNum, char* Copy_ServerIp, char* Copy_ConnectionType, u16 Copy_PortNum);

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
ErrorState_t Esp_SendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength);

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
ErrorState_t Esp_SendDataWithCont(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength, u16 Copy_InitialLength);

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
ErrorState_t Esp_ContSendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength);

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
ErrorState_t Esp_EndSendData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength);

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
ErrorState_t Esp_ReceiveData(Esp_UsartNum Copy_UsartNum, u8* Copy_Data, u16 Copy_DataLength, Esp_Recv_t Copy_RecvType, void (*Copy_NotificationFunc)(void));
 
#endif  /* ESP_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Esp_Interface.h
 *********************************************************************************************************************/
