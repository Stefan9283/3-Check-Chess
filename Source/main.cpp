#include <common.h>
#include "Table.h"

int main() {
    Table* table = nullptr;
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

        if (strstr(buffer, "quit")) {
            if (table)
                delete table;

            break;
        }

        if (buffer[0] >= 'a' && buffer[0] <= 'h')
            if (buffer[1] >= '1' && buffer[1] <= '8') {
                //char from[3], to[3];

                //from[0] = buffer[0]; from[1] = buffer[1]; from[2] = '\0';
                //to[0] = buffer[2]; to[1] = buffer[3]; to[2] = '\0';

                //std::cout << table->pickAMove() << "\n";

                //std::cout << table->makeBestMove();
               std::string move = table->getARandomMove(1);
               table->parseMove(move.c_str());
               std::cout << move << "\n";
            }
    }

    return 0;
}
