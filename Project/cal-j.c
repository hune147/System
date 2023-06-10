#include <stdio.h>

int is_leap_year(int year) {
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}

int get_julian_date(int day, int month, int year) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int julian_date = 0;
    int i;

    for (i = 1; i < month; i++) {
        julian_date += days_in_month[i - 1];
        if (i == 2 && is_leap_year(year))
            julian_date++;
    }

    julian_date += day;

    return julian_date;
}

int main() {
    int day, month, year;
    int julian_date;

    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);

    julian_date = get_julian_date(day, month, year);

    printf("Julian date: %d\n", julian_date);

    return 0;
}
