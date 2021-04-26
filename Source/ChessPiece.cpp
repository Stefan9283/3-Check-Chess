#include "ChessPiece.h"
#include "Table.h"

ChessPiece::ChessPiece(char color, vec2<int> pos, int index) {
    assert((color == 'w' || color == 'b') && "Chess Piece color should be either (b)lack or (w)hite");
    this->color = color; this->pos = pos; this->score = -1; this->index = index; this->abbreviation = '#';
}
ChessPiece::~ChessPiece() = default;

King::King(char color, vec2<int> pos, int index) : ChessPiece(color, pos, index) {score = 0; abbreviation = 'K';}
vector<PieceMove> King::getPositions(Table* t) {
    vector<PieceMove> moves;

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
vector<PieceMove> Queen::getPositions(Table* t) {
    vector<PieceMove> moves, rmoves, bmoves;

    Rook r(color, pos, index);;
    rmoves = r.getPositions(t);
    moves.insert(moves.begin(), rmoves.begin(), rmoves.end());

    Bishop b(color, pos, index);;
    bmoves = b.getPositions(t);
    moves.insert(moves.begin(), bmoves.begin(), bmoves.end());

    return moves;
} // {DONE}

Rook::Rook(char color, vec2<int> pos, int index) : ChessPiece(color, pos, index) {score = 5; abbreviation = 'R';}
vector<PieceMove> Rook::getPositions(Table* t) {
    vector<PieceMove> moves;
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
vector<PieceMove> Bishop::getPositions(Table* t) {
    vector<PieceMove> moves;

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
vector<PieceMove> Knight::getPositions(Table* t) {
    vector<PieceMove> moves;

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
vector<PieceMove> Pawn::getPositions(Table* t) {
    vector<PieceMove> moves;

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

// TODO verifica asta
ChessPiece* Pawn::promotePawn(Table* table, char op = 'q') {
    switch (op) {
        case 'q':
            return new Queen(color, pos, table->pieces[color == 'w' ? 0 : 1].size());
        case 'n':
            return new Knight(color, pos, table->pieces[color == 'w' ? 0 : 1].size());
        case 'r':
            return new Rook(color, pos, table->pieces[color == 'w' ? 0 : 1].size());
        case 'b':
            return new Bishop(color, pos, table->pieces[color == 'w' ? 0 : 1].size());
        default:
            assert("Pawn promote operation is not valid" && op);
    }
    return nullptr;
}

bool King::isInCheck(Table* table) {
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
			if (table->hasNoPiecesBetween_axis(table->pieces[line][8]->pos, pos))
				return true;

	if (table->pieces[line][9])
		if (table->pieces[line][9]->pos.x == pos.x || table->pieces[line][9]->pos.y == pos.y)
			if (table->hasNoPiecesBetween_axis(table->pieces[line][9]->pos, pos))
				return true;

	// Check from knight
	if (table->pieces[line][10])
		if ((abs(table->pieces[line][10]->pos.x - pos.x) == 2 && abs(table->pieces[line][10]->pos.y - pos.y) == 1) ||
			(abs(table->pieces[line][10]->pos.y - pos.y) == 2 && abs(table->pieces[line][10]->pos.x - pos.x) == 1))
				return true;

	if (table->pieces[line][11])
		if ((abs(table->pieces[line][11]->pos.x - pos.x) == 2 && abs(table->pieces[line][11]->pos.y - pos.y) == 1) ||
			(abs(table->pieces[line][11]->pos.y - pos.y) == 2 && abs(table->pieces[line][11]->pos.x - pos.x) == 1))
				return true;

	// Check from bishop
	if (table->pieces[line][12] && table->isSquareOfTheSameColor(this, table->pieces[line][12]))
		if (abs(table->pieces[line][12]->pos.x - pos.x) == abs(table->pieces[line][12]->pos.y - pos.y))
			if (table->hasNoPiecesBetween_diagonal(table->pieces[line][12]->pos, pos))
				return true;

	if (table->pieces[line][13] && table->isSquareOfTheSameColor(this, table->pieces[line][13]))
		if (abs(table->pieces[line][13]->pos.x - pos.x) == abs(table->pieces[line][13]->pos.y - pos.y))
			if (table->hasNoPiecesBetween_diagonal(table->pieces[line][13]->pos, pos))
				return true;

	// Check from queen(s)
    for (int i = 15; i < table->pieces[line].size(); i++)
        if (table->pieces[line][i]) {
            if (table->pieces[line][i]->pos.x == pos.x || table->pieces[line][i]->pos.y == pos.y)
                if (table->hasNoPiecesBetween_axis(table->pieces[line][i]->pos, pos))
                    return true;

            if (table->isSquareOfTheSameColor(this, table->pieces[line][i]))
                if (abs(table->pieces[line][i]->pos.x - pos.x) == abs(table->pieces[line][i]->pos.y - pos.y))
                    if (table->hasNoPiecesBetween_diagonal(table->pieces[line][i]->pos, pos))
                        return true;
        }

	return false;
}
