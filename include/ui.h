#pragma once

enum AutonMode {
    AUTON_NONE,
    AUTON_SKILLS,
    AUTON_PUSH7LEFT,
    AUTON_M3L4RIGHT,
    AUTON_AWPLEFT
};

extern AutonMode selectedAuton;

void uiInit();
void uiUpdate();
