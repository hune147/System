#include <stdio.h>

void clear_screen() {
    printf("\033[2J\033[H");
}

int main() {
    clear_screen();
    printf("화면이 초기화되었습니다.\n");

    return 0;
}

