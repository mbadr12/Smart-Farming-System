/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Dma_Types.h
 *		  Layer:  Mcal
 *       Module:  Dma
 *		Version:  2.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef DMA_TYPES_H
#define DMA_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define DMA_DCMI			((volatile u32*)0x50050028UL)

#define DMA_USART1			((volatile u32*)0x40011004UL)

#define DMA_USART2			((volatile u32*)0x40004404UL)

#define DMA_USART3			((volatile u32*)0x40004804UL)

#define DMA_UART4			((volatile u32*)0x40004c04UL)

#define DMA_UART5			((volatile u32*)0x40004504UL)

#define DMA_USART6			((volatile u32*)0x40011404UL)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	DMA_1=0,
	DMA_2
}Dma_Num;

typedef enum
{
	DMA_STREAM_0=0,
	DMA_STREAM_1,
	DMA_STREAM_2,
	DMA_STREAM_3,
	DMA_STREAM_4,
	DMA_STREAM_5,
	DMA_STREAM_6,
	DMA_STREAM_7,
}Dma_StreamNum;

typedef enum
{
	DMA_CHANNEL_0=0,
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7
}Dma_ChannelNum;

typedef enum
{
	DMA_STREAM_DIRECT=0,
	DMA_STREAM_FIFO
}Dma_StreamMode;

typedef enum
{
	DMA_FIFO_QUARTER_FULL=0,
	DMA_FIFO_HALF_FULL,
	DMA_FIFO_THREE_QUARTERS_FULL,
	DMA_FIFO_FULL,
}Dma_StreamFifoTreshold;

typedef enum
{
	DMA_CHANNEL_REGULAR=0,
	DMA_CHANNEL_DOUBLE_BUFFER
}Dma_ChannelMode;

typedef enum
{
	DMA_PERIPHERAL_TO_MEMORY=0,
	DMA_MEMORY_TO_PERIPHERAL,
	DMA_MEMORY_TO_MEMORY
}Dma_TransDirction;

typedef enum
{
	DMA_STREAM_LOW_PR=0,
	DMA_STREAM_MEDIUM_PR,
	DMA_STREAM_HIGH_PR,
	DMA_STREAM_VERY_HIGH_PR,
}Dma_StreamPriority;

typedef enum
{
	DMA_MEM_FIXED_PRPH_FIXED=0,
	DMA_MEM_FIXED_PRPH_INC,
	DMA_MEM_INC_PRPH_FIXED,
	DMA_MEM_INC_PRPH_INC
}Dma_SrcDesState;

typedef enum
{
	DMA_PRPH_SIZE_BYTE=0,
	DMA_PRPH_SIZE_HALF_WORD,
	DMA_PRPH_SIZE_WORD
}Dma_PeripheralSize;

typedef enum
{
	DMA_MEM_SIZE_BYTE=0,
	DMA_MEM_SIZE_HALF_WORD,
	DMA_MEM_SIZE_WORD
}Dma_MemorySize;

typedef enum
{
	DMA_SINGLE_TRANSFER=0,
	DMA_CIRCULAR_TRANSFER
}Dma_Transfer_t;


typedef struct
{
	Dma_Num DMA_Number;
	Dma_StreamNum Stream;
	Dma_ChannelNum Channel;
	Dma_StreamMode StreamMode;
	Dma_StreamFifoTreshold FifoThreshold;
	Dma_ChannelMode channelMode;
	Dma_TransDirction DataDirection;
	Dma_StreamPriority Priority;
	Dma_SrcDesState MemPrphIncMode;
	Dma_PeripheralSize PrphSize;
	Dma_MemorySize MemSize;
	Dma_Transfer_t TransferType;
}Dma_Config_t;

typedef struct
{
	Dma_Num DMA_Number;
	Dma_StreamNum Stream;
	Dma_TransDirction DataDirection;
	u32* SourceAddress;
	u32* DestnationAddress;
	u32* SrcDestAddress2;
	u16 NumberOfTrans;
}Dma_StreamStartTrans;


#endif  /* DMA_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Dma_Types.h
 *********************************************************************************************************************/
