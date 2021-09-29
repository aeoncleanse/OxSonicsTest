#pragma once

#include <mutex>
#include <string>
#include <fstream>
#include "device.hpp"

// How long should we wait for a response before deciding the hardware crashed?
constexpr int hardwareTimeout = 2;

// Create the thread locks
std::mutex CTLock;
std::mutex USLock;

template<IMAGE_TYPE type>
constexpr std::mutex& getLock() {
    if (type == IMAGE_TYPE::US) {
        return USLock;
    } else if (type == IMAGE_TYPE::CT) {
        return CTLock;
    }
}

template<IMAGE_TYPE type>
std::vector<double> getImages() {
    std::vector<double> toWrite;

    // Wait until we have the lock
    std::lock_guard guard(getLock<type>());

    while (toWrite.size() < 100) {
        try {
            // Set up a future, so we can asynchronously call to getImage based on type
            double result;
            std::future<ERROR_TYPE> response = std::async(getImage, type, &result);

            // Await the future's resolution. A timeout here indicates a hardware failure.
            std::future_status status = response.wait_for(std::chrono::seconds(hardwareTimeout));
            if (status == std::future_status::timeout) {
                fprintf(stderr, "Hardware failure detected by response timeout for image type %s\n",
                        type == IMAGE_TYPE::US ? "US" : "CT");
                return toWrite;
            }

            const ERROR_TYPE final = response.get();

            // If the result is OK, we need to push it to the queue for handling
            switch(final) {
                case(ERROR_TYPE::OK):
                    toWrite.push_back(result);
                    continue;
                case(ERROR_TYPE::EMPTY):
                    continue;
                case(ERROR_TYPE::TIMEOUT):
                    fprintf(stderr, "Timeout reported by hardware for image type %s\n",
                            type == IMAGE_TYPE::US ? "US" : "CT");
                    return toWrite;
            }
        } catch (const std::exception& e) {
            fprintf(stderr, "Exception caught: %s", e.what());
            return toWrite;
        }
    }

    return toWrite;
}

// TODO: This is what we want to do an integration test on
//  - Call this, check it outputs to console as expected
//  - Or, once fully implemented to save files, check all the files exist as expected
template<IMAGE_TYPE type>
void saveImages() {

    std::vector<double> toWrite = getImages<type>();
    fprintf(stdout, "DEBUG: writing %s\n", type == IMAGE_TYPE::US ? "US" : "CT");

    // Loop over the array and write it to disk
    for (const double img : toWrite) {
        std::string typeAsString = type == IMAGE_TYPE::US ? "US" : "CT";
        std::string filename = typeAsString + "_" + std::to_string((int)img) + ".txt";

        //fprintf(stdout, "DEBUG: Writing file %s\n", filename.c_str());

        /// This bit is commented out because testing is easier done in the console
        /// Otherwise we'd have to be deleting all these files all the time!
        //std::ofstream outfile (filename); // May need to specify a full path, or allow user to specify a dir
        //outfile << imgAsString << std::endl;
        //outfile.close();
    }
}

template<IMAGE_TYPE type>
[[noreturn]] void saveImagesLoop() {
    fprintf(stdout, "DEBUG: Starting %s\n", type == IMAGE_TYPE::US ? "US" : "CT");
    while(true) {
        saveImages<type>();
    }
}
