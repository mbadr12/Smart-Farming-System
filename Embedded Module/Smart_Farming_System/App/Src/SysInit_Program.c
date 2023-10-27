/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa, Mahmoud, Mazen
 *	   	   File:  SysInit_Program.c
 *		  Layer:  App
 *       Module:  SysInit
 *		Version:  1.0
 *	
 *  Description: A SysInit driver that ...
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F429xx.h"
#include "Bit_Math.h"
#include "farmstdlib.h"

#include "SysInit_Private.h"
#include "SysInit_Config.h"
#include "SysInit_Interface.h"

#include "LLSysInit_Interface.h"


/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/* Configure device drivers to read data from them */
Ldr_Config_t Sys_LdrConfig;
Fc28_Config_t Sys_Fc28Config1;
Fc28_Config_t Sys_Fc28Config2;

/* Configure device drivers to send out control signals to them */
WtrTank_Config_t Sys_WtrTankConfig;
LedGrid_Config_t Sys_LedGridConfig;
Pump_Config_t Sys_PumpResvoirConfig;
Valve_Config_t Sys_ValveWaterTankConfig;
Valve_Config_t Sys_ValveResvoirConfig;

Mqtt_Publish_t Sys_MqttTempPubConfig;
Mqtt_Publish_t Sys_MqttHumPubConfig;
Mqtt_Publish_t Sys_MqttLDRPubConfig;
Mqtt_Publish_t Sys_MqttSoil1PubConfig;
Mqtt_Publish_t Sys_MqttSoil2PubConfig;
Mqtt_Publish_t Sys_MqttTankPubConfig;
Mqtt_Publish_t Sys_MqttLightPubConfig;
Mqtt_Publish_t Sys_MqttPhotoPubConfig;

extern char App_MqttMessage[4];

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/* If LDR reading crossed the threshold (either from bright to dark or from dark to bright) */
static void Sys_LdrHandler(void){
	/* Get light state */
	u8 Local_LedGridStatel;
	LedGrid_GetState(&Sys_LedGridConfig, &Local_LedGridStatel);
	if(Local_LedGridStatel == LEDGRID_TURNED_ON){
		LedGrid_TurnOff(&Sys_LedGridConfig);
	}
	else{
		LedGrid_TurnOn(&Sys_LedGridConfig);
	}
	return;
}

/* If moisture sensor exceed threshold level close valves */
static void Sys_Fc28Handler(void){
	/* Close main water tank valve*/
	Valve_Close(&Sys_ValveWaterTankConfig);
	/* Close each line valve */
	/* Close water pump */
	return;
}

/* If main water tank is full */
static void Sys_WaterTankHlsHandler(void){
	Pump_TurnOff(&Sys_PumpResvoirConfig);
	Valve_Close(&Sys_ValveResvoirConfig);
	return;
}

/* If main water tank is empty */
static void Sys_WaterTankLlsHandler(void){
	Pump_TurnOn(&Sys_PumpResvoirConfig);
	Valve_Open(&Sys_ValveResvoirConfig);
	return;
}


static void Sys_LdrInit(void){
	static Adc_ConversionConfig_t Local_AdcConversionConfig = {
			.Adc = ADC_1,
			.Channel = ADC_CHANNEL7,
			.ChannelType = ADC_REGULAR_CHANNEL,
			.TriggerType = ADC_SW_TRIGGER,
			.SampleTime = ADC_28_CYCLES,
	};
	static Exti_PinConfig_t Local_ExtiConfig = {
			.Port = GPIO_PIN_D6 / NUMBER_OF_PINS_PER_PORT,
			.Pin = GPIO_PIN_D6 % NUMBER_OF_PINS_PER_PORT,
			.Trigger = EXTI_RIS_FALL_TRIGGER,
			.CallBackFunc = Sys_LdrHandler,

	};

	Sys_LdrConfig.DigitalPinId = GPIO_PIN_D6;
	Sys_LdrConfig.AnalogPinId = GPIO_PIN_D7;
	Sys_LdrConfig.DigitalPinInterruptEnable = ENABLE;
	Sys_LdrConfig.Adc_Resolution = ADC_12BIT;
	Sys_LdrConfig.Adc_ConversionConfig = &Local_AdcConversionConfig;
	Sys_LdrConfig.ExtiPinConfig = &Local_ExtiConfig;

	Ldr_Init(&Sys_LdrConfig);
}


