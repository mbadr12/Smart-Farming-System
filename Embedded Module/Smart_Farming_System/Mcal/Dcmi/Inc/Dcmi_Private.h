/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud, Mazen and Musa
 *	   	   File:  Dcmi_Private.h
 *		  Layer:  Mcal
 *       Module:  Dcmi
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

#ifndef DCMI_PRIVATE_H
#define DCMI_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define HW				0x00
#define EMBDEDD			0x10

#define EIGHT_BITS		0x00
#define TEN_BITS		0x200
#define TWELVE_BITS		0x400
#define FOURTEEN_BITS	0xc00

#define CONTENIOUS		0x00
#define SNAPSHOT		0x02

#define FALLING_EDGE	0
#define RAISING_EDGE	1

#define VSPOL			7
#define HSPOL			6
#define PCKPOL			5
#define CAPTURE			1
#define ENABLE			0x4000
 
#endif  /* DCMI_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Dcmi_Private.h
 *********************************************************************************************************************/
