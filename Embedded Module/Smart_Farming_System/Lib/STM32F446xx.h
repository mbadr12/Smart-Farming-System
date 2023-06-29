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


/************************* I2C Register Definition Structure ***********************/
typedef struct{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 OAR1;
	volatile u32 OAR2;
	volatile u32 DR;
	volatile u32 SR1;
	volatile u32 SR2;
	volatile u32 CCR;
	volatile u32 TRISE;
	volatile u32 FLTR;
}I2c_RegDef_t;
/************************* I2C Peripheral Definition ***********************/
#define I2C1 ((I2c_RegDef_t *)I2C1_BASE_ADDRESS)
#define I2C2 ((I2c_RegDef_t *)I2C2_BASE_ADDRESS)
#define I2C3 ((I2c_RegDef_t *)I2C3_BASE_ADDRESS)

/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos            (0U)                                         
#define I2C_CR1_PE_Msk            (0x1UL << I2C_CR1_PE_Pos)                     /*!< 0x00000001 */
#define I2C_CR1_PE                I2C_CR1_PE_Msk                               /*!<Peripheral Enable                             */
#define I2C_CR1_SMBUS_Pos         (1U)                                         
#define I2C_CR1_SMBUS_Msk         (0x1UL << I2C_CR1_SMBUS_Pos)                  /*!< 0x00000002 */
#define I2C_CR1_SMBUS             I2C_CR1_SMBUS_Msk                            /*!<SMBus Mode                                    */
#define I2C_CR1_SMBTYPE_Pos       (3U)                                         
#define I2C_CR1_SMBTYPE_Msk       (0x1UL << I2C_CR1_SMBTYPE_Pos)                /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE           I2C_CR1_SMBTYPE_Msk                          /*!<SMBus Type                                    */
#define I2C_CR1_ENARP_Pos         (4U)                                         
#define I2C_CR1_ENARP_Msk         (0x1UL << I2C_CR1_ENARP_Pos)                  /*!< 0x00000010 */
#define I2C_CR1_ENARP             I2C_CR1_ENARP_Msk                            /*!<ARP Enable                                    */
#define I2C_CR1_ENPEC_Pos         (5U)                                         
#define I2C_CR1_ENPEC_Msk         (0x1UL << I2C_CR1_ENPEC_Pos)                  /*!< 0x00000020 */
#define I2C_CR1_ENPEC             I2C_CR1_ENPEC_Msk                            /*!<PEC Enable                                    */
#define I2C_CR1_ENGC_Pos          (6U)                                         
#define I2C_CR1_ENGC_Msk          (0x1UL << I2C_CR1_ENGC_Pos)                   /*!< 0x00000040 */
#define I2C_CR1_ENGC              I2C_CR1_ENGC_Msk                             /*!<General Call Enable                           */
#define I2C_CR1_NOSTRETCH_Pos     (7U)                                         
#define I2C_CR1_NOSTRETCH_Msk     (0x1UL << I2C_CR1_NOSTRETCH_Pos)              /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH         I2C_CR1_NOSTRETCH_Msk                        /*!<Clock Stretching Disable (Slave mode)         */
#define I2C_CR1_START_Pos         (8U)                                         
#define I2C_CR1_START_Msk         (0x1UL << I2C_CR1_START_Pos)                  /*!< 0x00000100 */
#define I2C_CR1_START             I2C_CR1_START_Msk                            /*!<Start Generation                              */
#define I2C_CR1_STOP_Pos          (9U)                                         
#define I2C_CR1_STOP_Msk          (0x1UL << I2C_CR1_STOP_Pos)                   /*!< 0x00000200 */
#define I2C_CR1_STOP              I2C_CR1_STOP_Msk                             /*!<Stop Generation                               */
#define I2C_CR1_ACK_Pos           (10U)                                        
#define I2C_CR1_ACK_Msk           (0x1UL << I2C_CR1_ACK_Pos)                    /*!< 0x00000400 */
#define I2C_CR1_ACK               I2C_CR1_ACK_Msk                              /*!<Acknowledge Enable                            */
#define I2C_CR1_POS_Pos           (11U)                                        
#define I2C_CR1_POS_Msk           (0x1UL << I2C_CR1_POS_Pos)                    /*!< 0x00000800 */
#define I2C_CR1_POS               I2C_CR1_POS_Msk                              /*!<Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos           (12U)                                        
#define I2C_CR1_PEC_Msk           (0x1UL << I2C_CR1_PEC_Pos)                    /*!< 0x00001000 */
#define I2C_CR1_PEC               I2C_CR1_PEC_Msk                              /*!<Packet Error Checking                         */
#define I2C_CR1_ALERT_Pos         (13U)                                        
#define I2C_CR1_ALERT_Msk         (0x1UL << I2C_CR1_ALERT_Pos)                  /*!< 0x00002000 */
#define I2C_CR1_ALERT             I2C_CR1_ALERT_Msk                            /*!<SMBus Alert                                   */
#define I2C_CR1_SWRST_Pos         (15U)                                        
#define I2C_CR1_SWRST_Msk         (0x1UL << I2C_CR1_SWRST_Pos)                  /*!< 0x00008000 */
#define I2C_CR1_SWRST             I2C_CR1_SWRST_Msk                            /*!<Software Reset                                */

