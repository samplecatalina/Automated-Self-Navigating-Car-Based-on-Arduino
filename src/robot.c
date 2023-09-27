#include "include\robot.h"

/*void setup_robot(struct Robot *robot){
    robot->x = OVERALL_WINDOW_WIDTH/2-50;
    robot->y = OVERALL_WINDOW_HEIGHT-50;
    robot->true_x = OVERALL_WINDOW_WIDTH/2-50;
    robot->true_y = OVERALL_WINDOW_HEIGHT-50;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;*/
    //Maze 5
void setup_robot(struct Robot *robot){
    robot->x = 170;
    robot->y = 460;
    robot->true_x = 170;
    robot->true_y = 460;
    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
    

    printf("\nPress arrow keys to move manually.\n");
    printf("R to reset back to manual mode.\n");
    printf("SPACE to restart the level.\n\n");
    printf("Automatic movement controls:\n");
    printf("ENTER for Speed Mode, Right Wall\n");
    printf("Q for Precision Mode, RIght Wall\n");
    printf("W for Precision Mode, Left Wall\n");
    printf("E for Speed Mode, Left Wall\n\n");
    
}
int robot_off_screen(struct Robot * robot){
    if(robot->x < 0 || robot-> y < 0){
        return 0;
    }
    if(robot->x > OVERALL_WINDOW_WIDTH || robot->y > OVERALL_WINDOW_HEIGHT){
        return 0;
    }
    return 1;
}

int checkRobotHitWall(struct Robot * robot, struct Wall * wall) {

    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 wall->x,wall->width,wall->y, wall->height);

    return overlap;
}

int checkRobotHitWalls(struct Robot * robot, struct Wall_collection * head) {
   struct Wall_collection *ptr = head;
   int hit = 0;

   while(ptr != NULL) {
      hit = (hit || checkRobotHitWall(robot, &ptr->wall));
      ptr = ptr->next;
   }
   return hit;

}

int checkRobotReachedEnd(struct Robot * robot, int x, int y, int width, int height){

    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 x,width,y,height);

    return overlap;
}

void robotCrash(struct Robot * robot) {
    robot->currentSpeed = 0;
    if (!robot->crashed)
        printf("Ouchies!!!!!\n\nPress space to start again\n");
    robot->crashed = 1;
}

void robotSuccess(struct Robot * robot, int msec) {
    robot->currentSpeed = 0;
    if (!robot->crashed){
        printf("Success!!!!!\n\n");
        printf("Time taken %d seconds %d milliseconds \n", msec/1000, msec%1000);
        printf("Press space to start again\n");
    }
    robot->crashed = 1;
}

// void robotSuccess(struct Robot * robot, unsigned long msec) {
//     robot->currentSpeed = 0;
//     if (!robot->crashed){
//         printf("Success!!!!!\n\n");
//         printf("Time taken %lu seconds %lu milliseconds \n", msec/1000, msec%1000);
//         printf("Press space to start again\n");
//     }
//     robot->crashed = 1;
// }

int checkRobotSensor(int x, int y, int sensorSensitivityLength, struct Wall * wall)  {
    //viewing_region of sensor is a square of 2 pixels * chosen length of sensitivity
    int overlap = checkOverlap(x,2,y,sensorSensitivityLength,
                 wall->x,wall->width,wall->y, wall->height);

    return overlap;
}

int checkRobotSensorFrontRightAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;

    int sensorSensitivityLength =  floor(SENSOR_VISION/5);

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorFrontLeftAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorSideLeftTopAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorSideLeftLowerAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorSideRightTopAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round(robotCentreX+(ROBOT_WIDTH/2+SENSOR_VISION-sensorSensitivityLength*i-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(ROBOT_WIDTH/2+SENSOR_VISION-sensorSensitivityLength*i-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorSideRightLowerAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        xDir = round(robotCentreX+(ROBOT_WIDTH/2+SENSOR_VISION-sensorSensitivityLength*i-2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(ROBOT_WIDTH/2+SENSOR_VISION-sensorSensitivityLength*i-2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

void robotUpdate(struct SDL_Renderer * renderer, struct Robot * robot){
    double xDir, yDir;

    int robotCentreX, robotCentreY, xTR, yTR, xTL, yTL, xBR, yBR, xBL, yBL;
    SDL_SetRenderDrawColor(renderer, 204, 255, 255, 255);

    /*
    //Other Display options:
    // The actual square which the robot is tested against (not so nice visually with turns, but easier
    // to test overlap
    SDL_Rect rect = {robot->x, robot->y, robot->height, robot->width};
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    */
    /*
    //Center Line of Robot. Line shows the direction robot is facing
    xDir = -30 * sin(-robot->angle*PI/180);
    yDir = -30 * cos(-robot->angle*PI/180);
    xDirInt = robot->x+ROBOT_WIDTH/2+ (int) xDir;
    yDirInt = robot->y+ROBOT_HEIGHT/2+ (int) yDir;
    SDL_RenderDrawLine(renderer,robot->x+ROBOT_WIDTH/2, robot->y+ROBOT_HEIGHT/2, xDirInt, yDirInt);
    */

    //Rotating Square - This is for drawing the actual robot square.
    //Vector rotation to work out corners x2 = x1cos(angle)-y1sin(angle), y2 = x1sin(angle)+y1cos(angle)
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTR = (int) xDir;
    yTR = (int) yDir;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBR = (int) xDir;
    yBR = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBL = (int) xDir;
    yBL = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTL = (int) xDir;
    yTL = (int) yDir;

    SDL_RenderDrawLine(renderer,xTR, yTR, xBR, yBR);
    SDL_RenderDrawLine(renderer,xBR, yBR, xBL, yBL);
    SDL_RenderDrawLine(renderer,xBL, yBL, xTL, yTL);
    SDL_RenderDrawLine(renderer,xTL, yTL, xTR, yTR);

    //Front Right Sensor
    int sensor_sensitivity =  floor(SENSOR_VISION/5);
    int i;
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 51+(20*(5-i)), 255, 51+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Front Left Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 51+(20*(5-i)), 255, 51+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Side Left Top Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, sensor_sensitivity, 2};
        SDL_SetRenderDrawColor(renderer, 51+(20*(5-i)), 255, 51+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Side Left Bottom Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, sensor_sensitivity, 2};
        SDL_SetRenderDrawColor(renderer, 51+(20*(5-i)), 255, 51+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Side UPPER Right Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(ROBOT_WIDTH/2+SENSOR_VISION-sensor_sensitivity*i-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(ROBOT_WIDTH/2+SENSOR_VISION-sensor_sensitivity*i-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, sensor_sensitivity, 2};
        SDL_SetRenderDrawColor(renderer, 51+(20*(5-i)), 255, 51+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }
    //Side LOWER Right Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(ROBOT_WIDTH/2+SENSOR_VISION-sensor_sensitivity*i-2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(ROBOT_WIDTH/2+SENSOR_VISION-sensor_sensitivity*i-2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, sensor_sensitivity, 2};
        SDL_SetRenderDrawColor(renderer, 51+(20*(5-i)), 255, 51+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }
}


void robotMotorMove(struct Robot * robot) {
    double x_offset, y_offset;
    switch(robot->direction){
        case UP :
            robot->currentSpeed += DEFAULT_SPEED_CHANGE;
            if (robot->currentSpeed > MAX_ROBOT_SPEED)
                robot->currentSpeed = MAX_ROBOT_SPEED;
            break;
        case DOWN :
            robot->currentSpeed -= DEFAULT_SPEED_CHANGE;
            if (robot->currentSpeed < -MAX_ROBOT_SPEED)
                robot->currentSpeed = -MAX_ROBOT_SPEED;
            break;
        case LEFT :
            robot->angle = (robot->angle+360-DEFAULT_ANGLE_CHANGE)%360;
            break;
        case RIGHT :
            robot->angle = (robot->angle+DEFAULT_ANGLE_CHANGE)%360;
            break;
    }
    robot->direction = 0;
    x_offset = (-robot->currentSpeed * sin(-robot->angle*PI/180));
    y_offset = (-robot->currentSpeed * cos(-robot->angle*PI/180));

    robot->true_x += x_offset;
    robot->true_y += y_offset;

    x_offset = round(robot->true_x);
    y_offset = round(robot->true_y);

    robot->x = (int) x_offset;
    robot->y = (int) y_offset;
}

// Speed Mode Right Wall
int robotAutoMotorMove(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking) {

    int maxSpeed = 3;
    int rightTurnSpeed = 3;
    int leftTurnSpeed = 3;
    
    // FINDING INITIAL RIGHT WALL DIRECTLY
    if (tracking < -1) {
        // 90 degree turn right
        if (tracking >= -6) {
            robot->direction = RIGHT;
            tracking--;
        } 
        // Move towards right wall
        else if (tracking == -7) {
            if (robot->currentSpeed < maxSpeed && front_left_sensor == 0 && front_right_sensor == 0) {
                robot->direction = UP;
            } else {
                if (robot->currentSpeed > 1) {
                    robot->direction = DOWN;
                } else {
                    tracking = -10;
                }
            }
        } 
        // 90 degree turn left
        else if (tracking <= -10 && tracking >= -15) {
            robot->direction = LEFT;
            tracking--;
        } 
        // Start tracking along the wall
        else if (tracking == -16) {
            tracking = 2;
        }
    }

    // STRAIGHT, TRACKING ALONG THE WALL
    else if (tracking == 2) {
        
        // Checking for a right turn
        if (side_right_top_sensor <= 1 && side_right_top_sensor < side_right_lower_sensor) {
            if (robot->currentSpeed > rightTurnSpeed) {
                robot->direction = DOWN;
            }
            else {
                robot->direction = RIGHT;
                tracking = 1; 
            }
        }
        
        // Checking for a left turn
        else if ( ((front_left_sensor > 1) || (front_right_sensor > 2)) && ((side_right_lower_sensor > 0) || (side_right_top_sensor > 0)) || (front_right_sensor == front_left_sensor && front_right_sensor > 0)) {
            // If there is a sharp acute angle turn, need to stop completely before turning
            if (side_left_top_sensor > 0) {
                if (robot->currentSpeed > 0) {
                    robot->direction = DOWN;
                } else {
                    robot->direction = LEFT;
                    tracking = 0;
                }
            }
            // Else slow down to specified turning speed then turn
            else {
                if (robot->currentSpeed > leftTurnSpeed) {
                    robot->direction = DOWN;
                } else {
                    robot->direction = LEFT;
                    tracking = 0;
                }
            }
        }
        
        // Checking if dead end, for 180 degree turn
        else if (side_right_top_sensor > 0 && side_right_lower_sensor > 0 && side_left_top_sensor > 0 && side_left_lower_sensor > 0 && front_right_sensor > 0 && front_left_sensor > 0) {
            if (robot->currentSpeed > 0) {
                robot->direction = DOWN;
            } else {
                tracking = 50;
            }
        }
        
        // Curved wall tracking and adjustment
        else if (side_right_top_sensor > side_right_lower_sensor) {
            robot->direction = LEFT;
        }

        // Accelerate if no walls in front
        else if ((front_left_sensor == 0) && (front_right_sensor == 0)) {
            if (robot->currentSpeed < maxSpeed)
                robot->direction = UP;
        }
    }

    // LEFT TURN
    else if (tracking == 0) {
        
        // Checking if robot should keep turning
        if ((side_right_top_sensor > 0 || side_right_lower_sensor > 0) && (front_right_sensor > 2 || front_left_sensor > 1) || (front_right_sensor == front_left_sensor && front_right_sensor > 0)) {
            robot->direction = LEFT;
        }
        
        // Checking if ready to start tracking wall again
        else if ( ((side_right_top_sensor > 0) && (side_right_lower_sensor > 0)) && (front_right_sensor == 0) && (front_left_sensor == 0)) {
            robot->direction = LEFT;
            tracking = 2;
        }
    }

    // RIGHT TURN
    else if (tracking == 1) {

        // Checking if robot should keep turning
        if (side_right_top_sensor <= 1 && side_right_top_sensor < side_right_lower_sensor) {
            robot->direction = RIGHT;
        }

        // Checking if ready to start tracking wall again
        else if ((side_right_top_sensor > 0) && (side_right_lower_sensor > 0) && (front_right_sensor == 0) && (front_left_sensor == 0)){
            tracking = 2;
        }
        
        // Checking if there is another immediate left turn
        else if (((front_left_sensor > 0) && (front_left_sensor == front_right_sensor)) && ((side_right_lower_sensor > 0) || (side_right_top_sensor > 0))) {
            if (robot->currentSpeed > 0) {
                robot->direction = DOWN;
            }
            tracking = 0;
        }
    }
    
    // 180 TURN DEAD END
    else if (tracking >= 50 && tracking < 65) {
        robot->direction = RIGHT;
        tracking++;
        if (tracking == 62) {
            tracking = 2;
        }
    }

    return tracking;
}

// Precision Mode Right Wall
int robotAutoMotorMove2(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking) {
    
    // FINDING INITIAL RIGHT WALL DIRECTLY
    if (tracking < -1) {
        // 90 degree turn right
        if (tracking >= -6) {
            robot->direction = RIGHT;
            tracking--;
        } 
        // Move towards right wall
        else if (tracking == -7) {
            if (robot->currentSpeed < 3 && front_left_sensor == 0 && front_right_sensor == 0) {
                robot->direction = UP;
            } else {
                if (robot->currentSpeed > 0) {
                    robot->direction = DOWN;
                } else {
                    tracking = -10;
                }
            }
        } 
        // 90 degree turn left
        else if (tracking <= -10 && tracking >= -15) {
            robot->direction = LEFT;
            tracking--;
        } 
        // Start tracking along the wall
        else if (tracking == -16) {
            tracking = 2;
        }
    }

    // STRAIGHT, TRACKING ALONG THE WALL
    else if (tracking == 2) {
        
        // Checking for a left turn
        if ( ((front_left_sensor > 2) || (front_right_sensor > 2)) && ((side_right_lower_sensor > 0) || (side_right_top_sensor > 0))) {
            if (robot->currentSpeed > 0) {
                robot->direction = DOWN;
            } else {
                tracking = 100;
            }
        }
    
        // Checking for a right turn
        else if ( side_right_lower_sensor == 0) {
            if (robot->currentSpeed > 1) {
                robot->direction = DOWN;
            } else {
                tracking = 50;
            }
        }
    
        // Accelerate if no walls in front
        else if ((front_left_sensor == 0) && (front_right_sensor == 0)) {
            if (robot->currentSpeed < 3)
                robot->direction = UP;
        }
    }
    
    // 90 degree turn left
     else if (tracking >= 100) {
        robot->direction = LEFT;
        tracking++;
        if (tracking == 106) {
            tracking = 10;
        }
    }
    
    // 90 degree turn right
    else if (tracking >= 50 && tracking < 60) {
        robot->direction = RIGHT;
        tracking++;
        if (tracking == 56) {
            tracking = 10;
        }
    }
    
    // For the bot to know that it's finished the right/left turn, the side right lower sensor
    // has to detect the right wall. Otherwise, it will prematurely assume that the wall is being tracked
    // as soon as turn is completed, could lead to wrong turns.
    
    // FINISHING THE TURN
    else if (tracking == 10) {
        
        // Checking if ready to start tracking wall again
        if ((side_right_lower_sensor > 0) ){
            if (robot->currentSpeed == 0)
                robot->direction = UP;
            tracking = 2;
        }
        
        // Checking if there is another immediate left turn
        else if (((front_left_sensor > 2) || (front_right_sensor > 2)) && ((side_right_lower_sensor > 0) || (side_right_top_sensor > 0))) {
            if (robot->currentSpeed > 0) {
                robot->direction = DOWN;
            }
            tracking = 100;
        }
        
        // Accelerate if no walls in front
        else if (robot->currentSpeed < 3)
            robot->direction = UP;
    }

    return tracking;
}

// Precision Mode Left Wall
int robotAutoMotorMove3(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking) {
    
    // FINDING INITIAL LEFT WALL DIRECTLY
    if (tracking < -1) {
        // 90 degree turn left
        if (tracking >= -6) {
            robot->direction = LEFT;
            tracking--;
        } 
        // Move towards left wall
        else if (tracking == -7) {
            if (robot->currentSpeed < 3 && front_left_sensor == 0 && front_right_sensor == 0) {
                robot->direction = UP;
            } else {
                if (robot->currentSpeed > 0) {
                    robot->direction = DOWN;
                } else {
                    tracking = -10;
                }
            }
        } 
        // 90 degree turn left
        else if (tracking <= -10 && tracking >= -15) {
            robot->direction = RIGHT;
            tracking--;
        } 
        // Start tracking along the wall
        else if (tracking == -16) {
            tracking = 2;
        }
    }

    // STRAIGHT, TRACKING ALONG THE WALL
    else if (tracking == 2) {
        
        // Checking for a right turn
        if ( ((front_left_sensor > 2) || (front_right_sensor > 2)) && ((side_left_lower_sensor > 0) || (side_left_top_sensor > 0))) {
            if (robot->currentSpeed > 0) {
                robot->direction = DOWN;
            } else {
                tracking = 50;
            }
        }
        
        // Checking for a left turn
        else if ( side_left_lower_sensor == 0) {
            if (robot->currentSpeed > 1) {
                robot->direction = DOWN;
            } else {
                tracking = 100;
            }
        }
        
        // Accelerate if no walls in front
        else if ((front_left_sensor == 0) && (front_right_sensor == 0)) {
            if (robot->currentSpeed < 3)
                robot->direction = UP;
        }
    }
    
    // 90 degree turn left
     else if (tracking >= 100) {
        robot->direction = LEFT;
        tracking++;
        if (tracking == 106) {
            tracking = 10;
        }
    }
    
    // 90 degree turn right
    else if (tracking >= 50 && tracking < 60) {
        robot->direction = RIGHT;
        tracking++;
        if (tracking == 56) {
            tracking = 10;
        }
    }
    
    // For the bot to know that it's finished the right/left turn, the side left lower sensor
    // has to detect the left wall. Otherwise, it will prematurely assume that the wall is being tracked
    // as soon as turn is completed, could lead to wrong turns.
    
    // FINISHING THE TURN
    else if (tracking == 10) {
        
        // Checking if ready to start tracking wall again
        if ((side_left_lower_sensor > 0) ){
            if (robot->currentSpeed == 0)
                robot->direction = UP;
            tracking = 2;
        }
        
        // Checking if there is another immediate left turn
        else if (((front_left_sensor > 2) || (front_right_sensor > 2)) && ((side_left_lower_sensor > 0) || (side_left_top_sensor > 0))) {
            if (robot->currentSpeed > 0) {
                robot->direction = DOWN;
            }
            tracking = 50;
        }
        
        // Accelerate if no walls in front
        else if (robot->currentSpeed < 3)
            robot->direction = UP;
    }

    return tracking;
}

// Speed Mode Left Wall
int robotAutoMotorMove4(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking) {
    
    int maxSpeed = 3;
    int leftTurnSpeed = 3;
    int rightTurnSpeed = 3;
    
    // FINDING INITIAL LEFT WALL DIRECTLY
    if (tracking < -1) {
        // 90 degree turn left
        if (tracking >= -6) {
            robot->direction = LEFT;
            tracking--;
        } 
        // Move towards left wall
        else if (tracking == -7) {
            if (robot->currentSpeed < maxSpeed && front_left_sensor == 0 && front_right_sensor == 0) {
                robot->direction = UP;
            } else {
                if (robot->currentSpeed > 1) {
                    robot->direction = DOWN;
                } else {
                    tracking = -10;
                }
            }
        } 
        // 90 degree turn right
        else if (tracking <= -10 && tracking >= -15) {
            robot->direction = RIGHT;
            tracking--;
        } 
        // Start tracking along the wall
        else if (tracking == -16) {
            tracking = 2;
        }
    }

    // STRAIGHT, TRACKING ALONG THE WALL
    else if (tracking == 2) {
        
        // Checking for a left turn
        if (side_left_top_sensor <= 1 && side_left_top_sensor < side_left_lower_sensor) {
            if (robot->currentSpeed > leftTurnSpeed) {
                robot->direction = DOWN;
            }
            else {
                robot->direction = LEFT;
                tracking = 1; 
            }
        }
        
        // Checking for a right turn
        else if (((front_right_sensor > 1) || (front_left_sensor > 2)) && ((side_left_lower_sensor > 0) || (side_left_top_sensor > 0)) || (front_right_sensor == front_left_sensor && front_left_sensor > 0)) {
             // If there is a sharp acute angle turn, need to stop completely before turning
            if (side_right_top_sensor > 0) {
                if (robot->currentSpeed > 0) {
                    robot->direction = DOWN;
                } else {
                    robot->direction = RIGHT;
                    tracking = 0;
                }
            }
            // Else slow down to specified turning speed then turn
            else {
                if (robot->currentSpeed > rightTurnSpeed) {
                    robot->direction = DOWN;
                } else {
                    robot->direction = RIGHT;
                    tracking = 0;
                }
            }
        }

        // Checking if dead end, for 180 degree turn
        else if (side_right_top_sensor > 0 && side_right_lower_sensor > 0 && side_left_top_sensor > 0 && side_left_lower_sensor > 0 && front_right_sensor > 0 && front_left_sensor > 0) {
            if (robot->currentSpeed > 0) {
                robot->direction = DOWN;
            } else {
                tracking = 50;
            }
        }
        
        // Curved wall tracking and adjustment
        else if (side_left_top_sensor > side_left_lower_sensor) {
            robot->direction = RIGHT;
        }
        
        // Accelerate if no walls in front
        else if ((front_left_sensor == 0) && (front_right_sensor == 0)) {
            if (robot->currentSpeed < maxSpeed)
                robot->direction = UP;
        }
    }

    // RIGHT TURN
    else if (tracking == 0) {
        
        // Checking if robot should keep turning
        if ((side_left_top_sensor > 0 || side_left_lower_sensor > 0) && (front_left_sensor > 2 || front_right_sensor > 1) || (front_right_sensor == front_left_sensor && front_left_sensor > 0)) {
            robot->direction = RIGHT;
        }
        
        // Checking if ready to start tracking wall again
        else if ( ((side_left_top_sensor > 0) && (side_left_lower_sensor > 0)) && (front_right_sensor == 0) && (front_left_sensor == 0)) {
            robot->direction = RIGHT;
            tracking = 2;
        }
    }

    // LEFT TURN
    else if (tracking == 1) {

        // Checking if robot should keep turning
        if (side_left_top_sensor <= 1 && side_left_top_sensor < side_left_lower_sensor) {
            robot->direction = LEFT;
        }
        
        // Checking if ready to start tracking wall again
        else if ((side_left_top_sensor > 0) && (side_left_lower_sensor > 0) && (front_right_sensor == 0) && (front_left_sensor == 0)){
            tracking = 2;
        }
        
        // Checking if there is another immediate right turn
        else if (((front_right_sensor > 0) && (front_left_sensor == front_right_sensor)) && ((side_left_lower_sensor > 0) || (side_left_top_sensor > 0))) {
            if (robot->currentSpeed > 0) {
                robot->direction = DOWN;
            }
            tracking = 0;
        }
    }
    
    // 180 TURN DEAD END
    else if (tracking >= 50 && tracking < 65) {
        robot->direction = RIGHT;
        tracking++;
        if (tracking == 62) {
            tracking = 2;
        }
    }

    return tracking;
}

int robotFindRightWall(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking) {
    
    // Start tracking if robot already close to wall and aligned
    if (side_right_top_sensor > 0 && side_right_lower_sensor > 0 && side_right_top_sensor == side_right_lower_sensor) {
        robot->direction = UP;
        tracking = 2;
    } 
    // Find initial wall algorithm
    else {
        robot->direction = RIGHT;
        tracking = -2;
    }
    return tracking;
}

int robotFindLeftWall(struct Robot * robot, int front_left_sensor, int front_right_sensor, int side_left_top_sensor, int side_left_lower_sensor, int side_right_top_sensor, int side_right_lower_sensor, int tracking) {
    
    // Start tracking if robot already close to wall and aligned
    if (side_left_top_sensor > 0 && side_left_lower_sensor > 0 && side_left_top_sensor == side_left_lower_sensor) {
        robot->direction = UP;
        tracking = 2;
    } 
    // Find initial wall algorithm
    else {
        robot->direction = LEFT;
        tracking = -2;
    }
    return tracking;
}