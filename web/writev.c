#include <stdio.h>
#include <sys/uio.h>

int main(int argc, char* argv[]) {
    struct iovec vec[2];
    char buf1[] = "ABCDEFG";
    char buf2[] = "1234567";
    int strLen;

    vec[0].iov_base = buf1;
    vec[0].iov_len = 3;
    vec[1].iov_base = buf2;
    vec[1].iov_len = 4;

    strLen = writev(1, vec, 2);
    puts("");
    printf("Write bytes: %d \n", strLen);
    return 0;
}