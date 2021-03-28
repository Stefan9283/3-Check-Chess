//
// Created by Stefan on 08-Mar-21.
//

#include "tools.h"

void printTabs(int count) {
    for (int i = 0; i < count; ++i)
        std::cout << "\t";
}

Timer::Timer() {
    then = std::chrono::high_resolution_clock::now();
    now = then;
}
Timer::~Timer() {
    now = std::chrono::high_resolution_clock::now();
    std::cout << "Execution took " << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count() << " ms\n";
}
