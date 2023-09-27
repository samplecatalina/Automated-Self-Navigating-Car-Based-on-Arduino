#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>
// #include "time.h"

// Conditional compilation directives to ensure the right "include" path for Windows or Unix is used, as well as clock calculation
#ifdef _WIN32
    #include "include\SDL2\SDL.h"
    #include "SDL2_gfx\SDL2_gfxPrimitives.h"
    #define CLOCK_CALCULATION   1000 / CLOCKS_PER_SEC
#else
    #include "SDL2/SDL.h"
    #include "SDL2/SDL2_gfxPrimitives.h"

    #ifdef __linux__
        // Use Linux method of calclating clock from https://edstem.org/au/courses/6697/discussion/634345
        #include "unistd.h"
        #define CLOCK_CALCULATION   10 / sysconf(_SC_CLK_TCK)
    #else
        // macOS calulates clock with same formula as Windows
        #define CLOCK_CALCULATION   1000 / CLOCKS_PER_SEC
    #endif
#endif

#include "formulas.h"
#include "wall.h"
#include "robot.h"

int done = 0;

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_left_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_sensor, side_right_top_sensor, side_right_lower_sensor, front_right_sensor=0;
    int initialCounter = 0;
    int tracking = -1; // -1 for starting, 0 for left turn, 1 for right turn, 2 for tracking right wall, 3 for tracking left wall.
    struct timeval start_time, end_time;
    gettimeofday(&start_time, 0);
    unsigned long msec;
    // clock_t start_time, end_time;
    // int msec;


    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.

    //#include "mazeSetup2.txt"
    
    #include "math.h"   

//  int i;
//     insertAndSetFirstWall(&head, 12,  120, 450, 10, 30);
//     insertAndSetFirstWall(&head, 12,  220, 450, 10, 30);
//     for (i = 0; i < 100; i++){
//         insertAndSetFirstWall(&head, i,  20 + i , 350 + i, 10, 10); //1
//         insertAndSetFirstWall(&head, i,  20 +100 + i , 350 + i, 10, 10); //1
//     }
//     insertAndSetFirstWall(&head, 12,  20, 280, 10, 70);
//     insertAndSetFirstWall(&head, 12,  120, 280, 10, 70);
//     for (i = 0; i < 180; i++){
//         insertAndSetFirstWall(&head, i,  20 +190 - i/2 , 100 + i, 10, 10); //1
//     }
//     for (i = 0; i < 105; i++){
//         insertAndSetFirstWall(&head, i,  20 +105/2 - i/2 , 175 + i, 10, 10); //1
//     }
//     insertAndSetFirstWall(&head, 2,  20, 175, 105/2, 10);
//     insertAndSetFirstWall(&head, 2,  20, 20, 10, 155);
//     insertAndSetFirstWall(&head, 2,  20, 20, 300, 10);
//     insertAndSetFirstWall(&head, 2,  320, 20, 10, 60);
//     insertAndSetFirstWall(&head, 2,  80, 100, 130, 10);
//     insertAndSetFirstWall(&head, 2,  80, 80, 10, 20);
//     insertAndSetFirstWall(&head, 2,  80, 80, 160, 10);

//     double j;
//     for (i = 0; i < 50; i++){
//         j = i;
//         insertAndSetFirstWall(&head, i+1,
//                               // the most important bit is below.
//                               // increase the 20 for a tighter bend
//                               // descrease for a more meandering flow
//                               320 + 30*sin(10*j * M_PI/180),
//                               // increase the 5 for a spacier curve
//                               (i * 5)+80,
//                               10, 10);
//     }
//     for (i = 0; i < 75; i++){
//         j = i;
//         insertAndSetFirstWall(&head, i+1,
//                               // the most important bit is below.
//                               // increase the 20 for a tighter bend
//                               // descrease for a more meandering flow
//                               240 + 30*sin(10*j * M_PI/180),
//                               // increase the 5 for a spacier curve
//                               (i * 5)+80,
//                               10, 10);
//     }
//     insertAndSetFirstWall(&head, 2,  345, 330, 105, 10);
//     insertAndSetFirstWall(&head, 2,  450, 190, 10, 150);
//     insertAndSetFirstWall(&head, 2,  380, 190, 70, 10);
//     insertAndSetFirstWall(&head, 2,  380, 20, 10, 170);
//     insertAndSetFirstWall(&head, 2,  380, 20, 260, 10);

