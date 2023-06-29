/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Switch_Types.c
 *		  Layer:  Hal
 *       Module:  Switch
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the types used to configure a switch
 *  
 *********************************************************************************************************************/

#ifndef SWITCH_TYPES_H
#define SWITCH_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Switch type */
typedef enum
{
    SWITCH_PERMANENT=0,
    SWITCH_TEMPORARY
} Switch_Type_t;

/* Switch pull type */
typedef enum
{
    SWITCH_PULL_UP=0,
    SWITCH_PULL_DOWN
} Switch_Pull_t;

/* Switch state type */
typedef enum
{
    SWITCH_PRESSED=0,
    SWITCH_NOT_PRESSED
} Switch_State_t;

/* Switch configuration structure */
typedef struct
{
    u8 Port;
    u8 Pin;
    Switch_Type_t SwitchType;
    Switch_Pull_t PullType;
} Switch_Config_t;

#endif /* SWITCH_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Switch_Types.h
 *********************************************************************************************************************/
