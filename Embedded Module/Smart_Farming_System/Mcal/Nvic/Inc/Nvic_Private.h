/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Nvic_Private.h
 *		  Layer:  Mcal
 *       Module:  Nvic
 *		Version:  1.00
 *	
 *  Description:  private header file for Nvic module
 *  
 *********************************************************************************************************************/

#ifndef NVIC_PRIVATE_H 
#define NVIC_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define NVIC_VECT_KEY 0x5FAU
#define SCB_AIRCR_VECTKEY_Msk (0xFFFFUL << 16U)
#define SCB_AIRCR_VECTKEY_Pos (16U)
#define SCB_AIRCR_PRIGROUP_Msk (7UL << 8U)
#define SCB_AIRCR_PRIGROUP_Pos (8U)

// used to check for errors
#define NVIC_IS_IRQN(val) (val >= -14 && val <= 90)
#define NVIC_IS_PRIO(val) (val >= 0 && val <= 15)
#define NVIC_IS_PRIOGROUP(val) (val >= 0 && val <= 4)
 
#endif  /* NVIC_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Nvic_Private.h
 *********************************************************************************************************************/
