
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Dma_Program.c
 *		  Layer:  Mcal
 *       Module:  Dma
 *		Version:  2.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "Dma_Private.h"
#include "Dma_Interface.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static DMA_RegDef_t* Dma_Arr[DMA_NUM]={DMA1 ,DMA2};

static void(*Dma_CallBackFuncArr[DMA_NUM][STREAM_NUM])(void)={{NULL}};


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
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
ErrorState_t Dma_Init(Dma_Config_t* Copy_DmaConfig)
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_DmaConfig == NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		if((Copy_DmaConfig->DMA_Number < DMA_NUM) && (Copy_DmaConfig->Stream < CHANNEL_NUM) && (Copy_DmaConfig->Channel < STREAM_NUM))
		{
			/*Reset the control register and disable stream*/
			DMA_CONTROL_REG=0;
			/*polling in the enable bit to make sure it has been reset*/
			while(GET_BIT(DMA_CONTROL_REG,EN_BIT)==1);
			/*select the channel*/
			DMA_CONTROL_REG |= (Copy_DmaConfig->Channel<<CH_SELECT);
			/*configure the priority of the stream*/
			DMA_CONTROL_REG |= (Copy_DmaConfig->Priority<<PR_SELECT);
			/*configure the FIFO usage*/
			if(Copy_DmaConfig->StreamMode == DMA_STREAM_FIFO)
			{
				/*Disable the direct mode*/
				SET_BIT(DMA_FIFO_REG,FIFO_SELECT);
				/*select FIFO threshold*/
				DMA_FIFO_REG &= FIFO_THRESHOLD_MASK;
				DMA_FIFO_REG |= Copy_DmaConfig->FifoThreshold;
			}
			else if(Copy_DmaConfig->StreamMode == DMA_STREAM_DIRECT)
			{
				/*Disable the direct mode*/
				CLR_BIT(DMA_FIFO_REG,FIFO_SELECT);
			}
			else
			{
				Local_ErrorState=E_WRONG_OPTION;
			}
			/*configure the Data transfer direction*/
			DMA_CONTROL_REG |= Copy_DmaConfig->DataDirection<<DATA_SELECT;
			/*configure the memory peripheral increment*/
			DMA_CONTROL_REG |= Copy_DmaConfig->MemPrphIncMode<<MEM_INC_SELECT;
			/*configure the size of source and destination*/
			DMA_CONTROL_REG |= (Copy_DmaConfig->MemSize<<MEM_SIZE_SELECT) | (Copy_DmaConfig->MemSize<<PRPH_SIZE_SELECT);
			/*Select the channel transfer mode*/
			DMA_CONTROL_REG |= (Copy_DmaConfig->channelMode<<CIRCULER_SELECT);
			/*Select the transfer type*/
			DMA_CONTROL_REG |= (Copy_DmaConfig->TransferType<<DOUBLE_BUFFER_SELECT);
		}
		else
		{
			Local_ErrorState=E_WRONG_OPTION;
		}
	}
	return Local_ErrorState;
}

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
ErrorState_t Dma_StreamStartSynch(Dma_StreamStartTrans* Copy_StartTrans)
{
	ErrorState_t Local_ErrorState=E_OK;
	u8 Local_RegNum=0;
	u8 Local_StreamNum=0;
	if(Copy_StartTrans==NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		/*assign the source and destination addresses according to data transfer direction*/
		switch(Copy_StartTrans->DataDirection)
		{
		case DMA_PERIPHERAL_TO_MEMORY:
		case DMA_MEMORY_TO_MEMORY: DMA_PRPH_REG=(u32)Copy_StartTrans->SourceAddress; DMA_MEM_REG = (u32)Copy_StartTrans->DestnationAddress; break;
		case DMA_MEMORY_TO_PERIPHERAL: DMA_MEM_REG=(u32)Copy_StartTrans->SourceAddress; DMA_PRPH_REG = (u32)Copy_StartTrans->DestnationAddress; break;
		default: Local_ErrorState=E_WRONG_OPTION;
		}
		/*if the double buffer mode is enabled but the memory 2 address*/
		if(Copy_StartTrans->SrcDestAddress2 != NULL)
		{
			DMA_MEM2_REG=(u32)Copy_StartTrans->SrcDestAddress2;
		}
		/*put the Number of transactions*/
		DMA_NUM_DATA_REG = Copy_StartTrans->NumberOfTrans;
		/*Enable the DMA*/
		SET_BIT(DMA_CTRL_REG,EN_BIT);
		/*polling until the transfer complete*/
		Local_RegNum=Copy_StartTrans->Stream/4;
		Local_StreamNum=Copy_StartTrans->Stream%4;
		switch(Local_StreamNum)
		{
		case DMA_STREAM_0: while((GET_BIT(DMA_ISR_REG,TCF0_SELECT))==0); DMA_IFCR_REG= 1<<TC0_SELECT; break;
		case DMA_STREAM_1: while((GET_BIT(DMA_ISR_REG,TCF1_SELECT))==0); DMA_IFCR_REG= 1<<TC1_SELECT; break;
		case DMA_STREAM_2: while((GET_BIT(DMA_ISR_REG,TCF2_SELECT))==0); DMA_IFCR_REG= 1<<TC2_SELECT; break;
		case DMA_STREAM_3: while((GET_BIT(DMA_ISR_REG,TCF3_SELECT))==0); DMA_IFCR_REG= 1<<TC3_SELECT; break;
		default: Local_ErrorState=E_WRONG_OPTION;
		}
	}
	return Local_ErrorState;
}

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
ErrorState_t Dma_StreamStartASynch(Dma_StreamStartTrans* Copy_StartTrans, void(*Copy_NotificationFunc)(void))
{
	ErrorState_t Local_ErrorState=E_OK;
	if(Copy_StartTrans==NULL)
	{
		Local_ErrorState=E_NULL_POINTER;
	}
	else
	{
		/*assign the source and destination addresses according to data transfer direction*/
		switch(Copy_StartTrans->DataDirection)
		{
		case DMA_PERIPHERAL_TO_MEMORY:
		case DMA_MEMORY_TO_MEMORY: DMA_PRPH_REG=(u32)Copy_StartTrans->SourceAddress; DMA_MEM_REG = (u32)Copy_StartTrans->DestnationAddress; break;
		case DMA_MEMORY_TO_PERIPHERAL: DMA_MEM_REG=(u32)Copy_StartTrans->SourceAddress; DMA_PRPH_REG = (u32)Copy_StartTrans->DestnationAddress; break;
		default: Local_ErrorState=E_WRONG_OPTION;
		}
		/*if the double buffer mode is enabled but the memory 2 address*/
		if(Copy_StartTrans->SrcDestAddress2 != NULL)
		{
			DMA_MEM2_REG=(u32)Copy_StartTrans->SrcDestAddress2;
		}
		/*put the Number of transactions*/
		DMA_NUM_DATA_REG = Copy_StartTrans->NumberOfTrans;
		/*Turn on the TCIE*/
		SET_BIT(DMA_CTRL_REG,TRANS_COMPLETE_SELECT);
		/*Pass the Callback function to global pointer*/
		Dma_CallBackFuncArr[Copy_StartTrans->DMA_Number][Copy_StartTrans->Stream]=Copy_NotificationFunc;
		/*Enable the DMA*/
		SET_BIT(DMA_CTRL_REG,EN_BIT);
	}

	return Local_ErrorState;
}

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
void DMA_StopStream(Dma_Num Copy_DmaNumber, Dma_StreamNum Copy_StreamNum)
{
	CLR_BIT((Dma_Arr[Copy_DmaNumber]->Stream[Copy_StreamNum].CR),EN_BIT);
	while(GET_BIT((Dma_Arr[Copy_DmaNumber]->Stream[Copy_StreamNum].CR),EN_BIT) == 1);
}

