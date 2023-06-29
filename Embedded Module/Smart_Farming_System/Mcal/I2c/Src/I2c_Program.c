/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  I2c_Program.c
 *		  Layer:  Mcal
 *       Module:  I2c
 *		Version:  1.00
 *
 *  Description:  Implementation of the I2c module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Bit_Math.h"
#include "STM32F429xx.h"

#include "I2c_Config.h"
#include "I2c_Interface.h"
#include "I2c_Private.h"
#include "I2c_Types.h"
#include "SysTick_Interface.h"

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static I2c_RegDef_t *I2cx[I2C_NUM] = {I2C1, I2C2, I2C3};

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
// move these definition to a system-wide header file.
#define SYSTEM_CLK 16
#define SYSTEM_AHB_PRESCALER 1
#define SYSTEM_APB_PRESCALER 1
#define SYSTEM_APB1_CLK                                                        \
  (SYSTEM_CLK / SYSTEM_AHB_PRESCALER / SYSTEM_APB_PRESCALER)

/******************************************************************************
 * \Syntax          : static void I2c_Reset(I2c_Handle_t* hi2c)

 * \Description     : Reset peripheral register to default values.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : hi2c : handle to a I2c instance
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/

static void I2c_Reset(I2c_Handle_t *hi2c) {
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];
  pI2cx->CR1 |= I2C_CR1_SWRST;
  pI2cx->CR1 &= ~I2C_CR1_SWRST;
}

/******************************************************************************
 * \Syntax          : static void I2c_ClearAddressFlag(I2c_Handle_t *hi2c)

 * \Description     : Implements required sequence clear the address flag
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : hi2c : handle to a I2c instance
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/

static void I2c_ClearAddressFlag(I2c_Handle_t *hi2c) {
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  volatile u32 tmpreg = 0x00U;
  tmpreg = pI2cx->SR1;
  tmpreg = pI2cx->SR2;
  (void)tmpreg; // prevents warnings
}

/******************************************************************************
 * \Syntax          : static ErrorState_t I2c_IsAcknowledgeFailed(I2c_Handle_t
 *hi2c)

 * \Description     : Checks if master received a NACK
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : hi2c : handle to a I2c instance
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t I2c_IsAcknowledgeFailed(I2c_Handle_t *hi2c) {
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];
  if (I2c_GetFlag(hi2c, I2C_FLAG_AF) == SET) {
    /* Clear NACKF Flag by writing 0 */
    pI2cx->SR1 = ~(I2C_FLAG_AF & I2C_FLAG_MSK);

    hi2c->State = I2C_STATE_READY;
    hi2c->Mode = I2C_MODE_NONE;
    hi2c->ErrorCode |= I2C_ERROR_AF;

    /* Process Unlocked */
    hi2c->Lock = UNLOCKED;
    return E_NOK;
  }
  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t
 I2c_WaitOnFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Flag, u8 Copy_Status,
 u32 Copy_Timeout, u32 Copy_Tickstart)

 * \Description     : Waits on a flag with a particular state till it either
 change state or times out.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_Flag : the flag
 *                  Copy_Status : the flag state to poll over.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/

