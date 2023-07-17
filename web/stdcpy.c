#include <stdio.h>
#define BUF_SIZE 3

int main(int argc, char* argv[]) {
    FILE* fd1, *fd2;
    char buf[BUF_SIZE];

    fd1 = fopen("../web/news.txt", "r");
    fd2 = fopen("../web/cpy.txt", "w");

    while ((fgets(buf, BUF_SIZE, fd1)) > 0) {
        fputs(buf, fd2);
    }

    fclose(fd1);
    fclose(fd2);
    return 0;
}