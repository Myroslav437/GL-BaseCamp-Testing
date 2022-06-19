#include "simplethreadpool.hpp"

namespace fsearch
{
    
    SimpleThreadPool::SimpleThreadPool(int numThreads) 
    {
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(&SimpleThreadPool::run, this);
        }
    }

    void SimpleThreadPool::run() 
    {
        while (!stopFlag) {
            std::unique_lock<std::mutex> myLock(tasksMutex);

            // sleep if there is no tasks
            // continue if a new task was added or the stopFlag was rised;
            addTaskCv.wait(myLock, [this] { 
                return !tasks.empty() || stopFlag;
            });

            // bypass if the thread was awakened due to the stopFlag
            if (!tasks.empty()) {

                // get the front task with extraction
                auto elem = std::move(tasks.front());
                tasks.pop();

                // unlock since the work with the tasks container is done
                myLock.unlock();

                // run the task 
                elem.get();

                // increase the completedTasks counter
                // notify the waitAll method (if invoked)
                ++completedTasks;
                completeTaskCv.notify_all();
            }
        }
    }

    void SimpleThreadPool::waitAll() 
    {
        std::unique_lock<std::mutex> myLock(tasksMutex);
        
        // wait for a notification from the run() method
        completeTaskCv.wait(myLock, [this] {
            return stopFlag || (tasks.empty() && addedTasks == completedTasks);
        });
    }

    void SimpleThreadPool::softShutdown() 
    {
        stopFlag = true;
         for (int i = 0; i < threads.size(); ++i) {
            addTaskCv.notify_all();
        }
    }

    SimpleThreadPool::~SimpleThreadPool() {
        stopFlag = true;
        for (int i = 0; i < threads.size(); ++i) {
            addTaskCv.notify_all();
            
            if(threads[i].joinable()) {
                threads[i].join();
            }
        }
    }


} // namespace fsearch