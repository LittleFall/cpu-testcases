#include <thread>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

char str[100'000'000];

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

int main(int argc, char **args) {
    using std::chrono::system_clock;
    std::time_t tt;

    long long core = 100;
    long long cycle = 1e7;

    if (argc==2) {
        core = std::atoi(args[1]);
    }
    if (argc==3) {
        cycle = std::atoi(args[2]);
    }
    std::cout << "threads = " << core << std::endl;
    std::cout << "cycles = " << cycle << std::endl;

    std::vector<std::thread> save;

    constexpr std::chrono::duration<int> s1(1);
    for (int count = 0; count < 10000; count++)
    {
        std::this_thread::sleep_for(s1); // time waster for test

        tt = std::chrono::system_clock::to_time_t ( std::chrono::system_clock::now() );
        std::cout << "now is: " << ctime(&tt) << ", creating " << core << " task.\n";

        for(int i=0; i<core; ++i)
            save.emplace_back(run, cycle, i);
    }

//    for(int i=0; i<core; ++i)
//        save.emplace_back(write, cycle, i);
//    for(int i=core/2; i<core; ++i)
//        save.emplace_back(write, cycle, i);

    for(auto &th:save)
        th.join();
}
