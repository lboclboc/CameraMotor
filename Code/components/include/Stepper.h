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
#include <esp_timer.h>

typedef void (*step_callback_t)(void);

class Stepper
{
public:
	Stepper(gpio_num_t b=GPIO_NUM_12,
			gpio_num_t p=GPIO_NUM_13,
			gpio_num_t y=GPIO_NUM_14,
			gpio_num_t o=GPIO_NUM_15,
			float period=1.0,
			step_callback_t step_callback=0);
	virtual ~Stepper();
	void step();
	void set_period(float seconds);
	void set_step_callback(step_callback_t cb) { step_callback = cb; }
	void init();
	static const int fwd = -1;
	static const int rev = 1;

protected:
	void run();

private:
	static void timer_callback(void *);
	gpio_num_t orange_pin;	// Pin number for leeds
	gpio_num_t yellow_pin;
	gpio_num_t pink_pin;
	gpio_num_t blue_pin;
	long current_pos;		// Current stepper position
	short current_phase;
	unsigned long ticks;		// Number of ticks between stepping.
	short direction;
	const static unsigned char phases[8];
	TickType_t last_wake_time;
	esp_timer_handle_t timer_handle;
	step_callback_t step_callback;
};

#endif /* STEPPER_H_ */