static ErrorState_t I2c_WaitOnFlagUntilTimeout(I2c_Handle_t *hi2c,
                                               u32 Copy_Flag, u8 Copy_Status,
                                               u32 Copy_Timeout,
                                               u32 Copy_Tickstart) {
  /* Wait until flag is set */
  while (I2c_GetFlag(hi2c, Copy_Flag) == Copy_Status) {
    /* Check for the Timeout */
    if (Copy_Timeout != SYSTICK_MAX_DELAY) {
      if (((SysTick_GetTick() - Copy_Tickstart) > Copy_Timeout) ||
          (Copy_Timeout == 0U)) {
        hi2c->State = I2C_STATE_READY;
        hi2c->Mode = I2C_MODE_NONE;
        hi2c->ErrorCode |= I2C_ERROR_TIMEOUT;

        /* Process Unlocked */
        hi2c->Lock = UNLOCKED;

        return E_NOK;
      }
    }
  }
  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t
 I2c_WaitOnMasterAddressFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Flag, u32
 Copy_Timeout, u32 Copy_Tickstart)

 * \Description     : Master waits on the address flag until timeout.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_Flag : the flag (ADD10, ADD)
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t
I2c_WaitOnMasterAddressFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Flag,
                                        u32 Copy_Timeout, u32 Copy_Tickstart) {
  while (I2c_GetFlag(hi2c, Copy_Flag) == RESET) {
    /* Check if a NACK is detected */
    if (I2c_IsAcknowledgeFailed(hi2c) != E_OK) {
      return E_NOK;
    }

    /* Check for the Timeout */
    if (Copy_Timeout != SYSTICK_MAX_DELAY) {
      if (((SysTick_GetTick() - Copy_Tickstart) > Copy_Timeout) ||
          (Copy_Timeout == 0U)) {
        hi2c->State = I2C_STATE_READY;
        hi2c->Mode = I2C_MODE_NONE;
        hi2c->ErrorCode |= I2C_ERROR_TIMEOUT;

        /* Process Unlocked */
        hi2c->Lock = UNLOCKED;

        return E_NOK;
      }
    }
  }
  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t
 I2c_WaitOnTXEFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Timeout, u32
 Copy_Tickstart)

 * \Description     : Master waits on the TXE flag until timeout.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t I2c_WaitOnTXEFlagUntilTimeout(I2c_Handle_t *hi2c,
                                                  u32 Copy_Timeout,
                                                  u32 Copy_Tickstart) {
  while (I2c_GetFlag(hi2c, I2C_FLAG_TXE) == RESET) {
    /* Check if a NACK is detected */
    if (I2c_IsAcknowledgeFailed(hi2c) != E_OK) {
      return E_NOK;
    }

    /* Check for the Timeout */
    if (Copy_Timeout != SYSTICK_MAX_DELAY) {
      if (((SysTick_GetTick() - Copy_Tickstart) > Copy_Timeout) ||
          (Copy_Timeout == 0U)) {
        hi2c->State = I2C_STATE_READY;
        hi2c->Mode = I2C_MODE_NONE;
        hi2c->ErrorCode |= I2C_ERROR_TIMEOUT;

        /* Process Unlocked */
        hi2c->Lock = UNLOCKED;

        return E_NOK;
      }
    }
  }
  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t
 I2c_WaitOnBTFFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Timeout, u32
 Copy_Tickstart)

 * \Description     : Waits on the BTF flag until timeout.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t I2c_WaitOnBTFFlagUntilTimeout(I2c_Handle_t *hi2c,
                                                  u32 Copy_Timeout,
                                                  u32 Copy_Tickstart) {
  while (I2c_GetFlag(hi2c, I2C_FLAG_BTF) == RESET) {
    /* Check if a NACK is detected */
    if (I2c_IsAcknowledgeFailed(hi2c) != E_OK) {
      return E_NOK;
    }

    /* Check for the Timeout */
    if (Copy_Timeout != SYSTICK_MAX_DELAY) {
      if (((SysTick_GetTick() - Copy_Tickstart) > Copy_Timeout) ||
          (Copy_Timeout == 0U)) {
        hi2c->State = I2C_STATE_READY;
        hi2c->Mode = I2C_MODE_NONE;
        hi2c->ErrorCode |= I2C_ERROR_TIMEOUT;

        /* Process Unlocked */
        hi2c->Lock = UNLOCKED;

        return E_NOK;
      }
    }
  }
  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t
 I2c_WaitOnRXNEFlagUntilTimeout(I2c_Handle_t *hi2c, u32 Copy_Timeout, u32
 Copy_Tickstart)


 * \Description     : Waits on the RxNE flag until timeout.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t I2c_WaitOnRXNEFlagUntilTimeout(I2c_Handle_t *hi2c,
                                                   u32 Copy_Timeout,
                                                   u32 Copy_Tickstart) {

  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  while (I2c_GetFlag(hi2c, I2C_FLAG_RXNE) == RESET) {

    /* Check if a STOPF is detected (In case of a slave) */
    if (I2c_GetFlag(hi2c, I2C_FLAG_STOPF) == SET) {
      /* Clear STOP Flag */
      pI2cx->SR1 &= ~(I2C_FLAG_STOPF & I2C_FLAG_MSK);

      hi2c->State = I2C_STATE_READY;
      hi2c->Mode = I2C_MODE_NONE;
      hi2c->ErrorCode |= I2C_ERROR_NONE;

      /* Process Unlocked */
      hi2c->Lock = UNLOCKED;
      return E_NOK;
    }

    /* Check for the Timeout */
    if (Copy_Timeout != SYSTICK_MAX_DELAY) {
      if (((SysTick_GetTick() - Copy_Tickstart) > Copy_Timeout) ||
          (Copy_Timeout == 0U)) {
        hi2c->State = I2C_STATE_READY;
        hi2c->Mode = I2C_MODE_NONE;
        hi2c->ErrorCode |= I2C_ERROR_TIMEOUT;

        /* Process Unlocked */
        hi2c->Lock = UNLOCKED;

        return E_NOK;
      }
    }
  }

  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t I2c_MasterRequestWrite(I2c_Handle_t
 *hi2c, u16 Copy_DevAddress, u32 Copy_Timeout, u32 Copy_Tickstart)

 * \Description     : Handles the procedure when master tries to write to a
 slave.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_DevAddress : The slave address.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t I2c_MasterRequestWrite(I2c_Handle_t *hi2c,
                                           u16 Copy_DevAddress,
                                           u32 Copy_Timeout,
                                           u32 Copy_Tickstart) {
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Generate Start */
  SET_BIT(pI2cx->CR1, I2C_CR1_START_Pos);

  /* Wait until SB flag is set */
  if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Copy_Timeout,
                                 Copy_Tickstart) != E_OK) {
    hi2c->ErrorCode = I2C_WRONG_START;
    return E_TIME_OUT;
  }

  if (hi2c->Config.AddressingMode == I2C_ADDRESSINGMODE_7BIT) {
    /* Send slave address */
    pI2cx->DR = Copy_DevAddress & ~(1U << 0);
  } else {
    /* Send header of slave address */
    pI2cx->DR = I2C_10BIT_HEADER_WRITE(Copy_DevAddress);

    /* Wait until ADD10 flag is set */
    if (I2c_WaitOnMasterAddressFlagUntilTimeout(
            hi2c, I2C_FLAG_ADD10, Copy_Timeout, Copy_Tickstart) != E_OK) {
      return E_TIME_OUT;
    }

    /* Send slave address */
    pI2cx->DR = I2C_10BIT_ADDRESS(Copy_DevAddress);
  }

  /* Wait until ADDR flag is set */
  if (I2c_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Copy_Timeout,
                                              Copy_Tickstart) != E_OK) {
    return E_TIME_OUT;
  }

  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t I2c_MasterRequestRead(I2c_Handle_t
 *hi2c, u16 Copy_DevAddress, u32 Copy_Timeout, u32 Copy_Tickstart)

 * \Description     : Handles the procedure when master tries to read from a
 slave.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance.
 *                  Copy_DevAddress : The slave address.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t I2c_MasterRequestRead(I2c_Handle_t *hi2c,
                                          u16 Copy_DevAddress, u32 Copy_Timeout,
                                          u32 Copy_Tickstart) {

  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Enable Acknowledge */
  SET_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

  /* Generate Start */
  SET_BIT(pI2cx->CR1, I2C_CR1_START_Pos);

  /* Wait until SB flag is set */
  if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Copy_Timeout,
                                 Copy_Tickstart) != E_OK) {
    if ((pI2cx->CR1 & I2C_CR1_START) == I2C_CR1_START) {
      hi2c->ErrorCode = I2C_WRONG_START;
    }
    return E_TIME_OUT;
  }

  if (hi2c->Config.AddressingMode == I2C_ADDRESSINGMODE_7BIT) {
    /* Send slave address */
    pI2cx->DR = Copy_DevAddress | (1U << 0);
  } else {
    /* Send header of slave address */
    pI2cx->DR = I2C_10BIT_HEADER_WRITE(Copy_DevAddress);

    /* Wait until ADD10 flag is set */
    if (I2c_WaitOnMasterAddressFlagUntilTimeout(
            hi2c, I2C_FLAG_ADD10, Copy_Timeout, Copy_Tickstart) != E_OK) {
      return E_NOK;
    }

    /* Send slave address */
    pI2cx->DR = I2C_10BIT_ADDRESS(Copy_DevAddress);

    /* Wait until ADDR flag is set */
    if (I2c_WaitOnMasterAddressFlagUntilTimeout(
            hi2c, I2C_FLAG_ADDR, Copy_Timeout, Copy_Tickstart) != E_OK) {
      return E_NOK;
    }

    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);

    /* Generate Restart */
    SET_BIT(pI2cx->CR1, I2C_CR1_START_Pos);

    /* Wait until SB flag is set */
    if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Copy_Timeout,
                                   Copy_Tickstart) != E_OK) {
      if ((pI2cx->CR1 & I2C_CR1_START) == I2C_CR1_START) {
        hi2c->ErrorCode = I2C_WRONG_START;
      }
      return E_TIME_OUT;
    }

    /* Send header of slave address */
    pI2cx->DR = I2C_10BIT_HEADER_READ(Copy_DevAddress);
  }

  /* Wait until ADDR flag is set */
  if (I2c_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Copy_Timeout,
                                              Copy_Tickstart) != E_OK) {
    return E_NOK;
  }

  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t I2c_RequestMemoryWrite(I2c_Handle_t
 *hi2c, u16 Copy_DevAddress, u16 Copy_MemAddress, u16 Copy_MemAddSize, u32
 Copy_Timeout, u32 Copy_Tickstart)

 * \Description     : Handles the procedure when master tries to write to a
 specfic memeory location inside of a slave.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance.
 *                  Copy_DevAddress : The slave address.
 *                  Copy_MemAddress : The address of the memeory location.
 *                  Copy_MemAddSize : The size of the address.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t
