#include <Algorithm.h>
#include <AlgoPicker.h>
#include "Table.h"

#include "tools.h"




Square::Square(char color, ChessPiece* piece) {
    this->color = color; this->piece = piece;
}

Table::Table() {
    for (int i = 0; i < height; i++) {
        std::vector<Square*> line;

        for (int j = 0; j < width; j++) {
            char color = i % 2 == 0 ? (j % 2 == 0 ? 'b' : 'w') : (j % 2 == 0 ? 'w' : 'b');

            line.push_back(new Square(color, nullptr));
        }

        squares.push_back(line);
    }

    std::vector<ChessPiece*> white, black;

    for (int j = 0; j < width; j++) {
        squares[1][j]->piece = new Pawn('w', vec2<int>{ 1, j }, j);
        white.push_back(squares[1][j]->piece);
        squares[6][j]->piece = new Pawn('b', vec2<int>{ 6, j }, j);
        black.push_back(squares[6][j]->piece);
    }

    squares[0][0]->piece = new Rook('w', vec2<int>{0, 0}, 8);
    squares[0][7]->piece = new Rook('w', vec2<int>{0, 7}, 9);
    squares[7][0]->piece = new Rook('b', vec2<int>{7, 0}, 8);
    squares[7][7]->piece = new Rook('b', vec2<int>{7, 7}, 9);

    squares[0][1]->piece = new Knight('w', vec2<int>{0, 1}, 10);
    squares[0][6]->piece = new Knight('w', vec2<int>{0, 6}, 11);
    squares[7][1]->piece = new Knight('b', vec2<int>{7, 1}, 10);
    squares[7][6]->piece = new Knight('b', vec2<int>{7, 6}, 11);

    squares[0][2]->piece = new Bishop('w', vec2<int>{0, 2}, 12);
    squares[0][5]->piece = new Bishop('w', vec2<int>{0, 5}, 13);
    squares[7][2]->piece = new Bishop('b', vec2<int>{7, 2}, 12);
    squares[7][5]->piece = new Bishop('b', vec2<int>{7, 5}, 13);

    squares[0][4]->piece = new King ('w', vec2<int>{0, 4}, 14);
    squares[0][3]->piece = new Queen('w', vec2<int>{0, 3}, 15);

    squares[7][4]->piece = new King ('b', vec2<int>{7, 4}, 14);
    squares[7][3]->piece = new Queen('b', vec2<int>{7, 3}, 15);

    white.push_back(squares[0][0]->piece);
    white.push_back(squares[0][7]->piece);
    white.push_back(squares[0][1]->piece);
    white.push_back(squares[0][6]->piece);
    white.push_back(squares[0][2]->piece);
    white.push_back(squares[0][5]->piece);
    white.push_back(squares[0][4]->piece);
    white.push_back(squares[0][3]->piece);

    black.push_back(squares[7][0]->piece);
    black.push_back(squares[7][7]->piece);
    black.push_back(squares[7][1]->piece);
    black.push_back(squares[7][6]->piece);
    black.push_back(squares[7][2]->piece);
    black.push_back(squares[7][5]->piece);
    black.push_back(squares[7][4]->piece);
    black.push_back(squares[7][3]->piece);

    pieces.push_back(white);
    pieces.push_back(black);
}

Table::~Table() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (squares[i][j]->piece)
                delete squares[i][j]->piece;

            delete squares[i][j];
        }
    }
}

//Functii Stefan
#define COPY_HISTORY_TOO true

