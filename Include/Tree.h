#ifndef INC_3_CHECK_CHESS_TREE_H
#define INC_3_CHECK_CHESS_TREE_H

#include "common.h"

class Table;

class TreeNode {
public:
    Table* table;
    std::vector<TreeNode*> children;

    TreeNode(Table* table);
};

class Tree {
public:
    TreeNode* root;

    Tree(Table* table);

    void createTree(TreeNode* root, int level, int depth);

    void printTree(TreeNode* root, int level);
};

#endif //INC_3_CHECK_CHESS_TREE_H