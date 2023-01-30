/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr - Mazen Fahim
 *	   	   File:  STM32F446XX.h
 *		  Layer:  Lib
 *       Module:  STM32F446XX.h
 *		Version:  1.00
 *	
 *  Description:  A header file contiains the Registers of the microcontroller    
 *  
 *********************************************************************************************************************/

#ifndef STM32F446XX_H
#define STM32F446XX_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Platform_Types.h"
 
/***************************** 		Core Peripherals	*****************************/

/*****************************		Systick Registers	*****************************/

#define STK_CTRL		*((volatile u32*)(0xE000E010+0x00))
#define STK_LOAD		*((volatile u32*)(0xE000E010+0x04))
#define STK_VAL			*((volatile u32*)(0xE000E010+0x08))

/*************************** NVIC Peripheral Base Addresses *************************/

#define NVIC_BASE_ADDRESS		0xE000E100UL

/************************* NVIC Register Definition Structure ***********************/

typedef struct
{
	volatile u32 ISER[8];		/*Interrupt set-enable register*/
	u32 Reserved1[24];
	volatile u32 ICER[8];		/*Interrupt clear-enable register*/
	u32 Reserved[24];
	volatile u32 ISPR[8];		/*Interrupt set-pending register*/
	u32 Reserved2[24];
	volatile u32 ICPR[8];		/*Interrupt clear-pending register*/
	u32 Reserved4[24];
	volatile u32 IABR[8];		/*Interrupt active bit register*/
	u32 Reserved3[32];
	volatile u8 IPR[240];		/*Interrupt priority register*/
}NVIC_RegDef_t;

#define NVIC						((NVIC_RegDef_t*)NVIC_BASE_ADDRESS)

/**************************** SCB Peripheral Base Addresses *************************/

#define SCB_BASE_ADDRESS		0xE000ED00UL

/************************** SCB Register Definition Structure ***********************/

typedef struct
{
	volatile u32 CPUID;					/*CPUID base register*/
	volatile u32 ICSR;                  /*Interrupt control and state register*/
	volatile u32 VTOR;                  /*Vector table offset register*/
	volatile u32 AIRCR;                 /*Application interrupt and reset control register*/
	volatile u32 SCR;                   /*System control register*/
	volatile u32 CCR;                   /*Configuration and control register*/
	volatile u32 SHPR[3];               /*System handler priority registers*/
	volatile u32 SHCSR;                 /*System handler control and state register*/
	volatile u32 CFSR;                  /*Configurable fault status register*/
	volatile u32 HFSR;                  /*Hard fault status register*/
	volatile u32 Reserved;
	volatile u32 MMAR;                  /*Memory management fault address register*/
	volatile u32 BFAR;                  /*Bus fault status register*/
	volatile u32 AFSR;                  /*Auxiliary fault status register*/
}SCB_RegDef_t;

#define SCB					((SCB_RegDef_t*) SCB_BASE_ADDRESS)

/***************************** Memories Base Addresses ******************************/
#define FLASH_BASE_ADDRESS		0x08000000UL
#define SRAM1_BASE_ADDRESS		0x20000000UL
#define SRAM2_BASE_ADDRESS		0x2001C000UL
#define ROM_BASE_ADDRESS		0x1FFF0000UL

/*************************** AHB1 Peripheral Base Addresses *************************/

#define GPIOA_BASE_ADDRESS		0X40020000UL
#define GPIOB_BASE_ADDRESS		0X40020400UL
#define GPIOC_BASE_ADDRESS		0X40020800UL
#define GPIOD_BASE_ADDRESS		0X40020C00UL
#define GPIOE_BASE_ADDRESS		0X40021000UL
#define GPIOF_BASE_ADDRESS		0X40021400UL
#define GPIOG_BASE_ADDRESS		0X40021800UL
#define GPIOH_BASE_ADDRESS		0X40021C00UL
#define RCC_BASE_ADDRESS		0x40023800UL
#define DMA1_BASE_ADDRESS		0x40026000UL
#define DMA2_BASE_ADDRESS		0x40026400UL

