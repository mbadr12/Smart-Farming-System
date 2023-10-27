/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa, Mahmoud, Mazen
 *	   	   File:  LLSysInit_Program.c
 *		  Layer:  App
 *       Module:  LLSysInit
 *		Version:  1.0
 *	
 *  Description: A LLSysInit driver that ...
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Gpio_Types.h"
#include "STM32F429xx.h"
#include "Bit_Math.h"

#include "LLSysInit_Private.h"
#include "LLSysInit_Config.h"
#include "LLSysInit_Interface.h"

#include "Rcc_Interface.h"
#include "Gpio_Interface.h"
#include "Nvic_Interface.h"
#include "Dma_Interface.h"
#include "SysTick_Interface.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static void LLSysInit_Rcc(void)
* \Description     : Initialize all the clocks required.
*                                                                             
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
static void LLSysInit_Rcc(void)
{
    /* 1. Configure The system clock */
    Rcc_SetSysClkSrc(RCC_HSI);
    Rcc_Mco1Enable(SYSTEM_RCC_MCO1_SRC, SYSTEM_RCC_MCO1_PRESCALER);

    /* 1. PORTA  */
    Rcc_EnablePericlock(RCC_AHB1_GPIOA, 0);
    /* 2. PORTB  */
    Rcc_EnablePericlock(RCC_AHB1_GPIOB, 0);
    /* 3. PORTC  */
    Rcc_EnablePericlock(RCC_AHB1_GPIOC, 0);
    /* 4. PORTD  */
    Rcc_EnablePericlock(RCC_AHB1_GPIOD, 0);
    /* 5. GPIOE */
    Rcc_EnablePericlock(RCC_AHB1_GPIOE, 0);
    /* 6. Dcmi */
    Rcc_EnablePericlock(RCC_AHB2_DCMI, 0);
    /* 7. I2C2 */
    Rcc_EnablePericlock(RCC_APB1_I2C2, 0);
    /* 8. DMA2 */
    Rcc_EnablePericlock(RCC_AHB1_DMA2, 0);
    /* 9. UART4 */
    Rcc_EnablePericlock(RCC_APB1_UART4, 0);
    /* 10. ADC */
    Rcc_EnablePericlock(RCC_APB2_ADC1, 0);

}

/******************************************************************************
* \Syntax          : static void LLSysInit_Gpio(void)
* \Description     : Initialize all the I/O pins required.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
static void LLSysInit_Gpio(void)
{
    Gpio_Config_t Local_GpioConfig;
    /* 1. DCMI */
    Local_GpioConfig.PinMode = GPIO_MODE_AF;
    Local_GpioConfig.PinAF = GPIO_AF13_DCMI;
    Local_GpioConfig.PinOutputType = GPIO_OT_PUSH_PULL;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_NOTHING;

    Gpio_Init(DCMI_D0, &Local_GpioConfig);
    Gpio_Init(DCMI_D1, &Local_GpioConfig);
    Gpio_Init(DCMI_D2, &Local_GpioConfig);
    Gpio_Init(DCMI_D3, &Local_GpioConfig);
    Gpio_Init(DCMI_D4, &Local_GpioConfig);
    Gpio_Init(DCMI_D5, &Local_GpioConfig);
    Gpio_Init(DCMI_D6, &Local_GpioConfig);
    Gpio_Init(DCMI_D7, &Local_GpioConfig);
    Gpio_Init(DCMI_VSYNC, &Local_GpioConfig);
    Gpio_Init(DCMI_HSYNC, &Local_GpioConfig);
    Gpio_Init(DCMI_PIXCLK, &Local_GpioConfig);

    /* 2. I2C2 (for camera and sensor) */
    Local_GpioConfig.PinMode = GPIO_MODE_AF;
    Local_GpioConfig.PinAF = GPIO_AF4_I2C2;
    Local_GpioConfig.PinOutputType = GPIO_OT_OPEN_DRAIN;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_PULLUP;

    Gpio_Init(I2C2_SDA, &Local_GpioConfig);
    Gpio_Init(I2C2_SCL, &Local_GpioConfig);

    /* 3. Camera Reset digital pin */
    Local_GpioConfig.PinMode = GPIO_MODE_OUTPUT;
    Local_GpioConfig.PinAF = 0;
    Local_GpioConfig.PinOutputType = GPIO_OT_PUSH_PULL;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_NOTHING;
    Gpio_Init(CAMERA_RESET_PIN, &Local_GpioConfig);

    /* 4. MCO1 */
    Local_GpioConfig.PinMode = GPIO_MODE_AF;
    Local_GpioConfig.PinAF = GPIO_AF0_MCO;
    Local_GpioConfig.PinOutputType = GPIO_OT_PUSH_PULL;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_NOTHING;
    Gpio_Init(MCO_PIN, &Local_GpioConfig);

    /* 5. LDR */
    Local_GpioConfig.PinMode = GPIO_MODE_INPUT;
    Local_GpioConfig.PinAF = 0;
    Local_GpioConfig.PinOutputType = GPIO_OT_PUSH_PULL;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_PULLUP;
    Gpio_Init(LDR_DIGITAL_PIN, &Local_GpioConfig);

    Local_GpioConfig.PinMode = GPIO_MODE_ANALOG;
    Local_GpioConfig.PinAF = 0;
    Local_GpioConfig.PinOutputType = GPIO_OT_PUSH_PULL;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_NOTHING;
    Gpio_Init(LDR_ANALOG_PIN, &Local_GpioConfig);

    /* 6. FC28 */
    Local_GpioConfig.PinMode = GPIO_MODE_INPUT;
    Local_GpioConfig.PinAF = 0;
    Local_GpioConfig.PinOutputType = 0;
    Local_GpioConfig.PinOutputSpeed = 0;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_PULLUP;
    Gpio_Init(FC28_FIRST_DIGITAL_PIN, &Local_GpioConfig);
    Gpio_Init(FC28_SECOND_DIGITAL_PIN, &Local_GpioConfig);

    Local_GpioConfig.PinMode = GPIO_MODE_ANALOG;
    Local_GpioConfig.PinAF = 0;
    Local_GpioConfig.PinOutputType = GPIO_OT_PUSH_PULL;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_NOTHING;
    Gpio_Init(FC28_FIRST_ANALOG_PIN, &Local_GpioConfig);
    Gpio_Init(FC28_SECOND_ANALOG_PIN, &Local_GpioConfig);

    /* 7. Water Tank */
    Local_GpioConfig.PinMode = GPIO_MODE_INPUT;
    Local_GpioConfig.PinAF = 0;
    Local_GpioConfig.PinOutputType = 0;
    Local_GpioConfig.PinOutputSpeed = 0;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_PULLUP;
    Gpio_Init(WTRTANK_HLS, &Local_GpioConfig);
    Gpio_Init(WTRTANK_LLS, &Local_GpioConfig);

    /* 8. LED grid */
    Local_GpioConfig.PinMode = GPIO_MODE_OUTPUT;
    Local_GpioConfig.PinAF = 0;
    Local_GpioConfig.PinOutputType = GPIO_OT_PUSH_PULL;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_PULLUP;
    Gpio_Init(LEDGRID_PIN, &Local_GpioConfig);

    /* 9. Resvoir Pump */
    Gpio_Init(PUMP_WATERTANK, &Local_GpioConfig);

    /* 10. Main water tank valve */
    Gpio_Init(VALVE_WATERTANK, &Local_GpioConfig);


    /* 11. UART4 */
    Local_GpioConfig.PinMode = GPIO_MODE_AF;
    Local_GpioConfig.PinAF = GPIO_AF8_UART4;
    Local_GpioConfig.PinOutputType = GPIO_OT_PUSH_PULL;
    Local_GpioConfig.PinOutputSpeed = GPIO_OS_MEDIUM;
    Local_GpioConfig.PinInternalAttach = GPIO_IA_PULLUP;
    Gpio_Init(UART4_TX, &Local_GpioConfig);
    Gpio_Init(UART4_RX, &Local_GpioConfig);

    /* 12. */



}

