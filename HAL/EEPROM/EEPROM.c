/*********************************************************************/
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/I2C/I2C.h"
#include "EEPROM.h"
tenuErrorStatus EEPROM_enuWriteByte(uint8 u8ChipNbCpy , uint8 u8ByteAddCpy , uint8 u8DataCpy)
{
	 
	I2C_voidStart();
	if(I2C_u8GetStatus() != I2C_START )
	{
		return ENOK ;
	}
	/* user send to me u8ChipAddCpy  contain A2A1A0*/
	I2C_voidWrite(0b10100000|(u8ChipNbCpy <<1));
	if(I2C_u8GetStatus() != I2C_MT_SLA_W_ACK )
	{
		return ENOK ;
	}
	I2C_voidWrite(u8ByteAddCpy);
	if(I2C_u8GetStatus() != I2C_MT_DATA_ACK )
	{
		return ENOK ;
	}
	I2C_voidWrite(u8DataCpy);	
	if(I2C_u8GetStatus() != I2C_MT_DATA_ACK )
	{
		return ENOK ;
	}
	I2C_voidStop();
	return EOK ;
}

tenuErrorStatus EEPROM_enuReadByte(uint8 u8ChipNbCpy , uint8 u8ByteAddCpy , uint8 * pu8DataCpy)
{
	I2C_voidStart();
	if(I2C_u8GetStatus() != I2C_START )
	{
		return 1 ;
	}
	I2C_voidWrite(0b10100000|(u8ChipNbCpy <<1));
	if(I2C_u8GetStatus() != I2C_MT_SLA_W_ACK )
	{
	//	return 2 ;
	}
	I2C_voidWrite(u8ByteAddCpy);
	if(I2C_u8GetStatus() != I2C_MT_DATA_ACK )
	{
	//	return 3 ;
	}
	/*Repeat start condition*/
	I2C_voidStart();
	if(I2C_u8GetStatus() != I2C_REPEAT_START )
	{
		return 4 ;
	}
	/* Chip select with read*/
	I2C_voidWrite(0b10100001|(u8ChipNbCpy <<1));
	if(I2C_u8GetStatus() != I2C_MT_SLA_R_ACK )
	{
		//return 5 ;
	}
	*pu8DataCpy = I2C_u8ReadWithoutAck();
	if(I2C_u8GetStatus() != I2C_MR_DATA_NACK )
	{
		return 6 ;
	}
	I2C_voidStop();
	return EOK ; 
}
