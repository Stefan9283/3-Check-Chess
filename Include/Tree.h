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

    void move() {
        for (MoveHistory move : moves) {
            movePieceOnState(move);
            std::cout << move.pos.first.toString() << " " << move.pos.second.toString() << "\n";
        }
    }

    void moveInAdvanceOnState(const char* moves, char color);

    void blabla() {
        for (int i = moves.size() - 1; i >=0 ; i--)
            undoMoveOnState(moves[i]);
    }

    void movePieceOnState(MoveHistory move);

    void undoMoveOnState(MoveHistory move);

    void undoEnPassant(ChessPiece* piece, vec2<int> pos);

    void undoPawnPromotion(ChessPiece* piece, vec2<int> pos, int moveNo);

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