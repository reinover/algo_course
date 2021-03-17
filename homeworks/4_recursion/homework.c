#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIGITS 16

// 1
void represent(int num, int i){
    int k = num >> (DIGITS - i);
    int band = k & 1;
    if(i >= 0){
        represent(num, --i);
    }

    printf("%d", band);
}

// 2
// Рекурсивно, используя свойство чётности степени (то есть, если 
// степень, в которую нужно возвести число, чётная, основание 
// возводится в квадрат, а показатель делится на два, а если степень 
// нечётная - результат умножается на основание, а показатель 
// уменьшается на единицу)
int degree(int num, int deg){
    if(deg == 0) return 1;
    if(deg == 1) return num;
    if(deg %2 != 0)
        return num * degree(num, (deg - 1));
    else{
        num = degree(num, deg / 2);
        return num * num;
    }
}

// 3
#define HEIGHT 8
#define WIDTH 8

int board[HEIGHT][WIDTH];

void annul(){
    for(int i = 0; i < HEIGHT; ++i){
        for(int j = 0; j < WIDTH; ++j){
            board[i][j] = 0;
        }
    }
}

void printBoard(){
    char y[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'j', 'h'};
    int x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    printf("\n ");
    for(int w = 0; w < WIDTH; ++w){
        printf("%3d", x[w]);
    }
    printf("\n\n");

    for(int i = 0; i < HEIGHT; ++i){
        printf("%c", y[i]);
        for(int j = 0; j < WIDTH; ++j){
            if(board[i][j] == 2){
                printf("%2d*", board[i][j]);
                continue;
            }
            printf("%3d", board[i][j]);
        }
        printf("\n");
    }
}

void obstacle(){
    srand(time(NULL));
    for(int h = 0; h < HEIGHT; ++h){
        for(int w = 0; w < WIDTH; ++w){
            if(rand() % 128 <= 64){
                board[h][w] = 1;
            }
        }
    }
}

void entry_point(int *ep){
    for(int h = 0; h < HEIGHT; ++h){
        for(int w = 0; w < WIDTH; ++w){
            if(board[h][w] == 0){
                // printf("board[h][w]: %d", board[h][w]);
                ep[0] = h;
                ep[1] = w;
                break;
            }
        }
    }
}

int is_possible(int x, int y){
    return x >= 0 
    && x < WIDTH 
    && y >= 0 
    && y < HEIGHT 
    && board[y][x] == 0;
}

int possible[8][2] = {
    {-1, 0}, {-1, -1}, {-1, 1}, {1, 0},
    {1, -1}, {1, 1}, {0, -1}, {0, 1}
};

int king_move(int pos_x, int pos_y, int move){
    board[pos_y][pos_x] = move;
    int rec_start = 0;
    int nextX;
    int nextY;
    for(int i = 0; i < 8; ++i){
        nextX = pos_x + possible[i][0];
        nextY = pos_y + possible[i][1];
        if(is_possible(nextX, nextY)){
            rec_start = 1;
            break;
        }
    }
    if(rec_start == 1){
        king_move(nextX, nextY, move + 1);
    }
    return 0;
}

int main(){
    // 1 Рекурсивно из десятичного в двоичный код
    int arr[] = {10, 9, 8, 256, 128, 333};
    for(int i = 0; i < (sizeof(arr) / sizeof(int)); i++){
        printf("%d:\t", arr[i]);
        represent(arr[i], DIGITS);
        printf("\n");
    }
    printf("\n");

    // 2 Возведение числа a в степень b
    int numbers[] = {2, 3, -7};
    int degrees[] = {4, 6, 8, 3, 5};
    for(int n = 0; n < (sizeof(numbers) / sizeof(int)); n++){
        for(int d = 0; d < (sizeof(degrees) / sizeof(int)); d++){
            printf("%d in deg %d == ", numbers[n], degrees[d]);
            int res = degree(numbers[n], degrees[d]);
            printf("%d\n", res);
        }
    }
    printf("\n");

    // 3
    annul();
    // Заполняем доску еденицами в случайном порядке
    obstacle();
    printBoard();
    int ep[2];
    printf("\nКаждый первый ход короля обозначен цифрой 2\n");
    while(1){
        ep[0] = -1;
        // Определяем точку входа, свободную от препятствия
        entry_point(ep);
        if(ep[0] == -1){
            break;
        }
        king_move(ep[1], ep[0], 2);
        // Выводим доску после создания очередного маршрута
        // Каждый первый ход короля обозначен цифрой 2
        printBoard();
    }

    return 0;
}