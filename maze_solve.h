#ifndef MAZE_SOLVE_H
#define MAZE_SOLVE_H
#include "maze_print.h"


extern clock_t start, end;
extern double cpu_time_used;


typedef struct Node {
    int x, y;            // Position
    int gCost;           // Coût depuis le départ
    int hCost;           // Estimation du coût restant
    int fCost;           // Coût total (g + h)
    struct Node *parent; // Parent pour reconstruire le chemin
} Node;

// Structure pour une liste dynamique de coordonnées
typedef struct PathList {
    int x, y;
    struct PathList* next;
} PathList;

extern PathList* pathList;

typedef struct Queue {
    int x, y;
    struct Queue *next;
} Queue;
void enqueue(Queue **queue, int x, int y) ;
Queue* dequeue(Queue **queue) ;

PathList* SolveMazeDFS(int x, int y, int endX, int endY,Color color) ;
int SolveMazeBFS(int startX, int startY, int endX, int endY) ;
int Heuristic(int x1, int y1, int x2, int y2) ;
Node* FindLowestFCost(Node *openList[], int openCount) ;
int IsInList(Node *list[], int count, int x, int y) ;
void AddToPathList(PathList** pathList, int x, int y) ;
void PrintPath(PathList* pathList) ;
int CalculatePathLength(Node* endNode, PathList** pathList) ;
int SolveMazeAStar(int startX, int startY, int endX, int endY) ;



#endif
