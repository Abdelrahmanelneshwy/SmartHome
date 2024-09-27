/*********************************************************************/
/*  Description    :  DIO program file                               */
/*  Author         :  Abdelrahman Tarek                              */
/*  Version        :  0.1 V                                          */
/*  Date           :  2 Aug 2023                                     */
/*  History        :  initial creation                               */
/*********************************************************************/

#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_


typedef unsigned char        	  uint8;
typedef unsigned short int   	 uint16;
typedef unsigned long int    	 uint32;
typedef unsigned long long int   uint64;

typedef signed char               sint8;
typedef signed short int         sint16;
typedef signed long int          sint32;
typedef signed long long int  	 sint64;

typedef float				  	    f32;
typedef double 				   	    f64;
typedef long double					f128;

#define  NULL  (void*) 0
typedef void (*pf)(void);

typedef enum
{
	EOK=0,
	ENOK,
	PARAMRETER_OUT_RANGE,
	PARAMERTE_NULL_PTR

}tenuErrorStatus;

#endif /* LIB_STD_TYPES_H_ */
