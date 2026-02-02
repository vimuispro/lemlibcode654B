#include "config.h"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-1, -2, 4}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({-8, 9, 10}, pros::MotorGearset::blue);

// sensors
pros::Imu imu(12);
pros::Rotation horizontalEnc(-11);
pros::Rotation verticalEnc(19);

// tracking wheels
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, .4);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, -.5);

// extra motors
pros::Motor front_motor(18, pros::MotorGearset::blue);
pros::Motor back_motor(15, pros::MotorGearset::blue);

// pistons
pros::adi::DigitalOut Wing('A');
pros::adi::DigitalOut ML('B');
pros::adi::DigitalOut MG('C');
pros::adi::DigitalOut MD('D');
bool driverControlEnabled = true;

// drivetrain + chassis
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 11.425,
                              lemlib::Omniwheel::NEW_325, 450, 2);

lemlib::ControllerSettings linearController(
    10, 
    1, 
    50, 
    3, 
    1, 
    100, 
    3, 
    500, 
    20
);
lemlib::ControllerSettings angularController(
    6, 
    0, 
    49, 
    3, 
    1, 
    100, 
    3, 
    500, 
    0
);

lemlib::OdomSensors sensors(
    &vertical, 
    nullptr, 
    &horizontal, 
    nullptr, 
    &imu
);

lemlib::ExpoDriveCurve throttleCurve(
    3, 
    10, 
    1.019
);
lemlib::ExpoDriveCurve steerCurve(
    3, 
    10, 
    1.019
);

lemlib::Chassis chassis(
    drivetrain, 
    linearController, 
    angularController,          
    sensors, 
    &throttleCurve, 
    &steerCurve
);
