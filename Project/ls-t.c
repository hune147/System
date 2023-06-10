#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[256];
    time_t mtime;
} FileInfo;

int compareTimes(const void *a, const void *b) {
    FileInfo *fileA = (FileInfo *)a;
    FileInfo *fileB = (FileInfo *)b;

    return (int)(fileB->mtime - fileA->mtime);
}

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("디렉토리 열기 오류");
        return 1;
    }

    struct dirent *entry;
    FileInfo *fileInfos = NULL;
    int fileCount = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            FileInfo fileInfo;
            strncpy(fileInfo.name, entry->d_name, sizeof(fileInfo.name) - 1);
            fileInfo.name[sizeof(fileInfo.name) - 1] = '\0';
            struct stat fileStat;
            stat(entry->d_name, &fileStat);
            fileInfo.mtime = fileStat.st_mtime;

            fileInfos = realloc(fileInfos, (fileCount + 1) * sizeof(FileInfo));
            fileInfos[fileCount] = fileInfo;
            fileCount++;
        }
    }

    qsort(fileInfos, fileCount, sizeof(FileInfo), compareTimes);

    for (int i = 0; i < fileCount; i++) {
        printf("%s\n", fileInfos[i].name);
    }

    free(fileInfos);
    closedir(dir);

    return 0;
}

