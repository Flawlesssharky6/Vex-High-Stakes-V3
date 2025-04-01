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
  lady_brown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lady_brown_encoder.reset_position();
  chassis.calibrate(); // calibrate sensors
  //pros::delay(2000);
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
    optical_sensor.set_led_pwm(100);
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
  //blueLeftCorner();
  //skills();
  //redLeftCorner();
  //autonomusProgram();
  //redRightCorner();
  blueRightCorner();
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
  left_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  right_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  optical_sensor.set_led_pwm(100);
  bool doinkerPiston = false;
  bool clampPosition = true;
  bool intakePosition = true;
  auto timeFlag = pros::millis();
  std::string teamColor = "blue";
  // Capture teamColor by reference in the lambda function
  pros::Task changeTeamColor([&teamColor]{ change_color(teamColor); });

  while (true) {
    pros::lcd::set_text(4, std::to_string(lady_brown_encoder.get_position()));
    set_drive();
    conveyor_color_sort(teamColor);
    //set_conveyor_motor();
    clampPosition = set_clamp(clampPosition);
    //clampPosition = open_clamp(clampPosition);
    //intakePosition = set_intake(intakePosition);
    if (pros::millis() - timeFlag >= 1000) {
      controller.print(1, 0, "clamp: %s", clampPosition ? "Open" : "Closed");
      timeFlag = pros::millis();
    }
    pros::Task::delay_until(&timeFlag, 10);
    setLadyBrownMotor();

    prepareLadyBrown();
    doinkerPiston = setDoinker(doinkerPiston);
    //teamColor = change_color(teamColor);
    pros::delay(20); // Add a small delay to prevent overwhelming the CPU
  }
}