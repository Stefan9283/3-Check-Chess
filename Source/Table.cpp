
#include "Table.h"
#include <random>

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
#pragma region pieces manuvering
void Table::movePiece(ChessPiece* piece, vec2<int> pos) {
    assert(piece && "Piece meant to be moved is null");
    assert(isInside(pos) && "Can't move piece outside the squares");
    
    if (dynamic_cast<Pawn*>(piece)) {
        if (!pos.x || pos.x == height - 1) {
            Queen* queen = ((Pawn*)piece)->promotePawn(this);

            removePiece(piece);
            piece = queen;

            pieces[piece->color == 'w' ? 0 : 1].push_back(piece);
            piece->noOfMoves--;
        } else if (!squares[pos.x][pos.y]->piece && abs(piece->pos.y - pos.y) == 1)
            removePiece(squares[piece->pos.x][pos.y]->piece);
        else
            ((Pawn*)piece)->wasMoved = true;
    }

    piece->noOfMoves++;

    if (squares[pos.x][pos.y]->piece)
        removePiece(squares[pos.x][pos.y]->piece);

    vec2<int> prev = piece->pos;

    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    squares[pos.x][pos.y]->piece = piece;
    piece->pos = pos;

    addMove2History(std::make_pair(prev, pos));
    turn = 1 - turn;
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

    int total = 0, line = color == 'w' ? 0 : 1;

    for (ChessPiece* chessPiece : pieces[line])
        if (chessPiece)
            total += chessPiece->score;

    return total;
}
#pragma endregion
vec2<int> Table::string2coords(const char *coords) {
    assert(strlen(coords) >= 2 && "Coords should have at least a line and a column");
    return {coords[1] - '0' - 1, coords[0] - 'a'};
}

std::string Table::coords2string(vec2<int> pos) const {
    assert(isInside(pos) && "Position outside of the table");
    std::string s = "a";
    s[0] += pos.y;
    return s.append(std::to_string(pos.x + 1));
}

Table* Table::createNewState(ChessPiece* piece, vec2<int> pos) {
    auto* table = new Table(*this);

    for (int i = 0; i < table->height; ++i)
        for (int j = 0; j < table->width; ++j) {
            table->squares[i][j] = new Square(*squares[i][j]);
            table->squares[i][j]->possibleMoves.clear();

            ChessPiece* piece = table->squares[i][j]->piece;

            if (!piece)
                continue;

            if (dynamic_cast<Pawn*>(piece))
                table->squares[i][j]->piece = new Pawn(*dynamic_cast<Pawn*>(piece));
            else if (dynamic_cast<Rook*>(piece))
                table->squares[i][j]->piece = new Rook(*dynamic_cast<Rook*>(piece));
            else if (dynamic_cast<Bishop*>(piece))
                table->squares[i][j]->piece = new Bishop(*dynamic_cast<Bishop*>(piece));
            else if (dynamic_cast<Queen*>(piece))
                table->squares[i][j]->piece = new Queen(*dynamic_cast<Queen*>(piece));
            else if (dynamic_cast<Knight*>(piece))
                table->squares[i][j]->piece = new Knight(*dynamic_cast<Knight*>(piece));
            else if (dynamic_cast<King*>(piece))
                table->squares[i][j]->piece = new King(*dynamic_cast<King*>(piece));

            table->pieces[piece->color == 'w' ? 0 : 1][piece->index] = table->squares[i][j]->piece;
        }

    if (piece)
        table->movePiece(table->squares[piece->pos.x][piece->pos.y]->piece, pos);

    return table;
}

void Table::printGameBoard(char perspective, bool fromZero, bool yLetters, int tabsCount)  {
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
            else if (yLetters) std::cout << " " << (char)('a' + j) << "  ";
            else std::cout << " " << j + 1 << "  ";
        std::cout << "\n";
    } else if (perspective == 'b') {
        printTabs(tabsCount);
        for (int j = width - 1; j >= 0; --j)
            if (fromZero)
                std::cout << " " << j << "  ";
            else if (yLetters) std::cout << " " << (char)('a' + j) << "  ";
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
            else if (yLetters) std::cout << " " << (char)('a' + i) << " |";
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

std::vector<ChessPiece *> Table::getVulnerablePieces(int leastNumOfPiecesThatShouldBeAbleToTakeThePiece) {
    std::vector<ChessPiece *> res;

    turn = 1 - turn;
    markAllPossibleMoves();
    turn = 1 - turn;

    for (ChessPiece* piece : pieces[turn]) {
        if (squares[piece->pos.x][piece->pos.y]->possibleMoves.size() >= leastNumOfPiecesThatShouldBeAbleToTakeThePiece)
            res.push_back(piece);
    }

    unmarkAllPossibleMoves();

    return res;
}

// Functii Ovidiu
void Table::parseMove(const char* s) {
    const char from[] = {s[strlen(s) - 4], s[strlen(s) - 3], '\0'};
    const char to[] = {s[strlen(s) - 2], s[strlen(s) - 1], '\0'};

    movePiece(getPiece(from), to);
}


std::string Table::getARandomMove() {

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,7);

    ChessPiece* pawn = nullptr;

    std::vector<PieceMove> moves;

    bool doIhaveAnyPawns = false;
    for (int i = 0; i < 8; i++) {
        if (pieces[turn][i] && !pieces[turn][i]->getPositions(this).empty()) {
            doIhaveAnyPawns = true;
            break;
        }
    }

    if (!doIhaveAnyPawns) return std::string("resign");


    while (true) {
        pawn = pieces[turn][distribution(generator)];

        if (pawn) {
            moves = pawn->getPositions(this);
            if (!moves.empty())
                break;
        }
    }

    std::uniform_int_distribution<int> mvDistribution(0, moves.size() - 1);

    std::string from = coords2string(pawn->pos), to = coords2string(moves[mvDistribution(generator)].ownMove);

    return std::string("move ").append(from).append(to);
}

