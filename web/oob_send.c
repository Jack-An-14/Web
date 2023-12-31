#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in recv_adr;
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&recv_adr, 0, sizeof(recv_adr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_adr.sin_port = htons(atoi(argv[2]));
    
    //发送信息作为客户端，需要先启动接收端。要不然connect就会失败
    if (connect(sock, (struct sockaddr*)&recv_adr, sizeof(recv_adr)) == -1) {
        error_handling("connect() error");
    }
    //传输数据
    write(sock, "123", strlen("123"));
    //传输紧急信息
    send(sock, "4", strlen("4"), MSG_OOB);
    //普通数据
    write(sock, "567", strlen("567"));
    //紧急数据
    send(sock, "890", strlen("890"), MSG_OOB);
    close(sock);
    return 0;
}