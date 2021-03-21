#include "Engine.h"

Engine::Engine() {
    char buffer[256];

    signal(SIGTERM, SIG_IGN);
    signal(SIGINT, SIG_IGN);

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    while (true) {
        fflush(stdout);
        fgets(buffer, 256, stdin);

        if (strstr(buffer, "xboard"))
            continue;

        if (strstr(buffer, "protover 2")) {
            std::cout << "feature sigint=0 sigterm=0 san=0 name=Maximuss\n";
            continue;
        }

        if (strstr(buffer, "new")) {
            if (t)
                delete t;

            t = new Table();
            continue;
        }

        if (strstr(buffer, "go")) {
            std::string move = t->getBestMove(4);
            t->parseMove(move.c_str());
            std::cout << move << "\n";
            continue;
        }

        if (strstr(buffer, "quit")) {
            if (t)
                delete t;

            break;
        }

        if (buffer[0] >= 'a' && buffer[0] <= 'z' && buffer[1] >= '1' && buffer[1] <= '9') {
            t->movePiece(buffer);
            std::string move = t->getBestMove(5);
            t->parseMove(move.c_str());
            std::cout << move << "\n";
        }
    }
}

Engine::~Engine() {

}
