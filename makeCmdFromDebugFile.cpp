#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

void addMove(string* cmd, const char* move) {
    cmd->append("(");
    cmd->push_back(move[0]);
    cmd->push_back(move[1]);
    cmd->append(", ");
    cmd->push_back(move[2]);
    cmd->push_back(move[3]);
    cmd->append("), ");
}

int main(int argc, char** argv) {

    ifstream f;

    if (argc == 1)
        f = ifstream("xboard.debug");
    else
        f = ifstream(argv[1]);
    string line ;
    string cmd = "table->moveInAdvance(\"";
    while(getline(f, line ) )
    {
        if (strstr(line.c_str(), "first : ") && !strstr(line.c_str(), "tim") && !strstr(line.c_str(), "accept")
        && !strstr(line.c_str(), "=") && !strstr(line.c_str(), "xboard") && !strstr(line.c_str(), "new") && !strstr(line.c_str(), "level")
        && !strstr(line.c_str(), "hard") && !strstr(line.c_str(), "result") && !strstr(line.c_str(), "post") && !strstr(line.c_str(), "force")
        && !strstr(line.c_str(), "quit") && !strstr(line.c_str(), "3_Check_Chess")) {
            if (strstr(line.c_str(), "move"))
                addMove(&cmd, strstr(line.c_str(), "first : ") + 8 + 5);
            else
                addMove(&cmd, strstr(line.c_str(), "first : ") + 8);
        }
    }

    cmd[cmd.size() - 2] = '"';
    cmd[cmd.size() - 1] = ',';
    cmd.append(" 'w');");

    cout << cmd << "\n";

    return 0;
}