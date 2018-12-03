/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "myfunction.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId RC522TaskHandle;
osThreadId RS485TaskHandle;
osThreadId KeyTaskHandle;
osMessageQId Key_valueHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartRC522Task(void const * argument);
void StartRS485Task(void const * argument);
void StartKeyTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of RC522Task */
  osThreadDef(RC522Task, StartRC522Task, osPriorityBelowNormal, 0, 128);
  RC522TaskHandle = osThreadCreate(osThread(RC522Task), NULL);

  /* definition and creation of RS485Task */
  osThreadDef(RS485Task, StartRS485Task, osPriorityIdle, 0, 64);
  RS485TaskHandle = osThreadCreate(osThread(RS485Task), NULL);

  /* definition and creation of KeyTask */
  osThreadDef(KeyTask, StartKeyTask, osPriorityIdle, 0, 128);
  KeyTaskHandle = osThreadCreate(osThread(KeyTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of Key_value */
/* what about the sizeof here??? cd native code */
  osMessageQDef(Key_value, 5, 3);
  Key_valueHandle = osMessageCreate(osMessageQ(Key_value), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartRC522Task function */
void StartRC522Task(void const * argument)
{

  /* USER CODE BEGIN StartRC522Task */
	
	PcdReset();
	M500PcdConfigISOType ( 'A' );//设置工作方式
	
	
	char cStr [ 30 ];
  unsigned char ucArray_ID [ 4 ];  //先后存放IC卡的类型和UID(IC卡序列号)
	uint8_t ucStatusReturn;          //返回状态
  /* Infinite loop */
  for(;;)
  {
		printf("\r\nStartRC522Task");
		
		/*寻卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )                                   
			 /*若失败再次寻卡*/
		{
      ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		
		}			
		if ( ucStatusReturn == MI_OK  )
		{
      /*防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
				sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X", ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ] );							
				printf ( "%s\r\n",cStr ); 
      }       
		}
    osDelay(1000);
  }
  /* USER CODE END StartRC522Task */
}

/* StartRS485Task function */
void StartRS485Task(void const * argument)
{
  /* USER CODE BEGIN StartRS485Task */
  /* Infinite loop */
  for(;;)
  {
//		printf("\r\nStartRS485Task");
    osDelay(1000);
  }
  /* USER CODE END StartRS485Task */
}

/* StartKeyTask function */
void StartKeyTask(void const * argument)
{
  /* USER CODE BEGIN StartKeyTask */
	uint8_t key[3] = {0};
	uint8_t re_key[3] = {0};
	uint8_t err;
  /* Infinite loop */
  for(;;)
  {
		
//		printf("\r\nStartKeyTask");
		if(scan_key(key) == SUCCESS)
		{
			osDelay(30);
			if(scan_key(re_key) == SUCCESS)
			{
				if( memcmp(key, re_key, 3) == 0 )
				{
					for(int i = 0; i < 3; i++ )
					{
						if(key[i] != NULL)
						{
							if(Key_valueHandle != NULL)
							{
								err = xQueueSend(Key_valueHandle, &key[i], 10);
								if(err == errQUEUE_FULL)
								{
									printf("\r\nerrQUEUE_FULL");
								}
							}
						}
					}
					printf("Get the all key value %02X,%02X,%02X", key[0], key[1], key[2]);
				}
			}
		}
    osDelay(100);
  }
  /* USER CODE END StartKeyTask */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
