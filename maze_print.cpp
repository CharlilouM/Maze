#include "maze_print.h"


// Initialisation des variables
const int screenWidth = 1920 * 0.75;
const int screenHeight = 1080 * 0.75;
int startX = 0;
int startY = 0;
int endX = 0;
int endY = 0;
int BombeNumber=5;

int pathLength = 0;
int wall = 2;
const int offset = 20;

const int cellSize =(screenHeight-2*offset)/HEIGHT ;

Cell Maze[WIDTH][HEIGHT];
int directions[4][2] = {
    {0, -1}, // Nord
    {1, 0},  // Est
    {0, 1},  // Sud
    {-1, 0}  // Ouest
};

// Fonction pour initialiser le labyrinthe
void InitMaze() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Maze[i][j] = (Cell){i, j, 1, 1, 1, 1,false, WHITE, 0}; // Tout est mur au départ
        }
    }

}
void InitBomb(){
    for (int k=0;k<BombeNumber;k++){
        int x= rand() % WIDTH-1;
        int y=rand() % HEIGHT-1;
        Maze[x][y].bombe=true;
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
void resetCell(bool color){
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Maze[i][j].visited=0;
            if (color) Maze[i][j].color=WHITE;
            }
    }
    
    //Maze[startX][startY].color = GREEN; // Départ
    //Maze[endX][endY].color = RED;     // Arrivée
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
            
            if (cell.bombe) DrawCircle(x +cellSize/2,y+cellSize/2,cellSize*0.35,BLACK);

        }
    }
    DrawCircle(robot1.x * cellSize + offset +cellSize/2,robot1.y* cellSize + offset+cellSize/2,cellSize*0.35,robot1.color);
    DrawCircle(robot2.x * cellSize + offset+cellSize/2,robot2.y* cellSize + offset+cellSize/2,cellSize*0.35,robot2.color);
    Maze[robot1.aimX][robot1.aimY].color = PURPLE;
    Maze[robot2.aimX][robot2.aimY].color = RED;
}




void DrawTextBelowMaze() {
    int textSize = 20; // Taille du texte
    int textY = offset; 
    int textX = WIDTH * cellSize + 20+offset;

    // Dessiner le texte
    DrawText("E : Enable movement of 2", textX, textY, textSize, BLACK);
    DrawText("C : Clean path", textX, textY+20, textSize, BLACK);
    DrawText("R : Refresh end", textX, textY+40, textSize, BLACK);
    DrawText("1 : DFS", textX, textY+60, textSize, BLACK);
    DrawText("2 : BFS", textX, textY+80, textSize, BLACK);
    DrawText("3 : A*", textX, textY+100, textSize, BLACK);
    DrawText(TextFormat("Start : %d;%d | End %d;%d",startX,startY,endX,endY), textX, textY+120, textSize, BLACK);
    DrawText(timeText, textX, textY+140, textSize, BLACK);
    DrawText( pathLengthText, textX, textY+160, textSize, BLACK);
    DrawText(TextFormat("S : Skip Bomb = %d",(bool)SkipBomb), textX, textY+180, textSize, BLACK);
}
void newEnd(){
    Maze[endX][endY].color=WHITE;
    endX= rand() % WIDTH-1;
    endY=rand() % HEIGHT-1;
    Maze[endX][endY].color=RED;
}


void AnimPath(){
    // déplacer le carré bleu tout les X temps selon le Path
    
}
