#ifndef INC_3_CHECK_CHESS_TREE_H
#define INC_3_CHECK_CHESS_TREE_H

#include "common.h"

class ChessPiece;

class King;

class Table;

struct MoveHistory {
    int index;
    pair<vec2<int>, vec2<int>> pos;
};

struct Pair {
    float score;
    pair<vec2<int>, vec2<int>> pos;
};

class TreeNode {
public:
    Table* table;

    float bestScore = -INF;
    vector<MoveHistory> moves;

    vector<pair<ChessPiece*, int>> addedPieces;
    vector<pair<ChessPiece*, int>> deletedPieces;

    TreeNode* parent = nullptr;
    vector<TreeNode*> children;

    TreeNode(Table* table);

    TreeNode* createNode(pair<vec2<int>, vec2<int>> move);

    void eliminatePieceFromState(ChessPiece* piece, int index);

    void movePieceOnState(MoveHistory move);

    void undoMoveOnState(MoveHistory move);

    bool givesCheck();

    bool receivesCheck();

    float getBonus(bool maximizingPlayer);

    float getScoreFromTerminalState(bool maximizingPlayer);

    float getScoreFromState(int priority, bool maximizingPlayer);

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

    float MiniMax(TreeNode* root, int depth, float alpha, float beta, int priority, bool maximizingPlayer);

    float doExtraSearch(Table* table, int depth, int priority, bool maximizingPlayer);

    void deleteNodes(TreeNode* root);

    void printTree(TreeNode* root, int level);

    void countNodes(TreeNode* root, int* no);

    pair<vec2<int>, vec2<int>> getBestChoice(int depth, int priority, float score);

    void getCompressedTree(TreeNode* root, TreeNode* root_, float score);

    void setExtraSearchScores(TreeNode* root, int level, int depth, int priority, bool maximizingPlayer);
};

#endif //INC_3_CHECK_CHESS_TREE_H