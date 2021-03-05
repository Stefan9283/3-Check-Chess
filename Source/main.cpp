#include <common.h>
#include "Table.h"
#include "ChessPiece.h"

int main() {
    Table *t1, *t2;
    t1 = new Table();
    t1->printTable();
    t2 = t1->cloneTable(t1->squares[1][1]->cp, vec2{2, 1});
    cout << t2->getCoords(t2->squares[2][1]->cp->position).c_str() << "\n";
    t2->remove(t2->squares[0][1]->cp);
    cout << t2->getTotalScore('w') << "\n";
    t2->move(t2->squares[0][4]->cp, vec2{5, 4});
    t2->printTable();
    // WIP
    //std::cout << t2->squares[5][4]->cp->getPositions(t2).size() << "\n";
    //for (PieceMove move : t2->squares[5][4]->cp->getPositions(t2)) {
    //    std::cout << "$$$$$$$$$$$ another possible position for the bishop $$$$$$$$$$$$$$$$$$$\n";
    //    std::cout << move.ownMove.x << " " << move.ownMove.y << "\n";
    //    Table* t_tmp = t2->cloneTable(t2->squares[4][4]->cp, move.ownMove);
    //    t_tmp->printTable();
    //    delete t_tmp;
    //}
    return 0;
}
