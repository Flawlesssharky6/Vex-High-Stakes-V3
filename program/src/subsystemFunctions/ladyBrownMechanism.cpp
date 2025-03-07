#include "subsystemHeaders/ladyBrownMechanism.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "subsystemHeaders/globals.hpp"
#include <cstdlib>

//helper functions
void setLadyBrownMechanism(int power){
    lady_brown.move(power);
}

//driver functions
void setLadyBrownMotor(){
    //up button swings up, down button swings down
    //get_digital returns boolean (0 or 1)
    //up button - bottom button
    int motorPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)
    - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
    /*
    if(lady_brown_encoder.get_position() > 9400 && motorPower > 0){
        motorPower = 0;
    }
    */
    setLadyBrownMechanism(motorPower);
    pros::delay(20);
}
// Macro functions
void prepareLadyBrown(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) || partner_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        pros::lcd::set_text(4, "RIGHT button pressed");
        // Move the Lady Brown mechanism to a certain position
        int targetPosition = 40000; // Set your target position here
        pros::lcd::set_text(9, "Target position: " + std::to_string(targetPosition));
        if(lady_brown_encoder.get_position() < targetPosition){
            setLadyBrownMechanism(127); // Move up
            while (lady_brown_encoder.get_position() < targetPosition){
                pros::lcd::set_text(10, "Moving Lady Brown up: " + std::to_string(lady_brown_encoder.get_position()));
                pros::delay(20);
            }
        } else if(lady_brown_encoder.get_position() > targetPosition){
            setLadyBrownMechanism(-127); // Move down
            while (lady_brown_encoder.get_position() > targetPosition){
                pros::lcd::set_text(10, "Moving Lady Brown down: " + std::to_string(lady_brown_encoder.get_position()));
                pros::delay(20);
            }
        }
        setLadyBrownMechanism(0); // Stop movement
        pros::lcd::set_text(10, "Lady Brown stopped at target position");
    } 
}

void moveLadyBrownAsync() {
    lady_brown.move(-127);
    pros::delay(2000); // Adjust timing as needed
    lady_brown.move(0); // Stop movement
}

void secondary_lady_brown(){
    while(true){
        // Check if the main controller is controlling the mechanism
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) || controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
            // Main controller has priority
            int motorPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)
                                    - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
            setLadyBrownMechanism(motorPower);
        } else {
            // Secondary controller can control the mechanism
            int secondaryPower = partner_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            setLadyBrownMechanism(secondaryPower);
        }
        pros::delay(20); // Add a small delay to prevent hogging the CPU
    }
}