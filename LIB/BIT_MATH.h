/*********************************************************************/
/*  Description    :  DIO program file                               */
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/
#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(REG,BIT)	(REG|=(1<<BIT))
#define CLR_BIT(REG,BIT)	(REG&=~(1<<BIT))
#define GET_BIT(REG,BIT)	((REG>>BIT)&1)
#define Toggle_BIT(REG,BIT)	(REG^=(1<<BIT))

#endif /* LIB_BIT_MATH_H_ */
