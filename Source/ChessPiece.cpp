#include "ChessPiece.h"

// WIP

ChessPiece::ChessPiece(char color, vec2 pos) {
    this->color = color;
    this->position = pos;
}
ChessPiece::~ChessPiece() = default;

King::King(char color, vec2 pos) : ChessPiece(color, pos) { score = 0; }
std::vector<PieceMove> King::getPositions(Table *t) {
    std::vector<PieceMove> moves;

    vec2 v{};

    v = vec2{position.x + 1, position.y - 1};
    if (t->isInside(v)) {
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    }
    v = vec2{position.x + 1, position.y};
    if (t->isInside(v)) {
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    }
    v = vec2{position.x + 1, position.y + 1};
    if (t->isInside(v)) {
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    }
    v = vec2{position.x, position.y + 1};
    if (t->isInside(v)) {
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    }
    v = vec2{position.x, position.y - 1};
    if (t->isInside(v)) {
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    }
    v = vec2{position.x - 1, position.y - 1};
    if (t->isInside(v)) {
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    }
    v = vec2{position.x - 1, position.y};
    if (t->isInside(v)) {
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    }
    v = vec2{position.x - 1, position.y + 1};
    if (t->isInside(v)) {
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    }
    return moves;
}

Queen::Queen(char color, vec2 pos) : ChessPiece(color, pos) { score = 9; }
std::vector<PieceMove> Queen::getPositions(Table *t) {
    std::vector<PieceMove> moves, kmoves, bmoves;

    King k(color, position);
    kmoves = k.getPositions(t);
    moves.insert(moves.begin(), kmoves.begin(), kmoves.end());

    Bishop b(color, position);
    bmoves = b.getPositions(t);
    moves.insert(moves.begin(), bmoves.begin(), bmoves.end());

    return moves;
}

Rook::Rook(char color, vec2 pos) : ChessPiece(color, pos) { score = 5; }
std::vector<PieceMove> Rook::getPositions(Table *t) {
    std::vector<PieceMove> moves;

    int i = 1;
    while(i + position.y < t->height) {
        Square* squarePiece = t->squares[position.x][i + position.y];
        if (squarePiece) {
            moves.push_back(PieceMove{vec2{position.x, i + position.y}, t->getSquareScore(squarePiece, color)});
            break;
        }
        moves.push_back(PieceMove{vec2{position.x, i + position.y}});
        i++;
    } // UP

    i = -1;
    while(i + position.y >= 0) {
        Square* squarePiece = t->squares[position.x][i + position.y];
        if (squarePiece) {
            moves.push_back(PieceMove{vec2{position.x, i + position.y}, t->getSquareScore(squarePiece, color)});
            break;
        }
        moves.push_back(PieceMove{vec2{position.x, i + position.y}});
        i--;
    } // DOWN

    i = 1;
    while(i + position.x != t->width) {
        Square* squarePiece = t->squares[position.x][i + position.y];
        if (squarePiece) {
            moves.push_back(PieceMove{vec2{position.x, i + position.y}, t->getSquareScore(squarePiece, color)});
            break;
        }
        moves.push_back(PieceMove{vec2{position.x, i + position.y}});
        i++;
    } // RIGHT

    i = -1;
    while(i + position.x >= 0) {
        Square* squarePiece = t->squares[position.x][i + position.y];
        if (squarePiece) {
            moves.push_back(PieceMove{vec2{position.x, i + position.y}, t->getSquareScore(squarePiece, color)});
            break;
        }
        moves.push_back(PieceMove{vec2{position.x, i + position.y}});
        i--;
    } // LEFT

    return moves;
}

