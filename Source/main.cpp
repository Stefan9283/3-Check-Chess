#include <Engine.h>

int main() {
    //Engine e;

    Table* table = new Table();

    table->moveInAdvance("(e2, e4), (g7, g6), (d2, d4), (f7, f6), (e4, e5), (h7, h5), (e5, e6), (d7, e6), (d4, d5), (d8, d5), (d1, d5)", 'w');

    table->printGameBoard();

    std::cout << table->getARandomMove();

   /* std::cout << "\n";

    for (ChessPiece* piece : table->pieces[0])
        if (piece)
            std::cout << piece->pos.toString() << "\n";

    std::cout << "\n";

    for (ChessPiece* piece : table->pieces[1])
        if (piece)
            std::cout << piece->pos.toString() << "\n";*/
        
    //table->moveInAdvance("(e2, e4), (a7, a5), (d2, d4), (a5, a4), (d4, d5), (a4, a3), (d5, d6), (a3, b2), (c1, b2), (a8, a2), (a1, a2)", 'w');
    //table->printGameBoard();


    //Tree* tree = new Tree(table);

    //tree->createTree(tree->root, 0,2);
    //tree->printTree(tree->root, 0);

    //std::cout << table->getBestMove(2);
    //tree->printTree(tree->root, 0);
    
    return 0;
}
