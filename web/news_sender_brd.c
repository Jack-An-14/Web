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
    int sendSock;
    struct sockaddr_in broadAdr;
    FILE* fp;
    char buf[BUF_SIZE];
    int soBrd = 1;
    if (argc != 3) {
        printf("Usage : %s <Broadcast IP> <port>\n", argv[0]);
        exit(1);
    }

    sendSock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&broadAdr, 0, sizeof(broadAdr));
    broadAdr.sin_family = AF_INET;
    broadAdr.sin_addr.s_addr = inet_addr(argv[1]);
    broadAdr.sin_port = htons(atoi(argv[2]));

    setsockopt(sendSock, SOL_SOCKET, SO_BROADCAST, (void*)&soBrd, sizeof(soBrd));
    if ((fp = fopen("../web/news.txt", "r")) == NULL) {
        error_handling("fopen() error");
    }

    while (!feof(fp)) {
        fgets(buf, BUF_SIZE, fp);
        printf("%s", buf);
        sendto(sendSock, buf, strlen(buf), 0, (struct sockaddr*)&broadAdr, sizeof(broadAdr));
        sleep(2);
    }
    
    close(sendSock);
    return 0;
}