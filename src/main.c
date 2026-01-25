#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <lvgl/lvgl.h>

#include "cap_sdk.h"

int main(void)
{
    cap_sdk_init();

    lv_obj_t * screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x1f1f1f), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, "CAP-OS");
    
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);

    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, LV_PART_MAIN); 
    
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();

        usleep(time_till_next * 1000); 
    }

    return 0;
}