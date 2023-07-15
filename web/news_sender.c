#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TTL 64
#define BUF_SIZE 30
void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sendSock;
    struct sockaddr_in mulAdr;
    int timeLive = TTL;
    FILE* fp;
    char buf[BUF_SIZE];
    if (argc != 3) {
        printf("Usage : %s <GroupIP> <port>\n", argv[0]);
        exit(1);
    }
    
    sendSock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&mulAdr, 0, sizeof(mulAdr));
    mulAdr.sin_family = AF_INET;
    //Multicast IP
    mulAdr.sin_addr.s_addr = inet_addr(argv[1]);
    //Multicast Port
    mulAdr.sin_port = htons(atoi(argv[2]));

    //这里在设置TTL
    setsockopt(sendSock, IPPROTO_IP, IP_MULTICAST_TTL, (void*)&timeLive, sizeof(timeLive));

    if ((fp = fopen("../web/news.txt", "r")) == NULL) {
        error_handling("fopen() error");
    }

    //Broadcasting
    while (!feof(fp)) {
        fgets(buf, BUF_SIZE, fp);
        sendto(sendSock, buf, strlen(buf), 0, (struct sockaddr*)&mulAdr, sizeof(mulAdr));
        sleep(2);
    }
    fclose(fp);
    close(sendSock);
    return 0;
}