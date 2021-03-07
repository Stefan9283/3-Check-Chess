#include "ChessPiece.h"
#include "Table.h"

#define NOCHECK 0
#define CHECK 1
#define CHECKMATE 2

ChessPiece::ChessPiece(char color, vec2 pos, int index) {
    assert((color == 'w' || color == 'b') && "Chess Piece color should be either (b)lack or (w)hite");
    this->color = color; this->pos = pos; this->score = 0; this->index = index; this->abbreviation = '#';
}
ChessPiece::~ChessPiece() = default;

// ane
int King::isCheck(Table* t, ChessPiece* piece) {
    // verific daca o piesa pune in sah regele
    char color;
    int aux = 0;

    if (piece->color == 'b')
        color = 'w';
    else color = 'b'; // aflam culoarea regelui care este in pericol

    //pozitia regelui
    vec2 kPos = this->pos;
    if (dynamic_cast<Pawn*>(piece)) { // pion
        if (piece->color == 'w') {
            if (piece->pos.x + 1 == kPos.x && piece->pos.y + 1 == kPos.y) {
                this->checks++;
                return CHECK; // pionul pune in sah regele negru
            }
        }
        else {
            if (piece->pos.x - 1 == kPos.x && piece->pos.y - 1 == kPos.y) {
                this->checks++;
                return CHECK; // pionul pune in sah regele alb
            }
        }
    }
    else if (dynamic_cast<Knight*>(piece)) { // cal
        if ((piece->pos.x + 1 == kPos.x && piece->pos.y + 2 == kPos.y) || (piece->pos.x + 1 == kPos.x && piece->pos.y - 2 == kPos.y)
            || (piece->pos.x + 2 == kPos.x && piece->pos.y + 1) || (piece->pos.x - 1 == kPos.x && piece->pos.y + 2 == kPos.y)
            || (piece->pos.x - 1 == kPos.x && piece->pos.y - 2) || (piece->pos.x + 2 == kPos.x && piece->pos.y - 1 == kPos.y)
            || (piece->pos.x - 2 == kPos.x && piece->pos.y + 1) || (piece->pos.x - 2 == kPos.x && piece->pos.y - 1 == kPos.y)) {
            this->checks++;
            return CHECK;
        }
    }
    else if (dynamic_cast<Bishop*>(piece) || dynamic_cast<Queen*>(piece)) { // nebun sau regina
        int dist = 0;
        vec2 kDifPos; //la nebun x1-x2 = |y1-y2|
        kDifPos.x = kPos.x - piece->pos.x;
        kDifPos.y = kPos.y - piece->pos.y;
        if (kDifPos.x == kDifPos.y || kDifPos.x == -kDifPos.y) {
            //inseamna ca regele si nebunul/regina se afla pe aceeasi diagonala
            //verificam daca exista piese intermediare intre ele
            //LEFT UP x > 0,  y < 0 -  se afla regele in stanga sus fata de nebun
            if (kDifPos.x > 0 && kDifPos.y < 0) {
                for (int i = 1; i < kDifPos.x; i++) {
                    if (t->squares[1LL *piece->pos.x + i][1LL * piece->pos.y - i] != 0) break;
                    dist = dist + 1;// verificam daca ajunge pana la rege
                }
                if (dist = kDifPos.x) {
                    this->checks++;
                    return CHECK;
                }
            }
            // RIGHT up x>0, y>0
            if (kDifPos.x > 0 && kDifPos.y < 0) {
                for (int i = 1; i < kDifPos.x; i++) {
                    if (t->squares[1LL * piece->pos.x + i][1LL * piece->pos.y + i] != 0) break;
                    dist = dist + 1;// verificam daca ajunge pana la rege
                }
                if (dist = kDifPos.x) {
                    this->checks++;
                    return CHECK;
                }
            }
            //LEFT DOWN x<0, y<0
            if (kDifPos.x < 0 && kDifPos.y < 0) {
                for (int i = 1; i < -kDifPos.x; i++) {
                    if (t->squares[1LL * piece->pos.x - i][1LL * piece->pos.y - i] != 0) break;
                    dist = dist + 1;// verificam daca ajunge pana la rege
                }
                if (dist = -kDifPos.x) {
                    this->checks++;
                    return CHECK;
                }
            }
            //RIGHT DOWN x<0, y>0
            if (kDifPos.x < 0 && kDifPos.y > 0) {
                for (int i = 1; i < -kDifPos.y; i++) {
                    if (t->squares[1LL * piece->pos.x - i][1LL * piece->pos.y + i] != 0) break;
                    dist = dist + 1;// verificam daca ajunge pana la rege
                }
                if (dist = kDifPos.y) {
                    this->checks++;
                    return CHECK;
                }
            }
        }
    }
    else if (dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece)) { // tura sau regina
        int min;
        int dist = 0;
        if (piece->pos.x == kPos.x) {
            // verificam daca pe axa y exista celule libere de la o piesa la alta
            if (piece->pos.y < kPos.y) {
                for (int i = piece->pos.y; i < kPos.y; i++) {
                    if (t->squares[i][piece->pos.x] != 0) break;
                    dist = dist + 1; // calculam distanta sa verificam daca ajunge pana acolo

                }
                if (dist = kPos.y - piece->pos.y) {
                    this->checks++;
                    return CHECK;
                }
            }
            else {
                for (int i = kPos.y; i < piece->pos.y; i++) {
                    dist = dist + 1; // calculam distanta sa verificam daca ajunge pana acolo
                    if (t->squares[i][kPos.x] != 0) break;
                }
                if (dist = piece->pos.y - kPos.y) {
                    this->checks++;
                    return CHECK;
                }
            }
        }
        else if (piece->pos.y == kPos.y) {
            // verificam daca pe axa x exista celule libere de la o piesa la alta
            if (piece->pos.x < kPos.x) {
                for (int i = piece->pos.x; i < kPos.x; i++) {
                    dist = dist + 1; // calculam distanta sa verificam daca ajunge pana acolo
                    if (t->squares[i][piece->pos.y] != 0) break;
                }
                if (dist = kPos.x - piece->pos.x) {
                    this->checks++;
                    return CHECK;
                }
            }
            else {
                for (int i = kPos.x; i < piece->pos.x; i++) {
                    dist = dist + 1; // calculam distanta sa verificam daca ajunge pana acolo
                    if (t->squares[i][kPos.y] != 0) break;
                }
                if (dist = piece->pos.x - kPos.x) {
                    this->checks++;
                    return CHECK;
                }
            }

        }

    }
    return NOCHECK;
}

