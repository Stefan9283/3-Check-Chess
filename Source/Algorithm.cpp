
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

