#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
void error_handling(char * message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char * argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
    }
    
    //创建套结字
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    
    //调用connect函数向服务器发送连接请求
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("connect() error");
    }

    str_len = read(sock, message, sizeof(message) - 1);
    if(str_len == -1){
        error_handling("read() error");
    }

    printf("Message from server : %s\n", message);
    close(sock);
    return 0;
}