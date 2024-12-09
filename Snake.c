#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int i, j, height = 20, width = 20;
int gameover, score, level;
int x, y, fruitx, fruity;
int tailX[100], tailY[100];
int nTail = 0;
char direction; 

void setup() {
    gameover = 0;
    x = height / 2;
    y = width / 2;

    fruitx = rand() % (height - 2) + 1;
    fruity = rand() % (width - 2) + 1;

    score = 0;
    level = 1;
    nTail = 0;
    direction = 'd'; // Default direction is right
}

void draw() {
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("#");
            } else if (i == x && j == y) {
                printf("O");
            } else if (i == fruitx && j == fruity) {
                printf("*");
            } else {
                int printed = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == i && tailY[k] == j) {
                        printf("o");
                        printed = 1;
                    }
                }
                if (!printed) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d | Level: %d\n", score, level);
    printf("Press 'X' to exit.\n");
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'a': if (direction != 'd') direction = 'a'; break; // Left
            case 's': if (direction != 'w') direction = 's'; break; // Down
            case 'd': if (direction != 'a') direction = 'd'; break; // Right
            case 'w': if (direction != 's') direction = 'w'; break; // Up
            case 'x': gameover = 1; break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case 'a': y--; break; // Left
        case 's': x++; break; // Down
        case 'd': y++; break; // Right
        case 'w': x--; break; // Up
    }

    if (x <= 0 || x >= height - 1 || y <= 0 || y >= width - 1) {
        gameover = 1;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameover = 1;
        }
    }

    if (x == fruitx && y == fruity) {
        fruitx = rand() % (height - 2) + 1;
        fruity = rand() % (width - 2) + 1;
        score += 10;
        nTail++;
        if (score % 50 == 0) level++;
    }
}

void restartOrQuit() {
    printf("Game Over! Final Score: %d\n", score);
    printf("Press 'R' to restart or 'X' to exit: ");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'r' || choice == 'R') {
        setup();
    } else {
        exit(0);
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(200 - (level * 10)); 
    }
    restartOrQuit();
    return 0;
}
