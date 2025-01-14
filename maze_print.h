#ifndef MAZE_PRINT_H
#define MAZE_PRINT_H


#define WIDTH 40
#define HEIGHT 40

extern int endX;
extern int endY;
extern int pathLength ;
typedef struct Cell {
    int i, j;          // Position de la cellule
    int N, S, E, W;    // Murs : 1 = mur, 0 = pas de mur
    Color color;       // Couleur pour l'affichage
    int visited;       // Indique si la cellule a été visitée
     struct Cell *parent; // Pointeur vers la cellule parente
} Cell;


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

// Directions pour le déplacement : Haut, Droite, Bas, Gauche
int directions[4][2] = {
    {0, -1}, // Nord
    {1, 0},  // Est
    {0, 1},  // Sud
    {-1, 0}  // Ouest
};
void InitMaze();
void ShuffleDirections(int dir[4][2]);
void GenerateMaze(int x, int y);
void DrawMaze(int cellSize, int offset);
void resetCell();
void newEnd();




#endif
