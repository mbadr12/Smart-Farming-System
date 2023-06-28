/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  I2c_Types.h
 *		  Layer:  Mcal
 *       Module:  I2c
 *		Version:  1.00
 *	
 *  Description:  I2c driver API type definitions.     
 *  
 *********************************************************************************************************************/
#ifndef I2C_TYPES_H 
#define I2C_TYPES_H

/**********************************************************************************************************************
 * INCLUDES 
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Flag type definition */
#define I2C_FLAG_OVR                    0x00010800U
#define I2C_FLAG_AF                     0x00010400U
#define I2C_FLAG_ARLO                   0x00010200U
#define I2C_FLAG_BERR                   0x00010100U
#define I2C_FLAG_TXE                    0x00010080U
#define I2C_FLAG_RXNE                   0x00010040U
#define I2C_FLAG_STOPF                  0x00010010U
#define I2C_FLAG_ADD10                  0x00010008U
#define I2C_FLAG_BTF                    0x00010004U
#define I2C_FLAG_ADDR                   0x00010002U
#define I2C_FLAG_SB                     0x00010001U
#define I2C_FLAG_DUALF                  0x00100080U
#define I2C_FLAG_GENCALL                0x00100010U
#define I2C_FLAG_TRA                    0x00100004U
#define I2C_FLAG_BUSY                   0x00100002U
#define I2C_FLAG_MSL                    0x00100001U
typedef u32 I2c_Flag_t;


/** @defgroup I2C_duty_cycle_in_fast_mode I2C duty cycle in fast mode
  * @{
  */
#define I2C_DUTYCYCLE_2                 0x00000000U
#define I2C_DUTYCYCLE_16_9              I2C_CCR_DUTY
/**
  * @}
  */

/** @defgroup I2C_addressing_mode I2C addressing mode
  * @{
  */
#define I2C_ADDRESSINGMODE_7BIT         0x00004000U
#define I2C_ADDRESSINGMODE_10BIT        (I2C_OAR1_ADDMODE | 0x00004000U)
/**
  * @}
  */

/** @defgroup I2C_dual_addressing_mode  I2C dual addressing mode
  * @{
  */
#define I2C_DUALADDRESS_DISABLE        0x00000000U
#define I2C_DUALADDRESS_ENABLE         I2C_OAR2_ENDUAL
/**
  * @}
  */

/** @defgroup I2C_general_call_addressing_mode I2C general call addressing mode
  * @{
  */
#define I2C_GENERALCALL_DISABLE        0x00000000U
#define I2C_GENERALCALL_ENABLE         I2C_CR1_ENGC
/**
  * @}
  */

/** @defgroup I2C_nostretch_mode I2C nostretch mode
  * @{
  */
#define I2C_NOSTRETCH_DISABLE          0x00000000U
#define I2C_NOSTRETCH_ENABLE           I2C_CR1_NOSTRETCH
/**
  * @}
  */


/** @defgroup I2C_Error_Code_definition I2C Error Code definition
  * @brief  I2C Error Code definition
  * @{
  */
#define I2C_ERROR_NONE              0x00000000U    /*!< No error              */
#define I2C_ERROR_BERR              0x00000001U    /*!< BERR error            */
#define I2C_ERROR_ARLO              0x00000002U    /*!< ARLO error            */
#define I2C_ERROR_AF                0x00000004U    /*!< AF error              */
#define I2C_ERROR_OVR               0x00000008U    /*!< OVR error             */
#define I2C_ERROR_DMA               0x00000010U    /*!< DMA transfer error    */
#define I2C_ERROR_TIMEOUT           0x00000020U    /*!< Timeout Error         */
#define I2C_ERROR_SIZE              0x00000040U    /*!< Size Management error */
#define I2C_ERROR_DMA_PARAM         0x00000080U    /*!< DMA Parameter Error   */
#define I2C_ERROR_INVALID_CALLBACK  0x00000100U    /*!< Invalid Callback error */
#define I2C_WRONG_START             0x00000200U    /*!< Wrong start Error     */
/**
  * @}
  */

/** @defgroup I2C_XferOptions_definition I2C XferOptions definition
  * @{
  */
#define  I2C_FIRST_FRAME                0x00000001U
#define  I2C_FIRST_AND_NEXT_FRAME       0x00000002U
#define  I2C_NEXT_FRAME                 0x00000004U
#define  I2C_FIRST_AND_LAST_FRAME       0x00000008U
#define  I2C_LAST_FRAME_NO_STOP         0x00000010U
#define  I2C_LAST_FRAME                 0x00000020U

/* List of XferOptions in usage of :
 * 1- Restart condition in all use cases (direction change or not)
 */
#define  I2C_OTHER_FRAME                (0x00AA0000U)
#define  I2C_OTHER_AND_LAST_FRAME       (0xAA000000U)
/**
  * @}
  */


/** @defgroup I2C_Memory_Address_Size I2C Memory Address Size
  * @{
  */
#define I2C_MEMADD_SIZE_8BIT            0x00000001U
#define I2C_MEMADD_SIZE_16BIT           0x00000010U
/**
  * @}
  */

typedef enum{
    I2C_1=0,
    I2C_2,
    I2C_3
}I2c_Id_t;


