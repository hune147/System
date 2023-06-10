#include <stdio.h>
#include <sys/stat.h>

int main() {
    char directoryName[100];

    printf("생성할 디렉토리 이름: ");
    scanf("%s", directoryName);

    if (mkdir(directoryName, 0777) == 0) {
        printf("디렉토리를 성공적으로 생성했습니다.\n");
    } else {
        perror("디렉토리 생성 오류");
        return 1;
    }

    return 0;
}

