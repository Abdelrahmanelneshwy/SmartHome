/**************************************Including using Libraries****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "../LIB/STD_TYPES.h"

/* MCAL library */
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/UART/USART_interface.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/Timer2/Timer2.h"
#include "../MCAL/I2C/I2C.h"
/*
 * HAL Library
 */
#include "../HAL/EEPROM/EEPROM.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/LM35/LM35.h"

/* FreeRTOS Library */
#include "../freeRtos/FreeRTOS.h"
#include "../freeRtos/FreeRTOSConfig.h"
#include "../freeRtos/task.h"
#include "../freeRtos/queue.h"
#include "../freeRtos/semphr.h"

#include "App.h"
/**************************************End of including using Libraries****************************************************/


/******************************************Creating Task handle*************************************************/
TaskHandle_t vtask_Fan=NULL;
TaskHandle_t vtask_LM35=NULL;
TaskHandle_t vtask_Login=NULL;
/***************************************************************************************************************/


/******************************************Creating Queue*************************************************/
QueueHandle_t Queue_LM35;
/*********************************************************************************************************/


/******************************************Creating Semaphor*************************************************/
SemaphoreHandle_t LCD_Semaphore = NULL;
/************************************************************************************************************/

/******************************************Creating Global varibles*************************************************/
uint8* USER_NAME = "Neshwy"; // global variable to store user name of system and is set by default
uint8* USER_PASS = "123456"; // global variable to store user password of system and is set by default
// array of strings have welcome message
uint8 String[4][22]={"*******************","*login press 1    *","*new user press 2 *","*******************",};
/**********************************************************************************************************************/

int AppStart(void)
{
	/**************************************start of system initializations**************************************************/
    DIO_Init();
    UART_voidInit();
    LCD_voidInit();
    LM35_vidinit();
    TIM2_voidinit();
    TIM2_voidEnable(TIM2_PRESCALER_1);
    I2C_voidInit();
    /**************************************End of system initializations**************************************************/


    /**************************************start of Queue Creation**************************************************/
    Queue_LM35 = xQueueCreate(1, sizeof(uint32));
    /**************************************End of Queue Creation**************************************************/


    /**************************************start of Semaphor Creation**************************************************/
    LCD_Semaphore = xSemaphoreCreateBinary();
    /**************************************end of Semaphor Creation**************************************************/



    /**************************************start of Task Creation**************************************************/
    xTaskCreate(vLogin , "login" , 200 , NULL , 1 , &vtask_Login);
    xTaskCreate(vLM35  , "LM35"  , 150 , NULL , 2 , &vtask_LM35 );
    xTaskCreate(vFAN   , "FAN"   , 150 , NULL , 3 , &vtask_Fan  );
    /**************************************end of Task Creation**************************************************/


    /********************************************Suspended Tasks *******************************************************************/
    vTaskSuspend(vtask_Fan);
    vTaskSuspend(vtask_LM35);

    /* Start the scheduler*/
    vTaskStartScheduler();

    // Infinite loop (should never reach here)
    while (1);
}


