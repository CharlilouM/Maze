#ifndef MAZE_MOVE_H
#define MAZE_MOVE_H

#include "maze_solve.h"
#include "maze_print.h"

struct PathList;

typedef struct Robot {
    int x, y;          // Position du robot
    int aimX,aimY;
    Color color;       // Couleur pour l'affichage
    PathList* path;
    clock_t start_move;
} Robot;
extern Robot robot1;
extern Robot robot2;
extern bool mouvement;
extern bool EnableRobot2Movement;
void reset_robot();
int move_robot1();
int move_robot2();
void InitializeRobots();
#endif
