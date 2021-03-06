#ifndef INC_3_CHECK_CHESS_TABLE_H
#define INC_3_CHECK_CHESS_TABLE_H

#include "common.h"
#include "ChessPiece.h"

class ChessPiece;

class Square {
public:
    std::vector<vec2> possibleNormalMoves;
    std::vector<vec2> possibleSpecialMoves;
    ChessPiece* piece = nullptr;
};

class Table {
public:

    std::vector<std::vector<Square*>> squares;

    std::vector<std::vector<ChessPiece*>> pieces;
    std::vector<std::pair<vec2, vec2>> history;

    const int height = 8, width = 8;
    int orientation = 1;

    Table();
    ~Table();

    // Functii Stefan
    void movePiece(ChessPiece* piece, vec2 pos);
    void movePiece(ChessPiece* piece, const char* pos);
    void removePiece(ChessPiece* piece);
    ChessPiece* getPiece(const char* pos);

    bool isInside(vec2 pos);

    bool canIPlaceItHere(ChessPiece* cp, Square* sq);

    std::string getCoords(vec2 pos);

    int getTotalScore(char color);
    int getSquareScore(Square* sq, char myColor);

    Table* createNewState(ChessPiece* piece, vec2 pos);

    void printTable();
    void programmerPrint();

    void addMove2History(std::pair<vec2, vec2> move) {
        history.push_back(move);
    }

    // Functii Ovidiu
    bool isAnIllegalPiece(ChessPiece* piece, vec2 pos);

    void markPossibleMovesForPawn(Pawn* pawn);

    void markPossibleMovesForKnight(Knight* knight);

    void markPossibleMovesForBishop(Bishop* bishop);

    void markPossibleMovesForRook(Rook* rook);

    void markPossibleMovesForQueen(Queen* queen);
};

#endif //INC_3_CHECK_CHESS_TABLE_H
