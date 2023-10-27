/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Ov7670_Private.h
 *		  Layer:  Hal
 *       Module:  Ov7670
 *		Version:  1.00
 *
 *  Description:  private header for the Camera module
 *
 *********************************************************************************************************************/

#ifndef OV7670_PRIVATE_H
#define OV7670_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define REG_GAIN 0x00
#define REG_BLUE 0x01
#define REG_RED 0x02
#define REG_VREF 0x03
#define REG_COM1 0x04
#define REG_BAVE 0x05
#define REG_GbAVE 0x06
#define REG_AECHH 0x07
#define REG_RAVE 0x08
#define REG_COM2 0x09
#define REG_PID 0x0A
#define REG_VER 0x0B
#define REG_COM3 0x0C
#define REG_COM4 0x0D
#define REG_COM5 0x0E
#define REG_COM6 0x0F
#define REG_AECH 0x10
#define REG_CLKRC 0x11
#define REG_COM7 0x12
#define REG_COM8 0x13
#define REG_COM9 0x14
#define REG_COM10 0x15
#define REG_HSTART 0x17
#define REG_HSTOP 0x18
#define REG_VSTART 0x19
#define REG_VSTOP 0x1A
#define REG_PSHFT 0x1B
#define REG_MIDH 0x1C
#define REG_MIDL 0x1D
#define REG_MVFP 0x1E
#define REG_LAEC 0x1F
#define REG_ADCCTR0 0x20
#define REG_ADCCTR1 0x21
#define REG_ADCCTR2 0x22
#define REG_ADCCTR3 0x23
#define REG_AEW 0x24
#define REG_AEB 0x25
#define REG_VPT 0x26
#define REG_BBIAS 0x27
#define REG_GbBIAS 0x28
#define REG_EXHCH 0x2A
#define REG_EXHCL 0x2B
#define REG_RBIAS 0x2C
#define REG_ADVFL 0x2D
#define REG_ADVFH 0x2E
#define REG_YAVE 0x2F
#define REG_HSYST 0x30
#define REG_HSYEN 0x31
#define REG_HREF 0x32
#define REG_CHLF 0x33
#define REG_ARBLM 0x34
#define REG_ADC 0x37
#define REG_ACOM 0x38
#define REG_OFON 0x39
#define REG_TSLB 0x3A
#define REG_COM11 0x3B
#define REG_COM12 0x3C
#define REG_COM13 0x3D
#define REG_COM14 0x3E
#define REG_EDGE 0x3F
#define REG_COM15 0x40
#define REG_COM16 0x41
#define REG_COM17 0x42
#define REG_REG4B 0x4B
#define REG_DNSTH 0x4C
#define REG_MTX1 0x4F
#define REG_MTX2 0x50
#define REG_MTX3 0x51
#define REG_MTX4 0x52
#define REG_MTX5 0x53
#define REG_MTX6 0x54
#define REG_BRIGHT 0x55
#define REG_CONTRAS 0x56
#define REG_CONTRAS_CENTER 0x57
#define REG_MTXS 0x58
#define REG_LCC1 0x62
#define REG_LCC2 0x63
#define REG_LCC3 0x64

#define REG_RGB444 0x8C

#define CAM_REG_RESERVED -1
#define CAM_REG_LEAVE_DEFAULT -2
#define CAMERA_CMD_RESET 0x80
#define CAMERA_ARR_END 0xff

#define OV7670_SLAVE_ADDR 0x42
#define OV7670_REG_NUM 202UL
#define CAMERA_COM15_RANGE_00_FF 0xC0

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* OV7670_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Ov7670_Private.h
 *********************************************************************************************************************/
