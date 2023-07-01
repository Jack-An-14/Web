#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 1024
void error_handling(char * message);

int main(int argc, char * argv[]){
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int strLen = 0;
    socklen_t clnt_addr_size;

    char message[MAX];
    
    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);//调用socket函数创建套接字
    if(serv_sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    //调用bind函数分配IP地址和端口号
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }
    
    //调用listen函数将套接字转为可接受连接状态
    if(listen(serv_sock, 5) == -1) {
        error_handling("listent() error");
    }
    
    clnt_addr_size = sizeof(clnt_addr);
    for (int i = 0; i < 5; i++){
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
        
        if(clnt_sock == -1){
            error_handling("accept() error");
        }
        else {
            //这一块为什么会不显示,可能是复制的时候，括号的问题
            printf("Connected %d \n", i+1);
        }

        while ((strLen = read(clnt_sock, message, MAX)) != 0){
            write(clnt_sock, message, strLen);
        }

        close(clnt_sock);
    }
    
    
    close(serv_sock);
    return 0;
}


void error_handling(char * message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}