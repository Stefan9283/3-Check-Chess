#ifndef INC_3_CHECK_CHESS_TREE_H
#define INC_3_CHECK_CHESS_TREE_H

#include "common.h"

class ChessPiece;

class King;

class Table;

struct MoveHistory {
    int index;
    std::pair<vec2<int>, vec2<int>> pos;
};

class TreeNode {
public:
    Table* table;

    int bestScore = -INF;
    std::vector<MoveHistory> moves;

    std::vector<std::pair<ChessPiece*, int>> addedPieces;
    std::vector<std::pair<ChessPiece*, int>> deletedPieces;

    TreeNode* parent = nullptr;
    std::vector<TreeNode*> children;

    TreeNode(Table* table);

    void eliminatePieceFromState(ChessPiece* piece, int index);

    void movePieceOnState(MoveHistory move);

    void undoMoveOnState(MoveHistory move);

    void undoEnPassant(ChessPiece* piece, vec2<int> pos);

    void undoPawnPromotion(ChessPiece* piece, vec2<int> pos, int index);

    void undoShortCastle(King* king);

    void undoLongCastle(King* king);
};

class Tree {
public:
    TreeNode* root;
    Table* baseTable;

    Tree(Table* table);

    ~Tree();

    std::pair<vec2<int>, vec2<int>> MiniMax(TreeNode* root, int level, int depth, int priority);

    int getBestScore(TreeNode* root, int level);

    std::pair<vec2<int>, vec2<int>> getBestMove();

    void deleteNodes(TreeNode* root);

    void printTree(TreeNode* root, int level);

    void countNodes(TreeNode* root, int *no);
};

#endif //INC_3_CHECK_CHESS_TREE_H