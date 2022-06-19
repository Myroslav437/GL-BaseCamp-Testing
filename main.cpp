#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#include "fsearch/simplethreadpool.hpp"

void func() {
    static std::atomic_int i = 0;

    std::cout << "Call: " << i++ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(int argc, char *argv[]) {
    SimpleThreadPool pool(5);

    for(int i = 0; i < 50; ++i) {
        pool.addTask(func);
    }

    return 0;
}