/*
 * Led.cpp
 *
 *  Created on: May 4, 2019
 *      Author: lasse
 */

#include <esp_system.h>
#include <driver/gpio.h>
#include "Led.h"


Led::Led() {
	// TODO Auto-generated constructor stub
	gpio_config_t gpio_cfg = {
		GPIO_NUM_2, 			/*!< GPIO pin: set with bit mask, each bit maps to a GPIO */
		GPIO_MODE_OUTPUT,		/*!< GPIO mode: set input/output mode */
		GPIO_PULLUP_DISABLE, 	/*!< GPIO pull-up */
		GPIO_PULLDOWN_DISABLE, 	/*!< GPIO pull-down */
		GPIO_INTR_DISABLE, 		/*!< GPIO interrupt type */
	};

    ESP_ERROR_CHECK(gpio_config(&gpio_cfg));
    off();
}

Led::~Led() {
	// TODO Auto-generated destructor stub
}

void Led::on()
{
	gpio_set_level(GPIO_NUM_2, 1);
}

void Led::off()
{
	gpio_set_level(GPIO_NUM_2, 1);
}

void Led::toggle()
{
	gpio_set_level(GPIO_NUM_2, 1 - gpio_get_level(GPIO_NUM_2));
}