static void Sys_Fc28Init(void){
	static Adc_ConversionConfig_t Local_AdcConversionConfig = {
			.Adc = ADC_1,
			.Channel = ADC_CHANNEL1,
			.ChannelType = ADC_REGULAR_CHANNEL,
			.TriggerType = ADC_SW_TRIGGER,
			.SampleTime = ADC_28_CYCLES,
	};

	static Exti_PinConfig_t Local_ExtiConfig = {
			.Port = GPIO_PIN_D1 / NUMBER_OF_PINS_PER_PORT,
			.Pin = GPIO_PIN_D1 % NUMBER_OF_PINS_PER_PORT,
			.Trigger = EXTI_FALLING_TRIGGER,
			.CallBackFunc = Sys_Fc28Handler,
	};

	Sys_Fc28Config1.DigitalPinId = GPIO_PIN_D1;
	Sys_Fc28Config1.AnalogPinId = GPIO_PIN_D0;
	Sys_Fc28Config1.DigitalPinInterruptEnable = ENABLE;
	Sys_Fc28Config1.Adc_Resolution = ADC_12BIT;
	Sys_Fc28Config1.Adc_ConversionConfig = &Local_AdcConversionConfig;
	Sys_Fc28Config1.ExtiPinConfig = &Local_ExtiConfig;

	Fc28_Init(&Sys_Fc28Config1);

	Sys_Fc28Config2 = Sys_Fc28Config1;

	Sys_Fc28Config2.DigitalPinId = GPIO_PIN_C0;
	Sys_Fc28Config2.AnalogPinId = GPIO_PIN_A3;

	Fc28_Init(&Sys_Fc28Config2);
}

static void Sys_WaterTankInit(void){
    Exti_PinConfig_t Local_HlsExtiConfig = {
        .Port = GPIO_PIN_D5 / NUMBER_OF_PINS_PER_PORT,
        .Pin = GPIO_PIN_D5 % NUMBER_OF_PINS_PER_PORT,
        .Trigger = EXTI_FALLING_TRIGGER,
        .CallBackFunc = Sys_WaterTankHlsHandler,
    };
    Exti_PinConfig_t Local_LlsExtiConfig = {
        .Port = GPIO_PIN_D4 / NUMBER_OF_PINS_PER_PORT,
        .Pin = GPIO_PIN_D4 % NUMBER_OF_PINS_PER_PORT,
        .Trigger = EXTI_RAISING_TRIGGER,
        .CallBackFunc = Sys_WaterTankLlsHandler
    };

    Sys_WtrTankConfig.HlsPinId = GPIO_PIN_D5;
    Sys_WtrTankConfig.LlsPinId = GPIO_PIN_D4;
    Sys_WtrTankConfig.HlsInitState = WTRTANK_SWITCH_NORMALLY_OPENED;
    Sys_WtrTankConfig.LlsInitState = WTRTANK_SWITCH_NORMALLY_CLOSED;
    Sys_WtrTankConfig.HlsPullingType = SWITCH_PULL_UP;
    Sys_WtrTankConfig.LlsPullingType = SWITCH_PULL_UP;
    Sys_WtrTankConfig.HlsInterruptEnable = WTRTANK_SWITCH_INT_ENABLE;
    Sys_WtrTankConfig.LlsInterruptEnable = WTRTANK_SWITCH_INT_ENABLE;
    Sys_WtrTankConfig.HlsExtiPinConfig = &Local_HlsExtiConfig;
    Sys_WtrTankConfig.LlsExtiPinConfig = &Local_LlsExtiConfig;

    WtrTank_Init(&Sys_WtrTankConfig);
}

static void Sys_LedGridInit(void){
	Sys_LedGridConfig.PinId = GPIO_PIN_D3;
	Sys_LedGridConfig.ActivationType = LEDGRID_ACTIVE_HIGH;
}

static void Sys_ValveInit(void){
    Sys_ValveWaterTankConfig.PinId = GPIO_PIN_E4;
	Sys_ValveWaterTankConfig.ActivationType = PUMP_ACTIVE_HIGH;

    Sys_ValveResvoirConfig.PinId = GPIO_PIN_E5;
	Sys_ValveResvoirConfig.ActivationType = PUMP_ACTIVE_HIGH;
}

static void Sys_PumpInit(void){
    Sys_PumpResvoirConfig.PinId = GPIO_PIN_E2;
	Sys_PumpResvoirConfig.ActivationType = PUMP_ACTIVE_HIGH;
}