//     insertAndSetFirstWall(&head, 2,  255, 455, 345, 10);
//     insertAndSetFirstWall(&head, 2,  600, 100, 10, 365);
//     insertAndSetFirstWall(&head, 2,  530, 100, 70, 10);
//     insertAndSetFirstWall(&head, 2,  530, 80, 10, 20);
//     insertAndSetFirstWall(&head, 2,  530, 80, 110, 10);
 int i;
    insertAndSetFirstWall(&head, 12,  120, 450, 10, 30);
    insertAndSetFirstWall(&head, 12,  220, 450, 10, 30);
    for (i = 0; i < 100; i++){
        insertAndSetFirstWall(&head, i,  20 + i , 350 + i, 10, 10); //1
        insertAndSetFirstWall(&head, i,  20 +100 + i , 350 + i, 10, 10); //1
    }
    insertAndSetFirstWall(&head, 12,  20, 280, 10, 70);
    insertAndSetFirstWall(&head, 12,  120, 280, 10, 70);
    for (i = 0; i < 180; i++){
        insertAndSetFirstWall(&head, i,  20 +190 - i/2 , 100 + i, 10, 10); //1
    }
    for (i = 0; i < 105; i++){
        insertAndSetFirstWall(&head, i,  20 +105/2 - i/2 , 175 + i, 10, 10); //1
    }
    insertAndSetFirstWall(&head, 2,  20, 175, 105/2, 10);
    insertAndSetFirstWall(&head, 2,  20, 20, 10, 155);
    insertAndSetFirstWall(&head, 2,  20, 20, 300, 10);
    insertAndSetFirstWall(&head, 2,  320, 20, 10, 60);
    insertAndSetFirstWall(&head, 2,  80, 100, 130, 10);
    insertAndSetFirstWall(&head, 2,  80, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  80, 80, 160, 10);

    double j;
    for (i = 0; i < 50; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              320 + 30*sin(10*j * M_PI/180),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }
    for (i = 0; i < 75; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              240 + 30*sin(10*j * M_PI/180),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }
    insertAndSetFirstWall(&head, 2,  345, 330, 105, 10);
    insertAndSetFirstWall(&head, 2,  450, 190, 10, 150);
    insertAndSetFirstWall(&head, 2,  380, 190, 70, 10);
    insertAndSetFirstWall(&head, 2,  380, 20, 10, 170);
    insertAndSetFirstWall(&head, 2,  380, 20, 260, 10);

    insertAndSetFirstWall(&head, 2,  255, 455, 345, 10);
    insertAndSetFirstWall(&head, 2,  600, 100, 10, 365);
    insertAndSetFirstWall(&head, 2,  530, 100, 70, 10);
    insertAndSetFirstWall(&head, 2,  530, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  530, 80, 110, 10);



    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1) {
            if (initialCounter < 1){
                tracking = robotFindRightWall(&robot, front_left_sensor, front_right_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_top_sensor, side_right_lower_sensor, tracking);
                initialCounter++;
            } else {
                tracking = robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_top_sensor, side_right_lower_sensor, tracking);
                printf("\n%d\n", tracking);
            }
        } else if (robot.auto_mode == 2) {
            if (initialCounter < 1){
                tracking = robotFindRightWall(&robot, front_left_sensor, front_right_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_top_sensor, side_right_lower_sensor, tracking);
                initialCounter++;
            } else {
                tracking = robotAutoMotorMove2(&robot, front_left_sensor, front_right_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_top_sensor, side_right_lower_sensor, tracking);
                printf("\n%d\n", tracking);
            }
        } else if (robot.auto_mode == 3) {
            if (initialCounter < 1){
                tracking = robotFindLeftWall(&robot, front_left_sensor, front_right_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_top_sensor, side_right_lower_sensor, tracking);
                initialCounter++;
            } else {
                tracking = robotAutoMotorMove3(&robot, front_left_sensor, front_right_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_top_sensor, side_right_lower_sensor, tracking);
                printf("\n%d\n", tracking);
            }
        } else if (robot.auto_mode == 4) {
            if (initialCounter < 1){
                tracking = robotFindLeftWall(&robot, front_left_sensor, front_right_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_top_sensor, side_right_lower_sensor, tracking);
                initialCounter++;
            } else {
                tracking = robotAutoMotorMove4(&robot, front_left_sensor, front_right_sensor, side_left_top_sensor, side_left_lower_sensor, side_right_top_sensor, side_right_lower_sensor, tracking);
                printf("\n%d\n", tracking);
            }
        }
        robotMotorMove(&robot);

        //Check if robot reaches endpoint. and check sensor values
        //if (checkRobotReachedEnd(&robot, 220, 480, 100, 10)){
        if (checkRobotReachedEnd(&robot, 640, 20, 10, 60)){ //Maze 5
            robot.auto_mode = 0;
            gettimeofday(&end_time, 0);
            msec = ((end_time.tv_sec - start_time.tv_sec)*1000)+(end_time.tv_usec - start_time.tv_usec)/1000;
            // end_time = clock();
            // msec = (end_time-start_time) * CLOCK_CALCULATION;
            robotSuccess(&robot, msec);
        }
        else if(checkRobotHitWalls(&robot, head)) {
            robotCrash(&robot);
            initialCounter = 0;
            tracking = -1;
        }
        //Otherwise compute sensor information
        else {
            front_left_sensor = checkRobotSensorFrontLeftAllWalls(&robot, head);
            if (front_left_sensor>0)
                printf("Getting close on the front left. Score = %d\n", front_left_sensor);

            front_right_sensor = checkRobotSensorFrontRightAllWalls(&robot, head);
            if (front_right_sensor>0)
                printf("Getting close on the front right. Score = %d\n", front_right_sensor);

            side_left_top_sensor = checkRobotSensorSideLeftTopAllWalls(&robot, head);
            if (side_left_top_sensor>0)
                printf("Getting close on the UPPER side left. Score = %d\n", side_left_top_sensor);

            side_left_lower_sensor = checkRobotSensorSideLeftLowerAllWalls(&robot, head);
            if (side_left_lower_sensor>0)
                printf("Getting close on the LOWER side left. Score = %d\n", side_left_lower_sensor);

            side_right_top_sensor = checkRobotSensorSideRightTopAllWalls(&robot, head);
            if (side_right_top_sensor>0)
                printf("Getting close on the UPPER side right. Score = %d\n", side_right_top_sensor);

            side_right_lower_sensor = checkRobotSensorSideRightLowerAllWalls(&robot, head);
            if (side_right_lower_sensor>0)
                printf("Getting close on the LOWER side right. Score = %d\n", side_right_lower_sensor);

        }

        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                initialCounter = 0;
                tracking = -1;
                gettimeofday(&start_time, 0);
                // start_time = clock();
            }
            if(state[SDL_SCANCODE_Q]){
                robot.auto_mode = 2;
                initialCounter = 0;
                tracking = -1;
                gettimeofday(&start_time, 0);
                // start_time = clock();
            }
            if(state[SDL_SCANCODE_W]){
                robot.auto_mode = 3;
                initialCounter = 0;
                tracking = -1;
                gettimeofday(&start_time, 0);
                // start_time = clock();
            }
            if(state[SDL_SCANCODE_E]){
                robot.auto_mode = 4;
                initialCounter = 0;
                tracking = -1;
                gettimeofday(&start_time, 0);
                // start_time = clock();
            }
            if(state[SDL_SCANCODE_R]){
                robot.auto_mode = 0;
                initialCounter = 0;
                tracking = -1;
                gettimeofday(&start_time, 0);
                // start_time = clock();
            }
            
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
