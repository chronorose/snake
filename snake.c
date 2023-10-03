#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int head_x;
    int head_y;
} Snake;

typedef enum {
    UP = 'k',
    DOWN = 'j',
    LEFT = 'h',
    RIGHT = 'l',
} Direction;

unsigned short generate_random_number(int n) {
    srand(time(NULL));
    int r = rand();
    if(r > n) r = r % n;
    return r;
}

int** createMatrix(size_t n, size_t m) {
    int** arr;
    arr = malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++) {
        arr[i] = calloc(m, sizeof(int)); 
    }
    return arr;
}

int** initGame(int n, int m, Snake* snake) {
    initscr();
    raw();
    srand(time(NULL));
    snake->head_y = generate_random_number(n);
    snake->head_x = generate_random_number(m); 
    int** arr = createMatrix(n, m);
    arr[snake->head_y][snake->head_x] = 1;
    return arr;
}

bool update(int n, int m, Snake* snake) {
    char c = getch();
    printw("%c", c);
    refresh();
    switch(c) {
        case UP:
            snake->head_y = snake->head_y - 1;
            break;
        case DOWN:
            snake->head_y = snake->head_y + 1;
            break;
        case RIGHT:
            snake->head_x = snake->head_x + 1;
            break;
        case LEFT:
            snake->head_x = snake->head_x - 1;
            break;
        /* case UP - 32: */
        /*     snake->head_y--; */
        /* case DOWN - 32: */
        /*     snake->head_y++; */
        /* case RIGHT - 32: */
        /*     snake->head_x++; */
        /* case LEFT - 32: */
        /*     snake->head_x--; */
    }
    if(snake->head_x < 0 || snake->head_x > m ||
            snake->head_y < 0 || snake->head_y > n - 1) return true;
    return false;
}

void printGame(int** arr, int n, int m, Snake* snake) {
    clear();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == snake->head_y && j == snake->head_x) arr[i][j] = 1;
            else arr[i][j] = 0;
            printw("%d ", arr[i][j]);
        }
        printw("\n");
    }
    refresh();
}

void renderLoop(int** arr, int n, int m, Snake* snake) {
    printGame(arr, n, m, snake);
    bool gameOver = false;
    while(!gameOver) {
        gameOver = update(n, m, snake);
        printGame(arr, n, m, snake);
    } 
}

int main() {
    int n = 20, m = 20;
    Snake snake;
    int** arr = initGame(n, m, &snake);
    renderLoop(arr, n, m, &snake);
    endwin();
    return 0;
}
