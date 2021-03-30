#ifndef INC_3_CHECK_CHESS_TABLE_H
#define INC_3_CHECK_CHESS_TABLE_H

#include "common.h"
#include "ChessPiece.h"

typedef struct PieceHistory {
    std::pair<vec2<int>, vec2<int>> move;
} PieceHistory;

class Square {
public:
    char color;
    ChessPiece* piece;
    std::vector<ChessPiece*> possibleMoves;

    Square(char color, ChessPiece* piece);
};

class Table {
public:
    int height = 8, width = 8;
    int orientation = 1, turn = 0;

    std::vector<std::vector<Square*>> squares;
    std::vector<std::vector<ChessPiece*>> pieces;
    std::vector<PieceHistory> history;

    Table();
    ~Table();

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
    void printGameBoard(char perspective = 'w', bool fromZero = false, bool yLetters = true, int tabsCount = 0);

    void addMove2History(std::pair<vec2<int>, vec2<int>> move) {
        history.push_back({move});
    }

    void parseMove(const char* s);

    std::string getARandomMove();
};

#endif //INC_3_CHECK_CHESS_TABLE_H

