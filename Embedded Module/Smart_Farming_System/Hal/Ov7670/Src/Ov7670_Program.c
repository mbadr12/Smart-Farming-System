/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  OV7670_Program.c
 *		  Layer:  Hal
 *       Module:  OV7670
 *		Version:  1.00
 *
 *  Description:  implementation of the Camera module
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Bit_Math.h"

#include "Ov7670_Config.h"
#include "Ov7670_Interface.h"
#include "Ov7670_Private.h"
#include "Ov7670_Types.h"

#include "Dcmi_Interface.h"
#include "Dma_Types.h"
#include "I2c_Interface.h"

#include "Dma_Interface.h"
#include "Gpio_Interface.h"
#include "I2c_Types.h"
#include "Nvic_Interface.h"
#include "Rcc_Interface.h"
#include "SysTick_Interface.h"

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
/*
 * 1. Format is YUV
 * 2. Resolution is vga
 * 3. Downscale by 2
 * 4. No zoom out
 * 5. No windowing since we're using vsync
 * 6. Gamma enabled and the curve used is gamma 2.2
 * 7. Automatic saturation Enabled
 * 8. Color matrix is set by values recommended by Omnivision.
 * 9. Do not use raw input clock we use the camera PLL (Div by 2 then mul by 2)
 * it's more accurate (better images).
 * 10. Down scaled by 4
 *
 * */


/* QVGA RESOLUTION (320x240) YUV FORMAT 
 * 1. CLKRC = 0x01 -> Divide input clock by 2
 * 2. COM7 = 0x00 -> Choose YUV format.
 * 3. COM3 = 0x04 -> Enable Down sampling circuitry.
 * 4. COM14 = 0x19 -> Enable PCLK scaling & Divide pclk by 2.
 * 5. SCALING_XSC = 0x3A -> Scaling ratio of x is about 0.5 (Why is this needed?)
 * 6. SCALING_YSC = 0x35 -> Scaling ratio of y is about 0.5 (Why is this needed?)
 * 7. SCALING_DCWCTR = 0x11 -> Horizontal down sampling by 2 & Vertical down sampling by 2
 * 8. SCALING_PCLK_DIV = 0xF1 -> Divide pclk by 2. Note: Has to follow what we did in the COM14 register.
 * 9. SCALING_PCLK_DELAY = 0x02
 * */


volatile u8 OV7670_Frame[OV7670_FRAME_SIZE];


