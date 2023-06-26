/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  I2c_Private.h
 *		  Layer:  Mcal
 *       Module:  I2c
 *		Version:  1.00
 *	
 *  Description:  Private header for the I2c Module     
 *  
 *********************************************************************************************************************/
#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H
#include "I2c_Types.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define I2C_MAX_DEVICE_ADRESS   ((1<<7) - 1)
#define I2C_7BIT_ADRESS_MSK     (0x7F << 1)
#define I2C_10BIT_ADRESS_MSK    (0x3FF)
#define I2C_MAX_FLAG
#define I2C_NUM 3
#define I2C_FLAG_MSK (0x0000ffffUL)
#define I2C_NO_OPTION_FRAME       0xFFFF0000U /*!< XferOptions default value */


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define I2C_CCR_CALCULATION(__PCLK__, __SPEED__, __COEFF__)     (((((__PCLK__) - 1U)/((__SPEED__) * (__COEFF__))) + 1U) & I2C_CCR_CCR)
#define I2C_RISE_TIME(__FREQRANGE__, __SPEED__)            (((__SPEED__) <= 100000U) ? ((__FREQRANGE__) + 1U) : ((((__FREQRANGE__) * 300U) / 1000U) + 1U))
#define I2C_SPEED_STANDARD(__PCLK__, __SPEED__)            ((I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 2U) < 4U)? 4U:I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 2U))
#define I2C_SPEED_FAST(__PCLK__, __SPEED__, __DUTYCYCLE__) (((__DUTYCYCLE__) == I2C_DUTYCYCLE_2)? I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 3U) : (I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 25U) | I2C_DUTYCYCLE_16_9))
#define I2C_SPEED(__PCLK__, __SPEED__, __DUTYCYCLE__)      (((__SPEED__) <= 100000U)? (I2C_SPEED_STANDARD((__PCLK__), (__SPEED__))) : \
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__)) & I2C_CCR_CCR) == 0U)? 1U : \
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__))) | I2C_CCR_FS))


/* Slave address + Read/Write bit */
#define I2C_7BIT_ADD_WRITE(ADDRESS)                    ((u8)((ADDRESS) & (u8)(~0x1UL)))
#define I2C_7BIT_ADD_READ(ADDRESS)                     ((u8)((ADDRESS) | 0x1UL))

#define I2C_10BIT_ADDRESS(ADDRESS)                     ((u8)((u16)((ADDRESS) & (u16)0x00FF)))
#define I2C_10BIT_HEADER_WRITE(ADDRESS)                ((u8)((u16)((u16)(((u16)((ADDRESS) & (u16)0x0300)) >> 7) | (u16)0x00F0)))
#define I2C_10BIT_HEADER_READ(ADDRESS)                 ((u8)((u16)((u16)(((u16)((ADDRESS) & (u16)0x0300)) >> 7) | (u16)(0x00F1))))


#define I2C_MEM_ADD_LSB(ADDRESS)                       ((u8)((u16)((ADDRESS) & (u16)0x00FF)))
#define I2C_MEM_ADD_MSB(ADDRESS)                       ((u8)((u16)(((u16)((ADDRESS) & (u16)0xFF00)) >> 8)))
/**********************************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES 
 *********************************************************************************************************************/

static void I2c_ClearAddressFlag(I2c_Handle_t *hi2c);
static ErrorState_t I2c_IsAcknowledgeFailed(I2c_Handle_t *hi2c);

/* Polling on flags */
static ErrorState_t I2c_WaitOnFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Flag, u8 Copy_Status, u32 Copy_Timeout, u32 Copy_Tickstart);
static ErrorState_t I2c_WaitOnMasterAddressFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Flag, u32 Copy_Timeout, u32 Copy_Tickstart);
static ErrorState_t I2c_WaitOnTXEFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Timeout, u32 Copy_Tickstart);
static ErrorState_t I2c_WaitOnBTFFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Timeout, u32 Copy_Tickstart);

/* Helper functions to implement IO operations */
static ErrorState_t I2c_MasterRequestWrite(I2c_Handle_t *hi2c, u16 Copy_DevAddress, u32 Copy_Timeout, u32 Copy_Tickstart);
static ErrorState_t I2c_MasterRequestRead(I2c_Handle_t *hi2c, u16 Copy_DevAddress, u32 Copy_Timeout, u32 Copy_Tickstart);
static ErrorState_t I2c_RequestMemoryWrite(I2c_Handle_t *hi2c, u16 Copy_DevAddress, u16 Copy_MemAddress, u16 Copy_MemAddSize, u32 Copy_Timeout, u32 Copy_Tickstart);
static ErrorState_t I2c_RequestMemoryRead(I2c_Handle_t *hi2c, u16 Copy_DevAddress, u16 Copy_MemAddress, u16 Copy_MemAddSize, u32 Copy_Timeout, u32 Copy_Tickstart);

#endif  /* I2C_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: I2c_Private.h
 *********************************************************************************************************************/
