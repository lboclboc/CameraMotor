/*
 * PowerLoad.cpp
 *
 * Periodically pull current through the power load resistor.
 * This is needed for some power packs to not turn off after a while.
 * ** Not yet implemented **
 *  Created on: Jun 25, 2019
 *      Author: lasse
 */
#include <esp_system.h>
#include <FreeRTOS.h>
#include <task.h>
#include <PowerLoad.h>

PowerLoad::PowerLoad(gpio_num_t p) : pin(p) {
	// TODO Auto-generated constructor stub

}

PowerLoad::~PowerLoad() {
	// TODO Auto-generated destructor stub
}

void PowerLoad::init()
{
	gpio_config_t gpio_cfg = {
		BIT(pin),
		GPIO_MODE_OUTPUT,
		GPIO_PULLUP_DISABLE,
		GPIO_PULLDOWN_DISABLE,
		GPIO_INTR_DISABLE,
	};
    ESP_ERROR_CHECK(gpio_config(&gpio_cfg));

	gpio_set_level(pin, 0);
}
