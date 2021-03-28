#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SZ 10

#define T char
#define TRUE 1 == 1
#define FALSE 1 != 1
#define SIZE 20
#define DIGITS 8

void represent(int, char*);

// 1
typedef struct {
    int pr;
    int dat;
} Node;

Node *arr[SZ];
int head;
int tail;
int items;

void init(){
    for(int i = 0; i < SZ; ++i){
        arr[i] = NULL;
    }
    head = 0;
    tail = 0;
    items = 0;
}

void exclusion_ins(int pr, int dat){
    Node *node = (Node*) malloc(sizeof(Node));
    node->dat = dat;
    node->pr = pr;

    ++tail;
    for(int i = head; i < tail; ++i){
        arr[i] = node;
        ++head;
    }
    items++;
}

Node* exclusion_rem(){
    if(items == 0){
        return NULL;
    } else {
        int idx = -1;
        int max_pr = 0;
        for(int i = tail - 1; i >= 0; --i){
            if(arr[i] == NULL) continue;
            if(arr[i]->pr > max_pr) {
                max_pr = arr[i]->pr;
                idx = i;
            }
        }
        Node *tmp = arr[idx];
        arr[idx] = NULL;
        items--;
        return tmp;
    }
    // Находим наивысший приоритет
    // Возвращаем его
}

void printQueue(){
    printf("[ ");
    for(int i = 0; i < SZ; ++i){
        if(arr[i] == NULL){
            printf("[*, *] ");
        } else {
            printf("[%d, %d] ", arr[i]->pr, arr[i]->dat);
        }
    }
    printf("]\n");
}

// 2
typedef int boolean;
int cursor = -1;
T *Stack[SIZE];

boolean PushStack(int decimal){
    T *res = (char*)malloc(DIGITS * sizeof(char));
    represent(decimal, res);
    if(cursor < SIZE){
        Stack[++cursor] = res;
        return TRUE;
    } else{
        printf("Stack overflow\n");
        return FALSE;
    }
}

T *PopStack(){
    if(cursor != -1){
        return Stack[cursor--];
    } else {
        printf("Stack is empty\n");
        return NULL;
    }
}

void represent(int num, T *out){
    char bstring[DIGITS] = {0};
    for(int i = (DIGITS - 1); i >= 0; i --){
        // num = 134
        // num = 0000000010000110 >> 15
        // num = 0000000000000000.0000000010000110
        // k & 1 == 0000000000000000 & 0000000000000001 == 0
        // ...
        // num = 0000000010000110 >> 9 == 0000000000000001
        // k & 1 == 0000000000000001 & 0000000000000001 == 1
        // num = 0000000010000110 >> 3 == 0000000000010000
        // k & 1 == 0000000000010000 & 0000000000000001 == 0
        // num = 0000000010000110 >> 2 == 0000000000100001
        // k & 1 == 0000000000100001 & 0000000000000001 == 1

        // Хитрость в том, что все выражения раскладывается на двоичный код
        // и только затем выполняются бинарные операции
        int k = num >> i;
        int band = k & 1;
        strcat(bstring, (band == 1) ? "1" : "0");
    }
    strcpy(out, bstring);
}


int main() {
    /*
Описать очередь с приоритетным исключением
Указание: См. видео 9.4 Приоритетная и двусторонняя очередь.
В видео рассказано о двух типах очереди с приоритетами -
- С приоритетным исключением. В данном случае элемент вставляется как и в обычной очереди - в конец,
     а когда элемент удаляется, то выбирается тот, что имеет наивысший приоритет.
- С приоритетным включением. В данном случае элемент вставляется сразу на место согласно своему приоритету
     (чем выше приоритет, тем ближе к началу), а удаляется элемент также как и в обычной очереди - тот что стоит в начале.
В видео показана реализация очереди с приоритетным включением, вам же надо реализовать очередь с приоритиным исключением.
Подсказка: Вам понадобится -
a) структура Node из урока
b) функция void Init() - Данная функция инициализирует значения.
c) void insert(int pr, int dat) - Данная функция вставляет элемент c приоритетом pr и значением dat в очередь.
d) Node* rem() - Данная функция удаляет элемент из очереди и возвращает указатель на него.
     */
    init();
    exclusion_ins(1, 11);
    exclusion_ins(3, 22);
    exclusion_ins(4, 33);
    exclusion_ins(2, 44);
    exclusion_ins(3, 55);
    exclusion_ins(4, 66);
    exclusion_ins(5, 77);
    exclusion_ins(1, 88);
    exclusion_ins(7, 99);
    exclusion_ins(6, 100);
    printQueue();
    for(int i = 0; i < 5; ++i){
        Node *n = exclusion_rem();
        if(n == NULL) break;
        printf("pr=%d, dat=%d\n", n->pr, n->dat);
    }
    printQueue();
    printf("\n\n");
    /*
Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
Входные данные: число в десятичной системе счисления.
Выходные данные: двоичное представление числа, выведенное в консоль
Примеры:
25 - 11001
15 - 1111
Указание: реализуйте структуру данных Стек и напишите две функции PushStack(...) и PopStack(...).
Стек разбирается в видео "Создание стека с использованием массива".
Результатом работы должен стать один файл с кодом на языке С, содержащий функцию main,
а также функции, необходимые для работы приоритетной очереди и перевода систем счисления
     */
    int steps = 5;
    int decimals[] = {25, 128, 4, 44, 199};
    for(int i = 0; i < steps; i++){
        PushStack(decimals[i]);
    }
    for(int i = --steps; i >= 0; i--){
        T *res = PopStack();
        if(res == NULL) return 0;
        printf("%d\t- ", decimals[i]);
        puts(res);
    }
    return 0;
}
