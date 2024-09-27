/*********************************************************************/
/*  Description    :  ADC Program file                               */
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC.h"

pf ADCINT_pfCall= NULL;
uint16 ADC_uint16ReadVal;

/* inilize the mode single or free rrunning , mbit or 10 bit and prescaler and Vref */
void ADC_voidInit(void)
{

#if	Operation_MODE == AUTO_TRIGGER
	{
		SET_BIT(ADCSRA,ADATE);
#if AutoTrigger_MODE == FREE_RUNNING_MODE
		CLR_BIT(SFIOR,ADTS0);
		CLR_BIT(SFIOR,ADTS1);
		CLR_BIT(SFIOR,ADTS2);
#elif	AutoTrigger_MODE == ANALOG_Comparator
		SET_BIT(SFIOR,ADTS0);
		CLR_BIT(SFIOR,ADTS1);
		CLR_BIT(SFIOR,ADTS2);
#elif	AutoTrigger_MODE == External_Interrupt_Request_0
		CLR_BIT(SFIOR,ADTS0);
		SET_BIT(SFIOR,ADTS1);
		CLR_BIT(SFIOR,ADTS2);
#elif	AutoTrigger_MODE == Timer_Counter0_Compare_Match
		SET_BIT(SFIOR,ADTS0);
		SET_BIT(SFIOR,ADTS1);
		CLR_BIT(SFIOR,ADTS2);
#elif	AutoTrigger_MODE == Timer_Counter0_Overflow
		CLR_BIT(SFIOR,ADTS0);
		CLR_BIT(SFIOR,ADTS1);
		SET_BIT(SFIOR,ADTS2);
#elif	AutoTrigger_MODE == Timer_Counter_Compare_Match_B
		SET_BIT(SFIOR,ADTS0);
		CLR_BIT(SFIOR,ADTS1);
		SET_BIT(SFIOR,ADTS2);
#elif	AutoTrigger_MODE == Timer_Counter1_Overflow
		CLR_BIT(SFIOR,ADTS0);
		SET_BIT(SFIOR,ADTS1);
		SET_BIT(SFIOR,ADTS2);
#elif	AutoTrigger_MODE == Timer_Counter1_Capture_Event
		SET_BIT(SFIOR,ADTS0);
		SET_BIT(SFIOR,ADTS1);
		SET_BIT(SFIOR,ADTS2);
#endif
	}
#elif	Operation_MODE == Single_MODE
	CLR_BIT(ADCSRA,ADATE);
#endif


#if	BITS_MODE == BITS_8
	SET_BIT(ADMUX,ADLAR);
#elif	BITS_MODE == BITS_10
	CLR_BIT(ADMUX,ADLAR);
#endif

#if	VOLTAGE_REF == AREF
	CLR_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
#elif	VOLTAGE_REF == AVCC
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
#elif	VOLTAGE_REF == AVCC_2
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
#endif


#if	prescaler == prescaler_2
	CLR_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
#elif	prescaler == prescaler_4
	CLR_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
#elif	prescaler == prescaler_8
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
#elif	prescaler == prescaler_16
	CLR_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#elif	prescaler == prescaler_32
	SET_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#elif	prescaler == prescaler_64
	CLR_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#elif	prescaler == prescaler_128
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#endif

}

void ADC_voidEnable(void)
{
	SET_BIT(ADCSRA,ADEN);
}

void ADC_voidDisable(void)
{
	CLR_BIT(ADCSRA,ADEN);
}

void ADC_voidEnableInterrupt(void)
{
	SET_BIT(ADCSRA,ADIE);
}

void ADC_voidDisableInterrupt(void)
{
	CLR_BIT(ADCSRA,ADIE);
}

void ADC_voidSetCallback(pf pfCallbackCpy)
{
	ADCINT_pfCall = pfCallbackCpy;
}

void ADC_voidStartConversion(uint8 u8ChannelNbCpy)
{
	uint8 ADC_Channel=0x1F;
	ADC_Channel &= u8ChannelNbCpy;
	ADMUX &=0xE0 ;
	ADMUX |=u8ChannelNbCpy;
	SET_BIT(ADCSRA,ADSC);
}

void ADC_voidChangeMode(uint8 u8ModeCpy)
{
	switch(u8ModeCpy)
	{
	case Single_MODE :
		CLR_BIT(ADCSRA,ADATE);
		break;
	case AUTO_TRIGGER :
		SET_BIT(ADCSRA,ADATE);
		break;
	}
}

/* read the vlaue from ADC polling method*/
uint16 ADC_u16ReadSync(uint8 u8ChannelNbCpy)
{
	uint16 loc_ADCW;
	ADC_voidStartConversion(u8ChannelNbCpy);
	while(!GET_BIT(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
#if BITS_MODE == BITS_8
	loc_ADCW = ADCH;
#elif BITS_MODE == BITS_10
	loc_ADCW  = ADCL;
	loc_ADCW |= (ADCH<<8);
#endif
	return loc_ADCW;
}
/* read the vlaue from ADC Interrupt method*/
uint16 ADC_u16ReadAsync(void)
{
	return ADC_uint16ReadVal;
}


void __vector_16(void)   __attribute__ ((signal,used)); // for optimize

void __vector_16(void)
{
	if(ADCINT_pfCall != NULL)
	{
		ADCINT_pfCall();
	}
#if BITS_MODE == BITS_8
	ADC_uint16ReadVal = ADCH;
#elif BITS_MODE == BITS_10
	ADC_uint16ReadVal  = ADCL;
	ADC_uint16ReadVal |= (ADCH<<8);

#endif
}
