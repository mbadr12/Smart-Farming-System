/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Nvic_Types.h
 *		  Layer:  Mcal
 *       Module:  Nvic
 *		Version:  1.00
 *	
 *  Description:  api type definitions for the Nvic module
 *  
 *********************************************************************************************************************/
#ifndef NVIC_TYPES_H
#define NVIC_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NVIC_NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  NVIC_MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  NVIC_BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  NVIC_UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  NVIC_SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  NVIC_DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  NVIC_PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  NVIC_SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  NVIC_WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  NVIC_PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  NVIC_TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  NVIC_RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  NVIC_FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  NVIC_RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  NVIC_EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  NVIC_EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  NVIC_EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  NVIC_EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  NVIC_EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  NVIC_DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  NVIC_DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  NVIC_DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  NVIC_DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  NVIC_DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  NVIC_DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  NVIC_DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  NVIC_ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  NVIC_CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupt                                                 */
  NVIC_CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupt                                                */
  NVIC_CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
  NVIC_CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
  NVIC_EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  NVIC_TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  NVIC_TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  NVIC_TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  NVIC_TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  NVIC_TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  NVIC_TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  NVIC_TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  NVIC_I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  NVIC_I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
  NVIC_I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
  NVIC_I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  NVIC_SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  NVIC_SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  NVIC_USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  NVIC_USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  NVIC_USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */
  NVIC_EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  NVIC_RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  NVIC_OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  NVIC_TIM8_BRK_TIM12_IRQn         = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
  NVIC_TIM8_UP_TIM13_IRQn          = 44,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
  NVIC_TIM8_TRG_COM_TIM14_IRQn     = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
  NVIC_TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare global interrupt                             */
  NVIC_DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  NVIC_FMC_IRQn                    = 48,     /*!< FMC global Interrupt                                              */
  NVIC_SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
  NVIC_TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
  NVIC_SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  NVIC_UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
  NVIC_UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
  NVIC_TIM6_DAC_IRQn               = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
  NVIC_TIM7_IRQn                   = 55,     /*!< TIM7 global interrupt                                             */
  NVIC_DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  NVIC_DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  NVIC_DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  NVIC_DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  NVIC_DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  NVIC_ETH_IRQn                    = 61,     /*!< Ethernet global Interrupt                                         */
  NVIC_ETH_WKUP_IRQn               = 62,     /*!< Ethernet Wakeup through EXTI line Interrupt                       */
  NVIC_CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupt                                                 */
  NVIC_CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupt                                                */
  NVIC_CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupt                                                */
  NVIC_CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupt                                                */
  NVIC_OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  NVIC_DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  NVIC_DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  NVIC_DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  NVIC_USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
  NVIC_I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
  NVIC_I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
  NVIC_OTG_HS_EP1_OUT_IRQn         = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
  NVIC_OTG_HS_EP1_IN_IRQn          = 75,     /*!< USB OTG HS End Point 1 In global interrupt                        */
  NVIC_OTG_HS_WKUP_IRQn            = 76,     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
  NVIC_OTG_HS_IRQn                 = 77,     /*!< USB OTG HS global interrupt                                       */
  NVIC_DCMI_IRQn                   = 78,     /*!< DCMI global interrupt                                             */
  NVIC_HASH_RNG_IRQn               = 80,     /*!< Hash and Rng global interrupt                                     */
  NVIC_FPU_IRQn                    = 81,     /*!< FPU global interrupt                                              */
  NVIC_UART7_IRQn                  = 82,     /*!< UART7 global interrupt                                            */
  NVIC_UART8_IRQn                  = 83,     /*!< UART8 global interrupt                                            */
  NVIC_SPI4_IRQn                   = 84,     /*!< SPI4 global Interrupt                                             */
  NVIC_SPI5_IRQn                   = 85,     /*!< SPI5 global Interrupt                                             */
  NVIC_SPI6_IRQn                   = 86,     /*!< SPI6 global Interrupt                                             */
  NVIC_SAI1_IRQn                   = 87,     /*!< SAI1 global Interrupt                                             */
  NVIC_LTDC_IRQn                   = 88,     /*!< LTDC global Interrupt                                              */
  NVIC_LTDC_ER_IRQn                = 89,     /*!< LTDC Error global Interrupt                                        */
  NVIC_DMA2D_IRQn                  = 90      /*!< DMA2D global Interrupt                                            */
} Nvic_IRQn_t;

/*
 * NVIC_GROUPING_SYS_XXXX -> Group = 16 level, SubGroup = 0 level
 * NVIC_GROUPING_SYS_XXXY -> Group =  8 level, SubGroup = 2 level
 * NVIC_GROUPING_SYS_XXYY -> Group =  4 level, SubGroup = 4 level
 * NVIC_GROUPING_SYS_XYYY -> Group =  2 level, SubGroup = 8 level
 * NVIC_GROUPING_SYS_YYYY -> Group =  0 level, SubGroup = 16 level -> No Preemption!
 */
typedef enum{
    NVIC_GROUPING_SYS_XXXX=0,
    NVIC_GROUPING_SYS_XXXY,
    NVIC_GROUPING_SYS_XXYY,
    NVIC_GROUPING_SYS_XYYY,
    NVIC_GROUPING_SYS_YYYY,
}Nvic_PrioGroup_t;

#endif /* NVIC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Nvic_Types.h
 *********************************************************************************************************************/
