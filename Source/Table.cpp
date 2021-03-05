
#include "Table.h"

Table::Table() {
    for (int i = 0; i < height; ++i) {
        vector<Square *> line;
        for (int j = 0; j < width; ++j) {
            line.push_back(new Square());
        }
        squares.push_back(line);
    }

    for (int k = 0; k < width; ++k) {
        squares[1][k]->cp = new Pawn('w', vec2{1, k});
        squares[6][k]->cp = new Pawn('b', vec2{6, k});
    }

    squares[0][0]->cp = new Rook('w', vec2{0, 0});
    squares[0][7]->cp = new Rook('w', vec2{0, 7});
    squares[7][0]->cp = new Rook('b', vec2{7, 0});
    squares[7][7]->cp = new Rook('b', vec2{7, 7});

    squares[0][1]->cp = new Knight('w', vec2{0, 1});
    squares[0][6]->cp = new Knight('w', vec2{0, 6});
    squares[7][1]->cp = new Knight('b', vec2{7, 1});
    squares[7][6]->cp = new Knight('b', vec2{7, 6});

    squares[0][2]->cp = new Bishop('w', vec2{0, 2});
    squares[0][5]->cp = new Bishop('w', vec2{0, 5});
    squares[7][2]->cp = new Bishop('b', vec2{7, 2});
    squares[7][5]->cp = new Bishop('b', vec2{7, 5});

    squares[0][3]->cp = new Queen('w', vec2{0, 3});
    squares[0][4]->cp = new King('w', vec2{0, 4});

    squares[7][3]->cp = new King('b', vec2{7, 3});
    squares[7][4]->cp = new Queen('b', vec2{7, 4});
}
Table::~Table() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (squares[i][j]->cp)
                delete squares[i][j]->cp;
            delete squares[i][j];
        }
    }
}

void Table::move(ChessPiece *cp, vec2 newPos) {
    assert(isInside(newPos) && "Can't move piece outside the table");
    assert(cp != nullptr && "Piece meant to be moved is null");
    cp->prevPos = cp->position;
    squares[cp->position.x][cp->position.y]->cp = nullptr;
    cp->position = newPos;
    squares[newPos.x][newPos.y]->cp = cp;

}
void Table::remove(ChessPiece *cp) {
    assert(cp != nullptr && "Piece meant to be deleted is null");
    squares[cp->position.x][cp->position.y]->cp = nullptr;
    delete cp;
}

bool Table::canIPlaceItHere(ChessPiece *cp, Square *sq) {
    if (sq->cp) return cp->color == sq->cp->color;
    return true;
}

string Table::getCoords(vec2 pos) {
    assert(isInside(pos) && "Position outside of the table");
    string s = "a";
    s[0] += pos.x;

    return s.append(to_string(pos.y + 1));
}
bool Table::isInside(vec2 pos) const {
    return pos.x < width && pos.x >= 0 && pos.y >= 0 && pos.y < height;
}
Table *Table::cloneTable(ChessPiece *cp, vec2 newPos) {
    Table* t = new Table(*this);
    for (int i = 0; i < t->height; ++i) {
        for (int j = 0; j < t->width; ++j) {
            t->squares[i][j] = new Square(*squares[i][j]);
            ChessPiece* c = t->squares[i][j]->cp;
            if (!c) continue;

            if(dynamic_cast<Pawn*>(c))
                t->squares[i][j]->cp = new Pawn(*dynamic_cast<Pawn*>(c));
            else if(dynamic_cast<Rook*>(c))
                t->squares[i][j]->cp = new Rook(*dynamic_cast<Rook*>(c));
            else if(dynamic_cast<Bishop*>(c))
                t->squares[i][j]->cp = new Bishop(*dynamic_cast<Bishop*>(c));
            else if(dynamic_cast<Queen*>(c))
                t->squares[i][j]->cp = new Queen(*dynamic_cast<Queen*>(c));
            else if(dynamic_cast<Knight*>(c))
                t->squares[i][j]->cp = new Knight(*dynamic_cast<Knight*>(c));
            else if(dynamic_cast<King*>(c))
                t->squares[i][j]->cp = new King(*dynamic_cast<King*>(c));
        }
    }
    t->move(t->squares[cp->position.x][cp->position.y]->cp, newPos);
    return t;
}


int Table::getSquareScore(Square *sq, char myColor) {
    if (!sq || !sq->cp) return 0;
    return sq->cp->score;
}
int Table::getTotalScore(char color) {
    assert(color == 'w' || color == 'b' && "Can't calculate total score for anything else besides black and white");
    int total = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (squares[i][j]->cp && squares[i][j]->cp->color == color)
                total += squares[i][j]->cp->score;
        }
    }
    return total;
}

void Table::printTable() {
    cout << "###########################\n";
    for (int i = height - 1; i >= 0; i--) {
        std::cout << (char)('A' + i) << "| ";
        for (int j = 0; j < width; ++j) {
            if (squares[i][j]->cp)
                cout << " " << squares[i][j]->cp->score << " ";
            else cout << " - ";
        }
        cout << "\n";
    }

    cout << "   ------------------------\n";
    cout << "   ";
    for (int j = 0; j < width; ++j)
        cout << " " << j + 1 << " ";
    cout << "\n###########################\n";

}


