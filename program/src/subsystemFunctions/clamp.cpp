#include "main.h"
#include "subsystemHeaders/globals.hpp"

//driver control functions
bool set_clamp(bool clampPosition){
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        if (clampPosition == true){
            clamp.set_value(true);  // Activate solenoid
            clampPosition = false;
        }else{
            clamp.set_value(false);  // Activate solenoid
            clampPosition = true;
        }
    }
    pros::delay(20);
    return(clampPosition);
}

bool open_clamp(bool clampPosition){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        clamp.set_value(false);
        clampPosition = false;
    }
    pros::delay(20);
    return clampPosition;
}