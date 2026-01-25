#include "osal.h"
#include <lvgl/lvgl.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

extern osal_fb_info_t fb_dev; 

void ui_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    lv_color32_t *src32 = (lv_color32_t *)px_map;
    int32_t w = lv_area_get_width(area);

    for (int32_t y = area->y1; y <= area->y2; y++)
    {
        uint16_t *dst16 = (uint16_t *)(fb_dev.fbp + (y * fb_dev.finfo.line_length) + (area->x1 * 2));
        for (int32_t x = 0; x < w; x++)
        {
            uint16_t r = (src32->red >> 3) & 0x1F;
            uint16_t g = (src32->green >> 2) & 0x3F;
            uint16_t b = (src32->blue >> 3) & 0x1F;
            *dst16 = (uint16_t)((r << 11) | (g << 5) | b);
            dst16++;
            src32++;
        }
    }
    lv_display_flush_ready(disp);
}

lv_display_t *lv_display(void)
{
    lv_display_t *disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);

    static uint8_t buf[SCREEN_WIDTH * SCREEN_HEIGHT * 2 / 10];
    lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, ui_flush_cb);

    return disp;
}

void lv_indev(lv_display_t *disp)
{

    lv_indev_t *touch_indev = lv_evdev_create(LV_INDEV_TYPE_POINTER, "/dev/input/event4");
    lv_indev_set_display(touch_indev, disp);

    // endev - 90
    lv_evdev_set_swap_axes(touch_indev, true);

    // 99-calibration.conf-35-90
    lv_evdev_set_calibration(touch_indev, 3936, 268, 227, 3880);

}

void ui_init(void){
    lv_init();

    // FB - OK
    osal_fb_init();

    // tick/lvgl
    lv_tick_set_cb(osal_tick_get);

    // lvgl/display
    lv_display_t *disp = lv_display();

    // lvgl/indev
    lv_indev(disp);

    // TODO: MISC/STDLIB/THEMES
}