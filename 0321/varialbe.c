#include<stdio.h>
int fact(int n);
int global = 10;

int main(){
	int a = 4, b;
	b = fact(a);
	printf("b=%d", b);
	global += b;
}
int fact(int n){
	int result = 1;
	for(int i = 1; i < n; ++i)
		result *= i;
	return result;
}

