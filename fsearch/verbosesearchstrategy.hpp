#ifndef VERBOSESEARCHSTRATEGY_HPP
#define VERBOSESEARCHSTRATEGY_HPP

#include <ostream>

#include "searchstrategy.hpp"

namespace fsearch 
{

    class VerboseSearchStrategy : virtual public SearchStrategy 
    {
    public:
        void setLogStream(std::ostream* os) {this->logStream = os;};
        std::ostream* getLogStream() {return logStream;};

    protected:
        std::ostream* logStream;
    };

} // namespace fsearch

#endif