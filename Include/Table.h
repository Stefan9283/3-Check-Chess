#ifndef INC_3_CHECK_CHESS_TABLE_H
#define INC_3_CHECK_CHESS_TABLE_H

#include "common.h"
#include "ChessPiece.h"
#include "Tree.h"

class ChessPiece;

typedef struct PieceHistory {
    ChessPiece* piece;
    std::pair<vec2<int>, vec2<int>> move;
} PieceHistory;

class Square {
public:
    char color;

    ChessPiece* piece;
    std::vector<ChessPiece*> possibleNormalMoves;

    Square(char color, ChessPiece* piece);
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
    void movePiece(ChessPiece* piece, vec2<int> pos);
    void movePiece(ChessPiece* piece, const char* pos);
    void movePiece(const char* move);
    void removePiece(ChessPiece* piece);
    ChessPiece* getPiece(const char* pos);

    static bool canIPlaceItHere(ChessPiece* cp, Square* sq);
    bool isInside(vec2<int> pos) const;

    std::string coords2string(vec2<int> pos) const;
    vec2<int> string2coords(const char* coords);

    int getTotalScore(char color);
    static int getSquareScore(Square* sq, char myColor);

    Table* createNewState(ChessPiece* piece = nullptr, vec2<int> pos = vec2<int>());
    std::string pickAMove();
    void printGameBoard(char perspective = 'w', bool fromZero = false, bool xLetters = true, int tabsCount = 0);

    void addMove2History(ChessPiece* piece, std::pair<vec2<int>, vec2<int>> move) {
        history.push_back({piece, move});
    }

    // Functii Ovidiu
    void parseMove(const char* s);

    std::string getBestMove(int depth);

    std::string getARandomMove();

    int getTotalScore();

    void moveInAdvance(const char* moves, char color);

    bool isAnIllegalMove(ChessPiece* piece, vec2<int> pos);

    bool hasNoPiecesBetween_line(vec2<int> pos1, vec2<int> pos2);

    bool hasNoPiecesBetween_diagonal(vec2<int> pos1, vec2<int> pos2);

    bool isKingInConflict(King* king, vec2<int> pos);

    bool hasLegalMoves();

    void markAllPossibleMoves();

    void unmarkAllPossibleMoves();

    void markPossibleMovesForPawn(Pawn* pawn);

    void markPossibleMovesForKnight(Knight* knight);

    void markPossibleMovesForBishop(Bishop* bishop);

    void markPossibleMovesForRook(Rook* rook);

    void markPossibleMovesForQueen(Queen* queen);

    void markPossibleMovesForKing(King* king);

    bool isSquareOfTheSameColor(vec2<int> pos1, vec2<int> pos2);

    bool isSquareOfTheSameColor(ChessPiece* piece1, ChessPiece* piece2);
};

#endif //INC_3_CHECK_CHESS_TABLE_H

