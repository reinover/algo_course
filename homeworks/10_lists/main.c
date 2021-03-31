#include <stdio.h>
#include <stdlib.h>
#define true 1 == 1
#define false 1 != 1

typedef int boolean;

// 1
char couple(char symbol){
    if(symbol == '(') return ')';
    if(symbol == ')') return '(';
    if(symbol == '[') return ']';
    if(symbol == ']') return '[';
    if(symbol == '{') return '}';
    if(symbol == '}') return '{';
    return '#';
}

typedef struct Node{
    char element;
    char couple;
    boolean checked;
    int id;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} List;

void init(List *lst){
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
}

void pushBack(List *lst, char element, int id){
    Node *new = (Node*)malloc(sizeof(Node));
    new->element = element;
    new->couple = couple(element);
    new->checked = false;
    new->next = NULL;
    new->id = id;
    new->prev = lst->tail;
    if(lst->tail != NULL){
        lst->tail->next = new;
    }
    if(lst->head == NULL){
        lst->head = new;
    }
    lst->tail = new;
    lst->size++;
}

void printNode(Node *n){
    if(n == NULL){
        printf("[]");
        return;
    }
    printf("%c", n->element);
}

void printList(List *lst){
    Node *current = lst->head;
    if(current == NULL){
        printNode(current);
    } else {
        do {
            printNode(current);
            current = current->next;
        } while(current != NULL);
    }
    printf(" Size: %d \n", lst->size);
}

boolean walkLeftToRight(List *lst, char target, int id){
    Node *current = lst->head;
    while(current != NULL){
        if(current->couple == target && id < current->id && !current->checked){
            current->checked = true;
            return true;
        }
        current = current->next;
    }
    return false;
}

boolean walkRightToLeft(List *lst, char target, int id){
    Node *current = lst->tail;
    while(current != NULL){
        if(current->couple == target && id > current->id && !current->checked){
            current->checked = true;
            return true;
        }
        current = current->prev;
    }
    return false;
}

// 2
typedef struct OneListNode {
    int dat;
    struct OneListNode *next;
} OneListNode;

typedef struct {
    OneListNode *head;
    int size;
} OneList;

void OneListInit(OneList *lst){
    lst->head = NULL;
    lst->size = 0;
}

void ins(OneList *lst, int data){
    OneListNode *new = (OneListNode*) malloc(sizeof(OneListNode));
    new->dat = data;
    new->next = NULL;

    OneListNode *current = lst->head;
    if(current == NULL){
        lst->head = new;
        lst->size++;
    } else {
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new;
        lst->size++;
    }
}

void printOneListNode(OneListNode *n){
    if(n == NULL){
        printf("[]");
        return;
    }
    printf("[%d] ", n->dat);
}

void printOneListList(OneList *lst){
    OneListNode *current = lst->head;
    if(current == NULL){
        printOneListNode(current);
    } else {
        do{
            printOneListNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", lst->size);
}

void copyOneList(OneList *lst_source, OneList *lst_dest){
    OneListNode *source = lst_source->head;
    if(source == NULL) return;

    do{
        ins(lst_dest, source->dat);
        source = source->next;
    } while(source != NULL);
}

// 3
// Проверяет отсортирован ли список положительных чисел в порядке возрастания
boolean isIntSorted(OneList *lst){
    OneListNode *list = lst->head;
    if(list == NULL) return false;

    int max = 0;
    do{
        if(list->dat >= max) max = list->dat;
        else return false;
        list = list->next;
    } while(list != NULL);

    return true;
}

int main(){
    // 1
    List *lst = (List*)malloc(sizeof(List));
    init(lst);
    printList(lst);

//    char formula[] = {'[', '(', '5', '*', '8', ')', ']'};
//    (2+(2*2))
//    char formula[] = {'(', '2', '+', '(', '2', '*', '2', ')', ')'};
//    {2/{5*(4+7)]
    char formula[] = {'{', '2', '/', '{', '5', '*', '(', '4', '+', '7', ')', ']'};

    // Наполняем список данными
    for(int i = 0; i < (sizeof(formula) / sizeof(char)); i++){
        pushBack(lst, formula[i], i);
    }
    printList(lst);
    // ходим по списку вправо и влево
    int LtR_count = 0;
    int RtL_count = 0;
    boolean status = true;
    for(int i = 0; i < (sizeof(formula) / sizeof(char)); i++){
        if(couple(formula[i]) != '#'){
            if(walkLeftToRight(lst, formula[i], i)) LtR_count++;
            if(walkRightToLeft(lst, formula[i], i)) RtL_count++;
            if(LtR_count == 0 && RtL_count == 0){
                status = false;
                break;
            }
            LtR_count = 0; RtL_count = 0;
        }
    }
    if(status) printf("формула верна\n");
    else printf("формула не верна\n");

    // 2
    printf("\n---- 2 ----\n\n");
    OneList *list = (OneList*) malloc(sizeof(OneList));
    OneListInit(list);
    ins(list, 1);
    ins(list, 10);
    ins(list, 11);
    ins(list, 10);
    printOneListList(list);

    OneList *dest_list = (OneList*) malloc(sizeof(OneList));
    copyOneList(list, dest_list);
    printOneListList(dest_list);

    // 3
    printf("\n---- 3 ----\n\n");
    if(isIntSorted(dest_list))
        printf("список отсортирован\n");
    else
        printf("список не отсортирован\n");

    free(lst);
    free(list);
    free(dest_list);

    return 0;
}