I2c_RequestMemoryWrite(I2c_Handle_t *hi2c, u16 Copy_DevAddress,
                       u16 Copy_MemAddress, u16 Copy_MemAddSize,
                       u32 Copy_Timeout, u32 Copy_Tickstart) {
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Generate Start */
  SET_BIT(pI2cx->CR1, I2C_CR1_START_Pos);

  /* Wait until SB flag is set */
  if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Copy_Timeout,
                                 Copy_Tickstart) != E_OK) {
    hi2c->ErrorCode = I2C_WRONG_START;
    return E_TIME_OUT;
  }

  /* Send slave address */
  pI2cx->DR = Copy_DevAddress & ~(1U << 0);

  /* Wait until ADDR flag is set */
  if (I2c_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Copy_Timeout,
                                              Copy_Tickstart) != E_OK) {
    return E_NOK;
  }

  /* Clear ADDR flag */
  I2c_ClearAddressFlag(hi2c);

  /* Wait until TXE flag is set */
  if (I2c_WaitOnTXEFlagUntilTimeout(hi2c, Copy_Timeout, Copy_Tickstart) !=
      E_OK) {
    if (hi2c->ErrorCode == I2C_ERROR_AF) {
      /* Generate Stop */
      SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
    }
    return E_NOK;
  }

  /* If Memory address size is 8Bit */
  if (Copy_MemAddSize == I2C_MEMADD_SIZE_8BIT) {
    /* Send Memory Address */
    pI2cx->DR = I2C_MEM_ADD_LSB(Copy_MemAddress);
  }
  /* If Memory address size is 16Bit */
  else {
    /* Send MSB of Memory Address */
    pI2cx->DR = I2C_MEM_ADD_MSB(Copy_MemAddress);

    /* Wait until TXE flag is set */
    if (I2c_WaitOnTXEFlagUntilTimeout(hi2c, Copy_Timeout, Copy_Tickstart) !=
        E_OK) {
      if (hi2c->ErrorCode == I2C_ERROR_AF) {
        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
      }
      return E_NOK;
    }

    /* Send LSB of Memory Address */
    pI2cx->DR = I2C_MEM_ADD_LSB(Copy_MemAddress);
  }

  return E_OK;
}

