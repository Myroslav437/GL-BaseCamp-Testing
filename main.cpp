#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#include "fsearch/thrpoolrecsearch.hpp"

int main(int argc, char *argv[]) {
    fsearch::ThrPoolRecSearch search;
    search.setLogStream(&std::cout);
    search.setThreadNum(8);

    auto res = search.execute("/", ".gitignore");
    auto finalRes = res.get();

    std::cout   << std::endl << std::endl 
                << "Found file: " << finalRes 
                << std::endl << std::endl;

    return 0;
}