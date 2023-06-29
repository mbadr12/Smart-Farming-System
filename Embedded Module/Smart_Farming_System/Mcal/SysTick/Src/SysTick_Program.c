/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  SysTick_Program.c
 *		  Layer:  Mcal
 *       Module:  SysTick
 *		Version:  1.00
 *	
 *  Description:  implementation of the SysTick module.
 *  
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "SysTick_Interface.h"
#include "SysTick_Config.h"
#include "SysTick_Private.h"

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static volatile u32 SysTick_TickCount = 0;

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          :  void SysTick_Init(void)
 * \Description     : Initialize the system timer periferal

 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void SysTick_Init(SysTick_Config_t *pConfig) {
  /* Program the value in the STRRELOAD register with user define value */
  STK_LOAD = pConfig->ReloadValue;

  /* Clear the STCURRENT register by writing to it with any value*/
  STK_VAL = SYSTICK_STCURRENT_CLEAR;

  /* Configure STCTRL register for the required operation */
  /* 1. Choose the clock source for the system timer according to the user
   * configuration*/
  /* 2. Enable or Disable Interrupt according to the user configuration */
  STK_CTRL |= (pConfig->ClockSource << 2) | (pConfig->InterruptEnable << 1) ;

  /* 3. Enable The counter */
  STK_CTRL |= (1UL << 0);
}

/******************************************************************************
 * \Syntax          :  void SysTick_IncTick(void)
 * \Description     : Increments a local static variable by 1.
 *                  This function is called inside of the SysTick ISR.

 * \Sync\Async      : Synchronous
 * \Reentrancy      : non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void SysTick_IncTick(void){
    SysTick_TickCount++;
}

/******************************************************************************
 * \Syntax          :  u32 SysTick_GetTick(void)
 * \Description     : gets the current tick count. 

 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : u32
 *******************************************************************************/
u32 SysTick_GetTick(void){
    return SysTick_TickCount;
}

/******************************************************************************
 * \Syntax          :  u32 SysTick_Delay(u32 Copy_DelayMs)
 * \Description     :  blocking delay in ms.

 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : u32
 *******************************************************************************/
void SysTick_Delay(u32 Copy_DelayMs){
    u32 Local_InitialTick = SysTick_TickCount;
    while(SysTick_TickCount - Local_InitialTick < Copy_DelayMs);
}

/******************************************************************************
 * \Syntax          : void SysTick_Handler(void)
 * \Description     : SysTick ISR. 

 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void SysTick_Handler(void){
    SysTick_IncTick();
}
/**********************************************************************************************************************
 *  END OF FILE: SysTick_Program.c
 *********************************************************************************************************************/
