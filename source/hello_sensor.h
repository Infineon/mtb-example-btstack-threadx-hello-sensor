/*******************************************************************************
* (c) 2021-2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/
/** @file
*
* LE Vendor Specific Device
*
* This file provides definitions and function prototypes for Hello Sensor
* device
*
*/


#ifndef HELLO_SENSOR_H
#define HELLO_SENSOR_H

#ifdef COMPONENT_nvram_emulation
#include "nvram_emulation_mem.h"
#endif

#include "wiced_memory.h"
#include "bt_types.h"
#define BT_STACK_HEAP_SIZE          1024 * 6
#define wiced_bt_gatt_send_notification(id, type, len, ptr) wiced_bt_gatt_server_send_notification(id, type, len, ptr, NULL)
#define wiced_bt_gatt_send_indication(id, type, len, ptr)   wiced_bt_gatt_server_send_indication(id, type, len, ptr, NULL)
uint8_t *hello_sensor_alloc_buffer(uint16_t len);
void hello_sensor_free_buffer(uint8_t *p_data);
typedef void (*pfn_free_buffer_t)(uint8_t *);

extern const wiced_transport_cfg_t transport_cfg;
void hello_sensor_gatt_init();
extern const uint8_t hello_sensor_gatt_database[];
extern size_t hello_sensor_gatt_database_size;

#ifndef PACKED
#define PACKED
#endif

/******************************************************************************
 *                                Constants
 ******************************************************************************/
#define HELLO_SENSOR_MAX_NUM_CLIENTS 1

/* Hello Sensor App Timer Timeout in seconds  */
#define HELLO_SENSOR_APP_TIMEOUT_IN_SECONDS                 1

/* Hello Sensor App Fine Timer Timeout in milli seconds  */
#define HELLO_SENSOR_APP_FINE_TIMEOUT_IN_MS                 1

/* Hello Sensor Connection Idle  Timeout in milli seconds  */
#define HELLO_SENSOR_CONN_IDLE_TIMEOUT_IN_SECONDS           3

#define HELLO_SENSOR_VS_ID                      WICED_NVRAM_VSID_START
#define HELLO_SENSOR_LOCAL_KEYS_VS_ID          ( WICED_NVRAM_VSID_START + 1 )
#define HELLO_SENSOR_PAIRED_KEYS_VS_ID          ( WICED_NVRAM_VSID_START + 2 )

/******************************************************************************
 *                         Type Definitions
 ******************************************************************************/
typedef enum
{
    HANDLE_HSENS_GATT_SERVICE = 0x1, // service handle

    HANDLE_HSENS_GAP_SERVICE = 0x14, // service handle
    HANDLE_HSENS_GAP_SERVICE_CHAR_DEV_NAME, // characteristic handl
    HANDLE_HSENS_GAP_SERVICE_CHAR_DEV_NAME_VAL, // char value handle

    HANDLE_HSENS_GAP_SERVICE_CHAR_DEV_APPEARANCE, // characteristic handl
    HANDLE_HSENS_GAP_SERVICE_CHAR_DEV_APPEARANCE_VAL,// char value handle

    HANDLE_HSENS_SERVICE = 0x28,
    HANDLE_HSENS_SERVICE_CHAR_NOTIFY, // characteristic handl
    HANDLE_HSENS_SERVICE_CHAR_NOTIFY_VAL, // char value handle
    HANDLE_HSENS_SERVICE_CHAR_CFG_DESC, // charconfig desc handl

    HANDLE_HSENS_SERVICE_CHAR_BLINK, // characteristic handl
    HANDLE_HSENS_SERVICE_CHAR_BLINK_VAL, // char value handle

    HANDLE_HSENS_SERVICE_CHAR_LONG_MSG, // characteristic handl
    HANDLE_HSENS_SERVICE_CHAR_LONG_MSG_VAL, //long  char value handl......

    HANDLE_HSENS_DEV_INFO_SERVICE = 0x40,
    HANDLE_HSENS_DEV_INFO_SERVICE_CHAR_MFR_NAME, // characteristic handle
    HANDLE_HSENS_DEV_INFO_SERVICE_CHAR_MFR_NAME_VAL,// char value handle

    HANDLE_HSENS_DEV_INFO_SERVICE_CHAR_MODEL_NUM, // characteristic handl
    HANDLE_HSENS_DEV_INFO_SERVICE_CHAR_MODEL_NUM_VAL,// char value handle

    HANDLE_HSENS_DEV_INFO_SERVICE_CHAR_SYSTEM_ID, // characteristic handl
    HANDLE_HSENS_DEV_INFO_SERVICE_CHAR_SYSTEM_ID_VAL,// char value handle

    HANDLE_HSENS_BATTERY_SERVICE = 0x60, // service handle
    HANDLE_HSENS_BATTERY_SERVICE_CHAR_LEVEL, // characteristic handl
    HANDLE_HSENS_BATTERY_SERVICE_CHAR_LEVEL_VAL, // char value andle

    // Client Configuration
    HDLD_CURRENT_TIME_SERVICE_CURRENT_TIME_CLIENT_CONFIGURATION,
}hello_sensor_db_tags;

/******************************************************************************
 *                                Structures
 ******************************************************************************/
typedef struct
{
    BD_ADDR   remote_addr;              // remote peer device address
    uint32_t  timer_count;              // timer count
    uint32_t  fine_timer_count;         // fine timer count
    uint16_t  conn_id;                  // connection ID referenced by the stack
    uint16_t  peer_mtu;                 // peer MTU
    uint8_t   num_to_write;             // num msgs to send, incr on each button intr
    uint8_t   flag_indication_sent;     // indicates waiting for ack/cfm
    uint8_t   flag_stay_connected;      // stay connected or disconnect after all messages are sent
    uint8_t   battery_level;            // fake battery level

} hello_sensor_state_t;

#pragma pack(1)
/* Host information saved in  NVRAM */
typedef PACKED struct
{
    BD_ADDR  bdaddr;                                /* BD address of the bonded host */
    uint16_t  characteristic_client_configuration;  /* Current value of the client configuration descriptor */
    uint8_t   number_of_blinks;                     /* Sensor config, number of times to blink the LEd when button is pushed. */
} host_info_t;
#pragma pack()
typedef struct
{
    uint16_t handle;
    uint16_t attr_len;
    void     *p_attr;
} attribute_t;

#endif // HELLO_SENSOR_H
