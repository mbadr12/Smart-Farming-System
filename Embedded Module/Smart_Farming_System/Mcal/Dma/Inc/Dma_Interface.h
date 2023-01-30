/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Dma_Interface.h
 *		  Layer:  Mcal
 *       Module:  Dma
 *		Version:  2.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Dma_Types.h"

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t Dma_Init(Dma_Config_t* Copy_DmaConfig)
 * \Description     : Initialize the required DMA with required configuration
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_DmaConfig: pointer to structure contains the configurations
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Dma_Init(Dma_Config_t* Copy_DmaConfig);

/******************************************************************************
 * \Syntax          : ErrorState_t Dma_StreamStartSynch(Dma_StreamStartTrans* Copy_StartTrans)
 * \Description     : Initialize the transaction of DMA
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_DmaConfig: pointer to structure contains the Addresses and number of transactions
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Dma_StreamStartSynch(Dma_StreamStartTrans* Copy_StartTrans);

/******************************************************************************
 * \Syntax          : ErrorState_t Dma_StreamStartASynch(Dma_StreamStartTrans* Copy_StartTrans, void(*Copy_NotificationFunc)(void))
 * \Description     : Initialize the transaction of DMA
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_DmaConfig: pointer to structure contains the Addresses and number of transactions
 * 					  Copy_NotificationFunc: pointer to function contains the callback function
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Dma_StreamStartASynch(Dma_StreamStartTrans* Copy_StartTrans, void(*Copy_NotificationFunc)(void));


/******************************************************************************
 * \Syntax          : void DMA_StopStream(Dma_Num Copy_DmaNumber, Dma_StreamNum Copy_StreamNum)
 * \Description     : Stop the DMA Stream
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_DmaNumber: The required DMA
 * 					  Copy_StreamNum: The required stream
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA_StopStream(Dma_Num Copy_DmaNumber, Dma_StreamNum Copy_StreamNum);
 
#endif  /* DMA_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Dma_Interface.h
 *********************************************************************************************************************/
