#include <unistd.h>

int main(int argc, char *argv[]) {
    char buffer[64];
    char error_message[] = "open file error\n";
    char success_message[] = "open file success\n";

    int fd = open("read", 0, 0);
    if (fd == -1) {
        write(0, error_message, strlen(error_message));
        return -1;
    }
    write(0, success_message, strlen(success_message));

    read(fd, buffer, 64);
    close(fd);
    return 0;
}