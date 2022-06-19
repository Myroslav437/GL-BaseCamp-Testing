#ifndef THRPOOLRECSEARCH_HPP
#define THRPOOLRECSEARCH_HPP

#include "threadedsearchstrategy.hpp"
#include "verbosesearchstrategy.hpp"

namespace fsearch
{

class ThrPoolRecSearch : public ThreadedSearchStrategy, public VerboseSearchStrategy 
{
    public:
    virtual std::future<std::filesystem::path> execute(
            std::filesystem::path startFolder, 
            std::filesystem::path fileName
        ) override;

    private:
};


} // namespace fsearch

#endif