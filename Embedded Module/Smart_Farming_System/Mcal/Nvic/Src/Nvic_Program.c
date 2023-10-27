/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Nvic_Proram.c
 *		  Layer:  Mcal
 *       Module:  Nvic
 *		Version:  1.00
 *	
 *  Description:  Implemenation of the NVIC module.  
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "Nvic_Interface.h"
#include "Nvic_Private.h"
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
ErrorState_t Nvic_EnableIRQ(Nvic_IRQn_t Copy_IRQ){
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;

    u8 Local_RegOffset = Copy_IRQ / WORD_LENGTH_BITS;
    u8 Local_BitOffset = Copy_IRQ % WORD_LENGTH_BITS;
    SET_BIT(NVIC->ISER[Local_RegOffset], Local_BitOffset);

    return E_OK;
}

ErrorState_t Nvic_DisableIRQ(Nvic_IRQn_t Copy_IRQ){
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;

    u8 Local_RegOffset = Copy_IRQ / WORD_LENGTH_BITS;
    u8 Local_BitOffset = Copy_IRQ % WORD_LENGTH_BITS;
    SET_BIT(NVIC->ICER[Local_RegOffset], Local_BitOffset);

    return E_OK;
}

ErrorState_t Nvic_SetPendingIRQ(Nvic_IRQn_t Copy_IRQ){
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;

    u8 Local_RegOffset = Copy_IRQ / WORD_LENGTH_BITS;
    u8 Local_BitOffset = Copy_IRQ % WORD_LENGTH_BITS;
    SET_BIT(NVIC->ISPR[Local_RegOffset], Local_BitOffset);

    return E_OK;
}

ErrorState_t Nvic_ClearPendingIRQ(Nvic_IRQn_t Copy_IRQ){
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;

    u8 Local_RegOffset = Copy_IRQ / WORD_LENGTH_BITS;
    u8 Local_BitOffset = Copy_IRQ % WORD_LENGTH_BITS;
    SET_BIT(NVIC->ICPR[Local_RegOffset], Local_BitOffset);

    return E_OK;
}

ErrorState_t Nvic_GetPendingIRQ(Nvic_IRQn_t Copy_IRQ, bool *pState){
    if(pState == NULL)
        return E_NULL_POINTER;
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;

    u8 Local_RegOffset = Copy_IRQ / WORD_LENGTH_BITS;
    u8 Local_BitOffset = Copy_IRQ % WORD_LENGTH_BITS;
    *pState = GET_BIT(NVIC->ISPR[Local_RegOffset], Local_BitOffset);

    return E_OK;
}

ErrorState_t Nvic_GetActive(Nvic_IRQn_t Copy_IRQ, bool *pState){
    if(pState == NULL)
        return E_NULL_POINTER;
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;

    u8 Local_RegOffset = Copy_IRQ / WORD_LENGTH_BITS;
    u8 Local_BitOffset = Copy_IRQ % WORD_LENGTH_BITS;
    *pState = GET_BIT(NVIC->IABR[Local_RegOffset], Local_BitOffset);

    return E_OK;
}

// the default is XXXX
ErrorState_t Nvic_SetPriorityGrouping(Nvic_PrioGroup_t Copy_PrioGroup)
{
    if(!NVIC_IS_PRIOGROUP(Copy_PrioGroup))
        return E_WRONG_OPTION;

    u32 Local_RegVal;
    /* read old register configuration */
    Local_RegVal  =  SCB->AIRCR; 
    /* clear bits to change */
    Local_RegVal &= ~((u32) (SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); 
    /* Insert write key and priority group */
    Local_RegVal |=  ((u32)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) | (Copy_PrioGroup << SCB_AIRCR_PRIGROUP_Pos);
    SCB->AIRCR =  Local_RegVal;

    return E_OK;
}

ErrorState_t Nvic_SetPriority(Nvic_IRQn_t Copy_IRQ, u8 Copy_Prio){
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;
    if(!NVIC_IS_PRIO(Copy_Prio))
        return E_WRONG_OPTION;

    u8 Local_ByteOffset = Copy_IRQ;
    NVIC->IPR[Local_ByteOffset] = Copy_Prio << 4U;

    return E_OK;
}

ErrorState_t Nvic_GetPriority(Nvic_IRQn_t Copy_IRQ, u8 *pPrio){
    if(pPrio == NULL)
        return E_NULL_POINTER;
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;

    u8 Local_ByteOffset = Copy_IRQ;
    *pPrio = NVIC->IPR[Local_ByteOffset] >> 4U;

    return E_OK;
}



ErrorState_t Nvic_GenerateInterrupt(Nvic_IRQn_t Copy_IRQ){
    if(!NVIC_IS_IRQN(Copy_IRQ))
        return E_WRONG_OPTION;

    NVIC->STIR = Copy_IRQ;

    return E_OK;
}

/**********************************************************************************************************************
 *  END OF FILE: Nvic_Program.c
 *********************************************************************************************************************/
