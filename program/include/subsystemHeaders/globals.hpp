#pragma once
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

//declare motors
extern pros::Motor intake;
extern pros::Motor lady_brown;
extern pros::Motor conveyor;

// left motor group
extern pros::MotorGroup left_motor_group;
// right motor group
extern pros::MotorGroup right_motor_group;

//sensor for lady brown mechanism
extern pros::Rotation lady_brown_encoder;

//drivetrain settings
extern lemlib::Drivetrain drivetrain;

//odometry sensors
extern pros::Imu imu;
extern pros::Rotation horizontal_encoder;
extern pros::Rotation vertical_encoder;

//tracking wheels
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;

//odometry settings
extern lemlib::OdomSensors odom_sensors;

//pneumatics
extern pros::ADIDigitalOut clamp;
extern pros::ADIDigitalOut doinker;

//controller
extern pros::Controller controller;
//input curve for throttle (forward/backward) input during driver control
extern lemlib::ExpoDriveCurve throttle_curve; 
//inout curve for steer (turning) input during driver control
extern lemlib::ExpoDriveCurve steer_curve;

// lateral PID controller
extern lemlib::ControllerSettings lateral_controller;

// angular PID controller
extern lemlib::ControllerSettings angular_controller;

//create chassis
extern lemlib::Chassis chassis;

//Optical sensor
extern pros::Optical optical_sensor;