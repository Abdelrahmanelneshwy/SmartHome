/*
 * LCD_interface.h
 *
 * Created: 8/17/2024 2:05:49 PM
 *  Author: AMIT
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/*LCD  mode */
/* you can select lcd mode */
#define  _4_BIT_MODE     0 
#define  _8_BIT_MODE     1 

#define  LCD_MODE  _4_BIT_MODE


void LCD_voidSendData(uint8 copy_uint8data) ;
void LCD_voidSendCommand(uint8 copy_uint8command) ;
void LCD_voidInit(void) ; 

void LCD_voidSendString(uint8*str) ;


void LCD_voidGotoxy(uint8 copy_uint8x,uint8 copyuint8y) ;


void LCD_voidDrawData(uint8 pattern , uint8*data , uint8 x , uint8 y) ;


void LCD_voidSendNumber(uint32 number) ;
#endif /* LCD_INTERFACE_H_ */
