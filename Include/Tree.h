#ifndef INC_3_CHECK_CHESS_TREE_H
#define INC_3_CHECK_CHESS_TREE_H

#include "common.h"

class ChessPiece;

class King;

class Table;

class TreeNode {
public:
    Table* table;

    int bestScore = -INF;

    std::vector<std::pair<vec2<int>, vec2<int>>> moves;

    std::vector<ChessPiece*> addedPieces;
    std::vector<ChessPiece*> deletedPieces;

    TreeNode* parent = nullptr;
    std::vector<TreeNode*> children;

    TreeNode(Table* table);

    void eliminatePieceFromState(ChessPiece* piece);

    void moveInAdvanceOnState(const char* moves, char color);

    void blabla() {
        for (int i = moves.size() - 1; i >= 0; i--)
            undoMoveOnState(moves[i]);
    }

    void movePieceOnState(std::pair<vec2<int>, vec2<int>> move);

    void undoMoveOnState(std::pair<vec2<int>, vec2<int>> move);

    void undoShortCastle(King* king);

    void undoLongCastle(King* king);
};

class Tree {
public:
    TreeNode* root;
    Table* baseTable;

    Tree(Table* table);

    ~Tree();

    void createTree(TreeNode* root, int level, int depth);

    void deleteNodes(TreeNode* root);

    void printTree(TreeNode* root, int level);

    void countNodes(TreeNode* root, int *no);

    void MiniMax(TreeNode* root, int priority, int level);

    std::pair<vec2<int>, vec2<int>> getBestMove();
};

#endif //INC_3_CHECK_CHESS_TREE_H