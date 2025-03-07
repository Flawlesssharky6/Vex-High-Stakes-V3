#include "lemlib/asset.hpp"
#include "liblvgl/llemu.hpp"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "subsystemHeaders/drive.hpp"
#include "subsystemHeaders/globals.hpp"
#include "subsystemHeaders/autonomousHeaders.hpp"
#include "subsystemHeaders/conveyorMechanism.hpp"
#include "subsystemHeaders/ladyBrownMechanism.hpp"
#include <chrono>



void autonomusProgram(){
    //get alliance stake
    chassis.setPose(12, -13, -40);
    conveyor.move(127);
    intake.move(127);
    setLadyBrownMechanism(127);
    pros::delay(1000);
    setLadyBrownMechanism(0);
    //get 1st stake
    move(-50, 500);
    pros::Task ladyBrownTask(moveLadyBrownAsync);
    clamp.set_value(true);
    pros::delay(100);
    chassis.turnToHeading(90, 500);
    chassis.moveToPoint(48, -24, 1000);
    chassis.turnToHeading(170, 500);
    chassis.moveToPoint(48, -48, 500);
    chassis.turnToPoint(72, -60, 500);
    chassis.moveToPoint(72, -60, 1000);
    chassis.moveToPoint(48, -48, 500, {.forwards = false}, false);
    chassis.turnToHeading(270, 500);
    chassis.moveToPoint(24,-48,500);
    pros::delay(500);
    chassis.moveToPoint(8,-48, 500, {.maxSpeed = 50}, false);
    pros::delay(500);
    chassis.moveToPoint(36, -36, 1000, {.forwards = false}, false);
    chassis.moveToPoint(24, -60, 1000);
    chassis.moveToPoint(36,-36, 1000);
    chassis.turnToHeading(45, 500);
    chassis.moveToPoint(16, -56, 1500, {.forwards = false, .maxSpeed = 80}, false);
    conveyor.move(0);
    intake.move(0);
    clamp.set_value(false);
    //move to 2nd stake
    pros::delay(50);
    intake.move(127);
    conveyor.move(127);
    chassis.moveToPoint(24, -24, 1000, {.maxSpeed = 65}, false);
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(24,0,2000, {.forwards = false, .maxSpeed=65}, false);
    chassis.turnToHeading(180,1000);
    pros::delay(500);
    chassis.moveToPoint(24, 22, 4000, {.forwards = false, .maxSpeed = 30}, false);
    //clamp second stake
    clamp.set_value(true);
    pros::delay(500);
    chassis.turnToHeading(90, 500);
    chassis.moveToPoint(48, 24, 1000);
    chassis.turnToPoint(48, 48, 1000);
    chassis.moveToPoint(48, 48, 1000);
    
    chassis.turnToPoint(72, 62, 1000);
    chassis.moveToPoint(72, 62, 1000);
    
    chassis.moveToPoint(48, 48, 500, {.forwards = false}, false);
    chassis.turnToHeading(270, 500);
    chassis.moveToPoint(24,48,500);
    
    pros::delay(500);
    chassis.moveToPoint(12,48, 500, {.maxSpeed = 50}, false);
    chassis.moveToPoint(36, 36, 1000, {.forwards = false}, false);
    chassis.moveToPoint(24, 60, 1000);
    chassis.moveToPoint(36,36, 1000);
    chassis.turnToHeading(135, 500);
    chassis.moveToPoint(8, 64, 1500, {.forwards = false, .maxSpeed = 80}, false);
    clamp.set_value(false);
    
    //get 3rd stake
    chassis.moveToPoint(36, 36, 1000);
    chassis.turnToHeading(90, 500);
    chassis.moveToPoint(72, 48, 3000);
    conveyor.move(0);
    intake.move(0);
    chassis.turnToPoint(96 , 24, 500);
    chassis.moveToPoint(96, 24, 5000);
    intake.move(127);
    conveyor.move(127);
    pros::delay(500);
    intake.move(0);
    conveyor.move(0);
    chassis.turnToPoint(72, 48, 1000);
    chassis.moveToPoint(120, 0, 3000, {.forwards = false}, false);
    clamp.set_value(true);
}

