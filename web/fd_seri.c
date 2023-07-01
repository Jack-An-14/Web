//fd_seri.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void){
    int fd1, fd2, fd3;
    fd1 = socket(PF_INET, SOCK_STREAM, 0);
    fd2 = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);
    fd3 = socket(PF_INET, SOCK_DGRAM, 0);

    printf("file discriptor 1 : %d\n", fd1);
    printf("file discriptor 2 : %d\n", fd2);
    printf("file discriptor 3 : %d\n", fd3);

    return 0;
}