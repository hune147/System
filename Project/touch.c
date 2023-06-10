#include <stdio.h>
#include <utime.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    // 파일 열기 (없으면 생성)
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("파일 열기 오류");
        return 1;
    }

    // 파일의 수정 시간 업데이트
    if (utime(filename, NULL) == -1) {
        perror("수정 시간 업데이트 오류");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