bool Table::hasNoPiecesBetween_axis(vec2<int> pos1, vec2<int> pos2) {
    if (pos1.x == pos2.x) {
        int stY = std::min(pos1.y, pos2.y) + 1;
        int spY = std::max(pos1.y, pos2.y) - 1;

        while (stY <= spY) {
            if (squares[pos1.x][stY]->piece)
                return false;

            stY++;
        }

        return true;
    }

    int stX = std::min(pos1.x, pos2.x) + 1;
    int spX = std::max(pos1.x, pos2.x) - 1;

    while (stX <= spX) {
        if (squares[stX][pos1.y]->piece)
            return false;

        stX++;
    }

    return true;
}

bool Table::hasNoPiecesBetween_diagonal(vec2<int> pos1, vec2<int> pos2) {
    // Main diagonal
    if ((pos2.x > pos1.x && pos2.y > pos1.y) ||
        (pos2.x < pos1.x && pos2.y < pos1.y)) {
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

    st.x--; st.y++; sp.x++; sp.y--;

    while (st.x >= sp.x) {
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
        (piece->color == squares[pos.x][pos.y]->piece->color ||
        dynamic_cast<King*>(squares[pos.x][pos.y]->piece)))
            return true;

    if (dynamic_cast<King*>(piece)) {
        if (isKingInDanger(pieces[turn][14], pos) || isKingInConflict((King*)piece, pos))
            return true;
    } else if (isKingInDanger(piece, pos))
        return true;

    return false;
}

bool Table::isKingInConflict(King* king, vec2<int> pos) {
    int line = king->color == 'w' ? 1 : 0;

    return pos.getDistanceTo(pieces[line][14]->pos) < 2;
}

bool Table::isKingInDanger(ChessPiece* piece, vec2<int> pos) {
    assert(piece && isInside(pos));

    if (piece->pos == pos)
        return ((King*)piece)->isInCheck(this);

    ChessPiece* oldPiece = squares[pos.x][pos.y]->piece;
    vec2<int> oldPos = piece->pos;

    squares[piece->pos.x][piece->pos.y]->piece = nullptr;
    squares[pos.x][pos.y]->piece = piece;
    piece->pos = pos;

    if (oldPiece)
        pieces[turn == 0 ? 1 : 0][oldPiece->index] = nullptr;

    bool inCheck = ((King*)pieces[turn][14])->isInCheck(this);

    piece->pos = oldPos;
    squares[piece->pos.x][piece->pos.y]->piece = piece;
    squares[pos.x][pos.y]->piece = oldPiece;

    if (oldPiece)
        pieces[turn == 0 ? 1 : 0][oldPiece->index] = oldPiece;

    return inCheck;
}

bool Table::hasLegalMoves() {
    markAllPossibleMoves();

    bool found = false;

    for (int i = 0; i < height && !found; i++)
        for (int j = 0; j < width && !found; j++)
            if (squares[i][j]->possibleMoves.size())
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
            squares[i][j]->possibleMoves.clear();
}

bool Table::canEnPassant(Pawn* pawn, vec2<int> pos) {
    if (!isInside(pos))
        return false;

    if (!dynamic_cast<Pawn*>(squares[pawn->pos.x][pos.y]->piece))
        return false;

    if (pawn->color == squares[pawn->pos.x][pos.y]->piece->color)
        return false;

    if (history.back().move.second != vec2<int>(pawn->pos.x, pos.y))
        return false;

    if (abs(history.back().move.second.x - history.back().move.first.x) != 2)
        return false;

    ChessPiece* oldPiece = squares[pawn->pos.x][pos.y]->piece;
    vec2<int> oldPos = pawn->pos;

    squares[pawn->pos.x][pawn->pos.y]->piece = nullptr;
    squares[pos.x][pos.y]->piece = pawn;
    pawn->pos = pos;

    squares[oldPos.x][pos.y]->piece = nullptr;
    pieces[turn == 0 ? 1 : 0][oldPiece->index] = nullptr;

    bool inCheck = ((King*)pieces[turn][14])->isInCheck(this);

    pieces[turn == 0 ? 1 : 0][oldPiece->index] = oldPiece;
    squares[oldPos.x][pos.y]->piece = oldPiece;

    pawn->pos = oldPos;
    squares[pos.x][pos.y]->piece = nullptr;
    squares[pawn->pos.x][pawn->pos.y]->piece = pawn;

    return inCheck;
}

bool Table::canCastleShort(King* king) {
    if (!pieces[turn][9])
        return false;

    if (king->wasMoved || ((Rook*)pieces[turn][9])->wasMoved)
        return false;

    if (!hasNoPiecesBetween_axis(king->pos, pieces[turn][9]->pos))
        return false;

    if (isKingInDanger(king, king->pos) ||
        isKingInDanger(king, vec2<int>{king->pos.x, king->pos.y + 1}) ||
        isKingInDanger(king, vec2<int>{king->pos.x, king->pos.y + 2}))
            return false;

    return true;
}

bool Table::canCastleLong(King* king) {
    if (!pieces[turn][8])
        return false;

    if (king->wasMoved || ((Rook*)pieces[turn][8])->wasMoved)
        return false;

    if (!hasNoPiecesBetween_axis(king->pos, pieces[turn][8]->pos))
        return false;

    if (isKingInDanger(king, king->pos) ||
        isKingInDanger(king, vec2<int>{king->pos.x, king->pos.y - 1}) ||
        isKingInDanger(king, vec2<int>{king->pos.x, king->pos.y - 2}) ||
        isKingInDanger(king, vec2<int>{king->pos.x, king->pos.y - 3}))
            return false;

    return false;
}

void Table::markPossibleMovesForPawn(Pawn* pawn) {
    vec2<int> currPos;

    // One square
    currPos.x = pawn->pos.x + (pawn->color == 'w' ? 1 : -1); currPos.y = pawn->pos.y;

    if (isInside(currPos) && !squares[currPos.x][currPos.y]->piece && !isKingInDanger(pawn, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(pawn);

    // On diagonal
    currPos.x = pawn->pos.x + (pawn->color == 'w' ? 1 : -1);  currPos.y = pawn->pos.y - 1;

    if (isInside(currPos) && squares[currPos.x][currPos.y]->piece)
        if (squares[currPos.x][currPos.y]->piece->color != pawn->color && !isKingInDanger(pawn, currPos))
            squares[currPos.x][currPos.y]->possibleMoves.push_back(pawn);

    currPos.x = pawn->pos.x + (pawn->color == 'w' ? 1 : -1);  currPos.y = pawn->pos.y + 1;

    if (isInside(currPos) && squares[currPos.x][currPos.y]->piece)
        if (squares[currPos.x][currPos.y]->piece->color != pawn->color && !isKingInDanger(pawn, currPos))
            squares[currPos.x][currPos.y]->possibleMoves.push_back(pawn);

    // Two squares
    if (!pawn->wasMoved) {
        currPos.x = pawn->pos.x + (pawn->color == 'w' ? 2 : -2); currPos.y = pawn->pos.y;

        if (isInside(currPos) && !squares[currPos.x][currPos.y]->piece)
            if (!squares[currPos.x - (pawn->color == 'w' ? 1 : -1)][currPos.y]->piece && !isKingInDanger(pawn, currPos))
                squares[currPos.x][currPos.y]->possibleMoves.push_back(pawn);
    }

    // En passant
    currPos.x = pawn->pos.x + (pawn->color == 'w' ? 1 : -1); currPos.y = pawn->pos.y - 1;

    if (canEnPassant(pawn, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(pawn);

    currPos.x = pawn->pos.x + (pawn->color == 'w' ? 1 : -1); currPos.y = pawn->pos.y + 1;

    if (canEnPassant(pawn, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(pawn);
}

void Table::markPossibleMovesForKnight(Knight* knight) {
    // Up - right
    if (!isAnIllegalMove(knight, {knight->pos.x + 2, knight->pos.y + 1}))
        squares[knight->pos.x + 2][knight->pos.y + 1]->possibleMoves.push_back(knight);

    // Right - up
    if (!isAnIllegalMove(knight, {knight->pos.x + 1, knight->pos.y + 2}))
        squares[knight->pos.x + 1][knight->pos.y + 2]->possibleMoves.push_back(knight);

    // Down - right
    if (!isAnIllegalMove(knight, {knight->pos.x - 2, knight->pos.y + 1}))
        squares[knight->pos.x - 2][knight->pos.y + 1]->possibleMoves.push_back(knight);

    // Right - down
    if (!isAnIllegalMove(knight, {knight->pos.x - 1, knight->pos.y + 2}))
        squares[knight->pos.x - 1][knight->pos.y + 2]->possibleMoves.push_back(knight);

    // Up - left
    if (!isAnIllegalMove(knight, {knight->pos.x + 2, knight->pos.y - 1}))
        squares[knight->pos.x + 2][knight->pos.y - 1]->possibleMoves.push_back(knight);

    // Left - up
    if (!isAnIllegalMove(knight, {knight->pos.x + 1, knight->pos.y - 2}))
        squares[knight->pos.x + 1][knight->pos.y - 2]->possibleMoves.push_back(knight);

    // Down - left
    if (!isAnIllegalMove(knight, {knight->pos.x - 2, knight->pos.y - 1}))
        squares[knight->pos.x - 2][knight->pos.y - 1]->possibleMoves.push_back(knight);

    // Left - down
    if (!isAnIllegalMove(knight, {knight->pos.x - 1, knight->pos.y - 2}))
        squares[knight->pos.x - 1][knight->pos.y - 2]->possibleMoves.push_back(knight);
}

void Table::markPossibleMovesForBishop(Bishop* bishop) {
    vec2<int> currPos;

    // Up - right
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y + 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(bishop);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y++;
    }

    // Up - left
    currPos.x = bishop->pos.x + 1; currPos.y = bishop->pos.y - 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(bishop);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y--;
    }

    // Down - right
    currPos.x = bishop->pos.x - 1; currPos.y = bishop->pos.y + 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(bishop);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y++;
    }

    // Down - left
    currPos.x = bishop->pos.x - 1; currPos.y = bishop->pos.y - 1;

    while (!isAnIllegalMove(bishop, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(bishop);

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
        squares[currPos.x][currPos.y]->possibleMoves.push_back(rook);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++;
    }

    // Down
    currPos.x = rook->pos.x - 1; currPos.y = rook->pos.y;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(rook);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--;
    }

    // Left
    currPos.x = rook->pos.x; currPos.y = rook->pos.y - 1;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(rook);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y--;
    }

    // Right
    currPos.x = rook->pos.x; currPos.y = rook->pos.y + 1;

    while (!isAnIllegalMove(rook, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(rook);

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
        squares[currPos.x][currPos.y]->possibleMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++;
    }

    // Down
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--;
    }

    // Left
    currPos.x = queen->pos.x; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y--;
    }

    // Right
    currPos.x = queen->pos.x; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.y++;
    }

    // Up - right
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y++;
    }

    // Up - left
    currPos.x = queen->pos.x + 1; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x++; currPos.y--;
    }

    // Down - right
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y + 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y++;
    }

    // Down - left
    currPos.x = queen->pos.x - 1; currPos.y = queen->pos.y - 1;

    while (!isAnIllegalMove(queen, currPos)) {
        squares[currPos.x][currPos.y]->possibleMoves.push_back(queen);

        if (squares[currPos.x][currPos.y]->piece)
            break;

        currPos.x--; currPos.y--;
    }
}