void vLogin(void *pvParameters)
{
	/*Definitions of Local variable of Login task*/
	uint8 user_name[16],user_pass[16];
	uint8 entry_data;
	uint8 option,Key=3;
	while(1)
	{
		xSemaphoreTake(LCD_Semaphore,(TickType_t)30);

		/*****************************************start of sending interface message****************************************************/
		for(uint8 row_itr=0;row_itr < 4; row_itr ++)
		{
			for(uint8 col_itr=0;col_itr < 20; col_itr ++)
			{
				UART_voidSend(String[row_itr][col_itr]);
			}
			UART_voidSend('\r');
		}
		/*****************************************end of sending interface message****************************************************/


		/***********************************start loading user name *****************************************************************/
		for(uint8 u8Counter=0;u8Counter<16 ; u8Counter++ )
		{
			EEPROM_enuReadByte(0,(USER_NAME_BASE_ADDRESS|u8Counter) ,&USER_NAME[u8Counter]);
			if(USER_NAME[u8Counter] == '\0')
			{

				break;
			}
		}
		/***********************************end loading user name ********************************************************************/


		/***********************************start loading user password **************************************************************/
		for(uint8 u8Counter=0;u8Counter<16 ; u8Counter++ )
		{
			EEPROM_enuReadByte(0,(USER_PASS_BASE_ADDRESS|u8Counter) ,&USER_PASS[u8Counter]);
			if(USER_PASS[u8Counter] == '\0')
			{
				USER_PASS[u8Counter] = '\0';
				break;
			}
		}
		/***********************************end loading user password ****************************************************************/


		/*take user choice*/
		UART_enuRecieve(&option);
		switch(option)
		{
			case '1':
				/***********************************start receiving  user name *****************************************/
				UART_voidSend('\r');
				LCD_voidGotoxy(0,0);
				LCD_voidSendString("user name ");
				for(uint8 u8Counter=0;u8Counter<16 ; u8Counter++ )
				{
					UART_enuRecieve(&user_name[u8Counter]);
					if(user_name[u8Counter] == '\r')
					{
						user_name[u8Counter] = '\0';
						break;
					}
					LCD_voidGotoxy(u8Counter,1);
					LCD_voidSendData(user_name[u8Counter]);
				}
				/***********************************end receiving  user name *****************************************/


				/***********************************start receiving  user password *****************************************/
				LCD_voidSendCommand(0x01);
				LCD_voidGotoxy(0,0);
				LCD_voidSendString("password");
				for(uint8 u8Counter=0;u8Counter<16 ; u8Counter++ )
				{
					UART_enuRecieve(&user_pass[u8Counter]);
					if(user_pass[u8Counter] == '\r')
					{
						user_pass[u8Counter] = '\0';
						break;
					}
					LCD_voidGotoxy(u8Counter,1);
					LCD_voidSendData(user_pass[u8Counter]);
					_delay_ms(100);
					LCD_voidGotoxy(u8Counter,1);
					LCD_voidSendData('*');
				}
				/***********************************end receiving  user password *****************************************/

				/*checking user name and password*/
				if((strcmp(user_name,USER_NAME)==0) && (strcmp(user_pass,USER_PASS)==0))
				{
					/*Incase correct user name and password return Key value to default */
					Key=3;

					/*Open the Door lock*/
					DIO_enuWritePin(DOOR_PIN,DIO_HIGH);


					/*welcome the user*/
					LCD_voidSendCommand(0x01);
					LCD_voidGotoxy(0,0);
					LCD_voidSendString("Welcome ");
					LCD_voidSendString(USER_NAME);


					/*after one second close Door again*/
					_delay_ms(1000);
					DIO_enuWritePin(DOOR_PIN,DIO_LOW);
					LCD_voidSendCommand(0x01);

					/*release LCD semaphor*/
					xSemaphoreGive(LCD_Semaphore);

					/*resume all tasks except login task*/
					vTaskResume(vtask_Fan);
					vTaskResume(vtask_LM35);
					vTaskSuspend(vtask_Login);

				}
				else
				{
					/*Incase Wrong Passorwd or user name decrement Key's value*/
					Key--;
					LCD_voidSendCommand(0x01);
					LCD_voidGotoxy(0,0);
					LCD_voidSendString("invalid user");

					/*after one second clear screen*/
					_delay_ms(1000);
					LCD_voidSendCommand(0x01);

					/*in thrid trial Locked the system*/
					if(Key == 0)
					{
						/*after one second clear screen*/
						LCD_voidSendCommand(0x01);

						/*Set alarm*/
						DIO_enuWritePin(BUZZER_PIN,DIO_HIGH);

						/*inform user that system is locked*/
						LCD_voidGotoxy(0,0);
						LCD_voidSendString("System Locked");
						while(1);
					}
				}
				break;
			case '2':
				/***********************************start storing user name *****************************************/
				UART_voidSend('\r');
				/*ask about user name*/
				LCD_voidGotoxy(0,0);
				LCD_voidSendString("user name ?");

				for(uint8 u8Counter=0;u8Counter<16 ; u8Counter++ )
				{
					/*receiving name byte by byte*/
					UART_enuRecieve(&entry_data);

					/*stop at Enter*/
					if(entry_data == '\r')
					{
						/*store end of name at EEPROM*/
						entry_data= '\0';
						EEPROM_enuWriteByte(0,(USER_NAME_BASE_ADDRESS|u8Counter) ,entry_data);
						break;
					}
					/*store data at EEPROM*/
					EEPROM_enuWriteByte(0,(USER_NAME_BASE_ADDRESS|u8Counter) ,entry_data);
					/*show character at LCD screen*/
					LCD_voidGotoxy(u8Counter,1);
					LCD_voidSendData(entry_data);
				}
				/***********************************end storing user name *****************************************/

				/***********************************start storing user password *****************************************/
				LCD_voidSendCommand(0x01);

				/*ask about user password*/
				LCD_voidGotoxy(0,0);
				LCD_voidSendString("user password ?");

				/*receiving password byte by byte*/
				for(uint8 u8Counter=0;u8Counter<16 ; u8Counter++ )
				{
					UART_enuRecieve(&entry_data);
					if(entry_data == '\r')
					{
						/*store end of password at EEPROM*/
						entry_data= '\0';
						EEPROM_enuWriteByte(0,(USER_PASS_BASE_ADDRESS|u8Counter) ,entry_data);
						break;
					}
					/*store data at EEPROM*/
					EEPROM_enuWriteByte(0,(USER_PASS_BASE_ADDRESS|u8Counter) ,entry_data);
					/*show character at LCD screen*/
					LCD_voidGotoxy(u8Counter,1);
					LCD_voidSendData(entry_data);
					_delay_ms(100);
					LCD_voidGotoxy(u8Counter,1);
					LCD_voidSendData('*');
				}
				LCD_voidSendCommand(0x01);
				/***********************************end storing user password *****************************************/
				break;
		}
		/*release LCD semaphor*/
		xSemaphoreGive(LCD_Semaphore);

		/*get task in waiting state*/
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

/* Task to Reading of LM35*/
void vLM35(void *pvParameters)
{
  //  uint8 Message[20];  // Allocate fixed buffer for message
    uint32 temp=0;
    while (1)
    {
    	/*Taking LM35 sensor readings*/
        temp = LM35_f32Reading(ADC0);

        /*Send Temperature degree to Fan Task using Queue*/
        xQueueSend(Queue_LM35, ( void *)&temp,portMAX_DELAY);

        // Delay to prevent constant task execution
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


/* Task to handle displaying of Temperature*/
void vFAN(void *pvParameters)
{
    uint32 temp_value=0;
    while (1)
    {
    	/* take LCD semaphor to start using it*/
    	xSemaphoreTake(LCD_Semaphore,(TickType_t)10);

    	/*Receive Temperature degree from LM35 Task using Queue*/
    	xQueueReceive(Queue_LM35,( void *)&temp_value,portMAX_DELAY);

    	/*Show Temperature Degree on Screen*/
		LCD_voidGotoxy(0,0);
		LCD_voidSendString("Temperature:");
		LCD_voidSendNumber(temp_value);

		/*Controling Fan Speed according to Temperature Degree*/
		if(temp_value <= 30)TIM2_voidSetOCRValue(0);
		else if(temp_value <= 50)TIM2_voidSetOCRValue(80);
		else if(temp_value <= 70)TIM2_voidSetOCRValue(155);
		else TIM2_voidSetOCRValue(255);

		/*release LCD semaphor*/
		xSemaphoreGive(LCD_Semaphore);
		// Delay to prevent constant task execution
		vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

