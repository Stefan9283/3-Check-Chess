
#ifndef INC_3_CHECK_CHESS_ALGOPICKER_H
#define INC_3_CHECK_CHESS_ALGOPICKER_H

#include "../../../Stefan/Downloads/3-Check-Chess-Omega/3-Check-Chess-Omega/Include/common.h"
#include "Algorithm.h"

class AlgoPicker {
public:
    virtual Algorithm* pickAlgorithm(Table* t) = 0;
    virtual ~AlgoPicker() = default;
    vec2<float> CalculateStateScore(Table* t);
};

class TestPicker : public AlgoPicker {
public:
    Algorithm* pickAlgorithm(Table* t) override;
};

class DefaultPicker : public AlgoPicker {
public:
    Algorithm* pickAlgorithm(Table* t) override;
};

#endif //INC_3_CHECK_CHESS_ALGOPICKER_H
