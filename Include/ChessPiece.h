
#ifndef INC_3_CHECK_CHESS_CHESSPIECE_H
#define INC_3_CHECK_CHESS_CHESSPIECE_H

#include "common.h"

class ChessPiece {
public:
    char color; // b or w
    vec2 position, prevPos{-INT_MAX, -INT_MAX};
    int score;
    ChessPiece(char color, vec2 pos);
    virtual ~ChessPiece();
    //std::vector<vec2> getPositions();
};

class King : public ChessPiece {
public:
    bool moved = false;
    int checks = 0;
    King(char color, vec2 pos);
};
class Queen : public ChessPiece {
public:
    Queen(char color, vec2 pos);
};
class Rook : public ChessPiece {
public:
    bool moved = false;
    Rook(char color, vec2 pos);
};
class Knight : public ChessPiece {
public:
    Knight(char color, vec2 pos);
};
class Bishop : public ChessPiece {
public:
    Bishop(char color, vec2 pos);
};
class Pawn : public ChessPiece {
public:
    bool moved = false;
    Pawn(char color, vec2 pos);
};


#endif //INC_3_CHECK_CHESS_CHESSPIECE_H
