#include "filesearcher.hpp"

namespace fsearch {

    FileSearcher::FileSearcher(fs::path startf, std::shared_ptr<SearchStrategy> ss) :
        startFolder(startf),
        strategy(ss)
    {}

    std::future<fs::path> FileSearcher::find(fs::path filename, std::launch policy ) 
    {
        return strategy->execute(startFolder, filename, policy);
    }
}