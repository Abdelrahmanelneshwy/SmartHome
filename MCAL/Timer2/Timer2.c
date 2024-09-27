/*
 * Timer2.c
 *
 *  Created on: Aug 16, 2223
 *      Author: Abdelrahman
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "Timer2.h"
#include "Timer2_private.h"
#include "Timer2_config.h"


pf TIM2_pfOVFCallBack;
pf TIM2_pfCmpCallBack;

void TIM2_voidinit(void)
{
	/*selct timer mode*/
#if TIM2_MODE == TIM2_NORMAL
	CLR_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);

#elif TIM2_MODE == TIM2_CTC
	CLR_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);

#elif TIM2_MODE == TIM2_FAST_PWM
	SET_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);
#elif TIM2_MODE == TIM2_PHASE_CORRECT_PWM
	SET_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);

#else
	/*set normal as default*/
	CLR_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);

#endif

	/*selct wave form on oco pin */
#if	TIM2_WAVE == TIM2_TOGL_OC2
	SET_BIT(TCCR2,4);
	CLR_BIT(TCCR2,5);

#elif TIM2_WAVE == TIM2_SET_OC2
	SET_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);

#elif TIM2_WAVE == TIM2_CLR_OC2
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);

#elif TIM2_WAVE == TIM2_FAST_INVERT_OC2
	SET_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
#elif TIM2_WAVE == TIM2_FAST_NONINVERT_OC2
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);

#elif TIM2_WAVE == TIM2_PHASE_NONINVERT_OC2
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);

#elif TIM2_WAVE == TIM2_PHASE_INVERT_OC2
	SET_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);

#else
	CLR_BIT(TCCR2,4);
	CLR_BIT(TCCR2,5);
#endif

}
void TIM2_ExtClkEnable()
{
	SET_BIT(ASSR,3);
}
void TIM2_ExtClkDisable()
{
	CLR_BIT(ASSR,3);
}


void TIM2_voidEnable(uint8 u8PreScaler)
{

	TCCR2&=0b11111000;
	//& 0b00000111 --> to prevent the user  to entermore than 111 in bits 0,1,2

	TCCR2|= (u8PreScaler & 0b00000111);

}
void TIM2_voidDisable(void)
{
	TCCR2&=0b11111000;
}
void TIM2_voidEnableOvfINt(void)
{
	SET_BIT(TIMSK,6);
}
void TIM2_voidDisableOvfINt(void)
{
	CLR_BIT(TIMSK,6);

}
void TIM2_voidEnableComparINt(void)
{
	SET_BIT(TIMSK,7);

}
void TIM2_voidDisableCompareINt(void)
{
	CLR_BIT(TIMSK,7);
}

void TIM2_voidSetCallBackOvfInt(pf pfOvfcallBack)
{
	TIM2_pfOVFCallBack=pfOvfcallBack;
}
void TIM2_voidSetCallBackCompareInt(pf pfComcallBack)
{
	TIM2_pfCmpCallBack=pfComcallBack;
}

void TIM2_voidSetTCNTValue(uint8 u8TcntReg)
{
	TCNT2 = u8TcntReg;
}
void TIM2_voidSetOCRValue(uint8 u8OcrReg)
{
	OCR2 = u8OcrReg;
}
uint8 TIM2_u8ReadTcntReg(void)
{
	return TCNT2 ;
}

void TIM2_voidChangMode(uint8 u8Mode)
{}

/* ISR OVF*/


void __vector_5  (void)  __attribute__ ((signal,used));

void __vector_5  (void)
{
	TIM2_pfOVFCallBack();
}

/* COM ISR */
void __vector_4  (void)  __attribute__ ((signal,used));

void __vector_4  (void)
{
	TIM2_pfCmpCallBack();
}


