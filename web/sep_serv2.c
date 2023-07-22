#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
    int servSock, clntSock;
    FILE* readFp;
    FILE* writeFp;

    struct sockaddr_in servAdr, clntAdr;
    socklen_t clntAdrSz;
    char buf[BUF_SIZE] = {0, };

    servSock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&servAdr, 0, sizeof(servAdr));
    servAdr.sin_family = AF_INET;
    servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAdr.sin_port = htons(atoi(argv[1]));

    bind(servSock, (struct sockaddr*)&servAdr, sizeof(servAdr));
    listen(servSock, 5);
    clntAdrSz = sizeof(clntAdr);
    clntSock = accept(servSock, (struct sockaddr*)&clntAdr, &clntAdrSz);

    readFp = fdopen(clntSock, "r");
    writeFp = fdopen(dup(clntSock), "w");

    fputs("FROM SERVER: Hi! client? \n", writeFp);
    fputs("I LOVE ALL OF THE WORLD \n", writeFp);
    fputs("You are awesome! \n", writeFp);
    fflush(writeFp);

    shutdown(fileno(writeFp), SHUT_WR);
    fclose(writeFp);

    fgets(buf, sizeof(buf), readFp);
    fputs(buf, stdout);
    fclose(readFp);
    return 0;

}