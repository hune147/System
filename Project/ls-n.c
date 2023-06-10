#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

void print_file_info(const char* filename) {
    struct stat file_info;

    if (stat(filename, &file_info) < 0) {
        perror("stat");
        return;
    }

    // 파일 유형 출력
    printf((S_ISDIR(file_info.st_mode)) ? "d" : "-");

    // 파일 권한 출력
    printf((file_info.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_info.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_info.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_info.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_info.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_info.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_info.st_mode & S_IROTH) ? "r" : "-");
    printf((file_info.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_info.st_mode & S_IXOTH) ? "x " : "- ");

    // 링크 수 출력
    printf("%hu ", file_info.st_nlink);

    // 사용자 ID 출력
    printf("%ld ", (long)file_info.st_uid);

    // 그룹 ID 출력
    printf("%ld ", (long)file_info.st_gid);

    // 파일 크기 출력
    printf("%lld ", (long long)file_info.st_size);

    // 수정 시간 출력
    printf("%ld ", file_info.st_mtime);

    // 파일 이름 출력
    printf("%s\n", filename);
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

