/*****************************************************************/
/* Author  : Abdelrhaman                                         */
/* Layer   : MCAL                                                */
/* SWC     : USART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Aug 2023                                         */
/*****************************************************************/
#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_


#define UART_ASYNCH_OP         0
#define UART_SYNCH_OP          1

#define UART_PARITY_DIS        0
#define UART_PARITY_EVEN       2
#define UART_PARITY_ODD        3

#define UART_1BIT_STOP         0
#define UART_2BITS_STOP        1

#define UART_5BITS_DATA        0
#define UART_6BITS_DATA        1
#define UART_7BITS_DATA        2
#define UART_8BITS_DATA        3
#define UART_9BITS_DATA        7


#define UART_SETUP_RISING   2
#define UART_SETUP_FALLING  4

#define UART_BUAD_RATE_2400      207
#define UART_BUAD_RATE_4800      103

#define UART_BUAD_RATE_9600      103
#define UART_BUAD_RATE_14400     34
#define UART_BUAD_RATE_115200    8




#define UDR     *((volatile uint8 * )0x2C)
#define UCSRA   *((volatile uint8 * )0x2B)
#define UCSRB   *((volatile uint8 * )0x2A)
#define UCSRC   *((volatile uint8 * )0x40)
#define UBRRH   *((volatile uint8 * )0x40)
#define UBRRL   *((volatile uint8 * )0x29)


#endif
