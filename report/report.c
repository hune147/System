#include <stdio.h>

void printBinary(unsigned short n) {
int i;
for (i=15; i>=0; i--) {
printf("%d", (n>>i)&1); 
if (i == 12 || i == 9) printf(":"); 
}
printf("\n");
}

int main() {
unsigned short input;
printf("16진수 입력 : ");
scanf("%hx", &input); 
printf("2진수 출력 : ");
printBinary(input);
return 0;
}
