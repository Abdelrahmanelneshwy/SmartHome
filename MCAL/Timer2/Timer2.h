/*
 * Timer.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Abdelrahman
 */

#ifndef MCAL_TIMER2_TIMER2_H_
#define MCAL_TIMER2_TIMER2_H_

#define TIM2_PRESCALER_1 						1
#define TIM2_PRESCALER_8 						2
#define TIM2_PRESCALER_32 						3
#define TIM2_PRESCALER_64						4
#define TIM2_PRESCALER_128						5
#define TIM2_PRESCALER_256						6
#define TIM2_PRESCALER_1024					  	7


void TIM2_voidinit(void);
void TIM2_voidEnable(uint8 u8PrescalerCpy);
void TIM2_voidDisable(void);

void TIM2_ExtClkEnable();
void TIM2_ExtClkDisable();

void TIM2_voidEnableOvFInt(void);
void TIM2_voidDisableableOvFInt(void);
void TIM2_voidSetCallBackOVFInt(pf pfOVFCallBack);

void TIM2_voidEnableCompareInt(void);
void TIM2_voidDisableableCompareInt(void);
void TIM2_voidSetCallBackCompareInt(pf pfCampareCallBack);

void TIM2_voidSetTCNTValue(uint8 u8TCNTReg);
void TIM2_voidSetOCRValue(uint8 u8OCRReg);

uint8 TIM2_u8ReadTCNTReg(void);
void TIM2_ChangeMode(uint8 u8ModeCpy);




#endif /* MCAL_TIMER0_TIMER0_H_ */
