/*
 * App_Init.h
 * light inteisty
 *  Created on: Aug 9, 2023
 *      Author: Dr Tarek
 */

#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_



/************************************Macros********************************/
#define USER_NAME_BASE_ADDRESS      0x00
#define USER_PASS_BASE_ADDRESS      0xF0

#define DOOR_PIN					DIO_PORT_A_NUM_A2
#define BUZZER_PIN					DIO_PORT_A_NUM_A3




/**********************************************Tasks Prototypes*************************************************************************/
int AppStart(void);
void vLM35(void *pvParameters);
void vFAN(void *pvParameters);
void vLogin(void *pvParameters);
/***************************************************************************************************************************************/



#endif /* APPLICATION_APP_H_ */