/*************************** AHB2 Peripheral Base Addresses *************************/
#define DCMI_BASE_ADDRESS		0x50050000UL

/*************************** APB1 Peripheral Base Addresses *************************/

#define I2C3_BASE_ADDRESS		0x40005C00UL
#define I2C2_BASE_ADDRESS		0x40005800UL
#define I2C1_BASE_ADDRESS		0x40005400UL
#define USART2_BASE_ADDRESS		0x40004400UL
#define USART3_BASE_ADDRESS		0x40004800UL
#define UART4_BASE_ADDRESS		0x40004C00UL
#define UART5_BASE_ADDRESS		0x40005000UL
#define SPI2_BASE_ADDRESS		0x40003800UL
#define SPI3_BASE_ADDRESS		0x40003C00UL

/*************************** APB2 Peripheral Base Addresses *************************/

#define USART1_BASE_ADDRESS		0x40011000UL
#define USART6_BASE_ADDRESS		0x40011400UL
#define SPI1_BASE_ADDRESS		0x40013000UL
#define SPI4_BASE_ADDRESS		0x40013400UL
#define SYSCFG_BASE_ADDRESS		0x40013800UL
#define EXTI_BASE_ADDRESS		0x40013C00UL
#define ADC1_BASE_ADDRESS		0x40012000UL
#define ADC2_BASE_ADDRESS		0x40012100UL
#define ADC3_BASE_ADDRESS		0x40012200UL

/************************* GPIO Register Definition Structure ***********************/

typedef struct
{
	volatile u32 MODER;     		/*GPIO port mode register*/
	volatile u32 OTYPER;    		/*GPIO port output type register*/
	volatile u32 OSPEEDER;  		/*GPIO port output speed register*/
	volatile u32 PUPDR;     		/*GPIO port pull-up/pull-down register*/
	volatile u32 IDR;       		/*GPIO port input data register*/
	volatile u32 ODR;       		/*GPIO port output data register*/
	volatile u32 BSRR;      		/*GPIO port bit set/reset register*/
	volatile u32 LCKR;      		/*GPIO port configuration lock register*/
	volatile u32 AFR[2];    		/*AFR[0] : GPIO alternate function low register
									 *AFR[1] : GPIO alternate function high register*/
}Gpio_RegDef_t;

/***************************** GPIO Peripheral Definitions **************************/

#define GPIOA			((Gpio_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB			((Gpio_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC			((Gpio_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD			((Gpio_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE			((Gpio_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF			((Gpio_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG			((Gpio_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH			((Gpio_RegDef_t*)GPIOH_BASE_ADDRESS)

/************************* RCC Register Definition Structure ***********************/

