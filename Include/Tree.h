#ifndef INC_3_CHECK_CHESS_TREE_H
#define INC_3_CHECK_CHESS_TREE_H

#include "common.h"

class Table;

class TreeNode {
public:
    Table* table;
    vec2<int> pos;

    int bestScore = INF;
    std::pair<vec2<int>, vec2<int>> bestMove;

    TreeNode* parent = nullptr;
    std::vector<TreeNode*> children;

    TreeNode(Table* table);
};

class Tree {
public:
    TreeNode* root;

    Tree(Table* table);

    void createTree(TreeNode* root, int level, int depth);

    void deleteTree(TreeNode* root);

    void printTree(TreeNode* root, int level);

    void countNodes(TreeNode* root, int *no);

    void MiniMax(TreeNode* root, int turn, int level);

    std::pair<vec2<int>, vec2<int>> getBestMove();
};

#endif //INC_3_CHECK_CHESS_TREE_H