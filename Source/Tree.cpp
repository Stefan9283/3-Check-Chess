#include "Tree.h"
#include "Table.h"

TreeNode::TreeNode(Table* table) {
    this->table = table->createNewState(nullptr, vec2());
}

Tree::Tree(Table* table) {
    this->root = new TreeNode(table);
}

void Tree::createTree(TreeNode* root, int level, int depth) {
    if (level == 2 * depth - 1)
        return;

    for (int j = 0; j < root->table->width; j++)
        root->table->markPossibleMovesForPawn((Pawn*)root->table->pieces[0][j]);

    root->table->markPossibleMovesForRook((Rook*)root->table->pieces[0][8]);
    root->table->markPossibleMovesForRook((Rook*)root->table->pieces[0][9]);
    root->table->markPossibleMovesForKnight((Knight*)root->table->pieces[0][10]);
    root->table->markPossibleMovesForKnight((Knight*)root->table->pieces[0][11]);
    root->table->markPossibleMovesForBishop((Bishop*)root->table->pieces[0][12]);
    root->table->markPossibleMovesForBishop((Bishop*)root->table->pieces[0][13]);
    root->table->markPossibleMovesForQueen((Queen*)root->table->pieces[0][15]);
    root->table->markPossibleMovesForKing((King*)root->table->pieces[0][14]);

    for (int i = 0; i < root->table->height; i++)
        for (int j = 0; j < root->table->width; j++)
            for (ChessPiece* piece : root->table->squares[i][j]->possibleNormalMoves) {
                Table* newState = root->table->createNewState(piece, vec2(i, j));
                TreeNode* newNode = new TreeNode(newState);

                root->children.push_back(newNode);
            }
}

void Tree::printTree(TreeNode* root, int level) {
    if (!root)
        return;

    root->table->printGameBoard();

    for (TreeNode* child : root->children)
        printTree(child, level + 1);
}