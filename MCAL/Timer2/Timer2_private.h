/*
 * Timer0_private.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Abdelrahman
 */


#ifndef MCAL_TIMER2_TIMER2_PRIVATE_H_
#define MCAL_TIMER2_TIMER2_PRIVATE_H_


#define TIM2_NORMAL					0
#define TIM2_CTC					1
#define TIM2_FAST_PWM				2
#define TIM2_PHASE_CORRECT_PWM		3


/*Non_PWM mode*/
#define TIM2_TOGGLE_OC2				0
#define TIM2_SET_OC2				1
#define TIM2_CLR_OC2				2


/*Fast PWM mode*/
#define TIM2_FAST_INVERT_OC2		3
#define TIM2_FAST_NONINVERT_OC2		4


/*Phase correct PWM mode*/
#define TIM2_PHASE_INVERT_OC2		5
#define TIM2_PHASE_NONINVERT_OC2	6


#define TIM2_DISCONNECTED_OC2		7




#define TCCR2		*((volatile uint8 * ) 0x45)
#define TCNT2		*((volatile uint8 * ) 0x44)
#define OCR2		*((volatile uint8 * ) 0x43)
#define ASSR  		*((volatile uint8 * ) 0x42)
#define SFIOR		*((volatile uint8 * ) 0x50)
#define TIMSK		*((volatile uint8 * ) 0x59)
#define TIFR		*((volatile uint8 * ) 0x58)


#endif /* MCAL_TIMER2_TIMER2_PRIVATE_H_ */
