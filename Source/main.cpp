#include <common.h>
#include "Table.h"
#include "ChessPiece.h"

int main() {
    auto* table = new Table();
    table->moveInAdvance("(e2, e4), (d7, d5), (f1, c4), (g8, f6), (d2, d3)",'w');
    table->printGameBoard('w');

    //for (int j = 0; j < table->width; j++)
    //    table->markPossibleMovesForPawn((Pawn*)table->pieces[0][j]);
    //table->markPossibleMovesForRook((Rook*)table->pieces[0][8]);
    //table->markPossibleMovesForRook((Rook*)table->pieces[0][9]);
    //table->markPossibleMovesForKnight((Knight*)table->pieces[0][10]);
    //table->markPossibleMovesForKnight((Knight*)table->pieces[0][11]);
    //table->markPossibleMovesForBishop((Bishop*)table->pieces[0][12]);
    //table->markPossibleMovesForBishop((Bishop*)table->pieces[0][13]);
    //table->markPossibleMovesForQueen((Queen*)table->pieces[0][15]);
    //table->markPossibleMovesForKing((King*)table->pieces[0][14]);

    //or (int i = 0; i < table->height; i++)
    //   for (int j = 0; j < table->width; j++) {
    //       std::cout << i + 1 << " " << j + 1 << ": ";
    //       for (vec2 pos : table->squares[i][j]->possibleNormalMoves)
    //           std::cout << "(" << pos.x + 1 << ", " << pos.y + 1 << ") ";
    //       std::cout << "\n";
    //   }

    return 0;
}
