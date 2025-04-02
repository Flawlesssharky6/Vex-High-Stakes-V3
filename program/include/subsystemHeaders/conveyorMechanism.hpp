#pragma once

#include <string>

//helper function 
void set_conveyor_mechansim(int power);

//driver control functions
void set_conveyor_motor();

void conveyor_color_sort(std::string teamColor);

bool set_intake(bool intakePosition);

void auton_conveyor(std::string color);

void change_color(std::string& teamColor);