typedef struct
{
	volatile u32 CR; 				/*RCC clock control register*/				 
	volatile u32 PLLCFGR;           /*RCC PLL configuration register*/
	volatile u32 CFGR;              /*RCC clock configuration register*/
	volatile u32 CIR;               /*RCC clock interrupt register*/
	volatile u32 AHB1RSTR;          /*RCC AHB1 peripheral reset register*/
	volatile u32 AHB2RSTR;          /*RCC AHB2 peripheral reset register*/
	volatile u32 AHB3RSTR;          /*RCC AHB3 peripheral reset register*/
	volatile u32 Reserved;          /*Reserved*/
	volatile u32 APB1RSTR;          /*RCC APB1 peripheral reset register*/
	volatile u32 APB2RSTR;          /*RCC APB2 peripheral reset register*/
	volatile u32 Reserved1[2];      /*Reserved*/
	volatile u32 AHB1ENR;           /*RCC AHB1 peripheral clock enable register*/
	volatile u32 AHB2ENR;           /*RCC AHB2 peripheral clock enable register*/
	volatile u32 AHB3ENR;           /*RCC AHB3 peripheral clock enable register*/
	volatile u32 Reserved2;         /*Reserved*/
	volatile u32 APB1ENR;           /*RCC APB1 peripheral clock enable register*/
	volatile u32 APB2ENR;           /*RCC APB2 peripheral clock enable register*/
	volatile u32 Reserved3[2];      /*Reserved*/
	volatile u32 AHB1LPENR;         /*RCC AHB1 peripheral clock enable in low power mode register*/
	volatile u32 AHB2LPENR;         /*RCC AHB2 peripheral clock enable in low power mode register*/
	volatile u32 AHB3LPENR;         /*RCC AHB3 peripheral clock enable in low power mode register*/
	volatile u32 Reserved4;         /*Reserved*/
	volatile u32 APB1LPENR;         /*RCC APB1 peripheral clock enable in low power mode register*/
	volatile u32 APB2LPENR;         /*RCC APB2 peripheral clock enable in low power mode register*/
	volatile u32 Reserved5[2];      /*Reserved*/
	volatile u32 BDCR;              /*RCC Backup domain control register*/
	volatile u32 CSR;               /*RCC clock control & status register*/
	volatile u32 Reserved6[2];      /*Reserved*/
	volatile u32 SSCGR;             /*RCC spread spectrum clock generation register*/
	volatile u32 PLLI2SCFGR;        /*RCC PLLI2S configuration register*/
	volatile u32 PLLSAICFGR;        /*RCC PLLSAI configuration register*/
	volatile u32 DCKCFGR;           /*RCC dedicated clock configuration register*/
	volatile u32 CKGATENR;          /*RCC clocks gated enable register*/
	volatile u32 DCKCFGR2;          /*RCC dedicated clocks configuration register 2*/
}RCC_RegDef_t;

#define RCC				((RCC_RegDef_t*)RCC_BASE_ADDRESS)

/************************* SYSCFG Register Definition Structure ***********************/

typedef struct
{
	volatile u32 MEMRMP;			/*SYSCFG memory remap register*/
	volatile u32 PMC;				/*SYSCFG peripheral mode configuration register*/
	volatile u32 EXTICR[4];			/*SYSCFG external interrupt configuration registers*/
	u32 Reserved[2];
	volatile u32 CMPCR;				/*Compensation cell control register*/
	u32 Reserved2[2];
	volatile u32 CFGR;				/*SYSCFG configuration register*/
}SYSCFG_RegDef_t;

/***************************** SYSCFG Peripheral Definitions **************************/

#define SYSCFG					((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDRESS)

/************************* EXTI Register Definition Structure ***********************/

typedef struct
{
	volatile u32 IMR;               /*Interrupt mask register*/
	volatile u32 EMR;               /*Event mask register*/
	volatile u32 RTSR;              /*Rising trigger selection register*/
	volatile u32 FTSR;              /*Falling trigger selection register*/
	volatile u32 SWIER;             /*Software interrupt event register*/
	volatile u32 PR;                /*Pending register*/
}EXTI_RegDef_t;

/***************************** EXTI Peripheral Definitions **************************/

#define EXTI					((EXTI_RegDef_t*)EXTI_BASE_ADDRESS)

/************************** DMA Register Definition Structure ***********************/

typedef struct
{
	volatile u32 CR;				/*DMA stream x configuration register*/
	volatile u32 NDTR;              /*DMA stream x number of data register*/
	volatile u32 PAR;               /*DMA stream x peripheral address register*/
	volatile u32 M0AR;              /*DMA stream x memory 0 address register*/
	volatile u32 M1AR;               /*DMA stream x memory 1 address register*/
	volatile u32 FCR;               /*DMA stream x FIFO control register*/
}DMA_Stream_t;

typedef struct
{
	volatile u32 ISR[2];				/*DMA interrupt status registers*/
	volatile u32 IFCR[2];             	/*DMA interrupt flag clear registers*/
	volatile DMA_Stream_t Stream[8];
}DMA_RegDef_t;

