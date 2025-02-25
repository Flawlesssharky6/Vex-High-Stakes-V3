#include "lemlib/asset.hpp"
#include "liblvgl/llemu.hpp"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "subsystemHeaders/drive.hpp"
#include "subsystemHeaders/globals.hpp"
#include "subsystemHeaders/autonomousHeaders.hpp"
#include "subsystemHeaders/conveyorMechanism.hpp"

ASSET(testing1_txt);

void autonomusProgram(){
    // set position to x:0, y:0, heading:0
    //chassis.setPose(0, 0, -1.25);
    //pros::lcd::set_text(1, "done");
    // turn to face heading 90 with a very long timeout
    //chassis.moveToPose(0, 48, 0, 1000000000);
    //chassis.moveToPoint(0, 30, 100000);
    //chassis.turnToHeading(90, 2000);
    //chassis.moveToPoint(24, 48, 10000);
    //chassis.moveToPoint(0, 48, 10000);
    //chassis.moveToPoint(0, 0, 10000);
    chassis.turnToHeading(90, 100000);
    //translate(48, 80);
    //turn(1200, -40);
    //chassis.follow(testing1_txt, 15, 2000);
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

    //place ring on alliance stake
    move(50, 570);
    pros::delay(200);
    turn(550, -50);
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
    turn(780, 50);
    move(-50,800);
    turn(59,50);
    move(-50,500);
    clamp.set_value(true);
    pros::delay(150);
    turn(760,50);
    conveyor.move(127);
    intake.move(127);
    move(50, 800);
    pros::delay(100);

    //turn towards center pile and drive to ladder
    turn(510, 50);
    pros::delay(500);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(200);
    conveyor.move(127);
    intake.move(127);
    move(50, 750);
    pros::delay(150);
    move(-50,600);
    turn(450,50);
    move(50,600);
    move(50,550);
    conveyor.move(0);
    intake.move(0);

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