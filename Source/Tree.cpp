#include "Tree.h"
#include "Table.h"

TreeNode::TreeNode(Table* table) {
    this->table = table->createNewState();
}

Tree::Tree(Table* table) {
    this->root = new TreeNode(table);
}

void Tree::createTree(TreeNode* root, int level, int depth) {
    if (level == depth - 1)
        return;

    root->table->markAllPossibleMoves(root->table->turn + level % 2);

    for (int i = 0; i < root->table->height; i++)
        for (int j = 0; j < root->table->width; j++)
            for (ChessPiece* piece : root->table->squares[i][j]->possibleNormalMoves) {
                vec2<int> oldPos = piece->pos;

                Table* newTable = root->table->createNewState(piece, vec2<int>(i, j));
                TreeNode* newNode = new TreeNode(newTable);

                newNode->pos = oldPos;
                newNode->bestMove.second = vec2<int>(i, j);
                newNode->parent = root;
                root->children.push_back(newNode);
            }

    root->table->unmarkAllPossibleMoves();

    for (TreeNode* child : root->children)
        createTree(child, level + 1, depth);
}

void Tree::deleteTree(TreeNode* root) {
    if (!root)
        return;

    for (TreeNode* child : root->children)
        deleteTree(child);

    delete root->table;
    delete root;
}

void Tree::printTree(TreeNode* root, int level) {
    if (!root)
        return;

    root->table->printGameBoard('w', false, true, level);
    std::cout << "\n";

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

void Tree::MiniMax(TreeNode* root, int turn, int level) {
    if (!root)
        return;

    for (TreeNode* child : root->children)
        MiniMax(child, turn, level + 1);

    if (root->parent) {
        int currScore = (root->table->getTotalScore(0) - root->table->getTotalScore(1)) * (turn == 0 ? 1 : -1);

        if (level % 2 != 0) {
            if (root->parent->bestScore == INF || currScore > root->parent->bestScore) {
                root->parent->bestScore = currScore;
                root->parent->bestMove.first = root->pos;
                root->parent->bestMove.second = root->bestMove.second;
            }
        } else {
            if (root->parent->bestScore == INF || currScore < root->parent->bestScore) {
                root->parent->bestScore = currScore;
                root->parent->bestMove.first = root->pos;
                root->parent->bestMove.second = root->bestMove.second;
            }
        }
    }
}

std::pair<vec2<int>, vec2<int>> Tree::getBestMove() {
    return root->bestMove;
}
