#include <common.h>
#include "Table.h"
#include "ChessPiece.h"

int main() {
    Table* table = new Table();

    table->moveInAdvance("(b2, d2), (g2, f2), (b5, d5), (g4, f4), (b8, c8), (h7, f6), (b4, d4), (g8, f8), (a6, e2)", 'w');
    table->printGameBoard();

    for (int j = 0; j < table->width; j++)
        table->markPossibleMovesForPawn((Pawn*)table->pieces[0][j]);

    table->markPossibleMovesForRook((Rook*)table->pieces[0][8]);
    table->markPossibleMovesForRook((Rook*)table->pieces[0][9]);

    table->markPossibleMovesForKnight((Knight*)table->pieces[0][10]);
    table->markPossibleMovesForKnight((Knight*)table->pieces[0][11]);

    table->markPossibleMovesForBishop((Bishop*)table->pieces[0][12]);
    table->markPossibleMovesForBishop((Bishop*)table->pieces[0][13]);

    table->markPossibleMovesForQueen((Queen*)table->pieces[0][14]);
    table->markPossibleMovesForKing((King*)table->pieces[0][15]);

    for (int i = 0; i < table->height; i++)
        for (int j = 0; j < table->width; j++) {
            std::cout << i + 1 << " " << j + 1 << ": ";

            for (vec2 pos : table->squares[i][j]->possibleNormalMoves)
                std::cout << "(" << pos.x + 1 << ", " << pos.y + 1 << ") ";

            std::cout << "\n";
        }

    return 0;
}