/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos          (0U)                                         
#define I2C_CR2_FREQ_Msk          (0x3FUL << I2C_CR2_FREQ_Pos)                  /*!< 0x0000003F */
#define I2C_CR2_FREQ              I2C_CR2_FREQ_Msk                             /*!<FREQ[5:0] bits (Peripheral Clock Frequency)   */
#define I2C_CR2_FREQ_0            (0x01UL << I2C_CR2_FREQ_Pos)                  /*!< 0x00000001 */
#define I2C_CR2_FREQ_1            (0x02UL << I2C_CR2_FREQ_Pos)                  /*!< 0x00000002 */
#define I2C_CR2_FREQ_2            (0x04UL << I2C_CR2_FREQ_Pos)                  /*!< 0x00000004 */
#define I2C_CR2_FREQ_3            (0x08UL << I2C_CR2_FREQ_Pos)                  /*!< 0x00000008 */
#define I2C_CR2_FREQ_4            (0x10UL << I2C_CR2_FREQ_Pos)                  /*!< 0x00000010 */
#define I2C_CR2_FREQ_5            (0x20UL << I2C_CR2_FREQ_Pos)                  /*!< 0x00000020 */

#define I2C_CR2_ITERREN_Pos       (8U)                                         
#define I2C_CR2_ITERREN_Msk       (0x1UL << I2C_CR2_ITERREN_Pos)                /*!< 0x00000100 */
#define I2C_CR2_ITERREN           I2C_CR2_ITERREN_Msk                          /*!<Error Interrupt Enable  */
#define I2C_CR2_ITEVTEN_Pos       (9U)                                         
#define I2C_CR2_ITEVTEN_Msk       (0x1UL << I2C_CR2_ITEVTEN_Pos)                /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN           I2C_CR2_ITEVTEN_Msk                          /*!<Event Interrupt Enable  */
#define I2C_CR2_ITBUFEN_Pos       (10U)                                        
#define I2C_CR2_ITBUFEN_Msk       (0x1UL << I2C_CR2_ITBUFEN_Pos)                /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN           I2C_CR2_ITBUFEN_Msk                          /*!<Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos         (11U)                                        
#define I2C_CR2_DMAEN_Msk         (0x1UL << I2C_CR2_DMAEN_Pos)                  /*!< 0x00000800 */
#define I2C_CR2_DMAEN             I2C_CR2_DMAEN_Msk                            /*!<DMA Requests Enable     */
#define I2C_CR2_LAST_Pos          (12U)                                        
#define I2C_CR2_LAST_Msk          (0x1UL << I2C_CR2_LAST_Pos)                   /*!< 0x00001000 */
#define I2C_CR2_LAST              I2C_CR2_LAST_Msk                             /*!<DMA Last Transfer       */

/*******************  Bit definition for I2C_OAR1 register  *******************/
#define I2C_OAR1_ADD1_7           0x000000FEU                                  /*!<Interface Address */
#define I2C_OAR1_ADD8_9           0x00000300U                                  /*!<Interface Address */

