#ifndef THRPOOLRECSEARCH_HPP
#define THRPOOLRECSEARCH_HPP

#include "threadedsearchstrategy.hpp"
#include "verbosesearchstrategy.hpp"

namespace fsearch
{

class ThrPoolRecSearch : public ThreadedSearchStrategy, public VerboseSearchStrategy 
{
    public:
    ThrPoolRecSearch(unsigned int num, std::ostream* os);

    virtual std::future<std::filesystem::path> execute(
            std::filesystem::path startFolder, 
            std::filesystem::path fileName,
            std::launch policy
        ) override;

    private:
};


} // namespace fsearch

#endif