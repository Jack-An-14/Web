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
    struct sockaddr_in adr;
    int strLen;
    char buf[BUF_SIZE];
    if (argc != 2) {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(1);
    }

    recvSock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_port = htons(atoi(argv[1]));

    if (bind(recvSock, (struct sockaddr*)&adr, sizeof(adr)) == -1) {
        error_handling("bind() error");
    }

    while (1) {
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