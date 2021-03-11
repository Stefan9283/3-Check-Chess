#include <common.h>
#include "Table.h"
#include <fstream>
#include <Engine.h>

int main() {
    /*
    {
        Table* table = nullptr;

        table = new Table();
        table->printGameBoard();

        if(isAnIllegalMove(table->squares[0][0], table->getPiece("a2")))
            std::cout << "true" << "\n";
        else std::cout << "false" << "\n";

        std::cout << "////////////////////////////////////////////\n";
        for (PieceMove move : table->getPiece("b1")->getPositions(table)) {
            Table* tmp = table->createNewState(table->getPiece("b1"), move.ownMove);
            tmp->printGameBoard();
            delete tmp;
        }
    }*/
    Engine e;
    return 0;
}
