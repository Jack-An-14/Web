//low_read.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100

void error_handling(char * message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(void){
    int fd;
    char buf[BUF_SIZE];
    //open函数， 文件名和打开方式
    fd = open("data.txt", O_RDONLY);
    if(fd == -1){
        error_handling("open() error!\n");
    }
    printf("file descriptor: %d \n", fd);
    //read函数向buf数组中存入文件数据
    if(read(fd, buf, sizeof(buf)) == -1){
        printf("read() error!\n");
    }
    printf("file data: %s", buf);
    close(fd);
    return 0;
}