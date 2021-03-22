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
            if (table)
                delete table;

            table = new Table();
            continue;
        }

        if (strstr(buffer, "go")) {
            std::string move = table->getBestMove(4);
            table->parseMove(move.c_str());
            std::cout << move << "\n";
            continue;
        }

        if (strstr(buffer, "quit")) {
            if (table)
                delete table;

            break;
        }

        if (buffer[0] >= 'a' && buffer[0] <= 'z' && buffer[1] >= '1' && buffer[1] <= '9') {
            table->movePiece(buffer);

            if (table->hasLegalMoves()) {
                std::string move = table->getBestMove(5);
                table->parseMove(move.c_str());
                std::cout << move << "\n";
            }
        }
    }
}

Engine::~Engine() {

}
