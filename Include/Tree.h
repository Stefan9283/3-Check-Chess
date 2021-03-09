#ifndef INC_3_CHECK_CHESS_TREE_H
#define INC_3_CHECK_CHESS_TREE_H

#include "common.h"

class Table;

class TreeNode {
public:
    Table* table;
    vec2 pos;

    int bestScore = INF;
    std::pair<vec2, vec2> bestMove;

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

    std::pair<vec2, vec2> getBestMove();
};

#endif //INC_3_CHECK_CHESS_TREE_H