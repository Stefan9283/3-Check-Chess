#include <Engine.h>

int main() {
    Engine e;

    /*Table* table = new Table();

    table->moveInAdvance("(e2, e4), (a7, a5), (d2, d4), (e7, e6), (c2, c4), (f8, b4), (c1, d2), (b4, d2), (d1, d2), (d8, h4), (g2, g3), (h4, e4), (d2, e2), (e4, h1), (g1, f3), (a5, a4), (b2, b3), (a4, b3), (a2, b3), (a8, a1), (e2, e5), (a1, b1), (e1, e2), (h1, f1), (e2, d2), (f1, f2), (d2, d3), (b1, b3), (d3, e4), (b3, e3), (e4, f4), (f2, f3), (f4, g5), (f7, f6), (g5, h4), (f6, e5), (h4, g5), (e5, d4), (g5, h4)", 'w');
    std::cout << table->getBestMove(4);*/
    /*Tree* tree = new Tree(table);

    tree->root->moveInAdvanceOnState("(e2, e4), (a7, a5), (d2, d4), (e7, e6), (c2, c4), (f8, b4), (c1, d2), (b4, d2), (d1, d2), (d8, h4), (g2, g3), (h4, e4), (d2, e2), (e4, h1), (g1, f3), (a5, a4), (b2, b3), (a4, b3), (a2, b3), (a8, a1), (e2, e5), (a1, b1), (e1, e2), (h1, f1), (e2, d2), (f1, f2), (d2, d3), (b1, b3), (d3, e4), (b3, e3), (e4, f4), (f2, f3), (f4, g5), (f7, f6), (g5, h4), (f6, e5), (h4, g5), (e5, d4), (g5, h4)", 'w');
    tree->root->blabla();
    tree->baseTable->printGameBoard();

    for (ChessPiece* piece : tree->baseTable->pieces[0])
        std::cout << piece->pos.toString() << "\n";

    std::cout << "\n";

    for (ChessPiece* piece : tree->baseTable->pieces[1])
        std::cout << piece->pos.toString() << "\n";*/

    /*table->moveInAdvance("(e2, e4), (a7, a5), (d2, d4), (e7, e6), (c2, c4), (f8, b4), (c1, d2), (b4, d2), (d1, d2), (d8, h4), (g2, g3), (h4, e4), (d2, e2), (e4, h1), (g1, f3), (a5, a4), (b2, b3), (a4, b3), (a2, b3), (a8, a1), (e2, e5), (a1, b1), (e1, e2), (h1, f1), (e2, d2), (f1, f2), (d2, d3), (b1, b3), (d3, e4), (b3, e3), (e4, f4), (f2, f3), (f4, g5), (f7, f6), (g5, h4), (f6, e5), (h4, g5), (e5, d4), (g5, h4)", 'w');

    std::cout << table->getBestMove(3);*/

    return 0;
}