/******************************************************************************
 * \Syntax          : static ErrorState_t I2c_RequestMemoryRead(I2c_Handle_t
 *hi2c, u16 Copy_DevAddress, u16 Copy_MemAddress, u16 Copy_MemAddSize, u32
 Copy_Timeout, u32 Copy_Tickstart)

 * \Description     : Handles the procedure when master tries to read from a
 specfic memeory location inside of a slave.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance.
 *                  Copy_DevAddress : The slave address.
 *                  Copy_MemAddress : The address of the memeory location.
 *                  Copy_MemAddSize : The size of the address.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 *                  Copy_Tickstart : the initial value of the timer.
 *
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
static ErrorState_t I2c_RequestMemoryRead(I2c_Handle_t *hi2c,
                                          u16 Copy_DevAddress,
                                          u16 Copy_MemAddress,
                                          u16 Copy_MemAddSize, u32 Copy_Timeout,
                                          u32 Copy_Tickstart) {
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Enable Acknowledge */
  SET_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

  /* Generate Start */
  SET_BIT(pI2cx->CR1, I2C_CR1_START_Pos);

  /* Wait until SB flag is set */
  if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Copy_Timeout,
                                 Copy_Tickstart) != E_OK) {
    if ((pI2cx->CR1 & I2C_CR1_START) == I2C_CR1_START) {
      hi2c->ErrorCode = I2C_WRONG_START;
    }
    return E_TIME_OUT;
  }

  /* Send slave address */
  pI2cx->DR = I2C_7BIT_ADD_WRITE(Copy_DevAddress);

  /* Wait until ADDR flag is set */
  if (I2c_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Copy_Timeout,
                                              Copy_Tickstart) != E_OK) {
    return E_NOK;
  }

  /* Clear ADDR flag */
  I2c_ClearAddressFlag(hi2c);

  /* Wait until TXE flag is set */
  if (I2c_WaitOnTXEFlagUntilTimeout(hi2c, Copy_Timeout, Copy_Tickstart) !=
      E_OK) {
    if (hi2c->ErrorCode == I2C_ERROR_AF) {
      /* Generate Stop */
      SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
    }
    return E_NOK;
  }

  /* If Memory address size is 8Bit */
  if (Copy_MemAddSize == I2C_MEMADD_SIZE_8BIT) {
    /* Send Memory Address */
    pI2cx->DR = I2C_MEM_ADD_LSB(Copy_MemAddress);
  }
  /* If Memory address size is 16Bit */
  else {
    /* Send MSB of Memory Address */
    pI2cx->DR = I2C_MEM_ADD_MSB(Copy_MemAddress);

    /* Wait until TXE flag is set */
    if (I2c_WaitOnTXEFlagUntilTimeout(hi2c, Copy_Timeout, Copy_Tickstart) !=
        E_OK) {
      if (hi2c->ErrorCode == I2C_ERROR_AF) {
        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
      }
      return E_NOK;
    }

    /* Send LSB of Memory Address */
    pI2cx->DR = I2C_MEM_ADD_LSB(Copy_MemAddress);
  }

  /* Wait until TXE flag is set */
  if (I2c_WaitOnTXEFlagUntilTimeout(hi2c, Copy_Timeout, Copy_Tickstart) !=
      E_OK) {
    if (hi2c->ErrorCode == I2C_ERROR_AF) {
      /* Generate Stop */
      SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
    }
    return E_NOK;
  }

  /* Generate Restart */
  SET_BIT(pI2cx->CR1, I2C_CR1_START_Pos);

  /* Wait until SB flag is set */
  if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Copy_Timeout,
                                 Copy_Tickstart) != E_OK) {
    if ((pI2cx->CR1 & I2C_CR1_START) == I2C_CR1_START) {
      hi2c->ErrorCode = I2C_WRONG_START;
    }
    return E_TIME_OUT;
  }

  /* Send slave address */
  pI2cx->DR = I2C_7BIT_ADD_READ(Copy_DevAddress);

  /* Wait until ADDR flag is set */
  if (I2c_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Copy_Timeout,
                                              Copy_Tickstart) != E_OK) {
    return E_NOK;
  }

  return E_OK;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \syntax          : __attribute__((weak)) void Spi_LLInit(Spi_Handle_t *hi2c);
 * \description     : It takes care of the low level initilization for the
 *peripheral. Including: NVIC, RCC, GPIO, (DMA?). User implemnts this function
 *inside of the LLInit.c
 *
 * \sync\async      : synchronous
 * \reentrancy      : non reentrant
 * \parameters (in) : hi2c -> a handle for the Spi peripheral
 * \parameters (out): None
 * \return value:   : void
 *******************************************************************************/
__attribute__((weak)) void I2c_LLInit(I2c_Handle_t *hi2c) {
  (void)hi2c; // to avoid warnings
  return;
}

