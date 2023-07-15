#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int recvSock;
    int strLen;
    char buf[BUF_SIZE];
    struct sockaddr_in adr;
    struct ip_mreq joinAdr;
    if (argc != 3) {
        printf("Usage : %s <GroupIP> <port>\n", argv[0]);
        exit(1);
    }

    recvSock = socket(PF_INET, SOCK_DGRAM, 0);
    //这里socket没有正确返回值
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_port = htons(atoi(argv[2]));

    if (bind(recvSock, (struct sockaddr*)&adr, sizeof(adr)) == -1) {
        error_handling("bind() error");
    }

    joinAdr.imr_multiaddr.s_addr = inet_addr(argv[1]);
    joinAdr.imr_interface.s_addr = htonl(INADDR_ANY);

    setsockopt(recvSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&joinAdr, sizeof(joinAdr));
    while (1) {
        //这里为什么多播不成功，可能是因为路由器不支持多播功能
        //这里应该是没有收到消息
        strLen = recvfrom(recvSock, buf, BUF_SIZE - 1, 0, NULL, 0);
        if (strLen < 0) {
            break;
        }
        buf[strLen] = 0;
        fputs(buf, stdout);
    }
    close(recvSock);
    return 0;
}