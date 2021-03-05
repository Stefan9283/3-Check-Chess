#include "Table.h"

Table::Table() {
    for (int i = 0; i < height; i++) {
        std::vector<Square*> line;

        for (int j = 0; j < width; j++)
            line.push_back(new Square());

        squares.push_back(line);
    }

    for (int j = 0; j < width; j++) {
        squares[1][j]->piece = new Pawn('w', vec2{ 1, j });
        squares[6][j]->piece = new Pawn('b', vec2{ 6, j });
    }

    squares[0][0]->piece = new Rook('w', vec2{ 0, 0 });
    squares[0][7]->piece = new Rook('w', vec2{ 0, 7 });
    squares[7][0]->piece = new Rook('b', vec2{ 7, 0 });
    squares[7][7]->piece = new Rook('b', vec2{ 7, 7 });

    squares[0][1]->piece = new Knight('w', vec2{ 0, 1 });
    squares[0][6]->piece = new Knight('w', vec2{ 0, 6 });
    squares[7][1]->piece = new Knight('b', vec2{ 7, 1 });
    squares[7][6]->piece = new Knight('b', vec2{ 7, 6 });

    squares[0][2]->piece = new Bishop('w', vec2{ 0, 2 });
    squares[0][5]->piece = new Bishop('w', vec2{ 0, 5 });
    squares[7][2]->piece = new Bishop('b', vec2{ 7, 2 });
    squares[7][5]->piece = new Bishop('b', vec2{ 7, 5 });

    squares[0][3]->piece = new Queen('w', vec2{ 0, 3 });
    squares[0][4]->piece = new King('w', vec2{ 0, 4 });

    squares[7][3]->piece = new King('b', vec2{ 7, 3 });
    squares[7][4]->piece = new Queen('b', vec2{ 7, 4 });
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

    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    squares[pos.x][pos.y]->piece = piece;
    piece->pos = pos;
}

void Table::removePiece(ChessPiece* piece) {
    assert(piece != nullptr && "Piece meant to be deleted is null");

    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    delete piece;
}

bool Table::isInside(vec2 pos) {
    return pos.x >= 0 && pos.x < width&& pos.y >= 0 && pos.y < height;
}

bool Table::canIPlaceItHere(ChessPiece* piece, Square* sq) {
    if (sq->piece)
        return piece->color == sq->piece->color;

    return true;
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

// Functii Ovidiu
bool Table::isAnIllegalPiece(ChessPiece* piece, vec2 pos) {
    if (piece->color == squares[pos.x][pos.y]->piece->color ||
        !squares[pos.x][pos.y]->piece->score)
        return true;

    return false;
}

void Table::markPossibleMovesForPawn(Pawn* pawn) {
    vec2 currPos;

    // One square
    currPos.x = pawn->pos.x; currPos.y = pawn->pos.y + 1;
    squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);

    if (squares[currPos.x][currPos.y]->piece)
        if (isAnIllegalPiece(pawn, currPos))
            squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    
    // Two squares
    if (!pawn->wasMoved) {
        currPos.x = pawn->pos.x; currPos.y = pawn->pos.y + 2;
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(pawn->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(pawn, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }
}

void Table::markPossibleMovesForKnight(Knight* knight) {
    vec2 currPos;

    // Up - right
    currPos.x = knight->pos.x + 1; currPos.y = knight->pos.y + 2;

    if (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(knight, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }

    // Right - up
    currPos.x = knight->pos.x + 2; currPos.y = knight->pos.y + 1;

    if (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(knight, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }

    // Right - down
    currPos.x = knight->pos.x + 2; currPos.y = knight->pos.y - 1;

    if (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(knight, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }

    // Down - right
    currPos.x = knight->pos.x + 1; currPos.y = knight->pos.y - 2;

    if (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(knight, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }

    // Up - left
    currPos.x = knight->pos.x - 1; currPos.y = knight->pos.y + 2;

    if (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(knight, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }

    // Left - up
    currPos.x = knight->pos.x - 2; currPos.y = knight->pos.y + 1;

    if (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(knight, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }

    // Left - down
    currPos.x = knight->pos.x - 2; currPos.y = knight->pos.y - 1;

    if (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(knight, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }

    // Down - left
    currPos.x = knight->pos.x - 1; currPos.y = knight->pos.y - 2;

    if (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(knight->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(knight, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();
    }
}

void Table::markPossibleMovesForBishop(Bishop* bishop) {
    vec2 currPos;

    // Up - right
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y + 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(bishop->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalPiece(bishop, currPos))
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
                if (isAnIllegalPiece(bishop, currPos))
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
                if (isAnIllegalPiece(bishop, currPos))
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
                if (isAnIllegalPiece(bishop, currPos))
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
            if (isAnIllegalPiece(rook, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.y++;
    }

    // Down
    currPos.x = rook->pos.x; currPos.y = rook->pos.y - 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(rook, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.y--;
    }

    // Left
    currPos.x = rook->pos.x - 1; currPos.y = rook->pos.y;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(rook, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.x--;
    }

    // Right
    currPos.x = rook->pos.x + 1; currPos.y = rook->pos.y;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(rook->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(rook, currPos))
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
            if (isAnIllegalPiece(queen, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.y++;
    }

    // Down
    currPos.x = queen->pos.x; currPos.y = queen->pos.y - 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(queen, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.y--;
    }

    // Left
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(queen, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.x--;
    }

    // Right
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece)
            if (isAnIllegalPiece(queen, currPos))
                squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

        currPos.x++;
    }

    // Up - right
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y + 1;

    while (isInside(currPos)) {
        squares[currPos.x][currPos.y]->possibleNormalMoves.push_back(queen->pos);

        if (squares[currPos.x][currPos.y]->piece) {
            if (squares[currPos.x][currPos.y]->piece)
                if (isAnIllegalPiece(queen, currPos))
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
                if (isAnIllegalPiece(queen, currPos))
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
                if (isAnIllegalPiece(queen, currPos))
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
                if (isAnIllegalPiece(queen, currPos))
                    squares[currPos.x][currPos.y]->possibleNormalMoves.pop_back();

            break;
        }

        currPos.x--; currPos.y--;
    }
}
