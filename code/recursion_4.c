#include <stdio.h>

void rec(int a){
	printf("%5d", a);
	if(a > 0)
		rec(a - 1);
}

int sumDigitsInteractive(int num){
	int sum = 0;
	while(num > 0){
		sum += num % 10;
		num /= 10;
	}
	return sum;
}

int sumDigitsRecursive(int num){
	if(num > 0){
		return num % 10 + sumDigitsRecursive(num / 10);
	} else {
		return 0;
	}
}

int main(){
	rec(10);
	printf("\n %d \n", sumDigitsInteractive(12349));
	printf("%d \n", sumDigitsRecursive(123456));
	return 0;
}
