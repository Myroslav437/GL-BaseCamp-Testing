#ifndef SEARCHSTRATEGY_HPP
#define SEARCHSTRATEGY_HPP

#include <future>
#include <filesystem>

namespace fsearch {

    class SearchStrategy 
    {
    public:
        virtual std::future<std::filesystem::path> execute(
            std::filesystem::path startFolder, 
            std::filesystem::path fileName
        ) = 0;
    };

} // namespace fsearch

#endif