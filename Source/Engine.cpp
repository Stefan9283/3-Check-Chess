
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
        if (strstr(buffer, "quit")) {
            if (t)
                delete t;
            break;
        }
        //if (strlen(buffer) == 4)
        //    table->movePiece(buffer);
        if (buffer[0] <= 'z' && buffer[0] >= 'a'
            && buffer[1] <= '9' && buffer[1] >= '1'
            //&& buffer[2] <= 'z' && buffer[2] >= 'a'
            //&& buffer[3] <= '9' && buffer[3] >= '1'
                ) {
            t->movePiece(buffer);
            std::string mv = t->makeBestMove();
            fflush(stdout);
            std::cout << mv.c_str() << "\n";
            //table->movePiece(mv.c_str() + 5);
        }

        //char from[3], to[3];
        //from[0] = buffer[0]; from[1] = buffer[1]; from[2] = '\0';
        //to[0] = buffer[2]; to[1] = buffer[3]; to[2] = '\0';
        //table->movePiece(table->getPiece(from), to);

        //std::cout << "move f7f5\n";
        //std::cout << table->makeBestMove().c_str() << "\n";
    }

}

Engine::~Engine() {

}
