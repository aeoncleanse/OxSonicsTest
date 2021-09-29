#include <future>
#include <thread>
#include "fetchLoop.hpp"

int main() {
    // Create the thread locks
    std::mutex CTLock;
    std::mutex USLock;

    // Two CT threads
    std::thread CT1(saveImagesLoop<IMAGE_TYPE::CT>, std::ref(CTLock)); // Make the CT loop
    std::thread CT2(saveImagesLoop<IMAGE_TYPE::CT>, std::ref(CTLock)); // Make the CT loop
    std::thread CT3(saveImagesLoop<IMAGE_TYPE::CT>, std::ref(CTLock)); // Make the CT loop

    // Two US threads
    std::thread US1(saveImagesLoop<IMAGE_TYPE::US>, std::ref(USLock)); // Make the CT loop
    std::thread US2(saveImagesLoop<IMAGE_TYPE::US>, std::ref(USLock)); // Make the CT loop
    std::thread US3(saveImagesLoop<IMAGE_TYPE::US>, std::ref(USLock)); // Make the CT loop

    CT1.join();
    CT2.join();
    CT3.join();
    US1.join();
    US2.join();
    US3.join();

    return 0;
}
// We're going to run two threads which loop and handle the actual call, pushing the returned value to a queue
// We therefore also need an event queue which takes doubles and writes them to disk at its own pace