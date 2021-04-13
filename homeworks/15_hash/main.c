#include <stdio.h>
#include <stdlib.h>

int simpleHashSum(char *in){
    int sum = 0;
    for(int i = 0; i < 255; i++){
        if(in[i] == NULL) break;
        sum += (int)in[i];
    }
    return sum;
}

int* exchange(int* money, int size, int sum){
    int *count = (int*) calloc(size, sizeof(int));
    for(int i = 0; i < size; i++){
        count[i] = sum / money[i];
        sum %= money[i];
        if(sum == 0) break;
    }
    return count;
}

int main() {
    // Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
    // int simpleHashSum(char* in)
    char *strings[255] = {"Do you like what you see?",
                             "I'm hired for people to fulfill their fantasies, their big data fantasies",
                             "parsing is 300 bucks"};
    for(int i = 0; i < 3; i++){
        int hash = simpleHashSum(strings[i]);
        printf("hash:\t%d\n", hash);
    }
    printf("\n");

    //  Имеются монеты номиналом 50, 10, 5, 2, 1 коп. Напишите функцию которая минимальным количеством монет наберет сумму 98 коп.
    //  Для решения задачи используйте “жадный” алгоритм.
    //  int* exchange(int* money, int size, int sum)
    //
    //  Входные параметры:
    //  int* money - Массив с доступными номиналами монет размером size. Например: int money[] = {50, 10, 5, 2, 1};, size = 5.
    //
    //  Выходные параметры:
    //  Можно просто вывести необходимые монеты в консоль, либо вернуть указатель int* на массив,
    //  в котором первый элемент будет хранить его размер.
    //
    //  Считается что монет каждого номинала у нас неограниченное количество.
    int size = 5;
    // Номиналы монет в массиве должны быть расположены от большего к меньшему, иначе программа не будет верно работать.
    int money[] = {50, 10, 5, 2, 1};
    int sum = 97;
    int *result = exchange(money, size, sum);
    printf("amount %d consists of:\n", sum);
    for(int r = 0; r < size; r++){
        printf("\tdenomination: %4d\tamount: %d\n", money[r], result[r]);
    }
    free(result);
    return 0;
}
