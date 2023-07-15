#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_SIZE 30
void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int acptSock, recvSock;
    struct sockaddr_in acptAdr, recvAdr;
    int strLen, state;
    socklen_t recvAdrSize;
    char buf[BUF_SIZE];
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    acptSock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&acptAdr, 0, sizeof(acptAdr));
    acptAdr.sin_family = AF_INET;
    acptAdr.sin_addr.s_addr = htonl(INADDR_ANY);
    acptAdr.sin_port = htons(atoi(argv[1]));

    if (bind(acptSock, (struct sockaddr*)&acptAdr, sizeof(acptAdr)) == -1) {
        error_handling("bind() error!");
    }
    listen(acptSock, 5);

    recvAdrSize = sizeof(recvAdr);
    recvSock = accept(acptSock, (struct sockaddr*)&recvAdr, &recvAdrSize);

    while (1) {
        //MSG_PEEK选项会把接收队列中的可读数据拷贝到缓存buf中，并且不会影响原来的接收队列的数据
        strLen = recv(recvSock, buf, sizeof(buf) - 1, MSG_PEEK | MSG_DONTWAIT);
        if (strLen > 0) {
            break;
        }
    }

    buf[strLen] = 0;
    printf("Buffering %d bytes: %s \n", strLen, buf);
    
    //这里是从接收队列中把消息读出来
    strLen = recv(recvSock, buf, sizeof(buf) - 1, 0);
    buf[strLen] = 0;
    printf("Read again: %s \n", buf);
    close(acptSock);
    close(recvSock);
    return 0;
}