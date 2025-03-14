#include "main.h"
#include "pros/rtos.hpp"
#include "subsystemHeaders/globals.hpp"

//helper functions
void set_conveyor_mechanism(int power){
    conveyor.move(power);
    intake.move(power);
}

void conveyor_color_sort(std::string color){
    int red_threshold = 50;
    int blue_threshold = 140;
    int proximity_threshold = 240;
    
    int motorPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
    - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));

    if(color == "blue"){
        if(optical_sensor.get_hue() < red_threshold && optical_sensor.get_proximity() > proximity_threshold && motorPower > 0){
            pros::delay(50);
            set_conveyor_mechanism(0);
            pros::delay(50);
        }else{
            set_conveyor_mechanism(motorPower);
            pros::delay(10);
        }
    }else if(color == "red"){
        if(optical_sensor.get_hue() > blue_threshold && optical_sensor.get_proximity() > proximity_threshold && motorPower > 0){    
            pros::delay(50);
            set_conveyor_mechanism(0);
            pros::delay(50);
        }else{
            set_conveyor_mechanism(motorPower);
            pros::delay(10);
        }
}
}

void auton_conveyor(std::string teamColor){
    std::string color = teamColor;
    int red_threshold = 50;
    int blue_threshold = 140;
    int proximity_threshold = 240;
    int motorPower = 127;
    while (true){
        if(color == "blue"){
            if(optical_sensor.get_hue() < red_threshold && optical_sensor.get_proximity() > proximity_threshold && motorPower > 0){
                
                set_conveyor_mechanism(-127);
                pros::delay(500);
                /*
                if(optical_sensor.get_hue() > red_threshold && optical_sensor.get_proximity() > proximity_threshold){
                    set_conveyor_mechanism(127);
                }
                    */
            }else{
                set_conveyor_mechanism(motorPower);
                pros::delay(10);
            }
        }else if(color == "red"){
            if(optical_sensor.get_hue() > blue_threshold && optical_sensor.get_proximity() > proximity_threshold && motorPower > 0){    
                
                set_conveyor_mechanism(-127);
                pros::delay(500);
                /*
                if(optical_sensor.get_hue() > blue_threshold && optical_sensor.get_proximity() > proximity_threshold){
                    set_conveyor_mechanism(127);
                }
                */
            }else{
                set_conveyor_mechanism(motorPower);
                pros::delay(10);
            }
        }
    }

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

bool set_intake(bool intakePosition){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
        if (intakePosition == true){
            intake_piston.set_value(true);  // Activate solenoid
            intakePosition = false;
        }else{
            intake_piston.set_value(false);  // Activate solenoid
            intakePosition = true;
        }
    }
    pros::delay(20);
    return(intakePosition);
}

std::string change_color(std::string teamColor){
    if(partner_controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        teamColor = "red";
    }else if(partner_controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        teamColor = "blue";
    }
    pros::delay(20);
}

