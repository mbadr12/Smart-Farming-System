/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  WtrTank_Config.c
 *		  Layer:  Service
 *       Module:  WtrTank
 *		Version:  1.0
 *	
 *  Description:  A header file that contains macros used by user to configure the water tank
 *  
 *********************************************************************************************************************/

#ifndef WTRTANK_CONFIG_H
#define WTRTANK_CONFIG_H

/* Choose:
    - The amount of time to needed debounce the tank's switches
                                                                                */
#define DEBOUNCING_TIME             150

/* Choose:
    - USED: To enable software debouncing
    - NOT_USED: To disable software debouncing, but you mist enable IS_PERMANENT_SWITCH_USED in switch driver
                                                                                */
#define SOFTWARE_DEBOUNCING 		USED

#endif /* WTRTANK_CONFIG_H */

/**********************************************************************************************************************
 *  END OF FILE: WtrTank_Config.h
 *********************************************************************************************************************/
