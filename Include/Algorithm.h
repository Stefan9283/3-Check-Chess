//
// Created by Stefan on 08-Mar-21.
//

#ifndef INC_3_CHECK_CHESS_ALGORITHM_H
#define INC_3_CHECK_CHESS_ALGORITHM_H

#include "../../../Stefan/Downloads/3-Check-Chess-Omega/3-Check-Chess-Omega/Include/common.h"
#include "../../../Stefan/Downloads/3-Check-Chess-Omega/3-Check-Chess-Omega/Include/Table.h"

class Algorithm {
public:
    virtual string pickMove(Table* t) = 0;
    virtual ~Algorithm() = default;
    virtual vec2<float> CalculateStateScore(Table* t) = 0;
};


class RandomChessPiecePicker : public Algorithm {
public:
    string pickMove(Table* t) override;
    vec2<float> CalculateStateScore(Table* t) override;
};

class BringThemOn : public Algorithm {
public:
    string pickMove(Table* t) override;
    vec2<float> CalculateStateScore(Table* t) override;
}; // NormalMode

class IamDeathIncarnate : public Algorithm {
public:
    string pickMove(Table* t) override;
    vec2<float> CalculateStateScore(Table* t) override;
}; // AggressiveMode

class dontHurtMe : public Algorithm {
public:
    string pickMove(Table* t) override;
    vec2<float> CalculateStateScore(Table* t) override;
}; // DefensiveMode

class UberMode : public Algorithm {
public:
    string pickMove(Table* t) override;
    vec2<float> CalculateStateScore(Table* t) override;
};




#endif //INC_3_CHECK_CHESS_ALGORITHM_H
