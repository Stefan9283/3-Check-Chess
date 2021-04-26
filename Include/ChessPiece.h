#ifndef INC_3_CHECK_CHESS_CHESSPIECE_H
#define INC_3_CHECK_CHESS_CHESSPIECE_H

#include "common.h"

class Table;

class ChessPiece;

struct PieceMove {
    vec2<int> ownMove;

    int score = 0;

    ChessPiece* whoElseToMove = nullptr;
    vec2<int> otherMove{ 0, 0 };
};

class ChessPiece {
public:
    char color, abbreviation;
    int score, index;
    int noOfMoves = 0;
    vec2<int> pos{};

    ChessPiece(char color, vec2<int> pos, int index);

    virtual ~ChessPiece();

    virtual vector<PieceMove> getPositions(Table* t) = 0;
};

class King : public ChessPiece {
public:
    bool castle = false;
    bool wasMoved = false;
    int checks = 0;

    King(char color, vec2<int> pos, int index);

    vector<PieceMove> getPositions(Table* t) override;

    bool isInCheck(Table* table);
};

class Queen : public ChessPiece {
public:
    Queen(char color, vec2<int> pos, int index);

    vector<PieceMove> getPositions(Table* t) override;
};

class Rook : public ChessPiece {
public:
    bool wasMoved = false;

    Rook(char color, vec2<int> pos, int index);

    vector<PieceMove> getPositions(Table* t) override;
};

class Knight : public ChessPiece {
public:
    Knight(char color, vec2<int> pos, int index);

    vector<PieceMove> getPositions(Table* t) override;
};

class Bishop : public ChessPiece {
public:
    Bishop(char color, vec2<int> pos, int index);

    vector<PieceMove> getPositions(Table* t) override;
};

class Pawn : public ChessPiece {
public:
    bool wasMoved = false;

    Pawn(char color, vec2<int> pos, int index);

    vector<PieceMove> getPositions(Table* t) override;

    ChessPiece* promotePawn(Table* table, char op);
};

#endif //INC_3_CHECK_CHESS_CHESSPIECE_H
