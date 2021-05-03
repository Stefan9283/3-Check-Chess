#ifndef INC_3_CHECK_CHESS_TABLE_H
#define INC_3_CHECK_CHESS_TABLE_H

#include "common.h"
#include "ChessPiece.h"

struct PieceHistory {
    pair<vec2<int>, vec2<int>> move;
};


class Square {
public:
    char color;

    ChessPiece* piece;
    vector<ChessPiece*> possibleMoves;

    Square(char color, ChessPiece* piece);
};

class Table {
public:
    int height = 8, width = 8;
    int orientation = 1, turn = 0;

    default_random_engine generator;

    vector<vector<Square*>> squares;
    vector<vector<ChessPiece*>> pieces;
    vector<PieceHistory> history;

    Table();
    ~Table();

    void movePiece(ChessPiece* piece, vec2<int> pos, char opt);

    void movePiece(ChessPiece* piece, const char* pos, char opt);

    void movePiece(const char* move);

    void removePiece(ChessPiece* piece);
    ChessPiece* getPiece(const char* pos);

    static bool canIPlaceItHere(ChessPiece* cp, Square* sq);
    bool isInside(vec2<int> pos) const;

    string coords2string(vec2<int> pos) const;

    vec2<int> string2coords(const char* coords);

    static int getSquareScore(Square* sq, char myColor);

    Table* createNewState(ChessPiece* piece = nullptr, vec2<int> pos = vec2<int>());
    string pickAMove();
    void printGameBoard(char perspective = 'w', bool fromZero = false, bool yLetters = true, int tabsCount = 0);

    void addMove2History(pair<vec2<int>, vec2<int>> move) {
        history.push_back({move});
    }

    vector<ChessPiece*> getVulnerablePieces(int leastNumOfPiecesThatShouldBeAbleToTakeThePiece = 1);

    void parseMove(const char* s);

    int getDegreesOfFreedoom();

    string getARandomMove();

    string getARandomMoveV2();

    void castleShort(King* king);

    void castleLong(King* king);

    int getNoOfPieces(char color);

    void moveInAdvance(const char* moves, char color);

    bool isAnIllegalMove(ChessPiece* piece, vec2<int> pos);

    bool hasNoPiecesBetween_axis(vec2<int> pos1, vec2<int> pos2);

    bool hasNoPiecesBetween_diagonal(vec2<int> pos1, vec2<int> pos2);

    bool isKingInConflict(King* king, vec2<int> pos);

    bool isKingInDanger(ChessPiece* piece, vec2<int> pos);

    bool hasLegalMoves();

    vector<pair<vec2<int>, vec2<int>>> getAllMoves();

    void markAllPossibleMoves();

    void unmarkAllPossibleMoves();

    bool canEnPassant(Pawn* pawn, vec2<int> pos);

    bool canCastleShort(King* king);

    bool canCastleLong(King* king);

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

