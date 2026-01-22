#include "lemlib/api.hpp"
#include "driver.h"
#include "config.h"
#include "autons.h"
extern Autons autons;

DriverControl::DriverControl(pros::Controller* controller, lemlib::Chassis* chassis)
    : controller(controller), chassis(chassis) {}

void DriverControl::update() {
  


    int rightX = controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int leftY = controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);


    chassis->arcade(leftY, rightX);
    //---------------------------Test----------------------------------------
    // Autonomous turn test on button press A
    if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        autons.RedLeft();
    }

    // Front motor control with R2 and R1 buttons
    if (controller->get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        front_motor.move(127);
    } else if (controller->get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        front_motor.move(-127);
    } else {
        front_motor.move(0);
    }

    if (controller->get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        back_motor.move(127);
    } else if (controller->get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        back_motor.move(-127);
    } else {
        back_motor.move(0);
    }

    static bool wingState = false;
    if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        wingState = !wingState; // flip the state 
        Wing.set_value(wingState);
    } 
    static bool mlState = false;
    if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        mlState = !mlState; // flip the state 
        ML.set_value(mlState);
    } 
    static bool mgState = false;
    if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        mgState = !mgState; // flip the state 
        MG.set_value(mgState);
    } 
    static bool mdState = false;
    if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        mdState = !mdState; // flip the state 
        MD.set_value(mdState);
    } 

    pros::delay(25);
 }