static s16 Ov7670_RegVal[OV7670_REG_NUM] = {
    CAM_REG_LEAVE_DEFAULT, /* GAIN Register */
    CAM_REG_LEAVE_DEFAULT, /* BLUE Register */
    CAM_REG_LEAVE_DEFAULT, /* RED Register */
    CAM_REG_LEAVE_DEFAULT, /* VREF Register */
    0x00,                  // disable CCIR656 format /* COM1 Register */
    CAM_REG_LEAVE_DEFAULT, /* BAVE Register */
    CAM_REG_LEAVE_DEFAULT, /* Gbave Register */
    CAM_REG_LEAVE_DEFAULT, /* AECHH Register */
    CAM_REG_LEAVE_DEFAULT, /* RAVE Register */
    CAM_REG_LEAVE_DEFAULT, /* COM2 Register */
    CAM_REG_LEAVE_DEFAULT, /* PID Register */
    CAM_REG_LEAVE_DEFAULT, /* VER Register */
    0x04, // enable down sampling  /* COM3 Register */
    CAM_REG_LEAVE_DEFAULT, /* COM4 Register */
    CAM_REG_LEAVE_DEFAULT, /* COM5 Register */
    CAM_REG_LEAVE_DEFAULT, /* COM6 Register */
    CAM_REG_LEAVE_DEFAULT, /* AECH Register */
    0x02,                  // div input clock by 4 (Note: we then multiply it by 4 using internal PLL to get the exact input clock) /* CLKRC Register */
    0x00,                  // select YUV format /* COM7 Register */
    CAM_REG_LEAVE_DEFAULT, /* COM8 Register */
    CAM_REG_LEAVE_DEFAULT, /* COM9 Register */
    CAM_REG_LEAVE_DEFAULT, /* COM10 Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT, /* HSTART Register */
    CAM_REG_LEAVE_DEFAULT, /* HSTOP Register */
    CAM_REG_LEAVE_DEFAULT, /* VSTART Register */
    CAM_REG_LEAVE_DEFAULT, /* VSTOP Register */
    CAM_REG_LEAVE_DEFAULT, /* PSHFT Register */
    CAM_REG_LEAVE_DEFAULT, /* MIDH Register */
    CAM_REG_LEAVE_DEFAULT, /* MIDL Register */
    CAM_REG_LEAVE_DEFAULT, /* MVFP Register */
    CAM_REG_LEAVE_DEFAULT, /* LAEC Register */
    CAM_REG_LEAVE_DEFAULT, /* ADCCTR0 Register */
    CAM_REG_LEAVE_DEFAULT, /* ADCCTR1 Register */
    CAM_REG_LEAVE_DEFAULT, /* ADCCTR2 Register */
    CAM_REG_LEAVE_DEFAULT, /* ADCCTR3 Register */
    CAM_REG_LEAVE_DEFAULT, /* AEW Register */
    CAM_REG_LEAVE_DEFAULT, /* AEB Register */
    CAM_REG_LEAVE_DEFAULT, /* VPT Register */
    CAM_REG_LEAVE_DEFAULT, /* BBIAS Register */
    CAM_REG_LEAVE_DEFAULT, /* GbBIAS Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT, /* EXHCH Register */
    CAM_REG_LEAVE_DEFAULT, /* EXHCL Register */
    CAM_REG_LEAVE_DEFAULT, /* RBIAS Register */
    CAM_REG_LEAVE_DEFAULT, /* ADVFL Register */
    CAM_REG_LEAVE_DEFAULT, /* ADVFH Register */
    CAM_REG_LEAVE_DEFAULT, /* YAVE Register */
    CAM_REG_LEAVE_DEFAULT, /* HSYST Register */
    CAM_REG_LEAVE_DEFAULT, /* HSYEN Register */
    CAM_REG_LEAVE_DEFAULT, /* HREF Register */
    CAM_REG_LEAVE_DEFAULT, /* CHLF Register */
    CAM_REG_LEAVE_DEFAULT, /* ARBLM Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT, /* ADC Register */
    CAM_REG_LEAVE_DEFAULT, /* ACOM Register */
    CAM_REG_LEAVE_DEFAULT, /* OFON Register */
    CAM_REG_LEAVE_DEFAULT, /* TSLB Register */
    CAM_REG_LEAVE_DEFAULT, /* COM11 Register */
    CAM_REG_LEAVE_DEFAULT, /* COM12 Register */
    0xc0,
    /* COM13 Register */   // enable gamma and automaic saturation
    CAM_REG_LEAVE_DEFAULT, /* COM14 Register */
    CAM_REG_LEAVE_DEFAULT, /* EDGE Register */
    CAMERA_COM15_RANGE_00_FF,
    /* COM15 Register */ // output full range (0x00 -> 0xFF)
    0x38,
    /* COM16 Register */   // enable edge enhancement, de-noise, AWB gain
    CAM_REG_LEAVE_DEFAULT, /* COM17 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWBC1 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWBC2 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWBC3 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWBC4 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWBC5 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWBC6 Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT, /* REG4B Register */
    CAM_REG_LEAVE_DEFAULT, /* DNSTH Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    0x80,                  /* MTX1 Register */
    0x80,                  /* MTX2 Register */
    0x00,                  /* MTX3 Register */
    0x22,                  /* MTX4 Register */
    0x5e,                  /* MTX5 Register */
    0x80,                  /* MTX6 Register */
    CAM_REG_LEAVE_DEFAULT, /* BRIGHT Register */
    CAM_REG_LEAVE_DEFAULT, /* CONTRAS Register */
    CAM_REG_LEAVE_DEFAULT, /* CONTRAS-CENTER Register */
    0x9e,                  /* MTXS Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT, /* LCC1 Register */
    CAM_REG_LEAVE_DEFAULT, /* LCC2 Register */
    CAM_REG_LEAVE_DEFAULT, /* LCC3 Register */
    CAM_REG_LEAVE_DEFAULT, /* LCC4 Register */
    CAM_REG_LEAVE_DEFAULT, /* LCC5 Register */
    CAM_REG_LEAVE_DEFAULT, /* MANU Register */
    CAM_REG_LEAVE_DEFAULT, /* MANV Register */
    CAM_REG_LEAVE_DEFAULT, /* GFIX Register */
    CAM_REG_LEAVE_DEFAULT, /* GGAIN Register */
    0x40, /* DBLV Register */    // PLL input clock * 4
    CAM_REG_LEAVE_DEFAULT, /* AWCTR3 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWCTR2 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWCTR1 Register */
    CAM_REG_LEAVE_DEFAULT, /* AWCTR0 Register */
    0x3A,
    /* SCALING_XSC Register */ // the zoom out circuit does about 0.5 scaling if enabled (if x0.5
                               // then 0x40)
    0x35,
    /* SCALING_YSC Register */ // the zoom out circuit does about 0.5 scaling if enabled (if x0.5
                               // then 0x40)
    0x11,
    /* SCALING_DCWCTR Register */ // vertical/horizontal down sample by 2 (0x22
                                  // -> by 4, 0x33 -> by 8)
    0xF1,
    /* SCALING_PCLK_DIV Register */ // since we downscaled by 2 then 0x01 (if by
                                    // 4 then 0x02, by 8 then 0x03)
    CAM_REG_LEAVE_DEFAULT,          /* REG74 Register */
    CAM_REG_LEAVE_DEFAULT,          /* REG75 Register */
    CAM_REG_LEAVE_DEFAULT,          /* REG76 Register */
    CAM_REG_LEAVE_DEFAULT,          /* REG77 Register */
    CAM_REG_RESERVED,               /* RSVD Register */
    CAM_REG_RESERVED,               /* RSVD Register */
    32,
    /* SLOP Register */    /* Gamma curve 2.2 values */
    39,                    /* GAM1 Register */
    53,                    /* GAM2 Register */
    73,                    /* GAM3 Register */
    99,                    /* GAM4 Register */
    110,                   /* GAM5 Register */
    120,                   /* GAM6 Register */
    128,                   /* GAM7 Register */
    136,                   /* GAM8 Register */
    144,                   /* GAM9 Register */
    151,                   /* GAM10 Register */
    164,                   /* GAM11 Register */
    176,                   /* GAM12 Register */
    197,                   /* GAM13 Register */
    216,                   /* GAM14 Register */
    232,                   /* GAM15 Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    0x00,                  // disable RGB444 format     /* RGB444 Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT, /* DM_LNL Register */
    CAM_REG_LEAVE_DEFAULT, /* DM_LNH Register */
    CAM_REG_LEAVE_DEFAULT, /* LCC6 Register */
    CAM_REG_LEAVE_DEFAULT, /* LCC7 Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT, /* BD50ST Register */
    CAM_REG_LEAVE_DEFAULT, /* BD60ST Register */
    CAM_REG_LEAVE_DEFAULT, /* HAECC1 Register */
    CAM_REG_LEAVE_DEFAULT, /* HAECC2 Register */
    CAM_REG_RESERVED,      /* RSVD Register */
    0x02,
    /* SCALING_PCLK_DELAY Register */ // Do not need delay since the scalling is
                                      // a multiple of the original vga size (set it to two as mentioned in datasheet).
                                      // This register is related to COM14 if we
                                      // choose a predefine preset
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT,            /* NT_CTRL Register */
    CAM_REG_LEAVE_DEFAULT,            /* BD50MAX Register */
    CAM_REG_LEAVE_DEFAULT,            /* HAECC3 Register */
    CAM_REG_LEAVE_DEFAULT,            /* HAECC4 Register */
    CAM_REG_LEAVE_DEFAULT,            /* HAECC5 Register */
    CAM_REG_LEAVE_DEFAULT,            /* HAECC6 Register */
    CAM_REG_LEAVE_DEFAULT,            /* HAECC7 Register */
    CAM_REG_LEAVE_DEFAULT,            /* BD60MAX Register */
    CAM_REG_LEAVE_DEFAULT,            /* STR-OPT Register */
    CAM_REG_LEAVE_DEFAULT,            /* STR_R Register */
    CAM_REG_LEAVE_DEFAULT,            /* STR_G Register */
    CAM_REG_LEAVE_DEFAULT,            /* STR_B Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT,            /* ABLC1 Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT,            /* THL_ST Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT,            /* THL_DLT Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT,            /* AD-CHB Register */
    CAM_REG_LEAVE_DEFAULT,            /* AD-CHR Register */
    CAM_REG_LEAVE_DEFAULT,            /* AD-CHGb Register */
    CAM_REG_LEAVE_DEFAULT,            /* AD-CHGr Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_RESERVED,                 /* RSVD Register */
    CAM_REG_LEAVE_DEFAULT,            /* SATCTR Register */
};

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS0x21
 *********************************************************************************************************************/
