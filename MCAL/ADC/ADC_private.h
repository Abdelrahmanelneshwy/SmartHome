/*********************************************************************/
/*  Description    :  ADC Private file                               */
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/


#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADMUX	*((volatile  uint8*) 0x27)
#define ADCSRA	*((volatile  uint8*) 0x26)
#define ADCH	*((volatile  uint8*) 0x25)
#define ADCL	*((volatile  uint8*) 0x24)
#define SFIOR	*((volatile  uint8*) 0x50)


/*ADMUX Bits Names*/
#define MUX0	0
#define MUX1	1
#define MUX2	2
#define MUX3	3
#define MUX4	4
#define ADLAR	5
#define REFS0	6
#define REFS1	7


/*ADCSRA Bits Names*/
#define ADPS0	0
#define ADPS1	1
#define ADPS2	2
#define ADIE	3
#define ADIF	4
#define ADATE	5
#define ADSC	6
#define ADEN	7



/*SFIOR Bits Names*/
#define PSR10	0
#define PSR2	1
#define PUD		2
#define ACME	3

#define ADTS0	5
#define ADTS1	6
#define ADTS2	7


#define FREE_RUNNING_MODE				0
#define ANALOG_Comparator				1
#define External_Interrupt_Request_0	2
#define Timer_Counter0_Compare_Match	3
#define Timer_Counter0_Overflow			4
#define Timer_Counter_Compare_Match_B	5
#define Timer_Counter1_Overflow			6
#define Timer_Counter1_Capture_Event	7



#define AREF		0
#define AVCC		1
#define AVCC_2		2

#define BITS_10		0
#define BITS_8		1

#define AUTO_TRIGGER		0
#define Single_MODE			1


#define prescaler_2		0
#define prescaler_4		1
#define prescaler_8		2
#define prescaler_16	3
#define prescaler_32	4
#define prescaler_64	5
#define prescaler_128	6

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
