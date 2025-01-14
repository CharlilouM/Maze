#include "maze_solve.h"
#include "maze_print.h" // Inclure le fichier d'affichage



clock_t start, end;
double cpu_time_used;
char timeText[50];
char pathLengthText[50];

PathList* pathList = NULL;



int SolveMazeDFS(int x, int y, int endX, int endY) {
    // Vérifie si nous avons atteint la cellule d'arrivée
    if (x == endX && y == endY) {
        //Maze[x][y].color = BLUE; // Colorie le chemin trouvé
        return 1; // Solution trouvée
    }

    // Marquer la cellule comme visitée
    Maze[x][y].visited = 1;
    Maze[x][y].color = YELLOW; // Marque la cellule sur le chemin en exploration

    // Explorer les directions : Nord, Sud, Est, Ouest
    if (Maze[x][y].N == 0 && !Maze[x][y - 1].visited) { // Nord
        if (SolveMazeDFS(x, y - 1, endX, endY)) {
            Maze[x][y].color = BLUE; // Marquer le chemin
            pathLength++;
            return 1;
        }
    }
    if (Maze[x][y].S == 0 && !Maze[x][y + 1].visited) { // Sud
        if (SolveMazeDFS(x, y + 1, endX, endY)) {
            Maze[x][y].color = BLUE;
            pathLength++;
            return 1;
        }
    }
    if (Maze[x][y].E == 0 && !Maze[x + 1][y].visited) { // Est
        if (SolveMazeDFS(x + 1, y, endX, endY)) {
            Maze[x][y].color = BLUE;
            pathLength++;
            return 1;
        }
    }
    if (Maze[x][y].W == 0 && !Maze[x - 1][y].visited) { // Ouest
        if (SolveMazeDFS(x - 1, y, endX, endY)) {
            Maze[x][y].color = BLUE;
            pathLength++;
            return 1;
        }
    }

    // Si aucune direction n'aboutit, on revient en arrière
    Maze[x][y].color = GRAY; // Marque comme "cul-de-sac"
    return 0;
}


void enqueue(Queue **queue, int x, int y) {
    Queue *newNode = (Queue *)malloc(sizeof(Queue));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    
    if (*queue == NULL) {
        *queue = newNode;
    } else {
        Queue *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Queue* dequeue(Queue **queue) {
    if (*queue == NULL) return NULL;

    Queue *temp = *queue;
    *queue = (*queue)->next;
    return temp;
}

int SolveMazeBFS(int startX, int startY, int endX, int endY) {
    Queue *queue = NULL;
    enqueue(&queue, startX, startY);
    Maze[startX][startY].visited = 1;
    Maze[startX][startY].color = BLUE;

    //int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    while (queue) {
        Queue *current = dequeue(&queue);
        int x = current->x;
        int y = current->y;
        free(current);

        if (x == endX && y == endY) {
            // Reconstruct the path
            pathLength = 0;
            while (Maze[x][y].parent != NULL) {
                Maze[x][y].color = BLUE;
                x = Maze[x][y].parent->i;
                y = Maze[x][y].parent->j;
                pathLength++;
            }
            Maze[x][y].color = BLUE;
            return 1;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && !Maze[nx][ny].visited && 
                (Maze[x][y].N == 0 || Maze[x][y].E == 0 || Maze[x][y].S == 0 || Maze[x][y].W == 0)) {
                Maze[nx][ny].visited = 1;
                Maze[nx][ny].parent = &Maze[x][y];
                enqueue(&queue, nx, ny);
            }
        }
    }
    return 0; // Pas de solution
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
// Fonction pour ajouter une coordonnée à la liste du chemin
void AddToPathList(PathList** pathList, int x, int y) {
    // Crée un nouveau nœud pour la liste
    PathList* newNode = (PathList*)malloc(sizeof(PathList));
    newNode->x = x;
    newNode->y = y;
    newNode->next = *pathList;  // Le nouveau nœud pointe vers l'ancien début de liste
    *pathList = newNode;        // Le pointeur de la liste pointe maintenant vers ce nouveau nœud
}
// Fonction pour afficher le chemin parcouru
void PrintPath(PathList* pathList) {
    while (pathList != NULL) {
        printf("(%d, %d) -> ", pathList->x, pathList->y);
        pathList = pathList->next;
    }
    printf("End\n");
}
int CalculatePathLength(Node* endNode, PathList** pathList) {
    int length = 0;
    Node* current = endNode;

    // Parcourir le chemin en suivant les parents et ajouter les coordonnées à la liste
    while (current != NULL) {
        AddToPathList(pathList, current->x, current->y);  // Ajouter les coordonnées du nœud
        length++;
        current = current->parent;
    }
    // Afficher le chemin une fois qu'il est construit
    PrintPath(*pathList);
    return length;  // Retourner la longueur totale du chemin
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
            pathLength = CalculatePathLength(current, &pathList);
            // Marque le chemin en vert
            Node *path = current;
            while (path != NULL) {
                Maze[path->x][path->y].color = BLUE;
                path = path->parent;
            }
            Maze[current->x][current->y].color=RED;
            return 1;
        }

        // Exploration des voisins
        //int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
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