#define I2C_OAR1_ADD0_Pos         (0U)                                         
#define I2C_OAR1_ADD0_Msk         (0x1UL << I2C_OAR1_ADD0_Pos)                  /*!< 0x00000001 */
#define I2C_OAR1_ADD0             I2C_OAR1_ADD0_Msk                            /*!<Bit 0 */
#define I2C_OAR1_ADD1_Pos         (1U)                                         
#define I2C_OAR1_ADD1_Msk         (0x1UL << I2C_OAR1_ADD1_Pos)                  /*!< 0x00000002 */
#define I2C_OAR1_ADD1             I2C_OAR1_ADD1_Msk                            /*!<Bit 1 */
#define I2C_OAR1_ADD2_Pos         (2U)                                         
#define I2C_OAR1_ADD2_Msk         (0x1UL << I2C_OAR1_ADD2_Pos)                  /*!< 0x00000004 */
#define I2C_OAR1_ADD2             I2C_OAR1_ADD2_Msk                            /*!<Bit 2 */
#define I2C_OAR1_ADD3_Pos         (3U)                                         
#define I2C_OAR1_ADD3_Msk         (0x1UL << I2C_OAR1_ADD3_Pos)                  /*!< 0x00000008 */
#define I2C_OAR1_ADD3             I2C_OAR1_ADD3_Msk                            /*!<Bit 3 */
#define I2C_OAR1_ADD4_Pos         (4U)                                         
#define I2C_OAR1_ADD4_Msk         (0x1UL << I2C_OAR1_ADD4_Pos)                  /*!< 0x00000010 */
#define I2C_OAR1_ADD4             I2C_OAR1_ADD4_Msk                            /*!<Bit 4 */
#define I2C_OAR1_ADD5_Pos         (5U)                                         
#define I2C_OAR1_ADD5_Msk         (0x1UL << I2C_OAR1_ADD5_Pos)                  /*!< 0x00000020 */
#define I2C_OAR1_ADD5             I2C_OAR1_ADD5_Msk                            /*!<Bit 5 */
#define I2C_OAR1_ADD6_Pos         (6U)                                         
#define I2C_OAR1_ADD6_Msk         (0x1UL << I2C_OAR1_ADD6_Pos)                  /*!< 0x00000040 */
#define I2C_OAR1_ADD6             I2C_OAR1_ADD6_Msk                            /*!<Bit 6 */
#define I2C_OAR1_ADD7_Pos         (7U)                                         
#define I2C_OAR1_ADD7_Msk         (0x1UL << I2C_OAR1_ADD7_Pos)                  /*!< 0x00000080 */
#define I2C_OAR1_ADD7             I2C_OAR1_ADD7_Msk                            /*!<Bit 7 */
#define I2C_OAR1_ADD8_Pos         (8U)                                         
#define I2C_OAR1_ADD8_Msk         (0x1UL << I2C_OAR1_ADD8_Pos)                  /*!< 0x00000100 */
#define I2C_OAR1_ADD8             I2C_OAR1_ADD8_Msk                            /*!<Bit 8 */
#define I2C_OAR1_ADD9_Pos         (9U)                                         
#define I2C_OAR1_ADD9_Msk         (0x1UL << I2C_OAR1_ADD9_Pos)                  /*!< 0x00000200 */
#define I2C_OAR1_ADD9             I2C_OAR1_ADD9_Msk                            /*!<Bit 9 */

#define I2C_OAR1_ADDMODE_Pos      (15U)                                        
#define I2C_OAR1_ADDMODE_Msk      (0x1UL << I2C_OAR1_ADDMODE_Pos)               /*!< 0x00008000 */
#define I2C_OAR1_ADDMODE          I2C_OAR1_ADDMODE_Msk                         /*!<Addressing Mode (Slave mode) */

/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos       (0U)                                         
#define I2C_OAR2_ENDUAL_Msk       (0x1UL << I2C_OAR2_ENDUAL_Pos)                /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL           I2C_OAR2_ENDUAL_Msk                          /*!<Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos         (1U)                                         
#define I2C_OAR2_ADD2_Msk         (0x7FUL << I2C_OAR2_ADD2_Pos)                 /*!< 0x000000FE */
#define I2C_OAR2_ADD2             I2C_OAR2_ADD2_Msk                            /*!<Interface address           */

/********************  Bit definition for I2C_DR register  ********************/
#define I2C_DR_DR_Pos             (0U)                                         
#define I2C_DR_DR_Msk             (0xFFUL << I2C_DR_DR_Pos)                     /*!< 0x000000FF */
#define I2C_DR_DR                 I2C_DR_DR_Msk                                /*!<8-bit Data Register         */

