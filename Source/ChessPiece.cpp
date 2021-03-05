#include "ChessPiece.h"
#include "Table.h"

#define CHECKMATE 2
#define CHECK 1
#define NOCHECK 0

ChessPiece::ChessPiece(char color, vec2 pos) {
    this->color = color; this->pos = pos; this->score = 0;
}

ChessPiece::~ChessPiece() = default;

// ane
int King::isCheck(Table* t, ChessPiece* piece) {
    // verific daca o piesa pune in sah regele
    char color;
    int aux = 0;
    King* foundK;

    if (piece->color == 'b')
        color = 'w';
    else color = 'b'; // aflam culoarea regelui care este in pericol

    if (color == 'b') {  // daca piesa este alba, vom incepe cautarea de jos in sus
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (t->squares[i][j]->piece->score == 0) {
                    foundK = (King*)t->squares[i][j]->piece; // retinem regele ca sa ii cunoastem pozitia
                    aux = 1;
                    break;
                }
            }
            if (aux = 1) break;
        }
    }
    else {
        for (int i = 7; i > 0; i--) { // pornim cautarea de sus in jos ca sa aflam regele
            for (int j = 0; j < 8; j++) {
                if (t->squares[i][j]->piece->score == 0) {
                    foundK = (King*)t->squares[i][j]->piece; // retinem regele ca sa ii cunoastem pozitia
                    aux = 1;
                    break;
                }
            }
            if (aux = 1) break;
        }
    }

    //pozitia regelui
    vec2 kPos = vec2{ foundK->pos.x, foundK->pos.y };
    if (piece->score == 1) { // pion
        if (piece->color == 'w') {
            if (piece->pos.x + 1 == foundK->pos.x && (piece->pos.y - 1 == foundK->pos.y ||
                piece->pos.y + 1 == foundK->pos.y)) {
                foundK->checks++;
                //t->squares[foundK->pos.x][foundK->pos.y] = foundK; ??????
                return CHECK; // pionul pune in sah regele negru
            }
        }
        else {
            if (piece->pos.x - 1 == foundK->pos.x && (piece->pos.y - 1 == foundK->pos.y ||
                piece->pos.y + 1 == foundK->pos.y)) {
                foundK->checks++;
                //t->squares[foundK->pos.x][foundK->pos.y] = foundK; ??????
                return CHECK; // pionul pune in sah regele alb
            }
        }
    }
    else if (piece->score == 2) { // cal, am schimbat scorul, nu stiu daca e in regula
         // DYNAMIC CAST    dynamic_cast<Knight*>(c) ---> de adaugat asta SI DE schimbat 2 in 3
        if ((piece->pos.x + 1 == foundK->pos.x && piece->pos.y + 2 == foundK->pos.y) || (piece->pos.x + 1 == foundK->pos.x && piece->pos.y - 2 == foundK->pos.y)
            || (piece->pos.x + 2 == foundK->pos.x && piece->pos.y + 1) || (piece->pos.x - 1 == foundK->pos.x && piece->pos.y + 2 == foundK->pos.y)
            || (piece->pos.x - 1 == foundK->pos.x && piece->pos.y - 2) || (piece->pos.x + 2 == foundK->pos.x && piece->pos.y - 1 == foundK->pos.y)
            || (piece->pos.x - 2 == foundK->pos.x && piece->pos.y + 1) || (piece->pos.x - 2 == foundK->pos.x && piece->pos.y - 1 == foundK->pos.y)) {
            foundK->checks++;
            return CHECK;
        }
    }
    else if (piece->score == 3 || piece->score == 9) { // nebun sau regina
     // -- de facut !!!!




    }
    else if (piece->score == 5 || piece->score == 9) { // tura sau regina
        int min;
        int dist = 0;
        if (piece->pos.x == foundK->pos.x) {
            // verificam daca pe axa y exista celule libere de la o piesa la alta
            if (piece->pos.y < foundK->pos.y) {
                for (int i = piece->pos.y; i < foundK->pos.y; i++) {
                    dist = dist + 1; // calculam distanta sa verificam daca ajunge pana acolo
                    if (t->squares[i][piece->pos.x] != 0) break;
                }
                if (dist = foundK->pos.y - piece->pos.y) return CHECK;
            }
            else {
                for (int i = foundK->pos.y; i < piece->pos.y; i++) {
                    dist = dist + 1; // calculam distanta sa verificam daca ajunge pana acolo
                    if (t->squares[i][foundK->pos.x] != 0) break;
                }
                if (dist = piece->pos.y - foundK->pos.y) return CHECK;
            }
        }
        else if (piece->pos.y == foundK->pos.y) {
            // verificam daca pe axa x exista celule libere de la o piesa la alta
            if (piece->pos.x < foundK->pos.x) {
                for (int i = piece->pos.x; i < foundK->pos.x; i++) {
                    dist = dist + 1; // calculam distanta sa verificam daca ajunge pana acolo
                    if (t->squares[i][piece->pos.y] != 0) break;
                }
                if (dist = foundK->pos.x - piece->pos.x) return CHECK;
            }
            else {
                for (int i = foundK->pos.x; i < piece->pos.x; i++) {
                    dist = dist + 1; // calculam distanta sa verificam daca ajunge pana acolo
                    if (t->squares[i][foundK->pos.y] != 0) break;
                }
                if (dist = piece->pos.x - foundK->pos.x) return CHECK;
            }

        }

    }
    return NOCHECK;

}