#pragma region pieces manuvering
void Table::movePiece(ChessPiece* piece, vec2<int> pos) {
    assert(piece != nullptr && "Piece meant to be moved is null");
    assert(isInside(pos) && "Can't move piece outside the squares");

    turn = 1 - turn;

    if (squares[pos.x][pos.y]->piece)
        removePiece(squares[pos.x][pos.y]->piece);

    if (dynamic_cast<Pawn*>(piece)) {
        if (pos.x == height - 1) {
            Queen* queen = ((Pawn*)piece)->promotePawn(this);

            delete piece;
            piece = queen;
            pieces[piece->color == 'w' ? 0 : 1].push_back(piece);
        } else
            ((Pawn*)piece)->wasMoved = true;
    } else if (dynamic_cast<Rook*>(piece))
        ((Rook*)piece)->wasMoved = true;
    else if (dynamic_cast<King*>(piece))
        ((King*)piece)->wasMoved = true;

    vec2<int> prev = piece->pos;
    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    squares[pos.x][pos.y]->piece = piece;
    piece->pos = pos;
    addMove2History(piece, std::make_pair(prev, pos));
}
void Table::movePiece(ChessPiece *piece, const char* pos) {
    assert(strlen(pos) >= 2 && "A valid move position needs a line and a column");

    if (pos[0] >= 'a' && isInside(vec2<int>{pos[1] - '1', pos[0] - 'a'}))
        movePiece(piece, vec2<int>{pos[1] - '1', pos[0] - 'a'});
    else
        if (isInside(vec2<int>{pos[0] - '1', pos[1] - 'a'}))
            movePiece(piece, vec2<int>{pos[0] - '1', pos[1] - 'a'});
        else assert(!"Illegal move position");
}
void Table::movePiece(const char* move) {
    movePiece(getPiece(move), move + 2);
}
void Table::removePiece(ChessPiece* piece) {
    assert(piece != nullptr && "Piece meant to be deleted is null");
    pieces[piece->color == 'w' ? 0 : 1][piece->index] = nullptr;
    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    delete piece;
}
ChessPiece* Table::getPiece(const char *pos) {
    assert(strlen(pos) >= 2 && "A valid move position needs a line and a column");

    ChessPiece* piece = nullptr;
    if(pos[0] >= 'a' && isInside(vec2<int>{pos[1] - '1', pos[0] - 'a'}))
        piece = squares[pos[1] - '1'][pos[0] - 'a']->piece;
    else if (isInside(vec2<int>{pos[0] - '1', pos[1] - 'a'}))
        piece = squares[pos[0] - '1'][pos[1] - 'a']->piece;
    else assert(!"Illegal position");

    assert(piece && "Returned piece is null");

    return piece;
}
#pragma endregion
#pragma region checking funcs
bool Table::isInside(vec2<int> pos) const {
    return pos.x >= 0 && pos.x < height && pos.y >= 0 && pos.y < width;
}
bool Table::canIPlaceItHere(ChessPiece* piece, Square* sq) {
    if(!sq->piece) return true;
    return sq->piece && piece->color != sq->piece->color;
}
#pragma endregion
#pragma region score
int Table::getSquareScore(Square* sq, char myColor) {
    if (!sq || !sq->piece)
        return 0;
    return sq->piece->score;
}
int Table::getTotalScore(char color) {
    assert(color == 'w' || color == 'b' && "Unknown piece color");

    int total = 0;

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            if (squares[i][j]->piece && squares[i][j]->piece->color == color)
                total += squares[i][j]->piece->score;

    return total;
}
#pragma endregion
vec2<int> Table::string2coords(const char *coords) {
    assert(strlen(coords) >= 2 && "Coords should have at least a line and a column");
    return {coords[0] - 'a' - 1, coords[1] - '0'};
}
std::string Table::coords2string(vec2<int> pos) const {
    assert(isInside(pos) && "Position outside of the table");
    std::string s = "a";
    s[0] += pos.y;
    return s.append(std::to_string(pos.x + 1));
}

std::string Table::pickAMove() {
    AlgoPicker* picker = new TestPicker();
    Algorithm* algo = picker->pickAlgorithm(this);
    std::string move = "move ";
    move = move + algo->pickMove(this);
    vec2<int> start = string2coords(move.c_str() + 5), end = string2coords(move.c_str() + 7);
    delete algo;
    delete picker;
    return move;
}

