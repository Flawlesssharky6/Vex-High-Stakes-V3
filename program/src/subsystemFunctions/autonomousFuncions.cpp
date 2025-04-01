#include "lemlib/asset.hpp"
#include "liblvgl/llemu.hpp"
#include "liblvgl/misc/lv_async.h"
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "subsystemHeaders/doinker.hpp"
#include "subsystemHeaders/drive.hpp"
#include "subsystemHeaders/globals.hpp"
#include "subsystemHeaders/autonomousHeaders.hpp"
#include "subsystemHeaders/conveyorMechanism.hpp"
#include "subsystemHeaders/ladyBrownMechanism.hpp"
#include <chrono>
#include <random>



void autonomusProgram(){
    //get alliance stake
    chassis.setPose(12, -13, -40);
    setLadyBrownMechanism(127);
    pros::delay(900);
    setLadyBrownMechanism(0);
    //get 1st stake
    move(-50, 500);
    pros::Task ladyBrownTask(moveLadyBrownAsync);
    clamp.set_value(true);
    pros::delay(100);
    chassis.turnToHeading(90, 600);
    conveyor.move(-127);
    intake.move(-127);
    pros::delay(250);
    conveyor.move(127);
    intake.move(127);
    chassis.moveToPoint(48, -24, 900);
    chassis.turnToHeading(170, 600);
    chassis.moveToPoint(48, -48,900);
    chassis.turnToPoint(72, -60, 600);
    chassis.moveToPoint(72, -60, 900);
    
    chassis.moveToPoint(48, -48, 900, {.forwards = false}, false);
    //might have to change thesew coordinates
    chassis.turnToHeading(270, 700);
    conveyor.move(127);
    intake.move(127);
    chassis.moveToPoint(24,-48,1000, {.minSpeed = 80});
    pros::delay(500);
    chassis.moveToPoint(8,-48, 1000, {.maxSpeed = 50}, false);
    pros::delay(500);
    
    chassis.moveToPoint(26, -46, 1000, {.forwards = false}, false);
    chassis.moveToPoint(24, -63, 1000);
    chassis.moveToPoint(30,-42, 1500, {.forwards = false}, false);
    chassis.turnToHeading(45, 600);
    conveyor.move(-50);
    intake.move(-50);
    chassis.moveToPoint(12, -58, 2000, {.forwards = false, .maxSpeed = 80}, false);
    conveyor.move(0);
    intake.move(0);

    clamp.set_value(false);
    
    //move to 2nd stake
    chassis.moveToPoint(24, -24, 1000);
    chassis.turnToHeading(180, 1000);
    chassis.moveToPose(24, 24, 180, 2800, {.forwards = false}, false);
    //clamp second stake
    conveyor.move(-127);
    intake.move(-127);
    clamp.set_value(true);
    
    
    chassis.turnToHeading(90, 500);
    chassis.moveToPoint(48, 24, 1000);
    conveyor.move(127);
    intake.move(127);
    chassis.turnToPoint(48, 48, 1000);
    chassis.moveToPoint(48, 48, 1000);
    
    chassis.turnToPoint(72, 60, 1000);
    chassis.moveToPoint(72, 60, 1000);
    
    chassis.moveToPoint(48, 48, 1000, {.forwards = false}, false);
    chassis.turnToHeading(270, 500);
    chassis.moveToPoint(24,48,1000);
    
    pros::delay(500);
    chassis.moveToPoint(6,48, 750, {.maxSpeed = 60}, false);
    chassis.moveToPoint(36, 36, 1000, {.forwards = false}, false);
    chassis.moveToPoint(24, 60, 1000);
    chassis.moveToPoint(24,48, 1000);
    chassis.turnToHeading(135, 500);
    conveyor.move(-50);
    intake.move(-50);
    chassis.moveToPoint(8, 64, 1500, {.forwards = false}, false);
    clamp.set_value(false);
    
    chassis.setPose(13, 59, chassis.getPose().theta);
    //get 3rd stake
    
    chassis.moveToPoint(36, 48, 1500);
    conveyor.move(0);
    intake.move(0);
    chassis.turnToHeading(90, 1000);
    pros::delay(50);
    chassis.moveToPoint(72, 48, 1500);
    
    intake.move(127);
    conveyor.move(127);
    chassis.turnToPoint( 108, 36, 500);
    
    chassis.moveToPoint(108, 36, 1000);
    
    //chassis.moveToPoint(112, 12, 1000);
    intake.move(0);
    conveyor.move(0);
    //chassis.turnToPoint(112, 12, 500, {.forwards = false}, false);
    //chassis.moveToPoint(112,12, 1000, {.forwards = false, .maxSpeed=80}, false);
    chassis.turnToPoint(120,0, 500, {.forwards = false}, false);
    chassis.moveToPoint(120, 0, 3500, {.forwards = false, .maxSpeed=85}, false);
    clamp.set_value(true);
    pros::delay(100);
    intake.move(-127);
    conveyor.move(-127);
    chassis.turnToPoint(96, -24, 500);
    pros::Task conveyorTask([]{ auton_conveyor("red"); });
    chassis.moveToPoint(96, -24, 1000);
    chassis.turnToPoint(96, -48, 500);
    chassis.moveToPoint(96, -48, 1000);
    chassis.turnToPoint(120, -48, 500);
    chassis.moveToPoint(135, -48, 1500);
    chassis.moveToPoint(96, -48, 1000, {.forwards = false}, false); 
    chassis.turnToPoint(120, -60, 500);
    chassis.moveToPoint(120, -60, 1000);
    chassis.moveToPoint(96, -48, 1000, {.forwards = false}, false);
    chassis.turnToPoint(144,-72, 500, {.forwards = false}, false);
    intake.move(-127);
    conveyor.move(-127);
    conveyorTask.remove();
    clamp.set_value(false);
    chassis.moveToPoint(92,-44, 500);
    pros::delay(500);
    clamp.set_value(true);
    chassis.moveToPoint(150, -78, 1500, {.forwards = false,}, false);  
    chassis.moveToPoint(96, -48, 1000);
    intake.move(0);
    conveyor.move(0);
    //plow 4th stake
    intake_piston.set_value(true);
    chassis.turnToPoint(130, 24, 500);
    chassis.moveToPoint(130, 24, 1500, {.minSpeed=80, .earlyExitRange = 10}, false);
    chassis.turnToPoint(144, 72, 500);
    chassis.moveToPoint(144, 72, 2000);
    chassis.moveToPoint(124,48 , 1000, {.forwards = false, .earlyExitRange = 3}, false);
    //hang
    pros::Task ladyBrownUp([]{ moveLadyBrownAsync2(); });
    chassis.turnToHeading(50, 1000);
    //ladyBrownUp.remove();
    chassis.moveToPoint(80, 0, 7000, {.forwards = false, .maxSpeed = 64}, false);
    left_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    right_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    left_motor_group.move(30);
    right_motor_group.move(30);
    pros::delay(500);
    left_motor_group.move(0);
    right_motor_group.move(0);
    
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
    chassis.setPose(22,-61, 65);
    doinker.set_value(true);
    intake.move(127);
    conveyor.move(127);
    chassis.moveToPoint(53, -48, 1000);
    pros::delay(800);
    intake.move(0);
    conveyor.move(0);
    doinker.set_value(false);
    chassis.moveToPoint(45, -54, 1000, {.forwards = false}, false);
    doinker.set_value(true);
    pros::delay(100);
    chassis.moveToPose(48, -24, 180, 3000, {.forwards = false}, false);
    clamp.set_value(true);
    doinker.set_value(false);
    pros::delay(550);
    intake.move(127);
    conveyor.move(127);
    pros::delay(600);
    intake.move(0);
    conveyor.move(0);
    clamp.set_value(false);
    chassis.moveToPoint(48, -36, 1000, {.forwards = false}, false);
    chassis.turnToHeading(300,500);
    chassis.moveToPose(58, -56, 0, 3000, {.forwards = false}, false);
    clamp.set_value(true);
    chassis.turnToHeading(270, 500);
    pros::Task conveyorTask([]{ auton_conveyor("red"); });
    chassis.moveToPoint(4, -68, 2000);
    chassis.moveToPoint(20, -60, 1000, {.forwards = false}, false);
    chassis.turnToHeading(40, 500);
    conveyorTask.remove();
    clamp.set_value(false);
    chassis.moveToPoint(52, -8, 1000);
}
void redLeftCorner(){
    chassis.setPose(12, 14, 215);
    while(lady_brown_encoder.get_position() < 1750){
        setLadyBrownMechanism(127);
        while (lady_brown_encoder.get_position() < 200){
            pros::delay(20);
        }
    }
    setLadyBrownMechanism(0);
    conveyor.move(127);
    intake.move(127);
    pros::delay(1000);
    conveyor.move(0);
    intake.move(0);
    setLadyBrownMechanism(127);
    pros::delay(1000);
    setLadyBrownMechanism(0);
    pros::Task ladyBrownTask(moveLadyBrownAsync);
    //get 1st stake
    chassis.moveToPoint(22, 20, 500, {.forwards = false}, false);
    chassis.moveToPose(48,24,300,2500, {.forwards = false}, false);
    clamp.set_value(true);
    chassis.turnToHeading(60, 500);
    pros::Task conveyorTask([]{ auton_conveyor("red"); });
    chassis.moveToPoint(61, 47, 2000, {.maxSpeed = 50,  .minSpeed =30, .earlyExitRange = 5}, false);
    chassis.moveToPoint(60, 66, 1500, {.maxSpeed = 50}, false);
    chassis.turnToHeading(235, 500);
    chassis.moveToPoint(30, 12, 2000, {.minSpeed =50,  .earlyExitRange =8}, false);
    intake_piston.set_value(true);
    chassis.moveToPoint(24, 0, 1000, {.maxSpeed=90}, false);
    pros::delay(500);
    chassis.turnToHeading(90, 500);
    intake_piston.set_value(false);
    chassis.moveToPoint(48, 0, 2500);
    conveyorTask.remove();
    conveyor.move(0);
    intake.move(0);
    chassis.moveToPoint(55, 5, 2000, {.forwards = false}, false);

}
void blueLeftCorner(){

    chassis.setPose(22,32, 65);
    doinker.set_value(true);
    intake.move(127);
    conveyor.move(127);
    chassis.moveToPoint(53, 46, 1000);
    pros::delay(800);
    intake.move(0);
    conveyor.move(0);
    doinker.set_value(false);
    chassis.moveToPoint(45, 39, 1000, {.forwards = false}, false);
    doinker.set_value(true);
    pros::delay(100);

    chassis.moveToPose(48, 24, 0, 3000, {.forwards = false}, false);
    clamp.set_value(true);
    doinker.set_value(false);
    pros::delay(550);
    intake.move(127);
    conveyor.move(127);
    pros::delay(600);
    intake.move(0);
    conveyor.move(0);
    clamp.set_value(false);
    chassis.moveToPoint(48, 36, 1000, {.forwards = false}, false);
    chassis.turnToHeading(240,500);
    chassis.moveToPose(58, 56, 180, 3000, {.forwards = false}, false);
    clamp.set_value(true);
    chassis.turnToHeading(270, 500);
    pros::Task conveyorTask([]{ auton_conveyor("blue"); });
    chassis.moveToPoint(4, 68, 2000);
    chassis.moveToPoint(20, 60, 1000, {.forwards = false}, false);
    chassis.turnToHeading(40, 500);
    conveyorTask.remove();
    clamp.set_value(false);
    chassis.moveToPoint(52, 8, 3000);
}
void blueRightCorner(){
    chassis.setPose(12, -14, 325);
    while(lady_brown_encoder.get_position() < 1750){
        setLadyBrownMechanism(127);
        while (lady_brown_encoder.get_position() < 200){
            pros::delay(20);
        }
    }
    setLadyBrownMechanism(0);
    conveyor.move(127);
    intake.move(127);
    pros::delay(1000);
    conveyor.move(0);
    intake.move(0);
    pros::delay(1000);
    setLadyBrownMechanism(127);
    pros::delay(1000);
    setLadyBrownMechanism(0);
    pros::Task ladyBrownTask(moveLadyBrownAsync);
    //get 1st stake
    chassis.moveToPoint(22, -20, 500, {.forwards = false}, false);
    chassis.moveToPose(48,-24,240,2500, {.forwards = false}, false);
    clamp.set_value(true);
    chassis.turnToHeading(120, 500);
    pros::Task conveyorTask([]{ auton_conveyor("blue"); });
    chassis.moveToPoint(61, -47, 2000, {.maxSpeed = 50,  .minSpeed =30, .earlyExitRange = 5}, false);
    chassis.moveToPoint(60, -66, 1500, {.maxSpeed = 50}, false);
    chassis.turnToHeading(305, 500);
    chassis.moveToPoint(30, -12, 2000, {.minSpeed =50,  .earlyExitRange =8}, false);
    intake_piston.set_value(true);
    chassis.moveToPoint(24, 0, 1000, {.maxSpeed=90}, false);
    pros::delay(500);
    chassis.turnToHeading(180, 500);
    intake_piston.set_value(false);
    chassis.moveToPoint(-8, -80, 2500);
    conveyorTask.remove();
    conveyor.move(0);
    intake.move(0);
    chassis.moveToPoint(55, -5, 2000, {.forwards = false}, false);
}

void fractalILOVEYOU(){
    move(50,  300);
}