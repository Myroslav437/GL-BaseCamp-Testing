#ifndef THREADEDSEARCHSTRATEGY_HPP
#define THREADEDSEARCHSTRATEGY_HPP

#include "searchstrategy.hpp"

namespace fsearch 
{

    class ThreadedSearchStrategy : virtual public SearchStrategy 
    {
    public:
        ThreadedSearchStrategy() {};
        ThreadedSearchStrategy(unsigned int tnum) : threadNum(tnum) {};

        void setThreadNum(unsigned int num) {this->threadNum = num;};
        unsigned int getThreadNum() {return threadNum;};

    protected:
        unsigned int threadNum = 1;
    };

} // namespace fsearch

#endif