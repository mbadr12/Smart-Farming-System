/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa, Mahmoud, Mazen
 *	   	   File:  SysInit_Interface.h
 *		  Layer:  App
 *       Module:  SysInit
 *		Version:  1.0
 *	
 *  Description:  A header file that contains function prototypes of the sysinit module and includes its types.
 *  
 *********************************************************************************************************************/
#ifndef SYSINIT_INTERFACE_H 
#define SYSINIT_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "SysInit_Types.h"

/* Mcal Layer APIs included to expose internal types used by upper layers */
#include "Adc_Interface.h"
#include "Gpio_Interface.h"

/* Hal Layer*/
#include "Esp_Interface.h"
#include "Ov7670_Interface.h"
#include "Aht21b_Interface.h"
#include "Fc28_Interface.h"
#include "Exti_Interface.h"
#include "Pump_Interface.h"
#include "Valve_Interface.h"
#include "Ldr_Interface.h"
#include "LedGrid_Interface.h"

/* Service Layer*/
#include "WtrTank_Interface.h"
#include "Mqtt_Interface.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* Configure device drivers to read data from them */
extern Ldr_Config_t Sys_LdrConfig;
extern Fc28_Config_t Sys_Fc28Config1;
extern Fc28_Config_t Sys_Fc28Config2;

/* Configure device drivers to send out control signals to them */
extern WtrTank_Config_t Sys_WtrTankConfig;
extern LedGrid_Config_t Sys_LedGridConfig;
extern Pump_Config_t Sys_PumpResvoirConfig;
extern Valve_Config_t Sys_ValveWaterTankConfig;
extern Valve_Config_t Sys_ValveResvoirConfig;
 
extern Mqtt_Publish_t Sys_MqttTempPubConfig;
extern Mqtt_Publish_t Sys_MqttHumPubConfig;
extern Mqtt_Publish_t Sys_MqttLDRPubConfig;
extern Mqtt_Publish_t Sys_MqttSoil1PubConfig;
extern Mqtt_Publish_t Sys_MqttSoil2PubConfig;
extern Mqtt_Publish_t Sys_MqttTankPubConfig;
extern Mqtt_Publish_t Sys_MqttLightPubConfig;
extern Mqtt_Publish_t Sys_MqttPhotoPubConfig;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void SysInit(void);
 
#endif  /* SYSINIT_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: SysInit_Interface.h
 *********************************************************************************************************************/