/******************************************************************************
 * \Syntax          : ErrorState_t I2c_Init(I2c_Handle_t *hi2c)

 * \Description     : Initializes the i2c peripheral with the given
 configurations.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : hi2c : handle to a I2c instance
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t I2c_Init(I2c_Handle_t *hi2c) {
  /* If not initialized before */
  if (hi2c->State == I2C_STATE_RESET) {
    /* Initialize low level resouces */
    I2c_LLInit(hi2c);
  }

  /* Force update of peripheral state (I2c is Busy re/initializing) */
  hi2c->State = I2C_STATE_BUSY;

  /* Disable peripheral before configuring it */
  I2c_Disable(hi2c);

  /* Reset peripheral */
  I2c_Reset(hi2c);

  /* variable to hold the register definition of the i2c */
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Configure the peripheral */
  MODIFY_REG(pI2cx->CR1,
             hi2c->Config.GeneralCallMode | hi2c->Config.NoStretchMode,
             I2C_CR1_ENGC | I2C_CR1_NOSTRETCH);
  MODIFY_REG(pI2cx->CR2, SYSTEM_APB1_CLK, I2C_CR2_FREQ);
  MODIFY_REG(
      pI2cx->OAR1, (hi2c->Config.AddressingMode | hi2c->Config.OwnAddress1),
      (I2C_OAR1_ADDMODE | I2C_OAR1_ADD8_9 | I2C_OAR1_ADD1_7 | I2C_OAR1_ADD0));
  MODIFY_REG(pI2cx->OAR2,
             (hi2c->Config.DualAddressMode | hi2c->Config.OwnAddress2),
             (I2C_OAR2_ENDUAL | I2C_OAR2_ADD2));
  MODIFY_REG(pI2cx->CCR,
             I2C_SPEED(SYSTEM_APB1_CLK * 1000000, hi2c->Config.ClockSpeed,
                       hi2c->Config.DutyCycle),
             (I2C_CCR_FS | I2C_CCR_DUTY | I2C_CCR_CCR));
  MODIFY_REG(pI2cx->TRISE,
             I2C_RISE_TIME(SYSTEM_APB1_CLK, hi2c->Config.ClockSpeed),
             I2C_TRISE_TRISE);

  /* Enable peripheral after configuring it */
  I2c_Enable(hi2c);

  /* Peripheral is initialized */
  hi2c->State = I2C_STATE_READY;
  hi2c->Mode = I2C_MODE_NONE;
  hi2c->Lock = UNLOCKED;

  return E_OK;
}

/******************************************************************************
 * \Syntax          : ErrorState_t I2c_Master_Transmit(I2c_Handle_t *hi2c, u16
 Copy_DevAddress, u8 *pData, u16 Copy_Size, u32 Copy_Timeout)

 * \Description     : Master transmits data to a slave.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_DevAddress : The slave address
 *                  pData : a buffer containing the data to be sent.
 *                  Copy_Size : Number of bytes inside of the buffer to be sent.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t I2c_Master_Transmit(I2c_Handle_t *hi2c, u16 Copy_DevAddress,
                                 u8 *pData, u16 Copy_Size, u32 Copy_Timeout) {
  /* Init tickstart for timeout management*/
  u32 Local_Tickstart = SysTick_GetTick();

  /* lock resource */
  if (hi2c->Lock == LOCKED) {
    return E_BUSY;
  } else {
    hi2c->Lock = LOCKED;
  }

  /* Make sure peripheral is ready */
  if (hi2c->State != I2C_STATE_READY)
    return E_BUSY;
  if (I2c_GetFlag(hi2c, I2C_FLAG_BUSY))
    return E_BUSY;

  /* variable to hold the register definition of the i2c */
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Enable the I2c if not already enabled */
  if ((pI2cx->CR1 & I2C_CR1_PE) != I2C_CR1_PE) {
    I2c_Enable(hi2c);
  }

  /* Clear POS bit (1 byte receiption) */
  CLR_BIT(pI2cx->CR1, I2C_CR1_POS_Pos);

  /* Update peripheral state */
  hi2c->State = I2C_STATE_BUSY_TX;
  hi2c->Mode = I2C_MODE_MASTER;
  hi2c->ErrorCode = I2C_ERROR_NONE;

  /* Set the transaction information */
  hi2c->pBuffPtr = pData;
  hi2c->XferCount = Copy_Size;
  hi2c->XferSize = Copy_Size;

  /* Send Slave Address */
  if (I2c_MasterRequestWrite(hi2c, Copy_DevAddress, Copy_Timeout,
                             Local_Tickstart) != E_OK) {
    return E_NOK;
  }

  /* Clear ADDR flag */
  I2c_ClearAddressFlag(hi2c);

  while (hi2c->XferCount > 0U) {
    /* Wait until TXE flag is set */
    if (I2c_WaitOnTXEFlagUntilTimeout(hi2c, Copy_Timeout, Local_Tickstart) !=
        E_OK) {
      if (hi2c->ErrorCode == I2C_ERROR_AF) {
        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
      }
      return E_NOK;
    }

    /* Write data to DR */
    pI2cx->DR = *hi2c->pBuffPtr;

    /* Increment Buffer pointer */
    hi2c->pBuffPtr++;

    /* Update counter */
    hi2c->XferCount--;

    if ((I2c_GetFlag(hi2c, I2C_FLAG_BTF) == SET) && (hi2c->XferSize != 0U)) {
      /* Write data to DR */
      pI2cx->DR = *hi2c->pBuffPtr;

      /* Increment Buffer pointer */
      hi2c->pBuffPtr++;

      /* Update counter */
      hi2c->XferCount--;
    }

    /* Wait until BTF flag is set */
    if (I2c_WaitOnBTFFlagUntilTimeout(hi2c, Copy_Timeout, Local_Tickstart) !=
        E_OK) {
      if (hi2c->ErrorCode == I2C_ERROR_AF) {
        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
      }
      return E_NOK;
    }
  }

  /* Generate Stop */
  SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);

  /* Process Unlocked */
  hi2c->Lock = UNLOCKED;
  hi2c->State = I2C_STATE_READY;
  hi2c->Mode = I2C_MODE_NONE;

  return E_OK;
}

