#include "Table.h"

Table::Table() {
    for (int i = 0; i < height; i++) {
        std::vector<Square*> line;

        for (int j = 0; j < width; j++)
            line.push_back(new Square());

        squares.push_back(line);
    }

    std::vector<ChessPiece*> white, black;

    for (int j = 0; j < width; j++) {
        squares[1][j]->piece = new Pawn('w', vec2{ 1, j }, j);
        white.push_back(squares[1][j]->piece);

        squares[6][j]->piece = new Pawn('b', vec2{ 6, j }, j);
        black.push_back(squares[6][j]->piece);
    }

    squares[0][0]->piece = new Rook('w', vec2{ 0, 0 }, 8);
    squares[0][7]->piece = new Rook('w', vec2{ 0, 7 }, 9);
    squares[7][0]->piece = new Rook('b', vec2{ 7, 0 }, 8);
    squares[7][7]->piece = new Rook('b', vec2{ 7, 7 }, 9);

    squares[0][1]->piece = new Knight('w', vec2{ 0, 1 }, 10);
    squares[0][6]->piece = new Knight('w', vec2{ 0, 6 }, 11);
    squares[7][1]->piece = new Knight('b', vec2{ 7, 1 }, 10);
    squares[7][6]->piece = new Knight('b', vec2{ 7, 6 }, 11);

    squares[0][2]->piece = new Bishop('w', vec2{ 0, 2 }, 12);
    squares[0][5]->piece = new Bishop('w', vec2{ 0, 5 }, 13);
    squares[7][2]->piece = new Bishop('b', vec2{ 7, 2 }, 12);
    squares[7][5]->piece = new Bishop('b', vec2{ 7, 5 }, 13);

    squares[0][3]->piece = new Queen('w', vec2{ 0, 3 }, 14);
    squares[0][4]->piece = new King('w', vec2{ 0, 4 }, 15);

    squares[7][3]->piece = new Queen('b', vec2{ 7, 3 }, 14);
    squares[7][4]->piece = new King('b', vec2{ 7, 4 }, 15);

    white.push_back(squares[0][0]->piece);
    white.push_back(squares[0][7]->piece);
    white.push_back(squares[0][1]->piece);
    white.push_back(squares[0][6]->piece);
    white.push_back(squares[0][2]->piece);
    white.push_back(squares[0][5]->piece);
    white.push_back(squares[0][3]->piece);
    white.push_back(squares[0][4]->piece);

    black.push_back(squares[7][0]->piece);
    black.push_back(squares[7][7]->piece);
    black.push_back(squares[7][1]->piece);
    black.push_back(squares[7][6]->piece);
    black.push_back(squares[7][2]->piece);
    black.push_back(squares[7][5]->piece);
    black.push_back(squares[7][3]->piece);
    black.push_back(squares[7][4]->piece);

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
void Table::movePiece(ChessPiece* piece, vec2 pos) {
    assert(piece != nullptr && "Piece meant to be moved is null");
    assert(isInside(pos) && "Can't move piece outside the squares");

    vec2 prev = piece->pos;
    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    squares[pos.x][pos.y]->piece = piece;
    piece->pos = pos;
    addMove2History(std::make_pair(prev, pos));
}

void Table::movePiece(ChessPiece *piece, const char* pos) {
    assert(strlen(pos) == 2 && "A valid move position needs a line and a column");

    if(pos[0] >= 'a' && isInside(vec2{pos[1] - '1', pos[0] - 'a'}))
        movePiece(piece, vec2{pos[1] - '1', pos[0] - 'a'});
    else
     if (isInside(vec2{pos[0] - '1', pos[1] - 'a'}))
        movePiece(piece, vec2{pos[0] - '1', pos[1] - 'a'});
    else assert(!"Illegal move position");
}

void Table::removePiece(ChessPiece* piece) {
    assert(piece != nullptr && "Piece meant to be deleted is null");
    pieces[piece->color == 'w' ? 0 : 1][piece->index] = nullptr;
    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    delete piece;
}

ChessPiece* Table::getPiece(const char *pos) {
    assert(strlen(pos) == 2 && "A valid move position needs a line and a column");

    if(pos[0] >= 'a' && isInside(vec2{pos[1] - '1', pos[0] - 'a'}))
        return squares[pos[1] - '1'][pos[0] - 'a']->piece;
    else
    if (isInside(vec2{pos[0] - '1', pos[1] - 'a'}))
        return squares[pos[0] - '1'][pos[1] - 'a']->piece;
    else assert(!"Illegal position");
}

bool Table::isInside(vec2 pos) const {
    return pos.x >= 0 && pos.x < height && pos.y >= 0 && pos.y < width;
}

bool Table::canIPlaceItHere(ChessPiece* piece, Square* sq) {
    return !(sq->piece && piece->color == sq->piece->color);
}

std::string Table::getCoords(vec2 pos) {
    assert(isInside(pos) && "Position outside of the table");
    std::string s = "a";
    s[0] += pos.x;

    return s.append(std::to_string(pos.y + 1));
}

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

Table* Table::createNewState(ChessPiece* piece, vec2 pos) {
    Table* t = new Table(*this);
    for (int i = 0; i < t->height; ++i) {
        for (int j = 0; j < t->width; ++j) {
            t->squares[i][j] = new Square(*squares[i][j]);
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
        }
    }
    t->movePiece(t->squares[piece->pos.x][piece->pos.y]->piece, pos);
    return t;
}

bool Table::isAnIllegalMove(Square *sq, ChessPiece *piece) {
    if (!sq->piece) return false;
    return sq->piece->color == piece->color;
}

void Table::printGameBoard(char perspective, bool fromZero, bool xLetters) {
    assert(perspective == 'r' || perspective == 'b' || perspective == 'w' && "Perpective (w)hite/(b)lack/(r)otated");
    std::cout << "###################################\n";
    if (perspective == 'w') {
        for (int i = height - 1; i >= 0; --i) {
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

        std::cout << "   --------------------------------\n";
        std::cout << "   ";

        for (int j = 0; j < width; ++j)
            if (fromZero)
                std::cout << " " << j << "  ";
            else if (xLetters) std::cout << " " << (char)('a' + j) << "  ";
            else std::cout << " " << j + 1 << "  ";
        std::cout << "\n";
    } else if (perspective == 'b') {
        for (int j = width - 1; j >= 0; --j)
            if (fromZero)
                std::cout << " " << j << "  ";
            else if (xLetters) std::cout << " " << (char)('a' + j) << "  ";
            else std::cout << " " << j + 1 << "  ";
        std::cout << "\n";
        std::cout << " -----------------------------------\n";
        for (int i = 0; i <= height - 1; ++i) {
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
        std::cout << "    ";
        for (int k = 0; k < width; ++k)
            if (fromZero)
                std::cout << " " << k << "  ";
                else std::cout << " " << k + 1 << "  ";

        std::cout << "\n    ";
        for (int k = 0; k < width; ++k)
            std::cout << "----";
        std::cout << "\n";

        for (int i = 0; i < width ; ++i) {
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
    std::cout << "####################################\n";
}

// Functii Ovidiu
void Table::moveInAdvance(const char* moves, char color) {
    for (int i = 0; i < strlen(moves); i += 10) {
        char from[3], to[3];

        from[0] = moves[i + 1]; from[1] = moves[i + 2]; from[2] = '\0';
        to[0] = moves[i + 5]; to[1] = moves[i + 6]; to[2] = '\0';

        movePiece(getPiece(from), to);
        color = color == 'w' ? 'b' : 'w';
    }
}

bool Table::hasNoPiecesBetween_line(vec2 pos1, vec2 pos2) {
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

bool Table::hasNoPiecesBetween_diagonal(vec2 pos1, vec2 pos2) {
    // Main diagonal
    if ((pos2.x > pos1.x && pos2.y > pos1.y) ||
        (pos2.x < pos1.x && pos2.y < pos1.x)) {
        vec2 st = pos1.y < pos2.y ? pos1 : pos2;
        vec2 sp = pos1.y > pos2.y ? pos1 : pos2;

        st.x++; st.y++; sp.x--; sp.y--;

        while (st.x <= sp.x) {
            if (squares[st.x][st.y]->piece)
                return false;

            st.x++; st.y++;
        }

        return true;
    }

    // Secondary diagonal
    vec2 st = pos1.y < pos2.y ? pos1 : pos2;
    vec2 sp = pos1.y > pos2.y ? pos1 : pos2;

    st.x++; st.y++; sp.x--; sp.y--;

    while (st.x <= sp.x) {
        if (squares[st.x][st.y]->piece)
            return false;

        st.x--; st.y++;
    }

    return true;
}

bool Table::isAnIllegalMove(ChessPiece* piece, vec2 pos) {
    if (!isInside(pos))
        return true;

    if (!squares[pos.x][pos.y]->piece)
        return false;

    return piece->color == squares[pos.x][pos.y]->piece->color;
}

bool Table::isKingInConflict(King* king, vec2 pos) {
    int line = king->color == 'w' ? 1 : 0;

    if (pieces[line][15]->pos.x == pos.x && abs(pieces[line][15]->pos.y - pos.y) == 1)
        return true;

    if (pieces[line][15]->pos.y == pos.y && abs(pieces[line][15]->pos.x - pos.x) == 1)
        return true;

    if (abs(pieces[line][15]->pos.x - pos.x) == 1 && abs(pieces[line][15]->pos.y - pos.y) == 1)
        return true;

    return false;
}

void Table::markPossibleMovesForPawn(Pawn* pawn) {
    vec2 currPos;

    // One square
    currPos.x = pawn->color == 'w' ? pawn->pos.x + 1 : pawn->pos.x - 1; currPos.y = pawn->pos.y;

    if (!squares[currPos.x][currPos.y]->piece)
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);

    // On diagonal
    currPos.y = pawn->pos.y - 1;

    if (isInside(currPos) && squares[currPos.x][currPos.y]->piece && squares[currPos.x][currPos.y]->piece->color != pawn->color)
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);

    currPos.y = pawn->pos.y + 1;

    if (isInside(currPos) && squares[currPos.x][currPos.y]->piece && squares[currPos.x][currPos.y]->piece->color != pawn->color)
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);

    // Two squares
    if (!pawn->wasMoved) {
        currPos.x = pawn->color == 'w' ? pawn->pos.x + 2 : pawn->pos.x - 2; currPos.y = pawn->pos.y;

        if (!squares[currPos.x][currPos.y]->piece)
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);
    }
}

void Table::markPossibleMovesForKnight(Knight* knight) {
    // Up - right
    if (!isAnIllegalMove(knight, {knight->pos.x + 2, knight->pos.y + 1}))
        squares[1LL * knight->pos.x + 2][1LL * knight->pos.y + 1]->possibleNormalMoves.push_back(knight->pos);

    // Right - up
    if (!isAnIllegalMove(knight, {knight->pos.x + 1, knight->pos.y + 2}))
        squares[1LL * knight->pos.x + 1][1LL * knight->pos.y + 2]->possibleNormalMoves.push_back(knight->pos);

    // Down - right
    if (!isAnIllegalMove(knight, {knight->pos.x - 2, knight->pos.y + 1}))
        squares[1LL * knight->pos.x - 2][1LL * knight->pos.y + 1]->possibleNormalMoves.push_back(knight->pos);

    // Right - down
    if (!isAnIllegalMove(knight, {knight->pos.x - 1, knight->pos.y + 2}))
        squares[1LL * knight->pos.x - 1][1LL * knight->pos.y + 2]->possibleNormalMoves.push_back(knight->pos);

    // Up - left
    if (!isAnIllegalMove(knight, {knight->pos.x + 2, knight->pos.y - 1}))
        squares[1LL * knight->pos.x + 2][1LL * knight->pos.y - 1]->possibleNormalMoves.push_back(knight->pos);

    // Left - up
    if (!isAnIllegalMove(knight, {knight->pos.x + 1, knight->pos.y - 2}))
        squares[1LL * knight->pos.x + 1][1LL * knight->pos.y - 2]->possibleNormalMoves.push_back(knight->pos);

    // Down - left
    if (!isAnIllegalMove(knight, {knight->pos.x - 2, knight->pos.y - 1}))
        squares[1LL * knight->pos.x - 2][1LL * knight->pos.y - 1]->possibleNormalMoves.push_back(knight->pos);

    // Left - down
    if (!isAnIllegalMove(knight, {knight->pos.x - 1, knight->pos.y - 2}))
        squares[1LL * knight->pos.x - 1][1LL * knight->pos.y - 2]->possibleNormalMoves.push_back(knight->pos);
}

void Table::markPossibleMovesForBishop(Bishop* bishop) {
    vec2 currPos;

    // Up - right
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y + 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y++;
    }

    // Up - left
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y - 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y--;
    }

    // Down - right
    currPos.x = bishop->pos.x - 1; currPos.y = bishop->pos.y + 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y++;
    }

    // Down - left
    currPos.x = bishop->pos.x - 1; currPos.y = bishop->pos.y - 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y--;
    }
}

