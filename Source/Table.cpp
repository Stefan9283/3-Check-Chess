
#include "Table.h"

Table::Table() {
    for (int i = 0; i < DIM; ++i) {
        vector<Square *> line;
        for (int j = 0; j < DIM; ++j) {
            line.push_back(new Square())
        }
        mat.push_back(line);
    }

    for (int k = 0; k < DIM; ++k) {
        line[1][k]->cp = new Pawn('w', vec2{1, k});
        line[6][k]->cp = new Pawn('b', vec2{6, k});
    }

    line[0][0]->cp = new Rook('w', vec2{0, 0});
    line[0][7]->cp = new Rook('w', vec2{0, 7});
    line[7][0]->cp = new Rook('b', vec2{7, 0});
    line[7][7]->cp = new Rook('b', vec2{7, 7});

    line[0][1]->cp = new Knight('w', vec2{0, 1});
    line[0][6]->cp = new Knight('w', vec2{0, 6});
    line[7][1]->cp = new Knight('b', vec2{7, 1});
    line[7][6]->cp = new Knight('b', vec2{7, 6});

    line[0][2]->cp = new Bishop('w', vec2{0, 2});
    line[0][5]->cp = new Bishop('w', vec2{0, 5});
    line[7][2]->cp = new Bishop('b', vec2{7, 2});
    line[7][5]->cp = new Bishop('b', vec2{7, 5});

    line[0][3]->cp = new Queen('w', vec2{0, 3});
    line[0][4]->cp = new King('w', vec2{0, 4});

    line[7][3]->cp = new King('b', vec2{7, 3});
    line[7][4]->cp = new Queen('b', vec2{7, 4});
}