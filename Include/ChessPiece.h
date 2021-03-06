#ifndef INC_3_CHECK_CHESS_CHESSPIECE_H
#define INC_3_CHECK_CHESS_CHESSPIECE_H

#include "common.h"

class Table;

class ChessPiece;

struct PieceMove {
    vec2 ownMove;

    int score = 0;

    ChessPiece* whoElseToMove = nullptr;
    vec2 otherMove{ 0, 0 };
};

class ChessPiece {
public:
    char color;
    vec2 pos;
    int score;
    char abbreviation;

    int index;

    ChessPiece(char color, vec2 pos, int index);

    virtual ~ChessPiece();

    virtual std::vector<PieceMove> getPositions(Table* t) = 0;
};

class King : public ChessPiece {
public:
    bool castle = false;

    bool wasMoved = false;

    int checks = 0;

    King(char color, vec2 pos, int index);

    int isCheck(Table* t, ChessPiece* cp);

    std::vector<PieceMove> getPositions(Table* t) override;

    // Functii Ovidiu
    bool isInCheckAt(Table* table, vec2 pos);
};

class Queen : public ChessPiece {
public:
    Queen(char color, vec2 pos, int index);

    std::vector<PieceMove> getPositions(Table* t) override;
};

class Rook : public ChessPiece {
public:
    bool wasMoved = false;

    Rook(char color, vec2 pos, int index);

    std::vector<PieceMove> getPositions(Table* t) override;
};

class Knight : public ChessPiece {
public:
    Knight(char color, vec2 pos, int index);

    std::vector<PieceMove> getPositions(Table* t) override;
};

class Bishop : public ChessPiece {
public:
    Bishop(char color, vec2 pos, int index);

    std::vector<PieceMove> getPositions(Table* t) override;
};

class Pawn : public ChessPiece {
public:
    bool wasMoved = false;

    Pawn(char color, vec2 pos, int index);

    std::vector<PieceMove> getPositions(Table* t) override;
};

#endif //INC_3_CHECK_CHESS_CHESSPIECE_H
