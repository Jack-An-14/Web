//类似hello_client.c 改变read函数调用方式
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
void error_handling(char * message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
int main(int argc, char * argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    int idx = 0, read_len = 0;
    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    //创建套结字
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    
    //调用connect函数向服务器发送连接请求
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("connect() error");
    }
    
    //改动read函数的调
    // str_len = read(sock, message, sizeof(message) - 1);
    // if(str_len == -1){
    //     error_handling("read() error");
    // }
    
    for (int i = 0; i < 120000; i++){
        printf("Wait time %d \n", i);
    }
    //read的第二个参数传递地址，这里传递的就是字符串每个字符的地址并且每次就读取一个字符
    // while (read_len = read(sock, &message[idx++], 1)){
    //     if(read_len == -1){
    //         error_handling("read() error!");
    //     }
    //     //因为每次读取1个字符，str_len就是调用次数，说明数据传输存在边界
    //     str_len += read_len;
    // }
    str_len = read(sock, message, sizeof(message));

    printf("Message from server : %s\n", message);
    printf("Function read call count: %d \n", str_len);
    close(sock);
    return 0;
}