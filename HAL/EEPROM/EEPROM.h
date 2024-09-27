/*********************************************************************/
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/



#ifndef EEPROM_H
#define EEPROM_H


tenuErrorStatus EEPROM_enuWriteByte(uint8 u8ChipNbCpy , uint8 u8ByteAddCpy , uint8 u8DataCpy);
tenuErrorStatus EEPROM_enuReadByte(uint8 u8ChipNbCpy , uint8 u8ByteAddCpy , uint8 * pu8DataCpy);




#endif