/******************************************************************************
 * \Syntax          : void DMA1_Stream0_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 0 in DMA1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA1_Stream0_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_1][DMA_STREAM_0] != NULL)
	{
		Dma_CallBackFuncArr[DMA_1][DMA_STREAM_0]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA1->IFCR[LIFCR] = 1 << TC0_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA1_Stream1_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 1 in DMA1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA1_Stream1_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_1][DMA_STREAM_1] != NULL)
	{
		Dma_CallBackFuncArr[DMA_1][DMA_STREAM_1]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA1->IFCR[LIFCR] = 1 << TC1_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA1_Stream2_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 2 in DMA1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA1_Stream2_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_1][DMA_STREAM_2] != NULL)
	{
		Dma_CallBackFuncArr[DMA_1][DMA_STREAM_2]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA1->IFCR[LIFCR] = 1 << TC2_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA1_Stream3_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 3 in DMA1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA1_Stream3_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_1][DMA_STREAM_3] != NULL)
	{
		Dma_CallBackFuncArr[DMA_1][DMA_STREAM_3]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA1->IFCR[LIFCR] = 1 << TC3_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA1_Stream4_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 4 in DMA1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA1_Stream4_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_1][DMA_STREAM_4] != NULL)
	{
		Dma_CallBackFuncArr[DMA_1][DMA_STREAM_4]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA1->IFCR[HIFCR] = 1 << TC0_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA1_Stream5_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 5 in DMA1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA1_Stream5_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_1][DMA_STREAM_5] != NULL)
	{
		Dma_CallBackFuncArr[DMA_1][DMA_STREAM_5]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA1->IFCR[HIFCR] = 1 << TC1_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA1_Stream6_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 6 in DMA1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA1_Stream6_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_1][DMA_STREAM_6] != NULL)
	{
		Dma_CallBackFuncArr[DMA_1][DMA_STREAM_6]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA1->IFCR[HIFCR] = 1 << TC2_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA1_Stream7_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 7 in DMA1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA1_Stream7_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_1][DMA_STREAM_7] != NULL)
	{
		Dma_CallBackFuncArr[DMA_1][DMA_STREAM_7]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA1->IFCR[HIFCR] = 1 << TC3_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA2_Stream0_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 0 in DMA2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA2_Stream0_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_2][DMA_STREAM_0] != NULL)
	{
		Dma_CallBackFuncArr[DMA_2][DMA_STREAM_0]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA2->IFCR[LIFCR] = 1 << TC0_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA2_Stream1_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 1 in DMA2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA2_Stream1_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_2][DMA_STREAM_1] != NULL)
	{
		Dma_CallBackFuncArr[DMA_2][DMA_STREAM_1]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA2->IFCR[LIFCR] = 1 << TC1_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA2_Stream2_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 2 in DMA2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA2_Stream2_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_2][DMA_STREAM_2] != NULL)
	{
		Dma_CallBackFuncArr[DMA_2][DMA_STREAM_2]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA2->IFCR[LIFCR] = 1 << TC2_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA2_Stream3_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 3 in DMA2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA2_Stream3_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_2][DMA_STREAM_3] != NULL)
	{
		Dma_CallBackFuncArr[DMA_2][DMA_STREAM_3]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA2->IFCR[LIFCR] = 1 << TC3_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA2_Stream4_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 4 in DMA2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA2_Stream4_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_2][DMA_STREAM_4] != NULL)
	{
		Dma_CallBackFuncArr[DMA_2][DMA_STREAM_4]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA2->IFCR[HIFCR] = 1 << TC0_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA2_Stream5_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 5 in DMA2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA2_Stream5_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_2][DMA_STREAM_5] != NULL)
	{
		Dma_CallBackFuncArr[DMA_2][DMA_STREAM_5]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA2->IFCR[HIFCR] = 1 << TC1_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA2_Stream6_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 6 in DMA2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA2_Stream6_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_2][DMA_STREAM_6] != NULL)
	{
		Dma_CallBackFuncArr[DMA_2][DMA_STREAM_6]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA2->IFCR[HIFCR] = 1 << TC2_SELECT;
}

/******************************************************************************
 * \Syntax          : void DMA2_Stream7_IRQHandler(void)
 * \Description     : The interrupt request handler of stream 7 in DMA2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void DMA2_Stream7_IRQHandler(void)
{
	/*Invoke The CallBack Function*/
	if(Dma_CallBackFuncArr[DMA_2][DMA_STREAM_7] != NULL)
	{
		Dma_CallBackFuncArr[DMA_2][DMA_STREAM_7]();
	}
	/*Clear the transfer complete Interrupt Flag*/
	DMA2->IFCR[HIFCR] = 1 << TC3_SELECT;
}

/**********************************************************************************************************************
 *  END OF FILE: Dma_Program.c
 *********************************************************************************************************************/
