#include <iostream>

#include "fsearch/filesearcher.hpp"

int main(int argc, char *argv[]) {

    if(argc != 2 && argc != 3 ) {
        std::cout << "Invalid arguments" << std::endl
                  << "Required arguments:" << std::endl
                  << "\targ1: filename" << std::endl
                  << "\targ2 (optional): start folder. Default value: root directory" << std::endl;
        return 1;
    }

    // Using FileSearcher default strategy: ThrPoolRecSearch(8, &std::cout)
    // Using FileSearcher default startFolder: rootPath
    fsearch::FileSearcher fs;

    // If start folder specified
    if(argc == 3) {
        fs.setStartFolder(fs::path(argv[2]));
    }

    // Using default policy: deferred 
    auto fut = fs.find(fs::path(argv[1]));     // Run search
    auto res = fut.get();

    // Print results
    if(res.empty()) {
        std::cout << std::endl << std::endl 
                  << "No file with filename \"" << argv[1] << "\" found"
                  << std::endl;
    }
    else {
        std::cout << std::endl << std::endl 
                  << "Found file: " << res
                  << std::endl; 
    }

    return 0;
}