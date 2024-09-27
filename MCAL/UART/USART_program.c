/*****************************************************************/
/* Author  : Abdelrhaman                                         */
/* Layer   : MCAL                                                */
/* SWC     : USART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Aug 2023                                         */
/*****************************************************************/
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include <util/delay.h>
#include "USART_private.h"
#include "USART_config.h"
#include "USART_interface.h"

void UART_voidInit(void)
{

	uint8 u8TempBLoc = 0b00011000;
	uint8 u8TempCLoc = 0b10000000; //selsct UCSRC by set bit 7

#if UART_DATA_SIZE == UART_5BITS_DATA
CLR_BIT(u8TempCLoc,1);
CLR_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);
#elif UART_DATA_SIZE == UART_6BITS_DATA
SET_BIT(u8TempCLoc,1);
CLR_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);
#elif UART_DATA_SIZE == UART_7BITS_DATA
CLR_BIT(u8TempCLoc,1);
SET_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);

#elif UART_DATA_SIZE == UART_8BITS_DATA
SET_BIT(u8TempCLoc,1);
SET_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);

#elif UART_DATA_SIZE == UART_9BITS_DATA
SET_BIT(u8TempCLoc,1);
SET_BIT(u8TempCLoc,2);
SET_BIT(u8TempBLoc,2);

#else
/*default 8 */
SET_BIT(u8TempCLoc,1);
SET_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);

#endif


#if UART_MODE == UART_SYNCH_OP
SET_BIT(u8TempCLoc,6);
#else
CLR_BIT(u8TempCLoc,6);
#endif

#if UART_STOP_BIT ==  UART_1BIT_STOP
CLR_BIT(u8TempCLoc,3);
#else
SET_BIT(u8TempCLoc,3);
#endif


#if UART_PARITY == UART_PARITY_EVEN
CLR_BIT(u8TempCLoc,4);
SET_BIT(u8TempCLoc,5);

#elif UART_PARITY == UART_PARITY_ODD
SET_BIT(u8TempCLoc,4);
SET_BIT(u8TempCLoc,5);
#else
/* no parity*/
CLR_BIT(u8TempCLoc,4);
CLR_BIT(u8TempCLoc,5);
#endif
/* setup  --->send at syncronous mode */
#if  UART_CLOCK_POLARITY == UART_SETUP_RISING
CLR_BIT(u8TempCLoc,0);
#else
SET_BIT(u8TempCLoc,0);
#endif

UBRRH =(UART_BUAD_RATE>>8)& 0x0f ; // >8 bit
UBRRL =(uint8) UART_BUAD_RATE;

UCSRB=u8TempBLoc;
UCSRC=u8TempCLoc;
}

/*polling*/
void UART_voidSend(uint16 u16Data)
{
	while(GET_BIT(UCSRA,5) ==0);

#if UART_DATA_SIZE ==UART_9BITS_DATA
	if (GET_BIT(u16Data,8) == 0)
	{
		CLR_BIT(UCSRB,0);
	}
	else
	{
		SET_BIT(UCSRB,0);
	}
#endif
	UDR=u16Data;
}

tenuErrorStatus UART_enuRecieve(uint16* pu16Data)
{
	tenuErrorStatus ErrorState=EOK;

	uint8 u8checkError=0;
	uint8 u8ninebit;

	while(GET_BIT(UCSRA,7) ==0);
	u8checkError= UCSRA &0b00011100 ;
	if (u8checkError!=0)
	{
		ErrorState=ENOK;
	}
	else
	{
		#if UART_DATA_SIZE ==UART_9BITS_DATA
			u8ninebit=GET_BIT(UCSRB,1);

			*pu16Data = u8ninebit<<8  | UDR ;
		#else
			{
				*pu16Data =UDR;
			}

		#endif
	}
	return  ErrorState;
}

void UART_voidSendString(uint16 *_pu16Data,uint8 _u8bufferSize){
	uint8 loc_itr=0;
	for(loc_itr = 0 ; loc_itr < _u8bufferSize ; loc_itr++)
	{
		UART_voidSend(_pu16Data[loc_itr]);
	}
}
//RX complete
void UART_voidEnableIntRXComp(void)
{

}
void UART_voidDisableIntRXComp(void)
{

}

//TX complete
void UART_voidEnableIntTXComp(void){

}

void UART_voidDisableIntTXComp(void)
{

}

void UART_voidEnableIntTXEmpty(void)
{
	//TX Data Reg. empty
}
void UART_voidDisableIntTXEmpty(void)
{

}

