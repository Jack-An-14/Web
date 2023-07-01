#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char * message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
    int sd;
    FILE* fp;
    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in serv_adr;
    if(argc != 3){
        printf("Usage: %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    fp = fopen("receive.txt", "wb");
    sd = socket(PF_INET, SOCK_STREAM, 0);
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    while ((read_cnt = read(sd, buf, BUF_SIZE)) != 0)
    {
        fwrite((void*)buf, 1, read_cnt, fp);
    }

    //这里的puts不是很明白，往哪输出？打印在命令行上了，默认是stdout吧。没有第二参数-_-||
    puts("Received file data");
    //发送感谢语，对面服务器没有关闭输入流
    write(sd, "Thank you", 10);

    fclose(fp);
    close(sd);

    return 0;
    
}