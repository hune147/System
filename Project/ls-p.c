#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void print_file_info(const char* filename) {
    struct stat file_info;

    if (stat(filename, &file_info) < 0) {
        perror("stat");
        return;
    }

    // 디렉토리인 경우 이름 뒤에 슬래시를 추가하여 출력
    if (S_ISDIR(file_info.st_mode)) {
        printf("%s/\n", filename);
    } else {
        printf("%s\n", filename);
    }
}

int main() {
    DIR* dir;
    struct dirent* entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            print_file_info(entry->d_name);
        }
    }

    closedir(dir);

    return 0;
}

