#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname buf;
    if (uname(&buf) == -1) {
        perror("uname 오류");
        return 1;
    }

    printf("시스템 이름: %s\n", buf.sysname);
    printf("노드 이름: %s\n", buf.nodename);
    printf("커널 버전: %s\n", buf.release);
    printf("하드웨어 이름: %s\n", buf.machine);

    return 0;
}

