#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#define KILOBYTE 1024

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("디렉토리 열기 오류");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            stat(entry->d_name, &fileStat);
            printf("%-20s %ldK\n", entry->d_name, fileStat.st_size / KILOBYTE);
        }
    }

    closedir(dir);

    return 0;
}

