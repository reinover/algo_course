#include <stdio.h>

int is_simple(int num){
    if(num <= 1){
        return 0;
    }

    int divider = 2;
    int simple = 1;
    do{
        if((num % divider == 0) & (divider < num)){
            simple = 0;
            break;
        }
        divider++;
    }while(divider < num);

    return simple;
}

int main(){
    int numbers[11] = {1, 2, 3, 4, 5, 6, 7, 47, 149, 150, 151};
    
    for(int i = 0; i < (sizeof(numbers) / sizeof(int)); i++){
        int result = is_simple(numbers[i]);
    
        printf("%d", numbers[i]);
        (result == 1) ? printf("\t") : printf("\tне ");
        printf("простое число.\n");
    }
    return 0;
}