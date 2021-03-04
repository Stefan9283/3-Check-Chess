//
// Created by Stefan on 04-Mar-21.
//

#ifndef INC_3_CHECK_CHESS_CHESSPIECE_H
#define INC_3_CHECK_CHESS_CHESSPIECE_H

#include "common.h"

class ChessPiece {
public:
    char color; // b or w
    vec2 position;
    int symbol;

    ChessPiece(char color, vec2 pos);
};

class King : public ChessPiece {
public:
    King(char color, vec2 pos);
};
class Queen : public ChessPiece {
public:
    Queen(char color, vec2 pos);
};
class Rook : public ChessPiece {
public:
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
    Pawn(char color, vec2 pos);
};


#endif //INC_3_CHECK_CHESS_CHESSPIECE_H
