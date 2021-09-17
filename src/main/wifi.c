//additional tcp necessities
#include <stdio.h>
#include <sys/fcntl.h>
#include "esp_system.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "wifi.h"

#include <string.h>

//wifi necessities
#include "driver/gpio.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_wifi_default.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "sdkconfig.h"

#include "uni_debug.h"


//writing to motors
#include "uni_platform_implementation.h"

#define MESSAGE "rcvd...."
#define LISTENQ 2

//define true and false bits under nice names
#define GOT_IPV4_BIT BIT(0)
#define GOT_IPV6_BIT BIT(1)

#define TAG "wifi"

#define CONNECTED_BIT (GOT_IPV4_BIT)

struct motor_data {
    int32_t axis1;
    int32_t axis2;
};

//create a group handler for the event flags
static EventGroupHandle_t s_connect_event_group;

static esp_ip4_addr_t s_ip_addr;
static const char *s_connection_name;
static esp_netif_t *s_esp_netif = NULL;

static void start(void);
static void stop(void);

static void on_got_ip(void *arg, esp_event_base_t event_base,
                      int32_t event_id, void *event_data)
{
  ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
  memcpy(&s_ip_addr, &event->ip_info.ip, sizeof(s_ip_addr));
  xEventGroupSetBits(s_connect_event_group, GOT_IPV4_BIT);
}

esp_err_t wifi_connect(void)
{
  if (s_connect_event_group != NULL) {
      logi("invalid state");
    return ESP_ERR_INVALID_STATE;
  }
     logi("past invalid state");
  s_connect_event_group = xEventGroupCreate();
  start();
  ESP_ERROR_CHECK(esp_register_shutdown_handler(&stop));
  ESP_LOGI(TAG, "got to here at least.....");
  xEventGroupWaitBits(s_connect_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
  logi( "Connected to %s\n", s_connection_name);
  logi("IPv4 address: \n" IPSTR, IP2STR(&s_ip_addr));

  return ESP_OK;
}

esp_err_t wifi_disconnect(void)
{
    //if there is nothing to disconnect from, error
    if (s_connect_event_group == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    //otherwise delete the connection group and set it null
    vEventGroupDelete(s_connect_event_group);
    s_connect_event_group = NULL;
    //actually end the connection
    stop();
    s_connection_name = NULL;
    ESP_ERROR_CHECK(esp_unregister_shutdown_handler(&stop));
    return ESP_OK;
}


static void on_wifi_disconnect(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    esp_err_t err = esp_wifi_connect();
    if (err == ESP_ERR_WIFI_NOT_STARTED) {
        return;
    }
    ESP_ERROR_CHECK(err);
}

static void start(void)
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    esp_netif_config_t netif_config = ESP_NETIF_DEFAULT_WIFI_STA();
    esp_netif_t *netif = esp_netif_new(&netif_config);
    assert(netif);
    esp_netif_attach_wifi_station(netif);
    esp_wifi_set_default_wifi_sta_handlers();
    s_esp_netif = netif;
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &on_wifi_disconnect, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &on_got_ip, NULL));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "mazenet",
            .password = "Albifrons2020",
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    esp_wifi_connect();
    s_connection_name = CONFIG_EXAMPLE_WIFI_SSID;
}

static void stop(void)
{
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &on_wifi_disconnect));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &on_got_ip));
    esp_err_t err = esp_wifi_stop();

    if (err == ESP_ERR_WIFI_NOT_INIT) {
        return;
    }

    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(esp_wifi_deinit());
    ESP_ERROR_CHECK(esp_wifi_clear_default_wifi_driver_and_handlers(s_esp_netif));
    esp_netif_destroy(s_esp_netif);
    s_esp_netif = NULL;
}

esp_netif_t *get_netif(void)
{
  return s_esp_netif;
}


void tcp_server(void *pvParam){
    //TODO: blink LEDS until the connection is set
    turn_leds_on();

    ESP_LOGI(TAG,"tcp_server task started \n");
    struct sockaddr_in tcpServerAddr;
    tcpServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    tcpServerAddr.sin_family = AF_INET;
    tcpServerAddr.sin_port = htons( 3000 );
    int s, r;
    bool reset;
    //char recv_buf[11]; //space for two 4 digit numbers, a space, a comma, and a stop character
    struct motor_data motord;
    motord.axis1 = 0;
    motord.axis2 = 0;
    static struct sockaddr_in remote_addr;
    static unsigned int socklen;
    socklen = sizeof(remote_addr);
    int cs;//client socket
    xEventGroupWaitBits(s_connect_event_group,CONNECTED_BIT,false,true,portMAX_DELAY);

    while(1){
        reset = false;
        logi("Starting socket creation...");

        s = socket(AF_INET, SOCK_STREAM, 0);
        if(s < 0) {
            logi("... Failed to allocate socket.\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
        ESP_LOGI(TAG, "... allocated socket\n");
        if(bind(s, (struct sockaddr *)&tcpServerAddr, sizeof(tcpServerAddr)) != 0) {
            logi("... socket bind failed errno=%d \n", errno);
            close(s);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            continue;
        }
        ESP_LOGI(TAG, "... socket bind done \n");
        if(listen (s, LISTENQ) != 0) {
            logi("... socket listen failed errno=%d \n", errno);
            close(s);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            continue;
        }

        while(1){
            cs = accept( s, (struct sockaddr *)&remote_addr, &socklen);
            //set O_NONBLOCK so that recv will return, otherwise we need to implement message end
            //detection logic. If know the client message format you should instead implement logic
            //detect the end of message
            //fcntl(cs,F_SETFL,O_NONBLOCK);
            ESP_LOGI(TAG,"Incoming Message with data: ");

            do {
                
                //recieve the bytes for the motor data
                r = recv(cs, &motord, 8, 0);
                //logi("size of r is %d", r);
                logi("pwm1 = %d, ", motord.axis1);
                logi("pwm2 = %d \n", motord.axis2);

                //parse the motor speeds and set them accordingly
                set_pwm0(motord.axis1);
                set_pwm1(motord.axis2);

                //Writing Back to Computer
                if( write(cs , MESSAGE , strlen(MESSAGE)) < 0)
                {
                    //TODO: Is this too extreme of a response to one dropped send?
                    ESP_LOGE(TAG, "... Send failed, re-opening up new socket \n");
                    reset = true;
                    r = 0;
                }
                
            } while(r > 0);
            
            close(cs);
            if (reset) {
                close(s);

                //stop the motors after breaking communication
                set_pwm0(0);
                set_pwm1(0);
                break;
            }
        }
        
        ESP_LOGI(TAG, "... checking for another message....");
        //if we let the accept be blocking we don't need a delay here, originally -> vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(TAG, "...tcp_client task closed\n");
}

void start_tcp_server(){
    xTaskCreate(&tcp_server,"tcp_server",4096,NULL,5,NULL); //create the task for freeRTOS
}