/******************************************************************************
 * \Syntax          : ErrorState_t I2c_Mem_Write(I2c_Handle_t *hi2c, u16
 Copy_DevAddress, u16 Copy_MemAddress, u16 Copy_MemAddSize, u8 *pData, u16
 Copy_Size, u32 Copy_Timeout)

 * \Description     : Master writes data to a specific memory location inside of
 a slave.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_DevAddress : The slave address
 *                  Copy_MemAddress : The address of the memeory location.
 *                  Copy_MemAddSize : The size of the address.
 *                  pData : a buffer containing the data to be sent.
 *                  Copy_Size : Number of bytes inside of the buffer to be sent.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t I2c_Mem_Write(I2c_Handle_t *hi2c, u16 Copy_DevAddress,
                           u16 Copy_MemAddress, u16 Copy_MemAddSize, u8 *pData,
                           u16 Copy_Size, u32 Copy_Timeout) {
  /* Init tickstart for timeout management*/
  u32 Local_Tickstart = SysTick_GetTick();

  /* lock resource */
  if (hi2c->Lock == LOCKED) {
    return E_BUSY;
  } else {
    hi2c->Lock = LOCKED;
  }

  /* Make sure peripheral is ready */
  if (hi2c->State != I2C_STATE_READY)
    return E_BUSY;
  if (I2c_GetFlag(hi2c, I2C_FLAG_BUSY))
    return E_BUSY;

  /* variable to hold the register definition of the i2c */
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Enable the I2c if not already enabled */
  if ((pI2cx->CR1 & I2C_CR1_PE) != I2C_CR1_PE) {
    I2c_Enable(hi2c);
  }

  /* Clear POS bit (1 byte receiption) */
  CLR_BIT(pI2cx->CR1, I2C_CR1_POS_Pos);

  /* Update peripheral state */
  hi2c->State = I2C_STATE_BUSY_TX;
  hi2c->Mode = I2C_MODE_MEM;
  hi2c->ErrorCode = I2C_ERROR_NONE;

  /* Set the transaction information */
  hi2c->pBuffPtr = pData;
  hi2c->XferCount = Copy_Size;
  hi2c->XferSize = Copy_Size;

  /* Send Slave Address and Memory address */
  if (I2c_RequestMemoryWrite(hi2c, Copy_DevAddress, Copy_MemAddress,
                             Copy_MemAddSize, Copy_Timeout,
                             Local_Tickstart) != E_OK) {
    return E_NOK;
  }

  while (hi2c->XferCount > 0U) {
    /* Wait until TXE flag is set */
    if (I2c_WaitOnTXEFlagUntilTimeout(hi2c, Copy_Timeout, Local_Tickstart) !=
        E_OK) {
      if (hi2c->ErrorCode == I2C_ERROR_AF) {
        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
      }
      return E_NOK;
    }

    /* Write data to DR */
    pI2cx->DR = *hi2c->pBuffPtr;

    /* Increment Buffer pointer */
    hi2c->pBuffPtr++;

    /* Update counter */
    hi2c->XferCount--;

    if ((I2c_GetFlag(hi2c, I2C_FLAG_BTF) == SET) && (hi2c->XferSize != 0U)) {
      /* Write data to DR */
      pI2cx->DR = *hi2c->pBuffPtr;

      /* Increment Buffer pointer */
      hi2c->pBuffPtr++;

      /* Update counter */
      hi2c->XferCount--;
    }

    /* Wait until BTF flag is set */
    if (I2c_WaitOnBTFFlagUntilTimeout(hi2c, Copy_Timeout, Local_Tickstart) !=
        E_OK) {
      if (hi2c->ErrorCode == I2C_ERROR_AF) {
        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
      }
      return E_NOK;
    }
  }

  /* Generate Stop */
  SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);

  /* Process Unlocked */
  hi2c->Lock = UNLOCKED;
  hi2c->State = I2C_STATE_READY;
  hi2c->Mode = I2C_MODE_NONE;

  return E_OK;
}

