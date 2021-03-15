#include "Tree.h"
#include "Table.h"
#include "ChessPiece.h"

TreeNode::TreeNode(Table* table) {
    this->table = table;
}

void TreeNode::eliminatePieceFromState(ChessPiece* piece) {
    table->pieces[piece->color == 'w' ? 0 : 1][piece->index] = nullptr;
    table->squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    deletedPieces.push_back(piece);
}

void TreeNode::moveInAdvanceOnState(const char* moves, char color) {
    for (int i = 0; i < strlen(moves); i += 10) {
        char from[3], to[3];

        from[0] = moves[i + 1]; from[1] = moves[i + 2]; from[2] = '\0';
        to[0] = moves[i + 5]; to[1] = moves[i + 6]; to[2] = '\0';

        this->moves.push_back({table->string2coords(from), table->string2coords(to)});
        color = color == 'w' ? 'b' : 'w';
    }

    for (int i = 0; i < this->moves.size(); i++)
        movePieceOnState(this->moves[i]);
}

void TreeNode::movePieceOnState(std::pair<vec2<int>, vec2<int>> move) {
    ChessPiece* piece = table->squares[move.first.x][move.first.y]->piece;
    vec2<int> pos = move.second;

    assert(piece && table->isInside(pos) && "Illegal piece or position!");

    if (dynamic_cast<Pawn*>(piece)) {
        if (!pos.x || pos.x == table->height - 1) {
            Queen* queen = ((Pawn*)piece)->promotePawn(table);

            addedPieces.push_back(queen);
            eliminatePieceFromState(piece);

            piece = queen;
            table->pieces[piece->color == 'w' ? 0 : 1].push_back(piece);

            piece->noOfMoves--;
        }
        else if (!table->squares[pos.x][pos.y]->piece && abs(piece->pos.y - pos.y) == 1)
            eliminatePieceFromState(table->squares[piece->pos.x][pos.y]->piece);
        else
            ((Pawn*)piece)->wasMoved = true;
    }
    else if (dynamic_cast<Rook*>(piece) && !((Rook*)piece)->wasMoved)
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
        eliminatePieceFromState(table->squares[pos.x][pos.y]->piece);

    table->squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    table->squares[pos.x][pos.y]->piece = piece;
    piece->pos = pos;

    table->addMove2History(std::make_pair(move.first, pos));
    table->turn = 1 - table->turn;
}

void TreeNode::undoMoveOnState(std::pair<vec2<int>, vec2<int>> move) {
    ChessPiece* piece = table->squares[move.second.x][move.second.y]->piece;
    vec2<int> pos = move.first;

    assert(piece && table->isInside(pos) && "Illegal piece or position!");

    if (dynamic_cast<Pawn*>(piece)) {
        if (!(piece->noOfMoves - 1))
            ((Pawn*)piece)->wasMoved = false;

        if (deletedPieces.size())
            if (piece->pos != deletedPieces.back()->pos && abs(pos.y - piece->pos.y) == 1) {
                table->squares[pos.x][piece->pos.y]->piece = deletedPieces.back();
                table->pieces[piece->color == 'w' ? 1 : 0][deletedPieces.back()->index] = deletedPieces.back();
                deletedPieces.pop_back();
            }
    } else if (dynamic_cast<Queen*>(piece)) {
        if (addedPieces.size())
            if (piece->pos == addedPieces.back()->pos) {
                vec2<int> oldPos = piece->pos;

                table->squares[piece->pos.x][piece->pos.y]->piece = nullptr;
                table->pieces[piece->color == 'w' ? 0 : 1].pop_back();

                addedPieces.pop_back();
                delete piece;

                if (oldPos == deletedPieces.back()->pos) {
                    table->squares[oldPos.x][oldPos.y]->piece = deletedPieces.back();
                    table->pieces[!table->turn ? 1 : 0][deletedPieces.back()->index] = deletedPieces.back();
                    deletedPieces.pop_back();
                }

                piece = deletedPieces.back();
                deletedPieces.pop_back();

                table->squares[piece->pos.x][pos.y]->piece = piece;
                table->pieces[piece->color == 'w' ? 0 : 1][piece->index] = piece;

                table->history.pop_back();
                table->turn = 1 - table->turn;

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
        if ((piece->pos == deletedPieces.back()->pos)) {
            table->squares[piece->pos.x][piece->pos.y]->piece = deletedPieces.back();
            table->pieces[piece->color == 'w' ? 1 : 0][deletedPieces.back()->index] = deletedPieces.back();
            deletedPieces.pop_back();
        }
        
    piece->pos = pos;

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

void Tree::createTree(TreeNode* root, int level, int depth) {
    if (level == depth)
        return;

   /* if (root->moves.size())
        root->movePieceOnState(root->moves.back());*/

    for (std::pair<vec2<int>, vec2<int>> move : root->moves)
        root->movePieceOnState(move);

    root->table->markAllPossibleMoves();

    for (int i = 0; i < root->table->height; i++)
        for (int j = 0; j < root->table->width; j++)
            for (ChessPiece* piece : root->table->squares[i][j]->possibleNormalMoves) {
                TreeNode* newNode = new TreeNode(root->table);
                
                newNode->moves = root->moves;
                newNode->moves.push_back({piece->pos, vec2<int>(i, j)});
                
                root->children.push_back(newNode);
                newNode->parent = root;
            }

    root->table->unmarkAllPossibleMoves();

    for (int i = root->moves.size() - 1; i >= 0; i--)
        root->undoMoveOnState(root->moves[i]);

    for (TreeNode* child : root->children) {
        createTree(child, level + 1, depth);

        /*if (root->moves.size())
            root->undoMoveOnState(root->moves.back());*/
    }  
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

    for (std::pair<vec2<int>, vec2<int>> move : root->moves)
        root->movePieceOnState(move);

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

void Tree::MiniMax(TreeNode* root, int priority, int level) {
    if (!root)
        return;

    for (TreeNode* child : root->children)
        MiniMax(child, priority, level + 1);

    for (std::pair<vec2<int>, vec2<int>> move : root->moves)
        root->movePieceOnState(move);

    if (root->parent) {
        if (!root->children.size())
            root->bestScore = (root->table->getTotalScore('w') - root->table->getTotalScore('b')) * (priority == 0 ? 1 : -1);
        
        if (level % 2 != 0) {
            if (root->parent->bestScore == -INF || root->bestScore > root->parent->bestScore)
                root->parent->bestScore = root->bestScore;
        } else {
            if (root->parent->bestScore == -INF || root->bestScore < root->parent->bestScore)
                root->parent->bestScore = root->bestScore;
        }
    }

    for (int i = root->moves.size() - 1; i >= 0; i--)
        root->undoMoveOnState(root->moves[i]);
}

std::pair<vec2<int>, vec2<int>> Tree::getBestMove() {
    int maxScore = -INF;
    std::pair<vec2<int>, vec2<int>> bestMove = {vec2<int>(-INF, -INF), vec2<int>(-INF, -INF)};

    for (TreeNode* child : root->children)
        if (child->bestScore > maxScore) {
            maxScore = child->bestScore;
            bestMove = std::pair<vec2<int>, vec2<int>>(child->moves.back());
        }

    return bestMove;
}