King::King(char color, vec2 pos, int index) : ChessPiece(color, pos, index) { score = 0; abbreviation = 'K';  }
std::vector<PieceMove> King::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    vec2 v{};

    v = vec2{ pos.x + 1, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x + 1, pos.y };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x + 1, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x - 1, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x - 1, pos.y };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x - 1, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y])) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    return moves;
} // {DONE}

Queen::Queen(char color, vec2 pos, int index) : ChessPiece(color, pos, index) { score = 9; abbreviation = 'Q'; }
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

Rook::Rook(char color, vec2 pos, int index) : ChessPiece(color, pos, index) { score = 5; abbreviation = 'R'; }
std::vector<PieceMove> Rook::getPositions(Table* t) {
    std::vector<PieceMove> moves;
    int i;

    i = 1;
    while (i + pos.x < t->height) {
        Square* squarePiece = t->squares[pos.x + i][1LL * i + pos.y];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2{pos.x + i, pos.y}, t->getSquareScore(squarePiece, color)});
            if (squarePiece->piece) break;
        } else break;
        i++;
    } // UP

    i = -1;
    while (i + pos.x >= 0) {
        Square* squarePiece = t->squares[pos.x + i][pos.y];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2{pos.x + i, pos.y}, t->getSquareScore(squarePiece, color) });
            if (squarePiece->piece) break;
        } else break;
        i--;
    } // DOWN

    i = 1;
    while (pos.y + i < t->width) {
        Square* squarePiece = t->squares[pos.x][pos.y + i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2{pos.x, pos.y + i}, t->getSquareScore(squarePiece, color) });
            if (squarePiece->piece) break;
        } else break;
        i++;
    } // RIGHT

    i = -1;
    while (pos.y + i >= 0) {
        Square* squarePiece = t->squares[pos.x][pos.y + i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2{pos.x, pos.y + i}, t->getSquareScore(squarePiece, color) });
            if (squarePiece->piece) break;
        } else break;
        i--;
    } // LEFT

    return moves;
} // {DONE}

