#include "pros/apix.h"
#include "ui.h"
#include "config.h"
#include <algorithm>
#include <cmath>

// Screens
static lv_obj_t* homeScreen;
static lv_obj_t* fieldScreen;

// Home screen status lights

// Auton selection

Alliance selectedAlliance = ALLIANCE_NONE;
Side selectedSide = SIDE_LEFT;

// Auton buttons
static lv_obj_t* redLeftBtn;
static lv_obj_t* redRightBtn;
static lv_obj_t* blueLeftBtn;
static lv_obj_t* blueRightBtn;

// Styles
static lv_style_t selectedStyle;
static lv_style_t normalStyle;

void initAutonStyles() {
    lv_style_init(&selectedStyle);
    lv_style_set_bg_color(&selectedStyle, lv_color_hex(0x00AAFF));
    lv_style_set_bg_opa(&selectedStyle, LV_OPA_80);

    lv_style_init(&normalStyle);
    lv_style_set_bg_color(&normalStyle, lv_color_hex(0x333333));
    lv_style_set_bg_opa(&normalStyle, LV_OPA_80);
}

// ------------------------
// Status Light Helper
// ------------------------
lv_obj_t* makeStatusLight(lv_obj_t* parent, int x, int y, const char* labelText, const char* portText) {
    lv_obj_t* container = lv_obj_create(parent);
    lv_obj_set_size(container, 160, 20);
    lv_obj_set_pos(container, x, y);

    lv_obj_set_style_pad_all(container, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(container, 0, LV_PART_MAIN);

    char buf[48];
    snprintf(buf, sizeof(buf), "%s (%s)", labelText, portText);

    lv_obj_t* label = lv_label_create(container);
    lv_label_set_text(label, buf);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_set_pos(label, 3, 3);

    lv_obj_t* light = lv_obj_create(container);
    lv_obj_set_size(light, 12, 12);
    lv_obj_set_style_radius(light, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_pos(light, 135, 4);

    return light;
}

// ------------------------
// Build Home Screen
// ------------------------
void buildHomeScreen() {
    lv_obj_set_style_bg_color(homeScreen, lv_color_hex(0x111111), LV_PART_MAIN);

    int leftX = 20;
    int rightX = 260;
    int y = 5;
    int step = 22;


    // Auton Select Button
    lv_obj_t* fieldBtn = lv_button_create(homeScreen);
    lv_obj_set_size(fieldBtn, 150, 35);
    lv_obj_set_pos(fieldBtn, 165, 205);

    lv_obj_t* label = lv_label_create(fieldBtn);
    lv_label_set_text(label, "Auton Select");
    lv_obj_center(label);

    lv_obj_add_event_cb(fieldBtn, [](lv_event_t* e){
        lv_screen_load(fieldScreen);
    }, LV_EVENT_CLICKED, NULL);
}

// ------------------------
// Build Auton Selector Screen
// ------------------------
void buildFieldScreen() {
    lv_obj_set_style_bg_color(fieldScreen, lv_color_hex(0x000000), LV_PART_MAIN);

    int btnW = 140;
    int btnH = 40;

    // Red Left
    redLeftBtn = lv_button_create(fieldScreen);
    lv_obj_set_size(redLeftBtn, btnW, btnH);
    lv_obj_set_pos(redLeftBtn, 20, 20);
    lv_obj_add_style(redLeftBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_t* rlLabel = lv_label_create(redLeftBtn);
    lv_label_set_text(rlLabel, "Red Left");
    lv_obj_center(rlLabel);
    lv_obj_add_event_cb(redLeftBtn, [](lv_event_t* e){
        selectedAlliance = ALLIANCE_RED;
        selectedSide = SIDE_LEFT;
    }, LV_EVENT_CLICKED, NULL);

    // Red Right
    redRightBtn = lv_button_create(fieldScreen);
    lv_obj_set_size(redRightBtn, btnW, btnH);
    lv_obj_set_pos(redRightBtn, 180, 20);
    lv_obj_add_style(redRightBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_t* rrLabel = lv_label_create(redRightBtn);
    lv_label_set_text(rrLabel, "Red Right");
    lv_obj_center(rrLabel);
    lv_obj_add_event_cb(redRightBtn, [](lv_event_t* e){
        selectedAlliance = ALLIANCE_RED;
        selectedSide = SIDE_RIGHT;
    }, LV_EVENT_CLICKED, NULL);

    // Blue Left
    blueLeftBtn = lv_button_create(fieldScreen);
    lv_obj_set_size(blueLeftBtn, btnW, btnH);
    lv_obj_set_pos(blueLeftBtn, 20, 80);
    lv_obj_add_style(blueLeftBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_t* blLabel = lv_label_create(blueLeftBtn);
    lv_label_set_text(blLabel, "Blue Left");
    lv_obj_center(blLabel);
    lv_obj_add_event_cb(blueLeftBtn, [](lv_event_t* e){
        selectedAlliance = ALLIANCE_BLUE;
        selectedSide = SIDE_LEFT;
    }, LV_EVENT_CLICKED, NULL);

    // Blue Right
    blueRightBtn = lv_button_create(fieldScreen);
    lv_obj_set_size(blueRightBtn, btnW, btnH);
    lv_obj_set_pos(blueRightBtn, 180, 80);
    lv_obj_add_style(blueRightBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_t* brLabel = lv_label_create(blueRightBtn);
    lv_label_set_text(brLabel, "Blue Right");
    lv_obj_center(brLabel);
    lv_obj_add_event_cb(blueRightBtn, [](lv_event_t* e){
        selectedAlliance = ALLIANCE_BLUE;
        selectedSide = SIDE_RIGHT;
    }, LV_EVENT_CLICKED, NULL);

    // Back button
    lv_obj_t* backBtn = lv_button_create(fieldScreen);
    lv_obj_set_size(backBtn, 120, 40);
    lv_obj_set_pos(backBtn, 140, 160);

    lv_obj_t* backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);

    lv_obj_add_event_cb(backBtn, [](lv_event_t* e){
        lv_screen_load(homeScreen);
    }, LV_EVENT_CLICKED, NULL);
}

// ------------------------
// Highlight Logic
// ------------------------
void updateAutonHighlight() {
    // Reset all
    lv_obj_add_style(redLeftBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_add_style(redRightBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_add_style(blueLeftBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_add_style(blueRightBtn, &normalStyle, LV_PART_MAIN);

    // Apply highlight
    if (selectedAlliance == ALLIANCE_RED && selectedSide == SIDE_LEFT)
        lv_obj_add_style(redLeftBtn, &selectedStyle, LV_PART_MAIN);

    if (selectedAlliance == ALLIANCE_RED && selectedSide == SIDE_RIGHT)
        lv_obj_add_style(redRightBtn, &selectedStyle, LV_PART_MAIN);

    if (selectedAlliance == ALLIANCE_BLUE && selectedSide == SIDE_LEFT)
        lv_obj_add_style(blueLeftBtn, &selectedStyle, LV_PART_MAIN);

    if (selectedAlliance == ALLIANCE_BLUE && selectedSide == SIDE_RIGHT)
        lv_obj_add_style(blueRightBtn, &selectedStyle, LV_PART_MAIN);
}

// ------------------------
// Init UI
// ------------------------
void uiInit() {
    homeScreen = lv_obj_create(NULL);
    fieldScreen = lv_obj_create(NULL);

    initAutonStyles();
    buildHomeScreen();
    buildFieldScreen();

    lv_screen_load(homeScreen);

    pros::Task uiTask([] {
        while (true) {
            uiUpdate();
            pros::delay(50);
        }
    });
}

// ------------------------
// Update Home Screen
// ------------------------
void uiUpdate() {
    if (lv_screen_active() == fieldScreen) {
        updateAutonHighlight();
    }
}
