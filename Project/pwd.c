#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("현재 디렉토리: %s\n", cwd);
    } else {
        perror("getcwd() 오류");
        return 1;
    }

    return 0;
}

