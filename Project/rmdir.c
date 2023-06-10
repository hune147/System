#include <stdio.h>
#include <unistd.h>

int main() {
    char directoryPath[100];

    printf("삭제할 디렉토리 경로: ");
    scanf("%s", directoryPath);

    if (rmdir(directoryPath) == 0) {
        printf("디렉토리를 성공적으로 삭제했습니다.\n");
    } else {
        perror("디렉토리 삭제 오류");
        return 1;
    }

    return 0;
}

