#include <Engine.h>

int main() {
    //Engine e;

    Table* table = new Table();

    table->moveInAdvance("(e2, e4), (e7, e5), (d2, d4), (d8, h4), (d1, f3), (e5, d4), (g2, g3)", 'w');

    Tree* tree = new Tree(table);

    tree->createTree(tree->root, 0, 4);

    //std::cout << table->getBestMove(4);
    /*Tree* tree = new Tree(table);

    tree->root->moveInAdvanceOnState("(e2, e4), (c7, c6), (d2, d4), (f7, f5), (e4, f5), (g8, f6), (g1, f3), (c6, c5), (f3, e5), (h7, h6), (d4, c5), (b8, c6), (e5, c6), (d7, c6), (f1, c4), (c8, e6), (c4, e6), (d8, d4), (e6, d7), (e8, f7), (d7, c6), (g7, g6), (c6, b7), (g6, g5), (b7, a8), (f6, e4), (a8, e4), (e7, e6), (d1, d4), (f8, c5), (d4, c5), (h8, e8), (c5, a7), (f7, g8), (a7, e7), (e8, d8), (e7, e6), (g8, h7), (e6, e7), (h7, h8), (e7, d8), (h8, g7), (d8, e7), (g7, h8), (e7, g5), (h6, h5), (g5, h5), (h8, g7), (f5, f6), (g7, g8), (h5, h7), (g8, f8), (h7, e7), (f8, g8), (e7, e8)", 'w');
    tree->root->blabla();
    tree->baseTable->printGameBoard();

    for (ChessPiece* piece : tree->baseTable->pieces[0])
        if (piece)
            std::cout << piece->noOfMoves << " " << piece->pos.toString() << "\n";

    std::cout << "\n";

    for (ChessPiece* piece : tree->baseTable->pieces[1])
        if (piece)
            std::cout << piece->noOfMoves << " " <<  piece->pos.toString() << "\n";*/


    //std::cout << table->getBestMove(3);
    
    /*Tree* tree = new Tree(table);

    
    tree->root->blabla();
    tree->baseTable->printGameBoard();

    /*tree->createTree(tree->root, 0, 3);

    TreeNode* test = tree->root->children[0]->children[0]->children[0];*/

    //test->move();
    //test->blabla();

    //test->table->printGameBoard();
    //tree->baseTable->printGameBoard();
    
    //std::cout << table->getBestMove(3);
    
    //std::cout << table->getBestMove(3);
    
    //Tree* tree = new Tree(table);
    /*tree->root->blabla();
    //std::cout << tree->root->deletedPieces.back()->pos.toString() << "\n";
    tree->baseTable->printGameBoard();*/
    //std::cout << tree->root->moves[tree->root->moves.size() - 25].first.toString() << " " << tree->root->moves[tree->root->moves.size() - 25].second.toString();
    

    /*table->moveInAdvance("(e2, e4), (a7, a5), (d2, d4), (e7, e6), (c2, c4), (f8, b4), (c1, d2), (b4, d2), (d1, d2), (d8, h4), (g2, g3), (h4, e4), (d2, e2), (e4, h1), (g1, f3), (a5, a4), (b2, b3), (a4, b3), (a2, b3), (a8, a1), (e2, e5), (a1, b1), (e1, e2), (h1, f1), (e2, d2), (f1, f2), (d2, d3), (b1, b3), (d3, e4), (b3, e3), (e4, f4), (f2, f3), (f4, g5), (f7, f6), (g5, h4), (f6, e5), (h4, g5), (e5, d4), (g5, h4)", 'w');

    std::cout << table->getBestMove(3);*/

    return 0;
}
