#include "maze_move.h"

bool mouvement = 0;

float time_interval = 0.01;

Robot robot1;
Robot robot2;
int aimX = rand() % (WIDTH - 1);
int aimY = rand() % (HEIGHT - 1);

void InitializeRobots() {
    robot1 = (Robot){startX, startY, 0, 0, YELLOW, NULL,0};
    robot1.start_move=clock();
    robot2 = (Robot){endX, endY, 0, 0, ORANGE, NULL,0};
}
void reset_robot(){
    InitializeRobots();
}

int move_robot1() {
    // Recalculer le chemin à chaque appel en fonction de la position actuelle de robot2
    resetCell(false);  // Réinitialiser les cellules avant de recalculer le chemin
    robot1.aimX = robot2.x;  // Définir la destination comme la position actuelle de robot2
    robot1.aimY = robot2.y;
    robot1.path = SolveMazeDFS(robot1.x, robot1.y, robot1.aimX, robot1.aimY, BLUE);  // Calculer le chemin

    // Vérifier si le chemin a bien été trouvé
    if (!robot1.path) {
        printf("Erreur: Aucun chemin trouvé pour robot1.\n");
        return 4;  // Aucun chemin trouvé
    }

    // Vérifier si l'intervalle de temps est écoulé
    if ((float)(clock() - robot1.start_move) / CLOCKS_PER_SEC >= time_interval) {
        // Si robot1 a atteint sa destination, recalculer un nouveau chemin
        if (robot1.x == robot1.aimX && robot1.y == robot1.aimY) {
            printf("Le robot1 a atteint sa destination.\n");
            robot1.path = NULL;  // Réinitialiser le chemin
            //resetCell(true);
            return 0;  // Arrêter le mouvement
        }

        // Mettre à jour la position du robot en suivant le chemin
        if (robot1.path) {
            

            // Passer au prochain nœud dans le chemin
            PathList* oldPath = robot1.path;
            robot1.path = robot1.path->next;
            free(oldPath);  // Libérer l'ancien nœud
            robot1.x = robot1.path->x;
            robot1.y = robot1.path->y;
            // Redémarrer le timer pour le mouvement
            robot1.start_move = clock();

            printf("Déplacement de robot1 à (%d, %d)\n", robot1.x, robot1.y);
            return 1;  // Le robot continue de se déplacer
        }
    }

    return 3;  // L'intervalle de temps n'est pas encore écoulé
}



int move_robot2() {
    if (!robot2.path) {
        resetCell(true);
        robot2.aimX = rand() % (HEIGHT - 1);
        robot2.aimY = rand() % (WIDTH - 1);
        robot2.path = SolveMazeDFS(robot2.x, robot2.y, robot2.aimX, robot2.aimY,BROWN);
        PrintPath(robot2.path);
        robot2.start_move = clock();
        return 2;
    }
    else {
        // Vérifie si l'intervalle de temps est écoulé
        if ((float)(clock() - robot2.start_move) / CLOCKS_PER_SEC >= time_interval) {
            // Mettre à jour la position
            if(robot2.x == robot2.aimX && robot2.y == robot2.aimY && robot2.path!=NULL){
                 printf("Le robot2 a atteint sa destination.\n");
                 resetCell(true);
                 robot2.path=NULL;
                 return 0;
            }
            robot2.x = robot2.path->x;
            robot2.y = robot2.path->y;

            // Passer au prochain nœud dans le chemin
            PathList* oldPath = robot2.path;
            robot2.path = robot2.path->next;
            free(oldPath); // Libérer l'ancien nœud

            // Redémarrer le timer
            robot2.start_move = clock();

            return 1;
        }
        return 3;
    }
    return 4;
}