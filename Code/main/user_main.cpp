/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include <esp_system.h>
#include <esp_task_wdt.h>
#include <driver/adc.h>
#include <driver/gpio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>

void app_main(void);

#ifdef __cplusplus
}
#endif

#include "Stepper.h"

/******************************************************************************
 * FunctionName : app_main
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
static Stepper stepper;
xTaskHandle xStepperTask;

void app_main(void)
{
    printf("SDK version:%s\n", esp_get_idf_version());

	/* Start the stepper task - defined in this file. */
	if(xTaskCreate(Stepper::task, "blinkenLichten", configMINIMAL_STACK_SIZE + 512, &stepper, tskIDLE_PRIORITY+10, &xStepperTask) == pdPASS) {
		printf("Task 1 was properly created\n\r");
	}
}
