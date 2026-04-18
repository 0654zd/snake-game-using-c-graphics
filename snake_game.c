#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<dos.h>

int x, y;
int sx = 0, snakex[3072] = {0};
int sy = 0, snakey[3072] = {0};
int length = 1;
char direction = 'd'; // default: moving right
int score = 0;

int screenW, screenH;

void coordinates() {
    int temp_x, temp_y;
    int i;
    int valid = 0;
    srand(time(0));

    while (!valid) {
	temp_x = (rand() % (screenW / 10)) * 10;  
        temp_y = (rand() % (screenH / 10)) * 10;
        valid = 1;
        for (i = 0; i < length; i++) {
            if (snakex[i] == temp_x && snakey[i] == temp_y) {
                valid = 0;
                break;
            }
        }
    }
    x = temp_x;
    y = temp_y;
}

void drawSnake() {
    int i;
    setcolor(GREEN);
    for (i = 0; i < length; i++) {
        rectangle(snakex[i], snakey[i], snakex[i] + 9, snakey[i] + 9);
    }
}

void drawFood() {
    setcolor(RED);
    rectangle(x, y, x + 9, y + 9);
    floodfill(x + 5, y + 5, RED);  

void drawBorder() {
    setcolor(WHITE);
    rectangle(0, 0, screenW - 1, screenH - 1);
}

void showScore() {
    char buf[30];
    setcolor(YELLOW);
    sprintf(buf, "Score: %d", score);
    outtextxy(10, screenH + 5, buf);
}

int checkCollision() {
    int i;
    int hx = snakex[0];
    int hy = snakey[0];

    // Wall collision
    if (hx < 0 || hx + 9 >= screenW || hy < 0 || hy + 9 >= screenH)
        return 1;

    // Self collision
    for (i = 1; i < length; i++) {
        if (snakex[i] == hx && snakey[i] == hy)
            return 1;
    }
    return 0;
}

void moveSnake() {
    int i;

    
    for (i = length - 1; i > 0; i--) {
        snakex[i] = snakex[i - 1];
        snakey[i] = snakey[i - 1];
    }

    //  head moves based on direction
    // a=left, d=right, w=up, s=down 
    if (direction == 'd') snakex[0] += 10;       // right
    else if (direction == 'a') snakex[0] -= 10;  // left
    else if (direction == 'w') snakey[0] -= 10;  // up
    else if (direction == 's') snakey[0] += 10;  // down
}

void gameOver() {
    char buf[50];
    cleardevice();
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(screenW / 2 - 80, screenH / 2 - 40, "GAME OVER");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    sprintf(buf, "Final Score: %d", score);
    outtextxy(screenW / 2 - 60, screenH / 2 + 10, buf);
    outtextxy(screenW / 2 - 80, screenH / 2 + 30, "Press any key to exit.");
    getch();
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");  
    screenW = getmaxx() + 1;
    screenH = getmaxy() - 20;  

    
    screenW = (screenW / 10) * 10;
    screenH = (screenH / 10) * 10;

    // Initializing snake at center, 1 pixel (10x10 block)
    snakex[0] = (screenW / 2 / 10) * 10;
    snakey[0] = (screenH / 2 / 10) * 10;
    length = 1;

    // Place first food
    coordinates();

    while (1) {
        // Input handling (non-blocking)
        if (kbhit()) {
            char key = getch();
            if (key == 'a' && direction != 'd') direction = 'a';  // left  (can't reverse)
            else if (key == 'd' && direction != 'a') direction = 'd';  // right
            else if (key == 'w' && direction != 's') direction = 'w';  // up
            else if (key == 's' && direction != 'w') direction = 's';  // down
        }

        // Move
        moveSnake();

        // Check collisions
        if (checkCollision()) {
            gameOver();
            break;
        }

        // Check if food eaten 
        if (snakex[0] == x && snakey[0] == y) {
            length++;          // grow snake
            score += 10;
            coordinates();     // new food position
        }

        
        cleardevice();
        drawBorder();
        drawFood();
        drawSnake();
        showScore();

        delay(150);  
    }

    closegraph();
    return 0;
}
