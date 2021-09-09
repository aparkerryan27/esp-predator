#include "uni_main.h"

#include <string.h>

#include "esp_event.h"
#include "uni_bluetooth.h"
#include "uni_config.h"
#include "uni_debug.h"
#include "uni_hid_device.h"
#include "uni_platform.h"
#include "wifi.h"
#include "firmware.h"

// Main entry point, runs forever
int uni_main(int argc, const char** argv) {
  UNUSED(argc);
  UNUSED(argv);

  logi("\n\nPredator robot firmware.\n");
  logi("Version: v2.0.0\n\n");


  //set up the interface between motors and board
  logi("....setting up h/w interface...\n");
  uni_platform_init(argc, argv);


  //Creates a new instance of the ESP-NETIF layer for handling events
  ESP_ERROR_CHECK(esp_netif_init());
  //ESP_ERROR_CHECK is just an assert that converts any
  //  error throws into filenames and line numbers

  //The event loop library allows components to declare events
  //   to which other components can register handlers
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  
  logi("....connecting to wifi...\n");
  ESP_ERROR_CHECK(wifi_connect());
  start_tcp_server();

  //logi("....checking for OTA update...\n");
  //firmware_update("https://github.com/aparkerryan27/esp-predator-ota", true);
  
  


  //logi("....connecting to bluetooth...\n");
  // Human Interface Device setup
  //uni_hid_device_init();  
  // bluetooth setup.
  //uni_bluetooth_init(); 
  // BTStack loop (accept data forever)
  //btstack_run_loop_execute();  

  return 0;
}