Table* Table::createNewState(ChessPiece* piece, vec2<int> pos) {
    auto* t = new Table(*this);
    for (int i = 0; i < t->height; ++i)
        for (int j = 0; j < t->width; ++j) {
            t->squares[i][j] = new Square(*squares[i][j]);
            t->squares[i][j]->possibleNormalMoves.clear();
            ChessPiece* c = t->squares[i][j]->piece;
            if (!c) continue;
    
            if (dynamic_cast<Pawn*>(c))
                t->squares[i][j]->piece = new Pawn(*dynamic_cast<Pawn*>(c));
            else if (dynamic_cast<Rook*>(c))
                t->squares[i][j]->piece = new Rook(*dynamic_cast<Rook*>(c));
            else if (dynamic_cast<Bishop*>(c))
                t->squares[i][j]->piece = new Bishop(*dynamic_cast<Bishop*>(c));
            else if (dynamic_cast<Queen*>(c))
                t->squares[i][j]->piece = new Queen(*dynamic_cast<Queen*>(c));
            else if (dynamic_cast<Knight*>(c))
                t->squares[i][j]->piece = new Knight(*dynamic_cast<Knight*>(c));
            else if (dynamic_cast<King*>(c))
                t->squares[i][j]->piece = new King(*dynamic_cast<King*>(c));
    
            t->pieces[c->color == 'w' ? 0 : 1][c->index] = t->squares[i][j]->piece;
        }


    if (COPY_HISTORY_TOO)
        for (int i = 0; i < t->history.size(); ++i) {
            vec2<int> oldPiecePos = history[i].piece->pos;
            t->history[i].piece = t->squares[oldPiecePos.x][oldPiecePos.y]->piece;
        }

    
    if (piece)
        t->movePiece(t->squares[piece->pos.x][piece->pos.y]->piece, pos);

    return t;
}
void Table::printGameBoard(char perspective, bool fromZero, bool xLetters, int tabsCount)  {
    assert(perspective == 'r' || perspective == 'b' || perspective == 'w' && "Perpective (w)hite/(b)lack/(r)otated");
    printTabs(tabsCount); std::cout << "##################################\n";
    if (perspective == 'w') {

        for (int i = height - 1; i >= 0; --i) {
            printTabs(tabsCount);
            if (fromZero) std::cout << i << "| ";
                    else std::cout << i + 1 << "| ";

                for (int j = 0; j < width; ++j)
                    if (squares[i][j]->piece) {
                        std::cout << " " << squares[i][j]->piece->abbreviation;
                        std::cout << squares[i][j]->piece->color << " ";
                    } else
                        std::cout << " -- ";

            std::cout << "\n";
        }

        printTabs(tabsCount); std::cout << "   -------------------------------\n";
        printTabs(tabsCount); std::cout << "   ";

        for (int j = 0; j < width; ++j)
            if (fromZero)
                std::cout << " " << j << "  ";
            else if (xLetters) std::cout << " " << (char)('a' + j) << "  ";
            else std::cout << " " << j + 1 << "  ";
        std::cout << "\n";
    } else if (perspective == 'b') {
        printTabs(tabsCount);
        for (int j = width - 1; j >= 0; --j)
            if (fromZero)
                std::cout << " " << j << "  ";
            else if (xLetters) std::cout << " " << (char)('a' + j) << "  ";
            else std::cout << " " << j + 1 << "  ";
        std::cout << "\n";
        printTabs(tabsCount); std::cout << " -----------------------------------\n";
        for (int i = 0; i <= height - 1; ++i) {
            printTabs(tabsCount);
            for (int j = width - 1; j >= 0; --j) {
                if (squares[i][j]->piece) {
                    std::cout << " " << squares[i][j]->piece->abbreviation;
                    std::cout << squares[i][j]->piece->color << " ";
                }
                else
                    std::cout << " -- ";
            }
            if (fromZero) std::cout << " |" << i ;
            else std::cout << " |" << i + 1 ;
            std::cout << "\n";
        }
    } else {
        printTabs(tabsCount);
        std::cout << "    ";
        for (int k = 0; k < width; ++k)
            if (fromZero)
                std::cout << " " << k << "  ";
                else std::cout << " " << k + 1 << "  ";

        std::cout << "\n";
        printTabs(tabsCount);
        std::cout << "   ";
        for (int k = 0; k < width; ++k)
            std::cout << "----";
        std::cout << "\n";

        for (int i = 0; i < width ; ++i) {
            printTabs(tabsCount);
            if (fromZero)
                std::cout << " " << width - i - 1 << " |";
            else if (xLetters) std::cout << " " << (char)('a' + i) << " |";
            else std::cout << " " << width - i << " |";

            for (int j = height - 1; j >= 0; --j) {
                if (squares[j][i]->piece) {
                    std::cout << " " << squares[j][i]->piece->abbreviation;
                    std::cout << squares[j][i]->piece->color << " ";
                }
                else
                    std::cout << " -- ";
            }
            std::cout << "\n";
        }
    }
    printTabs(tabsCount); std::cout << "##################################\n";
}

