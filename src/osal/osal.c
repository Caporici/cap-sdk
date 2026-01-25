#include <fcntl.h>
#include <time.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <lvgl/lvgl.h>
#include <lvgl/src/drivers/evdev/lv_evdev.h>

#include "osal.h"

osal_fb_info_t fb_dev; 

uint32_t osal_tick_get(void)
{
    // https://github.com/lvgl/lvgl/issues/6296
    struct timespec period;
    clock_gettime(1, &period);
    uint64_t ticks_ms = period.tv_sec * 1000 + period.tv_nsec / 1000000;
    return (uint32_t)ticks_ms;
}

void osal_fb_init(void)
{

    int fbfd = open("/dev/fb1", O_RDWR);

    // Get fixed screen information
    ioctl(fbfd, FBIOGET_FSCREENINFO, &fb_dev.finfo);

    // Get variable screen information
    ioctl(fbfd, FBIOGET_VSCREENINFO, &fb_dev.vinfo);

    fb_dev.fbp = (char *)mmap(0, fb_dev.finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

    // https://github.com/bvdberg/code/blob/master/linux/framebuffer/fb-example.c
}


