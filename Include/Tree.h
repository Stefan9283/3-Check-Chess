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

struct Pair {
    int score;
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

    int evaluateState(int priority);

    std::vector<std::pair<vec2<int>, vec2<int>>> sortMoves(std::vector<std::pair<vec2<int>, vec2<int>>> allMoves, int priority, bool ascendingOrder);

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

    int MiniMax(TreeNode* root, int depth, int alpha, int beta, int priority, bool maximizingPlayer);

    void deleteNodes(TreeNode* root);

    void printTree(TreeNode* root, int level);

    void countNodes(TreeNode* root, int *no);
};

#endif //INC_3_CHECK_CHESS_TREE_H