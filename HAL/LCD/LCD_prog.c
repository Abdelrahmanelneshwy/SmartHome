/*
 * LCD_prog.c
 *
 * Created: 8/17/2024 2:06:16 PM
 *  Author: AMIT
 */ 

#include "../../LIB/BIT_MATH.h" 
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"

#define  F_CPU 16000000UL 
#include <util/delay.h>


void LCD_voidSHD(uint8  copy_uint8data) {
	
	uint8 LCD_PINS[4]={LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN} ;
	uint8 LOC_uint8in=0 ;
		for(LOC_uint8in=0;LOC_uint8in<4;LOC_uint8in++)
	    {
			DIO_enuWritePin(LCD_PINS[LOC_uint8in],GET_BIT(copy_uint8data,LOC_uint8in)) ;
		}
	
	
	
}

void LCD_voidSendEnable(){
	
	 /*Send enable pulse*/
	 DIO_enuWritePin(LCD_EN_PIN,DIO_HIGH) ;
	 _delay_ms(2) ;
	 DIO_enuWritePin(LCD_EN_PIN,DIO_LOW) ;
}

void LCD_voidSendData(uint8 copy_uint8data){
		/*make rs as DIO_HIGH to send data  */
		DIO_enuWritePin(LCD_RS_PIN,DIO_HIGH) ;
		/*make rw as DIO_LOW to write command   */
		DIO_enuWritePin(LCD_RW_PIN,DIO_LOW) ;
	#if LCD_MODE == _4_BIT_MODE
	LCD_voidSHD(copy_uint8data>>4) ;  // 1100 1100
	LCD_voidSendEnable() ;
	LCD_voidSHD(copy_uint8data) ;
	LCD_voidSendEnable() ;
	#elif LCD_MODE ==_8_BIT_MODE
	/* send command */
	DIO_voidSetPortVal(LCD_DPORT,copy_uint8data) ;  //  0B11100111
	LCD_voidSendEnable() ;
	#endif
	

	
		
	
}
void LCD_voidSendCommand(uint8 copy_uint8command){
	
	/*make rs as DIO_LOW to send command  */
	DIO_enuWritePin(LCD_RS_PIN,DIO_LOW) ;
	/*make rw as DIO_LOW to write command   */
	DIO_enuWritePin(LCD_RW_PIN,DIO_LOW) ;
	
	#if LCD_MODE == _4_BIT_MODE 
	  LCD_voidSHD(copy_uint8command>>4) ;  // 1100 1100
	   LCD_voidSendEnable() ; 
	  LCD_voidSHD(copy_uint8command) ;
	   LCD_voidSendEnable() ;
	#elif LCD_MODE ==_8_BIT_MODE    
	/* send command */
	 DIO_voidSetPortVal(LCD_DPORT,copy_uint8command) ;  //  0B11100111
	 LCD_voidSendEnable() ; 
   #endif 
	 

	 
	
}
void LCD_voidInit(void){
	 _delay_ms(40) ; 
	 
	 #if LCD_MODE== _8_BIT_MODE
	 /*send command function set */
	 LCD_voidSendCommand(0b00111000) ; 
	 #elif LCD_MODE ==_4_BIT_MODE 
	     
		  LCD_voidSHD(0b0010) ; 
		  LCD_voidSendEnable() ; 
		  LCD_voidSHD(0b0010) ;
		  LCD_voidSendEnable() ;
		  LCD_voidSHD(0b1000) ; 
		  LCD_voidSendEnable() ;
	#endif 	  
	 /*send command  display on/off */
	 LCD_voidSendCommand(0b00001100) ; 
	 /*send command   LCD CLR */
	 LCD_voidSendCommand(1) ;
	
}


void LCD_voidSendString(uint8*str){
	
	uint8 i=0 ;
	while(str[i] !='\0'){
		
		LCD_voidSendData(str[i]) ; 
		i++ ; 
	}
	
	
	
	
}
void LCD_voidGotoxy(uint8 copy_uint8x,uint8 copyuint8y){
	/* set address */
	uint8 ddram_address= copy_uint8x+copyuint8y*0x40 ;
	
	 /*set DDRAM */
	 SET_BIT(ddram_address,7) ;  // set bit7 in ddram 
	 
	 LCD_voidSendCommand(ddram_address) ; 
}
void LCD_voidDrawData(uint8 pattern , uint8*data , uint8 x , uint8 y){
	  uint8 loc_i=0 ;
	  uint8 address_CGRAM=pattern*8 ;  // set address
	  /* set CGRAM */
	  CLR_BIT(address_CGRAM,7) ; 
	  SET_BIT(address_CGRAM,6) ; 
	  LCD_voidSendCommand(address_CGRAM) ; 
	  
	  /* draw data in CGRAM */
	  for (loc_i=0 ; loc_i<8 ;loc_i++)
	  {
		   LCD_voidSendData(data[loc_i]) ;   
	  }
	  LCD_voidGotoxy(x,y) ; 
	  LCD_voidSendData(pattern) ; 
	  
	  
	
	
}
void LCD_voidSendNumber(uint32 number){
	
	sint8 i=0;
	uint8 array[10] ;
	
	if(number==0){
		
		LCD_voidSendData('0') ;
		return ;
	}
	for(i=0; number!=0 ;i++){
		
		array[i]= number % 10 + 48 ;
		number /= 10 ;
	}
	i-- ;
	while(i >= 0){
		
		LCD_voidSendData(array[i]) ;
		i-- ;
	}
}
