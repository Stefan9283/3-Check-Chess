
#ifndef INC_3_CHECK_CHESS_TABLE_H
#define INC_3_CHECK_CHESS_TABLE_H

#include "common.h"

class Square {
public:
    /*
     *  0 - gol
     * -1 - sah negru
     *  1 - sah alb
     *
     * */
    int type = 0;
    ChessPiece *cp{};
};

class Table {
public:
    vector<vector<Square *>> mat;
    const int DIM = 8;
    int orientation = 1;

    Table();
};

#endif //INC_3_CHECK_CHESS_TABLE_H
