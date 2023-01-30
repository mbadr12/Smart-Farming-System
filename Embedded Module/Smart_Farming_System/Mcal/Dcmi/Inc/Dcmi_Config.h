/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud, Mazen and Musa
 *	   	   File:  Dcmi_Config.h
 *		  Layer:  Mcal
 *       Module:  Dcmi
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef DCMI_CONFIG_H
#define DCMI_CONFIG_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*Choose Synch Source
 *1- HW		
 *2- EMBDEDD
*/
#define SYNCH_SOURCE EMBDEDD

/*Choose Number of Data Bits
 *1- EIGHT_BITS	
 *2- TEN_BITS	
 *3- TWELVE_BITS	
 *4- FOURTEEN_BITS
 */
#define DATA_BITS		FOURTEEN_BITS

/*Choose Capture mode
 *1- SNAPSHOT	
 *2- CONTENIOUS
 */
#define CAPTURE_MODE 	CONTENIOUS

/*Choose horizontal syncronization polarity
 *1- FALLING_EDGE
 *2- RAISING_EDGE
 */
#define HSYNCH_POLARITY	RAISING_EDGE

/*Choose vertical syncronization polarity
 *1- FALLING_EDGE
 *2- RAISING_EDGE
 */
#define VSYNCH_POLARITY RAISING_EDGE

/*Choose pixel clock polarity
 *1- FALLING_EDGE
 *2- RAISING_EDGE
 */
#define PXLCLK_POLARITY RAISING_EDGE


#endif  /* DCMI_CONFIG_H */

/**********************************************************************************************************************
 *  END OF FILE: Dcmi_Config.h
 *********************************************************************************************************************/
