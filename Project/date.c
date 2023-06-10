#include <stdio.h>
#include <time.h>

int main() {
    time_t currentTime;
    struct tm *localTime;
    char timeString[100];

    // 현재 시간 정보 가져오기
    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    // 형식 지정하여 시간 문자열로 변환
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localTime);

    printf("현재 시간: %s\n", timeString);

    return 0;
}

