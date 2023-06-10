#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void print_file_info(const char* filename) {
    printf("%s, ", filename);
}

int main() {
    DIR* dir;
    struct dirent* entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // 파일 및 디렉토리 정보 읽기
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            print_file_info(entry->d_name);
        }
    }

    closedir(dir);

    return 0;
}

