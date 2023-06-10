#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode))  ? "d" : "-");
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

    // 그룹 이름 출력
    struct group* gr = getgrgid(file_info.st_gid);
    if (gr != NULL)
        printf("%s ", gr->gr_name);

    // 파일 크기 출력 (사람이 읽기 쉬운 형식으로 변환)
    off_t size = file_info.st_size;
    char unit;
    double converted_size;

    if (size >= 1e9) {
        converted_size = (double)size / 1e9;
        unit = 'G';
    } else if (size >= 1e6) {
        converted_size = (double)size / 1e6;
        unit = 'M';
    } else if (size >= 1e3) {
        converted_size = (double)size / 1e3;
        unit = 'K';
    } else {
        converted_size = (double)size;
        unit = 'B';
    }

    printf("%.1f%c ", converted_size, unit);

    // 수정 시간 출력
    struct tm* time_info = localtime(&file_info.st_mtime);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", time_info);
    printf("%s ", time_str);

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
        print_file_info(entry->d_name);
    }

    closedir(dir);

    return 0;
}

