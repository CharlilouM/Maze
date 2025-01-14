#include "raylib.h"
#include "maze_print.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int startX=0;
int startY=0;
int endX=0;
int endY=0;

int pathLength=0 ;
int wall=2;
const int offset = 20;
const int screenWidth = 1920*0.75;
const int screenHeight = 1080*0.75;
const int cellSize =(screenHeight-2*offset)/HEIGHT ;

Cell Maze[WIDTH][HEIGHT];

clock_t start, end;
double cpu_time_used;
char timeText[50];
char pathLengthText[50];

// Fonction pour initialiser le labyrinthe
void InitMaze() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Maze[i][j] = (Cell){i, j, 1, 1, 1, 1, WHITE, 0}; // Tout est mur au départ
        }
    }

}

// Mélange les directions pour introduire de l'aléatoire
void ShuffleDirections(int dir[4][2]) {
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int tempX = dir[i][0];
        int tempY = dir[i][1];
        dir[i][0] = dir[j][0];
        dir[i][1] = dir[j][1];
        dir[j][0] = tempX;
        dir[j][1] = tempY;
    }
}

// Fonction récursive pour générer le labyrinthe
void GenerateMaze(int x, int y) {
    Maze[x][y].visited = 1;

    ShuffleDirections(directions);
    
    for (int d = 0; d < 4; d++) {
        int nx = x + directions[d][0];
        int ny = y + directions[d][1];

        // Vérifie si la cellule voisine est dans les limites et non visitée
        if (nx >= 0 && ny >= 0 && nx < WIDTH && ny < HEIGHT && !Maze[nx][ny].visited) {
            // Supprime les murs entre les cellules
            if (directions[d][0] == 0 && directions[d][1] == -1) { // Nord
                Maze[x][y].N = 0;
                Maze[nx][ny].S = 0;
            } else if (directions[d][0] == 1 && directions[d][1] == 0) { // Est
                Maze[x][y].E = 0;
                Maze[nx][ny].W = 0;
            } else if (directions[d][0] == 0 && directions[d][1] == 1) { // Sud
                Maze[x][y].S = 0;
                Maze[nx][ny].N = 0;
            } else if (directions[d][0] == -1 && directions[d][1] == 0) { // Ouest
                Maze[x][y].W = 0;
                Maze[nx][ny].E = 0;
            }
            // Appelle récursivement la fonction sur la cellule voisine
            GenerateMaze(nx, ny);
        }
    }
}
void resetCell(){
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Maze[i][j].visited=0;
            Maze[i][j].color=WHITE;                 
                    }
    }
    
    Maze[startX][startY].color = BLUE; // Départ
    Maze[endX][endY].color = RED;     // Arrivée
}
// Fonction pour dessiner le labyrinthe
void DrawMaze(int cellSize, int offset) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Cell cell = Maze[i][j];
            int x = cell.i * cellSize + offset;
            int y = cell.j * cellSize + offset;
            DrawRectangle(x, y, cellSize, cellSize, cell.color);
            // Dessine les murs
            if (cell.N) DrawRectangle(x, y, cellSize, wall, BLACK);
            if (cell.S) DrawRectangle(x, y + cellSize - wall, cellSize, wall, BLACK);
            if (cell.E) DrawRectangle(x + cellSize - wall, y, wall, cellSize, BLACK);
            if (cell.W) DrawRectangle(x, y, wall, cellSize, BLACK);
        }
    }
}


int SolveMazeDFS(int x, int y, int endX, int endY) {
    // Vérifie si nous avons atteint la cellule d'arrivée
    if (x == endX && y == endY) {
        //Maze[x][y].color = GREEN; // Colorie le chemin trouvé
        return 1; // Solution trouvée
    }

    // Marquer la cellule comme visitée
    Maze[x][y].visited = 1;
    Maze[x][y].color = YELLOW; // Marque la cellule sur le chemin en exploration

    // Explorer les directions : Nord, Sud, Est, Ouest
    if (Maze[x][y].N == 0 && !Maze[x][y - 1].visited) { // Nord
        if (SolveMazeDFS(x, y - 1, endX, endY)) {
            Maze[x][y].color = GREEN; // Marquer le chemin
            pathLength++;
            return 1;
        }
    }
    if (Maze[x][y].S == 0 && !Maze[x][y + 1].visited) { // Sud
        if (SolveMazeDFS(x, y + 1, endX, endY)) {
            Maze[x][y].color = GREEN;
            pathLength++;
            return 1;
        }
    }
    if (Maze[x][y].E == 0 && !Maze[x + 1][y].visited) { // Est
        if (SolveMazeDFS(x + 1, y, endX, endY)) {
            Maze[x][y].color = GREEN;
            pathLength++;
            return 1;
        }
    }
    if (Maze[x][y].W == 0 && !Maze[x - 1][y].visited) { // Ouest
        if (SolveMazeDFS(x - 1, y, endX, endY)) {
            Maze[x][y].color = GREEN;
            pathLength++;
            return 1;
        }
    }

    // Si aucune direction n'aboutit, on revient en arrière
    Maze[x][y].color = GRAY; // Marque comme "cul-de-sac"
    return 0;
}

