#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s pattern\n", argv[0]);
        return 1;
    }

    char *pattern = argv[1];

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strstr(buffer, pattern) != NULL) {
            printf("%s", buffer);
        }
    }

    return 0;
}