void Table::markPossibleMovesForRook(Rook* rook) {
    vec2 currPos;

    // Up
    currPos.x = rook->pos.x + 1; currPos.y = rook->pos.y;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++;
    }

    // Down
    currPos.x = rook->pos.x - 1; currPos.y = rook->pos.y;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--;
    }

    // Left
    currPos.x = rook->pos.x; currPos.y = rook->pos.y - 1;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y--;
    }

    // Right
    currPos.x = rook->pos.x; currPos.y = rook->pos.y + 1;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y++;
    }
}

void Table::markPossibleMovesForQueen(Queen* queen) {
    vec2 currPos;

    // Up
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++;
    }

    // Down
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--;
    }

    // Left
    currPos.x = queen->pos.x; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y--;
    }

    // Right
    currPos.x = queen->pos.x; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y++;
    }

    // Up - right
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y++;
    }

    // Up - left
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y--;
    }

    // Down - right
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y++;
    }

    // Down - left
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y--;
    }
}

void Table::markPossibleMovesForKing(King *king) {
    vec2 currPos;

    // Up
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y;

    if (!isAnIllegalMove(king, currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Down
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y;

    if (!isAnIllegalMove(king, currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Left
    currPos.x = king->pos.x; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Right
    currPos.x = king->pos.x; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Up - right
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Up - left
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Down - right
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Down - left
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Verify if white / black has already castled
    if (king->castle)
        return;

    int line = king->color == 'w' ? 0 : 1;

    // Short castle
    if (pieces[line][9])
        if (!king->wasMoved &&
            !((Rook*)pieces[line][9])->wasMoved &&
            !king->isInCheckAt(this, king->pos) &&
            !king->isInCheckAt(this, vec2{king->pos.x + 1, king->pos.y}) &&
            !king->isInCheckAt(this, vec2{king->pos.x + 2, king->pos.y}) &&
            hasNoPiecesBetween_line(king->pos, pieces[line][9]->pos))
                king->color == 'w' ? shortCastle_white = true : shortCastle_black = true;

    // Long castle
    if (pieces[line][8])
        if (!king->wasMoved &&
            !((Rook*)pieces[line][8])->wasMoved &&
            !king->isInCheckAt(this, king->pos) &&
            !king->isInCheckAt(this, vec2{king->pos.x - 1, king->pos.y}) &&
            !king->isInCheckAt(this, vec2{king->pos.x - 2, king->pos.y}) &&
            !king->isInCheckAt(this, vec2{king->pos.x - 3, king->pos.y}) &&
            hasNoPiecesBetween_line(king->pos, pieces[line][8]->pos))
                king->color == 'w' ? longCastle_white = true : longCastle_black = true;
}
