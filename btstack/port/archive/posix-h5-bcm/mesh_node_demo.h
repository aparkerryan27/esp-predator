
// mesh_node_demo.h generated from ../../example/mesh_node_demo.gatt for BTstack
// it needs to be regenerated when the .gatt file is updated. 

// To generate mesh_node_demo.h:
// ../../tool/compile_gatt.py ../../example/mesh_node_demo.gatt mesh_node_demo.h

// att db format version 1

// binary attribute representation:
// - size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#include <stdint.h>

const uint8_t profile_data[] =
{
    // ATT DB Version
    1,

    // 0x0001 PRIMARY_SERVICE-GAP_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18, 
    // 0x0002 CHARACTERISTIC-GAP_DEVICE_NAME-READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a, 
    // 0x0003 VALUE-GAP_DEVICE_NAME-READ | DYNAMIC-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x03, 0x00, 0x00, 0x2a, 
    // #import <mesh_provisioning_service.gatt> -- BEGIN
    // Specification Type org.bluetooth.service.mesh_provisioning
    // https://www.bluetooth.com/api/gatt/xmlfile?xmlFileName=org.bluetooth.service.mesh_provisioning.xml
    // Mesh Provisioning Service 1827

    // 0x0004 PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_MESH_PROVISIONING
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x27, 0x18, 
    // 0x0005 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_IN-DYNAMIC | WRITE_WITHOUT_RESPONSE
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x04, 0x06, 0x00, 0xdb, 0x2a, 
    // 0x0006 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_IN-DYNAMIC | WRITE_WITHOUT_RESPONSE-''
    // WRITE_ANYBODY
    0x08, 0x00, 0x04, 0x01, 0x06, 0x00, 0xdb, 0x2a, 
    // 0x0007 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_OUT-DYNAMIC | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x07, 0x00, 0x03, 0x28, 0x10, 0x08, 0x00, 0xdc, 0x2a, 
    // 0x0008 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_OUT-DYNAMIC | NOTIFY-''
    // 
    0x08, 0x00, 0x00, 0x01, 0x08, 0x00, 0xdc, 0x2a, 
    // 0x0009 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x09, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // #import <mesh_provisioning_service.gatt> -- END
    // #import <mesh_proxy_service.gatt> -- BEGIN
    // Specification Type org.bluetooth.service.mesh_proxy
    // https://www.bluetooth.com/api/gatt/xmlfile?xmlFileName=org.bluetooth.service.mesh_proxy.xml
    // Mesh Proxy Service 1828

    // 0x000a PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_MESH_PROXY
    0x0a, 0x00, 0x02, 0x00, 0x0a, 0x00, 0x00, 0x28, 0x28, 0x18, 
    // 0x000b CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROXY_DATA_IN-DYNAMIC | WRITE_WITHOUT_RESPONSE
    0x0d, 0x00, 0x02, 0x00, 0x0b, 0x00, 0x03, 0x28, 0x04, 0x0c, 0x00, 0xdd, 0x2a, 
    // 0x000c VALUE-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROXY_DATA_IN-DYNAMIC | WRITE_WITHOUT_RESPONSE-''
    // WRITE_ANYBODY
    0x08, 0x00, 0x04, 0x01, 0x0c, 0x00, 0xdd, 0x2a, 
    // 0x000d CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROXY_DATA_OUT-DYNAMIC | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x0d, 0x00, 0x03, 0x28, 0x10, 0x0e, 0x00, 0xde, 0x2a, 
    // 0x000e VALUE-ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROXY_DATA_OUT-DYNAMIC | NOTIFY-''
    // 
    0x08, 0x00, 0x00, 0x01, 0x0e, 0x00, 0xde, 0x2a, 
    // 0x000f CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x0f, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // #import <mesh_proxy_service.gatt> -- END

    // END
    0x00, 0x00, 
}; // total size 97 bytes 


//
// list service handle ranges
//
#define ATT_SERVICE_GAP_SERVICE_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_END_HANDLE 0x0003
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_MESH_PROVISIONING_START_HANDLE 0x0004
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_MESH_PROVISIONING_END_HANDLE 0x0009
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_MESH_PROXY_START_HANDLE 0x000a
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_MESH_PROXY_END_HANDLE 0x000f

//
// list mapping between characteristics and handles
//
#define ATT_CHARACTERISTIC_GAP_DEVICE_NAME_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_IN_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_OUT_01_VALUE_HANDLE 0x0008
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROVISIONING_DATA_OUT_01_CLIENT_CONFIGURATION_HANDLE 0x0009
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROXY_DATA_IN_01_VALUE_HANDLE 0x000c
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROXY_DATA_OUT_01_VALUE_HANDLE 0x000e
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MESH_PROXY_DATA_OUT_01_CLIENT_CONFIGURATION_HANDLE 0x000f
