#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <lvgl/lvgl.h>

#include <sys/reboot.h>

#include "cap_sdk.h"

int main(void)
{
    char output[14+1] = {0};

    cap_sdk_init();

    lv_obj_t * screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "CAP-OS");
    
    lv_obj_set_style_text_color(title, lv_color_hex(0x1f1f1f), LV_PART_MAIN);

    lv_obj_set_style_text_font(title, &cap_montserrat_42, 0);

    lv_obj_set_size(title, LV_SIZE_CONTENT, LV_SIZE_CONTENT); 
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -20);

    lv_obj_t * led  = lv_led_create(screen);
    lv_obj_set_size(led, 15, 15);
    lv_obj_align(led, LV_ALIGN_CENTER, -80, 30);
    lv_led_set_brightness(led, 150);
    lv_led_set_color(led, lv_palette_main(LV_PALETTE_LIGHT_GREEN));

    int ret = cap_wifi_init(WIFI_ON);
    printf("cap_wifi_init: %d \n", ret);

    memset(output, 0, sizeof(output));
    cap_wifi_info(WIFI_IP, output);
    printf("WIFI_IP: %s \n", output);

    lv_obj_t *ip = lv_label_create(screen);
    lv_label_set_text(ip, output);

    lv_obj_set_style_text_color(ip, lv_color_hex(0x1f1f1f), LV_PART_MAIN);

    lv_obj_set_style_text_font(ip, &cap_montserrat_24, 0);

    lv_obj_set_size(ip, LV_SIZE_CONTENT, LV_SIZE_CONTENT); 
    lv_obj_align(ip, LV_ALIGN_CENTER, 10, 30);
   

    /*memset(output, 0, sizeof(output));
    cap_wifi_info(WIFI_MACADDRESS, output);
    printf("WIFI_MACADDRESS: %s \n", output);*/

    
    
    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        
        usleep(time_till_next * 1000);    
    }
    
    return 0;
}