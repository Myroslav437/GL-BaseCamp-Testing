#ifndef SIMPLETHREADPOOL_HPP
#define SIMPLETHREADPOOL_HPP

#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class SimpleThreadPool 
{
public:
    SimpleThreadPool(int numThreads);
    void waitAll();

    template <class Func, class ...Args>
    void addTask(const Func& taskFunc, Args&&... args);
    void shutdown();

    ~SimpleThreadPool();

protected:
    void run();                             // method to run a task

private:
    std::queue<std::future<void>> tasks;    // container to store added tasks
    std::vector<std::thread> threads;       // container to store the threads objects

    std::mutex tasksMutex;                  // mutex to sync the tasks container

    std::condition_variable addTaskCv;      // condition_variable to notify on task addition
    std::condition_variable completeTaskCv; // condition_variable to notify on task completion

    std::atomic<bool> stopFlag = false;     // flag to stop the thread pool
    std::atomic<int> addedTasks = 0;        // variable to store the amount of added tasks
    std::atomic<int> completedTasks = 0;    // variable to store the amount of finished tasks
};

template <class Func, class ...Args>
void SimpleThreadPool::addTask(const Func& taskFunc, Args&&... args) 
{
    // Increase the value of added tasks counter
    ++addedTasks;

    std::lock_guard<std::mutex> myLock(tasksMutex);

    tasks.emplace(std::async(std::launch::deferred, taskFunc, args...));
    
    // notify a sleepling thread (if any) in the run() method
    addTaskCv.notify_one();
}

#endif