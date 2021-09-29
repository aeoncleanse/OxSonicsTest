/// Attempt at an event handler, but actually was not needed
/*

#pragma once

/// Adapted from https://www.cppstories.com/2019/12/threading-loopers-cpp17/

#include <thread>
#include <atomic>
#include <memory>
#include <functional>
#include <stdexcept>
#include <utility>
#include <mutex>
#include <queue>

class Queue {
    std::thread mThread;
    std::atomic_bool mRunning;
    std::atomic_bool mAbortRequested;
    std::recursive_mutex lock;
    std::queue<double*> queue;

public:
    explicit Queue() = default;

    ~Queue() {
        abortAndJoin();
    }

    bool running() const {
        return mRunning.load();
    }

    void stop() {
        abortAndJoin();
    }

    bool run(); // Start the loop thread
    bool push(double* input); // Push a new input to the queue

private:
    void abortAndJoin(); // Shared implementation of exiting the loop-function and joining to the main thread.
    double* next(); // Get the next entry from the queue, blocking
    void runFunc(); // Constant loop which polls the queue and executes on any entries
};
*/
