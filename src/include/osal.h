

#include <stdint.h>
#include <linux/fb.h>

/**
 * @brief Structure to hold Framebuffer device information.
 */
typedef struct {
    struct fb_var_screeninfo vinfo; /**< Variable screen info (res, bpp, etc.) */
    struct fb_fix_screeninfo finfo; /**< Fixed screen info (memory start, line length) */
    char *fbp;                      /**< Pointer to mapped framebuffer memory */
    int fbfd;                       /**< Framebuffer file descriptor */
} osal_fb_info_t;

/**
 * @brief Initializes the Framebuffer device (/dev/fb1).
 */
void osal_fb_init(void);

/**
 * @brief System tick callback for LVGL timing.
 * @return Monotonic system time in milliseconds.
 */
uint32_t osal_tick_get(void);
