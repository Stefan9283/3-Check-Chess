#include <common.h>
#include "Table.h"

int main() {
    //Table* t = new Table();
    //t->moveInAdvance("(e2, e4), (d7, d5), (f1, c4), (g8, f6), (d2, d3)",'w');
    //t->printGameBoard('r', false, true, 1);

    //std::cout << t->pickAMove().c_str() << "\n";
    //std::cout << t->history[0].move.first.toString() << t->history[0].move.second.toString() << "\n";

    //signal(SIGTERM, SIG_IGN);
    //char s[256];
    //setbuf(stdin, NULL);
    //setbuf(stdout, NULL);
    //while (true) {
    //    fflush(stdout);
    //    fgets(s, 256, stdin);
    //    if (strstr(s, "xboard")) continue;
    //    if (strstr(s, "protover 2")) {
    //        std::cout << "feature sigint=0 sigterm=0 san=1 myname=blue_thing\n"; //
    //    }
    //    if (strstr(s, "new")) {
    //        if (t) delete t;
    //        t = new Table();
    //        std::cout << "black\n";
    //    }
    //    if (strstr(s, "quit")) {
    //        if (t) delete t;
    //        break;
    //    }
    //    std::cout << t->pickAMove().c_str() << "\n";
    //}
//

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

    //for (int i = 0; i < table->height; i++)
    //   for (int j = 0; j < table->width; j++) {
    //       std::cout << i + 1 << " " << j + 1 << ": ";
    //       for (vec2 pos : table->squares[i][j]->possibleNormalMoves)
    //           std::cout << "(" << pos.x + 1 << ", " << pos.y + 1 << ") ";
    //       std::cout << "\n";
    //   }

    Table* table = new Table();
    Tree* tree = new Tree(table);

    tree->createTree(tree->root, 0, 2);
    tree->printTree(tree->root, 0);
    return 0;
}
