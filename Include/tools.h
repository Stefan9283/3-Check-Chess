//
// Created by Stefan on 08-Mar-21.
//

#ifndef INC_3_CHECK_CHESS_TOOLS_H
#define INC_3_CHECK_CHESS_TOOLS_H

#include "common.h"
#include <chrono>

void printTabs(int count);


class Timer {
public:
    std::chrono::high_resolution_clock::time_point then, now;
    Timer();
    ~Timer();
};

#endif //INC_3_CHECK_CHESS_TOOLS_H
