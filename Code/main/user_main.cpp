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
#include <esp_wifi.h>
#include <esp_log.h>
#include <esp_event_loop.h>
#include <esp_http_server.h>
#include <driver/adc.h>
#include <driver/gpio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <event_groups.h>

void app_main(void);

#ifdef __cplusplus
}
#endif

#include "Stepper.h"
#include "html_page.h"

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifi_event_group;
static const char *TAG = "simple wifi";
const int WIFI_CONNECTED_BIT = BIT0;


static Stepper stepper;
xTaskHandle xStepperTask;

esp_err_t root_get_handler(httpd_req_t *req)
{
//    char*  buf;
//    size_t buf_len;

//    /* Get header value string length and allocate memory for length + 1,
//     * extra byte for null termination */
//    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
//    if (buf_len > 1) {
//        buf = (char *)malloc(buf_len);
//        /* Copy null terminated value string into buffer */
//        if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK) {
//            ESP_LOGI(TAG, "Found header => Host: %s", buf);
//        }
//        free(buf);
//    }

	char query[200];
	char period_str[20];
	char timelapse_str[20];
	ESP_ERROR_CHECK(httpd_req_get_url_query_str(req, query, sizeof query));
	ESP_ERROR_CHECK(httpd_query_key_value(query, "period", period_str, sizeof period_str));
	ESP_ERROR_CHECK(httpd_query_key_value(query, "timelapse", timelapse_str, sizeof timelapse_str));
	float period = atof(period_str);
	float timelapse = atof(timelapse_str);
	stepper.set_period(period);
	ESP_LOGI(TAG, "Period=%d, timelapse=%d", (int)(period*100), (int)(timelapse*100));

//    /* Set some custom headers */
//    httpd_resp_set_hdr(req, "Custom-Header-1", "Custom-Value-1");
//    httpd_resp_set_hdr(req, "Custom-Header-2", "Custom-Value-2");

    /* Send response with custom headers and body set as the
     * string passed in user context*/
    httpd_resp_send(req, html_page, sizeof html_page);

    return ESP_OK;
}

httpd_uri_t root = {
    "/",
    HTTP_GET,
    root_get_handler,
    strdup("EQ Motor!")
};

httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &root);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

void stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    httpd_stop(server);
}

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
	httpd_handle_t *server = (httpd_handle_t *) ctx;

    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        /* Start the web server */
        if (*server == NULL) {
            *server = start_webserver();
        }
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;

    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "station:" MACSTR " join, AID=%d", MAC2STR(event->event_info.sta_connected.mac), event->event_info.sta_connected.aid);

        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "station:" MACSTR "leave, AID=%d", MAC2STR(event->event_info.sta_disconnected.mac), event->event_info.sta_disconnected.aid);

        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        if (*server) {
            stop_webserver(*server);
            *server = NULL;
        }
        xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;

    default:
        break;
    }
    return ESP_OK;
}

static void init_wifi(httpd_handle_t *server)
{
	printf("Setting up wifi..\n");

	wifi_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, server) );

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config;
    memset(&wifi_config, 0, sizeof wifi_config);
    strcpy((char *)wifi_config.sta.ssid, "ceciliadataab");
    strcpy((char *)wifi_config.sta.password, "asdqwe123");

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
}

/******************************************************************************
 * FunctionName : app_main
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void app_main(void)
{
    static httpd_handle_t server = NULL;
    printf("SDK version:%s\n", esp_get_idf_version());
    init_wifi(&server);

	/* Start the stepper task - defined in this file. */
	if(xTaskCreate(Stepper::task, "blinkenLichten", configMINIMAL_STACK_SIZE + 512, &stepper, tskIDLE_PRIORITY+10, &xStepperTask) == pdPASS) {
		printf("Task 1 was properly created\n\r");
	}
}
