#include "Tree.h"
#include "Table.h"
#include "ChessPiece.h"

TreeNode::TreeNode(Table* table) {
    this->table = table;
}

TreeNode* TreeNode::createNode(std::pair<vec2<int>, vec2<int>> move) {
    TreeNode* newNode = new TreeNode(table);
    MoveHistory moveHistory;

    newNode->moves = moves;
    moveHistory.pos = move;

    moveHistory.index = moves.size() + 1;
    newNode->moves.push_back(moveHistory);

    children.push_back(newNode);
    newNode->parent = this;

    return newNode;
}

void TreeNode::eliminatePieceFromState(ChessPiece* piece, int index) {
    table->pieces[piece->color == 'w' ? 0 : 1][piece->index] = nullptr;
    table->squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    deletedPieces.push_back({piece, index});
}

void TreeNode::movePieceOnState(MoveHistory move) {
    ChessPiece* piece = table->squares[move.pos.first.x][move.pos.first.y]->piece;
    vec2<int> pos = move.pos.second;

    assert(piece && table->isInside(pos) && "Illegal piece or position!");

    if (dynamic_cast<Pawn*>(piece)) {
        if (!pos.x || pos.x == table->height - 1) {
            Queen* queen = ((Pawn*)piece)->promotePawn(table);

            addedPieces.push_back({queen, move.index});
            eliminatePieceFromState(piece, move.index);

            piece = queen;
            table->pieces[piece->color == 'w' ? 0 : 1].push_back(piece);

            piece->noOfMoves--;
        } else if (!table->squares[pos.x][pos.y]->piece && abs(piece->pos.y - pos.y) == 1)
            eliminatePieceFromState(table->squares[piece->pos.x][pos.y]->piece, move.index);
        else
            ((Pawn*)piece)->wasMoved = true;
    } else if (dynamic_cast<Rook*>(piece) && !((Rook*)piece)->wasMoved)
        ((Rook*)piece)->wasMoved = true;
    else if (dynamic_cast<King*>(piece) && !((King*)piece)->wasMoved) {
        ((King*)piece)->wasMoved = true;
            
        if (piece->color == 'w' && pos == vec2<int>(0, 6)) {
            table->castleShort((King*)piece);
            return;
        }
        else  if (piece->color == 'w' && pos == vec2<int>(0, 2)) {
            table->castleLong((King*)piece);
            return;
        }
        else  if (piece->color == 'b' && pos == vec2<int>(7, 6)) {
            table->castleShort((King*)piece);
            return;
        }
        else  if (piece->color == 'b' && pos == vec2<int>(7, 2)) {
            table->castleLong((King*)piece);
            return;
        }
    }

    piece->noOfMoves++;

    if (table->squares[pos.x][pos.y]->piece)
        eliminatePieceFromState(table->squares[pos.x][pos.y]->piece, move.index);

    table->squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    table->squares[pos.x][pos.y]->piece = piece;
    piece->pos = pos;

    table->addMove2History(std::make_pair(move.pos.first, pos));
    table->turn = 1 - table->turn;
}