Bishop::Bishop(char color, vec2 pos) : ChessPiece(color, pos) { score = 3; }
std::vector<PieceMove> Bishop::getPositions(Table *t) {
    std::vector<PieceMove> moves;

    int i;

    i = 1;
    while(t->isInside(vec2{position.x - i, position.y + i})) {
        Square* squarePiece = t->squares[position.x - i][i + position.y];
        if (squarePiece) {
            moves.push_back(PieceMove{vec2{position.x - i, i + position.y}, t->getSquareScore(squarePiece, color)});
            break;
        }
        moves.push_back(PieceMove{vec2{position.x - i, i + position.y}});
        i++;
    } // LEFT UP

    //i = 1;
    //while(t->isInside(vec2{position.x - i, position.y - i})) {
    //    Square* squarePiece = t->squares[position.x - i][- i + position.y];
    //    if (squarePiece) {
    //        moves.push_back(PieceMove{vec2{position.x - i, - i + position.y}, t->getSquareScore(squarePiece, color)});
    //        break;
    //    }
    //    moves.push_back(PieceMove{vec2{position.x - i, i + position.y}});
    //    i++;
    //} // LEFT DOWN
    //
    //i = 1;
    //while(t->isInside(vec2{position.x + i, position.y + i})) {
    //    Square* squarePiece = t->squares[position.x + i][i + position.y];
    //    if (squarePiece) {
    //        moves.push_back(PieceMove{vec2{position.x + i, i + position.y}, t->getSquareScore(squarePiece, color)});
    //        break;
    //    }
    //    moves.push_back(PieceMove{vec2{position.x + i, position.y + i}});
    //    i++;
    //} // RIGHT UP
//
    //i = 1;
    //while(t->isInside(vec2{position.x + i, position.y - i})) {
    //    cout << position.x + i << " vec " << position.y - i << "\n";
    //    Square* squarePiece = t->squares[position.x + i][position.y - i];
    //    if (squarePiece) {
    //        moves.push_back(PieceMove{vec2{position.x + i, position.y - i}, t->getSquareScore(squarePiece, color)});
    //        break;
    //    }
    //    moves.push_back(PieceMove{vec2{position.x + i, position.y - i}});
    //    i++;
    //} // RIGHT DOWN

    return moves;
}

Knight::Knight(char color, vec2 pos) : ChessPiece(color, pos) { score = 3; }
std::vector<PieceMove> Knight::getPositions(Table *t) {
    std::vector<PieceMove> moves;

    vec2 v;

    // UP
    v = vec2{position.x + 1, position.y + 2};
    if (t->isInside(v))
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    v = vec2{position.x - 1, position.y + 2};
    if (t->isInside(v))
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});

    // DOWN
    v = vec2{position.x + 1, position.y - 2};
    if (t->isInside(v))
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    v = vec2{position.x - 1, position.y - 2};
    if (t->isInside(v))
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});

    // RIGHT
    v = vec2{position.x + 2, position.y + 1};
    if (t->isInside(v))
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    v = vec2{position.x + 2, position.y - 1};
    if (t->isInside(v))
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});

    // LEFT
    v = vec2{position.x - 2, position.y + 1};
    if (t->isInside(v))
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});
    v = vec2{position.x - 2, position.y - 1};
    if (t->isInside(v))
        moves.push_back(PieceMove{v, t->getSquareScore(t->squares[v.x][v.y], color)});

    return moves;
}

Pawn::Pawn(char color, vec2 pos) : ChessPiece(color, pos) { score = 1; }
std::vector<PieceMove> Pawn::getPositions(Table *t) {
    std::vector<PieceMove> moves;
    if (moved && t->isInside(vec2{position.x, position.y + 2}))
        moves.push_back(PieceMove{vec2{position.x, position.y + 2}});
    if (t->isInside(vec2{position.x, position.y + 1}))
        moves.push_back(PieceMove{vec2{position.x, position.y + 1}});
    if (t->isInside(vec2{position.x - 1, position.y + 1}) && t->squares[position.x - 1][position.y + 1]->cp)
        moves.push_back(PieceMove{vec2{position.x - 1, position.y + 1}, t->squares[position.x - 1][position.y + 1]->cp->score});
    if (t->isInside(vec2{position.x + 1, position.y + 1}) && t->squares[position.x + 1][position.y + 1]->cp)
        moves.push_back(PieceMove{vec2{position.x + 1, position.y + 1}, t->squares[position.x + 1][position.y + 1]->cp->score});
    return moves;
}
