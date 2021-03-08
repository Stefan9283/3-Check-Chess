#include "Tree.h"
#include "Table.h"

TreeNode::TreeNode(Table* table) {
    this->table = table->createNewState();
}

Tree::Tree(Table* table) {
    this->root = new TreeNode(table);
}

void Tree::createTree(TreeNode* root, int level, int depth) {
    if (level == depth)
        return;

    root->table->markAllPossibleMoves(root->table->turn + level % 2);

    for (int i = 0; i < root->table->height; i++)
        for (int j = 0; j < root->table->width; j++)
            for (ChessPiece* piece : root->table->squares[i][j]->possibleNormalMoves) {
                Table* newTable = root->table->createNewState(piece, vec2(i, j));
                TreeNode* newNode = new TreeNode(newTable);

                root->children.push_back(newNode);
            }

    root->table->unmarkAllPossibleMoves();

    for (TreeNode* child : root->children)
        createTree(child, level + 1, depth);
}

void Tree::printTree(TreeNode* root, int level) {
    if (!root)
        return;

    root->table->printGameBoard('w', true, false, level);

    for (TreeNode* child : root->children)
        printTree(child, level + 1);
}

void Tree::countNodes(TreeNode* root, int* no) {
    if (!root)
        return;

    (*no)++;

    for (TreeNode* child : root->children)
        countNodes(child, no);
}