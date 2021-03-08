
#ifndef INC_3_CHECK_CHESS_ALGOPICKER_H
#define INC_3_CHECK_CHESS_ALGOPICKER_H

#include "common.h"
#include "Algorithm.h"

class AlgoPicker {
public:
    virtual Algorithm* pickAlgorithm(Table* t) = 0;
    virtual ~AlgoPicker() = default;
};

class TestPicker : public AlgoPicker {
public:
    Algorithm* pickAlgorithm(Table* t) override;
};

#endif //INC_3_CHECK_CHESS_ALGOPICKER_H
