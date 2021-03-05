#include <common.h>
#include <Table.h>
#include "ChessPiece.h"

int main() {
    Table *t, *t2;
    t = new Table();
    t->printTable();
    t2 = t->copyTable(t->squares[1][1]->cp, vec2{2, 1});
    t2->printTable();
    cout << t2->getRealCoords(t2->squares[2][1]->cp->position).c_str() << "\n";
    cout << t2->getTotalScore('w') << "\n";
    t2->Delete(t->squares[0][0]->cp);
    t2->printTable();
    cout << t2->getTotalScore('w') << "\n";
    return 0;
}
