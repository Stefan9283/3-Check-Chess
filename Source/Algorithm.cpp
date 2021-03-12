
#include "Algorithm.h"
#include <fstream>

using namespace std;

std::string RandomChessPiecePicker::pickMove(Table* t) {
    srand(time(0));
    std::ofstream f("out2.txt");
    
    streambuf* stream_buffer_cout = cout.rdbuf(); 
    streambuf* stream_buffer_file = f.rdbuf(); 
    cout.rdbuf(stream_buffer_file); 
    while (1) {
        int index = rand() % t->pieces.size();
        f << "AAAAAAAAAAAAAAAAAAAAA\n";
        if (t->pieces[t->orientation][index]) {
            std::vector<PieceMove> moves = t->pieces[t->orientation][index]->getPositions(t);
            int moveIndex = rand() % moves.size();
            f << index << " " << moveIndex << " " << t->coords2string(t->pieces[t->orientation][index]->pos) + t->coords2string(moves[moveIndex].ownMove) << "\n";
            t->printGameBoard();            
            cout.rdbuf(stream_buffer_cout); 
            f.close();

            return t->coords2string(t->pieces[t->orientation][index]->pos) + t->coords2string(moves[moveIndex].ownMove);
        }
    }
}
vec2<float> RandomChessPiecePicker::CalculateStateScore(Table *t) {
    return vec2<float>();
}



std::string dontHurtMe::pickMove(Table *t) {
    return std::string();
}
vec2<float> dontHurtMe::CalculateStateScore(Table *t) {
    vec2<float> scores{};
    vec2<int> defendingPieces{};
    for (ChessPiece* i : t->pieces[0]) {
        if (i) {
            scores.x++;
            if(!dynamic_cast<King*>(i) && !dynamic_cast<Pawn*>(i))
                scores.x += 1 / i->pos.getDistanceTo(t->pieces[0][14]->pos);
        }
    }
    for (auto & i : t->pieces[1]) {
        if (i) {
            scores.x++;
            if(!dynamic_cast<King*>(i) && !dynamic_cast<Pawn*>(i))
                scores.x += 1 / i->pos.getDistanceTo(t->pieces[1][14]->pos);
        }
    }

    return scores/16 -
    vec2<float>{
            (float)dynamic_cast<King*>(t->pieces[0][14])->checks,
            (float)dynamic_cast<King*>(t->pieces[1][14])->checks
    };
}

std::string BringThemOn::pickMove(Table *t) {
    return std::string();
}
vec2<float> BringThemOn::CalculateStateScore(Table *t) {
    vec2<float> scores{};
    vec2<float> pieceCounter{};

    for (ChessPiece* piece : t->pieces[0]) {
        if (!piece) continue;
        pieceCounter.x++;
        int maxValue = 0;
        for (PieceMove move : piece->getPositions(t)) {
            maxValue = max(maxValue, t->getSquareScore(t->squares[move.ownMove.x][move.ownMove.y], 'w'));
            if (!t->isKingInDanger(piece, move.ownMove))
                scores.x = 5;
        }
        scores.x = max((float)maxValue, scores.y);
    }

    for (ChessPiece* piece : t->pieces[1]) {
        if (!piece) continue;
        pieceCounter.y++;
        int maxValue = 0;
        for (PieceMove move : piece->getPositions(t)) {
            maxValue = max(maxValue, t->getSquareScore(t->squares[move.ownMove.x][move.ownMove.y], 'b'));
            if (!t->isKingInDanger(piece, move.ownMove))
                scores.y = 5;
        }
        scores.y = max((float)maxValue, scores.x);
    }


    return scores; //TODO use this --> 10 * (scores/9 + pieceCounter/16);
}

std::string IamDeathIncarnate::pickMove(Table *t) {
    return std::string();
}
vec2<float> IamDeathIncarnate::CalculateStateScore(Table *t) {
    vec2<float> scores{};

    for (ChessPiece* piece : t->pieces[0]) {
        if (!piece) continue;
        int maxValue = 0;
        for (PieceMove move : piece->getPositions(t)) {
            maxValue = max(maxValue, t->getSquareScore(t->squares[move.ownMove.x][move.ownMove.y], 'w'));
            if (!t->isKingInDanger(piece, move.ownMove)) {
                scores.x = 9;
                goto exitw;
            }
        }
        scores.x = max((float)maxValue, scores.y);
    }
    exitw:

    for (ChessPiece* piece : t->pieces[1]) {
        if (!piece) continue;
        int maxValue = 0;
        for (PieceMove move : piece->getPositions(t)) {
            maxValue = max(maxValue, t->getSquareScore(t->squares[move.ownMove.x][move.ownMove.y], 'b'));
            if (!t->isKingInDanger(piece, move.ownMove)) {
                scores.y = 9;
                goto exitb;
            }
        }
        scores.y = max((float)maxValue, scores.x);
    }
    exitb:

    return scores;
}

std::string UberMode::pickMove(Table *t) {
    return std::string();
}
vec2<float> UberMode::CalculateStateScore(Table *t) {
    vec2<float> scores{};
    for (ChessPiece* piece : t->pieces[0]) {
        if (!piece) continue;
        for (PieceMove move : piece->getPositions(t)) {
            if (!t->isKingInDanger(piece, move.ownMove))
                scores.x++;
        }
    }
    for (ChessPiece* piece : t->pieces[1]) {
        if (!piece) continue;
        for (PieceMove move : piece->getPositions(t)) {
            if (!t->isKingInDanger(piece, move.ownMove))
                scores.y++;
        }
    }
    return scores;
}
