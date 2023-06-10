#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

typedef struct {
    char name[256];
    off_t size;
} File;

int compare_files(const void* a, const void* b) {
    const File* file1 = (const File*)a;
    const File* file2 = (const File*)b;
    return file2->size - file1->size;
}

void print_file_info(const char* filename) {
    struct stat file_info;

    if (stat(filename, &file_info) < 0) {
        perror("stat");
        return;
    }

    // 파일 이름 출력
    printf("%s\n", filename);
}

int main() {
    DIR* dir;
    struct dirent* entry;
    File files[1000];
    int file_count = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // 디렉토리 내의 파일 및 디렉토리 정보 읽기
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            strncpy(files[file_count].name, entry->d_name, sizeof(files[file_count].name));
            files[file_count].name[sizeof(files[file_count].name) - 1] = '\0';
            struct stat file_info;
            if (stat(entry->d_name, &file_info) == 0) {
                files[file_count].size = file_info.st_size;
                file_count++;
            }
        }
    }

    closedir(dir);

    // 파일 크기를 기준으로 정렬
    qsort(files, file_count, sizeof(File), compare_files);

    // 파일 정보 출력
    for (int i = 0; i < file_count; i++) {
        print_file_info(files[i].name);
    }

    return 0;
}

