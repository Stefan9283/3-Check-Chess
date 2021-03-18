#include <Engine.h>

int main() {
    Engine e;
    /*Table* table = new Table();
    table->moveInAdvance("(d2, d4), (d7, d6), (e2, e4), (b8, a6), (c2, c4), (g8, f6), (d4, d5)", 'w');
    table->printGameBoard();*/
    //table->markAllPossibleMoves();

    /*for (int i = 0; i < table->height; i++)
        for (int j = 0; j < table->width; j++) {
            std::cout << i << ", " << j << ": ";

            for (ChessPiece* chessPiece : table->squares[i][j]->possibleMoves)
                std::cout << chessPiece->pos.toString() << " ";

            std::cout << "\n";
        }*/
    
    
    /*table->moveInAdvance("(d2, d4)", 'w');

    Tree* tree = new Tree(table);

    //int no = 0;

    tree->MiniMax(tree->root, 0, 4, 1);
    //tree->countNodes(tree->root, &no);

    //std::cout << no;*/
    //std::cout << table->getBestMove(4);

    return 0;
}
