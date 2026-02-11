#include "pros/apix.h"
#include "ui.h"
#include "config.h"

// Screens
static lv_obj_t* homeScreen;
static lv_obj_t* fieldScreen;

// Auton selection enum
AutonMode selectedAuton = AUTON_NONE;

// Auton buttons
static lv_obj_t* skillsBtn;
static lv_obj_t* push7Btn;
static lv_obj_t* m3l4Btn;
static lv_obj_t* awpBtn;

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
// Build Home Screen
// ------------------------
void buildHomeScreen() {
    lv_obj_set_style_bg_color(homeScreen, lv_color_hex(0x111111), LV_PART_MAIN);

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

    int btnW = 180;
    int btnH = 45;

    // Skills
    skillsBtn = lv_button_create(fieldScreen);
    lv_obj_set_size(skillsBtn, btnW, btnH);
    lv_obj_set_pos(skillsBtn, 20, 20);
    lv_obj_add_style(skillsBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_t* skLabel = lv_label_create(skillsBtn);
    lv_label_set_text(skLabel, "Skills");
    lv_obj_center(skLabel);
    lv_obj_add_event_cb(skillsBtn, [](lv_event_t* e){
        selectedAuton = AUTON_SKILLS;
    }, LV_EVENT_CLICKED, NULL);

    // Push7Left
    push7Btn = lv_button_create(fieldScreen);
    lv_obj_set_size(push7Btn, btnW, btnH);
    lv_obj_set_pos(push7Btn, 20, 80);
    lv_obj_add_style(push7Btn, &normalStyle, LV_PART_MAIN);
    lv_obj_t* p7Label = lv_label_create(push7Btn);
    lv_label_set_text(p7Label, "Push7Left");
    lv_obj_center(p7Label);
    lv_obj_add_event_cb(push7Btn, [](lv_event_t* e){
        selectedAuton = AUTON_PUSH7LEFT;
    }, LV_EVENT_CLICKED, NULL);

    // M3L4Right
    m3l4Btn = lv_button_create(fieldScreen);
    lv_obj_set_size(m3l4Btn, btnW, btnH);
    lv_obj_set_pos(m3l4Btn, 20, 140);
    lv_obj_add_style(m3l4Btn, &normalStyle, LV_PART_MAIN);
    lv_obj_t* m3Label = lv_label_create(m3l4Btn);
    lv_label_set_text(m3Label, "M3L4Right");
    lv_obj_center(m3Label);
    lv_obj_add_event_cb(m3l4Btn, [](lv_event_t* e){
        selectedAuton = AUTON_M3L4RIGHT;
    }, LV_EVENT_CLICKED, NULL);

    // AWPleft
    awpBtn = lv_button_create(fieldScreen);
    lv_obj_set_size(awpBtn, btnW, btnH);
    lv_obj_set_pos(awpBtn, 20, 200);
    lv_obj_add_style(awpBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_t* awpLabel = lv_label_create(awpBtn);
    lv_label_set_text(awpLabel, "AWPleft");
    lv_obj_center(awpLabel);
    lv_obj_add_event_cb(awpBtn, [](lv_event_t* e){
        selectedAuton = AUTON_AWPLEFT;
    }, LV_EVENT_CLICKED, NULL);

    // Back button
    lv_obj_t* backBtn = lv_button_create(fieldScreen);
    lv_obj_set_size(backBtn, 120, 40);
    lv_obj_set_pos(backBtn, 220, 260);

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
    lv_obj_add_style(skillsBtn, &normalStyle, LV_PART_MAIN);
    lv_obj_add_style(push7Btn, &normalStyle, LV_PART_MAIN);
    lv_obj_add_style(m3l4Btn, &normalStyle, LV_PART_MAIN);
    lv_obj_add_style(awpBtn, &normalStyle, LV_PART_MAIN);

    if (selectedAuton == AUTON_SKILLS)
        lv_obj_add_style(skillsBtn, &selectedStyle, LV_PART_MAIN);

    if (selectedAuton == AUTON_PUSH7LEFT)
        lv_obj_add_style(push7Btn, &selectedStyle, LV_PART_MAIN);

    if (selectedAuton == AUTON_M3L4RIGHT)
        lv_obj_add_style(m3l4Btn, &selectedStyle, LV_PART_MAIN);

    if (selectedAuton == AUTON_AWPLEFT)
        lv_obj_add_style(awpBtn, &selectedStyle, LV_PART_MAIN);
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
// Update Loop
// ------------------------
void uiUpdate() {
    if (lv_screen_active() == fieldScreen) {
        updateAutonHighlight();
    }
}
