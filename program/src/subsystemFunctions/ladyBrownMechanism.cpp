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
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        if(lady_brown_encoder.get_position() < 1250){
            setLadyBrownMechanism(127);
            while (lady_brown_encoder.get_position() < 200 && !controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
                pros::delay(20);
            }
        }
        setLadyBrownMechanism(0);
    } 
}
/*
void moveToPositionAsync(void* param) {
    // Extract the target position from the parameter
    int targetPosition = *static_cast<int*>(param);

    // Get the current position of the encoder
    int currentPosition = lady_brown_encoder.get_position();

    // Determine direction: positive or negative
    int direction = (targetPosition > currentPosition) ? 1 : -1;

    // Set the motor to move towards the target position
    setLadyBrownMechanism(127 * direction);

    // Keep moving until the target position is reached
    while ((direction == 1 && lady_brown_encoder.get_position() < targetPosition) ||
           (direction == -1 && lady_brown_encoder.get_position() > targetPosition)) {
        pros::delay(20); // Delay to avoid hogging the CPU
    }

    // Stop the motor once the position is reached
    setLadyBrownMechanism(0);
}

void prepareLadyBrown() {
    // Static variables to keep track of the task and target position
    static pros::Task* prepareTask = nullptr;
    static int targetPosition = 1800; // Desired position for lady brown

    // Check if the button was just pressed
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        // If there's an existing task, remove and delete it
        if (prepareTask != nullptr) {
            prepareTask->remove();
            delete prepareTask;
        }

        // Create a new task to move to the desired position
        prepareTask = new pros::Task(moveToPositionAsync, &targetPosition, "PrepareLadyBrownTask");
    }
}  
*/