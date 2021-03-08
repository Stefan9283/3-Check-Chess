//
// Created by Stefan on 08-Mar-21.
//

#ifndef INC_3_CHECK_CHESS_ALGORITHM_H
#define INC_3_CHECK_CHESS_ALGORITHM_H

#include "common.h"
#include "Table.h"

class Algorithm {
public:
    virtual std::string pickMove(Table* t) = 0;
    virtual ~Algorithm() = default;
};


class RandomChessPiecePicker : public Algorithm {
public:
    std::string pickMove(Table* t) override;
};

#endif //INC_3_CHECK_CHESS_ALGORITHM_H
