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

    if(pos[0] >= 'a' && isInside(vec2{pos[0] - 'a', pos[1] - '1'}))
        movePiece(piece, vec2{pos[0] - 'a', pos[1] - '1'});
    else
     if (isInside(vec2{pos[1] - 'a', pos[0] - '1'}))
        movePiece(piece, vec2{pos[1] - 'a', pos[0] - '1'});
    else assert(!"Illegal move position");
}

void Table::removePiece(ChessPiece* piece) {
    assert(piece != nullptr && "Piece meant to be deleted is null");
    pieces[piece->color == 'w' ? 0 : 1][piece->index] = nullptr;
    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    delete piece;
}

ChessPiece *Table::getPiece(const char *pos) {
    assert(strlen(pos) == 2 && "A valid move position needs a line and a column");

    if(pos[0] >= 'a' && isInside(vec2{pos[0] - 'a', pos[1] - '1'}))
        return squares[pos[0] - 'a'][pos[1] - '1']->piece;
    else
    if (isInside(vec2{pos[1] - 'a', pos[0] - '1'}))
        return squares[pos[1] - 'a'][pos[0] - '1']->piece;
    else assert(!"Illegal move position");
}

bool Table::isInside(vec2 pos) {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
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

void Table::printTable() {
    std::cout << "###########################\n";

    if (orientation == 1) {
        for (int i = height - 1; i >= 0; --i) {
            std::cout << (char)('a' + i) << "| ";

            for (int j = 0; j < width; ++j)
                if (squares[i][j]->piece)
                    std::cout << " " << squares[i][j]->piece->score << " ";
                else
                    std::cout << " - ";

            std::cout << "\n";
        }

        std::cout << "   ------------------------\n";
        std::cout << "   ";

        for (int j = 0; j < width; ++j)
            std::cout << " " << j + 1 << " ";
    }
    else {
        for (int i = 0; i <= height - 1; ++i) {
            std::cout << (char)('h' - i) << "| ";

            for (int j = 0; j < width; ++j)
                if (squares[i][j]->piece)
                    std::cout << " " << squares[i][j]->piece->score << " ";
                else
                    std::cout << " - ";

            std::cout << "\n";
        }

        std::cout << "   ------------------------\n";
        std::cout << "   ";

        for (int j = 0; j < width; ++j)
            std::cout << " " << width - j << " ";
    }

    std::cout << "\n###########################\n";
}

void Table::programmerPrint() {
    std::cout << "###########################\n";

    if (orientation == 1) {
        for (int i = height - 1; i >= 0; --i) {
            std::cout << i << "| ";

            for (int j = 0; j < width; ++j)
                if (squares[i][j]->piece)
                    std::cout << " " << squares[i][j]->piece->score << " ";
                else
                    std::cout << " - ";

            std::cout << "\n";
        }

        std::cout << "  ------------------------\n";
        std::cout << "   ";

        for (int j = 0; j < width; ++j)
            std::cout << " " << j << " ";
    }
    else {
        for (int i = 0; i <= height - 1; ++i) {
            std::cout << (char)('h' - i) << "| ";

            for (int j = 0; j < width; ++j)
                if (squares[i][j]->piece)
                    std::cout << " " << squares[i][j]->piece->score << " ";
                else
                    std::cout << " - ";

            std::cout << "\n";
        }

        std::cout << "   ------------------------\n";
        std::cout << "   ";

        for (int j = 0; j < width; ++j)
            std::cout << " " << width - j << " ";
    }

    std::cout << "\n###########################\n";
}

// Functii Ovidiu
bool Table::hasNoPiecesBetween_line(vec2 pos1, vec2 pos2) {
    if (pos1.x == pos2.x) {
        int stY = std::min(pos1.y, pos2.y);
        int spY = std::max(pos1.y, pos2.y);

        while (stY != spY) {
            if (squares[stY][pos1.x]->piece)
                return false;

            stY++;
        }

        return true;
    }

    int stX = std::min(pos1.x, pos2.x);
    int spX = std::max(pos1.x, pos2.x);

    while (stX != spX) {
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

        while (st.x != sp.x) {
            if (squares[st.x][st.y]->piece)
                return false;

            st.x++; st.y++;
        }

        return true;
    }

    // Secondary diagonal
    vec2 st = pos1.y < pos2.y ? pos1 : pos2;
    vec2 sp = pos1.y > pos2.y ? pos1 : pos2;

    while (st.x != sp.x) {
        if (squares[st.x][st.y]->piece)
            return false;

        st.x--; st.y++;
    }

    return true;
}

bool Table::isAnIllegalMove(ChessPiece* piece, vec2 pos) {
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
    currPos.x = pawn->pos.x; currPos.y = pawn->color == 'w' ? pawn->pos.y + 1 : pawn->pos.y - 1;

    if (!squares[currPos.x][currPos.y]->piece)
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);

    // On diagonal
    currPos.x = pawn->pos.x - 1;

    if (isInside(currPos))
        if (squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(pawn, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);

    currPos.x = pawn->pos.x + 1;

    if (isInside(currPos))
        if (squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(pawn, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);

    // Two squares
    if (!pawn->wasMoved) {
        currPos.x = pawn->pos.x; currPos.y = pawn->color == 'w' ? pawn->pos.y + 2 : pawn->pos.y - 2;

        if (!squares[currPos.x][currPos.y]->piece)
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);
    }
}

void Table::markPossibleMovesForKnight(Knight* knight) {
    vec2 currPos;

    // Up - right
    currPos.x = knight->pos.x + 1; currPos.y = knight->pos.y + 2;

    if (isInside(currPos))
        if (!squares[currPos.x][currPos.y]->piece || !isAnIllegalMove(knight, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

    // Right - up
    currPos.x = knight->pos.x + 2; currPos.y = knight->pos.y + 1;

    if (isInside(currPos))
        if (!squares[currPos.x][currPos.y]->piece || !isAnIllegalMove(knight, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

    // Right - down
    currPos.x = knight->pos.x + 2; currPos.y = knight->pos.y - 1;

    if (isInside(currPos))
        if (!squares[currPos.x][currPos.y]->piece || !isAnIllegalMove(knight, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

    // Down - right
    currPos.x = knight->pos.x + 1; currPos.y = knight->pos.y - 2;

    if (isInside(currPos))
        if (!squares[currPos.x][currPos.y]->piece || !isAnIllegalMove(knight, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

    // Up - left
    currPos.x = knight->pos.x - 1; currPos.y = knight->pos.y + 2;

    if (isInside(currPos))
        if (!squares[currPos.x][currPos.y]->piece || !isAnIllegalMove(knight, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

    // Left - up
    currPos.x = knight->pos.x - 2; currPos.y = knight->pos.y + 1;

    if (isInside(currPos))
        if (!squares[currPos.x][currPos.y]->piece || !isAnIllegalMove(knight, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

    // Left - down
    currPos.x = knight->pos.x - 2; currPos.y = knight->pos.y - 1;

    if (isInside(currPos))
        if (!squares[currPos.x][currPos.y]->piece || !isAnIllegalMove(knight, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

    // Down - left
    currPos.x = knight->pos.x - 1; currPos.y = knight->pos.y - 2;

    if (isInside(currPos))
        if (!squares[currPos.x][currPos.y]->piece || !isAnIllegalMove(knight, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);
}

void Table::markPossibleMovesForBishop(Bishop* bishop) {
    vec2 currPos;

    // Up - right
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y + 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalMove(bishop, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x++; currPos.y++;
    }

    // Up - left
    currPos.x = bishop->pos.x - 1; currPos.y = bishop->pos.y + 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalMove(bishop, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x--; currPos.y++;
    }

    // Down - right
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y - 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalMove(bishop, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x++; currPos.y--;
    }

    // Down - left
    currPos.x = bishop->pos.x - 1; currPos.y = bishop->pos.y - 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalMove(bishop, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x--; currPos.y--;
    }
}

void Table::markPossibleMovesForRook(Rook* rook) {
    vec2 currPos;

    // Up
    currPos.x = rook->pos.x; currPos.y = rook->pos.y + 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalMove(rook, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.y++;
    }

    // Down
    currPos.x = rook->pos.x; currPos.y = rook->pos.y - 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalMove(rook, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.y--;
    }

    // Left
    currPos.x = rook->pos.x - 1; currPos.y = rook->pos.y;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalMove(rook, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.x--;
    }

    // Right
    currPos.x = rook->pos.x + 1; currPos.y = rook->pos.y;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalMove(rook, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.x++;
    }
}

void Table::markPossibleMovesForQueen(Queen* queen) {
    vec2 currPos;

    // Up
    currPos.x = queen->pos.x; currPos.y = queen->pos.y + 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen ->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalMove(queen, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.y++;
    }

    // Down
    currPos.x = queen->pos.x; currPos.y = queen->pos.y - 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalMove(queen, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.y--;
    }

    // Left
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalMove(queen, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.x--;
    }

    // Right
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalMove(queen, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.x++;
    }

    // Up - right
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y + 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalMove(queen, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x++; currPos.y++;
    }

    // Up - left
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y + 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalMove(queen, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x--; currPos.y++;
    }

    // Down - right
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y - 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalMove(queen, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x++; currPos.y--;
    }

    // Down - left
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y - 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalMove(queen, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x--; currPos.y--;
    }
}

void Table::markPossibleMovesForKing(King *king) {
    vec2 currPos;

    // Up
    currPos.x = king->pos.x; currPos.y = king->pos.y + 1;

    if (isInside(currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        if (!squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(king, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Down
    currPos.x = king->pos.x; currPos.y = king->pos.y - 1;

    if (isInside(currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        if (!squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(king, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Left
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y;

    if (isInside(currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        if (!squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(king, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Right
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y;

    if (isInside(currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        if (!squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(king, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Up - right
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y + 1;

    if (isInside(currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        if (!squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(king, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Up - left
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y + 1;

    if (isInside(currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        if (!squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(king, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Down - right
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y - 1;

    if (isInside(currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        if (!squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(king, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(king->pos);

    // Down - left
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y - 1;

    if (isInside(currPos) && !king->isInCheckAt(this, currPos) && !isKingInConflict(king, currPos))
        if (!squares[currPos.x][currPos.y]->piece && !isAnIllegalMove(king, currPos))
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