static ErrorState_t OV7670_Write(I2c_Handle_t *hi2c, u8 Copy_Addr, u8 Copy_Data) {
    ErrorState_t Local_ErrorState = E_OK;
    Local_ErrorState = I2c_Mem_Write(hi2c, OV7670_SLAVE_ADDR, I2C_MEMADD_SIZE_8BIT, Copy_Addr, &Copy_Data, 1, SYSTICK_MAX_DELAY);
    return Local_ErrorState;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t Ov7670_Init(I2c_Id_t Copy_I2cId)

 * \Description     : Initilization of the I2c and DCMI interfaces used by the camera.
 *                  Initilization of the OV7670 internal registers
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : I2c_Id_t : I2c interface Id.
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Ov7670_Init(I2c_Id_t Copy_I2cId) {
	OV7670_Frame[0] = 123;
  /* Initialize I2c */
  I2c_Handle_t hi2c;
  hi2c.Id = Copy_I2cId;
  hi2c.Config.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c.Config.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c.Config.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  hi2c.Config.ClockSpeed = 100000;
  hi2c.Config.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c.Config.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c.Config.OwnAddress1 = 0;
  hi2c.Config.OwnAddress1 = 0;
  hi2c.State = I2C_STATE_RESET;
  I2c_Init(&hi2c);

  /* Initialize DCMI */
  Dcmi_Init();

  /* Hardware reset */
  Gpio_WritePin(GPIO_PIN_E0, LOW);
  SysTick_Delay(100);
  Gpio_WritePin(GPIO_PIN_E0, HIGH);
  SysTick_Delay(100);

  /* Reset registers using software (0x12 -> COM7)*/
  OV7670_Write(&hi2c, 0x12, CAMERA_CMD_RESET);

  /* Delay for 1ms settling time after reset (MAX = 1ms) */
  SysTick_Delay(30);

  /* Write configs to registers */
  for (u32 i = 0; i < OV7670_REG_NUM; i++) {
    s16 Local_Val = Ov7670_RegVal[i];
    if (Local_Val != CAM_REG_LEAVE_DEFAULT && Local_Val != CAM_REG_RESERVED) {
      if (OV7670_Write(&hi2c, i, Ov7670_RegVal[i]) != E_OK) {
        return E_NOK;
      }
    }
  }
  return E_OK;
}

/******************************************************************************
 * \Syntax          : ErrorState_t OV7670_SnapShot(void (*Frame_Cplt)(void))

 * \Description     : Capture an image via the DCMI interface and transfer the receved frame 
 *                  to a buffer in SRAM via DMA.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : Frame_Cplt : a pointer to a notification function called when frame is complete.
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t OV7670_SnapShot(void (*Frame_Cplt)(void)) {
  Dma_StreamStartTrans Local_StartTransaction = {
      .Stream = DMA_STREAM_1,
      .DMA_Number = DMA_2,
      .NumberOfTrans = (u16)(OV7670_FRAME_SIZE / 4),
      .DataDirection = DMA_PERIPHERAL_TO_MEMORY,
      .DestnationAddress = (u32 *)OV7670_Frame,
      .SourceAddress = DMA_DCMI,
      .SrcDestAddress2 = NULL,
  };

  Dma_StreamStartASynch(&Local_StartTransaction, Frame_Cplt);
  Dcmi_CaptureImage();
  return E_OK;
}

/**********************************************************************************************************************
 *  END OF FILE: OV7670_Program.c
 *********************************************************************************************************************/
