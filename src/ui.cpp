#include "pros/apix.h"   // MUST be first
#include "ui.h"
#include "config.h"
#include <algorithm>


// LVGL objects
static lv_obj_t* field;
static lv_obj_t* robotDot;

static lv_obj_t* imuLight;
static lv_obj_t* encLight;
static lv_obj_t* motorLight;
static lv_obj_t* batteryLight;

               // initializes LVGL

lv_obj_t* makeStatusLight(int x, int y, const char* labelText) {
    lv_obj_t* container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(container, 200, 30);
    lv_obj_set_pos(container, x, y);

    lv_obj_t* label = lv_label_create(container);
    lv_label_set_text(label, labelText);
    lv_obj_set_pos(label, 5, 5);

    lv_obj_t* light = lv_obj_create(container);
    lv_obj_set_size(light, 20, 20);
    lv_obj_set_style_radius(light, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_pos(light, 170, 5);

    return light;
}

void uiInit() {
    // Field
    field = lv_obj_create(lv_scr_act());
    lv_obj_set_size(field, 240, 240);
    lv_obj_set_style_bg_color(field, lv_color_hex(0x222222), LV_PART_MAIN);
    lv_obj_set_style_border_color(field, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_pos(field, 10, 10);

    // Robot dot
    robotDot = lv_obj_create(lv_scr_act());
    lv_obj_set_size(robotDot, 10, 10);
    lv_obj_set_style_radius(robotDot, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_bg_color(robotDot, lv_color_hex(0xFF0000), LV_PART_MAIN);

    // Status lights
    imuLight     = makeStatusLight(260, 20, "IMU");
    encLight     = makeStatusLight(260, 60, "Encoders");
    motorLight   = makeStatusLight(260, 100, "Motors");
    batteryLight = makeStatusLight(260, 140, "Battery");

    // Start UI update task
    pros::Task uiTask([] {
        while (true) {
            uiUpdate();
            pros::delay(50);
        }
    });
}

void uiUpdate() {
    // Update odometry dot
    auto pose = chassis.getPose();

    int x = pose.x * 5;
    int y = pose.y * 5;

    x = std::clamp(x, 0, 230);
    y = std::clamp(y, 0, 230);

    lv_obj_set_pos(robotDot, 10 + x, 10 + (230 - y));

    // Update status lights
    lv_obj_set_style_bg_color(
        imuLight,
        imu.is_calibrating() ? lv_color_hex(0xFF0000) : lv_color_hex(0x00FF00),
        LV_PART_MAIN
    );

    bool encOK = horizontalEnc.get_position() != 0 || verticalEnc.get_position() != 0;
    lv_obj_set_style_bg_color(
        encLight,
        encOK ? lv_color_hex(0x00FF00) : lv_color_hex(0xFF0000),
        LV_PART_MAIN
    );

    bool motorsOK = front_motor.get_temperature() < 70 && back_motor.get_temperature() < 70;
    lv_obj_set_style_bg_color(
        motorLight,
        motorsOK ? lv_color_hex(0x00FF00) : lv_color_hex(0xFFA500),
        LV_PART_MAIN
    );

    bool batteryOK = pros::battery::get_capacity() > 20;
    lv_obj_set_style_bg_color(
        batteryLight,
        batteryOK ? lv_color_hex(0x00FF00) : lv_color_hex(0xFF0000),
        LV_PART_MAIN
    );
}
