#include "osal.h"

/**
 * @brief High-level SDK initialization.
 * * Initializes hardware abstraction and the graphical user interface.
 */

LV_FONT_DECLARE(cap_montserrat_8);
LV_FONT_DECLARE(cap_montserrat_10);
LV_FONT_DECLARE(cap_montserrat_12);
LV_FONT_DECLARE(cap_montserrat_14);
LV_FONT_DECLARE(cap_montserrat_16);
LV_FONT_DECLARE(cap_montserrat_18);
LV_FONT_DECLARE(cap_montserrat_20);
LV_FONT_DECLARE(cap_montserrat_22);
LV_FONT_DECLARE(cap_montserrat_24);
LV_FONT_DECLARE(cap_montserrat_26);
LV_FONT_DECLARE(cap_montserrat_28);
LV_FONT_DECLARE(cap_montserrat_30);
LV_FONT_DECLARE(cap_montserrat_32);
LV_FONT_DECLARE(cap_montserrat_34);
LV_FONT_DECLARE(cap_montserrat_36);
LV_FONT_DECLARE(cap_montserrat_38);
LV_FONT_DECLARE(cap_montserrat_40);
LV_FONT_DECLARE(cap_montserrat_42);
LV_FONT_DECLARE(cap_montserrat_44);
LV_FONT_DECLARE(cap_montserrat_46);
LV_FONT_DECLARE(cap_montserrat_48);



void cap_sdk_init(void);

int cap_wifi_init(wifi_state_t state);

void cap_wifi_info(wifi_info_t info, char * output);