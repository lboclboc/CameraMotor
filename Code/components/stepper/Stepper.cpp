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
static const char *TAG = "Stepper";
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

Stepper::Stepper(gpio_num_t b, gpio_num_t p, gpio_num_t y, gpio_num_t o, float s, step_callback_t cb) :
		orange_pin(o),
		yellow_pin(y),
		pink_pin(p),
		blue_pin(b),
		current_pos(0),
		current_phase(0),
		ticks(0),
		direction(fwd),
		last_wake_time(0),
		timer_handle(0),
		step_callback(cb)
{
//	set_period(s);
}

Stepper::~Stepper() {

}

void Stepper::init()
{
	gpio_config_t gpio_cfg = {
		BIT(orange_pin) | BIT(yellow_pin) | BIT(pink_pin) | BIT(blue_pin),
		GPIO_MODE_OUTPUT,
		GPIO_PULLUP_DISABLE,
		GPIO_PULLDOWN_DISABLE,
		GPIO_INTR_DISABLE,
	};
    ESP_ERROR_CHECK(gpio_config(&gpio_cfg));

	printf("Stepper created at address %p, tick=%ld\n", this, ticks);

	esp_timer_create_args_t args = {&timer_callback, this, ESP_TIMER_TASK, "stepper"};
	ESP_ERROR_CHECK(esp_timer_create(&args, &timer_handle));
	set_period(1);
}

void Stepper::step()
{
	current_phase += direction;
    if (current_phase >= (int)(sizeof phases / sizeof phases[0])) {
		current_phase = 0;
	}
    else if (current_phase < 0) {
		current_phase = (int)(sizeof phases / sizeof phases[0]) - 1;
	}

	// Set motor windings (via inverting transistor).
	gpio_set_level(orange_pin, (phases[current_phase] & orange) ? 1 : 0);
	gpio_set_level(yellow_pin, (phases[current_phase] & yellow) ? 1 : 0);
	gpio_set_level(pink_pin,   (phases[current_phase] & pink) ? 1 : 0);
	gpio_set_level(blue_pin,   (phases[current_phase] & blue) ? 1 : 0);

	current_pos += direction;
	if (step_callback) {
		(*step_callback)();
	}
}

void Stepper::timer_callback(void *p)
{
	Stepper *s = (Stepper *)p;
	s->step();
}

void Stepper::set_period(float seconds)
{
	if (timer_handle == 0) {
		return;
	}

	ESP_ERROR_CHECK(esp_timer_stop(timer_handle));
	ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handle, (uint64_t)(seconds * 1000000.0)));
}
