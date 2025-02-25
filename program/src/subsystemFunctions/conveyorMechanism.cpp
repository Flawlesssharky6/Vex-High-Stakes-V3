#include "main.h"
#include "pros/rtos.hpp"

//helper functions
void set_conveyor_mechanism(int power){
    conveyor.move(power);
    intake.move(power);
}

void conveyor_color_sort(std::string color){
    int red_threshold = 40;
    int blue_threshold = 150;
    int proximity_threshold = 240;

    int motorPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
    - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));

    if(color == "blue"){
        if(optical_sensor.get_hue() < red_threshold && optical_sensor.get_proximity() > proximity_threshold && motorPower > 0){
            pros::delay(50);
            set_conveyor_mechanism(0);
            pros::delay(800);
        }else{
            set_conveyor_mechanism(motorPower);
            pros::delay(50);
        }
    }else if(color == "red"){
        if(optical_sensor.get_hue() > blue_threshold && optical_sensor.get_proximity() > proximity_threshold && motorPower > 0){    
            pros::delay(50);
            set_conveyor_mechanism(0);
            pros::delay(800);
        }else{
            set_conveyor_mechanism(motorPower);
            pros::delay(50);
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