void TreeNode::undoMoveOnState(MoveHistory move) {
    ChessPiece* piece = table->squares[move.pos.second.x][move.pos.second.y]->piece;
    vec2<int> pos = move.pos.first;
      
    assert(piece && table->isInside(pos) && "Illegal piece or position!");

    if (dynamic_cast<Pawn*>(piece)) {
        if (!(piece->noOfMoves - 1))
            ((Pawn*)piece)->wasMoved = false;

        if (deletedPieces.size())
            if (move.index == deletedPieces.back().second)
                if (deletedPieces.back().first->pos == vec2<int>(pos.x, piece->pos.y) && abs(pos.y - piece->pos.y) == 1)
                    undoEnPassant(piece, pos);
    } else if (dynamic_cast<Queen*>(piece)) {
        if (addedPieces.size())
            if (move.index == addedPieces.back().second) {
                undoPawnPromotion(piece, pos, move.index);
                return;
            }
    } else if (dynamic_cast<Rook*>(piece)) {
        if (!(piece->noOfMoves - 1))
            ((Rook*)piece)->wasMoved = false;
    } else if (dynamic_cast<King*>(piece)) {
        if (pos == vec2<int>(0, 4) && piece->pos == vec2<int>(0, 6)) {
            undoShortCastle((King*)piece);
            return;
        } else if (pos == vec2<int>(0, 4) && piece->pos == vec2<int>(0, 2)) {
            undoLongCastle((King*)piece);
            return;
        } else if (pos == vec2<int>(7, 4) && piece->pos == vec2<int>(7, 6)) {
            undoShortCastle((King*)piece);
            return;
        } else if (pos == vec2<int>(7, 4) && piece->pos == vec2<int>(7, 2)) {
            undoLongCastle((King*)piece);
            return;
        }

        if (!(piece->noOfMoves - 1))
            ((King*)piece)->wasMoved = false;
    }

    piece->noOfMoves--;
    table->squares[pos.x][pos.y]->piece = piece;
    table->squares[piece->pos.x][piece->pos.y]->piece = nullptr;

    if (deletedPieces.size())
        if (move.index == deletedPieces.back().second) {
            table->squares[piece->pos.x][piece->pos.y]->piece = deletedPieces.back().first;
            table->pieces[piece->color == 'w' ? 1 : 0][deletedPieces.back().first->index] = deletedPieces.back().first;
            deletedPieces.pop_back();
        }
        
    piece->pos = pos;

    table->history.pop_back();
    table->turn = 1 - table->turn;
}

bool TreeNode::givesCheck() {
    return ((King*)table->pieces[table->turn][14])->isInCheck(table);
}

bool TreeNode::receivesCheck() {
    return ((King*)table->pieces[!table->turn][14])->isInCheck(table);
}

float TreeNode::getBonus(bool maximizingPlayer) {
    if ((moves.back().pos.first == vec2<int>(0, 4) && moves.back().pos.second == vec2<int>(0, 2)) ||
        (moves.back().pos.first == vec2<int>(0, 4) && moves.back().pos.second == vec2<int>(0, 6)) ||
        (moves.back().pos.first == vec2<int>(7, 4) && moves.back().pos.second == vec2<int>(7, 2)) ||
        (moves.back().pos.first == vec2<int>(7, 4) && moves.back().pos.second == vec2<int>(7, 6)))
            return maximizingPlayer ? -1.5 : 1.5;

    if (dynamic_cast<King*>(table->squares[moves.back().pos.first.x][moves.back().pos.first.y]->piece))
        if (!((King*)table->squares[moves.back().pos.first.x][moves.back().pos.first.y]->piece)->wasMoved)
            return maximizingPlayer ? 2 : -2;

    if (dynamic_cast<Rook*>(table->squares[moves.back().pos.first.x][moves.back().pos.first.y]->piece))
        if (!((Rook*)table->squares[moves.back().pos.first.x][moves.back().pos.first.y]->piece)->wasMoved)
            return maximizingPlayer ? 1 : -1;

    if (givesCheck())
        return maximizingPlayer ? -0.5 : 0.5;

    if (receivesCheck())
        return maximizingPlayer ? 0.5 : -0.5;
   
    return 0;
}

float TreeNode::getScoreFromTerminalState(bool maximizingPlayer) {
    if (maximizingPlayer) {
        if (((King*)table->pieces[table->turn][14])->isInCheck(table))
            return -INF;
        
        if (((King*)table->pieces[!table->turn][14])->isInCheck(table))
            return INF;
        
        return 0;
    } 
    
    if (((King*)table->pieces[table->turn][14])->isInCheck(table))
        return INF;
    
    if (((King*)table->pieces[!table->turn][14])->isInCheck(table))
        return -INF;
    
    return 0;
}

float TreeNode::getScoreFromState(int priority, bool maximizingPlayer) {
    if (!table->getAllMoves().size())
        return getScoreFromTerminalState(maximizingPlayer);

    return (table->getTotalScore('w') - table->getTotalScore('b')) * (!priority ? 1 : -1);
}