/******************************************************************************
 * \Syntax          : ErrorState_t I2c_Master_Receive(I2c_Handle_t *hi2c, u16
 Copy_DevAddress, u8 *pData, u16 Copy_Size, u32 Copy_Timeout)

 * \Description     : Master receives data from a slave.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_DevAddress : The slave address
 *                  pData : a buffer that will be filled with the data received.
 *                  Copy_Size : Number of bytes to be received.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t I2c_Master_Receive(I2c_Handle_t *hi2c, u16 Copy_DevAddress,
                                u8 *pData, u16 Copy_Size, u32 Copy_Timeout) {
  /* Init tickstart for timeout management*/
  u32 Local_Tickstart = SysTick_GetTick();

  /* lock resource */
  if (hi2c->Lock == LOCKED) {
    return E_BUSY;
  } else {
    hi2c->Lock = LOCKED;
  }

  /* Make sure peripheral is ready */
  if (hi2c->State != I2C_STATE_READY)
    return E_BUSY;
  if (I2c_GetFlag(hi2c, I2C_FLAG_BUSY))
    return E_BUSY;

  /* variable to hold the register definition of the i2c */
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Enable the I2c if not already enabled */
  if ((pI2cx->CR1 & I2C_CR1_PE) != I2C_CR1_PE) {
    I2c_Enable(hi2c);
  }

  /* Disable Pos */
  CLR_BIT(pI2cx->CR1, I2C_CR1_POS_Pos);

  hi2c->State = I2C_STATE_BUSY_RX;
  hi2c->Mode = I2C_MODE_MASTER;
  hi2c->ErrorCode = I2C_ERROR_NONE;

  /* Set the transaction information */
  hi2c->pBuffPtr = pData;
  hi2c->XferCount = Copy_Size;
  hi2c->XferSize = Copy_Size;

  /* Send Slave Address */
  if (I2c_MasterRequestRead(hi2c, Copy_DevAddress, Copy_Timeout,
                            Local_Tickstart) != E_OK) {
    return E_NOK;
  }

  if (hi2c->XferSize == 0U) {
    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);

    /* Generate Stop */
    SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
  } else if (hi2c->XferSize == 1U) {
    /* Disable Acknowledge */
    CLR_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);

    /* Generate Stop */
    SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
  } else if (hi2c->XferSize == 2U) {
    /* Disable Acknowledge */
    CLR_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

    /* Enable Pos (So that the nack is sent after the second byte not the first
     */
    SET_BIT(pI2cx->CR1, I2C_CR1_POS_Pos);

    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);
  } else {
    /* Enable Acknowledge */
    SET_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);
  }

  while (hi2c->XferCount > 0U) {
    if (hi2c->XferCount <= 3U) {
      /* One byte */
      if (hi2c->XferCount == 1U) {
        /* Wait until RXNE flag is set */
        if (I2c_WaitOnRXNEFlagUntilTimeout(hi2c, Copy_Timeout,
                                           Local_Tickstart) != E_OK) {
          return E_NOK;
        }

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;
      }
      /* Two bytes */
      else if (hi2c->XferCount == 2U) {
        /* Wait until BTF flag is set */
        if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Copy_Timeout,
                                       Local_Tickstart) != E_OK) {
          return E_NOK;
        }

        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;
      }
      /* 3 Last bytes */
      else {
        /* Wait until BTF flag is set */
        if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Copy_Timeout,
                                       Local_Tickstart) != E_OK) {
          return E_NOK;
        }

        /* Disable Acknowledge */
        CLR_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;

        /* Wait until BTF flag is set */
        if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Copy_Timeout,
                                       Local_Tickstart) != E_OK) {
          return E_NOK;
        }

        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;
      }
    } else {
      /* Wait until RXNE flag is set */
      if (I2c_WaitOnRXNEFlagUntilTimeout(hi2c, Copy_Timeout, Local_Tickstart) !=
          E_OK) {
        return E_NOK;
      }

      /* Read data from DR */
      *hi2c->pBuffPtr = (u8)pI2cx->DR;

      /* Increment Buffer pointer */
      hi2c->pBuffPtr++;

      /* Update counter */
      hi2c->XferCount--;

      if (I2c_GetFlag(hi2c, I2C_FLAG_BTF) == SET) {
        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;
      }
    }
  }

  /* Process Unlocked */
  hi2c->Lock = UNLOCKED;
  hi2c->State = I2C_STATE_READY;
  hi2c->Mode = I2C_MODE_NONE;

  return E_OK;
}

