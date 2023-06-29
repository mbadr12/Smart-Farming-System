/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud
 *	   	   File:  Aht21b_Program.c
 *		  Layer:  Hal
 *       Module:  Aht21b
 *		Version:  1.0
 *	
 *  Description: A Aht21b driver that read the temperature and relative humidity of the environment
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "SysTick_Interface.h"
#include "I2c_Interface.h"

#include "Aht21b_Interface.h"
#include "Aht21b_Private.h"
#include "Aht21b_Config.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

static u8 SignalsReceivingBuffer[7];

static u8 ReadSignalsNumberCalls = 0;

static I2c_Handle_t I2cHandle;
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static u8 CalculateCRC8(void)
* \Description     : Calculate the CRC8/MAXIM value with polynomial(X8 + X5 + X4 + 1)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : u8     Returns the CRC value
*******************************************************************************/
static u8 CalculateCRC8(void)
{
    u8 Local_CRC8Value = 0xFF;
    
    for (u8 ByteIndex = FIRST_BYTE; ByteIndex < CRC_BYTE; ByteIndex++)
    {
        Local_CRC8Value ^= (SignalsReceivingBuffer[ByteIndex]);

        for (u8 Counter = 8; Counter > 0; Counter--)
        {
            if (Local_CRC8Value & 0x80)
            {
                Local_CRC8Value = (Local_CRC8Value << 1) ^ 0x31;
            }
            else
            {
                Local_CRC8Value = (Local_CRC8Value << 1);
            }
        }
    }

    return Local_CRC8Value;
}

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
static ErrorState_t ReadSignals(void)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_StatusByte;
    u8 Local_TriggerMeasurement[3] = {TRIGGER_MEASUREMENT_COMMAND, MEASUREMENT_COMMAND_PARAMETER0, MEASUREMENT_COMMAND_PARAMETER1};
    u8 Local_SignalNumberBytes = SIGNAL_NUMBER_BYTES_NO_CRC;
    u16 Local_TimeoutAmount = TIMEOUT_AMOUNT;

    /* Read the CRC value if it is enabled */
#if CRC_STATE == ENABLED
    Local_SignalNumberBytes = SIGNAL_NUMBER_BYTES_CRC;
#endif

    /* Wait for 10 ms to send the measurement command(0xAC) */
    SysTick_Delay(10);
    /* Send a write request to send the measurement command and its parameters */
    Local_ErrorState = I2c_Master_Transmit(&I2cHandle, SLAVE_ADDRESS_WITH_WRITE, Local_TriggerMeasurement, 3, TIMEOUT_AMOUNT);

    /* Wait for more than 80 ms for the measurement to be completed */
    SysTick_Delay(85);
    /* Check the busy indication bit until it's idle and measurement is complete or timeout occurs */
    do
    {
        /* Receive frame from sensor (status byte + Humudity + Temprature) */
        Local_ErrorState = I2c_Master_Receive(&I2cHandle, SLAVE_ADDRESS_WITH_READ, SignalsReceivingBuffer, Local_SignalNumberBytes , TIMEOUT_AMOUNT);
        Local_StatusByte = SignalsReceivingBuffer[STATUS_BYTE];
    } while ((BUSY == (Local_StatusByte >> BUSY_INDICATION_BIT_POS)) && (--Local_TimeoutAmount));
    
    /* Check the timeout occurrence */
    if (TIMEOUT == Local_TimeoutAmount)
    {
        Local_ErrorState = E_TIME_OUT;
    }
    
#if CRC_STATE == ENABLED
    /* Calculate the CRC and if the data is corrupted fill it all with zeros */
    if (CalculateCRC8() != SignalsReceivingBuffer[CRC_BYTE])
    {
        for (u8 BufferByteIndex = SECOND_BYTE; BufferByteIndex < Local_SignalNumberBytes; BufferByteIndex++)
        {
            SignalsReceivingBuffer[BufferByteIndex] = 0;
        }
    }
#endif

    /* Increment the number of call by one */
    ReadSignalsNumberCalls++;

    return Local_ErrorState;
}

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
static ErrorState_t InitRegs(u8 Copy_RegisterAddress)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_Parameters[2] = {0x00, 0x00};
    u8 Local_ThreeByteBuffer[3];
    
    /* Initialize the register inside module */
    Local_ErrorState = I2c_Mem_Write(&I2cHandle, SLAVE_ADDRESS_WITH_WRITE, Copy_RegisterAddress, I2C_MEMADD_SIZE_8BIT, Local_Parameters, 2, TIMEOUT_AMOUNT);

    /* Wait about 5 ms */
    SysTick_Delay(5);
    /* Receive the 3 data bytes from the module */
    Local_ErrorState = I2c_Master_Receive(&I2cHandle, SLAVE_ADDRESS_WITH_READ, Local_ThreeByteBuffer, 3, TIMEOUT_AMOUNT);

    /* Wait about 10 ms */
    SysTick_Delay(10);
    /* Register command(no more detail in the sample code), then send the second and the third received bytes */
    Local_ErrorState = I2c_Mem_Write(&I2cHandle, SLAVE_ADDRESS_WITH_WRITE, (0xB0 | Copy_RegisterAddress), I2C_MEMADD_SIZE_8BIT, &Local_ThreeByteBuffer[1], 2, TIMEOUT_AMOUNT);

    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t Aht21b_Init(void)
