#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"GIE.h"
#include"GIE_priv.h"



void GIE_voidEnable(void)
{
	SET_BIT(SREG,INTEURRPT_PIN);
}


void GIE_voidDisable(void)
{
	CLR_BIT(SREG,INTEURRPT_PIN);
}
