#include <stdio.h>
#include <stdlib.h>

void fillIntArray(int *array, const int len, int base){
    for(int l = 0; l < len; ++l){
        array[l] = rand() % base;
    }
}

void printIntArray(int *array, const int len){
    for(int l = 0; l < len; ++l){
        printf("%4d", array[l]);
    }
}

void swapInt(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void qs2(int* s_arr, int first, int last){
    int i = first, j = last, x = s_arr[(first + last) / 2];

    do {
        while (s_arr[i] < x) i++;
        while (s_arr[j] > x) j--;

        if(i <= j) {
            if (s_arr[i] > s_arr[j]) swapInt(&s_arr[i], &s_arr[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        qs2(s_arr, i, last);
    if (first < j)
        qs2(s_arr, first, j);
}

void sortInserts(int *arr, int len){
    int temp, pos;
    for(int i = 1; i < len; ++i){
        temp = arr[i];
        pos = i - 1;
        while(pos >= 0 && arr[pos] > temp){
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = temp;
    }
}

// Быстрая сортировка
void speedSort(int *arr, int len){
    if(len <= 10){
        sortInserts(arr, len);
    }
    else{
        // Нахождение медианы первого, срединного и последнего значений неотсортированного массива
        int middle_index = len / 2;
        int med[3] = {arr[0], arr[middle_index], arr[len - 1]};
        int med_orig[3] = {arr[0], arr[middle_index], arr[len - 1]};
        int med_ind[3] = {0, middle_index, len - 1};

        sortInserts(&med, 3);
        int median_index = -1;
        for(int i = 0; i < 3; i++){
            if(med_orig[i] == med[1]){
                median_index = med_ind[i];
                break;
            }
        }
        // Меняем местами найденный элемент с центральным элементом массива
        int temp = arr[middle_index];
        arr[middle_index] = arr[median_index];
        arr[median_index] = temp;
        // Запускаем Хоара
        qs2(arr, 0, len - 1);
    }
}

// Блочная сортировка + homework mod
void bucketSort(int *arr, int len){
    const int max = len;
    const int b = 10;

    int buckets[b][max+1];
    for(int i = 0; i < b; ++i){
        buckets[i][max] = 0;
    }

    for(int digit = 1; digit < 1000000000; digit*=10){
        int odds[len];
        int odc = 0;
        for(int i = 0; i < max; ++i){
            if(arr[i] % 2 != 0){
                odds[odc] = i;
                odc++;
                continue;
            }

            int d = (arr[i] / digit) % b;
            int counter = buckets[d][max];
            buckets[d][counter] = arr[i];
            counter++;
            buckets[d][max] = counter;
//            buckets[d][buckets[d][max]++] = arr[i];
        }
        int idx = 0;
        for(int i = 0; i < b; ++i){
            for(int j = 0; j < buckets[i][max]; ++j){
                int lock = 0;
                for(int c = 0; c <= odc; c++){
                    if(idx == odds[c]){
                        lock = 1;
                    }
                }
                if(lock == 1) continue;
                arr[idx] = buckets[i][j];
                idx++;
            }
            buckets[i][max] = 0;
        }
    }
}

int main() {
    // 1). Описать в коде улучшенный алгоритм быстрой сортировки - описана в видео "Быстрая Сортировка. Улучшения."
    printf("---- 1 ----\n");
    const int SZ = 100;
    int arr[SZ];
    fillIntArray(arr, SZ, 100);
    printIntArray(arr, SZ);
    printf("\n");
    speedSort(arr, SZ);
    printIntArray(arr, SZ);
    printf("\n\n");

    // 2). Сортировать в массиве целых положительных чисел только чётные числа, нечётные оставив на своих местах при помощи алгоритма блочной сортировки,
    //Пример: массив [0 2 8 3 4 6 5 9 8 2 7 3] превратить в массив [0 2 2 3 4 6 5 9 8 8 7 3]
    //
    //Результатом работы должен стать один файл с кодом на языке С, содержащий функцию main и функции, необходимые для реализации сортировок
    printf("---- 2 ----\n");
    int test_arr[12] = {0, 2, 8, 3, 4, 6, 5, 9, 8, 2, 7, 3};
    bucketSort(&test_arr, 12);
    printIntArray(&test_arr, 12);
    printf("\n");
    return 0;
}