/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Aht21b_Private.h
 *		  Layer:  Hal
 *       Module:  Aht21b
 *		Version:  1.0
 *	
 *  Description:  A header file that contains local macros and functions used only in the program file of the aht21b module and not needed outside the scope of this module.
 *  
 *********************************************************************************************************************/

#ifndef AHT21B_PRIVATE_H
#define AHT21B_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define SLAVE_ADDRESS_WITHOUT_REQUEST           0x38    /* 0b0111000x, x:for read/write request*/
#define SLAVE_ADDRESS_WITH_WRITE                0x70    /* 0b01110000, for write request*/
#define SLAVE_ADDRESS_WITH_READ                 0x71    /* 0b01110001, for read request*/

#define CALIBRATION_VALUE_CHECK                 0x18

#define TRIGGER_MEASUREMENT_COMMAND             0xAC
#define MEASUREMENT_COMMAND_PARAMETER0          0x33
#define MEASUREMENT_COMMAND_PARAMETER1          0x00

#define CALIBRATED                              1
#define UNCALIBRATED                            0

#define BUSY                                    1
#define IDLE                                    0

#define BUSY_INDICATION_BIT_POS                 7

#define TIMEOUT                                 0

#define SIGNAL_NUMBER_BYTES_CRC                 7
#define SIGNAL_NUMBER_BYTES_NO_CRC              6

#define CALLED                                  1
#define NOT_CALLED                              0

#define FIRST_BYTE                              0
#define SECOND_BYTE                             1
#define THIRD_BYTE                              2
#define FOURTH_BYTE                             3
#define FIFTH_BYTE                              4
#define SIXTH_BYTE                              5
#define SEVENTH_BYTE                            6

#define STATUS_BYTE                             FIRST_BYTE
#define CRC_BYTE                                SEVENTH_BYTE

#define ENABLED                                 1
#define DISABLED                                0

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static u8 CalculateCRC8(void)
* \Description     : Calculate the CRC8/MAXIM value
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : u8     Returns the CRC value
*******************************************************************************/
static u8 CalculateCRC8(void);

/******************************************************************************
* \Syntax          : static ErrorState_t ReadSignals(void)
* \Description     : Get both the temperature signal(S_T) and the relative humidity signal(S_RH) and CRC if needed, then store them in a local array
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
static ErrorState_t ReadSignals(void);

/******************************************************************************
* \Syntax          : static ErrorState_t InitRegs(u8 Copy_RegisterAddress)
* \Description     : Calibrate and initialize registers 0x1B, 0x1C and 0x1E
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_RegisterAddress   The address of the register to be initialize
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
static ErrorState_t InitRegs(u8 Copy_RegisterAddress);

#endif  /* AHT21B_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Aht21b_Private.h
 *********************************************************************************************************************/