/******************************************************************************
 * \Syntax          : ErrorState_t I2c_Mem_Read(I2c_Handle_t *hi2c, u16
 Copy_DevAddress, u16 Copy_MemAddress, u16 Copy_MemAddSize, u8 *pData, u16
 Copy_Size, u16 Copy_Timeout)

 * \Description     : Master reads data from a specific memory location inside
 of a slave.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance
 *                  Copy_DevAddress : The slave address
 *                  Copy_MemAddress : The address of the memeory location.
 *                  Copy_MemAddSize : The size of the address.
 *                  pData : a buffer that will be filled with the data received.
 *                  Copy_Size : Number of bytes to be received.
 *                  Copy_Timeout : The duration of the timeout period in ms.
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t I2c_Mem_Read(I2c_Handle_t *hi2c, u16 Copy_DevAddress,
                          u16 Copy_MemAddress, u16 Copy_MemAddSize, u8 *pData,
                          u16 Copy_Size, u16 Copy_Timeout) {
  /* Init tickstart for timeout management*/
  u32 Local_Tickstart = SysTick_GetTick();

  /* lock resource */
  if (hi2c->Lock == LOCKED) {
    return E_BUSY;
  } else {
    hi2c->Lock = LOCKED;
  }

  /* Make sure peripheral is ready */
  if (hi2c->State != I2C_STATE_READY)
    return E_BUSY;
  if (I2c_GetFlag(hi2c, I2C_FLAG_BUSY))
    return E_BUSY;

  /* variable to hold the register definition of the i2c */
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* Enable the I2c if not already enabled */
  if ((pI2cx->CR1 & I2C_CR1_PE) != I2C_CR1_PE) {
    I2c_Enable(hi2c);
  }

  /* Disable Pos */
  CLR_BIT(pI2cx->CR1, I2C_CR1_POS_Pos);

  hi2c->State = I2C_STATE_BUSY_RX;
  hi2c->Mode = I2C_MODE_MEM;
  hi2c->ErrorCode = I2C_ERROR_NONE;

  /* Prepare transfer parameters */
  hi2c->pBuffPtr = pData;
  hi2c->XferCount = Copy_Size;
  hi2c->XferSize = Copy_Size;

  /* Send Slave Address and Memory Address */
  if (I2c_RequestMemoryRead(hi2c, Copy_DevAddress, Copy_MemAddress,
                            Copy_MemAddSize, Copy_Timeout,
                            Local_Tickstart) != E_OK) {
    return E_NOK;
  }

  if (hi2c->XferSize == 0U) {
    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);

    /* Generate Stop */
    SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
  } else if (hi2c->XferSize == 1U) {
    /* Disable Acknowledge */
    CLR_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);

    /* Generate Stop */
    SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);
  } else if (hi2c->XferSize == 2U) {
    /* Disable Acknowledge */
    CLR_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

    /* Enable Pos (So that the nack is sent after the second byte not the first
     */
    SET_BIT(pI2cx->CR1, I2C_CR1_POS_Pos);

    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);
  } else {
    /* Enable Acknowledge */
    SET_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

    /* Clear ADDR flag */
    I2c_ClearAddressFlag(hi2c);
  }

  while (hi2c->XferCount > 0U) {
    if (hi2c->XferCount <= 3U) {
      /* One byte */
      if (hi2c->XferCount == 1U) {
        /* Wait until RXNE flag is set */
        if (I2c_WaitOnRXNEFlagUntilTimeout(hi2c, Copy_Timeout,
                                           Local_Tickstart) != E_OK) {
          return E_NOK;
        }

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;
      }
      /* Two bytes */
      else if (hi2c->XferCount == 2U) {
        /* Wait until BTF flag is set */
        if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Copy_Timeout,
                                       Local_Tickstart) != E_OK) {
          return E_NOK;
        }

        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;
      }
      /* 3 Last bytes */
      else {
        /* Wait until BTF flag is set */
        if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Copy_Timeout,
                                       Local_Tickstart) != E_OK) {
          return E_NOK;
        }

        /* Disable Acknowledge */
        CLR_BIT(pI2cx->CR1, I2C_CR1_ACK_Pos);

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;

        /* Wait until BTF flag is set */
        if (I2c_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Copy_Timeout,
                                       Local_Tickstart) != E_OK) {
          return E_NOK;
        }

        /* Generate Stop */
        SET_BIT(pI2cx->CR1, I2C_CR1_STOP_Pos);

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;

        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;
      }
    } else {
      /* Wait until RXNE flag is set */
      if (I2c_WaitOnRXNEFlagUntilTimeout(hi2c, Copy_Timeout, Local_Tickstart) !=
          E_OK) {
        return E_NOK;
      }

      /* Read data from DR */
      *hi2c->pBuffPtr = (u8)pI2cx->DR;

      /* Increment Buffer pointer */
      hi2c->pBuffPtr++;

      /* Update counter */
      hi2c->XferCount--;

      if (I2c_GetFlag(hi2c, I2C_FLAG_BTF) == SET) {
        /* Read data from DR */
        *hi2c->pBuffPtr = (u8)pI2cx->DR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        /* Update counter */
        hi2c->XferCount--;
      }
    }
  }

  /* Process Unlocked */
  hi2c->Lock = UNLOCKED;
  hi2c->State = I2C_STATE_READY;
  hi2c->Mode = I2C_MODE_NONE;

  return E_OK;
}

/******************************************************************************
 * \Syntax          : u8 I2c_GetFlag(I2c_Handle_t *hi2c, I2c_Flag_t Copy_Flag)

 * \Description     : Get the state of a particular flag inside of the I2c.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance.
 *                  Copy_Flag : The flag we want to check.
 * \Parameters (out): None
 * \Return value:   : u8
 *******************************************************************************/
u8 I2c_GetFlag(I2c_Handle_t *hi2c, I2c_Flag_t Copy_Flag) {
  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];

  /* This means the flag is in SR1 */
  if ((u8)(Copy_Flag >> 16U) == 0x01U) {
    if ((pI2cx->SR1 & (Copy_Flag & I2C_FLAG_MSK)) ==
        (Copy_Flag & I2C_FLAG_MSK)) {
      return SET;
    } else {
      return RESET;
    }
  }
  /* This means the flag is in SR2 */
  else {
    if ((pI2cx->SR2 & (Copy_Flag & I2C_FLAG_MSK)) ==
        (Copy_Flag & I2C_FLAG_MSK)) {
      return SET;
    } else {
      return RESET;
    }
  }
}

/******************************************************************************
 * \Syntax          : void I2c_Enable(I2c_Handle_t* hi2c)

 * \Description     : Enable I2c.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance.
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void I2c_Enable(I2c_Handle_t *hi2c) {

  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];
  SET_BIT(pI2cx->CR1, I2C_CR1_PE_Pos);
}

/******************************************************************************
 * \Syntax          : void I2c_Disable(I2c_Handle_t* hi2c)

 * \Description     : Disable I2c.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) :
 *                  hi2c : handle to a I2c instance.
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void I2c_Disable(I2c_Handle_t *hi2c) {

  I2c_RegDef_t *pI2cx = I2cx[hi2c->Id];
  CLR_BIT(pI2cx->CR1, I2C_CR1_PE_Pos);
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
