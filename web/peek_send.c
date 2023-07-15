#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in sendAdr;
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&sendAdr, 0, sizeof(sendAdr));
    sendAdr.sin_family = AF_INET;
    sendAdr.sin_addr.s_addr = inet_addr(argv[1]);
    sendAdr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&sendAdr, sizeof(sendAdr)) == -1) {
        error_handling("connect() error!");
    }
    
    write(sock, "123", strlen("123"));
    close(sock);
    return 0;
}