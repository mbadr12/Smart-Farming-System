/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Aht21b_Config.h
 *		  Layer:  Hal
 *       Module:  Aht21b
 *		Version:  1.0
 *	
 *  Description:  A header file that contains macros used by the user to configure the aht21b module.
 *  
 *********************************************************************************************************************/
#ifndef AHT21B_CONFIG_H
#define AHT21B_CONFIG_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Choose:
    - The timeout amount
                                                                                */
#define TIMEOUT_AMOUNT              1000

/* Choose:
    - ENABLED: To enable CRC(cyclic redundancy check)
    - DISABLED: To disable CRC(cyclic redundancy check)
                                                                                */
#define CRC_STATE                   DISABLED

/* Choose:
    - I2C_1: To connect the AHB21B to I2C number 1
    - I2C_2: To connect the AHB21B to I2C number 2
    - I2C_3: To connect the AHB21B to I2C number 3
                                                                                */
#define AHT21B_I2C                  I2C_3

#endif  /* AHT21B_CONFIG_H */

/**********************************************************************************************************************
 *  END OF FILE: Aht21b_Config.h
 *********************************************************************************************************************/
