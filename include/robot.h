#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "formulas.h"
#include "time.h"
#include "wall.h"
#include "math.h"

// Conditional compilation directives to ensure the right "include" path for Windows or Unix is used
#ifdef _WIN32
    #include "include\SDL2\SDL.h"
    #include "SDL2_gfx\SDL2_gfxPrimitives.h"
#else
    #include "SDL2/SDL.h"
    #include "SDL2/SDL2_gfxPrimitives.h"
#endif

//Setup
void setup_robot(struct Robot *robot);

//Error/Finish Checking
int robot_off_screen(struct Robot * robot);
int checkRobotHitWall(struct Robot * robot, struct Wall * wall);
int checkRobotHitWalls(struct Robot * robot, struct Wall_collection * head);
int checkRobotReachedEnd(struct Robot * robot, int x, int y, int width, int height);
void robotCrash(struct Robot * robot);
void robotSuccess(struct Robot * robot, unsigned long msec);
// void robotSuccess(struct Robot * robot, int msec);

//Sensor Checking
int checkRobotSensor(int x, int y, int sensorSensitivityLength, struct Wall * wall) ;

int checkRobotSensorFrontRightAllWalls(struct Robot * robot, struct Wall_collection * head);
int checkRobotSensorFrontLeftAllWalls(struct Robot * robot, struct Wall_collection * head);

int checkRobotSensorSideRightTopAllWalls(struct Robot * robot, struct Wall_collection * head);
int checkRobotSensorSideRightLowerAllWalls(struct Robot * robot, struct Wall_collection * head);

int checkRobotSensorSideLeftTopAllWalls(struct Robot * robot, struct Wall_collection * head);
int checkRobotSensorSideLeftLowerAllWalls(struct Robot * robot, struct Wall_collection * head);
//Visual Display
void robotUpdate(struct SDL_Renderer * renderer, struct Robot * robot);

//Movement
void robotMotorMove(struct Robot * robot);
int robotAutoMotorMove(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking);
int robotAutoMotorMove2(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking);
int robotAutoMotorMove3(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking);
int robotAutoMotorMove4(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking);
int robotFindRightWall(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking);
int robotFindLeftWall(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking);

#endif // ROBOT_H_INCLUDED
