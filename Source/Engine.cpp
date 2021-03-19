#include "Engine.h"

Engine::Engine() {
    char buffer[256];

    signal(SIGTERM, SIG_IGN);
    signal(SIGINT, SIG_IGN);

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    bool editMode = false;

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
            delete t;
            t = new Table();
            continue;
        }
        if (strstr(buffer, "go")) {
            editMode = false;
            std::string move = t->getARandomMove();
            std::cout << move << "\n";
            t->parseMove(move.c_str());
            continue;
        }
        if (strstr(buffer, "force")) {
            editMode = true;
        }
        if (strstr(buffer, "quit")) {
            delete t;
            break;
        }

        if (buffer[0] >= 'a' && buffer[0] <= 'z' && buffer[1] >= '1' && buffer[1] <= '9') {
            t->movePiece(buffer);
            if (!editMode) {
                std::string move = t->getARandomMove();
                std::cout << move << "\n";
                t->parseMove(move.c_str());
            }
        }
    }
}

Engine::~Engine() {

}
