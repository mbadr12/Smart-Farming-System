/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Switch_Config.c
 *		  Layer:  Hal
 *       Module:  Switch
 *		Version:  1.0
 *	
 *  Description:  A header file that contains macros used by user to configure the switch
 *  
 *********************************************************************************************************************/

#ifndef SWITCH_CONFIG_H
#define SWITCH_CONFIG_H

/* Choose:
    - 0: To disable software debouncing
    - 1: To enable software debouncing
                                                                                */
#define SOFTWARE_DEBOUNCING 		1

/* Choose:
    - 0: To choose wait & double check technique
                                                                                */
#define DEBOUNCING_TECHNIQUE 		0

/* Choose:
    - 0: If you are using a temporary switch, but make sure to enable software debouncing
    - 1: If you are using a permanent switch or no need to software debouncing
                                                                                */
#define IS_PERMANENT_SWITCH_USED 	0

#endif /* SWITCH_CONFIG_H */

/**********************************************************************************************************************
 *  END OF FILE: Switch_Config.h
 *********************************************************************************************************************/
