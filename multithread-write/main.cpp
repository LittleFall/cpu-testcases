#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <thread>
#include <time.h>
#include <atomic>
#include <sched.h>
#include <vector>

constexpr int CORES = 48;
int num_thread = 0;
char *block[CORES];

#define log(format, ...) do {                                       \
    char message[200] = {};                                         \
    time_t t;                                                       \
    time(&t);                                                       \
    sprintf(message, "[%s", ctime(&t));                             \
    message[strlen(message)-1] = ']';                               \
    sprintf(message+strlen(message), format, __VA_ARGS__);        \
    perror(message);                                                \
} while(0)  

int recored_thread_on_cpu(int times) {
    static constexpr int max_run_times = 20;
    static std::atomic_int threads_on_cpu[CORES][max_run_times]={}; // cpu, times
    static std::atomic_int total[max_run_times];

    if (times >= max_run_times) {
        log ("%s", "run too many times to log.");
        return 0;
    }
    threads_on_cpu[sched_getcpu()][times]++;

    int t = ++total[times];
    if(t == num_thread) {
        log("now is %d times", times);
        for(int i=0; i<CORES; ++i) {
            log("       cpu %d has %d threads", i, (int)threads_on_cpu[i][times]);
        }
    }
    return t;
}

void myWrite(int id, char dir[200], int block_size) {

    recored_thread_on_cpu(0);

    int core_bind = rand()%48;
    printf("thread %d will use %d array\n", id, core_bind);

    int fd;
    char filename[200] = {};
    sprintf(filename, "%s/a.out_%d", dir, id);

    fd = open(filename, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        log("[thread %4d] open file error", id);
        return;
    }

    int dones = 0;
    while (true) {
        int prev_cpu = -1, after_cpu = -1;

        int already_count = recored_thread_on_cpu(dones);

        prev_cpu = sched_getcpu();

        int ret = write(fd, block[core_bind], block_size);

        after_cpu = sched_getcpu();

        if (ret < block_size-1) {
            log("[thread %4d] write expected %d bytes, actually %d bytes.", id, block_size, ret);
        } else {
            ++dones;
            //log("[thread %4d] done %d times(%4d threads done these times), prev_cpu=%d, after_cpu=%d", id,dones, already_count, prev_cpu, after_cpu);
           
        }
    }
}

int main(int argc, char *argv[]) {
    int block_size = 1'000'000;
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

    block[0] = new char[block_size+1];
    for (int i=0; i<block_size; ++i) {
        block[0][i] = 'c';
    }
    for(int i=1; i<CORES; ++i) {
        block[i] = new char[block_size+1];
        memcpy(block[i], block[0], block_size);
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
