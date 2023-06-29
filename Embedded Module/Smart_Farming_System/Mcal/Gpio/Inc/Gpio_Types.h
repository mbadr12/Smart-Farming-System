/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Gpio_Types.h
 *		  Layer:  Mcal
 *       Module:  Gpio
 *		Version:  1.00
 *
 *  Description:  Gpio module API type definitions.
 *
 *********************************************************************************************************************/
#ifndef GPIO_TYPES_H
#define GPIO_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum {
  GPIO_PIN_A0 = 0,
  GPIO_PIN_A1,
  GPIO_PIN_A2,
  GPIO_PIN_A3,
  GPIO_PIN_A4,
  GPIO_PIN_A5,
  GPIO_PIN_A6,
  GPIO_PIN_A7,
  GPIO_PIN_A8,
  GPIO_PIN_A9,
  GPIO_PIN_A10,
  GPIO_PIN_A11,
  GPIO_PIN_A12,
  GPIO_PIN_A13,
  GPIO_PIN_A14,
  GPIO_PIN_A15,

  GPIO_PIN_B0,
  GPIO_PIN_B1,
  GPIO_PIN_B2,
  GPIO_PIN_B3,
  GPIO_PIN_B4,
  GPIO_PIN_B5,
  GPIO_PIN_B6,
  GPIO_PIN_B7,
  GPIO_PIN_B8,
  GPIO_PIN_B9,
  GPIO_PIN_B10,
  GPIO_PIN_B11,
  GPIO_PIN_B12,
  GPIO_PIN_B13,
  GPIO_PIN_B14,
  GPIO_PIN_B15,

  GPIO_PIN_C0,
  GPIO_PIN_C1,
  GPIO_PIN_C2,
  GPIO_PIN_C3,
  GPIO_PIN_C4,
  GPIO_PIN_C5,
  GPIO_PIN_C6,
  GPIO_PIN_C7,
  GPIO_PIN_C8,
  GPIO_PIN_C9,
  GPIO_PIN_C10,
  GPIO_PIN_C11,
  GPIO_PIN_C12,
  GPIO_PIN_C13,
  GPIO_PIN_C14,
  GPIO_PIN_C15,

  GPIO_PIN_D0,
  GPIO_PIN_D1,
  GPIO_PIN_D2,
  GPIO_PIN_D3,
  GPIO_PIN_D4,
  GPIO_PIN_D5,
  GPIO_PIN_D6,
  GPIO_PIN_D7,
  GPIO_PIN_D8,
  GPIO_PIN_D9,
  GPIO_PIN_D10,
  GPIO_PIN_D11,
  GPIO_PIN_D12,
  GPIO_PIN_D13,
  GPIO_PIN_D14,
  GPIO_PIN_D15,

  GPIO_PIN_E0,
  GPIO_PIN_E1,
  GPIO_PIN_E2,
  GPIO_PIN_E3,
  GPIO_PIN_E4,
  GPIO_PIN_E5,
  GPIO_PIN_E6,
  GPIO_PIN_E7,
  GPIO_PIN_E8,
  GPIO_PIN_E9,
  GPIO_PIN_E10,
  GPIO_PIN_E11,
  GPIO_PIN_E12,
  GPIO_PIN_E13,
  GPIO_PIN_E14,
  GPIO_PIN_E15,

  GPIO_PIN_F0,
  GPIO_PIN_F1,
  GPIO_PIN_F2,
  GPIO_PIN_F3,
  GPIO_PIN_F4,
  GPIO_PIN_F5,
  GPIO_PIN_F6,
  GPIO_PIN_F7,
  GPIO_PIN_F8,
  GPIO_PIN_F9,
  GPIO_PIN_F10,
  GPIO_PIN_F11,
  GPIO_PIN_F12,
  GPIO_PIN_F13,
  GPIO_PIN_F14,
  GPIO_PIN_F15,

  GPIO_PIN_G0,
  GPIO_PIN_G1,
  GPIO_PIN_G2,
  GPIO_PIN_G3,
  GPIO_PIN_G4,
  GPIO_PIN_G5,
  GPIO_PIN_G6,
  GPIO_PIN_G7,
  GPIO_PIN_G8,
  GPIO_PIN_G9,
  GPIO_PIN_G10,
  GPIO_PIN_G11,
  GPIO_PIN_G12,
  GPIO_PIN_G13,
  GPIO_PIN_G14,
  GPIO_PIN_G15,

  GPIO_PIN_H0,
  GPIO_PIN_H1,
  GPIO_PIN_H2,
  GPIO_PIN_H3,
  GPIO_PIN_H4,
  GPIO_PIN_H5,
  GPIO_PIN_H6,
  GPIO_PIN_H7,
  GPIO_PIN_H8,
  GPIO_PIN_H9,
  GPIO_PIN_H10,
  GPIO_PIN_H11,
  GPIO_PIN_H12,
  GPIO_PIN_H13,
  GPIO_PIN_H14,
  GPIO_PIN_H15,

  GPIO_PIN_I0,
  GPIO_PIN_I1,
  GPIO_PIN_I2,
  GPIO_PIN_I3,
  GPIO_PIN_I4,
  GPIO_PIN_I5,
  GPIO_PIN_I6,
  GPIO_PIN_I7,
  GPIO_PIN_I8,
  GPIO_PIN_I9,
  GPIO_PIN_I10,
  GPIO_PIN_I11,
  GPIO_PIN_I12,
  GPIO_PIN_I13,
  GPIO_PIN_I14,
  GPIO_PIN_I15,

  GPIO_PIN_J0,
  GPIO_PIN_J1,
  GPIO_PIN_J2,
  GPIO_PIN_J3,
  GPIO_PIN_J4,
  GPIO_PIN_J5,
  GPIO_PIN_J6,
  GPIO_PIN_J7,
  GPIO_PIN_J8,
  GPIO_PIN_J9,
  GPIO_PIN_J10,
  GPIO_PIN_J11,
  GPIO_PIN_J12,
  GPIO_PIN_J13,
  GPIO_PIN_J14,
  GPIO_PIN_J15,

  GPIO_PIN_K0,
  GPIO_PIN_K1,
  GPIO_PIN_K2,
  GPIO_PIN_K3,
  GPIO_PIN_K4,
  GPIO_PIN_K5,
  GPIO_PIN_K6,
  GPIO_PIN_K7,
  GPIO_PIN_K8,
  GPIO_PIN_K9,
  GPIO_PIN_K10,
  GPIO_PIN_K11,
  GPIO_PIN_K12,
  GPIO_PIN_K13,
  GPIO_PIN_K14,
  GPIO_PIN_K15,
} Gpio_PinId_t;

