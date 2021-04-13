#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
typedef int bool;

int get_elements(char *message){
    int elements = 0;
    while(true){
        if(message[elements] == NULL) break;
        elements++;
    }
    return elements;
}

char* caesar(char* in, int key, bool encrypt){
    int count = 0;
    int elements = get_elements(in);
    char *message = (char*) calloc(elements, sizeof(char));

    while(true){
        if (in[count] == NULL) break;
        if(encrypt) {
            int num = (int) in[count] + key;
            message[count] = (char)num;
        } else {
            int num = (int)in[count] - key;
            message[count] = (char)num;
        }
        count++;
    }
    return message;
}

void show_me(char* message){
    int elements = get_elements(message);
    for(int i = 0; i < elements; i++){
        printf("%c", message[i]);
    }
    printf("\n");
}

void shuffle(int** in, int rows, int columns, int key[], bool encrypt){
    int key_elements = columns;
    if(key_elements % 2 != 0) key_elements--;
    if(encrypt) {
        for (int k = 0; k < key_elements; k += 2) {
            int src = key[k];
            int dst = key[k + 1];
            printf("%d --> %d\n", src, dst);
            for (int r = 0; r < rows; r++) {
                int temp = in[r][src];
                in[r][src] = in[r][dst];
                in[r][dst] = temp;
            }
        }
    }
    else {
        for (int k = key_elements - 1; k >= 0; k -= 2){
            int src = key[k];
            int dst = key[k - 1];
            printf("%d --> %d\n", src, dst);
            for (int r = 0; r < rows; r++) {
                int temp = in[r][src];
                in[r][src] = in[r][dst];
                in[r][dst] = temp;
            }
        }
    }
}

void showMe2dim(int *x[], int dim1, int dim2){
    for(int i = 0; i < dim1; i++){
        for(int k = 0; k < dim2; k++){
            printf("[%d][%d]: %c, ", i, k, x[i][k]);
        }
        printf("\n");
    }
}

void showMeSource(int *x[], int dim1, int dim2){
    for(int i = 0; i < dim1; i++){
        for(int k = 0; k < dim2; k++){
            printf("%c", x[i][k]);
        }
    }
    printf("\n");
}

int main() {
//    Реализовать шифрование и расшифровку цезаря с передаваемым в функцию сообщением и ключом
//    char* caesar(char* in, int key, bool encrypt)
//    bool encrypt - Если true, то происходит шифрование строки char* in. Если false, то расшифровка
    char *messages[255] = {
        "And the LORD spake unto Moses in the wilderness of Sinai, in the tabernacle of the congregation, on the first day of the second month, in the second year after they were come out of the land of Egypt, saying,",
        "Take ye the sum of all the congregation of the children of Israel, after their families, by the house of their fathers, with the number of their names, every male by their polls",
        "From twenty years old and upward, all that are able to go forth to war in Israel: thou and Aaron shall number them by their armies.",
        "And with you there shall be a man of every tribe; every one head of the house of his fathers.",
    };
    int step = 3;
    char *encrypted;
    char *decrypted;
    for(int i = 0; i < 4; i++){
        encrypted = caesar(messages[i], step, true);
        printf("encrypted message:\t");
        show_me(encrypted);
        decrypted = caesar(encrypted, step, false);
        printf("decrypted message:\t");
        show_me(decrypted);
    }
    free(encrypted);
    free(decrypted);

//    Реализовать шифрование и расшифровку перестановками с передаваемым в функцию сообщением и количеством столбцов
//    char* shuffle(char* in, int key, bool encrypt)
//    bool encrypt - Если true, то происходит шифрование строки char* in. Если false, то расшифровка
    printf("\n");
    int rows = 5;
    char tail_symbol = ' ';
    for(int i = 0; i < 4; i++){
        int elements = get_elements(messages[i]);
        int tail = elements % rows;
        int columns = elements / rows;
        if(tail > 0) columns++;
        // Создаём двумерный массив
        int **map = (int**)malloc(rows * sizeof(int*));
        for(int r = 0; r < rows; r++){
            map[r] = (int*)malloc(columns * sizeof(int));
        }
        // Передаём сообщение в массив
        int mc = 0;
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < columns; c++){
                if(mc >= elements){
                    map[r][c] = tail_symbol;
                }
                else{
                    map[r][c] = messages[i][mc];
                    mc++;
                }
            }
        }
        // Шифруем методом перестановки
        int key[columns];
        for(int c = 0; c < columns; c++){
            key[c] = rand() % (columns - 1);
        }
        shuffle(map, rows, columns, key, true);
        printf("encrypted message:\t");
        showMeSource(map, rows, columns);
        shuffle(map, rows, columns, key, false);
        printf("decrypted message:\t");
        showMeSource(map, rows, columns);
        printf("\n");
    }
    return 0;
}
