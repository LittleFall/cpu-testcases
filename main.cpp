#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <thread>
#include <time.h>

constexpr int len = 4097;
char str[len];

// TODO use posix interface to write
// TODO fflush
// read file
// 读多个不同的文件，可以没有内容
// 边读边算
void myWrite(int id) {
    char name[20] = "a.out", message[50] = {};
    int fd;
    time_t t;

    sprintf(name + strlen(name), "%d", id);

    fd = open(name, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror(name);
    }

    while (true) {
        int ret = write(fd, str, len - 1);
        if (ret < len-1) {
            time(&t);
            sprintf(message, "[%s][%s]", ctime(&t), name);
            perror(message);
        }
    }
}

int main() {
    for (int i=0; i<len-1; ++i) {
        str[i] = 'c';
    }

    long long core = 48;

    auto threads = new std::thread[core];
    for(int i=0; i<core; ++i) {
        threads[i] = std::thread(myWrite, i);
    }
    for(int i=0; i<core; ++i) {
        threads[i].join();
    }
    delete []threads;
}