typedef enum {
  GPIO_PORT_A = 0,
  GPIO_PORT_B,
  GPIO_PORT_C,
  GPIO_PORT_D,
  GPIO_PORT_E,
  GPIO_PORT_F,
  GPIO_PORT_G,
  GPIO_PORT_H,
  GPIO_PORT_I,
  GPIO_PORT_J,
  GPIO_PORT_K,
} Gpio_PortId_t;

typedef u16 Gpio_PortLevel_t;
typedef enum { GPIO_LOW, GPIO_HIGH } Gpio_PinLevel_t;

/*** CONFIG TYPES ***/

typedef enum {
  GPIO_MODE_INPUT = 0,
  GPIO_MODE_OUTPUT,
  GPIO_MODE_AF,
  GPIO_MODE_ANALOG
} Gpio_PinMode_t;

typedef enum { GPIO_OT_PUSH_PULL = 0, GPIO_OT_OPEN_DRAIN } Gpio_PinOutputType_t;

typedef enum {
  GPIO_OS_LOW = 0,
  GPIO_OS_MEDIUM,
  GPIO_OS_HIGH,
  GPIO_OS_VERY_HIGH
} Gpio_PinOutputSpeed_t;

typedef enum {
  GPIO_IA_NOTHING = 0,
  GPIO_IA_PULLUP,
  GPIO_IA_PULLDOWN,
  GPIO_IA_OPENDRAIN,
} Gpio_PinInternalAttach_t;

typedef enum {
  Gpio_EXTI_DISABLE = 0,
  Gpio_EXTI_RISING_EDGE,
  Gpio_EXTI_FALLING_EDGE,
  Gpio_EXTI_BOTH_EDGES,
} Gpio_PinExternalInterrupt_t;

typedef u16 Gpio_PinAlternateFunction_t;
#define GPIO_AF0_RTC_50Hz      ((u8)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((u8)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_TAMPER        ((u8)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((u8)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((u8)0x00)  /* TRACE Alternate Function mapping                          */

#define GPIO_AF1_TIM1          ((u8)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((u8)0x01)  /* TIM2 Alternate Function mapping */

#define GPIO_AF2_TIM3          ((u8)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4          ((u8)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM5          ((u8)0x02)  /* TIM5 Alternate Function mapping */

#define GPIO_AF3_TIM8          ((u8)0x03)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF3_TIM9          ((u8)0x03)  /* TIM9 Alternate Function mapping  */
#define GPIO_AF3_TIM10         ((u8)0x03)  /* TIM10 Alternate Function mapping */
#define GPIO_AF3_TIM11         ((u8)0x03)  /* TIM11 Alternate Function mapping */

