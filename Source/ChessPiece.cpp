#include "ChessPiece.h"
#include "Table.h"

ChessPiece::ChessPiece(char color, vec2<int> pos, int index) {
    assert((color == 'w' || color == 'b') && "Chess Piece color should be either (b)lack or (w)hite");
    this->color = color; this->pos = pos; this->score = -1; this->index = index; this->abbreviation = '#';
}
ChessPiece::~ChessPiece() = default;

King::King(char color, vec2<int> pos, int index) : ChessPiece(color, pos, index) {score = 0; abbreviation = 'K';}
std::vector<PieceMove> King::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    vec2<int> v{};

    v = vec2<int>{ pos.x + 1, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2<int>{ pos.x + 1, pos.y };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2<int>{ pos.x + 1, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2<int>{ pos.x, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2<int>{ pos.x, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2<int>{ pos.x - 1, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2<int>{ pos.x - 1, pos.y };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2<int>{ pos.x - 1, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    return moves;
} // {DONE}

Queen::Queen(char color, vec2<int> pos, int index) : ChessPiece(color, pos, index) {score = 9; abbreviation = 'Q';}
std::vector<PieceMove> Queen::getPositions(Table* t) {
    std::vector<PieceMove> moves, rmoves, bmoves;

    Rook r(color, pos, index);;
    rmoves = r.getPositions(t);
    moves.insert(moves.begin(), rmoves.begin(), rmoves.end());

    Bishop b(color, pos, index);;
    bmoves = b.getPositions(t);
    moves.insert(moves.begin(), bmoves.begin(), bmoves.end());

    return moves;
} // {DONE}

Rook::Rook(char color, vec2<int> pos, int index) : ChessPiece(color, pos, index) {score = 5; abbreviation = 'R';}
std::vector<PieceMove> Rook::getPositions(Table* t) {
    std::vector<PieceMove> moves;
    int i;

    i = 1;
    while (i + pos.x < t->height) {
        Square* squarePiece = t->squares[pos.x + i][pos.y];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2<int>{pos.x + i, pos.y}, t->getSquareScore(squarePiece, color)});
        }
        if (squarePiece->piece) break;
        i++;
    } // UP
    i = -1;
    while (i + pos.x >= 0) {
        Square* squarePiece = t->squares[pos.x + i][pos.y];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2<int>{pos.x + i, pos.y}, t->getSquareScore(squarePiece, color) });
        }
        if (squarePiece->piece) break;

        i--;
    } // DOWN
    i = 1;
    while (pos.y + i < t->width) {
        Square* squarePiece = t->squares[pos.x][pos.y + i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2<int>{pos.x, pos.y + i}, t->getSquareScore(squarePiece, color) });
        }
        if (squarePiece->piece) break;
        i++;
    } // RIGHT
    i = -1;
    while (pos.y + i >= 0) {
        Square* squarePiece = t->squares[pos.x][pos.y + i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2<int>{pos.x, pos.y + i}, t->getSquareScore(squarePiece, color) });
        }
        if (squarePiece->piece) break;
        i--;
    } // LEFT
    return moves;
} // {DONE}

