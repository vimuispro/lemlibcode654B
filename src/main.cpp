#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-1, -2, 4},
                            pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors({-8, 9, 10}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

// Inertial Sensor on port 10
pros::Imu imu(12);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(-11);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(19);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, .4);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, -.5);


pros::Motor front_motor(18, pros::MotorGearset::blue);
pros::Motor back_motor(15, pros::MotorGearset::blue);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.425, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 410
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);


// lateral motion controller
lemlib::ControllerSettings linearController(13, // proportional gain (kP16
                                            1, // integral gain (kI)
                                            37, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(6, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             31, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
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
            // delay to save resources
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

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 100000);
}

/**
 * Runs in driver control
 */
void opcontrol() {
    while (true) {
        // Driver control arcade drive with corrected turn input
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);


        chassis.arcade(leftY, rightX);
        //---------------------------Test----------------------------------------
        // Autonomous turn test on button press A
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
                    // Reset pose to zero at start
            front_motor.move(127);
            chassis.moveToPose(1.0, 27.0, 9,5000);
            //intakes blocks
    
            pros::delay(1000);
            
            //goes toward goal
            
            chassis.turnToHeading(-127, 3000);
            lemlib::MoveToPointParams params;
            params.forwards = false;
            
            chassis.moveToPoint(10.56, 36.217, 5000, params);
            pros::delay(700);
            back_motor.move(-127);
            //outakes blocks
            
            pros::delay(1000);

            front_motor.move(0);
            back_motor.move(0);
                               //-----------------
            
            
            chassis.moveToPose(-28.717, 6.949, -127, 3000);
            //------------
            chassis.moveToPose(-31.706, -8.035, -145, 1000);
            //chassis.moveToPose(-24.533, 32.746, 5000);
            //--------------------------------------------------
            //chassis.moveTo(0.861, 25.156, 5000);
            //chassis.moveTo(13.56, 33.217, 5000);
            //chassis.moveTo(-28.717, 6.949, 5000);
            //chassis.moveTo(-31.706, -6.035, 5000);
            //chassis.moveTo(-24.901, 23.44, 5000);

            
        
        //-----------------------------------------------------------------------
        }

        // Front motor control with R2 and R1 buttons
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            front_motor.move(127);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            front_motor.move(-127);
        } else {
            front_motor.move(0);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            back_motor.move(127);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            back_motor.move(-127);
        } else {
            back_motor.move(0);
        }

        pros::delay(25);
    }
}


