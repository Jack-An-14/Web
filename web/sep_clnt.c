#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
    int sock;
    char buf[BUF_SIZE];
    struct sockaddr_in servAddr;

    FILE* readFp;
    FILE* writeFp;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr));
    readFp = fdopen(sock, "r");
    writeFp = fdopen(sock, "w");

    while (1) {
        if (fgets(buf, sizeof(buf), readFp) == NULL) {
            break;
        }
        fputs(buf, stdout);
        fflush(stdout);
    }

    fputs("FROM CLIENT: THANK you! \n", writeFp);
    fflush(writeFp);
    fclose(writeFp);
    fclose(readFp);
    return 0;
}