void skills(){

    //put ring on alliance stake
    conveyor.move(127);
    intake.move(127);
    pros::delay(600);
    conveyor.move(0);
    intake.move(0);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(200);
    conveyor.move(0);
    intake.move(0);
    pros::delay(50);

    //get first stake
    move(50, 520);
    pros::delay(50);
    turn(520, -50);
    pros::delay(50);
    move(-40, 550);
    left_motor_group.move(-35);
    right_motor_group.move(-35);
    pros::delay(360);
    clamp.set_value(true);
    pros::delay(190);
    left_motor_group.move(0);
    right_motor_group.move(0);
    pros::delay(100);

    //get rings
    turn(570, 50);
    pros::delay(50);
    conveyor.move(127);
    intake.move(127);  
    move(50, 700);
    pros::delay(50);
    move(-50,100);
    pros::delay(200);
    turn(320, 50);
    move(50, 900);
    conveyor.move(-127);
    intake.move(-127);  
    pros::delay(200);
    conveyor.move(127);
    intake.move(127);
    move(50, 850);
    pros::delay(250);
    turn(960, 50);
    move(50, 700);
    pros::delay(50);

    //corner rings 
    turn(145, -50);
    pros::delay(50);
    move(50, 600);
    pros::delay(500);
    move(50, 600);
    pros::delay(1000);
    move(50, 1000); 
    pros::delay(1250); 
    move(50, 1000); 
    move(-50, 800);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(200);
    conveyor.move(127);
    intake.move(127);
    turn(500, -50);
    move(50, 1500);
    move(-50, 300);
    move(50,500);
    pros::delay(150);
    turn(820, -50);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(200);
    conveyor.move(127);
    intake.move(127);
    move(-50, 750);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(100);
    clamp.set_value(false);

    //begin move to second corner
    move(50, 375);
    conveyor.move(0);
    intake.move(0);
    turn(570, 50);
    move(50,2000);
    pros::delay(500);
    move(-70, 1300);
    conveyor.move(127);
    intake.move(127);
    turn(530, 50);
    move(50, 1200);
    move(-50, 660);
    pros::delay(50);
    turn(505, -50);
    conveyor.move(0);
    intake.move(0);
    move(-50, 1265);

    //clamp new goal and grab corner rings
    clamp.set_value(true);
    move(-50,35);
    turn(1100, 50);
    conveyor.move(127);
    intake.move(127);
    move(50, 300);
    pros::delay(500);
    move(50, 600);
    pros::delay(1000);
    move(50, 900); 
    conveyor.move(0);
    intake.move(0);
    pros::delay(250); 
    move(50, 300); 
    conveyor.move(127);
    intake.move(127);
    move(-50, 800);
    pros::delay(300);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(400);
    conveyor.move(127);
    intake.move(127);
    turn(500, -50);
    move(50, 1000);
    move(-50, 300);
    move(50,500);
    pros::delay(150);
    turn(820, -50);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(200);
    conveyor.move(127);
    intake.move(127);
    move(-50, 750);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(100);

    //put goal in corner and go towards middle
    clamp.set_value(false);
    conveyor.move(0);
    intake.move(0);
    move(50, 500);
    turn(300,-50);
    conveyor.move(127);
    intake.move(127);
    clamp.set_value(true);
    move(-50, 1000);
    move(80, 1550);

    //plow goals into corner
    turn(780, -50);
    move(-80, 1000);
    turn(100,50);
    move(-80,3000);
    move(50, 800);
    turn(500, -50);
    move(-50,700);
    move(50,900);
    turn(360, -50);
    move(-100,3700);
    move(100,800);


}