// Functii Ovidiu
void Table::parseMove(const char* s) {
    const char from[] = {s[strlen(s) - 4], s[strlen(s) - 3], '\0'};
    const char to[] = {s[strlen(s) - 2], s[strlen(s) - 1], '\0'};

    movePiece(getPiece(from), to);
}

std::string Table::getBestMove(int depth) {
    bool canMove = hasLegalMoves();

    if (((King*)pieces[turn][14])->isInCheck(this, pieces[turn][14]->pos))
        if (!canMove)
            return std::string("resign");

    Tree* tree = new Tree(this);

    tree->createTree(tree->root, 0, depth);
    tree->MiniMax(tree->root, turn, 0);

    std::pair<vec2<int>, vec2<int>> bestMove = tree->getBestMove();

    std::string from = coords2string(bestMove.first);
    std::string to = coords2string(bestMove.second);

    tree->deleteTree(tree->root);

    return std::string("move ").append(from).append(to);
}

std::string Table::getARandomMove() {
    srand(time(NULL));

    bool canMove = hasLegalMoves();

    if (((King*)pieces[turn][14])->isInCheck(this, pieces[turn][14]->pos))
        if (!canMove)
            return std::string("resign");

    markAllPossibleMoves();

    int squareNo = rand() % (height * width);
 
    while (!squares[squareNo / height][squareNo % width]->possibleNormalMoves.size())
        squareNo = rand() % (height * width);

    int moveNo = rand() % squares[squareNo / height][squareNo % width]->possibleNormalMoves.size();

    std::string from = coords2string(squares[squareNo / height][squareNo % width]->possibleNormalMoves[moveNo]->pos);
    std::string to = coords2string(vec2<int>(squareNo / height, squareNo % width));

    unmarkAllPossibleMoves();

    return std::string("move ").append(from).append(to);
}

int Table::getTotalScore() {
    int total = 0;

    for (ChessPiece* chessPiece : pieces[turn])
        if (chessPiece)
            total += chessPiece->score;

    return total;
}

void Table::moveInAdvance(const char* moves, char color) {
    for (int i = 0; i < strlen(moves); i += 10) {
        char from[3], to[3];

        from[0] = moves[i + 1]; from[1] = moves[i + 2]; from[2] = '\0';
        to[0] = moves[i + 5]; to[1] = moves[i + 6]; to[2] = '\0';

        movePiece(getPiece(from), to);
        color = color == 'w' ? 'b' : 'w';
    }
}

bool Table::hasNoPiecesBetween_line(vec2<int> pos1, vec2<int> pos2) {
    if (pos1.x == pos2.x) {
        int stY = std::min(pos1.y, pos2.y) + 1;
        int spY = std::max(pos1.y, pos2.y) - 1;

        while (stY <= spY) {
            if (squares[stY][pos1.x]->piece)
                return false;

            stY++;
        }

        return true;
    }

    int stX = std::min(pos1.x, pos2.x) + 1;
    int spX = std::max(pos1.x, pos2.x) - 1;

    while (stX <= spX) {
        if (squares[stX][pos1.x]->piece)
            return false;

        stX++;
    }

    return true;
}

bool Table::hasNoPiecesBetween_diagonal(vec2<int> pos1, vec2<int> pos2) {
    // Main diagonal
    if ((pos2.x > pos1.x && pos2.y > pos1.y) ||
        (pos2.x < pos1.x && pos2.y < pos1.x)) {
        vec2<int> st = pos1.y < pos2.y ? pos1 : pos2;
        vec2<int> sp = pos1.y > pos2.y ? pos1 : pos2;

        st.x++; st.y++; sp.x--; sp.y--;

        while (st.x <= sp.x) {
            if (squares[st.x][st.y]->piece)
                return false;

            st.x++; st.y++;
        }

        return true;
    }

    // Secondary diagonal
    vec2<int> st = pos1.y < pos2.y ? pos1 : pos2;
    vec2<int> sp = pos1.y > pos2.y ? pos1 : pos2;

    st.x++; st.y++; sp.x--; sp.y--;

    while (st.x <= sp.x) {
        if (squares[st.x][st.y]->piece)
            return false;

        st.x--; st.y++;
    }

    return true;
}

