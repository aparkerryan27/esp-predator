# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# compile C with /home/parker/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
C_FLAGS = -mlongcalls -Wno-frame-address  

C_DEFINES = -DHAVE_CONFIG_H -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\" -DUNITY_INCLUDE_CONFIG_H -DWITH_POSIX

C_INCLUDES = -I/home/parker/esp/esp-idf/components/xtensa/include -I/home/parker/esp/esp-idf/components/xtensa/esp32/include -I/home/parker/esp/robot/src/build/config -I/home/parker/esp/esp-idf/components/newlib/platform_include -I/home/parker/esp/esp-idf/components/freertos/include -I/home/parker/esp/esp-idf/components/heap/include -I/home/parker/esp/esp-idf/components/log/include -I/home/parker/esp/esp-idf/components/lwip/include/apps -I/home/parker/esp/esp-idf/components/lwip/include/apps/sntp -I/home/parker/esp/esp-idf/components/lwip/lwip/src/include -I/home/parker/esp/esp-idf/components/lwip/port/esp32/include -I/home/parker/esp/esp-idf/components/lwip/port/esp32/include/arch -I/home/parker/esp/esp-idf/components/lwip/port/esp32/tcp_isn -I/home/parker/esp/esp-idf/components/soc/esp32/include -I/home/parker/esp/esp-idf/components/soc/include -I/home/parker/esp/esp-idf/components/esp_rom/include -I/home/parker/esp/esp-idf/components/esp_common/include -I/home/parker/esp/esp-idf/components/esp32/include -I/home/parker/esp/esp-idf/components/driver/include -I/home/parker/esp/esp-idf/components/driver/esp32/include -I/home/parker/esp/esp-idf/components/esp_ringbuf/include -I/home/parker/esp/esp-idf/components/efuse/include -I/home/parker/esp/esp-idf/components/efuse/esp32/include -I/home/parker/esp/esp-idf/components/vfs/include -I/home/parker/esp/esp-idf/components/esp_wifi/include -I/home/parker/esp/esp-idf/components/esp_wifi/esp32/include -I/home/parker/esp/esp-idf/components/esp_event/include -I/home/parker/esp/esp-idf/components/esp_netif/include -I/home/parker/esp/esp-idf/components/esp_eth/include -I/home/parker/esp/esp-idf/components/tcpip_adapter/include -I/home/parker/esp/esp-idf/components/app_trace/include -I/home/parker/esp/esp-idf/components/app_update/include -I/home/parker/esp/esp-idf/components/spi_flash/include -I/home/parker/esp/esp-idf/components/bootloader_support/include -I/home/parker/esp/esp-idf/components/mbedtls/port/include -I/home/parker/esp/esp-idf/components/mbedtls/mbedtls/include -I/home/parker/esp/esp-idf/components/nvs_flash/include -I/home/parker/esp/esp-idf/components/pthread/include -I/home/parker/esp/esp-idf/components/espcoredump/include -I/home/parker/esp/esp-idf/components/perfmon/include -I/home/parker/esp/esp-idf/components/wpa_supplicant/include -I/home/parker/esp/esp-idf/components/wpa_supplicant/port/include -I/home/parker/esp/esp-idf/components/wpa_supplicant/include/esp_supplicant -I/home/parker/esp/esp-idf/components/asio/asio/asio/include -I/home/parker/esp/esp-idf/components/asio/port/include -I/home/parker/esp/esp-idf/components/bt/include -I/home/parker/esp/esp-idf/components/bt/common/osi/include -I/home/parker/esp/esp-idf/components/btstack/3rd-party/bluedroid/decoder/include -I/home/parker/esp/esp-idf/components/btstack/3rd-party/bluedroid/encoder/include -I/home/parker/esp/esp-idf/components/btstack/3rd-party/hxcmod-player -I/home/parker/esp/esp-idf/components/btstack/3rd-party/hxcmod-player/mods -I/home/parker/esp/esp-idf/components/btstack/3rd-party/lwip/dhcp-server -I/home/parker/esp/esp-idf/components/btstack/3rd-party/md5 -I/home/parker/esp/esp-idf/components/btstack/3rd-party/yxml -I/home/parker/esp/esp-idf/components/btstack/src/classic -I/home/parker/esp/esp-idf/components/btstack/src/ble/gatt-service -I/home/parker/esp/esp-idf/components/btstack/src/ble -I/home/parker/esp/esp-idf/components/btstack/src -I/home/parker/esp/esp-idf/components/btstack/platform/embedded -I/home/parker/esp/esp-idf/components/btstack/platform/freertos -I/home/parker/esp/esp-idf/components/btstack/platform/lwip -I/home/parker/esp/esp-idf/components/btstack/include -I/home/parker/esp/esp-idf/components/cbor/port/include -I/home/parker/esp/esp-idf/components/coap/port/include -I/home/parker/esp/esp-idf/components/coap/port/include/coap -I/home/parker/esp/esp-idf/components/coap/libcoap/include -I/home/parker/esp/esp-idf/components/coap/libcoap/include/coap2 -I/home/parker/esp/esp-idf/components/console -I/home/parker/esp/esp-idf/components/nghttp/port/include -I/home/parker/esp/esp-idf/components/nghttp/nghttp2/lib/includes -I/home/parker/esp/esp-idf/components/esp-tls -I/home/parker/esp/esp-idf/components/esp_adc_cal/include -I/home/parker/esp/esp-idf/components/esp_gdbstub/include -I/home/parker/esp/esp-idf/components/tcp_transport/include -I/home/parker/esp/esp-idf/components/esp_http_client/include -I/home/parker/esp/esp-idf/components/esp_http_server/include -I/home/parker/esp/esp-idf/components/esp_https_ota/include -I/home/parker/esp/esp-idf/components/protobuf-c/protobuf-c -I/home/parker/esp/esp-idf/components/protocomm/include/common -I/home/parker/esp/esp-idf/components/protocomm/include/security -I/home/parker/esp/esp-idf/components/protocomm/include/transports -I/home/parker/esp/esp-idf/components/mdns/include -I/home/parker/esp/esp-idf/components/esp_local_ctrl/include -I/home/parker/esp/esp-idf/components/sdmmc/include -I/home/parker/esp/esp-idf/components/esp_serial_slave_link/include -I/home/parker/esp/esp-idf/components/esp_websocket_client/include -I/home/parker/esp/esp-idf/components/expat/expat/expat/lib -I/home/parker/esp/esp-idf/components/expat/port/include -I/home/parker/esp/esp-idf/components/wear_levelling/include -I/home/parker/esp/esp-idf/components/fatfs/diskio -I/home/parker/esp/esp-idf/components/fatfs/vfs -I/home/parker/esp/esp-idf/components/fatfs/src -I/home/parker/esp/esp-idf/components/freemodbus/common/include -I/home/parker/esp/esp-idf/components/idf_test/include -I/home/parker/esp/esp-idf/components/jsmn/include -I/home/parker/esp/esp-idf/components/json/cJSON -I/home/parker/esp/esp-idf/components/libsodium/libsodium/src/libsodium/include -I/home/parker/esp/esp-idf/components/libsodium/port_include -I/home/parker/esp/esp-idf/components/mqtt/esp-mqtt/include -I/home/parker/esp/esp-idf/components/openssl/include -I/home/parker/esp/esp-idf/components/spiffs/include -I/home/parker/esp/esp-idf/components/ulp/include -I/home/parker/esp/esp-idf/components/unity/include -I/home/parker/esp/esp-idf/components/unity/unity/src -I/home/parker/esp/esp-idf/components/wifi_provisioning/include -I/home/parker/esp/robot/src/main -I/home/parker/esp/esp-idf/examples/common_components/protocol_examples_common/include 

