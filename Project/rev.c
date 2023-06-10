#include <stdio.h>
#include <string.h>

void reverse_string(char* str) {
    int length = strlen(str);

    for (int i = length - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }

    printf("\n");
}

int main() {
    char input_string[256];

    printf("Enter a string: ");
    fgets(input_string, sizeof(input_string), stdin);

    // fgets는 개행 문자도 입력으로 받으므로 개행 문자 제거
    input_string[strcspn(input_string, "\n")] = '\0';

    reverse_string(input_string);

    return 0;
}

