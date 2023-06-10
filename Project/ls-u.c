#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char name[256];
    time_t modified_time;
} FileEntry;

int compare_entries(const void* a, const void* b) {
    const FileEntry* entry_a = (const FileEntry*)a;
    const FileEntry* entry_b = (const FileEntry*)b;

    return difftime(entry_b->modified_time, entry_a->modified_time);
}

void print_file_info(const char* filename) {
    struct stat file_info;

    if (stat(filename, &file_info) < 0) {
        perror("stat");
        return;
    }

    printf("%s\n", filename);
}

int main() {
    DIR* dir;
    struct dirent* entry;
    FileEntry* file_entries = NULL;
    int num_entries = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // 파일 및 디렉토리 정보 읽기
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            struct stat file_info;
            char file_path[256];

            snprintf(file_path, sizeof(file_path), "./%s", entry->d_name);

            if (stat(file_path, &file_info) < 0) {
                perror("stat");
                continue;
            }

            FileEntry new_entry;
            strncpy(new_entry.name, entry->d_name, sizeof(new_entry.name));
            new_entry.modified_time = file_info.st_mtime;

            file_entries = (FileEntry*)realloc(file_entries, (num_entries + 1) * sizeof(FileEntry));
            file_entries[num_entries] = new_entry;
            num_entries++;
        }
    }

    closedir(dir);

    // 수정된 시간 기준으로 정렬
    qsort(file_entries, num_entries, sizeof(FileEntry), compare_entries);

    // 출력
    for (int i = 0; i < num_entries; i++) {
        print_file_info(file_entries[i].name);
    }

    free(file_entries);

    return 0;
}

