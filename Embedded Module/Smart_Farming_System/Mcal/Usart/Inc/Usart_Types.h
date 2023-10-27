/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Usart_Types.h
 *		  Layer:  Mcal
 *       Module:  Usart
 *		Version:  1.00
 *	
 *  Description:  File contains the types used to configure uart     
 *  
 *********************************************************************************************************************/
 
#ifndef USART_TYPES_H
#define USART_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*USART Peripheral number*/
typedef enum
{
	USART_1=0,
	USART_2,
	USART_3,
	UART_4,
	UART_5,
	USART_6
}Usart_Number_t;

/*Data length*/
typedef enum
{
	USART_EIGHT_BIT=0,
	USART_NINE_BIT
}Usart_DataLength_t;

/*USART Parity type*/
typedef enum
{
	USART_PARITY_DISABLED=0,
	USART_PARITY_EVEN=2,
	USART_PARITY_ODD
}Usart_Parity_t;

/*USART mode*/
typedef enum
{
	USART_ASYNCH=0,
	USART_SYNCH
}Usart_mode_t;

/*Number of stop Bits*/

typedef enum
{
	USART_ONE_STOP_BIT=0,
	USART_HALF_STOP_BIT,
	USART_TWO_STOP_BIT,
	USART_ONE_AND_HALF_STOP_BIT
}Usart_StopBit_t;

/*Transfer Type*/
typedef enum
{
	USART_UC_TRANCEIVER=0,
	USART_DMA_RECEIVER,
	USART_DMA_TRANSMITER,
	USART_DMA_TRANCEIVER
}Usart_DataTransfer_t;

/*USART configuration structure*/
typedef struct
{
	Usart_Number_t Num;
	Usart_mode_t Mode;
	u32 BuadRate;
	Usart_DataLength_t DataLength;
	Usart_Parity_t Parity;
	Usart_StopBit_t StopBitNo;
	Usart_DataTransfer_t DataTransMode;
}Usart_config_t;

#endif  /* USART_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Usart_Types.h
 *********************************************************************************************************************/