bool Table::isAnIllegalMove(ChessPiece* piece, vec2<int> pos) {
    if (!piece)
        return true;

    if (!isInside(pos))
        return true;

    if (squares[pos.x][pos.y]->piece && 
        piece->color == squares[pos.x][pos.y]->piece->color)
            return true;

    if (dynamic_cast<King*>(piece)) {
        if (((King*)pieces[turn][14])->isInCheck(this, pos) || isKingInConflict((King*)piece, pos))
            return true;
    } else if (((King*)pieces[turn][14])->isInCheck(this, piece, pos))
        return true;

    return false;
}

bool Table::isKingInConflict(King* king, vec2<int> pos) {
    int line = king->color == 'w' ? 1 : 0;

    return pos.getDistanceTo(pieces[line][14]->pos) < 2;
}

bool Table::hasLegalMoves() {
    markAllPossibleMoves();

    bool found = false;

    for (int i = 0; i < height && !found; i++)
        for (int j = 0; j < width && !found; j++)
            if (squares[i][j]->possibleNormalMoves.size())
                found = true;

    unmarkAllPossibleMoves();

    return found;
}

void Table::markAllPossibleMoves() {
    for (ChessPiece* piece : pieces[turn]) {
        if (!piece)
            continue;

        if (dynamic_cast<Pawn*>(piece))
            markPossibleMovesForPawn((Pawn*)piece);
        else if (dynamic_cast<Knight*>(piece))
            markPossibleMovesForKnight((Knight*)piece);
        else if (dynamic_cast<Bishop*>(piece))
            markPossibleMovesForBishop((Bishop*)piece);
        else if (dynamic_cast<Rook*>(piece))
            markPossibleMovesForRook((Rook*)piece);
        else if (dynamic_cast<Queen*>(piece))
            markPossibleMovesForQueen((Queen*)piece);
        else
            markPossibleMovesForKing((King*)piece);
    }
}

void Table::unmarkAllPossibleMoves() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            squares[i][j]->possibleNormalMoves.clear();

    bool shortCastle_white = false;
    bool shortCastle_black = false;

    bool longCastle_white = false;
    bool longCastle_black = false;
}

void Table::markPossibleMovesForPawn(Pawn* pawn) {
    vec2<int> currPos;

    // One square
    currPos.x = pawn->color == 'w' ? pawn->pos.x + 1 : pawn->pos.x - 1; currPos.y = pawn->pos.y;

    if (!isAnIllegalMove(pawn, currPos) && !squares[currPos.x][currPos.y]->piece)
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn);

    // On diagonal
    currPos.y = pawn->pos.y - 1;

    if (!isAnIllegalMove(pawn, currPos) && squares[currPos.x][currPos.y]->piece)
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn);

    currPos.y = pawn->pos.y + 1;

    if (!isAnIllegalMove(pawn, currPos) && squares[currPos.x][currPos.y]->piece)
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn);

    // Two squares
    if (!pawn->wasMoved) {
        currPos.x = pawn->pos.x + pawn->color == 'w' ? 2 :-2; currPos.y = pawn->pos.y;

        if (!isAnIllegalMove(pawn, currPos) &&
            !squares[currPos.x][currPos.y]->piece &&
            !squares[pawn->pos.x + (pawn->color == 'w' ? 1 : -1)][pawn->pos.y]->piece)
                squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn);
    }
}

void Table::markPossibleMovesForKnight(Knight* knight) {
    // Up - right
    if (!isAnIllegalMove(knight, {knight->pos.x + 2, knight->pos.y + 1}))
        squares[knight->pos.x + 2][knight->pos.y + 1]->possibleNormalMoves.push_back(knight);

    // Right - up
    if (!isAnIllegalMove(knight, {knight->pos.x + 1, knight->pos.y + 2}))
        squares[knight->pos.x + 1][knight->pos.y + 2]->possibleNormalMoves.push_back(knight);

    // Down - right
    if (!isAnIllegalMove(knight, {knight->pos.x - 2, knight->pos.y + 1}))
        squares[knight->pos.x - 2][knight->pos.y + 1]->possibleNormalMoves.push_back(knight);

    // Right - down
    if (!isAnIllegalMove(knight, {knight->pos.x - 1, knight->pos.y + 2}))
        squares[knight->pos.x - 1][knight->pos.y + 2]->possibleNormalMoves.push_back(knight);

    // Up - left
    if (!isAnIllegalMove(knight, {knight->pos.x + 2, knight->pos.y - 1}))
        squares[knight->pos.x + 2][knight->pos.y - 1]->possibleNormalMoves.push_back(knight);

    // Left - up
    if (!isAnIllegalMove(knight, {knight->pos.x + 1, knight->pos.y - 2}))
        squares[knight->pos.x + 1][knight->pos.y - 2]->possibleNormalMoves.push_back(knight);

    // Down - left
    if (!isAnIllegalMove(knight, {knight->pos.x - 2, knight->pos.y - 1}))
        squares[knight->pos.x - 2][knight->pos.y - 1]->possibleNormalMoves.push_back(knight);

    // Left - down
    if (!isAnIllegalMove(knight, {knight->pos.x - 1, knight->pos.y - 2}))
        squares[knight->pos.x - 1][knight->pos.y - 2]->possibleNormalMoves.push_back(knight);
}

