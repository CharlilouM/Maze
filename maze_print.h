#ifndef MAZE_PRINT_H
#define MAZE_PRINT_H
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze_move.h"

#define WIDTH 20
#define HEIGHT 20

extern const int screenWidth;
extern const int screenHeight;
extern int startX;
extern int startY;
extern int endX;
extern int endY;
extern int BombeNumber;
extern int pathLength;
extern int wall;
extern const int offset;
extern const int cellSize ;
extern char timeText[50];
extern char pathLengthText[50];

typedef struct Cell {
    int i, j;          // Position de la cellule
    int N, S, E, W;    // Murs : 1 = mur, 0 = pas de mur
    int bombe;
    Color color;       // Couleur pour l'affichage
    int visited;       // Indique si la cellule a été visitée
    struct Cell *parent; // Pointeur vers la cellule parente
} Cell;

extern Cell Maze[WIDTH][HEIGHT];


extern int directions[4][2];
void InitMaze();
void ShuffleDirections(int dir[4][2]);
void GenerateMaze(int x, int y);
void DrawMaze(int cellSize, int offset);
void resetCell(bool color);
void newEnd();
void DrawTextBelowMaze();

void InitBomb();




#endif
