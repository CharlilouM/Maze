#include "maze_print.h"
#include "maze_solve.h"

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
        Maze[startX][startY].color = GREEN; // Départ
        Maze[endX][endY].color = RED;     // Arrivée
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawMaze(cellSize, offset);
        DrawTextBelowMaze();
        EndDrawing()
        ;
        if (IsKeyPressed(KEY_ONE)){
            resetCell();
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
        if (IsKeyPressed(KEY_THREE)){
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
         if (IsKeyPressed(KEY_A)){
            mouvement!=mouvement;
            if (mouvement){
                move();
            }
         }
            

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
