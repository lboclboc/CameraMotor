/*
 * PowerLoad.h
 *
 *  Created on: Jun 25, 2019
 *      Author: lasse
 */

#ifndef POWERLOAD_H_
#define POWERLOAD_H_
#include <driver/gpio.h>

class PowerLoad {
public:
	PowerLoad(gpio_num_t pin=GPIO_NUM_16);
	virtual ~PowerLoad();
	void init();

private:
	gpio_num_t pin;
};

#endif /* POWERLOAD_H_ */
