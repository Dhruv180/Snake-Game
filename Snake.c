#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>  

int i, j, height = 20, width = 20;
int gameover, score, level;
int x, y, fruitx, fruity, flag;
int tailX[100], tailY[100];
int nTail = 0; // Initial snake length

void setup()
{
    gameover = 0;
    x = height / 2;
    y = width / 2;

    // fruit initial position
    do {
        fruitx = rand() % 20;
    } while (fruitx == 0);

    do {
        fruity = rand() % 20;
    } while (fruity == 0);

    score = 0;
    level = 1;
    nTail = 0; // Reset tail length
}

void draw()
{
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                printf("#");
            else {
                int isTail = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == i && tailY[k] == j) {
                        printf("o");
                        isTail = 1;
                    }
                }
                if (!isTail) {
                    if (i == x && j == y)
                        printf("O");  // Snake head
                    else if (i == fruitx && j == fruity)
                        printf("*"); // Fruit
                    else
                        printf(" "); // Empty space
                }
            }
        }
        printf("\n");
    }

    printf("Score = %d | Level = %d\n", score, level);
    printf("Press X to quit the game\n");
}

void input()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (flag != 2)  // Prevent moving in the opposite direction
                flag = 1;
            break;
        case 's':
            if (flag != 4)
                flag = 2;
            break;
        case 'd':
            if (flag != 1)
                flag = 3;
            break;
        case 'w':
            if (flag != 3)
                flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic()
{
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

    switch (flag) {
    case 1: // Move left
        y--;
        break;
    case 2: // Move down
        x++;
        break;
    case 3: // Move right
        y++;
        break;
    case 4: // Move up
        x--;
        break;
    default:
        break;
    }

    // Check for game over conditions (wall collision or snake collision)
    if (x < 0 || x > height - 1 || y < 0 || y > width - 1)
        gameover = 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;
    }

    // Check if the snake eats the fruit
    if (x == fruitx && y == fruity) {
        while (1) {
            fruitx = rand() % 20;
            if (fruitx != 0)
                break;
        }

        while (1) {
            fruity = rand() % 20;
            if (fruity != 0)
                break;
        }

        score += 10;
        nTail++; // Increase the snake's length

        // Level-up after every 50 points
        if (score % 50 == 0) {
            level++;
        }
    }
}

void restartOrQuit() {
    char choice;
    printf("Game Over! Final Score = %d\n", score);
    printf("Press R to restart or X to quit: ");
    scanf(" %c", &choice);
    if (choice == 'R' || choice == 'r') {
        setup(); 
        while (!gameover) { 
            draw();
            input();
            logic();

           
            int sleepTime = 100 - (level * 10);  
            Sleep(sleepTime);  
        }
    } else if (choice == 'X' || choice == 'x') {
        exit(0);
    }
}

int main()
{
    setup();

    while (!gameover) {
        draw();
        input();
        logic();

        int sleepTime;
        if (level == 1) {
            sleepTime = 200;  // Slower speed at Level 1
        } else {
            sleepTime = 100;  // Normal speed after Level 1
        }

        Sleep(sleepTime);  
    }

    restartOrQuit();

    return 0;
}
