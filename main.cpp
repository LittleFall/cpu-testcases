#include <thread>
#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>

constexpr int len = 10'000'001;
char str[len];

void run(long long cycle, int id) {
    while(cycle--) {
    }
}

// TODO use posix interface to write
// TODO fflush
// read file
// 读多个不同的文件，可以没有内容
// 边读边算
void write(long long cycle, int id) {

}

int main() {
    for (int i=0; i<len-1; ++i) {
        str[i] = 'c';
    }

    long long cycle = 5e12;
    long long core = 1000;

    std::vector<std::thread> save;

    for(int i=0; i<core; ++i)
        save.emplace_back([i=i]{
            std::ofstream fout("a.out"+std::to_string(i));
            long long cycle = 5e12;
            while(cycle--) {
                fout << str << std::endl;
            }
        });
//    for(int i=core/2; i<core; ++i)
//        save.emplace_back(write, cycle, i);

    for(auto &th:save)
        th.join();
}
