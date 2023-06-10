#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define COLOR_RESET "\033[0m"
#define COLOR_DIRECTORY "\033[1;34m"
#define COLOR_EXECUTABLE "\033[1;32m"

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void print_file_info(const char* filename) {
    struct stat file_info;

    if (stat(filename, &file_info) < 0) {
        perror("stat");
        return;
    }

    // 파일 유형과 권한 출력
    print_permissions(file_info.st_mode);
    printf(" ");

    // 링크 수 출력
    printf("%hu ", file_info.st_nlink);

    // 소유자 이름 출력
    struct passwd* pw = getpwuid(file_info.st_uid);
    if (pw != NULL)
        printf("%s ", pw->pw_name);

    // 그룹 이름 출력 (색상 적용)
    struct group* gr = getgrgid(file_info.st_gid);
    if (gr != NULL)
        printf("\033[38;5;63m%s\033[0m ", gr->gr_name);

    // 파일 크기 출력
    printf("%lld ", (long long)file_info.st_size);

    // 수정 시간 출력
    struct tm* time_info = localtime(&file_info.st_mtime);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", time_info);
    printf("%s ", time_str);

    // 파일 이름 출력 (색상 적용)
    if (S_ISDIR(file_info.st_mode)) {
        printf(COLOR_DIRECTORY "%s" COLOR_RESET "\n", filename);
    } else if (file_info.st_mode & S_IXUSR || file_info.st_mode & S_IXGRP || file_info.st_mode & S_IXOTH) {
        printf(COLOR_EXECUTABLE "%s" COLOR_RESET "\n", filename);
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