Bishop::Bishop(char color, vec2 pos, int index) : ChessPiece(color, pos, index) { score = 3; abbreviation = 'B'; }

std::vector<PieceMove> Bishop::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    int i;

    i = 1;
    while (t->isInside(vec2{ pos.x + i, pos.y - i })) {
        Square* squarePiece = t->squares[pos.x + i][1LL * pos.y - i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2{pos.x + i, pos.y - i}, t->getSquareScore(squarePiece, color)});
            if (squarePiece->piece) break;
        }
        i++;
    } // LEFT UP

    i = 1;
    while(t->isInside(vec2{pos.x - i, pos.y - i})) {
        Square* squarePiece = t->squares[pos.x - i][1LL * pos.y - i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{ vec2{pos.x - i, pos.y - i}, t->getSquareScore(squarePiece, color)});
            if (squarePiece->piece) break;
        }
        i++;
    } // LEFT DOWN

    i = 1;
    while(t->isInside(vec2{pos.x + i, pos.y + i})) {
        Square* squarePiece = t->squares[pos.x + i][1LL * i + pos.y];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{vec2{pos.x + i, i + pos.y}, t->getSquareScore(squarePiece, color)});
            if (squarePiece->piece) break;
        }
        i++;
    } // RIGHT UP

    i = 1;
    while(t->isInside(vec2{pos.x - i, pos.y + i})) {
        Square* squarePiece = t->squares[pos.x - i][1LL * pos.y + i];
        if (t->canIPlaceItHere(this, squarePiece)) {
            moves.push_back(PieceMove{vec2{pos.x - i, pos.y + i}, t->getSquareScore(squarePiece, color)});
            if (squarePiece->piece) break;
        }
        i++;
    } // RIGHT DOWN

    return moves;
} // {DONE}

