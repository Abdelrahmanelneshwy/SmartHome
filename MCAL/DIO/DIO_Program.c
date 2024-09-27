/*
 * DIO_Program.c
 *
 *  Created on: Aug 17, 2024
 *      Author: DELL
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "DIO_configuration.h"
#include "DIO_Register.h"
#include "DIO_interface.h"


void DIO_Init(void)
{
	DDRA = CONC(DIO_PIN_NUM_A7_DIR ,DIO_PIN_NUM_A6_DIR ,DIO_PIN_NUM_A5_DIR ,DIO_PIN_NUM_A4_DIR ,DIO_PIN_NUM_A3_DIR ,DIO_PIN_NUM_A2_DIR,DIO_PIN_NUM_A1_DIR ,DIO_PIN_NUM_A0_DIR  );
	DDRB = CONC(DIO_PIN_NUM_B7_DIR ,DIO_PIN_NUM_B6_DIR ,DIO_PIN_NUM_B5_DIR ,DIO_PIN_NUM_B4_DIR ,DIO_PIN_NUM_B3_DIR ,DIO_PIN_NUM_B2_DIR,DIO_PIN_NUM_B1_DIR ,DIO_PIN_NUM_B0_DIR  );
	DDRC = CONC(DIO_PIN_NUM_C7_DIR ,DIO_PIN_NUM_C6_DIR ,DIO_PIN_NUM_C5_DIR ,DIO_PIN_NUM_C4_DIR ,DIO_PIN_NUM_C3_DIR ,DIO_PIN_NUM_C2_DIR,DIO_PIN_NUM_C1_DIR ,DIO_PIN_NUM_C0_DIR  );
	DDRD = CONC(DIO_PIN_NUM_D7_DIR ,DIO_PIN_NUM_D6_DIR ,DIO_PIN_NUM_D5_DIR ,DIO_PIN_NUM_D4_DIR ,DIO_PIN_NUM_D3_DIR ,DIO_PIN_NUM_D2_DIR,DIO_PIN_NUM_D1_DIR ,DIO_PIN_NUM_D0_DIR  );
}

//write pins value

tenuErrorStatus DIO_enuTogglePin(uint8 u8PinNumCpy ){
	tenuErrorStatus retunState=EOK;
	if(u8PinNumCpy >= 0  && u8PinNumCpy <= 7)
			{
				Toggle_BIT(PORTA, u8PinNumCpy);
			}
			else if( u8PinNumCpy >= 8  && u8PinNumCpy <= 15 )
			{
				Toggle_BIT(PORTB, (u8PinNumCpy%8));
			}
			else if( u8PinNumCpy >= 16  && u8PinNumCpy <= 23 )
			{
				Toggle_BIT(PORTC, (u8PinNumCpy%8));
			}
			else if( u8PinNumCpy >= 24  && u8PinNumCpy <= 31 )
			{
				Toggle_BIT(PORTD, (u8PinNumCpy%8));
			}
			else
			{
				retunState = PARAMRETER_OUT_RANGE;
			}
	return retunState;
}
tenuErrorStatus DIO_enuWritePin(uint8 u8PinNumCpy , uint8 u8PinValueCpy)
{
	tenuErrorStatus retunState=EOK;
	switch(u8PinValueCpy)
	{
	case DIO_LOW:
		if(u8PinNumCpy >= 0  && u8PinNumCpy <= 7)
		{
			CLR_BIT(PORTA, u8PinNumCpy);
		}
		else if( u8PinNumCpy >= 8  && u8PinNumCpy <= 15 )
		{
			CLR_BIT(PORTB, (u8PinNumCpy%8));
		}
		else if( u8PinNumCpy >= 16  && u8PinNumCpy <= 23 )
		{
			CLR_BIT(PORTC, (u8PinNumCpy%8));
		}
		else if( u8PinNumCpy >= 24  && u8PinNumCpy <= 31 )
		{
			CLR_BIT(PORTD, (u8PinNumCpy%8));
		}
		else
		{
			retunState = PARAMRETER_OUT_RANGE;
		}
		break;

	case DIO_HIGH:
		if(u8PinNumCpy >= 0  && u8PinNumCpy <= 7)
		{
			SET_BIT(PORTA, u8PinNumCpy);
		}
		else if( u8PinNumCpy >= 8  && u8PinNumCpy <= 15 )
		{
			SET_BIT(PORTB, (u8PinNumCpy%8));
		}
		else if( u8PinNumCpy >= 16  && u8PinNumCpy <= 23 )
		{
			SET_BIT(PORTC, (u8PinNumCpy%8));
		}
		else if( u8PinNumCpy >= 24  && u8PinNumCpy <= 31 )
		{
			SET_BIT(PORTD, (u8PinNumCpy%8));
		}
		else
		{
			retunState = PARAMRETER_OUT_RANGE;
		}
		break;
	default:
		//do nothing
		break;
	}
	return retunState;
}

tenuErrorStatus DIO_enuReadPin(uint8 u8PinNumCpy , uint8* pu8PinValue)
{
	tenuErrorStatus retunState=EOK;
	if(u8PinNumCpy >= 0  && u8PinNumCpy <= 7)
	{
		*pu8PinValue = GET_BIT(PINA,u8PinNumCpy);
	}
	else if( u8PinNumCpy >= 8  && u8PinNumCpy <= 15 )
	{
		*pu8PinValue = GET_BIT(PINB,(u8PinNumCpy%8));
	}
	else if( u8PinNumCpy >= 16  && u8PinNumCpy <= 23 )
	{
		*pu8PinValue = GET_BIT(PINC,(u8PinNumCpy%8));
	}
	else if( u8PinNumCpy >= 24  && u8PinNumCpy <= 31 )
	{
		*pu8PinValue = GET_BIT(PIND,(u8PinNumCpy%8));
	}
	else
	{
		retunState = PARAMRETER_OUT_RANGE;
	}
	return retunState;
}


/*to activate pull up resistor you need to make input direction and make PORT register high */
tenuErrorStatus DIO_enuStatePullup(uint8 u8PinNumCpy , uint8 u8StateCpy)
{
	tenuErrorStatus retunState=EOK;
		switch(u8StateCpy)
		{
		case DIO_DEACTIVATE_PULLUP:
			if(u8PinNumCpy >= 0  && u8PinNumCpy <= 7)
			{
				CLR_BIT(PORTA, u8PinNumCpy);
			}
			else if( u8PinNumCpy >= 8  && u8PinNumCpy <= 15 )
			{
				CLR_BIT(PORTB, (u8PinNumCpy%8));
			}
			else if( u8PinNumCpy >= 16  && u8PinNumCpy <= 23 )
			{
				CLR_BIT(PORTC, (u8PinNumCpy%8));
			}
			else if( u8PinNumCpy >= 24  && u8PinNumCpy <= 31 )
			{
				CLR_BIT(PORTD, (u8PinNumCpy%8));
			}
			else
			{
				retunState = PARAMRETER_OUT_RANGE;
			}
			break;

		case DIO_ACTIVATE_PULLUP:
			if(u8PinNumCpy >= 0  && u8PinNumCpy <= 7)
			{
				SET_BIT(PORTA, u8PinNumCpy);
			}
			else if( u8PinNumCpy >= 8  && u8PinNumCpy <= 15 )
			{
				SET_BIT(PORTB, (u8PinNumCpy%8));
			}
			else if( u8PinNumCpy >= 16  && u8PinNumCpy <= 23 )
			{
				SET_BIT(PORTC, (u8PinNumCpy%8));
			}
			else if( u8PinNumCpy >= 24  && u8PinNumCpy <= 31 )
			{
				SET_BIT(PORTD, (u8PinNumCpy%8));
			}
			else
			{
				retunState = PARAMRETER_OUT_RANGE;
			}
			break;
		default:
			//do nothing
			break;
		}
		return retunState;
}

tenuErrorStatus DIO_enuWriteGroup(uint8* pau8PinNumCpy , uint8* pau8PinValueCpy,uint8 u8Sizecpy)
{
	tenuErrorStatus returnState = EOK;
	for(uint8 i =0; i < u8Sizecpy ; i++)
	{
		returnState = DIO_enuWritePin(pau8PinNumCpy[i],pau8PinValueCpy[i]);
	}
	return returnState;
}

tenuErrorStatus DIO_enuWritePort(uint8 u8PortCpy , uint8 u8PortValueCpy)
{
	tenuErrorStatus retunState=EOK;
		switch(u8PortCpy)
		{
		case GPIOA:
			PORTA = u8PortValueCpy;
			break;

		case GPIOB:
			PORTB = u8PortValueCpy;
			break;
		case GPIOC:
			PORTC = u8PortValueCpy;
			break;

		case GPIOD:
			PORTD = u8PortValueCpy;
			break;
		default:
			retunState = PARAMRETER_OUT_RANGE;
			break;
		}
		return retunState;
}

