#include <stdlib.h>
void show_me_two_dim(int *dim_2[], int row, int col){
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            printf("%d ", dim_2[r][c]);
        }
        printf("\n");
    }
}

void show_me_1_dim(int *arr, int len){
    for(int l = 0; l < len; l++){
        printf("%d ", arr[l]);
    }
}

void allocation_two_dim(int *dim_2[], int row, int col){
    for(int r = 0; r < row; r++){
        dim_2[r] = (int*)calloc(col, sizeof(int));
    }
}

void fill_two_dim(int *dim_2[], int row, int col, int data[]){
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            dim_2[r][c] = data[r * col + c];
        }
    }
}