/*
 * TODO: Stop or not while taking photo.
 * TODO: Exposure time.
 */

#include <string>
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

#define MINOR_COGS 9
#define MAJOR_COGS 37
#define STEPS_PER_TURN 4096
#define SIDEREAL_DAY_SECONDS ((((23 * 60.0) + 65) * 60.0) + 4.091)

void app_main(void);

#ifdef __cplusplus
}
#endif

#include "Stepper.h"
#include "PowerLoad.h"

char template_period[20];
char template_timelapse[20];
char template_sidereal[20];

#include "html_page.h"

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifi_event_group;
static const char *TAG = "user_main";
const int WIFI_CONNECTED_BIT = BIT0;


static Stepper stepper;
static PowerLoad power_load;
static float sidereal = (SIDEREAL_DAY_SECONDS * MINOR_COGS) / (MAJOR_COGS * STEPS_PER_TURN);
static float period = sidereal;

esp_err_t root_get_handler(httpd_req_t *req)
{
	char query[200];

	float timelapse = 0;
	if (httpd_req_get_url_query_str(req, query, sizeof query) == ESP_OK) {
		if (httpd_query_key_value(query, "period", template_period, sizeof template_period) == ESP_OK) {
			period = atof(template_period);
			period = stepper.set_period(period);
		}

		if (httpd_query_key_value(query, "timelapse", template_timelapse, sizeof template_timelapse) == ESP_OK) {
			timelapse = atof(template_timelapse);
		}
	}

	gcvtf(period, 7,template_period);
	gcvtf(timelapse, 7,template_timelapse);
	gcvtf(sidereal, 7,template_sidereal);
	ESP_LOGI(TAG, "template_period=%s", template_period);

    /* Send response */
	for (const char *s : html_page) {
		httpd_resp_send_chunk(req, s, strlen(s));
	}
	httpd_resp_send_chunk(req, 0, 0);

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
	uint8_t mac[6];
	char ssid[32];
	ESP_LOGI(TAG, "Setting up wifi...");


	wifi_event_group = xEventGroupCreate();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, server) );

	ESP_ERROR_CHECK(esp_wifi_get_mac(ESP_IF_WIFI_AP, mac));
	sprintf(ssid, "EQCAM%02X%02X%02X", mac[3], mac[4], mac[5]);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config;
    memset(&wifi_config, 0, sizeof wifi_config);
    strncpy((char *)wifi_config.ap.ssid, ssid, sizeof wifi_config.ap.ssid);
    wifi_config.ap.ssid_len = strlen(ssid);
    wifi_config.ap.max_connection = 5;
    wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;

    strncpy((char *)wifi_config.ap.password, "asdqwe123", sizeof wifi_config.ap.password);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_softap finished");

}

/******************************************************************************
 * FunctionName : app_main
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void app_main(void)
{
    printf("SDK version:%s\n", esp_get_idf_version());

    static httpd_handle_t server = NULL;
    stepper.init();
    stepper.set_period(sidereal);
    power_load.init();
    init_wifi(&server);

    if (server == NULL) {
        server = start_webserver();
    }
}
