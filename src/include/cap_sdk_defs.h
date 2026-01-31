#ifndef CAP_SDK_DEFS_H
#define CAP_SDK_DEFS_H

typedef enum{
    WIFI_ON = 0,
    WIFI_OFF = 1,
}  wifi_state_t;

typedef enum{
    WIFI_IP = 0,
    WIFI_MACADDRESS = 1,
    WIFI_NETWORK_NAME = 2,
    WIFI_NETWORK_STATUS = 3,
} wifi_info_t;

typedef enum {
    RET_OK = 0,
    RET_NOTOK = 1,
    RET_INVALID_PARAMS = 2,
} cap_sdk_returns;

#endif