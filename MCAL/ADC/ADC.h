/*********************************************************************/
/*  Description    :  ADC interface file                             */
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/
#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#define ADC0	0
#define ADC1	1
#define ADC2	2
#define ADC3	3
#define ADC4	4
#define ADC5	5
#define ADC6	6
#define ADC7	7



/* inilize the mode single or free rrunning , mbit or 10 bit and prescaler and Vref */
void ADC_voidInit(void);

void ADC_voidEnable(void);

void ADC_voidDisable(void);

void ADC_voidEnableInterrupt(void);

void ADC_voidDisableInterrupt(void);

void ADC_voidSetCallback(pf pfCallbackCpy);

void ADC_voidStartConversion(uint8 u8ChannelNbCpy);

void ADC_voidChangeMode(uint8 u8ModeCpy);

 /* read the vlaue from ADC polling method*/
uint16 ADC_u16ReadSync(uint8 u8ChannelNbCpy);
/* read the vlaue from ADC Interrupt method*/
uint16 ADC_u16ReadAsync(void);


#endif /* MCAL_ADC_ADC_H_ */