/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos            (0U)                                         
#define I2C_SR1_SB_Msk            (0x1UL << I2C_SR1_SB_Pos)                     /*!< 0x00000001 */
#define I2C_SR1_SB                I2C_SR1_SB_Msk                               /*!<Start Bit (Master mode)                         */
#define I2C_SR1_ADDR_Pos          (1U)                                         
#define I2C_SR1_ADDR_Msk          (0x1UL << I2C_SR1_ADDR_Pos)                   /*!< 0x00000002 */
#define I2C_SR1_ADDR              I2C_SR1_ADDR_Msk                             /*!<Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos           (2U)                                         
#define I2C_SR1_BTF_Msk           (0x1UL << I2C_SR1_BTF_Pos)                    /*!< 0x00000004 */
#define I2C_SR1_BTF               I2C_SR1_BTF_Msk                              /*!<Byte Transfer Finished                          */
#define I2C_SR1_ADD10_Pos         (3U)                                         
#define I2C_SR1_ADD10_Msk         (0x1UL << I2C_SR1_ADD10_Pos)                  /*!< 0x00000008 */
#define I2C_SR1_ADD10             I2C_SR1_ADD10_Msk                            /*!<10-bit header sent (Master mode)                */
#define I2C_SR1_STOPF_Pos         (4U)                                         
#define I2C_SR1_STOPF_Msk         (0x1UL << I2C_SR1_STOPF_Pos)                  /*!< 0x00000010 */
#define I2C_SR1_STOPF             I2C_SR1_STOPF_Msk                            /*!<Stop detection (Slave mode)                     */
#define I2C_SR1_RXNE_Pos          (6U)                                         
#define I2C_SR1_RXNE_Msk          (0x1UL << I2C_SR1_RXNE_Pos)                   /*!< 0x00000040 */
#define I2C_SR1_RXNE              I2C_SR1_RXNE_Msk                             /*!<Data Register not Empty (receivers)             */
#define I2C_SR1_TXE_Pos           (7U)                                         
#define I2C_SR1_TXE_Msk           (0x1UL << I2C_SR1_TXE_Pos)                    /*!< 0x00000080 */
#define I2C_SR1_TXE               I2C_SR1_TXE_Msk                              /*!<Data Register Empty (transmitters)              */
#define I2C_SR1_BERR_Pos          (8U)                                         
#define I2C_SR1_BERR_Msk          (0x1UL << I2C_SR1_BERR_Pos)                   /*!< 0x00000100 */
#define I2C_SR1_BERR              I2C_SR1_BERR_Msk                             /*!<Bus Error                                       */
#define I2C_SR1_ARLO_Pos          (9U)                                         
#define I2C_SR1_ARLO_Msk          (0x1UL << I2C_SR1_ARLO_Pos)                   /*!< 0x00000200 */
#define I2C_SR1_ARLO              I2C_SR1_ARLO_Msk                             /*!<Arbitration Lost (master mode)                  */
#define I2C_SR1_AF_Pos            (10U)                                        
#define I2C_SR1_AF_Msk            (0x1UL << I2C_SR1_AF_Pos)                     /*!< 0x00000400 */
#define I2C_SR1_AF                I2C_SR1_AF_Msk                               /*!<Acknowledge Failure                             */
#define I2C_SR1_OVR_Pos           (11U)                                        
#define I2C_SR1_OVR_Msk           (0x1UL << I2C_SR1_OVR_Pos)                    /*!< 0x00000800 */
#define I2C_SR1_OVR               I2C_SR1_OVR_Msk                              /*!<Overrun/Underrun                                */
#define I2C_SR1_PECERR_Pos        (12U)                                        
#define I2C_SR1_PECERR_Msk        (0x1UL << I2C_SR1_PECERR_Pos)                 /*!< 0x00001000 */
#define I2C_SR1_PECERR            I2C_SR1_PECERR_Msk                           /*!<PEC Error in reception                          */
#define I2C_SR1_TIMEOUT_Pos       (14U)                                        
#define I2C_SR1_TIMEOUT_Msk       (0x1UL << I2C_SR1_TIMEOUT_Pos)                /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT           I2C_SR1_TIMEOUT_Msk                          /*!<Timeout or Tlow Error                           */
#define I2C_SR1_SMBALERT_Pos      (15U)                                        
#define I2C_SR1_SMBALERT_Msk      (0x1UL << I2C_SR1_SMBALERT_Pos)               /*!< 0x00008000 */
#define I2C_SR1_SMBALERT          I2C_SR1_SMBALERT_Msk                         /*!<SMBus Alert                                     */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos           (0U)                                         
#define I2C_SR2_MSL_Msk           (0x1UL << I2C_SR2_MSL_Pos)                    /*!< 0x00000001 */
#define I2C_SR2_MSL               I2C_SR2_MSL_Msk                              /*!<Master/Slave                                    */
#define I2C_SR2_BUSY_Pos          (1U)                                         
#define I2C_SR2_BUSY_Msk          (0x1UL << I2C_SR2_BUSY_Pos)                   /*!< 0x00000002 */
#define I2C_SR2_BUSY              I2C_SR2_BUSY_Msk                             /*!<Bus Busy                                        */
#define I2C_SR2_TRA_Pos           (2U)                                         
#define I2C_SR2_TRA_Msk           (0x1UL << I2C_SR2_TRA_Pos)                    /*!< 0x00000004 */
#define I2C_SR2_TRA               I2C_SR2_TRA_Msk                              /*!<Transmitter/Receiver                            */
#define I2C_SR2_GENCALL_Pos       (4U)                                         
#define I2C_SR2_GENCALL_Msk       (0x1UL << I2C_SR2_GENCALL_Pos)                /*!< 0x00000010 */
#define I2C_SR2_GENCALL           I2C_SR2_GENCALL_Msk                          /*!<General Call Address (Slave mode)               */
#define I2C_SR2_SMBDEFAULT_Pos    (5U)                                         
#define I2C_SR2_SMBDEFAULT_Msk    (0x1UL << I2C_SR2_SMBDEFAULT_Pos)             /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT        I2C_SR2_SMBDEFAULT_Msk                       /*!<SMBus Device Default Address (Slave mode)       */
#define I2C_SR2_SMBHOST_Pos       (6U)                                         
#define I2C_SR2_SMBHOST_Msk       (0x1UL << I2C_SR2_SMBHOST_Pos)                /*!< 0x00000040 */
#define I2C_SR2_SMBHOST           I2C_SR2_SMBHOST_Msk                          /*!<SMBus Host Header (Slave mode)                  */
#define I2C_SR2_DUALF_Pos         (7U)                                         
#define I2C_SR2_DUALF_Msk         (0x1UL << I2C_SR2_DUALF_Pos)                  /*!< 0x00000080 */
#define I2C_SR2_DUALF             I2C_SR2_DUALF_Msk                            /*!<Dual Flag (Slave mode)                          */
#define I2C_SR2_PEC_Pos           (8U)                                         
#define I2C_SR2_PEC_Msk           (0xFFUL << I2C_SR2_PEC_Pos)                   /*!< 0x0000FF00 */
#define I2C_SR2_PEC               I2C_SR2_PEC_Msk                              /*!<Packet Error Checking Register                  */

