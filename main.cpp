#include <thread>
#include <vector>

void run(long long cycle) {
    while(cycle--) {

    }
}

int main() {
    long long cycle = 5e10;
    long long core = 24;

    run(cycle);
//    std::vector<std::thread> save;
//
//    for(int i=0; i<core; ++i)
//        save.emplace_back(run, cycle);
//
//    for(auto &th:save)
//        th.join();
}
