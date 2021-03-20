#include <stdio.h>
#include "two_dim_array.h"
#include <math.h>

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void bubble_sort(int *arr, int len){
    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len - 1; ++j){
            if(arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int *two_dim_to_one(int *dim_2[], int row, int col){
    int *one_dim= (int*)calloc(row * col, sizeof(int));
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            one_dim[r * col + c] = dim_2[r][c];
        }
    }
    return one_dim;
}

int **one_dim_to_two(int *arr, int row, int col){
    int **two_dim = (int**)calloc(row, sizeof(int));
    for(int r = 0; r < row; r++){
        two_dim[r] = (int*)calloc(col, sizeof(int));
    }

    int current_row = 0;
    int current_col = 0;
    for(int i = 0; i < (row * col); i++){
        if(i != 0 && i != 1 && i % row == 0) {
            current_row++;
            current_col = 0;
        }
//        printf("%d ", current_col);
        two_dim[current_row][current_col] = arr[i];
        current_col++;
    }
    return two_dim;
}

double function(double num){
    return sqrt(fabs(num)) + 5 * pow(num, 3);
}

int main() {
    // 1 Пузырьковая сортировка двумерного массива
    printf("==== 1 ====\n");
    int dim1 = 3;
    int dim2 = 3;
    int *input[dim2];
    allocation_two_dim(input, dim1, dim2);
    int data[] = {1, 9, 2, 5, 7, 6, 4, 3, 8};
    fill_two_dim(input, dim1, dim2, data);
    show_me_two_dim(input, dim1, dim2);
    printf("\n");

    int *input_one_dim = two_dim_to_one(input, dim1, dim2);
    bubble_sort(input_one_dim, dim1*dim2);
    int **result = one_dim_to_two(input_one_dim, dim1, dim2);
    show_me_two_dim(result, dim1, dim2);

    // TPK
    printf("\n==== 2 ====\n");
    double in_arr[11] = {1.11, 2.22, 3.33, 4.44, 5.55, 6.66, 7.77, 8.88, 9.99, 10.10, 11.11};

//    printf("\nвведите 11 чисел: \n");
//    double in_arr[11];
//    for(int i = 0; i < 11; i++){
//        scanf("%lf", &in_arr[i]);
//    }

    for(int i = 10; i >= 0; i--){
        double res = function(in_arr[i]);
        if(res > 400) printf("Слишком большое значение.\n");
        else printf("%f\n", res);
    }

    return 0;
}