/***************************** DMA Peripheral Definitions **************************/

#define DMA1					((DMA_RegDef_t*)DMA1_BASE_ADDRESS)	
#define DMA2					((DMA_RegDef_t*)DMA2_BASE_ADDRESS)

/************************** Usart Register Definition Structure ***********************/

typedef struct
{
	volatile u32 SR;                 /*Status register*/
	volatile u32 DR;                 /*Data register*/
	volatile u32 BRR;                /*Baud rate register*/
	volatile u32 CR1;                /*Control register 1*/
	volatile u32 CR2;                /*Control register 2*/
	volatile u32 CR3;                /*Control register 3*/
	volatile u32 GTPR;               /*Guard time and prescaler register*/
}Usart_RegDef_t;

/***************************** Usart Peripheral Definitions **************************/

#define USART1					((Usart_RegDef_t*)USART1_BASE_ADDRESS)	
#define USART2					((Usart_RegDef_t*)USART2_BASE_ADDRESS)
#define USART3					((Usart_RegDef_t*)USART3_BASE_ADDRESS)	
#define UART4					((Usart_RegDef_t*)UART4_BASE_ADDRESS)
#define UART5					((Usart_RegDef_t*)UART5_BASE_ADDRESS)
#define USART6					((Usart_RegDef_t*)USART6_BASE_ADDRESS)

/************************** Dcmi Register Definition Structure ***********************/

typedef struct
{
	volatile u32 CR;				/*control register*/		
	volatile u32 SR;                /*status register*/
	volatile u32 RIS;               /*raw interrupt status register*/
	volatile u32 IER;               /*interrupt enable register*/
	volatile u32 MIS;               /*masked interrupt status register*/
	volatile u32 ICR;               /*interrupt clear register*/
	volatile u32 ESCR;              /*embedded synchronization code register*/
	volatile u32 ESUR;              /*embedded synchronization unmask register*/
	volatile u32 CWSTRT;            /*crop window start*/
	volatile u32 CWSIZE;            /*crop window size*/
	volatile u32 DR;                /*data register*/
}Dcmi_RegDef_t;

/***************************** Dcmi Peripheral Definitions **************************/
#define DCMI					((Dcmi_RegDef_t*)DCMI_BASE_ADDRESS)

/************************** Adc Register Definition Structure ***********************/

typedef struct
{
	volatile u32 SR;                 /*status register*/
	volatile u32 CR[2];              /*control registers*/
	volatile u32 SMPR[2];            /*sample time registers*/
	volatile u32 JOFR[4];            /*injected channel data offset registers*/
	volatile u32 HTR;                /*watchdog higher threshold register*/
	volatile u32 LTR;                /*ADC watchdog lower threshold register*/
	volatile u32 SQR[3];             /*ADC regular sequence registers*/
	volatile u32 JSQR;               /*ADC injected sequence register*/
	volatile u32 JDR[4];             /*ADC injected data registers*/
	volatile u32 DR;                 /*ADC regular data register*/
}Adc_RegDef_t;

typedef struct
{
	volatile u32 CSR;
	volatile u32 CCR;
	volatile u32 CDR;
}Adc_CommonRegDef_t;

/***************************** Adc Peripheral Definitions **************************/
#define ADC1					((Adc_RegDef_t*)ADC1_BASE_ADDRESS)
#define ADC2					((Adc_RegDef_t*)ADC2_BASE_ADDRESS)
#define ADC3					((Adc_RegDef_t*)ADC3_BASE_ADDRESS)
#define ADC_COMMON				((Adc_CommonRegDef_t*)(ADC1_BASE_ADDRESS+0x300))

#endif		/* STM32F446XX_H */

/**********************************************************************************************************************
 *  END OF FILE: STM32F446XX.h
 *********************************************************************************************************************/