King::King(char color, vec2 pos) : ChessPiece(color, pos) { score = 0; }
std::vector<PieceMove> King::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    vec2 v{};

    v = vec2{ pos.x + 1, pos.y - 1 };
    if (t->isInside(v)) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x + 1, pos.y };
    if (t->isInside(v)) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x + 1, pos.y + 1 };
    if (t->isInside(v)) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x, pos.y + 1 };
    if (t->isInside(v)) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x, pos.y - 1 };
    if (t->isInside(v)) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x - 1, pos.y - 1 };
    if (t->isInside(v)) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x - 1, pos.y };
    if (t->isInside(v)) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    v = vec2{ pos.x - 1, pos.y + 1 };
    if (t->isInside(v)) {
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    }
    return moves;
}

Queen::Queen(char color, vec2 pos) : ChessPiece(color, pos) { score = 9; }
std::vector<PieceMove> Queen::getPositions(Table* t) {
    std::vector<PieceMove> moves, kmoves, bmoves;

    King k(color, pos);
    kmoves = k.getPositions(t);
    moves.insert(moves.begin(), kmoves.begin(), kmoves.end());

    Bishop b(color, pos);
    bmoves = b.getPositions(t);
    moves.insert(moves.begin(), bmoves.begin(), bmoves.end());

    return moves;
}

Rook::Rook(char color, vec2 pos) : ChessPiece(color, pos) { score = 5; }
std::vector<PieceMove> Rook::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    int i = 1;
    while (i + pos.y < t->height) {
        Square* squarePiece = t->squares[pos.x][i + pos.y];
        if (squarePiece) {
            moves.push_back(PieceMove{ vec2{pos.x, i + pos.y}, t->getSquareScore(squarePiece, color) });
            break;
        }
        moves.push_back(PieceMove{ vec2{pos.x, i + pos.y} });
        i++;
    } // UP

    i = -1;
    while (i + pos.y >= 0) {
        Square* squarePiece = t->squares[pos.x][i + pos.y];
        if (squarePiece) {
            moves.push_back(PieceMove{ vec2{pos.x, i + pos.y}, t->getSquareScore(squarePiece, color) });
            break;
        }
        moves.push_back(PieceMove{ vec2{pos.x, i + pos.y} });
        i--;
    } // DOWN

    i = 1;
    while (i + pos.x != t->width) {
        Square* squarePiece = t->squares[pos.x][i + pos.y];
        if (squarePiece) {
            moves.push_back(PieceMove{ vec2{pos.x, i + pos.y}, t->getSquareScore(squarePiece, color) });
            break;
        }
        moves.push_back(PieceMove{ vec2{pos.x, i + pos.y} });
        i++;
    } // RIGHT

    i = -1;
    while (i + pos.x >= 0) {
        Square* squarePiece = t->squares[pos.x][i + pos.y];
        if (squarePiece) {
            moves.push_back(PieceMove{ vec2{pos.x, i + pos.y}, t->getSquareScore(squarePiece, color) });
            break;
        }
        moves.push_back(PieceMove{ vec2{pos.x, i + pos.y} });
        i--;
    } // LEFT

    return moves;
}

