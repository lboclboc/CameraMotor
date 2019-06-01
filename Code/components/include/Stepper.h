/*
 * Stepper.h
 *
 *  Created on: May 4, 2019
 *      Author: lasse
 */

#ifndef STEPPER_H_
#define STEPPER_H_
#include <driver/gpio.h>
#include <timers.h>
#include "Led.h"

class Stepper
{
public:
	Stepper(gpio_num_t b=GPIO_NUM_12, gpio_num_t p=GPIO_NUM_13, gpio_num_t y=GPIO_NUM_14, gpio_num_t o=GPIO_NUM_15);
	virtual ~Stepper();
	static void task(void *);
	void step();
	void set_period(float seconds);
	void init();

protected:
	void run();

private:
	gpio_num_t orange_pin;	// Pin number for leeds
	gpio_num_t yellow_pin;
	gpio_num_t pink_pin;
	gpio_num_t blue_pin;
	long current_pos;		// Current stepper position
	short current_phase;
	unsigned long ticks;		// Number of ticks between stepping.
	enum {fwd=1, rev=-1} direction;
	const static unsigned char phases[8];
	TickType_t last_wake_time;
	Led led;
	TaskHandle_t task_handle;
};

#endif /* STEPPER_H_ */
