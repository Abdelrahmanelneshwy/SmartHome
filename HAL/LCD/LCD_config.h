/*
 * LCD_config.h
 *
 * Created: 8/17/2024 2:06:02 PM
 *  Author: AMIT
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_



#if LCD_MODE ==_8_BIT_MODE 

#define  LCD_DPORT    DIO_PORTA

#elif LCD_MODE ==_4_BIT_MODE 


#define  LCD_D4_PIN   DIO_PORT_A_NUM_A4
#define  LCD_D5_PIN   DIO_PORT_A_NUM_A5
#define  LCD_D6_PIN   DIO_PORT_A_NUM_A6
#define  LCD_D7_PIN   DIO_PORT_A_NUM_A7
#endif 



#define LCD_RS_PIN   DIO_PORT_B_NUM_B1
#define LCD_RW_PIN   DIO_PORT_B_NUM_B2
#define LCD_EN_PIN   DIO_PORT_B_NUM_B3






#endif /* LCD_CONFIG_H_ */