#define GPIO_AF4_I2C1          ((u8)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((u8)0x04)  /* I2C2 Alternate Function mapping */
#define GPIO_AF4_I2C3          ((u8)0x04)  /* I2C3 Alternate Function mapping */

#define GPIO_AF5_SPI1          ((u8)0x05)  /* SPI1 Alternate Function mapping        */
#define GPIO_AF5_SPI2          ((u8)0x05)  /* SPI2/I2S2 Alternate Function mapping   */
#define GPIO_AF5_SPI3          ((u8)0x05)  /* SPI3/I2S3 Alternate Function mapping   */
#define GPIO_AF5_SPI4          ((u8)0x05)  /* SPI4 Alternate Function mapping        */
#define GPIO_AF5_SPI5          ((u8)0x05)  /* SPI5 Alternate Function mapping        */
#define GPIO_AF5_SPI6          ((u8)0x05)  /* SPI6 Alternate Function mapping        */
#define GPIO_AF5_I2S3ext       ((u8)0x05)  /* I2S3ext_SD Alternate Function mapping  */

#define GPIO_AF6_SPI3          ((u8)0x06)  /* SPI3/I2S3 Alternate Function mapping  */
#define GPIO_AF6_I2S2ext       ((u8)0x06)  /* I2S2ext_SD Alternate Function mapping */
#define GPIO_AF6_SAI1          ((u8)0x06)  /* SAI1 Alternate Function mapping       */

#define GPIO_AF7_USART1        ((u8)0x07)  /* USART1 Alternate Function mapping     */
#define GPIO_AF7_USART2        ((u8)0x07)  /* USART2 Alternate Function mapping     */
#define GPIO_AF7_USART3        ((u8)0x07)  /* USART3 Alternate Function mapping     */
#define GPIO_AF7_I2S3ext       ((u8)0x07)  /* I2S3ext_SD Alternate Function mapping */

#define GPIO_AF8_UART4         ((u8)0x08)  /* UART4 Alternate Function mapping  */
#define GPIO_AF8_UART5         ((u8)0x08)  /* UART5 Alternate Function mapping  */
#define GPIO_AF8_USART6        ((u8)0x08)  /* USART6 Alternate Function mapping */
#define GPIO_AF8_UART7         ((u8)0x08)  /* UART7 Alternate Function mapping  */
#define GPIO_AF8_UART8         ((u8)0x08)  /* UART8 Alternate Function mapping  */

#define GPIO_AF9_CAN1          ((u8)0x09)  /* CAN1 Alternate Function mapping    */
#define GPIO_AF9_CAN2          ((u8)0x09)  /* CAN2 Alternate Function mapping    */
#define GPIO_AF9_TIM12         ((u8)0x09)  /* TIM12 Alternate Function mapping   */
#define GPIO_AF9_TIM13         ((u8)0x09)  /* TIM13 Alternate Function mapping   */
#define GPIO_AF9_TIM14         ((u8)0x09)  /* TIM14 Alternate Function mapping   */
#define GPIO_AF9_LTDC          ((u8)0x09)  /* LCD-TFT Alternate Function mapping */

#define GPIO_AF10_OTG_FS        ((u8)0x0A)  /* OTG_FS Alternate Function mapping */
#define GPIO_AF10_OTG_HS        ((u8)0x0A)  /* OTG_HS Alternate Function mapping */

#define GPIO_AF11_ETH           ((u8)0x0B)  /* ETHERNET Alternate Function mapping */

#define GPIO_AF12_FMC           ((u8)0x0C)  /* FMC Alternate Function mapping                      */
#define GPIO_AF12_OTG_HS_FS     ((u8)0x0C)  /* OTG HS configured in FS, Alternate Function mapping */
#define GPIO_AF12_SDIO          ((u8)0x0C)  /* SDIO Alternate Function mapping                     */

#define GPIO_AF13_DCMI          ((u8)0x0D)  /* DCMI Alternate Function mapping */

#define GPIO_AF14_LTDC          ((u8)0x0E)  /* LCD-TFT Alternate Function mapping */

#define GPIO_AF15_EVENTOUT      ((u8)0x0F)  /* EVENTOUT Alternate Function mapping */

typedef struct {
  Gpio_PinMode_t PinMode;
  Gpio_PinOutputType_t PinOutputType;
  Gpio_PinOutputSpeed_t PinOutputSpeed;
  Gpio_PinInternalAttach_t PinInternalAttach;
  Gpio_PinAlternateFunction_t PinAF;
  Gpio_PinExternalInterrupt_t PinEXTI;
} Gpio_Config_t;

#endif /* GPIO_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpio_Types.h
 *********************************************************************************************************************/