Bishop::Bishop(char color, vec2<int> pos, int index) : ChessPiece(color, pos, index) {score = 3; abbreviation = 'B';}
std::vector<PieceMove> Bishop::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    int i;

    i = 1;
    while (t->isInside(vec2<int>{ pos.x + i, pos.y - i })) {
        Square* squarePiece = t->squares[pos.x + i][1LL * pos.y - i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            if(squarePiece->piece && color != squarePiece->piece->color)
                moves.push_back(PieceMove{ vec2<int>{pos.x + i, pos.y - i}, t->getSquareScore(squarePiece, color)});
        }
        if (squarePiece->piece) {
            break;
        }
        i++;
    } // LEFT UP

    i = 1;
    while(t->isInside(vec2<int>{pos.x + i, pos.y + i})) {
        Square* squarePiece = t->squares[pos.x + i][- 1LL * i + pos.y];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{vec2<int>{pos.x + i, i + pos.y}, t->getSquareScore(squarePiece, color)});
        }
        if (squarePiece->piece) {
            break;
        }
        i++;
    } // RIGHT UP

    i = 1;
    while(t->isInside(vec2<int>{pos.x - i, pos.y - i})) {
        Square* squarePiece = t->squares[pos.x - i][pos.y - i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2<int>{pos.x - i, pos.y - i}, t->getSquareScore(squarePiece, color)});
        }
        if (squarePiece->piece) {
            break;
        }
        i++;
    } // LEFT DOWN


    i = 1;
    while(t->isInside(vec2<int>{pos.x - i, pos.y + i})) {
        Square* squarePiece = t->squares[pos.x - i][pos.y + i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{vec2<int>{pos.x - i, pos.y + i}, t->getSquareScore(squarePiece, color)});

        }
        if (squarePiece->piece) {
            break;
        }
        i++;
    } // RIGHT DOWN

    return moves;
} // {DONE}

Knight::Knight(char color, vec2<int> pos, int index) : ChessPiece(color, pos, index) {score = 3; abbreviation = 'N';}
std::vector<PieceMove> Knight::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    vec2<int> v{};

    // UP
    v = vec2<int>{ pos.x + 1, pos.y + 2 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2<int>{ pos.x - 1, pos.y + 2 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // DOWN
    v = vec2<int>{ pos.x + 1, pos.y - 2 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2<int>{ pos.x - 1, pos.y - 2 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // RIGHT
    v = vec2<int>{ pos.x + 2, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2<int>{ pos.x + 2, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // LEFT
    v = vec2<int>{ pos.x - 2, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2<int>{ pos.x - 2, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    return moves;
} // {DONE}

Pawn::Pawn(char color, vec2<int> pos, int index) : ChessPiece(color, pos, index) {score = 1; abbreviation = 'P';}
std::vector<PieceMove> Pawn::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    int direction = color == 'w' ? 1 : -1;

    // 2 UP
    if (!wasMoved && t->isInside(vec2<int>{pos.x + 2 * direction, pos.y}) && !t->squares[pos.x + 2 * direction][pos.y]->piece)
        moves.push_back(PieceMove{vec2<int>{pos.x + 2 * direction, pos.y}});

    // 1 UP
    if (t->isInside(vec2<int>{pos.x + 1 * direction, pos.y}) && !t->squares[pos.x + 1 * direction][pos.y]->piece)
        moves.push_back(PieceMove{ vec2<int>{pos.x + 1 * direction, pos.y} });

    // LEFT
    if (t->isInside(vec2<int>{pos.x + 1 * direction , pos.y - 1 * direction})
            && t->squares[pos.x + 1 * direction][pos.y - 1 * direction]->piece && t->squares[pos.x + 1 * direction][pos.y - 1 * direction]->piece->color != color)
            moves.push_back(PieceMove{ vec2<int>{pos.x + 1 * direction, pos.y - 1 * direction}, t->getSquareScore(t->squares[pos.x + 1 * direction][pos.y - 1 * direction], color)});

        // RIGHT
        if (t->isInside(vec2<int>{pos.x + 1 * direction,  pos.y + 1 * direction})
            && t->squares[pos.x + 1 * direction][pos.y + 1 * direction]->piece && t->squares[pos.x + 1 * direction][pos.y + 1 * direction]->piece->color != color)
            moves.push_back(PieceMove{ vec2<int>{pos.x + 1 * direction, pos.y + 1 * direction}, t->getSquareScore(t->squares[pos.x + 1 * direction][pos.y + 1 * direction], color)});
        return moves;
    } // {DONE}

// Functii Ovidiu
Queen* Pawn::promotePawn(Table* table) {
    return new Queen(color, pos, table->pieces[color == 'w' ? 0 : 1].size());
}
