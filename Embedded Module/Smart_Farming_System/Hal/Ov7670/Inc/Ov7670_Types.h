/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Ov7670_Types.h
 *		  Layer:  Hal
 *       Module:  Ov7670
 *		Version:  1.00
 *	
 *  Description:  api type definitions of the Camera module
 *  
 *********************************************************************************************************************/
#ifndef CAMERA_TYPES_H
#define CAMERA_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "I2c_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Resolutions:-
 * 1) VGA 	-> 640x480
 * 2) QVGA 	-> 320x240
 * 3) QQVGA -> 160x120
 * 4) CIF 	-> 352x288
 * 5) QCIF	-> 176x144
 * 6) QQCIF -> 88x72
 * */
typedef enum{
	/* Raw Bayer Format */
	CAMERA_FMT_RAW_BAYER_RGB_VGA,

	/* Processed Bayer Format */
	CAMERA_FMT_PROCESSED_BAYER_RGB_VGA,
	CAMERA_FMT_PROCESSED_BAYER_RGB_QVGA,

	/* YUV Format */
	CAMERA_FMT_YUV_VGA,
	CAMERA_FMT_YUV_QVGA,
	CAMERA_FMT_YUV_QQVGA,
	CAMERA_FMT_YUV_CIF,
	CAMERA_FMT_YUV_QCIF,
	CAMERA_FMT_YUV_QQCIF,

	/* GRB 4:2:2 Format */
	CAMERA_FMT_GRB_VGA,
	CAMERA_FMT_GRB_QVGA,
	CAMERA_FMT_GRB_QQVGA,
	CAMERA_FMT_GRB_CIF,
	CAMERA_FMT_GRB_QCIF,
	CAMERA_FMT_GRB_QQCIF,

	/* GRB565 Format */
	CAMERA_FMT_RGB565_VGA,
	CAMERA_FMT_RGB565_QVGA,
	CAMERA_FMT_RGB565_QQVGA,
	CAMERA_FMT_RGB565_CIF,
	CAMERA_FMT_RGB565_QCIF,
	CAMERA_FMT_RGB565_QQCIF,

	/* GRB555 Format */
	CAMERA_FMT_RGB555_VGA,
	CAMERA_FMT_RGB555_QVGA,
	CAMERA_FMT_RGB555_QQVGA,
	CAMERA_FMT_RGB555_CIF,
	CAMERA_FMT_RGB555_QCIF,
	CAMERA_FMT_RGB555_QQCIF,
}Camera_Format_t;

typedef enum{
	CAMERA_CONTINUOS_CAP,
	CAMERA_SINGLE_CAP,
}Camera_CaptureMode_t;

typedef struct {
    Camera_Format_t Fmt;
    Camera_CaptureMode_t CaptMode;
}Camera_Config_t;

typedef enum{
    Ov7670_I2C1=0,
    Ov7670_I2C2,
    Ov7670_I2C3,
}Ov7670_I2cId_t;

#endif  /* CAMERA_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Ov7670_Types.h
 *********************************************************************************************************************/
