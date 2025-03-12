#include "subsystemHeaders/ladyBrownMechanism.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "subsystemHeaders/globals.hpp"
#include <cstdlib>

//helper functions
void setLadyBrownMechanism(int power){
    lady_brown.move(power);
}

//driver functions
void setLadyBrownMotor(){
    int motorPower = 0;
    // Check if the main controller is controlling the mechanism
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) || controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
        motorPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)
                            - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
    }
    // If the main controller is not controlling the mechanism, check the secondary controller
    else{
        motorPower = partner_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    }
    setLadyBrownMechanism(motorPower);
    pros::delay(20);
}
// Macro functions
void prepareLadyBrown(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) || partner_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        while(lady_brown_encoder.get_position() < 1750){
            setLadyBrownMechanism(127);
            while (lady_brown_encoder.get_position() < 200 && !controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
                pros::delay(20);
            }
        }
        setLadyBrownMechanism(0);
    } 
}



void moveLadyBrownAsync() {
    lady_brown.move(-127);
    pros::delay(1500); // Adjust timing as needed
    lady_brown.move(0); // Stop movement
}

void moveLadyBrownAsync2() {
    lady_brown.move(127);
    pros::delay(2000); // Adjust timing as needed
    lady_brown.move(0); // Stop movement
}

void secondary_lady_brown(){
    while (true){
        // Check if the main controller is not controlling the mechanism
        if(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
            // Secondary controller can control the mechanism
            int secondaryPower = partner_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            setLadyBrownMechanism(secondaryPower);
        }
        pros::delay(20); // Add a small delay to prevent hogging the CPU
    }
}