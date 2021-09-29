#pragma once

enum ERROR_TYPE {
    OK,
    EMPTY,
    TIMEOUT
};

enum IMAGE_TYPE {
    US,
    CT
};

double USVAL = 0;
double CTVAL = 0;

/// A mock of the hardware API that lets us build without the actual hardware
ERROR_TYPE getImage(IMAGE_TYPE type, double* image) {
    if (type == IMAGE_TYPE::US) {
        USVAL++;
        *image = USVAL;
    } else if (type == IMAGE_TYPE::CT) {
        CTVAL++;
        *image = CTVAL;
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(30ms);

    return ERROR_TYPE::OK;
}
