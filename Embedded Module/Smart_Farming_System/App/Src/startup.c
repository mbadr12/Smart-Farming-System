/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  startup.c
 *		Version:  1.00
 *	
 *  Description:  This file Initializes the vector table and it contains the first
 *  code that will be run after reset that's responsible for initializing different
 *  memories.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES 
 *********************************************************************************************************************/
extern u32 _estack;

extern u32 _stext;
extern u32 _etext;

extern u32 _sdata;
extern u32 _edata;

extern u32 _sbss;
extern u32 _ebss;
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES 
 *********************************************************************************************************************/
int main(void);

void Reset_Handler(void);
void NMI_Handler(void) __attribute((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute((weak, alias("Default_Handler")));
void WWDG_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void ADC_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void USART3_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void FMC_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void SDIO_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM5_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void UART4_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void UART5_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void ETH_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void ETH_WKUP_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void USART6_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DCMI_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void CRYP_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void HASH_RNG_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void FPU_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void UART7_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void UART8_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void SPI4_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void SPI5_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void SPI6_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void SAI1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void LCD_TFT_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void LCD_TFT_1_IRQHandler(void) __attribute((weak, alias("Default_Handler")));
void DMA2D_IRQHandler(void) __attribute((weak, alias("Default_Handler")));

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
u32 vectors[] __attribute((section(".isr_vectors"))) = {
    (u32) &_estack,
    (u32) &Reset_Handler,
    (u32) &NMI_Handler,
    (u32) &HardFault_Handler,
  	(u32) &MemManage_Handler,
  	(u32) &BusFault_Handler,
  	(u32) &UsageFault_Handler,
    0,
  	0,
  	0,
  	0,
  	(u32) &SVC_Handler,
  	(u32) &DebugMon_Handler,
  	0,
  	(u32) &PendSV_Handler,
  	(u32) &SysTick_Handler,
  	(u32) &WWDG_IRQHandler,              		/* Window Watchdog interrupt                                          */
  	(u32) &PVD_IRQHandler,              			/* PVD through EXTI line detection interrupt                          */
  	(u32) &TAMP_STAMP_IRQHandler,       			/* Tamper and TimeStamp interrupts through the EXTI line              */
  	(u32) &RTC_WKUP_IRQHandler,         			/* RTC Wakeup interrupt through the EXTI line                         */
  	(u32) &FLASH_IRQHandler,            			/* Flash global interrupt                                             */
  	(u32) &RCC_IRQHandler,              			/* RCC global interrupt                                               */
  	(u32) &EXTI0_IRQHandler,            			/* EXTI Line0 interrupt                                               */
  	(u32) &EXTI1_IRQHandler,            			/* EXTI Line1 interrupt                                               */
  	(u32) &EXTI2_IRQHandler,            			/* EXTI Line2 interrupt                                               */
  	(u32) &EXTI3_IRQHandler,            			/* EXTI Line3 interrupt                                               */
  	(u32) &EXTI4_IRQHandler,            			/* EXTI Line4 interrupt                                               */
  	(u32) &DMA1_Stream0_IRQHandler,     			/* DMA1 Stream0 global interrupt                                      */
  	(u32) &DMA1_Stream1_IRQHandler,     			/* DMA1 Stream1 global interrupt                                      */
  	(u32) &DMA1_Stream2_IRQHandler,     			/* DMA1 Stream2 global interrupt                                      */
  	(u32) &DMA1_Stream3_IRQHandler,     			/* DMA1 Stream3 global interrupt                                      */
  	(u32) &DMA1_Stream4_IRQHandler,     			/* DMA1 Stream4 global interrupt                                      */
  	(u32) &DMA1_Stream5_IRQHandler,     			/* DMA1 Stream5 global interrupt                                      */
  	(u32) &DMA1_Stream6_IRQHandler,     			/* DMA1 Stream6 global interrupt                                      */
  	(u32) &ADC_IRQHandler,              			/* ADC2 global interrupts                                             */
  	(u32) &CAN1_TX_IRQHandler,          			/* CAN1 TX interrupts                                                 */
  	(u32) &CAN1_RX0_IRQHandler,         			/* CAN1 RX0 interrupts                                                */
  	(u32) &CAN1_RX1_IRQHandler,         			/* CAN1 RX1 interrupts                                                */
  	(u32) &CAN1_SCE_IRQHandler,         			/* CAN1 SCE interrupt                                                 */
  	(u32) &EXTI9_5_IRQHandler,          			/* EXTI Line[9:5] interrupts                                          */
  	(u32) &TIM1_BRK_TIM9_IRQHandler,    			/* TIM1 Break interrupt and TIM9 global interrupt                     */
  	(u32) &TIM1_UP_TIM10_IRQHandler,    			/* TIM1 Update interrupt and TIM10 global interrupt                   */
  	(u32) &TIM1_TRG_COM_TIM11_IRQHandler,		/* TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
  	(u32) &TIM1_CC_IRQHandler,          			/* TIM1 Capture Compare interrupt                                     */
  	(u32) &TIM2_IRQHandler,             			/* TIM2 global interrupt                                              */
  	(u32) &TIM3_IRQHandler,             			/* TIM3 global interrupt                                              */
  	(u32) &TIM4_IRQHandler,             			/* TIM4 global interrupt                                              */
  	(u32) &I2C1_EV_IRQHandler,          			/* I2C1 event interrupt                                               */
  	(u32) &I2C1_ER_IRQHandler,          			/* I2C1 error interrupt                                               */
  	(u32) &I2C2_EV_IRQHandler,          			/* I2C2 event interrupt                                               */
  	(u32) &I2C2_ER_IRQHandler,          			/* I2C2 error interrupt                                               */
  	(u32) &SPI1_IRQHandler,             			/* SPI1 global interrupt                                              */
  	(u32) &SPI2_IRQHandler,             			/* SPI2 global interrupt                                              */
  	(u32) &USART1_IRQHandler,           			/* USART1 global interrupt                                            */
  	(u32) &USART2_IRQHandler,           			/* USART2 global interrupt                                            */
  	(u32) &USART3_IRQHandler,           			/* USART3 global interrupt                                            */
  	(u32) &EXTI15_10_IRQHandler,        			/* EXTI Line[15:10] interrupts                                        */
  	(u32) &RTC_Alarm_IRQHandler,        			/* RTC Alarms (A and B) through EXTI line interrupt                   */
  	(u32) &OTG_FS_WKUP_IRQHandler,      			/* USB On-The-Go FS Wakeup through EXTI line interrupt                */
  	(u32) &TIM8_BRK_TIM12_IRQHandler,   			/* TIM8 Break interrupt and TIM12 global interrupt                    */
  	(u32) &TIM8_UP_TIM13_IRQHandler,    			/* TIM8 Update interrupt and TIM13 global interrupt                   */
  	(u32) &TIM8_TRG_COM_TIM14_IRQHandler,		/* TIM8 Trigger and Commutation interrupts and TIM14 global interrupt */
  	(u32) &TIM8_CC_IRQHandler,          			/* TIM8 Capture Compare interrupt                                     */
  	(u32) &DMA1_Stream7_IRQHandler,     			/* DMA1 Stream7 global interrupt                                      */
  	(u32) &FMC_IRQHandler,              			/* FMC global interrupt                                               */
  	(u32) &SDIO_IRQHandler,             			/* SDIO global interrupt                                              */
  	(u32) &TIM5_IRQHandler,             			/* TIM5 global interrupt                                              */
  	(u32) &SPI3_IRQHandler,             			/* SPI3 global interrupt                                              */
  	(u32) &UART4_IRQHandler,            			/* UART4 global interrupt                                             */
  	(u32) &UART5_IRQHandler,            			/* UART5 global interrupt                                             */
  	(u32) &TIM6_DAC_IRQHandler,         			/* TIM6 global interrupt, DAC1 and DAC2 underrun error interrupt      */
  	(u32) &TIM7_IRQHandler,             			/* TIM7 global interrupt                                              */
  	(u32) &DMA2_Stream0_IRQHandler,     			/* DMA2 Stream0 global interrupt                                      */
  	(u32) &DMA2_Stream1_IRQHandler,     			/* DMA2 Stream1 global interrupt                                      */
  	(u32) &DMA2_Stream2_IRQHandler,     			/* DMA2 Stream2 global interrupt                                      */
  	(u32) &DMA2_Stream3_IRQHandler,     			/* DMA2 Stream3 global interrupt                                      */
  	(u32) &DMA2_Stream4_IRQHandler,     			/* DMA2 Stream4 global interrupt                                      */
  	(u32) &ETH_IRQHandler,              			/* Ethernet global interrupt                                          */
  	(u32) &ETH_WKUP_IRQHandler,         			/* Ethernet Wakeup through EXTI line interrupt                        */
  	(u32) &CAN2_TX_IRQHandler,          			/* CAN2 TX interrupts                                                 */
  	(u32) &CAN2_RX0_IRQHandler,         			/* CAN2 RX0 interrupts                                                */
  	(u32) &CAN2_RX1_IRQHandler,         			/* CAN2 RX1 interrupts                                                */
  	(u32) &CAN2_SCE_IRQHandler,         			/* CAN2 SCE interrupt                                                 */
  	(u32) &OTG_FS_IRQHandler,           			/* USB On The Go FS global interrupt                                  */
  	(u32) &DMA2_Stream5_IRQHandler,     			/* DMA2 Stream5 global interrupt                                      */
  	(u32) &DMA2_Stream6_IRQHandler,     			/* DMA2 Stream6 global interrupt                                      */
  	(u32) &DMA2_Stream7_IRQHandler,     			/* DMA2 Stream7 global interrupt                                      */
  	(u32) &USART6_IRQHandler,           			/* USART6 global interrupt                                            */
  	(u32) &I2C3_EV_IRQHandler,          			/* I2C3 event interrupt                                               */
  	(u32) &I2C3_ER_IRQHandler,          			/* I2C3 error interrupt                                               */
  	(u32) &OTG_HS_EP1_OUT_IRQHandler,   			/* USB On The Go HS End Point 1 Out global interrupt                  */
  	(u32) &OTG_HS_EP1_IN_IRQHandler,    			/* USB On The Go HS End Point 1 In global interrupt                   */
  	(u32) &OTG_HS_WKUP_IRQHandler,      			/* USB On The Go HS Wakeup through EXTI interrupt                     */
  	(u32) &OTG_HS_IRQHandler,           			/* USB On The Go HS global interrupt                                  */
  	(u32) &DCMI_IRQHandler,             			/* DCMI global interrupt                                              */
  	(u32) &CRYP_IRQHandler,             			/* CRYP crypto global interrupt                                       */
  	(u32) &HASH_RNG_IRQHandler,         			/* Hash and Rng global interrupt                                      */
  	(u32) &FPU_IRQHandler,              			/* FPU interrupt                                                      */
  	(u32) &UART7_IRQHandler,            			/* UART 7 global interrupt                                            */
  	(u32) &UART8_IRQHandler,            			/* UART 8 global interrupt                                            */
  	(u32) &SPI4_IRQHandler,             			/* SPI 4 global interrupt                                             */
  	(u32) &SPI5_IRQHandler,             			/* SPI 5 global interrupt                                             */
  	(u32) &SPI6_IRQHandler,             			/* SPI 6 global interrupt                                             */
  	(u32) &SAI1_IRQHandler,             			/* SAI1 global interrupt                                              */
  	(u32) &LCD_TFT_IRQHandler,          			/* LTDC global interrupt                                              */
  	(u32) &LCD_TFT_1_IRQHandler,        			/* LTDC global error interrupt                                        */
  	(u32) &DMA2D_IRQHandler             			/* DMA2D global interrupt                                             */
};

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Default_Handler(void){
    while (1);
}


void Reset_Handler(void){
    // Copy .data section from FLASH to RAM 
    u32 size = (u32)&_edata - (u32)&_sdata;
    u8 *pSrc = (u8 *) &_etext;
    u8 *pDst = (u8 *) &_sdata;
    for(u32 i = 0; i < size; i++){
        *pDst++ = *pSrc++;
    }

    // Initialize .bss section to zero in RAM
    size  = &_ebss - &_sbss;
    pDst = (u8 *) &_sbss;
    for(u32 i = 0; i < size; i++){
        *pDst++ = 0; 
    }
      
    // Call main
    main();
}

