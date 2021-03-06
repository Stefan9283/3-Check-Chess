#include <common.h>
#include "Table.h"
#include "ChessPiece.h"

int main() {
    Table* t = new Table();
    ChessPiece* piece = t->squares[0][1]->piece;
    t->movePiece(piece, "f3");
    King* k = dynamic_cast<King*>(t->pieces[0][15]);
    t->movePiece(k, "c4");
    t->movePiece(t->getPiece("b3"), "3c");
    t->movePiece(t->getPiece("a8"), "c8");
    //t->printTable();
    /*
    int i = 0;
    for (ChessPiece* piece : t->pieces[0]) {
        std::cout << k->isCheck(t, piece) << " ";
        if (i == 7) std::cout << "\n";
        i++;
    }
    /*
     * [Stefan T]: n-ar trebui sa fie
     * 0 0 1 0 1 0 0 0
     * 0 1 0 0 0 0 0 0
     * ?
     *
     * (sunt pe prima linie pionii apoi pe a doua
     * turaL, turaR, nebunL, ... regina, rege)
     * */

    t->movePiece(t->getPiece("c8"), "e4");
    t->programmerPrint();

    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    for (PieceMove move : t->getPiece("e4")->getPositions(t)) {
        Table* tmp = t->createNewState(t->getPiece("e4"), move.ownMove);
        tmp->programmerPrint();
        delete tmp;
    }

    return 0;
}
