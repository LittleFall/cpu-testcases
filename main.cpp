#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <thread>
#include <time.h>

char buf[1'048'57600+8192]={1};

void myRead(int id, char filename[200], int block_size) {
    char message[200] = {};
    int fd;
    time_t t = 0, lstt = 0;
    
    while (true) {
        fd = open(filename, O_DIRECT | O_RDONLY);
        if (fd == -1) {
            perror(filename);
            return;
        }
        int ret = read(fd, (char*)((uintptr_t(buf)>>12)+1 << 12), block_size);
        if (ret<block_size) {
            time(&t);
            sprintf(message, "[thread=%d][time: %lld][%s] %d byte has been read, cost %d seconds.", id, t, filename, ret, t-lstt);
            perror(message);
            lstt = t;
        }
        close(fd);
    }
}

int main(int argc, char *argv[]) {
    int num_thread = 1000, block_size = 1'048'57600;
    char filepath[200] = {};
    
    if (argc>=2) {
        num_thread  = atoi(argv[1]);
    }
    if (argc>=3) {
        block_size = atoi(argv[2]);
    }
    if (argc>=4) {
        strcpy(filepath, argv[3]);
    } else {
        strcpy(filepath, argv[0]);
    }
    
    printf("Multithread reading test.\n");
    printf("Number of threads = %d, try read size = %d\n", num_thread, block_size);
    printf("Reading file: `%s`.\n", filepath);

    auto threads = new std::thread[num_thread];
    for(int i=0; i<num_thread; ++i) {
        threads[i] = std::thread(myRead, i, filepath, block_size);
    }
    for(int i=0; i<num_thread; ++i) {
        threads[i].join();
    }
    delete []threads;
}


