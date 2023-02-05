/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Uart_Private.h
 *		  Layer:  Mcal
 *       Module:  Usart
 *		Version:  1.00
 *	
 *  Description:  File contains the private macros used to configure uart     
 *  
 *********************************************************************************************************************/

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define USART_NUM			6                      /*Number of USARTs*/

#define USART_CR1			Usart_Arr[Copy_config->Num]->CR1

#define USART_CR2			Usart_Arr[Copy_config->Num]->CR2

#define USART_CR3			Usart_Arr[Copy_config->Num]->CR3

#define USART_BRR			Usart_Arr[Copy_config->Num]->BRR

#define USART_SR			Usart_Arr[Copy_UsartNum]->SR

#define USART_DR			Usart_Arr[Copy_UsartNum]->DR

#define UE					13                     /*USART enable*/

#define M					12                     /*Word length*/

#define PS					9                      /*Parity selection*/

#define TE					3                      /*Transmitter enable*/

#define RE					2                      /*Receiver enable*/

#define STOP				12						/*Stop Bits*/

#define DMAT				7						/*DMA enable transmitter*/

#define CLKEN				11						/*Clock enable*/

#define TXE					7						/*Transmit data register empty*/

#define RXNE				5						/*Read data register not empty*/

#define TXEIE				7						/*TXE interrupt enable*/

#define RXNEIE				5						/*RXNE interrupt enable*/

#define TC					6						/*Transmission complete*/

#define USART_TIME_OUT		(u32)((CLK_FRequancy/1000)*5)	/*5ms time out*/

 
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
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
u16 Usart_BRRRegisterValue(u32 Copy_BaudRate);
 
#endif  /* USART_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Usart_Private.h
 *********************************************************************************************************************/
