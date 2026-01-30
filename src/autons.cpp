#include "autons.h"
#include "config.h"   // gives access to motors, pistons, sensors

Autons::Autons(lemlib::Chassis* chassis)
    : chassis(chassis) {}

// Example auton
void Autons::testAuton() {
   
}

// Add more autons here
void Autons::skillsAuton() {
    // your skills routine
}

void Autons::RedRight() {
    // left side routine
}

void Autons::RedLeft() {
    chassis->setPose(-47.4, 17.6, 79.5); // starting pose

    front_motor.move(127); // start intake

    chassis->moveToPoint(-21, 21, 5000,{.maxSpeed=97},true);// goes infront of middle goal
    chassis->waitUntil(10);
    ML.set_value(true);
    chassis->waitUntilDone();
    chassis->turnToHeading(315, 3000,{},false);// turns backwards
    ML.set_value(false);
    pros::delay(200); 
    chassis->turnToHeading(315, 3000,{},false);// trns backwards

    MG.set_value(false);
    lemlib::MoveToPointParams params;
    params.forwards = false;
    chassis->moveToPoint(-9.0, 9.0, 5000, params); // moves to goal, backwards
    pros::delay(1000);               //let robot settle
    back_motor.move(127);  // outake blocks
    pros::delay(4000); 
    back_motor.move(0);  // outake blocks
    pros::delay(1000); 
    back_motor.move(127);
    chassis->setPose(-9.0,9.0,chassis->getPose().theta);   // scores blocks
    front_motor.brake(); //stop front motor
    back_motor.brake();    // stop back motor
    ML.set_value(true);
    chassis->moveToPoint(-40.427, 47.244, 5000); // goes infront of match loader

    chassis->turnToPoint(-67.8, 46.5, 3000); //turns to face match loader

    chassis->moveToPoint(-60.75, 46.5, 5000); // goes to match loader

    chassis->moveToPoint(-30.5, 47.236, 5000, params); // should go backward into long goal
    pros::delay(700); // let robot settle
    front_motor.move(127); // score blocks
    pros::delay(2000); // let blocks score
    front_motor.move(0); // stop front motor

}
