#include "main.h"
#include "subsystemHeaders/globals.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motors.hpp"

// define motors
pros::Motor conveyor(20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
pros::Motor intake(-21, pros::v5::MotorGears::rpm_200, pros::v5::MotorUnits::counts);
pros::Motor lady_brown(-4, pros::v5::MotorGears::rpm_200, pros::v5::MotorUnits::counts);
    
// left motor group
pros::MotorGroup left_motor_group({ -1, -2, -3 },
    pros::MotorGearset::blue);
// right motor group
pros::MotorGroup right_motor_group({ 8, 9, 10 }, 
    pros::MotorGearset::blue);

//drive train settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              12.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // new 2.75" omni wheels
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
                              );

//sensor for lady brown mechanism
pros::Rotation lady_brown_encoder(19);

//odometry sensors               
pros::Imu imu(5);
pros::Rotation horizontal_encoder(-18);
pros::Rotation vertical_encoder(17);

//tracking wheels
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, -3);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, .92);

// odometry settings
lemlib::OdomSensors odom_sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

//pneumatics
pros::ADIDigitalOut clamp('G');
pros::ADIDigitalOut doinker('H');

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//input curve for throttle (forward/backward) input during driver control
extern lemlib::ExpoDriveCurve throttle_curve(3, //set joystick dead zone to avoid drift
                                            10, //minimum output 
                                                1.019 //exponential curve gain
); 
//inout curve for steer (turning) input during driver control
extern lemlib::ExpoDriveCurve steer_curve(3, //set joystick dead zone to avoid drift
                                         10, //minimum output 
                                         1.05 //exponential curve gain
); 

// lateral PID controller
    lemlib::ControllerSettings lateral_controller(6, // proportional gain (kP)
                                                0.03, // integral gain (kI)
                                                .8, // derivative gain (kD)
                                                6, // anti windup
                                                1, // small error range, in inches
                                                100, // small error range timeout, in milliseconds
                                                3, // large error range, in inches
                                                500, // large error range timeout, in milliseconds
                                                0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              11.9, // derivative gain (kD)
                                                3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

//create chassis
lemlib::Chassis chassis(
                        drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        odom_sensors // odometry sensors
);

//color sensor
pros::Optical optical_sensor(15);