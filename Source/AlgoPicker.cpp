//
// Created by Stefan on 08-Mar-21.
//

#include "AlgoPicker.h"

Algorithm* TestPicker::pickAlgorithm(Table* t) {
    return new RandomChessPiecePicker;
}

