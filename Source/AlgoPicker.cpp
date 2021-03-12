

#include "AlgoPicker.h"


vec2<float> AlgoPicker::CalculateStateScore(Table *t) {
    Algorithm* algo = pickAlgorithm(t);
    vec2<float> scores = algo->CalculateStateScore(t);
    delete algo;
    return scores;
}

Algorithm* TestPicker::pickAlgorithm(Table* t) {
    return new RandomChessPiecePicker;
}
Algorithm *DefaultPicker::pickAlgorithm(Table *t) {
    return nullptr;
}


