#include "pros/apix.h"   // LVGL comes from here
#include "config.h"
#include <algorithm>
#pragma once

// Make enums visible to all files
enum Alliance { ALLIANCE_NONE, ALLIANCE_RED, ALLIANCE_BLUE, SKILLS };
enum Side { SIDE_LEFT, SIDE_RIGHT };

// These variables are defined in ui.cpp
extern Alliance selectedAlliance;
extern Side selectedSide;

void uiInit();
void uiUpdate();

