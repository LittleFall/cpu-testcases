#include <thread>
#include <vector>
#include <fstream>
#include <iostream>

char str[100'000'001];

void run(long long cycle, int id) {
    while(cycle--) {
    }
}

void write(long long cycle, int id) {
    std::ofstream fout("a.out"+std::to_string(id));
    while(cycle--) {
        fout << str;
    }
}

int main() {

    for (int i=0; i<100'000'000; ++i) {
        str[i] = 'c';
    }


    long long cycle = 5e12;
    long long core = 1000;

    std::vector<std::thread> save;

    for(int i=0; i<core; ++i)
        save.emplace_back(write, cycle, i);
//    for(int i=core/2; i<core; ++i)
//        save.emplace_back(write, cycle, i);

    for(auto &th:save)
        th.join();
}
