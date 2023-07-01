/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  LedGrid_Types.h
 *		  Layer:  Hal
 *       Module:  LedGrid
 *		Version:  1.0
 *	
 *  Description:  A header file that contains the API types of the LED grid module. And it includes standard types
 *  
 *********************************************************************************************************************/
#ifndef LEDGRID_TYPES_H
#define LEDGRID_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpio_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* LED grid current state value */
typedef enum
{
    LEDGRID_TURNED_OFF=0,
    LEDGRID_TURNED_ON
} LedGrid_State_t;

/* Switch Activation Value */
typedef enum
{
    LEDGRID_ACTIVE_LOW=0,
    LEDGRID_ACTIVE_HIGH
} LedGrid_Activation_t;

/* LED grid configuration structure */
typedef struct
{
    Gpio_PinId_t PinId;
    LedGrid_Activation_t ActivationType;
} LedGrid_Config_t;

#endif  /* LEDGRID_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: LedGrid_Types.h
 *********************************************************************************************************************/