/*******************  Bit definition for I2C_CCR register  ********************/
#define I2C_CCR_CCR_Pos           (0U)                                         
#define I2C_CCR_CCR_Msk           (0xFFFUL << I2C_CCR_CCR_Pos)                  /*!< 0x00000FFF */
#define I2C_CCR_CCR               I2C_CCR_CCR_Msk                              /*!<Clock Control Register in Fast/Standard mode (Master mode) */
#define I2C_CCR_DUTY_Pos          (14U)                                        
#define I2C_CCR_DUTY_Msk          (0x1UL << I2C_CCR_DUTY_Pos)                   /*!< 0x00004000 */
#define I2C_CCR_DUTY              I2C_CCR_DUTY_Msk                             /*!<Fast Mode Duty Cycle                                       */
#define I2C_CCR_FS_Pos            (15U)                                        
#define I2C_CCR_FS_Msk            (0x1UL << I2C_CCR_FS_Pos)                     /*!< 0x00008000 */
#define I2C_CCR_FS                I2C_CCR_FS_Msk                               /*!<I2C Master Mode Selection                                  */

/******************  Bit definition for I2C_TRISE register  *******************/
#define I2C_TRISE_TRISE_Pos       (0U)                                         
#define I2C_TRISE_TRISE_Msk       (0x3FUL << I2C_TRISE_TRISE_Pos)               /*!< 0x0000003F */
#define I2C_TRISE_TRISE           I2C_TRISE_TRISE_Msk                          /*!<Maximum Rise Time in Fast/Standard mode (Master mode) */

/******************  Bit definition for I2C_FLTR register  *******************/
#define I2C_FLTR_DNF_Pos          (0U)                                         
#define I2C_FLTR_DNF_Msk          (0xFUL << I2C_FLTR_DNF_Pos)                   /*!< 0x0000000F */
#define I2C_FLTR_DNF              I2C_FLTR_DNF_Msk                             /*!<Digital Noise Filter */
#define I2C_FLTR_ANOFF_Pos        (4U)                                         
#define I2C_FLTR_ANOFF_Msk        (0x1UL << I2C_FLTR_ANOFF_Pos)                 /*!< 0x00000010 */
#define I2C_FLTR_ANOFF            I2C_FLTR_ANOFF_Msk                           /*!<Analog Noise Filter OFF */

#endif		/* STM32F446XX_H */




/**********************************************************************************************************************
 *  END OF FILE: STM32F446XX.h
 *********************************************************************************************************************/
