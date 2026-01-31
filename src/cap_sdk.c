#include "osal.h"
#include "ui.h"

void cap_sdk_init(void){
    ui_init();
}

int cap_wifi_init(wifi_state_t state){
    return wifi_set_power(state);
}

void cap_wifi_info(wifi_info_t info, char * output){
    wifi_get_info(info, output);
}