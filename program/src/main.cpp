#include "main.h"
#include "fmt/format.h"
#include "lemlib/api.hpp"  IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/motors.h"
#include "subsystemHeaders/autonomousHeaders.hpp"
#include "subsystemHeaders/drive.hpp"
#include "subsystemHeaders/globals.hpp"
#include <string>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::lcd::initialize(); // initialize brain screen
  pros::lcd::set_text(1, "32092D");
  chassis.calibrate(); // calibrate sensors
  lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lady_brown_encoder.reset_position();
  imu.reset();
  pros::delay(2000);
      // thread to for brain screen and position logging
      pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  left_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  blueLeftCorner();
  //skills();
  //autonomusProgram();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  chassis.setPose(0, 0, 0);
  left_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  bool doinkerPiston = false;
  bool clampPosition = true;
  auto timeFlag=pros::millis();
  while (true) {
    /*
        lemlib::Pose pose = chassis.getPose();
    std::string positionText = 
            "X: " + std::to_string(pose.x) + 
            ", Y: " + std::to_string(pose.y) + 
            ", Theta: " + std::to_string(pose.theta);
    pros::lcd::set_text(0, positionText);
    */

    set_drive();
    set_conveyor_motor();
    clampPosition = set_clamp(clampPosition);
    clampPosition = open_clamp(clampPosition);
    pros::lcd::set_text(4, "done");
    if(pros::millis()-timeFlag>=1000)
    {
     controller.print(1, 0, "clamp: %s", clampPosition ? "closed" : "open");
     timeFlag=pros::millis();
    }
    pros::Task::delay_until(&timeFlag, 10);
    setLadyBrownMotor();
    prepareLadyBrown(); // Check and start the prepareLadyBrownTask if the button is pressed
    doinkerPiston = setDoinker(doinkerPiston);
    pros::delay(20); // Add a small delay to prevent overwhelming the CPU
  } 
}