#ifndef INC_3_CHECK_CHESS_TABLE_H
#define INC_3_CHECK_CHESS_TABLE_H

#include "common.h"
#include "ChessPiece.h"
#include "Tree.h"

class ChessPiece;

typedef struct PieceHistory {
    ChessPiece* piece;
    std::pair<vec2, vec2> move;
} PieceHistory;

class Square {
public:
    std::vector<ChessPiece*> possibleNormalMoves;

    ChessPiece* piece = nullptr;
};

class Table {
public:
    int height = 8, width = 8;
    int orientation = 1, turn = 0;

    std::vector<std::vector<Square*>> squares;
    std::vector<std::vector<ChessPiece*>> pieces;

    std::vector<PieceHistory> history;

    // Not permanent
    bool shortCastle_white = false;
    bool shortCastle_black = false;

    bool longCastle_white = false;
    bool longCastle_black = false;

    Table();
    ~Table();

    // Functii Stefan
    void movePiece(ChessPiece* piece, vec2 pos);
    void movePiece(ChessPiece* piece, const char* pos);
    void removePiece(ChessPiece* piece);
    ChessPiece* getPiece(const char* pos);

    static bool isAnIllegalMove(Square* sq, ChessPiece* piece);
    static bool canIPlaceItHere(ChessPiece* cp, Square* sq);
    bool isInside(vec2 pos) const;

    std::string coords2string(vec2 pos) const;
    vec2 string2coords(const char* coords);

    int getTotalScore(char color);
    static int getSquareScore(Square* sq, char myColor);

    Table* createNewState(ChessPiece* piece = nullptr, vec2 pos = vec2());
    std::string pickAMove();
    void printGameBoard(char perspective = 'w', bool fromZero = false, bool xLetters = true, int tabsCount = 0);

    void addMove2History(ChessPiece* piece, std::pair<vec2, vec2> move) {
        history.push_back({piece, move});
    }

    // Functii Ovidiu
    std::string makeBestMove();

    int getTotalScore(int turn);

    void moveInAdvance(const char* moves, char color);

    bool isAnIllegalMove(ChessPiece* piece, vec2 pos);

    bool hasNoPiecesBetween_line(vec2 pos1, vec2 pos2);

    bool hasNoPiecesBetween_diagonal(vec2 pos1, vec2 pos2);

    bool isKingInConflict(King* king, vec2 pos);

    void markAllPossibleMoves(int turn);

    void unmarkAllPossibleMoves();

    void markPossibleMovesForPawn(Pawn* pawn);

    void markPossibleMovesForKnight(Knight* knight);

    void markPossibleMovesForBishop(Bishop* bishop);

    void markPossibleMovesForRook(Rook* rook);

    void markPossibleMovesForQueen(Queen* queen);

    void markPossibleMovesForKing(King* king);
};

#endif //INC_3_CHECK_CHESS_TABLE_H