Bishop::Bishop(char color, vec2 pos) : ChessPiece(color, pos) { score = 3; }
std::vector<PieceMove> Bishop::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    int i;

    i = 1;
    while (t->isInside(vec2{ pos.x - i, pos.y + i })) {
        Square* squarePiece = t->squares[pos.x - i][i + pos.y];
        if (squarePiece) {
            moves.push_back(PieceMove{ vec2{pos.x - i, i + pos.y}, t->getSquareScore(squarePiece, color) });
            break;
        }
        moves.push_back(PieceMove{ vec2{pos.x - i, i + pos.y} });
        i++;
    } // LEFT UP

    //i = 1;
    //while(t->isInside(vec2{pos.x - i, pos.y - i})) {
    //    Square* squarePiece = t->squares[pos.x - i][- i + pos.y];
    //    if (squarePiece) {
    //        moves.push_back(PieceMove{vec2{pos.x - i, - i + pos.y}, t->getSquareScore(squarePiece, color)});
    //        break;
    //    }
    //    moves.push_back(PieceMove{vec2{pos.x - i, i + pos.y}});
    //    i++;
    //} // LEFT DOWN
    //
    //i = 1;
    //while(t->isInside(vec2{pos.x + i, pos.y + i})) {
    //    Square* squarePiece = t->squares[pos.x + i][i + pos.y];
    //    if (squarePiece) {
    //        moves.push_back(PieceMove{vec2{pos.x + i, i + pos.y}, t->getSquareScore(squarePiece, color)});
    //        break;
    //    }
    //    moves.push_back(PieceMove{vec2{pos.x + i, pos.y + i}});
    //    i++;
    //} // RIGHT UP
//
    //i = 1;
    //while(t->isInside(vec2{pos.x + i, pos.y - i})) {
    //    cout << pos.x + i << " vec " << pos.y - i << "\n";
    //    Square* squarePiece = t->squares[pos.x + i][pos.y - i];
    //    if (squarePiece) {
    //        moves.push_back(PieceMove{vec2{pos.x + i, pos.y - i}, t->getSquareScore(squarePiece, color)});
    //        break;
    //    }
    //    moves.push_back(PieceMove{vec2{pos.x + i, pos.y - i}});
    //    i++;
    //} // RIGHT DOWN

    return moves;
}

Knight::Knight(char color, vec2 pos) : ChessPiece(color, pos) { score = 3; }
std::vector<PieceMove> Knight::getPositions(Table* t) {
    std::vector<PieceMove> moves;

    vec2 v;

    // UP
    v = vec2{ pos.x + 1, pos.y + 2 };
    if (t->isInside(v))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2{ pos.x - 1, pos.y + 2 };
    if (t->isInside(v))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // DOWN
    v = vec2{ pos.x + 1, pos.y - 2 };
    if (t->isInside(v))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2{ pos.x - 1, pos.y - 2 };
    if (t->isInside(v))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // RIGHT
    v = vec2{ pos.x + 2, pos.y + 1 };
    if (t->isInside(v))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2{ pos.x + 2, pos.y - 1 };
    if (t->isInside(v))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    // LEFT
    v = vec2{ pos.x - 2, pos.y + 1 };
    if (t->isInside(v))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });
    v = vec2{ pos.x - 2, pos.y - 1 };
    if (t->isInside(v))
        moves.push_back(PieceMove{ v, t->getSquareScore(t->squares[v.x][v.y], color) });

    return moves;
}

Pawn::Pawn(char color, vec2 pos) : ChessPiece(color, pos) { score = 1; }
std::vector<PieceMove> Pawn::getPositions(Table* t) {
    std::vector<PieceMove> moves;
    if (wasMoved && t->isInside(vec2{ pos.x, pos.y + 2 }))
        moves.push_back(PieceMove{ vec2{pos.x, pos.y + 2} });
    if (t->isInside(vec2{ pos.x, pos.y + 1 }))
        moves.push_back(PieceMove{ vec2{pos.x, pos.y + 1} });
    if (t->isInside(vec2{ pos.x - 1, pos.y + 1 }) && t->squares[pos.x - 1][pos.y + 1]->piece)
        moves.push_back(PieceMove{ vec2{pos.x - 1, pos.y + 1}, t->squares[pos.x - 1][pos.y + 1]->piece->score });
    if (t->isInside(vec2{ pos.x + 1, pos.y + 1 }) && t->squares[pos.x + 1][pos.y + 1]->piece)
        moves.push_back(PieceMove{ vec2{pos.x + 1, pos.y + 1}, t->squares[pos.x + 1][pos.y + 1]->piece->score });
    return moves;
}
