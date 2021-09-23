#include <sys/resource.h>
#include <iostream>
#include <cstring>

int main(int argc, char **argv) 
{
    rlimit rlim;

    int res = getrlimit(RLIMIT_CORE, &rlim);
    perror(("getrlimit "+std::to_string(res)).c_str());
    std::cout << "rlim_max = " << rlim.rlim_max << "\n"
              << "rlim_cur = " << rlim.rlim_cur << "\n";

    puts("");

    long long lim = 1024 * 1024 * 1024;
    if (argc>=2) {
        lim = atoi(argv[1]);
    }
    std::cout << "will set lim = " << lim << "\n";
    rlim.rlim_cur = lim;
    res = setrlimit(RLIMIT_CORE, &rlim);
    perror(("setrlimit "+std::to_string(res)).c_str());

    if (int code = setrlimit(RLIMIT_CORE, &rlim); code)
    {
        std::string message = "Cannot set max size of core file to " + std::to_string(rlim.rlim_cur) +
                                ", rlim_max = " + std::to_string(rlim.rlim_max) + ", rlim_cur = " + std::to_string(rlim.rlim_cur) +
                                ", error code = " + std::to_string(code) + ", error message = " + std::string(strerror(errno));
        /// It doesn't work under address/thread sanitizer. http://lists.llvm.org/pipermail/llvm-bugs/2013-April/027880.html
        std::cerr << message << std::endl;
    }

    puts("");

    res = getrlimit(RLIMIT_CORE, &rlim);
    perror(("getrlimit "+std::to_string(res)).c_str());
    std::cout << "rlim_max = " << rlim.rlim_max << "\n"
            << "rlim_cur = " << rlim.rlim_cur << "\n";

}