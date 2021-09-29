/// Attempt at an event handler, but actually was not needed
/*
#include "Queue.hpp"

bool Queue::run() {
    try {
        mThread = std::thread(&Queue::runFunc, this);
    } catch(...) {
        return false;
    }

    return true;
}

bool Queue::push(double* input) {
    if (!running()) {
        return false;
    }

    try {
        std::lock_guard guard(lock); // CTAD, C++17

        queue.push(input);
    } catch(...) {
        return false;
    }

    return true;
}

double* Queue::next() {
    std::lock_guard guard(lock); // CTAD, C++17

    if(queue.empty()) {
        return nullptr;
    }

    double* out = queue.front();
    queue.pop();

    return out;
}

void Queue::runFunc() {
    using namespace std::chrono_literals;
    mRunning.store(true);

    while(!mAbortRequested.load()) {
        try {
            double* img = next();
            if (img != nullptr) {
                // Do the actual handling of the image (which is a double)
                fprintf(stdout, "DEBUG: Processing double - %f", *img);
            } else {
                std::this_thread::sleep_for(1ms);
            }
        } catch(std::runtime_error& e) {
            // Some more specific
        } catch(...) {
            // Make sure that nothing leaves the thread for now...
        }
    }

    mRunning.store(false);
}

void Queue::abortAndJoin() {
    mAbortRequested.store(true);
    if(mThread.joinable()) {
        mThread.join();
    }
}
*/
