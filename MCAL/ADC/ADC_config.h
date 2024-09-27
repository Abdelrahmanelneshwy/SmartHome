/*********************************************************************/
/*  Description    :  ADC configuration file                         */
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/
#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/* inilize the mode single or free running , mbit or 10 bit and prescaler and Vref */
#define VOLTAGE_REF 		AREF
#define Operation_MODE		Single_MODE
#define AutoTrigger_MODE	FREE_RUNNING_MODE
#define prescaler			prescaler_16
#define	BITS_MODE			BITS_10

#endif /* MCAL_ADC_ADC_CONFIG_H_ */
