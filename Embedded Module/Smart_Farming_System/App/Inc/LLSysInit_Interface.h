/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa, Mahmoud, Mazen
 *	   	   File:  LLSysInit_Interface.h
 *		  Layer:  App
 *       Module:  LLSysInit
 *		Version:  1.0
 *	
 *  Description:  A header file that contains function prototypes of the llsysinit module and includes its types.
 *  
 *********************************************************************************************************************/
#ifndef LLSYSINIT_INTERFACE_H 
#define LLSYSINIT_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LLSysInit_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*** SYSTEM CLOCK PARAMETERS ***/
#define SYSTEM_CLK 16
#define SYSTEM_AHB_PRESCALER 1
#define SYSTEM_APB_PRESCALER 1
#define SYSTEM_APB1_CLK (SYSTEM_CLK / SYSTEM_AHB_PRESCALER / SYSTEM_APB_PRESCALER)

#define SYSTEM_RCC_MCO1_SRC RCC_MCO1_HSI
#define SYSTEM_RCC_MCO1_PRESCALER RCC_MCO_PS_4

/*** PIN DEFINITIONS ***/

/* DCMI */
#define DCMI_D0 GPIO_PIN_C6
#define DCMI_D1 GPIO_PIN_C7
#define DCMI_D2 GPIO_PIN_C8
#define DCMI_D3 GPIO_PIN_C9
#define DCMI_D4 GPIO_PIN_C11
#define DCMI_D5 GPIO_PIN_B6
#define DCMI_D6 GPIO_PIN_B8
#define DCMI_D7 GPIO_PIN_B9
#define DCMI_VSYNC GPIO_PIN_B7
#define DCMI_HSYNC GPIO_PIN_A4
#define DCMI_PIXCLK GPIO_PIN_A6

/* I2C2 */
#define I2C2_SCL GPIO_PIN_B10
#define I2C2_SDA GPIO_PIN_B11

/* Camera reset pin */
#define CAMERA_RESET_PIN GPIO_PIN_E0

/* LDR */
#define LDR_DIGITAL_PIN GPIO_PIN_D6
#define LDR_ANALOG_PIN GPIO_PIN_D7

/* Moisture */
#define FC28_FIRST_DIGITAL_PIN GPIO_PIN_D1
#define FC28_FIRST_ANALOG_PIN GPIO_PIN_D0
#define FC28_SECOND_DIGITAL_PIN GPIO_PIN_C0
#define FC28_SECOND_ANALOG_PIN GPIO_PIN_A3

/* Water Tank */
#define WTRTANK_HLS GPIO_PIN_D5
#define WTRTANK_LLS GPIO_PIN_D4

/* LED Grid */
#define LEDGRID_PIN GPIO_PIN_D3

/* PUMP water tank*/
#define PUMP_WATERTANK GPIO_PIN_E2

/* Valve water tank */
#define VALVE_WATERTANK GPIO_PIN_E4

/* MCO */
#define MCO_PIN GPIO_PIN_A8

/* UART4 */
#define UART4_TX GPIO_PIN_A0
#define UART4_RX GPIO_PIN_A1

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void LLSysInit(void);

 
#endif  /* LLSYSINIT_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: LLSysInit_Interface.h
 *********************************************************************************************************************/

