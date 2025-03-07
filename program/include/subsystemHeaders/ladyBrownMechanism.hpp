#pragma once

//helper functions
void setLadyBrownMechanism(int power);

void moveToPosition(int targetPosition);

//driver functions
void setLadyBrownMotor();
//macro functions
void prepareLadyBrownTask(void* param);

void prepareLadyBrown();

void moveLadyBrownAsync();

void secondary_lady_brown();