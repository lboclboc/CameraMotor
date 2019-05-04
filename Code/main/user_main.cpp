/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#define  ICACHE_FLASH_ATTR
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include <esp_system.h>
#include <esp_task_wdt.h>
#include <driver/adc.h>
#include <driver/gpio.h>

void app_main(void);

#ifdef __cplusplus
}
#endif


/******************************************************************************
 * FunctionName : app_main
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void app_main(void)
{
	static uint16_t samples[8192];
	adc_config_t adc_cfg;

	adc_cfg.mode = ADC_READ_TOUT_MODE;
	adc_cfg.clk_div = 8;

	gpio_config_t gpio_cfg = {
		GPIO_Pin_2, 			/*!< GPIO pin: set with bit mask, each bit maps to a GPIO */
		GPIO_MODE_OUTPUT,		/*!< GPIO mode: set input/output mode */
		GPIO_PULLUP_DISABLE, 	/*!< GPIO pull-up */
		GPIO_PULLDOWN_DISABLE, 	/*!< GPIO pull-down */
		GPIO_INTR_DISABLE, 		/*!< GPIO interrupt type */
	};

    printf("SDK version:%s\n", esp_get_idf_version());
    ESP_ERROR_CHECK(adc_init(&adc_cfg));
    ESP_ERROR_CHECK(gpio_config(&gpio_cfg));
    while(1)
    {
		ESP_ERROR_CHECK(adc_read_fast(samples, sizeof samples / sizeof samples[0]));
		//printf("ADC value: %d\n", sample);
		gpio_set_level(GPIO_NUM_2, 1 - gpio_get_level(GPIO_NUM_2));
		esp_task_wdt_reset();
    }
}
