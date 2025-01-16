#include "maze_print.h"
#include "maze_solve.h"
#include "maze_move.h"

// Programme principal
int main() {
    bool EnableRobot2Movement=true;
    newEnd();
    InitializeRobots();
    InitWindow(screenWidth, screenHeight, "Labyrinthe en C");
    SetTargetFPS(60);

    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    InitMaze();
    GenerateMaze(0, 0); // Génération du labyrinthe depuis le coin haut-gauche
    resetCell();

    

    

    while (!WindowShouldClose()) {
        // Maze[startX][startY].color = GREEN; // Départ
        // Maze[endX][endY].color = RED;     // Arrivée
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawMaze(cellSize, offset);
        DrawTextBelowMaze();
        EndDrawing()
        ;
        if (IsKeyPressed(KEY_ONE)){
            resetCell();
            pathLength=1;
            pathList = NULL;
            start = clock();
            PathList* path = SolveMazeDFS(startX, startY, endX, endY,BLUE);
            PrintPath(path);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            }
           
        if (IsKeyPressed(KEY_TWO)){
            resetCell();
            pathLength=0;
            pathList = NULL;
            start = clock();
            if (SolveMazeAStar(startX, startY, endX, endY)) {
                printf("Solution trouvée !\n");
            } else {
                printf("Aucune solution n'existe !\n");
            }
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            }
        if (IsKeyPressed(KEY_THREE)){
            pathLength=1;
            pathList = NULL;
            resetCell();
            start = clock();
            if (SolveMazeAStar(startX, startY, endX, endY)) {
                printf("Solution trouvée !\n");
            } else {
                printf("Aucune solution n'existe !\n");
            }
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            } 
         if (IsKeyPressed(KEY_E)){
            mouvement = !mouvement; 
         }
        if (mouvement){
            move_robot1();//active mouvement de la cible
            if (EnableRobot2Movement)  move_robot2();
        }
        else reset_robot();

         if(IsKeyPressed(KEY_R)){
            newEnd();
            resetCell();
         }
         if(IsKeyPressed(KEY_C)){ 
            resetCell();
         }
         if(IsKeyPressed(KEY_SPACE)){ 
            AnimPath();
         }

        // Mise à jour du texte affiché
        snprintf(timeText, sizeof(timeText), "Time: %.5f seconds", cpu_time_used);
        snprintf(pathLengthText, sizeof(pathLengthText), "Longueur du chemin %d", pathLength);


    }

    CloseWindow();
    return 0;
}
