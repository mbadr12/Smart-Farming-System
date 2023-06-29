/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Mqtt_Interface.h
 *		  Layer:  Service
 *       Module:  Mqtt
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef MQTT_INTERFACE_H
#define MQTT_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Mqtt_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t Mqtt_Connect(Mqtt_UsartNum Copy_UsartNum ,char* Copy_ClientId, Mqtt_EspConnection* Copy_EspConfig)
 * \Description     : Function initializes the whole Connection and Sends the Connect Packet to broker
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_UsartNum   The USART Connected to WiFi module
 *					  Copy_ClientId	  The configuration of client (MCU) to communicate with broker
 *					  Copy_EspConfig  The configuration of ESP module
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Mqtt_Connect(Mqtt_UsartNum Copy_UsartNum ,Mqtt_Connect_t* Copy_Connect, Mqtt_EspConnection* Copy_EspConfig);
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
ErrorState_t Mqtt_Publish(Mqtt_UsartNum Copy_UsartNum, Mqtt_Publish_t* Copy_PubPacket);

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
ErrorState_t Mqtt_Subscribe(Mqtt_UsartNum Copy_UsartNum, char* Copy_TopicName, Mqtt_Qos_t Copy_MaxQos);
 
#endif  /* MQTT_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Mqtt_Interface.h
 *********************************************************************************************************************/