static void Sys_MqttInit(void){
	Mqtt_EspConnection Local_EspConfig={"Musa", "hhhh.0000", "broker.hivemq.com", 1883};
	Mqtt_Connect_t Local_ConnectConfig={.ClientId="SmartFarmingSystem",.UserName="MQTThivebroker",.Password="MQTThivebroker"};

	Sys_MqttTempPubConfig.TopicName="SmartFarmingSystem/Sensor/Temperature";
	Sys_MqttTempPubConfig.Msg= App_MqttMessage;
	Sys_MqttTempPubConfig.Qos=MQTT_QOS1;
	Sys_MqttTempPubConfig.MsgLen= strlen(App_MqttMessage);
	Sys_MqttTempPubConfig.Telemetry="Temperature";
	Sys_MqttTempPubConfig.TelLen=strlen("Temperature");

	Sys_MqttHumPubConfig.TopicName="SmartFarmingSystem/Sensor/Humidity";
	Sys_MqttHumPubConfig.Msg= App_MqttMessage;
	Sys_MqttHumPubConfig.Qos=MQTT_QOS1;
	Sys_MqttHumPubConfig.MsgLen= strlen(App_MqttMessage);
	Sys_MqttHumPubConfig.Telemetry="Humidity";
	Sys_MqttHumPubConfig.TelLen=strlen("Humidity");

	Sys_MqttLDRPubConfig.TopicName="SmartFarmingSystem/Sensor/luminancePercentage";
	Sys_MqttLDRPubConfig.Msg= App_MqttMessage;
	Sys_MqttLDRPubConfig.Qos=MQTT_QOS1;
	Sys_MqttLDRPubConfig.MsgLen= strlen(App_MqttMessage);
	Sys_MqttLDRPubConfig.Telemetry="luminancePercentage";
	Sys_MqttLDRPubConfig.TelLen=strlen("luminancePercentage");

	Sys_MqttSoil1PubConfig.TopicName="SmartFarmingSystem/Sensor/SoilMoisturePercentage1";
	Sys_MqttSoil1PubConfig.Msg= App_MqttMessage;
	Sys_MqttSoil1PubConfig.Qos=MQTT_QOS1;
	Sys_MqttSoil1PubConfig.MsgLen= strlen(App_MqttMessage);
	Sys_MqttSoil1PubConfig.Telemetry="SoilMoisturePercentage1";
	Sys_MqttSoil1PubConfig.TelLen=strlen("SoilMoisturePercentage1");

	Sys_MqttSoil2PubConfig.TopicName="SmartFarmingSystem/Sensor/SoilMoisturePercentage2";
	Sys_MqttSoil2PubConfig.Msg= App_MqttMessage;
	Sys_MqttSoil2PubConfig.Qos=MQTT_QOS1;
	Sys_MqttSoil2PubConfig.MsgLen= strlen(App_MqttMessage);
	Sys_MqttSoil2PubConfig.Telemetry="SoilMoisturePercentage2";
	Sys_MqttSoil2PubConfig.TelLen=strlen("SoilMoisturePercentage2");

	Sys_MqttTankPubConfig.TopicName="SmartFarmingSystem/Irrigation/WaterTankState";
	Sys_MqttTankPubConfig.Msg= App_MqttMessage;
	Sys_MqttTankPubConfig.Qos=MQTT_QOS1;
	Sys_MqttTankPubConfig.MsgLen= strlen(App_MqttMessage);
	Sys_MqttTankPubConfig.Telemetry="WaterTankState";
	Sys_MqttTankPubConfig.TelLen=strlen("WaterTankState");

	Sys_MqttLightPubConfig.TopicName="SmartFarmingSystem/Lighting/LEDGridState";
	Sys_MqttLightPubConfig.Msg=App_MqttMessage;
	Sys_MqttLightPubConfig.Qos=MQTT_QOS1;
	Sys_MqttLightPubConfig.MsgLen= strlen(App_MqttMessage);
	Sys_MqttLightPubConfig.Telemetry="LEDGridState";
	Sys_MqttLightPubConfig.TelLen=strlen("LEDGridState");

	Sys_MqttPhotoPubConfig.TopicName="SmartFarmingSystem/Camera/Photo";
	Sys_MqttPhotoPubConfig.Msg= OV7670_Frame;
	Sys_MqttPhotoPubConfig.Qos= MQTT_QOS1;
	Sys_MqttPhotoPubConfig.MsgLen= OV7670_FRAME_SIZE;
	Sys_MqttPhotoPubConfig.Telemetry="Photo";
	Sys_MqttPhotoPubConfig.TelLen=strlen("Photo");

	Mqtt_Connect(MQTT_UART4, &Local_ConnectConfig, &Local_EspConfig);
}

/******************************************************************************
* \Syntax          : void SysInit(void)
* \Description     : Initialize all of the system peripherals 
*                                                                             
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : void
* *****************************************************************************/
void SysInit(void)
{
    /* Low Level Resources Initialization */
    LLSysInit();

	/* HAL Layer Initialization */
	Sys_LdrInit();
	Sys_Fc28Init();
	Sys_Fc28Init();

	Sys_LedGridInit();
	Sys_ValveInit();
	Sys_PumpInit();
	Aht21b_Init(I2C_2);
	Ov7670_Init(I2C_2);

	/* Service Layer Initialization */
	Sys_MqttInit();
	Sys_WaterTankInit();
}

/**********************************************************************************************************************
 *  END OF FILE: SysInit_Program.c
 *********************************************************************************************************************/

