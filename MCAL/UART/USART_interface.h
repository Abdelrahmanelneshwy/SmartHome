/*****************************************************************/
/* Author  : Abdelrhaman                                         */
/* Layer   : MCAL                                                */
/* SWC     : USART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Aug 2023                                         */
/*****************************************************************/
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


void UART_voidInit(void);
void UART_voidSend(uint16 u16Data);
tenuErrorStatus UART_enuRecieve(uint16* pu16Data);
void UART_voidSendString(uint16 *_pu16Data,uint8 _u8bufferSize);

void UART_voidEnableIntRXComp(void);  //RX complete
void UART_voidDisableIntRXComp(void);


void UART_voidEnableIntTXComp(void);  //TX complete
void UART_voidDisableIntTXComp(void);

void UART_voidEnableIntTXEmpty(void);  //TX Data Reg. empty
void UART_voidDisableIntTXEmpty(void);













#endif
