#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)b, *(const char **)a);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    char **fileNames;
    int count = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("디렉토리 열기 오류");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        count++;
    }

    rewinddir(dir);

    fileNames = (char **)malloc(count * sizeof(char *));
    if (fileNames == NULL) {
        perror("메모리 할당 오류");
        closedir(dir);
        return 1;
    }

    count = 0;
    while ((entry = readdir(dir)) != NULL) {
        fileNames[count] = strdup(entry->d_name);
        count++;
    }

    qsort(fileNames, count, sizeof(char *), compare);

    for (int i = 0; i < count; i++) {
        printf("%s\n", fileNames[i]);
        free(fileNames[i]);
    }

    free(fileNames);
    closedir(dir);

    return 0;
}

