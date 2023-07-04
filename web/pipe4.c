#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main() {
    char str1[] = "Who are you ?";
    char str2[] = "I'm child proc.";
    char str3[] = "OK";
    char buf[BUF_SIZE];
    int fds1[2], fds2[2];
    pid_t pid;
    pipe(fds1);
    pipe(fds2);

    pid = fork();
    if (pid == 0) {
        //子进程
        read(fds1[0], buf, BUF_SIZE);
        printf("Parent proc say: %s \n", buf);
        write(fds2[1], str2, sizeof(str2));
        read(fds1[0], buf, BUF_SIZE);
        printf("Parent proc say: %s \n", buf);
        
    } else {
        //父进程
        write(fds1[1], str1, sizeof(str1));
        read(fds2[0], buf, BUF_SIZE);
        printf("Child proc say: %s \n", buf);
        sleep(3);
        write(fds1[1], str3, sizeof(str3));
    }



    return 0;
}