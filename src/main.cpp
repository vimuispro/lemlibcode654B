#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "config.h"
#include "driver.h"
#include "autons.h"
DriverControl driver(&controller, &chassis);
Autons autons(&chassis);

void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // the default rate is 50. however, if you need to change the rate, you
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
            pros::lcd::print(3, "Rotation Sensor horizontal: %i", horizontalEnc.get_position());
            pros::lcd::print(4, "Rotation Sensor vertical: %i", verticalEnc.get_position()); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
 
            pros::delay(50);
        }
    });
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
    //autons.RedLeft();
}

void opcontrol() {
    while (true) {
        driver.update(); 
        pros::delay(15);
}
}

