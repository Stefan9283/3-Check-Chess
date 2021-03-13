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
    cmd->append(") ");
}

int main() {
    ifstream f("xboard.debug");
    string line ;
    string cmd = "table->moveInAdvance(";
    while(getline(f, line ) ) 
    {
        if (strstr(line.c_str(), "first : ") && !strstr(line.c_str(), "tim") && !strstr(line.c_str(), "accept")
        && !strstr(line.c_str(), "=") && !strstr(line.c_str(), "xboard") && !strstr(line.c_str(), "new") && !strstr(line.c_str(), "level")
        && !strstr(line.c_str(), "hard") && !strstr(line.c_str(), "post")) {
            if (strstr(line.c_str(), "move"))
                addMove(&cmd, strstr(line.c_str(), "first : ") + 8 + 5);
            else
                addMove(&cmd, strstr(line.c_str(), "first : ") + 8);
        }
    }
    cmd[cmd.size() - 1] = ')';
    cmd.push_back(';');

    cout << cmd << "\n";

    return 0;
}