int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
Node* FindLowestFCost(Node *openList[], int openCount) {
    Node *lowest = openList[0];
    for (int i = 1; i < openCount; i++) {
        if (openList[i]->fCost < lowest->fCost || 
           (openList[i]->fCost == lowest->fCost && openList[i]->hCost < lowest->hCost)) {
            lowest = openList[i];
        }
    }
    return lowest;
}
int IsInList(Node *list[], int count, int x, int y) {
    for (int i = 0; i < count; i++) {
        if (list[i]->x == x && list[i]->y == y) {
            return 1;
        }
    }
    return 0;
}
int CalculatePathLength(Node *endNode) {
    int length = 0;
    Node *current = endNode;

    // Parcourir le chemin en suivant les parents
    while (current != NULL) {
        length++;
        current = current->parent;
    }

    return length; // Retourne la longueur totale
}

int SolveMazeAStar(int startX, int startY, int endX, int endY) {
    Node *openList[WIDTH * HEIGHT];
    Node *closedList[WIDTH * HEIGHT];
    int openCount = 0, closedCount = 0;

    // Initialisation du nœud de départ
    Node startNode = {startX, startY, 0, Heuristic(startX, startY, endX, endY), 0, NULL};
    startNode.fCost = startNode.gCost + startNode.hCost;
    openList[openCount++] = &startNode;

    while (openCount > 0) {
        // Trouver le nœud avec le coût F le plus bas
        Node *current = FindLowestFCost(openList, openCount);

        // Retirer ce nœud de la liste ouverte et l'ajouter à la liste fermée
        for (int i = 0; i < openCount; i++) {
            if (openList[i] == current) {
                openList[i] = openList[--openCount];
                break;
            }
        }
        closedList[closedCount++] = current;

        // Vérifie si on a atteint la fin
        if (current->x == endX && current->y == endY) {
            pathLength = CalculatePathLength(current);
            // Marque le chemin en vert
            Node *path = current;
            while (path != NULL) {
                Maze[path->x][path->y].color = GREEN;
                path = path->parent;
            }
            Maze[current->x][current->y].color=RED;
            return 1;
        }

        // Exploration des voisins
        int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
        for (int d = 0; d < 4; d++) {
            int nx = current->x + directions[d][0];
            int ny = current->y + directions[d][1];

            // Vérifie si le voisin est dans les limites et s'il n'y a pas de mur
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && 
                !IsInList(closedList, closedCount, nx, ny)) {
                
                // Vérifie les murs en fonction de la direction
                if ((directions[d][0] == 0 && directions[d][1] == -1 && Maze[current->x][current->y].N == 1) || // Nord
                    (directions[d][0] == 1 && directions[d][1] == 0 && Maze[current->x][current->y].E == 1) || // Est
                    (directions[d][0] == 0 && directions[d][1] == 1 && Maze[current->x][current->y].S == 1) || // Sud
                    (directions[d][0] == -1 && directions[d][1] == 0 && Maze[current->x][current->y].W == 1)) { // Ouest
                    continue;
                }

                int gCost = current->gCost + 1;
                int hCost = Heuristic(nx, ny, endX, endY);
                int fCost = gCost + hCost;

                if (!IsInList(openList, openCount, nx, ny)) {
                    // Ajouter le voisin à la liste ouverte
                    Node *neighbor = (Node *)malloc(sizeof(Node));
                    *neighbor = (Node){nx, ny, gCost, hCost, fCost, current};
                    openList[openCount++] = neighbor;
                }
            }
        }
    }

    return 0; // Pas de solution trouvée
}

void DrawTextBelowMaze() {
    int textSize = 20; // Taille du texte
    int textY = offset; 
    int textX = WIDTH * cellSize + 20+offset;

    // Dessiner le texte
    DrawText("C : clear", textX, textY, textSize, BLACK);
    DrawText("R : Refresh end", textX, textY+20, textSize, BLACK);
    DrawText("1 : DFS", textX, textY+40, textSize, BLACK);
    DrawText("2 : A*", textX, textY+60, textSize, BLACK);
    DrawText(timeText, textX, textY+80, textSize, BLACK);
    DrawText( pathLengthText, textX, textY+100, textSize, BLACK);
}
void newEnd(){
    Maze[endX][endY].color=WHITE;
    endX= rand() % WIDTH-1;
    endY=rand() % HEIGHT-1;
    Maze[endX][endY].color=RED;
}
// Programme principal
int main() {
    
    newEnd();

    InitWindow(screenWidth, screenHeight, "Labyrinthe en C");
    SetTargetFPS(60);

    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    InitMaze();
    GenerateMaze(0, 0); // Génération du labyrinthe depuis le coin haut-gauche
    resetCell();

    

    

    while (!WindowShouldClose()) {
        Maze[startX][startY].color = BLUE; // Départ
        Maze[endX][endY].color = RED;     // Arrivée
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawMaze(cellSize, offset);
        DrawTextBelowMaze();
        EndDrawing()
        ;
        if (IsKeyPressed(KEY_ONE)){
            pathLength=1;
            start = clock();
            if (SolveMazeDFS(startX, startY, endX, endY)) {
                printf("Solution trouvée !\n");
                
            } else {
                printf("Aucune solution n'existe !\n");
            }
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            }
           
        if (IsKeyPressed(KEY_TWO)){
            start = clock();
            if (SolveMazeAStar(startX, startY, endX, endY)) {
                printf("Solution trouvée !\n");
            } else {
                printf("Aucune solution n'existe !\n");
            }
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            }
            
         if (IsKeyPressed(KEY_C)) resetCell();

         if(IsKeyPressed(KEY_R)){
            newEnd();
            resetCell();
         }

        // Mise à jour du texte affiché
        snprintf(timeText, sizeof(timeText), "Time: %.5f seconds", cpu_time_used);
        snprintf(pathLengthText, sizeof(pathLengthText), "Longueur du chemin %d", pathLength);


    }

    CloseWindow();
    return 0;
}
