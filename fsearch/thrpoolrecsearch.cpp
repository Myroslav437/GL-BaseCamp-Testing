#include <algorithm>
#include <ostream>
#include <atomic>

#include "thrpoolrecsearch.hpp"
#include "threadpool/simplethreadpool.hpp"

namespace fs = std::filesystem;

namespace fsearch {

static void threadPoolRecursiveSearch(
    fs::path startFolder,
    const fs::path* fileNamePtr,
    SimpleThreadPool* tpPtr,
    std::ostream* os,
    fs::path* resultPtr,
    bool* successPtr
);

static fs::path execute_(fs::path startFolder, fs::path fileName, unsigned int threadNum, std::ostream* os); 

std::future<fs::path> ThrPoolRecSearch::execute(
            fs::path startFolder, 
            fs::path fileName) 
{
    return std::async(std::launch::async, execute_, startFolder, fileName, this->threadNum, this->logStream);
}

static fs::path execute_(            
    fs::path startFolder, 
    fs::path fileName,
    std::
    unsigned int threadNum,
    std::ostream* os
    ) 
{
    SimpleThreadPool tp(threadNum);
    fs::path result;
    bool success = false;
    tp.addTask(threadPoolRecursiveSearch, startFolder, &fileName, &tp, os, &result, &success);
    tp.waitAll();

    // if nothing found return empty string
    if(!success) {
        result = fs::path();
    }

    return result;
}

static void threadPoolRecursiveSearch(
    fs::path startFolder,
    const fs::path* fileNamePtr,
    SimpleThreadPool* tpPtr,
    std::ostream* os,
    fs::path* resultPtr,
    bool* successPtr
) 
{
    try{
        *os << "Searching in" << startFolder << std::endl;

        std::for_each(
            fs::directory_iterator(startFolder),
            fs::directory_iterator(),
            [&](const fs::directory_entry& dir_entry) {
                fs::path fname = dir_entry.path().filename();
                if(fname == *fileNamePtr) {

                    *os << "File found in" << dir_entry.path() << std::endl;

                    tpPtr->softShutdown();
                    *resultPtr = dir_entry.path();
                    *successPtr = true;
                }
                else if(dir_entry.is_directory()) {
                    tpPtr->addTask(threadPoolRecursiveSearch, startFolder/fname, fileNamePtr, tpPtr, resultPtr, successPtr);
                }
            } 
        );
    }
    catch(...) {
        *os << "Error while reading" << startFolder << std::endl;
    }
}

} // namespace fsearch