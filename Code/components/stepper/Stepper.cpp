/*
 * Stepper.cpp
 *
 *  Created on: May 4, 2019
 *      Author: lasse
 */
#include <stdio.h>
#include <esp_system.h>
#include <FreeRTOS.h>
#include <task.h>
#include "Stepper.h"

/*
 * Phase table for motor 28BYJ-48 (active low)
 * wire/phase  0 1 2 3 4 5 6 7
 * ----------  ---------------
 * Orange      0 0 1 1 1 1 1 0
 * Yellow      1 0 0 0 1 1 1 1
 * Pink        1 1 1 0 0 0 1 1
 * Blue        1 1 1 1 1 0 0 0
 */

typedef enum { orange=1, yellow=2, pink=4, blue=8 } wire_t;

const unsigned char Stepper::phases[8] = {
	orange, 		// 0
	orange|yellow,	// 1
	yellow,			// 2
	yellow|pink,	// 3
	pink,			// 4
	pink|blue,		// 5
	blue,			// 6
	orange|blue,	// 7
};

Stepper::Stepper(gpio_num_t b, gpio_num_t p, gpio_num_t y, gpio_num_t o) :
		orange_pin(o),
		yellow_pin(y),
		pink_pin(p),
		blue_pin(b),
		current_pos(0),
		current_phase(0),
		ticks(3 / portTICK_PERIOD_MS),
		direction(fwd),
		last_wake_time(0),
		task_handle(0)
{

}

Stepper::~Stepper() {
	// TODO Auto-generated destructor stub
}

void Stepper::init()
{
	gpio_config_t gpio_cfg = {
		BIT(orange_pin) | BIT(yellow_pin) | BIT(pink_pin) | BIT(blue_pin) | BIT(GPIO_NUM_4) | BIT(GPIO_NUM_5),
		GPIO_MODE_OUTPUT,
		GPIO_PULLUP_DISABLE,
		GPIO_PULLDOWN_DISABLE,
		GPIO_INTR_DISABLE,
	};
    ESP_ERROR_CHECK(gpio_config(&gpio_cfg));

    printf("Setting wake times...\n");
	last_wake_time = xTaskGetTickCount();
	printf("Stepper created at address %p, tick=%ld\n", this, ticks);

	/* Start the stepper task - defined in this file. */
	if(xTaskCreate(Stepper::task, "stepper", configMINIMAL_STACK_SIZE + 512, this, tskIDLE_PRIORITY+10, &task_handle) == pdPASS) {
		printf("Task 1 was properly created\n\r");
	}
}

void Stepper::step()
{
    printf("Phase1: %d\n", current_phase);
	current_phase += direction;
    printf("Phase2: %d\n", current_phase);
    if (current_phase >= (int)(sizeof phases / sizeof phases[0])) {
		current_phase = 0;
	}
    else if (current_phase < 0) {
		current_phase = (int)(sizeof phases / sizeof phases[0]) - 1;
	    printf("Clamping negative phase\n");
	}

	// Set motor windings (via inverting transistor).
	gpio_set_level(orange_pin, (phases[current_phase] & orange) ? 1 : 0);
	gpio_set_level(yellow_pin, (phases[current_phase] & yellow) ? 1 : 0);
	gpio_set_level(pink_pin,   (phases[current_phase] & pink) ? 1 : 0);
	gpio_set_level(blue_pin,   (phases[current_phase] & blue) ? 1 : 0);

	current_pos += direction;
}

void Stepper::task(void *p)
{
	Stepper *s = (Stepper *)p;
	s->run();
}

void Stepper::set_period(float seconds)
{
	ticks = (int)(seconds * 1000 / portTICK_PERIOD_MS);
	if (ticks == 0) ticks = 1;
//	if (task_handle != 0) {
//		xTaskAbortDelay(task_handle);
//	}
}

void Stepper::run()
{
	printf("Stepper::run@%p called, ticks=%ld\n", this, ticks);
	while(1)
	{
		vTaskDelayUntil(&last_wake_time, ticks);
		step();
		if (current_pos >= 4096 || current_pos < 0) {
			direction = -direction;
		    printf("New direction: %d\n", direction);
		}
	}
}
