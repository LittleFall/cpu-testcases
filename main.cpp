#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <thread>

constexpr int len = 10'000'001;
char str[len];

// TODO use posix interface to write
// TODO fflush
// read file
// 读多个不同的文件，可以没有内容
// 边读边算
[[noreturn]] void myWrite(int id) {
    char name[20] = "a.out";
    sprintf(name + strlen(name), "%d", id);
    int fd = open(name, O_CREAT | O_TRUNC, S_IWUSR | S_IWGRP);
    if (fd == -1) {
        perror(name);
    }

    while (true) {
        int ret = write(fd, str, len - 1);
        if (ret < 0) {
            perror(name);
        }
    }
}

int main() {
    for (int i=0; i<len-1; ++i) {
        str[i] = 'c';
    }

    long long core = 1000;

    auto threads = new std::thread[core];
    for(int i=0; i<core; ++i) {
        threads[i] = std::thread(myWrite, i);
    }
    for(int i=0; i<core; ++i) {
        threads[i].join();
    }
    delete []threads;
}
