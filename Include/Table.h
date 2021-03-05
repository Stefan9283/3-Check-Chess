#ifndef INC_3_CHECK_CHESS_TABLE_H
#define INC_3_CHECK_CHESS_TABLE_H

#include "common.h"
#include "ChessPiece.h"

class ChessPiece;

class Square {
public:
    /*
     *  0 - gol
     * -1 - sah negru
     *  1 - sah alb
     * */
    int type = 0;
    vector<ChessPiece*> possibleMoves;
    ChessPiece *cp{};
};

class Table {
public:
    vector<vector<Square *>> squares;
    const int height = 8, width = 8;
    int orientation = 1;

    Table();
    ~Table();

    void move(ChessPiece* cp, vec2 newPos);
    void remove(ChessPiece* cp);

    bool canIPlaceItHere(ChessPiece* cp, Square* sq);

    string getCoords(vec2 pos);
    bool isInside(vec2 pos) const;

    int getSquareScore(Square* sq, char myColor);
    int getTotalScore(char color);

    Table* cloneTable(ChessPiece* cp, vec2 newPos);

    void printTable();
};

#endif //INC_3_CHECK_CHESS_TABLE_H
