#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <thread>
#include <time.h>

char *block;

void myWrite(int id, char dir[200], int block_size) {
    char message[200] = {};
    int fd;
    time_t t;
    char filename[200] = {};
    
    sprintf(filename, "%s/a.out_%d", dir, id);

    fd = open(filename, O_CREAT | O_RDWR | O_APPEND | O_SYNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror(filename);
        return;
    }

    while (true) {
        int ret = write(fd, block, block_size);
        if (ret < block_size-1) {
            time(&t);
            sprintf(message, "[%s][%s]", ctime(&t), filename);
            perror(message);
        }
        
    }
}

int main(int argc, char *argv[]) {
    int num_thread = 48, block_size = 1'000'000;
    char directory[200] = ".";

    if (argc>=2) {
        num_thread  = atoi(argv[1]);
    }
    if (argc>=3) {
        block_size = atoi(argv[2]);
    }
    if (argc>=4) {
        strcpy(directory, argv[3]);
    }
    
    printf("Multithread writing test.\n");
    printf("Number of threads = %d, write block size = %d\n", num_thread, block_size);
    printf("A thread writes a file, stores in the `%s` directory.\n", directory);

    block = new char[block_size+1];
    for (int i=0; i<block_size; ++i) {
        block[i] = 'c';
    }

    auto threads = new std::thread[num_thread];
    for(int i=0; i<num_thread; ++i) {
        threads[i] = std::thread(myWrite, i, directory, block_size);
    }
    for(int i=0; i<num_thread; ++i) {
        threads[i].join();
    }
    delete []threads;
}