//autonomous skills
/*
void skills(){
    chassis.setPose(0, 0, 0);

    //put ring on alliance stake
    conveyor.move(127);
    intake.move(127);
    pros::delay(400);
    conveyor.move(0);
    intake.move(0);

    //get first stake
    move(50, 550);
    pros::delay(50);
    chassis.turnToHeading(-90, 750, {.maxSpeed = 80}, false);
    pros::delay(500);
    move(-40, 550);
    left_motor_group.move(-35);
    right_motor_group.move(-35);
    pros::delay(450);
    clamp.set_value(true);
    pros::delay(50);
    left_motor_group.move(0);
    right_motor_group.move(0);
    pros::delay(100);

    //get rings 
    chassis.turnToHeading(0, 750, {.maxSpeed = 80}, false);
    pros::delay(50);
    conveyor.move(127);
    intake.move(127);   
    move(50, 650);
    pros::delay(100);
    chassis.turnToHeading(-119, 1000, {.maxSpeed = 80}, false);
    pros::delay(100);
    move(50, 1800);
    pros::delay(100);
    chassis.turnToHeading(-10, 750, {.maxSpeed = 80}, false);
    //pros::delay(100);
    //move(50, 600);
    //chassis.turnToHeading(180, 400);
    //clamp.set_value(false);
}
*/

//Head to Head autonomous
void redRightCorner(){
    move(-30, 3000);
    clamp.set_value(true);
    pros::delay(500);
    conveyor.move(127);
    intake.move(127);
    turn(850,-50);
    move(30,600);
}
void redLeftCorner(){
    chassis.setPose(12, 14, 215);
    pros::Task conveyorTask([]{ auton_conveyor("red"); });
    setLadyBrownMechanism(127);
    pros::delay(1000);
    setLadyBrownMechanism(0);
    pros::Task ladyBrownTask(moveLadyBrownAsync);
    //get 1st stake
    chassis.moveToPoint(48, 24, 2000, {.forwards = false, .maxSpeed =80}, false);
    clamp.set_value(true);
    chassis.turnToHeading(60, 500);
    chassis.moveToPoint(65, 48, 2000, {.maxSpeed = 50,  .minSpeed =30, .earlyExitRange = 5}, false);
    chassis.moveToPoint(60, 65, 2000, {.maxSpeed = 50}, false);
    chassis.turnToHeading(235, 500);
    chassis.moveToPoint(36, 24, 2000, {.maxSpeed = 90, .minSpeed =50,  .earlyExitRange =5}, false);
    intake_piston.set_value(true);
    chassis.moveToPoint(24, 0, 1000);
    chassis.turnToHeading(0, 500);
    intake_piston.set_value(false);
    chassis.moveToPoint(0, 60, 4000);

}
void blueLeftCorner(){
    move(-30, 3000);
    clamp.set_value(true);
    pros::delay(2000);
    turn(850,50);
    conveyor.move(127);
    intake.move(127);
    move(30,600);
}
void blueRightCorner(){
    //place ring on alliance stake
    move(50, 570);
    pros::delay(200);
    turn(550, 50);
    clamp.set_value(true);
    pros::delay(50);
    move(-50, 280);
    pros::delay(100);
    conveyor.move(127);
    intake.move(127);
    pros::delay(1500);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(200);
    conveyor.move(0);
    intake.move(0);
    clamp.set_value(false);

    //drive to next stake and grab first ring
    move(50,200);
    pros::delay(100);
    turn(780, -50);
    move(-50,800);
    turn(59,-50);
    move(-50,500);
    clamp.set_value(true);
    pros::delay(150);
    turn(760,-50);
    conveyor.move(127);
    intake.move(127);
    move(50, 800);
    pros::delay(100);

    //turn towards center pile and drive to ladder
    turn(510, -50);
    pros::delay(500);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(200);
    conveyor.move(127);
    intake.move(127);
    move(50, 750);
    pros::delay(150);
    move(-50,600);
    turn(450,-50);
    move(50,600);
    move(50,550);
    conveyor.move(0);
    intake.move(0);
}

void fractalILOVEYOU(){
    move(50,  300);
}