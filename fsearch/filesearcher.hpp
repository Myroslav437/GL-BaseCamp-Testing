#ifndef FILESEARCHER_HPP
#define FILESEARCHER_HPP

#include <filesystem>
#include <memory>
#include <iostream>
#include <future>

#include "searchstrategy.hpp"
#include "thrpoolrecsearch.hpp"

namespace fs = std::filesystem;

namespace fsearch {

    class FileSearcher 
    {
    public: 
        FileSearcher(
            fs::path startf = fs::current_path().root_path(),  
            std::shared_ptr<SearchStrategy> = std::shared_ptr<SearchStrategy>(new ThrPoolRecSearch(8, &std::cout))
        );

        void setStartFolder(fs::path sf) {this->startFolder = sf;};
        fs::path getStartFolder() {return this->startFolder;};

        void setStrategy(std::shared_ptr<SearchStrategy> ss) {this->strategy = std::move(ss);};
        std::shared_ptr<SearchStrategy> getStrategy() {return this->strategy;};

        std::future<fs::path> find(fs::path filename, std::launch policy = std::launch::async);

    protected:
        fs::path startFolder;
        std::shared_ptr<SearchStrategy> strategy;
    };

} // namespace fsearch

#endif