Knight::Knight(char color, vec2 pos, int index) : ChessPiece(color, pos, index) { score = 3; abbreviation = 'N'; }
std::vector<PieceMove> Knight::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    vec2 v;

    // UP
    v = vec2{ pos.x + 1, pos.y + 2 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2{ pos.x - 1, pos.y + 2 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // DOWN
    v = vec2{ pos.x + 1, pos.y - 2 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2{ pos.x - 1, pos.y - 2 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // RIGHT
    v = vec2{ pos.x + 2, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2{ pos.x + 2, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // LEFT
    v = vec2{ pos.x - 2, pos.y + 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2{ pos.x - 2, pos.y - 1 };
    if (t->isInside(v) && t->canIPlaceItHere(this, t->squares[v.x][v.y]))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    return moves;
} // {DONE}

Pawn::Pawn(char color, vec2 pos, int index) : ChessPiece(color, pos, index) { score = 1; abbreviation = 'P';}
std::vector<PieceMove> Pawn::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    int direction = color == 'w' ? 1 : -1;

    // 2 UP
    if (!wasMoved && t->isInside(vec2{pos.x + 2 * direction, pos.y}) && !t->squares[pos.x + 2 * direction][pos.y]->piece)
        moves.push_back(PieceMove{vec2{pos.x + 2 * direction, pos.y}});

    // 1 UP
    if (t->isInside(vec2{pos.x + 1 * direction, pos.y}) && !t->squares[pos.x + 1 * direction][pos.y]->piece)
        moves.push_back(PieceMove{ vec2{pos.x + 1 * direction, pos.y} });

    // LEFT
    if (t->isInside(vec2{pos.x + 1 * direction , pos.y - 1 * direction})
            && t->squares[pos.x + 1 * direction][pos.y - 1 * direction]->piece && t->squares[pos.x + 1 * direction][pos.y - 1 * direction]->piece->color != color)
        moves.push_back(PieceMove{ vec2{pos.x + 1 * direction, pos.y - 1 * direction}, t->getSquareScore(t->squares[pos.x + 1 * direction][pos.y - 1 * direction], color)});

    // RIGHT
    if (t->isInside(vec2{pos.x + 1 * direction,  pos.y + 1 * direction})
        && t->squares[pos.x + 1 * direction][pos.y + 1 * direction]->piece && t->squares[pos.x + 1 * direction][pos.y + 1 * direction]->piece->color != color)
        moves.push_back(PieceMove{ vec2{pos.x + 1 * direction, pos.y + 1 * direction}, t->getSquareScore(t->squares[pos.x + 1 * direction][pos.y + 1 * direction], color)});
    return moves;
}

// Functii Ovidiu

// Verrify if the king is in check at a specified position
bool King::isInCheckAt(Table* table, vec2 pos) {
    int line = color == 'w' ? 1 : 0;

    // Check from pawn
    for (int j = 0; j < table->width; j++)
        if (table->pieces[line][j])
            if (((color == 'w' && table->pieces[line][j]->pos.x == pos.x + 1) ||
                (color == 'b' && table->pieces[line][j]->pos.x == pos.x - 1)) &&
                abs(table->pieces[line][j]->pos.y - pos.y) == 1)
                    return true;

    // Check from rook
    if (table->pieces[line][8])
        if (table->pieces[line][8]->pos.x == pos.x || table->pieces[line][8]->pos.y == pos.y)
            if (table->hasNoPiecesBetween_line(table->pieces[line][8]->pos, pos))
                return true;

    if (table->pieces[line][9])
        if (table->pieces[line][9]->pos.x == pos.x || table->pieces[line][9]->pos.y == pos.y)
            if (table->hasNoPiecesBetween_line(table->pieces[line][9]->pos, pos))
                return true;

    // Check from knight
    if (table->pieces[line][10] &&
        (abs(table->pieces[line][10]->pos.x - pos.x) == 2 && abs(table->pieces[line][10]->pos.y - pos.y) == 1) ||
        (abs(table->pieces[line][10]->pos.y - pos.y) == 2 && abs(table->pieces[line][10]->pos.x - pos.x) == 1))
            return true;

    if (table->pieces[line][11] &&
        (abs(table->pieces[line][11]->pos.x - pos.x) == 2 && abs(table->pieces[line][11]->pos.y - pos.y) == 1) ||
        (abs(table->pieces[line][11]->pos.y - pos.y) == 2 && abs(table->pieces[line][11]->pos.x - pos.x) == 1))
            return true;

    // Check from bishop
    if (table->pieces[line][12])
        if (abs(table->pieces[line][12]->pos.x - pos.x) == abs(table->pieces[line][12]->pos.y - pos.y))
            if (table->hasNoPiecesBetween_diagonal(table->pieces[line][12]->pos, pos))
                return true;

    if (table->pieces[line][13])
        if (abs(table->pieces[line][13]->pos.x - pos.x) == abs(table->pieces[line][13]->pos.y - pos.y))
            if (table->hasNoPiecesBetween_diagonal(table->pieces[line][13]->pos, pos))
                return true;

    // Check from queen
    if (table->pieces[line][14]) {
        if (table->pieces[line][14]->pos.x == pos.x || table->pieces[line][14]->pos.y == pos.y)
            if (table->hasNoPiecesBetween_line(table->pieces[line][14]->pos, pos))
                return true;

        if (abs(table->pieces[line][14]->pos.x - pos.x) == abs(table->pieces[line][14]->pos.y - pos.y))
            if (table->hasNoPiecesBetween_diagonal(table->pieces[line][14]->pos, pos))
                return true;
    }

    return false;
}
