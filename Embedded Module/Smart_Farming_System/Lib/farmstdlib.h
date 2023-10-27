/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Musa Mahmoud, Mazen, Mahmoud Badr
 *	   	   File:  Aht21b_Interface.h
 *		  Layer:  Hal
 *       Module:  Aht21b
 *		Version:  1.0
 *
 *  Description:  A simple header file library that implements useful helper functions.
 *
 *********************************************************************************************************************/
#ifndef AHT21B_INTERFACE_H
#define AHT21B_INTERFACE_H


u16 strlen(char* Copy_Str)
{
	u16 Len=0;
	while(Copy_Str[Len] !='\0')
	{
		Len++;
	}
	return Len;
}

void itos(u16 Copy_Number, char* Copy_String)
{
	u8 Local_Length = 0;
	u8 Local_Counter=0;
	u16 Local_Rest=Copy_Number;
	while(Local_Rest !=0)
	{
		Local_Length++;
		Local_Rest/=10;
	}
	for(Local_Counter=0;Local_Counter<Local_Length;Local_Counter++)
	{
		Local_Rest=Copy_Number%10;
		Copy_Number/=10;
		Copy_String[Local_Length-Local_Counter-1]=Local_Rest+'0';
	}
	Copy_String[Local_Length]='\0';
}



#endif
/**********************************************************************************************************************
 *  END OF FILE: Aht21b_Interface.h
 *********************************************************************************************************************/
