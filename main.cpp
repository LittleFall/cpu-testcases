#include <thread>
#include <vector>

void run(long long cycle) {
    while(cycle--) {

    }
}

int main() {
    long long cycle = 5e12;
    long long core = 1;

    run(cycle);
//    std::vector<std::thread> save;
//
//    for(int i=0; i<core; ++i)
//        save.emplace_back(run, cycle);
//
//    for(auto &th:save)
//        th.join();
}
