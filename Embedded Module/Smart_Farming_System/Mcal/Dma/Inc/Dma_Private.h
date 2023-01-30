/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Dma_Private.h
 *		  Layer:  Mcal
 *       Module:  Dma
 *		Version:  2.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

#define DMA_NUM					2

#define STREAM_NUM				8

#define CHANNEL_NUM				8

#define EN_BIT					0

#define CH_SELECT				25

#define PR_SELECT				16

#define FIFO_SELECT				2

#define DATA_SELECT				6

#define INC_SELECT				9

#define MEM_SIZE_SELECT			13

#define PRPH_SIZE_SELECT		11

#define DOUBLE_BUFFER_SELECT	8

#define CIRCULER_SELECT			18

#define TC0_SELECT				0

#define TC1_SELECT				6

#define TC2_SELECT				16

#define TC3_SELECT				22

#define TCF0_SELECT				5

#define TCF1_SELECT				11

#define TCF2_SELECT				21

#define TCF3_SELECT				27

#define MEM_INC_SELECT			9

#define TRANS_COMPLETE_SELECT	4

#define LIFCR					0

#define HIFCR					1

#define DMA_USART

#define FIFO_THRESHOLD_MASK		~((u32)0b11)

#define DMA_CONTROL_REG			Dma_Arr[Copy_DmaConfig->DMA_Number]->Stream[Copy_DmaConfig->Stream].CR

#define DMA_FIFO_REG			Dma_Arr[Copy_DmaConfig->DMA_Number]->Stream[Copy_DmaConfig->Stream].FCR

#define DMA_MEM_REG				Dma_Arr[Copy_StartTrans->DMA_Number]->Stream[Copy_StartTrans->Stream].M0AR

#define DMA_MEM2_REG			Dma_Arr[Copy_StartTrans->DMA_Number]->Stream[Copy_StartTrans->Stream].M1AR

#define DMA_PRPH_REG			Dma_Arr[Copy_StartTrans->DMA_Number]->Stream[Copy_StartTrans->Stream].PAR

#define DMA_NUM_DATA_REG		Dma_Arr[Copy_StartTrans->DMA_Number]->Stream[Copy_StartTrans->Stream].NDTR

#define DMA_CTRL_REG			Dma_Arr[Copy_StartTrans->DMA_Number]->Stream[Copy_StartTrans->Stream].CR

#define DMA_ISR_REG				Dma_Arr[Copy_StartTrans->DMA_Number]->ISR[Local_RegNum]

#define DMA_IFCR_REG			Dma_Arr[Copy_StartTrans->DMA_Number]->IFCR[Local_RegNum]

 
#endif  /* DMA_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Dma_Private.h
 *********************************************************************************************************************/
