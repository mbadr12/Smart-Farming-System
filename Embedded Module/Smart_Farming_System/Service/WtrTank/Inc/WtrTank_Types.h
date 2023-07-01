/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  WtrTank_Types.c
 *		  Layer:  Service
 *       Module:  WtrTank
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the types used to configure a water tank
 *  
 *********************************************************************************************************************/

#ifndef WTRTANK_TYPES_H
#define WTRTANK_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpio_Types.h"
#include "Exti_Types.h"

#include "Switch_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* High/Low level switch(HLS/LLS) initial state type */
typedef enum
{
    WTRTANK_SWITCH_NORMALLY_CLOSED=0,
    WTRTANK_SWITCH_NORMALLY_OPENED,
} WtrTank_SwitchInitialState_t;

/* Switch state type */
typedef enum
{
    WTRTANK_EMPTY=0,
    WTRTANK_FULL,
    WTRTANK_STANDBY
} WtrTank_State_t;

typedef enum
{
    WTRTANK_SWITCH_INT_DISABLE=0,
    WTRTANK_SWITCH_INT_ENABLE
} WtrTank_SwitchIntEnable_t;

/* Water tank configuration structure */
typedef struct
{
    WtrTank_SwitchInitialState_t HlsInitState;
    WtrTank_SwitchInitialState_t LlsInitState;
    Gpio_PinId_t HlsPinId;
    Gpio_PinId_t LlsPinId;
    Switch_Pull_t HlsPullingType;
    Switch_Pull_t LlsPullingType;
    WtrTank_SwitchIntEnable_t HlsInterruptEnable;
    WtrTank_SwitchIntEnable_t LlsInterruptEnable;
    Exti_PinConfig_t *HlsExtiPinConfig;
    Exti_PinConfig_t *LlsExtiPinConfig;
} WtrTank_Config_t;

#endif /* WTRTANK_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: WtrTank_Types.h
 *********************************************************************************************************************/
