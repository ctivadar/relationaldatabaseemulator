// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "silly.h"

void Silly::run() {
    string cmd;
    string junk;
    do {
        cout << "% ";
        cin >> cmd;
        if (cmd[0] == '#') {
            comment();
        } else if (cmd[0] == 'C') {
            if (cmd == "CREATE") {
                create();
            }
        } else if (cmd[0] == 'R') {
            if (cmd == "REMOVE") {
                remove();
            }
        } else if (cmd[0] == 'I') {
            if (cmd == "INSERT") {
                insert();
            }
        } else if (cmd[0] == 'P') {
            if (cmd == "PRINT") {
                print();
            }
        } else if (cmd[0] == 'D') {
            if (cmd == "DELETE") {
                delete_function();
            }
        } else if (cmd[0] == 'J') {
            if (cmd == "JOIN") {
                join();
            }
        } else if (cmd[0] == 'G') {
            if (cmd == "GENERATE") {
                generate();
            }
        } else if (cmd[0] == 'Q') {
            if (cmd == "QUIT") {
                cout << "Thanks for being silly!\n";
            }
        } else {
            cout << "Error: unrecognized command\n";
            getline(cin, junk);
        }
    } while (cmd != "QUIT");
}
