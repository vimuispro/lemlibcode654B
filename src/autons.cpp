#include "autons.h"
#include "config.h"   // gives access to motors, pistons, sensors

Autons::Autons(lemlib::Chassis* chassis)
    : chassis(chassis) {}


void Autons::collect(time){

    ML.set_value(true);
    front_motor.move(127);
    pros::delay(time);
    ML.set_value(false);
    front_motor.move(0);

}

void Autons::middle_score(time){
    front_motor.move(127);
    back_motor.move(127);
    pros::delay(time);
    front_motor.move(0);
    back_motor.move(0);

}

void Autons::load(){
    ML.set_value(true);
    front_motor.move(127);
    pros::delay(1100);
    front_motor.move(0);
}

void Autons::long_score(time){
    front_motor.move(127);
    back_motor.move(-127);
    pros::delay(time);
    front_motor.move(0);
    back_motor.move(0);

}

void Autons::wing(){
    
}


// Add more autons here
void Autons::skillsAuton() {

    front_motor.move(127);
    pros::delay(10000);
    front_motor.move(0);
}

void Autons::Push7Left() {

}
void Autons::M3L4Right() {
    
}
void Autons::AWPleft() {
    
}
