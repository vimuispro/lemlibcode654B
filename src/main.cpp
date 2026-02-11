#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "config.h"
#include "driver.h"
#include "autons.h"
#include "ui.h"
DriverControl driver(&controller, &chassis);
Autons autons(&chassis);



/*
So the coordinate system is:
x = 0 → 479
y = 0 → 239
Top‑left corner = (0, 0)
Bottom‑right corner = (479, 239)
*/


void initialize() {
    pros::lcd::initialize();   // optional, for PROS text
    chassis.calibrate(); // calibrate sensors    
    uiInit();                  // ⭐ build your LVGL UI


 
            
 }


 

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy


void autonomous() {

    switch (selectedAuton) {

        case AUTON_SKILLS:
            autons.skillsAuton();
            break;

        case AUTON_PUSH7LEFT:
            autons.Push7Left();
            break;

        case AUTON_M3L4RIGHT:
            autons.M3L4Right();
            break;

        case AUTON_AWPLEFT:
            autons.AWPleft();
            break;

        default:
            autons.Push7Left(); // fallback
            break;
    }
}


void opcontrol() {
    while (true) {
        driver.update(); 
        pros::delay(15);
}
}