* \Description     : Initialize the AHT21B Module
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Aht21b_Init(void)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_StatusByte;
    I2c_Config_t Local_I2cConfig = {
        .AddressingMode = I2C_ADDRESSINGMODE_7BIT,
        .GeneralCallMode = I2C_GENERALCALL_DISABLE,
        .NoStretchMode = I2C_NOSTRETCH_DISABLE,
        .ClockSpeed = 100,
        .DutyCycle = I2C_DUTYCYCLE_2,
        .DualAddressMode = I2C_DUALADDRESS_DISABLE,
        .OwnAddress1 = 0,
        .OwnAddress2 = 0,
    };

    /* Initialize the I2C handel */
    I2cHandle.Id = AHT21B_I2C;
    I2cHandle.Config = Local_I2cConfig;

    /* Initializing the I2C */
    I2c_Init(&I2cHandle);

    /* Delay from 100ms to 500ms after power-on to reach the idle state and it is ready to receive commands*/
    SysTick_Delay(500);
    /* I2C configuration */
    Local_ErrorState = I2c_Master_Receive(&I2cHandle, SLAVE_ADDRESS_WITH_READ, &Local_StatusByte, 1, TIMEOUT_AMOUNT);

    /* Check the calibration */
    if (CALIBRATION_VALUE_CHECK != (Local_StatusByte & CALIBRATION_VALUE_CHECK))
    {
        /* These register is specified like that in the datasheet without mentioning the details  */
        Local_ErrorState = InitRegs(0x1B);
        Local_ErrorState = InitRegs(0x1C);
        Local_ErrorState = InitRegs(0x1E);
    }
    
    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Aht21b_ReadTemperatureInCelsius(s8 *Copy_Temperature)
* \Description     : Get the enviornment temperature in degree celsius(from -40 to 80 'C)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant                     
* \Parameters (in) : None
* \Parameters (out): Copy_Temperature   Pointer to return the enviornment temperature in celsius
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Aht21b_ReadTemperatureInCelsius(s8 *Copy_Temperature)
{
    ErrorState_t Local_ErrorState = E_OK;
    u32 Local_TemperatureSignal = 0;

    /* Check the function arguments then early return */
    if (NULL == Copy_Temperature)
    {
        return E_NULL_POINTER;
    }

    /* Reset the ReadSignals function number of call if it exceed 2 calls */
    if (ReadSignalsNumberCalls < 1)
    {
        Local_ErrorState = ReadSignals();
    }
    else
    {
        ReadSignalsNumberCalls = 0;
    }
    
    /* calculate the temperature in celsius from the temperature output signal */
    Local_TemperatureSignal |= (SignalsReceivingBuffer[FOURTH_BYTE] << 16);
    Local_TemperatureSignal |= (SignalsReceivingBuffer[FIFTH_BYTE] << 8);
    Local_TemperatureSignal |= (SignalsReceivingBuffer[SIXTH_BYTE]);
    Local_TemperatureSignal &= 0xFFFFF;

    *Copy_Temperature = ((Local_TemperatureSignal * 200UL) / (1UL << 20)) - 50UL;

    return Local_ErrorState;
}

/******************************************************************************
* \Syntax          : ErrorState_t Aht21b_ReadRelativeHumidity(u8 *Copy_Humidity)
* \Description     : Get the enviornment relative humidity(from 0 to 100 %RH)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): Copy_Temperature   Pointer to return the enviornment relative humidity
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Aht21b_ReadRelativeHumidity(u8 *Copy_Humidity)
{
    ErrorState_t Local_ErrorState = E_OK;
    u32 Local_HumiditySignal = 0;

    /* Check the function arguments then early return */
    if (NULL == Copy_Humidity)
    {
        return E_NULL_POINTER;
    }
    
    /* Reset the ReadSignals function number of call if it exceed 2 calls */
    if (ReadSignalsNumberCalls < 1)
    {
        Local_ErrorState = ReadSignals();
    }
    else
    {
        ReadSignalsNumberCalls = 0;
    }
    
    /* calculate the relative humidity(RH) from the relative humidity signal */
    Local_HumiditySignal |= (SignalsReceivingBuffer[SECOND_BYTE] << 16);
    Local_HumiditySignal |= (SignalsReceivingBuffer[THIRD_BYTE] << 8);
    Local_HumiditySignal |= (SignalsReceivingBuffer[FOURTH_BYTE]);
    Local_HumiditySignal >>= 4;

    *Copy_Humidity = (Local_HumiditySignal * 100UL) / (1UL << 20);

    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  END OF FILE: Aht21b_Program.c
 *********************************************************************************************************************/
