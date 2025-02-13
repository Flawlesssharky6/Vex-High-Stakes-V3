#include "main.h"

//helper functions
void set_conveyor_mechanism(int power){
    conveyor.move(power);
    intake.move(power);
}

//driver control functions
void set_conveyor_motor(){
    //bottom trigger intakes, top trigger outtakes
    //get_digital returns boolean (0 or 1)
    //bottom triggers - top triggers
    int motorPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
    - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));

    set_conveyor_mechanism(motorPower);
}