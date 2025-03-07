#include "main.h"

//driver control
bool setDoinker(bool doinkerPiston){
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (doinkerPiston == true){
            doinker.set_value(true);  // Activate solenoid
            doinkerPiston = false;
        }else{
            doinker.set_value(false);  // Activate solenoid
            doinkerPiston = true;
        }
    }
    pros::delay(20);
    return(doinkerPiston);
}

bool secondary_setDoinker(bool doinkerPiston){
    if (partner_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (doinkerPiston == true){
            doinker.set_value(true);  // Activate solenoid
            doinkerPiston = false;
        }else{
            doinker.set_value(false);  // Activate solenoid
            doinkerPiston = true;
        }
    }
    pros::delay(20);
    return(doinkerPiston);
}