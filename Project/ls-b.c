#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

void escapeString(const char *input, char *output) {
    size_t inputLen = strlen(input);
    size_t outputIndex = 0;

    for (size_t i = 0; i < inputLen; i++) {
        switch (input[i]) {
            case '\'':
            case '\"':
            case '\\':
            case '\a':
            case '\b':
            case '\f':
            case '\n':
            case '\r':
            case '\t':
            case '\v':
                output[outputIndex++] = '\\';
                break;
        }

        output[outputIndex++] = input[i];
    }

    output[outputIndex] = '\0';
}

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("디렉토리 열기 오류");
        return 1;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        char *escapedName = (char *)malloc((strlen(entry->d_name) * 2 + 1) * sizeof(char));
        escapeString(entry->d_name, escapedName);
        printf("%s\n", escapedName);
        free(escapedName);
    }

    closedir(dir);

    return 0;
}

