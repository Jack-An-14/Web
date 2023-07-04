#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main() {
    int fds[2];
    char str[] = "Who are you?";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();
    if (pid == 0) {
        //子进程执行
        write(fds[1], str, sizeof(str));
    } else {
        //父进程执行
        read(fds[0], buf, BUF_SIZE);
        puts(buf);
    }

    return 0;
}