void TreeNode::undoEnPassant(ChessPiece* piece, vec2<int> pos) {
    table->squares[pos.x][piece->pos.y]->piece = deletedPieces.back().first;
    table->pieces[piece->color == 'w' ? 1 : 0][deletedPieces.back().first->index] = deletedPieces.back().first;
    deletedPieces.pop_back();
}

void TreeNode::undoPawnPromotion(ChessPiece* piece, vec2<int> pos, int index) {
    vec2<int> oldPos = piece->pos;

    table->squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    table->pieces[piece->color == 'w' ? 0 : 1].pop_back();

    addedPieces.pop_back();
    delete piece;

    if (oldPos == deletedPieces.back().first->pos && index == deletedPieces.back().second) {
        table->squares[oldPos.x][oldPos.y]->piece = deletedPieces.back().first;
        table->pieces[table->turn][deletedPieces.back().first->index] = deletedPieces.back().first;
        deletedPieces.pop_back();
    }

    piece = deletedPieces.back().first;
    deletedPieces.pop_back();

    table->squares[piece->pos.x][piece->pos.y]->piece = piece;
    table->pieces[piece->color == 'w' ? 0 : 1][piece->index] = piece;

    table->history.pop_back();
    table->turn = 1 - table->turn;
}

void TreeNode::undoShortCastle(King* king) {
    int line = king->color == 'w' ? 0 : 1;

    table->squares[king->pos.x][king->pos.y]->piece = nullptr;
    table->squares[king->color == 'w' ? 0 : 7][4]->piece = king;
    king->pos = vec2<int>(king->color == 'w' ? 0 : 7, 4);

    table->squares[table->pieces[line][9]->pos.x][5]->piece = nullptr;
    table->squares[king->color == 'w' ? 0 : 7][7]->piece = table->pieces[line][9];
    table->pieces[line][9]->pos.y += 2;

    king->castle = false;
    king->wasMoved = false;
    king->noOfMoves--;

    ((Rook*)table->pieces[line][9])->wasMoved = false;
    table->pieces[line][9]->noOfMoves--;

    table->history.pop_back();
    table->turn = 1 - table->turn;
}

void TreeNode::undoLongCastle(King* king) {
    int line = king->color == 'w' ? 0 : 1;

    table->squares[king->pos.x][king->pos.y]->piece = nullptr;
    table->squares[king->color == 'w' ? 0 : 7][4]->piece = king;
    king->pos = vec2<int>(king->color == 'w' ? 0 : 7, 4);

    table->squares[table->pieces[line][8]->pos.x][3]->piece = nullptr;
    table->squares[king->color == 'w' ? 0 : 7][0]->piece = table->pieces[line][8];
    table->pieces[line][8]->pos.y -= 3;

    king->castle = false;
    king->wasMoved = false;
    king->noOfMoves--;

    ((Rook*)table->pieces[line][8])->wasMoved = false;
    table->pieces[line][8]->noOfMoves--;

    table->history.pop_back();
    table->turn = 1 - table->turn;
}

Tree::Tree(Table* table) {
    baseTable = table->createNewState(); root = new TreeNode(baseTable);
}

Tree::~Tree() {
    deleteNodes(root);
    delete baseTable;
}

float Tree::MiniMax(TreeNode* root, int depth, float alpha, float beta, int priority, bool maximizingPlayer) {
    if (!depth) {
        for (int i = 0; i < root->moves.size(); i++)
            root->movePieceOnState(root->moves[i]);

        root->bestScore = root->getScoreFromState(priority, maximizingPlayer) + root->getBonus(maximizingPlayer);

        for (int i = root->moves.size() - 1; i >= 0; i--)
            root->undoMoveOnState(root->moves[i]);

        return root->bestScore;
    }

    for (int i = 0; i < root->moves.size(); i++)
        root->movePieceOnState(root->moves[i]);

    std::vector<std::pair<vec2<int>, vec2<int>>> allMoves = root->table->getAllMoves();

    if (!allMoves.size()) {
        root->bestScore = root->getScoreFromTerminalState(maximizingPlayer);

        for (int i = root->moves.size() - 1; i >= 0; i--)
            root->undoMoveOnState(root->moves[i]);

        return root->bestScore;
    }

    float bonus =  root->moves.size() ? root->getBonus(maximizingPlayer) : 0;

    for (int i = root->moves.size() - 1; i >= 0; i--)
        root->undoMoveOnState(root->moves[i]);

    if (maximizingPlayer) {
        float maxScore = -INF;

        for (std::pair<vec2<int>, vec2<int>> move : allMoves) {
            TreeNode* child = root->createNode(move);
            float currScore = MiniMax(child, depth - 1, alpha, beta, priority, false);

            maxScore = std::max(maxScore, currScore);
            alpha = std::max(alpha, maxScore);

            if (beta <= alpha)
                break;
        }

        root->bestScore = maxScore + bonus;
        return maxScore + bonus;
    }

    float minScore = INF;

    for (std::pair<vec2<int>, vec2<int>> move : allMoves) {
        TreeNode* child = root->createNode(move);
        float currScore = MiniMax(child, depth - 1, alpha, beta, priority, true);

        minScore = std::min(minScore, currScore);
        beta = std::min(beta, minScore);

        if (beta <= alpha)
            break;
    }

    root->bestScore = minScore + bonus;
    return minScore + bonus;
}

