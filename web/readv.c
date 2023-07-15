#include <stdio.h>
#include <sys/uio.h>
#define BUF_SIZE 100

int main(int argc, char* argv[]) {
    struct iovec vec[2];
    //从来没见过这样申明的  char buf1[BUF_SIZE] = {0, };
    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];
    int strLen;

    vec[0].iov_base = buf1;
    vec[0].iov_len = 5;
    vec[1].iov_base = buf2;
    vec[1].iov_len = BUF_SIZE;
    
    strLen = readv(0, vec, 2);
    printf("Read bytes: %d \n", strLen);
    printf("First message: %s \n", buf1);
    printf("Second message: %s \n", buf2);
    return 0;
}