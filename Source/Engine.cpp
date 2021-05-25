#include "Engine.h"

Engine::Engine() {
    char buffer[256];
    bool editMode = false;

    signal(SIGTERM, SIG_IGN);
    signal(SIGINT, SIG_IGN);

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    while (true) {
        fflush(stdout);
        char* res = fgets(buffer, 256, stdin);

        if (strstr(buffer, "xboard"))
            continue;

        if (strstr(buffer, "protover 2")) {
            cout << "feature sigint=0 sigterm=0 san=0 name=Maximuss\n";
            continue;
        }

        if (strstr(buffer, "new")) {
            delete t;
            t = new Table();
            continue;
        }




        if (strstr(buffer, "go")) {
            editMode = false;
            string move = t->getBestMove(3);
            cout << move << "\n";
            t->parseMove(move.c_str());
            continue;
        }

        if (strstr(buffer, "force"))
            editMode = true;

        if (strstr(buffer, "quit")) {
            delete t;
            break;
        }

        if (buffer[0] >= 'a' && buffer[0] <= 'z' && buffer[1] >= '1' && buffer[1] <= '9') {
            t->movePiece(buffer);

            if (((King*)t->pieces[1][14])->isInCheck(t)){
        		t->checks[1]++;
			}

            if (t->checks[1] >= 3)
                cout << "resign" << "\n";
            else if (!editMode) {
                string move = t->getBestMove(3);

                cout << move << "\n";
                t->parseMove(move.c_str());
				if (((King*)t->pieces[0][14])->isInCheck(t)){
        			t->checks[0]++;
				}
            }
        }
    }
}

Engine::~Engine() {

}