float Tree::doExtraSearch(Table* table, int depth, int priority, bool maximizingPlayer) {
    Tree* extendedTree = new Tree(table);

    float bestScore = MiniMax(extendedTree->root, depth, -INF, INF, priority, maximizingPlayer);
    delete extendedTree;

    return bestScore;
}

void Tree::deleteNodes(TreeNode* root) {
    if (!root)
        return;

    for (TreeNode* child : root->children)
        deleteNodes(child);

    delete root;
}

void Tree::printTree(TreeNode* root, int level) {
    if (!root)
        return;

    for (int i = 0; i < root->moves.size(); i++)
        root->movePieceOnState(root->moves[i]);

    root->table->printGameBoard('w', false, true, level);

    for (int i = root->moves.size() - 1; i >= 0; i--)
        root->undoMoveOnState(root->moves[i]);

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

std::pair<vec2<int>, vec2<int>> Tree::getBestChoice(int depth, int priority, float score) {
    srand(time(NULL));

    Tree* compressedTree = new Tree(baseTable);
    std::pair<vec2<int>, vec2<int>> bestMove;

    getCompressedTree(compressedTree->root, this->root, score);
    setExtraSearchScores(compressedTree->root, 0, depth, priority, true);

    int no = 0;

    for (TreeNode* child : compressedTree->root->children)
        if (fabs(child->bestScore - compressedTree->root->bestScore) < EPS)
            no++;

    int config = rand() % no, actConfig = 0;

    for (TreeNode* child : compressedTree->root->children)
        if (child->bestScore == compressedTree->root->bestScore) {
            if (actConfig == config) {
                bestMove = child->moves.back().pos;
                break;
            }

            actConfig++;
        }

    delete compressedTree;
    return bestMove;
}

void Tree::getCompressedTree(TreeNode* root, TreeNode* root_, float score) {
    if (!root_)
        return;

    for (TreeNode* child : root_->children)
        if (fabs(child->bestScore - score) < EPS) {
            TreeNode* newNode = new TreeNode(root_->table);

            newNode->moves = child->moves;
            root->children.push_back(newNode);
            newNode->parent = root;
            getCompressedTree(newNode, child, score);
        }
}

void Tree::setExtraSearchScores(TreeNode* root, int level, int depth, int priority, bool maximizingPlayer) {
    if (!root)
        return;

    if (!root->children.size()) {
        for (int i = 0; i < root->moves.size(); i++)
            root->movePieceOnState(root->moves[i]);

        root->bestScore = doExtraSearch(root->table, depth, priority, maximizingPlayer);
            
        for (int i = root->moves.size() - 1; i >= 0; i--)
            root->undoMoveOnState(root->moves[i]);

        TreeNode* root_ = root;

        while (root_->parent) {
            if (root->bestScore > root_->parent->bestScore)
                root_->parent->bestScore = root->bestScore;
            else
                break;

            root_ = root_->parent;
        }
    }

    for (TreeNode* child : root->children)
        setExtraSearchScores(child, level + 1, depth, priority, !maximizingPlayer);
}
