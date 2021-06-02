#include <thread>
#include <vector>
#include <fstream>
#include <iostream>

void run(long long cycle, int id) {
    while(cycle--) {
    }
}

void write(long long cycle, int id) {
    getchar();
}

int main() {


    long long cycle = 5e12;
    long long core = 24;

    std::vector<std::thread> save;

    for(int i=0; i<core; ++i)
        save.emplace_back(write, cycle, i);
//    for(int i=core/2; i<core; ++i)
//        save.emplace_back(write, cycle, i);

    for(auto &th:save)
        th.join();
}
