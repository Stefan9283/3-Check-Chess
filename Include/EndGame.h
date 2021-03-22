#include "common.h"

class Table;

class TreeNode;

class EndGame {
public:
	int advantageousPart;

	virtual std::string getBestMove(Table* table, int depth) = 0;
};

class PiecesVsKing : EndGame {
public:
	float MiniMax(TreeNode* root, int depth, float alpha, float beta, int priority, bool maximizingPlayer);

	std::string getBestMove(Table* table, int depth);
};