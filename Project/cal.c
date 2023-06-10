#include <stdio.h>
#include <time.h>

int main() {
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);

    int year = currentTime->tm_year + 1900;
    int month = currentTime->tm_mon + 1;

    printf("     %d년 %d월\n", year, month);
    printf("일 월 화 수 목 금 토\n");

    struct tm date = { 0, 0, 0, 1, month - 1, year - 1900 };
    t = mktime(&date);

    int startDay = date.tm_wday;
    int totalDays = 0;

    while (date.tm_mon == (month - 1)) {
        if (date.tm_wday == 0) {
            printf("\n");
        }
        if (date.tm_wday == startDay) {
            printf("%2d ", date.tm_mday);
            totalDays++;
        } else if (totalDays > 0) {
            printf("%2d ", date.tm_mday);
            totalDays++;
        } else {
            printf("   ");
        }

        date.tm_mday++;
        t = mktime(&date);
        localtime_r(&t, &date);
    }

    printf("\n");

    return 0;
}

