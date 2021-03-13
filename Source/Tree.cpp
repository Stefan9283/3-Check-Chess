#include "Tree.h"
#include "Table.h"

TreeNode::TreeNode(Table* table) {
    this->table = table->createNewState(); move = std::pair<vec2<int>, vec2<int>>(vec2<int>(-INF, -INF), vec2<int>(-INF, -INF));
}

Tree::Tree(Table* table) {
    this->root = new TreeNode(table);
}

void Tree::createTree(TreeNode* root, int level, int depth) {
    if (level == depth)
        return;

    root->table->markAllPossibleMoves();

    for (int i = 0; i < root->table->height; i++)
        for (int j = 0; j < root->table->width; j++)
            for (ChessPiece* piece : root->table->squares[i][j]->possibleNormalMoves) {
                Table* newTable = root->table->createNewState(piece, vec2<int>(i, j));
                TreeNode* newNode = new TreeNode(newTable);

                newNode->move.first = piece->pos;
                newNode->move.second = vec2<int>(i, j);
                newNode->parent = root;
                newNode->table->turn = 1 - root->table->turn;
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

void Tree::MiniMax(TreeNode* root, int level) {
    if (!root)
        return;

    for (TreeNode* child : root->children)
        MiniMax(child, level + 1);

    if (root->parent) {
        int score1 = root->table->getTotalScore('w'), score2 = root->table->getTotalScore('b');

        if (level % 2 != 0) {
            if (!root->table->turn) {
                if (root->parent->bestScore == -INF || score2 > root->parent->bestScore) {
                    root->parent->bestScore = score2;
                    root->parent->bestMove.first = root->move.first;
                    root->parent->bestMove.second = root->move.second;
                }
            } else {
                if (root->parent->bestScore == -INF || score1 > root->parent->bestScore) {
                    root->parent->bestScore = score1;
                    root->parent->bestMove.first = root->move.first;
                    root->parent->bestMove.second = root->move.second;
                }
            }
        } else {
            if (!root->table->turn) {
                if (root->parent->bestScore == -INF || score1 < root->parent->bestScore) {
                    root->parent->bestScore = score1;
                    root->parent->bestMove.first = root->move.first;
                    root->parent->bestMove.second = root->move.second;
                }
            }
            else {
                if (root->parent->bestScore == -INF || score2 < root->parent->bestScore) {
                    root->parent->bestScore = score2;
                    root->parent->bestMove.first = root->move.first;

                    root->parent->bestMove.second = root->move.second;
                }
            }
        }
    }
}

std::pair<vec2<int>, vec2<int>> Tree::getBestMove() {
    return root->bestMove;
}