/*
 * Stepper.cpp
 *
 *  Created on: May 4, 2019
 *      Author: lasse
 */
#include <stdio.h>
#include <esp_system.h>
#include <driver/hw_timer.h>
#include "Stepper.h"
//static const char *TAG = "Stepper";
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
		step_callback(cb),
		prescaler(1)
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

	ESP_ERROR_CHECK(hw_timer_init(&timer_callback, this));
	printf("Timer clkdiv %d\n", hw_timer_get_clkdiv());
}

void Stepper::step()
{
	static unsigned short clk = 0;
	if (++clk < prescaler) {
		return;
	}
	clk = 0;

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

float Stepper::set_period(float seconds)
{
	prescaler = (seconds > 1) ? 1000 : 1;

	ESP_ERROR_CHECK(hw_timer_disarm());
	if (seconds <= 0.001) {
		seconds = 0.001;
	}
	uint32_t us = seconds *(1000000/prescaler);
	printf("Setting timer to %d\n", us);
	ESP_ERROR_CHECK(hw_timer_alarm_us(us, true));
	ESP_ERROR_CHECK(hw_timer_enable(true));
	return seconds;
}