void Table::markPossibleMovesForKing(King *king) {
    vec2<int> currPos;

    // Up
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y;

    if (!isAnIllegalMove(king, currPos) )
        squares[currPos.x][currPos.y]->possibleMoves.push_back(king);

    // Down
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(king);

    // Left
    currPos.x = king->pos.x; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(king);

    // Right
    currPos.x = king->pos.x; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(king);

    // Up - right
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(king);

    // Up - left
    currPos.x = king->pos.x + 1; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(king);

    // Down - right
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y + 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(king);

    // Down - left
    currPos.x = king->pos.x - 1; currPos.y = king->pos.y - 1;

    if (!isAnIllegalMove(king, currPos))
        squares[currPos.x][currPos.y]->possibleMoves.push_back(king);

    // Verify if white / black has already castled
    if (king->castle)
        return;

    // Short castle
    if (canCastleShort(king))
        king->color == 'w' ? squares[0][6]->possibleMoves.push_back(king) : squares[7][6]->possibleMoves.push_back(king);

    // Long castle
    if (canCastleLong(king))
        king->color == 'w' ? squares[0][2]->possibleMoves.push_back(king) : squares[7][2]->possibleMoves.push_back(king);
}

bool Table::isSquareOfTheSameColor(vec2<int> pos1, vec2<int> pos2) {
    return squares[pos1.x][pos1.y]->color == squares[pos2.x][pos2.y]->color;
}

bool Table::isSquareOfTheSameColor(ChessPiece* piece1, ChessPiece* piece2) {
    return isSquareOfTheSameColor(piece1->pos, piece2->pos);
}
