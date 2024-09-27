/*********************************************************************/
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/ADC/ADC.h"
#include "LM35.h"
#include "LM35_private.h"


void LM35_vidinit()
{
	ADC_voidInit();
	ADC_voidEnable();
}
f32 LM35_f32Reading(uint8 u8ChannelCpy)
{
	f32 f32SensorReadingLoc;
	uint16 Local_uint16Val;
	Local_uint16Val = ADC_u16ReadSync(u8ChannelCpy);
	f32SensorReadingLoc = (((f32)Local_uint16Val*5)/1024)*100;
	return f32SensorReadingLoc;
}

