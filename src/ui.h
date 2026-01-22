#include "pros/apix.h"   // LVGL comes from here
#include "liblvgl/lvgl.h"
#include "liblvgl/lv_api_map_v8.h"  // For v8 API compatibility
#include "config.h"
#include <algorithm>


void uiInit();     // builds the UI
void uiUpdate();   // updates odom + status lights
