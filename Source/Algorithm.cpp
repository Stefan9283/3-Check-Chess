
#include "Algorithm.h"

std::string RandomChessPiecePicker::pickMove(Table* t) {
    srand(time(0));
    while (1) {
        int index = rand() % t->pieces.size();
        if (t->pieces[t->orientation][index]) {
            std::vector<PieceMove> moves = t->pieces[t->orientation][index]->getPositions(t);
            int moveIndex = rand() % moves.size();
            return t->coords2string(t->pieces[t->orientation][index]->pos) + t->coords2string(moves[moveIndex].ownMove);
        }
    }
}