void Table::markPossibleMovesForBishop(Bishop* bishop) {
    vec2<int> currPos;

    // Up - right
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y + 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y++;
    }

    // Up - left
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y - 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y--;
    }

    // Down - right
    currPos.x = bishop->pos.x - 1; currPos.y = bishop->pos.y + 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y++;
    }

    // Down - left
    currPos.x = bishop->pos.x - 1; currPos.y = bishop->pos.y - 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y--;
    }
}

void Table::markPossibleMovesForRook(Rook* rook) {
    vec2<int> currPos;

    // Up
    currPos.x = rook->pos.x + 1; currPos.y = rook->pos.y;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++;
    }

    // Down
    currPos.x = rook->pos.x - 1; currPos.y = rook->pos.y;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--;
    }

    // Left
    currPos.x = rook->pos.x; currPos.y = rook->pos.y - 1;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y--;
    }

    // Right
    currPos.x = rook->pos.x; currPos.y = rook->pos.y + 1;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y++;
    }
}

void Table::markPossibleMovesForQueen(Queen* queen) {
    vec2<int> currPos;

    // Up
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++;
    }

    // Down
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--;
    }

    // Left
    currPos.x = queen->pos.x; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y--;
    }

    // Right
    currPos.x = queen->pos.x; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y++;
    }

    // Up - right
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y++;
    }

    // Up - left
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y--;
    }

    // Down - right
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y++;
    }

    // Down - left
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y--;
    }
}

void Table::markPossibleMovesForKing(King *king) {
    vec2<int> currPos;

    // Up
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king);

    // Down
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king);

    // Left
    currPos.x = king->pos.x; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king);

    // Right
    currPos.x = king->pos.x; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king);

    // Up - right
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king);

    // Up - left
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king);

    // Down - right
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king);

    // Down - left
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king);

    // Verify if white / black has already castled
    if (king->castle)
        return;

    int line = king->color == 'w' ? 0 : 1;

    // Short castle
    if (pieces[line][9])
        if (!king->wasMoved &&
            !((Rook*)pieces[line][9])->wasMoved &&
            !king->isInCheck(this, king->pos) &&
            !king->isInCheck(this, vec2<int>{king->pos.x, king->pos.y + 1}) &&
            !king->isInCheck(this, vec2<int>{king->pos.x, king->pos.y + 2}) &&
            hasNoPiecesBetween_line(king->pos, pieces[line][9]->pos))
                king->color == 'w' ? shortCastle_white = true : shortCastle_black = true;

    // Long castle
    if (pieces[line][8])
        if (!king->wasMoved &&
            !((Rook*)pieces[line][8])->wasMoved &&
            !king->isInCheck(this, king->pos) &&
            !king->isInCheck(this, vec2<int>{king->pos.x, king->pos.y - 1}) &&
            !king->isInCheck(this, vec2<int>{king->pos.x, king->pos.y - 2}) &&
            !king->isInCheck(this, vec2<int>{king->pos.x, king->pos.y - 3}) &&
            hasNoPiecesBetween_line(king->pos, pieces[line][8]->pos))
                king->color == 'w' ? longCastle_white = true : longCastle_black = true;
}

bool Table::isSquareOfTheSameColor(vec2<int> pos1, vec2<int> pos2) {
    return squares[pos1.x][pos1.y]->color == squares[pos2.x][pos2.y]->color;
}

bool Table::isSquareOfTheSameColor(ChessPiece* piece1, ChessPiece* piece2) {
    return isSquareOfTheSameColor(piece1->pos, piece2->pos);
}