typedef struct
{
  u32 ClockSpeed;       /*!< Specifies the clock frequency.
                                  This parameter must be set to a value lower than 400kHz */

  u32 DutyCycle;        /*!< Specifies the I2C fast mode duty cycle.
                                  This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

  u32 OwnAddress1;      /*!< Specifies the first device own address.
                                  This parameter can be a 7-bit or 10-bit address. */

  u32 AddressingMode;   /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
                                  This parameter can be a value of @ref I2C_addressing_mode */

  u32 DualAddressMode;  /*!< Specifies if dual addressing mode is selected.
                                  This parameter can be a value of @ref I2C_dual_addressing_mode */

  u32 OwnAddress2;      /*!< Specifies the second device own address if dual addressing mode is selected
                                  This parameter can be a 7-bit address. */

  u32 GeneralCallMode;  /*!< Specifies if general call mode is selected.
                                  This parameter can be a value of @ref I2C_general_call_addressing_mode */

  u32 NoStretchMode;    /*!< Specifies if nostretch mode is selected.
                                  This parameter can be a value of @ref I2C_nostretch_mode */

} I2c_Config_t;


typedef enum
{
  I2C_MODE_NONE               = 0x00U,   /*!< No I2C communication on going             */
  I2C_MODE_MASTER             = 0x10U,   /*!< I2C communication is in Master Mode       */
  I2C_MODE_SLAVE              = 0x20U,   /*!< I2C communication is in Slave Mode        */
  I2C_MODE_MEM                = 0x40U    /*!< I2C communication is in Memory Mode       */

} I2c_Mode_t;


typedef enum
{
  I2C_STATE_RESET             = 0x00U,   /*!< Peripheral is not yet Initialized         */
  I2C_STATE_READY             = 0x20U,   /*!< Peripheral Initialized and ready for use  */
  I2C_STATE_BUSY              = 0x24U,   /*!< An internal process is ongoing            */
  I2C_STATE_BUSY_TX           = 0x21U,   /*!< Data Transmission process is ongoing      */
  I2C_STATE_BUSY_RX           = 0x22U,   /*!< Data Reception process is ongoing         */
  I2C_STATE_LISTEN            = 0x28U,   /*!< Address Listen Mode is ongoing            */
  I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   /*!< Address Listen Mode and Data Transmission
                                             process is ongoing                         */
  I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   /*!< Address Listen Mode and Data Reception
                                             process is ongoing                         */
  I2C_STATE_ABORT             = 0x60U,   /*!< Abort user request ongoing                */
  I2C_STATE_TIMEOUT           = 0xA0U,   /*!< Timeout state                             */
  I2C_STATE_ERROR             = 0xE0U    /*!< Error                                     */

} I2c_State_t;
/* These states are used for previous satate */
#define I2C_STATE_MSK             ((u32)((u32)((u32)I2C_STATE_BUSY_TX | (u32)I2C_STATE_BUSY_RX) & (u32)(~((u32)I2C_STATE_READY)))) /*!< Mask State define, keep only RX and TX bits            */
#define I2C_STATE_NONE            ((u32)(I2C_MODE_NONE))                                                        /*!< Default Value */
#define I2C_STATE_MASTER_BUSY_TX  ((u32)(((u32)I2C_STATE_BUSY_TX & I2C_STATE_MSK) | (u32)I2C_MODE_MASTER))            /*!< Master Busy TX, combinaison of State LSB and Mode enum */
#define I2C_STATE_MASTER_BUSY_RX  ((u32)(((u32)I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (u32)I2C_MODE_MASTER))            /*!< Master Busy RX, combinaison of State LSB and Mode enum */
#define I2C_STATE_SLAVE_BUSY_TX   ((u32)(((u32)I2C_STATE_BUSY_TX & I2C_STATE_MSK) | (u32)I2C_MODE_SLAVE))             /*!< Slave Busy TX, combinaison of State LSB and Mode enum  */
#define I2C_STATE_SLAVE_BUSY_RX   ((u32)(((u32)I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (u32)I2C_MODE_SLAVE))             /*!< Slave Busy RX, combinaison of State LSB and Mode enum  */





typedef struct I2c_Handle_t{
    I2c_Id_t Id;
    I2c_Config_t Config;

    /* only one buffer is needed not like Spi where we had two. that's Because
     * I2c is half-duplex communication it will be using in all of it's apis one
     * buffer at a time. */
    u8 *pBuffPtr; 
    u16 XferSize;
    volatile u16 XferCount;

    /* process lock */
    Lock_t Lock; 

    /* the state of the peripheral */
    volatile I2c_State_t State;  

    /* note that here the mode is not inside of the config struct but 
     * inside of the handle. Because I2c doesn't really behave differently circuit-wise
     * whether it's operating in master or slave mode. So there's not really a Bit
     * that we need to set or reset to configure the peripheral as either of the modes.
     * The purpose of this variable is to carry the current mode of the peripheral. this
     * changes according to what api we use. */
    volatile I2c_Mode_t Mode; 

    /* Pointer to function that holds the Tx ISR */
    void (*TxISR)(struct I2c_Handle_t *Id);
    
    /* Pointer to function that holds the Rx ISR */
    void (*RxISR)(struct I2c_Handle_t *Id);

    /* Spi Tx Dma handle */

    /* Spi Rx Dma handle */

    /* Error code */
    volatile u32 ErrorCode;

} I2c_Handle_t;




#endif  /* I2C_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: I2c_Types.h
 *********************************************************************************************************************/