/******************************************************************************
* \Syntax          : static void LLSysInit_Nvic(void)
* \Description     : Enable all the interrupts required.
*                                                                             
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
static void LLSysInit_Nvic(void)
{
    /* Set the subgroub priority */
    Nvic_SetPriorityGrouping(NVIC_GROUPING_SYS_XXXX);

    /* 1. DMA2 STREAM 1 */
    Nvic_SetPriority(NVIC_DMA2_Stream1_IRQn, 1);
    Nvic_EnableIRQ(NVIC_DMA2_Stream1_IRQn);

    return;
}

/******************************************************************************
* \Syntax          : static void LLSysInit_Dma(void)
* \Description     : Initialize all DMA channels required.
*                                                                             
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
static void LLSysInit_Dma(void)
{
    Dma_Config_t Local_DmaConfig = {
        .DMA_Number = DMA_2,
        .Stream = DMA_STREAM_1,
        .Channel = DMA_CHANNEL_1,
        .MemSize = DMA_MEM_SIZE_WORD,
        .PrphSize = DMA_PRPH_SIZE_WORD,
        .Priority = DMA_STREAM_VERY_HIGH_PR,
        .StreamMode = DMA_STREAM_FIFO,
        .channelMode = DMA_CHANNEL_REGULAR,
        .TransferType = DMA_SINGLE_TRANSFER,
        .DataDirection = DMA_PERIPHERAL_TO_MEMORY,
        .FifoThreshold = DMA_FIFO_FULL,
        .MemPrphIncMode = DMA_MEM_INC_PRPH_FIXED};

    Dma_Init(&Local_DmaConfig);
}

/******************************************************************************
* \Syntax          : static void LLSysInit_SysTick(void)
* \Description     : Initialize the systemTick to have a time base of 1ms
*                                                                             
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
static void LLSysInit_SysTick(void)
{
    SysTick_Config_t config;
    config.InterruptEnable = 1;
    config.ClockSource = SYSTICK_AHB_DIV_8;
    // since AHB is running on 16 Mhz HSI then systick running on 16/8 = 2Mhz
    // Reload vale for SysTick interrupt every 1ms = 2000
    config.ReloadValue = 2000;
    SysTick_Init(&config);
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static void LLSysInit(void)
* \Description     : Initialize all the Low Level resources required.
*                                                                             
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void LLSysInit(void)
{
    LLSysInit_Rcc();
    LLSysInit_Gpio();
    LLSysInit_Nvic();
    LLSysInit_Dma();
    LLSysInit_SysTick();

}

/**********************************************************************************************************************
 *  END OF FILE: LLSysInit_Program.c
 *********************************************************************************************************************/

